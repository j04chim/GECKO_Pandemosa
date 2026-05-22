#include "config.h"
#include "datatypes/Config.h"

TestConfig::TestConfig( CppTest*& t ) {

    this->_t = t;

    Config* c = new Config();
    c->parse("../config_template");

    this->_t->test(
        c->get("port") == "8080", "TestConfig.Get string",
        "Wrong port value: " + c->get("port")
    );
    this->_t->test(
        c->get("driver") == "sqlite", "TestConfig.Get string",
        "Wrong driver value: " + c->get("driver")
    );
    this->_t->test(
        c->get("database") == "../../data/sqlite.db", "TestConfig.Get string",
        "Wrong database value: " + c->get("database")
    );

    this->_t->test(
        c->get(0) == "8080", "TestConfig.Get int",
        "Wrong port value: " + c->get(0)
    );
    this->_t->test(
        c->get(1) == "sqlite", "TestConfig.Get int",
        "Wrong driver value: " + c->get(1)
    );
    this->_t->test(
        c->get(2) == "../../data/sqlite.db", "TestConfig.Get int",
        "Wrong database value: " + c->get(2)
    );

}
