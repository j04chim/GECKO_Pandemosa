#pragma once
#include <string>
#include <sqlite3.h>
#include <vector>

#include "../Database.h"
#include "../datatypes/Config.h"
#include "../datatypes/Session.h"
#include "../datatypes/Event.h"
#include "../datatypes/Note.h"

class Sqlite: public Database {

    public:

        Sqlite( Config& );
        virtual ~Sqlite();

        virtual std::vector<Event> selectEvents(
            std::string id = "",
            std::string report_date = "",
            std::string detail_level = "",
            std::string decision_relevance = "",
            std::string uncertainty_level = ""
        ) override;

        virtual int insertSession(
            std::string creation_date = "", std::string ingame_date = ""
        ) override;

        virtual Session selectSession( std::string id = "" ) override;

        virtual std::vector<Note> selectNotes(
            std::string id = "", std::string session_id = ""
        ) override;

        virtual int insertAction(
            int session_id, int report_id, std::string action,
            std::string description
        ) override;

        virtual int insertNote(
            int session_id, std::string title,
            std::string content
        ) override;

    private:

        sqlite3* _db;
        bool _loaded;

};