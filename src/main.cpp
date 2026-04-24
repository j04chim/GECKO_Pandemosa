#include <stdio.h>

#include "logger.h"
#include "App.h"

void display_help() {

    printf( "Kausjan - Pandemic simulation game\n" );
    printf( "Usage:\n" );
    printf( "   kausjan [config file path]\n" );
    printf( "   kausjan_test [config file path]\n" );

}

int main(int argc, char** argv) {

    if ( argc != 2 ) {
        display_help();
        return 0;
    }

    Config* conf = new Config();

    if ( conf->parse( argv[1] ) )
        return 1;

    App* app = new App( *conf );

    return 0;

}