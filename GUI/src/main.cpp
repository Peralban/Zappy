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
    if (ac == 2 && std::string(av[1]) == "-help") {
        std::cout << "USAGE: ./zappy_gui -p port -h machine\nDescription:\n"
        "\t-p port is the port number\n"
        "\t-h machine is the name of the machine; localhost by default\n" << std::endl;
        return 0;
    }
    if (ac != 5) {
        std::cerr << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        return 84;
    }
    int width = 1920;
    int height = 1080;
    int platformX = 0;
    int platformY = 0;
    float tileSize = 30.0f;
    quality gameQuality = HIGH;
    bool debug = false;
    Core core(width, height, platformX, platformY, tileSize, gameQuality, debug);
    try {
        core.initialize(ac, av);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    core.run();
    return 0;
}
