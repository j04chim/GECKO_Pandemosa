#include "Request.h"


void Column_int::append( int d ) {

    this->content.push_back( d );

}


std::vector<int> Column_int::getInteger() {

    return this->content;

}


void Column_bool::append( bool d ) {

    this->content.push_back( d );

}


std::vector<bool> Column_bool::getBoolean() {

    return this->content;

}


void Column_text::append( std::string d ) {

    this->content.push_back( d );

}


std::vector<std::string> Column_text::getText() {

    return this->content;

}


void Request::append( Column d ) {

    this->content.push_back( d );

}


std::vector<Column> Request::getContent() {

    return this->content;

}