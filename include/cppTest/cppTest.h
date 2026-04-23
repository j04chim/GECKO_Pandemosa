#include <vector>
#include <string>

/**
 * @class MessagesTree
 * @brief Store messages in a tree format
 *
 * Internal object to manipulate trees and manage messages.
 */
class MessagesTree {

    public:

        MessagesTree();
        MessagesTree( std::string name );
        ~MessagesTree();

        /**
         * @fn appendMessage
         * @brief Append a message to the tree with the given path.
         * @param path The path in the tree to the leaf were to store the
         *        message.
         * @param message String of text.
         *
         * Add a message to the tree. If the node does not exist, then it is
         * created until we reach the end of the path.
         * A path is under the format "folder 1.folder 2.file 1".
         */
        void appendMessage( std::string path, std::string message );

        /**
         * @fn display
         * @brief Recusively display the messages in the node and its sub-nodes.
         * @param before String to display before the text being displayed.
         */
        void display( std::string before );

        /**
         * @fn getName
         * @brief Return the name of the node.
         */
        std::string* getName();

    private:

        std::string* _name;
        std::vector<MessagesTree*> _subtree;
        std::vector<std::string*> _leaves;

};

/**
 * @class CppTest
 * @brief Execute, manage and display tests.
 *
 * This class is reponsible for checking tests done with test(), storing the
 * result in MessageTree object and then retreive these results to the user
 * with the display() function.
 */
class CppTest {

    public:

        CppTest();

        /**
         * @fn test
         * @brief Check a test.
         * @param t The result of the test, assert style.
         * @param path The path in the tree to the leaf were to store the
         *        message if the check fail.
         * @param message The message which will be display if the test fail.
         *
         * Check if t is true and stored the failure message in the message
         * tree if that is the case.
         * Path is in the format "folder 1.folder 2.file 1".
         */
        void test( bool t, std::string path, std::string message );

        /**
         * @fn display
         * @brief Display the messages stored in the message tree.
         */
        void display();

    private:

        int _total_tests;
        int _passed_tests;
        MessagesTree _messages;

};
