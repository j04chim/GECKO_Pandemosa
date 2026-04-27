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