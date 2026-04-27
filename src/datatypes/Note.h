#pragma once
#include <string>

class Note {

    public:

        Note(
          int id,
          int session_id,
          std::string title,
          std::string content
        );

        std::string toJson();

        int getId() { return this->_id; }

    private:

        int _id;
        int _session_id;
        std::string _title;
        std::string _content;

};