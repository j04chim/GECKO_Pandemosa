#pragma once
#include <string>
#include <vector>

class Driver {

    public:

        Driver();
        Driver( std::string configuration );
        virtual ~Driver() = default;

        virtual void select(
            std::string table,
            std::vector<std::string> selection,
            std::string where
        ) = 0;

    private:

};