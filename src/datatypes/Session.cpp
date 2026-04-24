#include "Session.h"
#include "logger.h"

Session::Session( Database* db ) {

    this->_db = db;

}


bool Session::open() {

    logger( 0, "Session opened" );

    return true;

}


bool Session::close() {

    logger( 0, "Session closed" );

    return true;

}


std::string Session::toJson() {

    return
        "{\"id\": " + std::to_string( this->_id ) + "\"," +
        "\"creation_date\": " + std::to_string( this->_creation_date ) + "\"," +
        "\"ingame_date\": " + std::to_string( this->_ingame_date ) + "\"," +
        "\"locked\": " + std::to_string( this->_locked ) + "\"}";

}
