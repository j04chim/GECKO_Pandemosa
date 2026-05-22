#include "config.h"

int main() {

    CppTest* t = new CppTest();

    TestConfig config(t);

    t->display();

    if (t->success())
        return 0;
    return 1;

}