#include <string>
#include <vector>
#include <sqlite3.h>

#include "Driver.h"

class Sqlite: public Driver {

public:

    Sqlite();
    Sqlite( std::string configuration );
    virtual ~Sqlite() = default;

    virtual Request select(
        std::string table,
        std::vector<std::string> selection,
        std::string where
    ) = 0;

private:

};