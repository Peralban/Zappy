/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** playerPosition
*/

#include "playerPosition.hpp"
#include "player.hpp"
#include "game/ZappyGame.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>

PlayerPos::PlayerPos()
{
    //simple coordinates
    this->_X = 0;
    this->_Y = 0;
    this->_Z = 0;

    //converted coordinates
    this->_Converted_x = 0;
    this->_Converted_y = 0;
    this->_Converted_z = 0;

    //simple orientation
    this->_Orientation_x = 0;
    this->_Orientation_y = 0;
    this->_Orientation_z = 0;

    //converted orientation
    this->_Converted_Orientation_x = 0;
    this->_Converted_Orientation_y = 0;
    this->_Converted_Orientation_z = 0;

    this->_TileSize = 0.0f;
    this->_ParentPlayer = nullptr;
}


PlayerPos::PlayerPos(Player *parentPlayer) :
    PlayerPos()
{
    this->_ParentPlayer = parentPlayer;
}

PlayerPos::~PlayerPos()
{
    std::cout << "\nPlayerPos destroyed\n" << std::endl;
}

void PlayerPos::setParentPlayer(Player *parentPlayer)
{
    this->_ParentPlayer = parentPlayer;
    this->_TileSize = parentPlayer->getParentGame()->getParentDevice()->getTileSize();
}

void PlayerPos::initPos()
{
    if (this->_ParentPlayer == nullptr)
        return;
    this->_TileSize = _ParentPlayer->getParentGame()->getParentDevice()->getTileSize();
}

// -------------- GETTERS --------------

int PlayerPos::getX()
{
    return this->_X;
}

int PlayerPos::getY()
{
    return this->_Y;
}

int PlayerPos::getZ()
{
    return this->_Z;
}

float PlayerPos::getConvertedX()
{
    return this->_Converted_x;
}

float PlayerPos::getConvertedY()
{
    return this->_Converted_y;
}

float PlayerPos::getConvertedZ()
{
    return this->_Converted_z;
}

int PlayerPos::getOrientationX()
{
    return this->_Orientation_x;
}

int PlayerPos::getOrientationY()
{
    return this->_Orientation_y;
}

int PlayerPos::getOrientationZ()
{
    return this->_Orientation_z;
}

int PlayerPos::getConvOrientationX()
{
    return this->_Converted_Orientation_x;
}

int PlayerPos::getConvOrientationY()
{
    return this->_Converted_Orientation_y;
}

int PlayerPos::getConvOrientationZ()
{
    return this->_Converted_Orientation_z;
}

float PlayerPos::getTileSize()
{
    return this->_TileSize;
}

// -------------- SETTERS --------------

void PlayerPos::setX(int x)
{
    float newx = float(x) * this->_TileSize;
    this->_X = x;
    setConvertedX(newx);
}

void PlayerPos::setY(int y)
{
    float newy = float(y) * this->_TileSize;
    this->_Y = y;
    setConvertedY(newy);
}

void PlayerPos::setZ(int z)
{
    float newz = float(z) * this->_TileSize;
    this->_Z = z;
    setConvertedZ(newz);
}

void PlayerPos::setConvertedX(float x)
{
    this->_Converted_x = x;
    this->_X = int(x / this->_TileSize);
}

void PlayerPos::setConvertedY(float y)
{
    this->_Converted_y = y;
    this->_Y = int(y / this->_TileSize);
}

void PlayerPos::setConvertedZ(float z)
{
    this->_Converted_z = z;
    this->_Z = int(z / this->_TileSize);
}

void PlayerPos::setOrientationX(int orientationx)
{
    int newx = orientationx * 90;
    this->_Orientation_x = orientationx;
    setConvertedOrientationX(newx);
}

void PlayerPos::setOrientationY(int orientationy)
{
    int newy = orientationy * 90;
    this->_Orientation_y = orientationy;
    setConvertedOrientationY(newy);
}

void PlayerPos::setOrientationZ(int orientationz)
{
    int newz = orientationz * 90;
    this->_Orientation_z = orientationz;
    setConvertedOrientationZ(newz);
}

void PlayerPos::setConvertedOrientationX(int orientationx)
{
    this->_Converted_Orientation_x = orientationx;
    this->_Orientation_x = int(orientationx / 90);
}

void PlayerPos::setConvertedOrientationY(int orientationy)
{
    this->_Converted_Orientation_y = orientationy;
    this->_Orientation_y = int(orientationy / 90);
}

void PlayerPos::setConvertedOrientationZ(int orientationz)
{
    this->_Converted_Orientation_z = orientationz;
    this->_Orientation_z = int(orientationz / 90);
}

void PlayerPos::setTileSize(float tileSize)
{
    this->_TileSize = tileSize;
}


// --------------- MULTI SETTERS ---------------

void PlayerPos::setPos(int x, int y, int z)
{
    this->setX(x);
    this->setConvertedX(float(x) * this->_TileSize);
    this->setY(y);
    this->setConvertedY(float(y) * this->_TileSize);
    if (z != -1) {
        this->setZ(z);
        this->setConvertedZ(float(z) * this->_TileSize);
    }
}

void PlayerPos::setConvertedPos(float x, float y, float z)
{
    this->setConvertedX(x);
    this->setConvertedY(y);
    if (z != -1.0)
        this->setConvertedZ(z);
}

void PlayerPos::setOrientation(int orientationx, int orientationy, int orientationz)
{
    this->setOrientationX(orientationx);
    this->_Converted_Orientation_x = orientationx * 90;
    this->setOrientationY(orientationy);
    this->_Converted_Orientation_y = orientationy * 90;
    this->setOrientationZ(orientationz);
    this->_Converted_Orientation_z = orientationz * 90;
}

void PlayerPos::setConvertedOrientation(int orientationx, int orientationy, int orientationz)
{
    this->setConvertedOrientationX(orientationx);
    this->_Orientation_x = orientationx / 90;
    this->setConvertedOrientationY(orientationy);
    this->_Orientation_y = orientationy / 90;
    this->setConvertedOrientationZ(orientationz);
    this->_Orientation_z = orientationz / 90;
}

PlayerPos *PlayerPos::getPlayerPos()
{
    return this;
}

irr::core::vector3df PlayerPos::getVecPosConverted()
{
    return irr::core::vector3df(this->_Converted_x, this->_Converted_z, this->_Converted_y);
}

irr::core::vector3di PlayerPos::getVecPos()
{
    return irr::core::vector3di(this->_X, this->_Z, this->_Y);
}

irr::core::vector3df PlayerPos::getVecRotConverted()
{
    return irr::core::vector3df(float(this->_Converted_Orientation_x), float(this->_Converted_Orientation_z), float(this->_Converted_Orientation_y));
}

irr::core::vector3di PlayerPos::getVecRot()
{
    return irr::core::vector3di(this->_Orientation_x, this->_Orientation_z, this->_Orientation_y);
}
