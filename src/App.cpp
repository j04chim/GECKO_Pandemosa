#include <ctime>

#include "App.h"
#include "logger.h"
#include "drivers/Sqlite.h"


App::App( Config& configuration ) {

    if ( configuration.get( "driver" ) == "sqlite" )
        this->_database = new Sqlite( configuration );

    std::string port = configuration.get( "port" );

    if ( port == "" )
        this->_port = 8080;
    else
        this->_port = std::stoi(port);

}


App::~App() {

    delete this->_database;

}


void App::run() {

	auto& cors = this->_app.get_middleware<crow::CORSHandler>();
	cors.global().origin("*");

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
            std::string ct =
                req.url_params.get("ct") ? req.url_params.get("ct") : "";

            if ( sd == "" || ct == "" ) {

                response.body = "{}";
                return response;

            }

            Note n = this->_database->insertNote(
                sd,
                req.url_params.get("tt") ? req.url_params.get("tt") : "",
                ct
            );

            response.body = n.toJson();
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

    this->_app.port(this->_port).run();

}
