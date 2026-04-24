
#include "Sqlite.h"
#include "logger.h"


Sqlite::Sqlite( Config& configuration ) {

    logger( 0, "Created Sqlite connection !" );

}


Sqlite::~Sqlite() {


}


std::vector<Event> Sqlite::selectEvents(
    std::string id,
    std::string date,
    std::string detail_level,
    std::string decision_relevance,
    std::string uncertainty_level
) {

    return {};

}


bool Sqlite::insertSession(
    std::string id, std::string creation_date,
    std::string ingame_date, std::string locked
) {

    return true;

}


Session Sqlite::selectSession( std::string id ) {

    return Session( this );

}


std::vector<Note> Sqlite::selectNotes(
    std::string id, std::string session_id
) {

    return {};

}