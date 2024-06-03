/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** playerPosition
*/

#pragma once

#include "main.hpp"

class PlayerPos {
    public:
        PlayerPos();
        ~PlayerPos();
    private:
        int _X;
        int _Y;
        int _Converted_x;
        int _Converted_y;
        int _Orientation;
};