#pragma once
#include <string>

/**
 * @class Note
 * @brief Note data model
 */
class Note {

    public:

        Note(
          int id,
          int session_id,
          std::string title,
          std::string content
        );

        /**
         * @fn toJson
         * @brief Return a JSON string representing the object.
         * @return std::string JSON string
         */
        std::string toJson();

        /**
         * @fn getId
         * @brief Return object's id
         * @return int id of the object
         */
        int getId() { return this->_id; }

    private:

        int _id;
        int _session_id;
        std::string _title;
        std::string _content;

};


/**
 * @class NoteLink
 * @brief NoteLink data model
 */
class NoteLink {

    public:

        NoteLink(
          int session_id,
          int note_a,
          int note_b
        );

        /**
         * @fn toJson
         * @brief Return a JSON string representing the object.
         * @return std::string JSON string
         */
        std::string toJson();

        /**
         * @fn getSessionId
         * @brief Return object's id
         * @return int id of the object
         */
        int getSessionId() { return this->_session_id; }

    private:

        int _session_id;
        int _note_a;
        int _note_b;

};