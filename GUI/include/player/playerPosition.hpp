/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** playerPosition
*/

#pragma once

#include "main.hpp"

class Player;

class PlayerPos {
    public:
        PlayerPos();
        PlayerPos(Player *parentPlayer);
        ~PlayerPos();

        void setParentPlayer(Player *parentPlayer);
        void initPos();

        int getX();
        int getY();
        int getZ();

        float getConvertedX();
        float getConvertedY();
        float getConvertedZ();

        int getOrientationX();
        int getOrientationY();
        int getOrientationZ();

        int getConvOrientationX();
        int getConvOrientationY();
        int getConvOrientationZ();
        float getTileSize();

        void setX(int x);
        void setY(int y);
        void setZ(int z);

        void setConvertedX(float x);
        void setConvertedY(float y);
        void setConvertedZ(float z);

        void setOrientationX(int orientationx);
        void setOrientationY(int orientationy);
        void setOrientationZ(int orientationz);

        void setConvertedOrientationX(int orientationx);
        void setConvertedOrientationY(int orientationy);
        void setConvertedOrientationZ(int orientationz);

        void setTileSize(float tileSize);

        void setPos(int x, int y, int z = -1);
        void setConvertedPos(float x, float y, float z = -1.0);
        void setOrientation(int orientationx, int orientationy, int orientationz);
        void setConvertedOrientation(int orientationx, int orientationy, int orientationz);

        PlayerPos *getPlayerPos();

        vector3df getVecPosConverted();
        vector3di getVecPos();

        vector3df getVecRotConverted();
        vector3di getVecRot();

    private:
        int _X;
        int _Y;
        int _Z;

        int _Orientation_x;
        int _Orientation_y;
        int _Orientation_z;

        float _Converted_x;
        float _Converted_y;
        float _Converted_z;

        float _Converted_Orientation_x;
        float _Converted_Orientation_y;
        float _Converted_Orientation_z;

        float _TileSize;
        Player *_ParentPlayer;
};