#include <stdio.h>

#include "cppTest.h"


MessagesTree::MessagesTree( ) {

    this->_name = new std::string( );

}


MessagesTree::MessagesTree( std::string name ) {

    this->_name = new std::string( name );

}


MessagesTree::~MessagesTree( ) {

    for ( std::string* m: this->_leaves ) {

        delete m;

    }

    for ( MessagesTree* m: this->_subtree ) {

        delete m;

    }

    delete this->_name;

}


void MessagesTree::appendMessage( std::string path, std::string message ) {

    if ( path.empty() ) return;

    if ( path == *this->_name ) {

        this->_leaves.push_back( new std::string(message) );
        return;

    }

    std::string name = path.substr( 0, path.find_first_of( "." ) );
    path = path.substr( path.find_first_of( "." ) + 1 );

    for ( MessagesTree* m: this->_subtree ) {

        if ( *m->getName() == name ) {

            m->appendMessage( path, message );
            return;

        }

    }

    MessagesTree* new_tree = new MessagesTree( name );
    new_tree->appendMessage( path, message );
    this->_subtree.push_back(new_tree);

    return;

}


std::string* MessagesTree::getName( ) {

    return this->_name;

}


void MessagesTree::display( std::string before ) {

    for ( int i = 0; i < this->_leaves.size( ); ++i ) {

        if ( this->_subtree.empty( ) &&
             i == this->_leaves.size( ) - 1
        ) {

            printf( ( before + "\033[33m ╰╴\033[0m%s\n" ).c_str( ), this->_leaves.at( i )->c_str() );

        } else {

            printf( ( before + "\033[33m ├╴\033[0m%s\n" ).c_str( ), this->_leaves.at( i )->c_str() );

        }

    }

    for ( int i = 0; i < this->_subtree.size( ); ++i ) {

        if ( i == this->_subtree.size( ) - 1 ) {

            printf( ( before + "\033[33m ╰╴%s\033[0m\n" ).c_str( ), this->_subtree.at( i )->getName( )->c_str() );
            this->_subtree.at( i )->display( before + "  " );

        } else {

            printf( ( before + "\033[33m ├╴%s\033[0m\n" ).c_str( ), this->_subtree.at( i )->getName( )->c_str() );
            this->_subtree.at( i )->display( before + "\033[33m │\033[0m" );

        }

    }

}


CppTest::CppTest( ) {

    this->_total_tests = 0;
    this->_passed_tests = 0;

}


void CppTest::test( bool t, std::string path, std::string message ) {

    this->_total_tests++;

    if ( !t ) {

        this->_messages.appendMessage( path, message );
        printf( "\033[31mF\033[0m" );


    } else {

        this->_passed_tests++;
        printf( "\033[32m.\033[0m" );

    }

}


void CppTest::display( ) {

    printf( "\n\033[32m%d tests passed,\033[0m \033[31m%d tests failed\033[0m\n",
            this->_passed_tests,
            this->_total_tests - this->_passed_tests
    );

    this->_messages.display( "" );

}
