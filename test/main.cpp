#include "cppTest.h"
#include "logger.h"

int main() {

    CppTest t;

    logger( 0, "Test" );
    logger( 1, "Test" );
    logger( 2, "Test" );
    logger( 3, "Test" );
    t.test( 1 != 1, "root", "1 == 1");

    t.display();

    return 0;

}