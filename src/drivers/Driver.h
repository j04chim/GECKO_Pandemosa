#pragma once
#include <string>
#include <vector>

#include "../datatypes/Request.h"

class Driver {

    public:

        virtual ~Driver() = default;

        virtual Request select(
            std::string table,
            std::vector<std::string> selection,
            std::string where
        ) = 0;

};