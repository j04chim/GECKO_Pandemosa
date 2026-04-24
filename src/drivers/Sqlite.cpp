
#include "Sqlite.h"
#include "logger.h"


Sqlite::Sqlite( Config& configuration ) {

    logger( 0, "Created Sqlite connection !" );

}


Sqlite::~Sqlite() {


}


Request Sqlite::select(
    std::string table,
    std::vector<std::string> selection,
    std::string where
) {

    return Request();

}