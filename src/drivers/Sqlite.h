#include <string>
#include <vector>

#include "Driver.h"

class Sqlite: public Driver {

public:

    Sqlite();
    Sqlite( std::string configuration );
    virtual ~Sqlite() = default;

    virtual void select(
        std::string table,
        std::vector<std::string> selection,
        std::string where
    ) = 0;

private:

};