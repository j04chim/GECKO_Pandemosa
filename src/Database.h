#pragma once
#include <string>
#include <vector>

#include "datatypes/Session.h"
#include "datatypes/Event.h"
#include "datatypes/Note.h"

class Database {

    public:

        Database() = default;
        virtual ~Database() = default;

        virtual std::vector<Event> selectEvents(
            std::string id = "",
            std::string report_date = "",
            std::string detail_level = "",
            std::string decision_relevance = "",
            std::string uncertainty_level = ""
        ) = 0;

        virtual int insertSession(
            std::string creation_date = "", std::string ingame_date = ""
        ) = 0;

        virtual Session selectSession( std::string id = "" ) = 0;

        virtual std::vector<Note> selectNotes(
            std::string id = "", std::string session_id = ""
        ) = 0;

        virtual int insertAction(
            int session_id, int report_id, std::string action,
            std::string description
        ) = 0;

        virtual int insertNote(
            int session_id, std::string title,
            std::string content
        ) = 0;

};