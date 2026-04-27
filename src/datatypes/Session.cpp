#include "Session.h"
#include "logger.h"


Session::Session() { }


Session::Session(
    int id,
    std::string creation_date,
    std::string ingame_date,
    int locked
) {

    this->_id = id;
    this->_creation_date = creation_date;
    this->_ingame_date = ingame_date;
    this->_locked = locked;

}


std::string Session::toJson() {

    return
        "{\"id\": " + std::to_string( this->_id ) + "," +
        "\"creation_date\": \"" + this->_creation_date + "\"," +
        "\"ingame_date\": \"" + this->_ingame_date + "\"," +
        "\"locked\": " + std::to_string( this->_locked ) + "}";

}
