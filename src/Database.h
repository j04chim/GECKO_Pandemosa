#pragma once
#include <string>
#include <vector>

#include "datatypes/Session.h"
#include "datatypes/Event.h"
#include "datatypes/Note.h"

/**
 * @class Database
 * @brief Abstract class to managed databases.
 */
class Database {

    public:

        Database() = default;
        virtual ~Database() = default;

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
        ) = 0;

        /**
        * @fn insertSession
        * @brief Insert a session in the database and return it.
        * @param creation_date Creation date of the session
        * @param ingame_date Current date in-game
        * @return Session Created session
        */
        virtual Session insertSession(
            std::string creation_date = "", std::string ingame_date = ""
        ) = 0;

        /**
        * @fn selectSession
        * @brief Return a session with the given ID.
        * @param id Session's id
        * @return Session Found session.
        */
        virtual Session selectSession( std::string id = "" ) = 0;

        /**
        * @fn selectNotes
        * @brief Return all the notes of a given session.
        * @param session_id Session's id
        * @return std::vector<Note> Session's notes
        */
        virtual std::vector<Note> selectNotes(
            std::string session_id = ""
        ) = 0;

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
        ) = 0;

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
        ) = 0;

        /**
        * @fn updateSession
        * @brief Update the session's in-game date.
        * @param session_id Session's id
        * @param new_ingame_date New in-game date
        * @return int 0/1 success/failure
        */
        virtual int updateSession(
            std::string session_id,
            std::string new_ingame_date
        ) = 0;

};