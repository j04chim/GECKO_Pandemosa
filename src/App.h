#pragma once
#include <string>

#include "crow.h"
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
        crow::SimpleApp _app;
        int _port;

};