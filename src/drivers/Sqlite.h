#pragma once
#include <string>
#include <sqlite3.h>
#include <vector>

#include "../Database.h"
#include "../datatypes/Config.h"
#include "../datatypes/Session.h"
#include "../datatypes/Event.h"
#include "../datatypes/Note.h"

/**
 * @class Sqlite
 * @brief Sqlite3 driver for managing sqlite3 database.
 *
 * Sqlite3 driver for managing sqlite3 database.
 * config:
 * database=path
 */
class Sqlite: public Database {

    public:

        Sqlite( Config& );
        virtual ~Sqlite();

        /**
        * @fn selectEvents
        * @brief Return events with the given parameters.
        * @param id Event ID
        * @param report_date Event date
        * @param detail_level Event's detail level
        * @param decision_relevance Event's decision relevance
        * @param uncertainty_level Event's uncertainty level
        * @return std::vector<Event> List of matching events
        */
        virtual std::vector<Event> selectEvents(
            std::string id = "",
            std::string report_date = "",
            std::string detail_level = "",
            std::string decision_relevance = "",
            std::string uncertainty_level = ""
        ) override;

        /**
        * @fn insertSession
        * @brief Insert a session in the database and return it.
        * @param creation_date Creation date of the session
        * @param ingame_date Current date in-game
        * @return Session Created session
        */
        virtual Session insertSession(
            std::string creation_date = "", std::string ingame_date = ""
        ) override;

        /**
        * @fn selectSession
        * @brief Return a session with the given ID.
        * @param id Session's id
        * @return Session Found session.
        */
        virtual Session selectSession( std::string id = "" ) override;

        /**
        * @fn selectNotes
        * @brief Return all the notes of a given session.
        * @param session_id Session's id
        * @return std::vector<Note> Session's notes
        */
        virtual std::vector<Note> selectNotes(
            std::string session_id = ""
        ) override;

        /**
        * @fn insertAction
        * @brief Insert a player action in the database.
        * @param session_id Session's id
        * @param report_id Event the action is linked to
        * @param action The action done
        * @param description Action's description
        * @return int Action id
        */
        virtual int insertAction(
            std::string session_id, std::string report_id, std::string action,
            std::string description
        ) override;

        /**
        * @fn insertNote
        * @brief Insert a note in the database.
        * @param session_id Session's id
        * @param title Title of the note
        * @param content Content of the note
        * @return Note Created note
        */
        virtual Note insertNote(
            std::string session_id, std::string title,
            std::string content
        ) override;

        /**
        * @fn insertNote
        * @brief Update the session's in-game date.
        * @param session_id Session's id
        * @param new_ingame_date New in-game date
        * @return int 0/1 success/failure
        */
        virtual int updateSession(
            std::string session_id,
            std::string new_ingame_date
        ) override;

        /**
        * @fn updateNote
        * @brief Update note content.
        * @param note_id Note's id
        * @param title New title
        * @param content New content
        * @return int 0/1 success/failure
        */
        virtual int updateNote(
            std::string note_id, std::string title,
            std::string content
        ) override;

        /**
        * @fn deleteNote
        * @brief Delete a note.
        * @param note_id Note's id
        * @return int 0/1 success/failure
        */
        virtual int deleteNote(
            std::string note_id
        ) override;

        /**
        * @fn insertNoteLink
        * @brief Link two notes.
        * @param note_id_a first Note's id
        * @param note_id_b second Note's id
        * @return int 0/1 success/failure
        */
        virtual int insertNoteLink(
            std::string session_id,
            std::string note_id_a,
            std::string note_id_b
        ) override;

        /**
        * @fn selectNoteLink
        * @brief Get links of a session.
        * @param note_id_a first Note's id
        * @param note_id_b second Note's id
        * @return std::vector<NoteLink> NoteLink
        */
        virtual std::vector<NoteLink> selectNoteLink(
            std::string session_id
        ) override;

    private:

        sqlite3* _db;
        bool _loaded;

};
