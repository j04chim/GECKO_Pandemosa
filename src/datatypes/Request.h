#pragma once
#include <string>
#include <vector>


class Column {

    public:

        virtual void append( int ) { return; };
        virtual void append( bool ) { return; };
        virtual void append( std::string ) { return; };
        virtual std::vector<int> getInteger() { return {}; };
        virtual std::vector<std::string> getText() { return {}; };
        virtual std::vector<bool> getBoolean()  { return {}; };

};


class Column_int: public Column {

    public:

        virtual void append( int );
        virtual std::vector<int> getInteger();

    private:

        std::vector<int> content;

};


class Column_bool: public Column {

    public:

        virtual void append( bool );
        virtual std::vector<bool> getBoolean();

    private:

        std::vector<bool> content;

};


class Column_text: public Column {

    public:

        virtual void append( std::string );
        virtual std::vector<std::string> getText();

    private:

        std::vector<std::string> content;

};


class Request {

    public:

        void append( Column );
        std::vector<Column> getContent();

    private:

        std::vector<Column> content;

};