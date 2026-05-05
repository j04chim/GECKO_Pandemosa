#pragma once
#include <string>

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "Database.h"
#include "datatypes/Config.h"

/**
 * @class App
 * @brief Kausjan's main process.
 *
 * Kausjan's main process.
 * Config:
 * port=integer
 */
class App {

    public:

        App( Config& configuration );
        ~App();

        /**
         * @fn run
         * @brief Run the application.
         */
        void run();

    private:

        Database* _database;
        crow::App<crow::CORSHandler> _app;
        int _port;

};