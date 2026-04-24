
#include "App.h"
#include "logger.h"
#include "drivers/Sqlite.h"


App::App( Config& configuration ) {

    if ( configuration.get( "driver" ) == "sqlite" )
        this->_database = new Sqlite( configuration );

    logger( 0, "Created application !" );

}


App::~App() {

    delete this->_database;
    for ( Session* s: this->_session )
        delete s;

}


void App::landing_page() {


}


void App::auth() {


}


void App::getEvents( std::string date ) {


}


void App::postAction(
    int session_id, int report_id, std::string action,
    std::string description
) {


}


void App::getStats() {


}