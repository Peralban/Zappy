/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#include "zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>
#include "core/Core.hpp"

int main(int ac, char **av)
{
    int width = 1920;
    int height = 1080;
    int platformX = 0;
    int platformY = 0;
    float tileSize = 30.0f;
    quality gameQuality = HIGH;
    bool debug = false;
    Core core(width, height, platformX, platformY, tileSize, gameQuality, debug);

    core.initialize(ac, av);
    core.run();
    return 0;
}
