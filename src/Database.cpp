
#include "Database.h"
#include "datatypes/Session.h"
#include "drivers/Sqlite.h"
#include "logger.h"

Database::Database( Config& configuration ) {

    if ( configuration.get( "driver" ) == "sqlite" )
        this->_connection = new Sqlite( configuration );

    logger( 0, "Created database interface !" );

}


Database::~Database() {

    delete this->_connection;

}


std::vector<Event> Database::selectEvents(
    std::string id,
    std::string date,
    std::string detail_level,
    std::string decision_relevance,
    std::string uncertainty_level
) {

    return {};

}


bool Database::insertSession(
    std::string id, std::string creation_date,
    std::string ingame_date, std::string locked
) {

    return true;

}


Session Database::selectSession( std::string id ) {

    return Session( this );

}


std::vector<Note> Database::selectNotes(
    std::string id, std::string session_id
) {

    return {};

}
