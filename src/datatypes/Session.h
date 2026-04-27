#pragma once
#include <string>

class Database;

class Session {

    public:

        Session();
        Session(
            int id,
            std::string creation_date,
            std::string ingame_date,
            int locked
        );

        bool open();
        bool close();
        std::string toJson();

    private:

        int _id;
        std::string _creation_date;
        std::string _ingame_date;
        int _locked;
        Database* _db;

};