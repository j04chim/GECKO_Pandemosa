#pragma once
#include <string>
#include <vector>


class Config {

    public:

        int parse( std::string );
        std::string get( std::string );
        std::string get( int );
        std::vector<std::string> keys();
        std::vector<std::string> values();
        int size();

    private:

        std::vector<std::string> _keys;
        std::vector<std::string> _values;

};