/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#include "zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>
#include "core/Core.hpp"

int main(int argc, char **argv)
{
    Core gameManager(argc, argv);

    gameManager.initialize();
    gameManager.run();
    return 0;
}
