#include <string>
#include <vector>

#include "Database.h"

class App {

    public:

        App();
        App( std::string configuration );
        ~App();

        void landing_page();
        void auth();
        void getEvents( std::string date );
        void postAction(
            int session_id, int report_id, std::string action,
            std::string description
        );
        void getStats();

    private:

        std::vector<Session> _session;
        Database _database;

};