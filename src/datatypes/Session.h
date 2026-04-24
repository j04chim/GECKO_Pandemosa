#pragma once
#include <string>

class Database;

class Session {

    public:

        Session( Database* );

        bool open();
        bool close();
        std::string toJson();

    private:

        int _id;
        int _creation_date;
        int _ingame_date;
        bool _locked;
        Database* _db;

};