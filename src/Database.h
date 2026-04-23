#include <string>
#include <vector>

#include "Session.h"
#include "Event.h"
#include "Note.h"
#include "drivers/Driver.h"
#include "drivers/Sqlite.h"

class Database {

    public:

        Database();
        Database( std::string configuration );

        std::vector<Event> selectEvents(
            std::string id = "",
            std::string date = "",
            std::string detail_level = "",
            std::string decision_relevance = "",
            std::string uncertainty_level = ""
        );
        bool insertSession(
            std::string id = "", std::string creation_date = "",
            std::string ingame_date = "", std::string locked = ""
        );
        Session selectSession( std::string id = "" );
        std::vector<Note> selectNotes(
            std::string id = "", std::string session_id = ""
        );

    private:

        Driver* _connection;

};