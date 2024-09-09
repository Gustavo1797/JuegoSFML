#include <iostream>
#include "rlutil.h"
#include <cstdlib>


void Titulo() {
    rlutil::setColor(rlutil::COLOR::WHITE); // COLOR TEXTO MENU
    rlutil::hidecursor(); // Sin Cursor
    rlutil::cls(); // Limpiar Consola

    rlutil::setColor(rlutil::COLOR::DARKGREY);
    rlutil::locate(5, 2);
    std::cout << "  ######    #######  ######### ##    ##    ######   ##     ##        ########  ##  ########## ##      ##" << std::endl;
    rlutil::locate(5, 3);
    std::cout << " ##    ##  ##     ##    ##     ##    ##   ##    ##  ## # # ##        ##                ##     ##      ##       " << std::endl;
    rlutil::locate(5, 4);
    std::cout << " ##        ##     ##    ##     ##    ##   ##    ##  ##  #  ##        ##        ##      ##       ##  ##   " << std::endl;
    rlutil::locate(5, 5);
    std::cout << " ##  ####  ##     ##    ##     ########   ########  ##  #  ##        ##        ##      ##         ##" << std::endl;
    rlutil::locate(5, 6);
    std::cout << " ##    ##  ##     ##    ##     ##    ##   ##    ##  ##     ##        ##        ##      ##         ##    " << std::endl;
    rlutil::locate(5, 7);
    std::cout << " ##    ##  ##     ##    ##     ##    ##   ##    ##  ##     ##        ##        ##      ##         ##     " << std::endl;
    rlutil::locate(5, 8);
    std::cout << "  ######    #######     ##     ##    ##   ##    ##  ##     ##        ########  ##      ##         ##" << std::endl;
}

void Comojugar() {
}


