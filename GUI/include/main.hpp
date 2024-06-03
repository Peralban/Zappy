/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** main
*/

#pragma once

#include <irrlicht.h>
#include <iostream>
#include <filesystem> 
#include <fstream>

enum pieceType {BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK};
enum pieceColor {BLACK, WHITE};
enum quality {LowPoly, MidPoly, HighPoly};	

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

