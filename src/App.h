#pragma once
#include <string>
#include <vector>

#include "crow.h"
#include "Database.h"
#include "datatypes/Config.h"

class App {

    public:

        App( Config& configuration );
        ~App();

        void landing_page();
        void auth();
        void getEvents( std::string date );
        void postAction(
            int session_id, int report_id, std::string action,
            std::string description
        );
        void getStats();
        void run();

    private:

        std::vector<Session*> _session;
        Database* _database;
        crow::SimpleApp _app;
        int _port;

};