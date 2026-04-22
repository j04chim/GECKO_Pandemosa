#include <vector>
#include <string>


class MessagesTree {

    public:

        MessagesTree( );
        MessagesTree( std::string name );
        ~MessagesTree( );
        void appendMessage( std::string path, std::string message );
        void display( std::string before );
        std::string* getName( );

    private:

        std::string* _name;
        std::vector<MessagesTree*> _subtree;
        std::vector<std::string*> _leaves;

};


class CppTest {

    public:

        CppTest( );
        void test( bool t, std::string path, std::string message );
        void display( );

    private:

        int _total_tests;
        int _passed_tests;
        MessagesTree _messages;

};
