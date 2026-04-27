#pragma once
#include <string>

/**
 * @class Session
 * @brief Session data model
 */
class Session {

    public:

        Session();
        Session(
            int id,
            std::string creation_date,
            std::string ingame_date,
            int locked
        );

        /**
         * @fn toJson
         * @brief Return a JSON string representing the object.
         * @return std::string JSON string
         */
        std::string toJson();

    private:

        int _id;
        std::string _creation_date;
        std::string _ingame_date;
        int _locked;

};