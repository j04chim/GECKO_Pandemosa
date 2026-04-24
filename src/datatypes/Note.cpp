#include "Note.h"


Note::Note(
          int id,
          int session_id,
          std::string title,
          std::string content
) {

    this->_id = id;
    this->_session_id = session_id;
    this->_title = title;
    this->_content = content;

}


std::string Note::toJson() {

    return
        "{\"id\": \"" + std::to_string( this->_id ) + "\"," +
        "\"session_id\": \"" + std::to_string( this->_session_id ) + "\"," +
        "\"title\": \"" + this->_title + "\"," +
        "\"content\": \"" + this->_content + "\"}";

}