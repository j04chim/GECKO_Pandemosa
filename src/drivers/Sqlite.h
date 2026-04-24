#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>

#include "Driver.h"
#include "../datatypes/Config.h"

class Sqlite: public Driver {

    public:

        Sqlite( Config& configuration );
        virtual ~Sqlite();

        virtual Request select(
            std::string table,
            std::vector<std::string> selection,
            std::string where
        );

    private:

};