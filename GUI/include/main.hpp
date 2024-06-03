/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#pragma once

#include <../irrlicht/irrlicht.h>
#include <iostream>
#include <filesystem> 
#include <fstream>
#include <map>

enum pieceType {BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK};
enum quality {LOW, MID, HIGH};
enum teamColor {DEFAULT, BLACK, WHITE, RED, GREEN, BLUE};

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
