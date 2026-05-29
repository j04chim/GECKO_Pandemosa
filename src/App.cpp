#include <ctime>
#include <dirent.h>

#include "App.h"
#include "logger.h"
#include "drivers/Sqlite.h"


class reLogger : public crow::ILogHandler {

public:

    reLogger() {}
    void log(const std::string& message, crow::LogLevel level) {

        switch (level)
            {
            case crow::LogLevel::Debug:
                    logger(0, message.c_str());
                    break;
                case crow::LogLevel::Info:
                    logger(1, message.c_str());
                    break;
                case crow::LogLevel::Warning:
                    logger(2, message.c_str());
                    break;
                case crow::LogLevel::Error:
                    logger(3, message.c_str());
                    break;
                case crow::LogLevel::Critical:
                    logger(4, message.c_str());
                    break;
            }

    }

};


App::App( Config& configuration ) {

    if ( configuration.get( "driver" ) == "sqlite" )
        this->_database = new Sqlite( configuration );
    else {
        logger( 4, "Can't access database, no driver specified in configuration !" );
        throw;
    }

    std::string port = configuration.get( "port" );
    this->_url = configuration.get( "url" );

    if ( port == "" ) {
        logger( 2, "Selecting default port 8080 as no port has been specified in configuration." );
        this->_port = 8080;
    } else
        this->_port = std::stoi( port );


    if ( this->_url == "" ) {
        logger( 2, "No URL specified, using local adress 127.0.0.1." );
        this->_url = "http://127.0.0.1:" + port + "/";
    }

}


App::~App() {

    delete this->_database;

}


void App::run() {

    reLogger log;
    crow::logger::setHandler(&log);
    auto& cors = this->_app.get_middleware<crow::CORSHandler>();
    cors.global().origin( "*" );
    this->_app.loglevel(crow::LogLevel::Warning);

    CROW_ROUTE(this->_app, "/getEvents").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            std::vector<Event> es = this->_database->selectEvents(
                req.url_params.get("id") ? req.url_params.get("id") : "",
                req.url_params.get("dt") ? req.url_params.get("dt") : "",
                req.url_params.get("dl") ? req.url_params.get("dl") : "",
                req.url_params.get("dr") ? req.url_params.get("dr") : "",
                req.url_params.get("ul") ? req.url_params.get("ul") : ""
            );

            std::string res = "{\"Events\": [";
            for ( int i = 0; i < es.size(); ++i ) {

                res += es[i].toJson();

                if ( i + 1 != es.size() )
                    res += ",";

            }
            res += "]}";

            crow::response response;
            response.body = res;
            response.set_header("content-type", "application/json");
            return response;

    });


    CROW_ROUTE(this->_app, "/createSession").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            time_t timestamp;
            time(&timestamp);
            std::string time = std::string(ctime(&timestamp)).substr(0, 24);

            Session s = this->_database->insertSession(
                time,
                "2019-12-31"
            );

            crow::response response;
            response.body = s.toJson();
            response.set_header("content-type", "application/json");
            return response;

    });

    CROW_ROUTE(this->_app, "/getSession").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string id =
                req.url_params.get("id") ? req.url_params.get("id") : "";

            if ( id == "" ) {

                response.body = "{}";
                return response;

            }

            Session s = this->_database->selectSession(id);

            response.body = s.toJson();
            return response;

    });

    CROW_ROUTE(this->_app, "/createNote").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string sd =
                req.url_params.get("sd") ? req.url_params.get("sd") : "";
            std::string ct_ugly =
                req.url_params.get("ct") ? req.url_params.get("ct") : "";
            std::string tt_ugly =
                req.url_params.get("tt") ? req.url_params.get("tt") : "";

            if ( sd == "" ) {

                response.body = "{}";
                return response;

            }

            std::string ct_good;
            for (char c: ct_ugly) {
                if (c == '\n' || c == '\r') {
                    ct_good += "\\n";
                } else if (c == '"') {
                    ct_good += "\\\"";
                }
                else {
                    ct_good += c;
                }
            }

            Note n = this->_database->insertNote(
                sd,
                tt_ugly,
                ct_good
            );

            response.body = n.toJson();
            return response;

    });

    CROW_ROUTE(this->_app, "/createNoteLink").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string sd =
                req.url_params.get("sd") ? req.url_params.get("sd") : "";
            std::string na =
                req.url_params.get("na") ? req.url_params.get("na") : "";
            std::string nb =
                req.url_params.get("nb") ? req.url_params.get("nb") : "";

            if ( sd == "" || na == "" || nb == "" ) {

                response.body = "{}";
                return response;

            }

            int n = this->_database->insertNoteLink(
                sd,
                na,
                nb
            );

            response.body = "{}";
            return response;

    });

    CROW_ROUTE(this->_app, "/getNotes").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string sd =
                req.url_params.get("sd") ? req.url_params.get("sd") : "";

            if ( sd == "" ) {

                response.body = "{}";
                return response;

            }

            std::vector<Note> sn = this->_database->selectNotes(sd);

            std::string res = "{\"Notes\": [";
            for ( int i = 0; i < sn.size(); ++i ) {

                res += sn[i].toJson();

                if ( i + 1 != sn.size() )
                    res += ",";

            }
            res += "]}";

            response.body = res;
            return response;

    });

    CROW_ROUTE(this->_app, "/getNoteLink").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string sd =
                req.url_params.get("sd") ? req.url_params.get("sd") : "";

            if ( sd == "" ) {

                response.body = "{}";
                return response;

            }

            std::vector<NoteLink> sn = this->_database->selectNoteLink(sd);

            std::string res = "{\"NoteLink\": [";
            for ( int i = 0; i < sn.size(); ++i ) {

                res += sn[i].toJson();

                if ( i + 1 != sn.size() )
                    res += ",";

            }
            res += "]}";

            response.body = res;
            return response;

    });

    CROW_ROUTE(this->_app, "/deleteNote").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string nid =
                req.url_params.get("nid") ? req.url_params.get("nid") : "";

            if ( nid == "" ) {

                response.body = "{}";
                return response;

            }

            this->_database->deleteNote(nid);

            response.body = "{}";
            return response;

    });

    CROW_ROUTE(this->_app, "/updateNote").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string nid =
                req.url_params.get("nid") ? req.url_params.get("nid") : "";
            std::string ct_ugly =
                req.url_params.get("ct") ? req.url_params.get("ct") : "";

            if ( nid == "" || ct_ugly == "" ) {

                response.body = "{}";
                return response;

            }

            std::string ct_good;
            for (char c: ct_ugly) {
                if (c == '\n' || c == '\r') {
                    ct_good += "\\n";
                } else if (c == '"') {
                    ct_good += "\\\"";
                }
                else {
                    ct_good += c;
                }
            }

            this->_database->updateNote(
                nid,
                req.url_params.get("tt") ? req.url_params.get("tt") : "",
                ct_good
            );

            response.body = "{}";
            return response;

    });

    CROW_ROUTE(this->_app, "/createAction").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {

            crow::response response;
            response.set_header("content-type", "application/json");

            std::string sd =
                req.url_params.get("sd") ? req.url_params.get("sd") : "";
            std::string rd =
                req.url_params.get("rd") ? req.url_params.get("rd") : "";
            std::string ac =
                req.url_params.get("ac") ? req.url_params.get("ac") : "";

            if ( sd == "" || rd == "" || ac == "" ) {

                response.body = "{}";
                return response;

            }

            std::vector<Event> e = this->_database->selectEvents(rd);

            std::string res = "{}";

            if ( e.size() == 1 ) {

                int n = this->_database->insertAction(
                    sd, rd, ac,
                    req.url_params.get("ds") ? req.url_params.get("ds") : ""
                );

                int f = this->_database->updateSession(sd, e[0].getDate());

                res = "{\"Action\": \"" + std::to_string(n) + "\"," +
                      "\"update\" : \"" + std::to_string(f) + "\"}";

            }

            response.body = res;
            return response;

    });

    CROW_ROUTE(this->_app, "/")
        ([this](const crow::request& req) {
        auto page = crow::mustache::load("index.html");
        crow::mustache::context ctx ({{"url", this->_url}});
        return page.render(ctx);
    });

    this->_app.port(this->_port).run();

}
