
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
    for ( Session* s: this->_session )
        delete s;

}


void App::run() {

    CROW_ROUTE(this->_app, "/events").methods(crow::HTTPMethod::Get)
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

                if ( i + 1 == es.size() )
                    res += "]}";
                else
                    res += ",";

            }

            crow::response response;
            response.body = res;
            response.set_header("content-type", "application/json");
            return response;

    });

    this->_app.port(this->_port).run();

}


void App::landing_page() {


}


void App::auth() {


}


void App::postAction(
    int session_id, int report_id, std::string action,
    std::string description
) {


}


void App::getStats() {


}