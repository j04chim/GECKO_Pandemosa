
#include "Sqlite.h"
#include "logger.h"


Sqlite::Sqlite( Config& configuration ) {

    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open( configuration.get( "database" ).c_str(), &this->_db );

    if( rc ) {

        logger( 3,
            ( std::string( "Failed to create Sqlite connection! " ) +
            sqlite3_errmsg( this->_db ) ).c_str()
        );
        this->_loaded = false;

    }

    this->_loaded = true;
    logger( 0, "Created Sqlite connection !" );

}


Sqlite::~Sqlite() {

    sqlite3_close(this->_db);

}


std::vector<Event> Sqlite::selectEvents(
    std::string id,
    std::string report_date,
    std::string detail_level,
    std::string decision_relevance,
    std::string uncertainty_level
) {

    std::vector<Event> result;

    sqlite3_stmt* st;
    std::string sql = "SELECT * FROM Report WHERE id > -1 ";

    if ( id != "" )
        sql += "AND id = ?1 ";
    if ( report_date != "" )
        sql += "AND report_date = ?2 ";
    if ( detail_level != "" )
        sql += "AND detail_level = ?3 ";
    if ( decision_relevance != "" )
        sql += "AND decision_relevance = ?4 ";
    if ( uncertainty_level != "" )
        sql += "AND uncertainty_level = ?5 ";

    sqlite3_prepare_v2( this->_db, sql.c_str(), -1, &st, NULL);

    if ( id != "" ) {
        sqlite3_bind_int( st, 1, std::stoi(id) );
    }
    if ( report_date != "" ) {
        sqlite3_bind_text(
            st, 2, report_date.c_str(), report_date.size(), SQLITE_TRANSIENT
        );

    }
    if ( detail_level != "" ) {
        sqlite3_bind_int( st, 3, std::stoi(detail_level) );
    }
    if ( decision_relevance != "" ) {
        sqlite3_bind_int( st, 4, std::stoi(decision_relevance) );
    }
    if ( uncertainty_level != "" ) {
        sqlite3_bind_text(
            st, 5, decision_relevance.c_str(), decision_relevance.size(),
            SQLITE_TRANSIENT
        );
    }

    int code = sqlite3_step( st );
    int first = -1;
    while ( code == SQLITE_ROW || code == SQLITE_BUSY ) {

        if ( code == SQLITE_ROW ) {

            Event tmp(
                sqlite3_column_int(st, 0),
                sqlite3_column_text(st, 1) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 1))) :
                    std::string(),
                sqlite3_column_text(st, 2) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 2))) :
                    std::string(),
                sqlite3_column_text(st, 3) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 3))) :
                    std::string(),
                sqlite3_column_int(st, 4),
                sqlite3_column_int(st, 5),
                sqlite3_column_text(st, 6) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 6))) :
                    std::string(),
                sqlite3_column_text(st, 7) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 7))) :
                    std::string(),
                sqlite3_column_int(st, 8),
                sqlite3_column_int(st, 9),
                sqlite3_column_int(st, 10),
                sqlite3_column_int(st, 11),
                sqlite3_column_int(st, 12),
                sqlite3_column_text(st, 13) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 13))) :
                    std::string()
            );

            if ( first == tmp.getId() )
                return result;
            if ( first == -1 )
                first = tmp.getId();

            result.push_back(tmp);

        }

        int code = sqlite3_step( st );

    }

    if ( code == SQLITE_ERROR )
        logger( 1,
            ( std::string( "Failed to execute request, SQLITE_ERROR: ") +
            sqlite3_errmsg( this->_db ) ).c_str()
        );

    return result;

}


int Sqlite::insertSession(
    std::string creation_date, std::string ingame_date
) {

    sqlite3_stmt* st;

    std::string sql =
        "INSERT INTO Session (creation_date, ingame_date, locked) VALUES (?, ?, ?)";

    sqlite3_bind_text(
        st, 1, creation_date.c_str(), creation_date.size(), SQLITE_TRANSIENT
    );
    sqlite3_bind_text(
        st, 2, ingame_date.c_str(), ingame_date.size(), SQLITE_TRANSIENT
    );
    sqlite3_bind_int( st, 3, 0 );


    sqlite3_prepare_v2( this->_db, sql.c_str(), -1, &st, NULL);
    int id = sqlite3_last_insert_rowid(this->_db);

    int code = sqlite3_step( st );

    if ( code == SQLITE_DONE )
        logger( 0, "Inserted new session in database" );

    if ( code == SQLITE_ERROR )
        logger( 1,
            ( std::string( "Failed to execute request, SQLITE_ERROR: ") +
            sqlite3_errmsg( this->_db ) ).c_str()
        );

    return id;

}


int Sqlite::insertAction(
    int session_id, int report_id, std::string action,
    std::string description
) {

    sqlite3_stmt* st;

    std::string sql =
        "INSERT INTO Action (session_id, report_id, action, description) VALUES (?, ?, ?, ?)";


    sqlite3_bind_int( st, 1, session_id );
    sqlite3_bind_int( st, 2, report_id );
    sqlite3_bind_text(
        st, 3, action.c_str(), action.size(), SQLITE_TRANSIENT
    );
    sqlite3_bind_text(
        st, 4, description.c_str(), description.size(), SQLITE_TRANSIENT
    );

    sqlite3_prepare_v2( this->_db, sql.c_str(), -1, &st, NULL);
    int id = sqlite3_last_insert_rowid(this->_db);

    int code = sqlite3_step( st );

    if ( code == SQLITE_DONE )
        logger( 0, "Inserted new action in database" );

    if ( code == SQLITE_ERROR )
        logger( 1,
            ( std::string( "Failed to execute request, SQLITE_ERROR: ") +
            sqlite3_errmsg( this->_db ) ).c_str()
        );

    return id;

}


int Sqlite::insertNote(
    int session_id, std::string title, std::string content
) {

    sqlite3_stmt* st;

    std::string sql =
        "INSERT INTO Action (session_id, title, content) VALUES (?, ?, ?)";

    sqlite3_bind_int( st, 1, session_id );
    sqlite3_bind_text(
        st, 3, title.c_str(), sizeof(title), SQLITE_TRANSIENT
    );
    sqlite3_bind_text(
        st, 4, content.c_str(), sizeof(content), SQLITE_TRANSIENT
    );

    sqlite3_prepare_v2( this->_db, sql.c_str(), -1, &st, NULL);
    int id = sqlite3_last_insert_rowid(this->_db);

    int code = sqlite3_step( st );

    if ( code == SQLITE_DONE )
        logger( 0, "Inserted new note in database" );

    if ( code == SQLITE_ERROR )
        logger( 1,
            ( std::string( "Failed to execute request, SQLITE_ERROR: ") +
            sqlite3_errmsg( this->_db ) ).c_str()
        );

    return id;

}


Session Sqlite::selectSession( std::string id ) {

    sqlite3_stmt* st;
    std::string sql = "SELECT * FROM Session WHERE id = ?";


    sqlite3_prepare_v2( this->_db, sql.c_str(), -1, &st, NULL);

    sqlite3_bind_int( st, 1, std::stoi(id) );


    int code = sqlite3_step( st );
    while ( code == SQLITE_ROW || code == SQLITE_BUSY ) {

        if ( code == SQLITE_ROW  ) {

            return Session(
                sqlite3_column_int(st, 0),
                sqlite3_column_text(st, 1) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 1))) :
                    std::string(),
                sqlite3_column_text(st, 2) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 2))) :
                    std::string(),
                sqlite3_column_int(st, 3)
            );

        }

    }

    if ( code == SQLITE_ERROR )
        logger( 1,
            ( std::string( "Failed to execute request, SQLITE_ERROR: ") +
            sqlite3_errmsg( this->_db ) ).c_str()
        );

    return Session();

}


std::vector<Note> Sqlite::selectNotes(
    std::string id, std::string session_id
) {

    std::vector<Note> result;

    sqlite3_stmt* st;
    std::string sql = "SELECT * FROM Note WHERE id > -1";

    if ( id != "" )
        sql += "id = ? ";
    if ( session_id != "" )
        sql += "session_id = ? ";

    sqlite3_prepare_v2( this->_db, sql.c_str(), -1, &st, NULL);

    int p = 1;

    if ( id != "" ) {
        sqlite3_bind_int( st, p, std::stoi(id) );
        p++;
    }
    if ( session_id != "" ) {
        sqlite3_bind_int( st, p, std::stoi(session_id) );
        p++;
    }


    int code = sqlite3_step( st );
    int first = -1;
    while ( code == SQLITE_ROW || code == SQLITE_BUSY ) {

        if ( code == SQLITE_ROW ) {

            Note tmp(
                sqlite3_column_int(st, 0),
                sqlite3_column_int(st, 1),
                sqlite3_column_text(st, 2) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 2))) :
                    std::string(),
                sqlite3_column_text(st, 3) ?
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(st, 3))) :
                    std::string()
            );

            if ( first == tmp.getId() )
                return result;
            if ( first == -1 )
                first = tmp.getId();

            result.push_back(tmp);

        }

    }

    if ( code == SQLITE_ERROR )
        logger( 1,
            ( std::string( "Failed to execute request, SQLITE_ERROR: ") +
            sqlite3_errmsg( this->_db ) ).c_str()
        );

    return result;

}