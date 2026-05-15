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

NoteLink::NoteLink(
    int session_id,
    int note_a,
    int note_b
) {

    this->_session_id = session_id;
    this->_note_a = note_a;
    this->_note_b = note_b;

}

std::string NoteLink::toJson() {

    return
        "{\"session_id\": \"" + std::to_string( this->_session_id ) + "\"," +
        "\"note_a\": \"" + std::to_string( this->_note_a ) + "\"," +
        "\"note_b\": \"" + std::to_string( this->_note_b ) + "\"}";

}