/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** playerPosition
*/

#pragma once

#include <irrlicht/irrlicht.h>

class Player;

/**
 * @class PlayerPos
 * @brief The PlayerPos class represents the position and orientation of a player in the game.
 * 
 * the convertion will be VAL * TILESIZE
 * this is used for x, y, z and orientation.
 */
class PlayerPos {
    public:
        /**
         * @brief Default constructor for PlayerPos.
         */
        PlayerPos();

        /**
         * @brief Constructor for PlayerPos with a parent player.
         * @param parentPlayer The parent player object.
         */
        PlayerPos(Player *parentPlayer);

        /**
         * @brief Destructor for PlayerPos.
         */
        ~PlayerPos();

        /**
         * @brief Sets the parent player object.
         * @param parentPlayer The parent player object.
         */
        void setParentPlayer(Player *parentPlayer);

        /**
         * @brief Initializes the position.
         * 
         * this will get the tile size from the parent game parent player.
         * it will be used to convert the position to the irrlicht scene.
         */
        void initPos();

        /**
         * @brief Gets the X coordinate of the position.
         * @return The X coordinate.
         */
        int getX();

        /**
         * @brief Gets the Y coordinate of the position.
         * @return The Y coordinate.
         */
        int getY();

        /**
         * @brief Gets the Z coordinate of the position.
         * @return The Z coordinate.
         */
        int getZ();

        /**
         * @brief Gets the converted X coordinate of the position.
         * @return The converted X coordinate.
         */
        float getConvertedX();

        /**
         * @brief Gets the converted Y coordinate of the position.
         * @return The converted Y coordinate.
         */
        float getConvertedY();

        /**
         * @brief Gets the converted Z coordinate of the position.
         * @return The converted Z coordinate.
         */
        float getConvertedZ();

        /**
         * @brief Gets the X orientation of the position.
         * @return The X orientation.
         */
        int getOrientationX();

        /**
         * @brief Gets the Y orientation of the position.
         * @return The Y orientation.
         */
        int getOrientationY();

        /**
         * @brief Gets the Z orientation of the position.
         * @return The Z orientation.
         */
        int getOrientationZ();

        /**
         * @brief Gets the converted X orientation of the position.
         * @return The converted X orientation.
         */
        int getConvOrientationX();

        /**
         * @brief Gets the converted Y orientation of the position.
         * @return The converted Y orientation.
         */
        int getConvOrientationY();

        /**
         * @brief Gets the converted Z orientation of the position.
         * @return The converted Z orientation.
         */
        int getConvOrientationZ();

        /**
         * @brief Gets the tile size.
         * @return The tile size.
         */
        float getTileSize();

        /**
         * @brief Sets the X coordinate of the position.
         * @param x The X coordinate.
         */
        void setX(int x);

        /**
         * @brief Sets the Y coordinate of the position.
         * @param y The Y coordinate.
         */
        void setY(int y);

        /**
         * @brief Sets the Z coordinate of the position.
         * @param z The Z coordinate.
         */
        void setZ(int z);

        /**
         * @brief Sets the converted X coordinate of the position.
         * @param x The converted X coordinate.
         */
        void setConvertedX(float x);

        /**
         * @brief Sets the converted Y coordinate of the position.
         * @param y The converted Y coordinate.
         */
        void setConvertedY(float y);

        /**
         * @brief Sets the converted Z coordinate of the position.
         * @param z The converted Z coordinate.
         */
        void setConvertedZ(float z);

        /**
         * @brief Sets the X orientation of the position.
         * @param orientationx The X orientation.
         */
        void setOrientationX(int orientationx);

        /**
         * @brief Sets the Y orientation of the position.
         * @param orientationy The Y orientation.
         */
        void setOrientationY(int orientationy);

        /**
         * @brief Sets the Z orientation of the position.
         * @param orientationz The Z orientation.
         */
        void setOrientationZ(int orientationz);

        /**
         * @brief Sets the converted X orientation of the position.
         * @param orientationx The converted X orientation.
         */
        void setConvertedOrientationX(int orientationx);

        /**
         * @brief Sets the converted Y orientation of the position.
         * @param orientationy The converted Y orientation.
         */
        void setConvertedOrientationY(int orientationy);

        /**
         * @brief Sets the converted Z orientation of the position.
         * @param orientationz The converted Z orientation.
         */
        void setConvertedOrientationZ(int orientationz);

        /**
         * @brief Sets the tile size.
         * @param tileSize The tile size.
         */
        void setTileSize(float tileSize);

        /**
         * @brief Sets the position.
         * @param x The X coordinate.
         * @param y The Y coordinate.
         * @param z The Z coordinate.
         */
        void setPos(int x, int y, int z = -1);

        /**
         * @brief Sets the converted position.
         * @param x The converted X coordinate.
         * @param y The converted Y coordinate.
         * @param z The converted Z coordinate.
         */
        void setConvertedPos(float x, float y, float z = -1.0);

        /**
         * @brief Sets the orientation.
         * @param orientationx The X orientation.
         * @param orientationy The Y orientation.
         * @param orientationz The Z orientation.
         */
        void setOrientation(int orientationx, int orientationy, int orientationz);

        /**
         * @brief Sets the converted orientation.
         * @param orientationx The converted X orientation.
         * @param orientationy The converted Y orientation.
         * @param orientationz The converted Z orientation.
         */
        void setConvertedOrientation(int orientationx, int orientationy, int orientationz);

        /**
         * @brief Gets the PlayerPos object.
         * @return The PlayerPos object.
         */
        PlayerPos *getPlayerPos();

        /**
         * @brief Gets the converted position as a vector.
         * @return The converted position as irrlicht vector.
         */
        irr::core::vector3df getVecPosConverted();

        /**
         * @brief Gets the position as a vector.
         * @return The position as irrlicht vector.
         */
        irr::core::vector3di getVecPos();

        /**
         * @brief Gets the converted orientation as a vector.
         * @return The converted orientation as irrlicht vector.
         */
        irr::core::vector3df getVecRotConverted();

        /**
         * @brief Gets the orientation as a vector.
         * @return The orientation as  irrlicht vector.
         */
        irr::core::vector3di getVecRot();

    private:
        int _X; /**< The X coordinate of the position. */
        int _Y; /**< The Y coordinate of the position. */
        int _Z; /**< The Z coordinate of the position. */

        int _Orientation_x; /**< The X orientation of the position. */
        int _Orientation_y; /**< The Y orientation of the position. */
        int _Orientation_z; /**< The Z orientation of the position. */

        float _Converted_x; /**< The converted X coordinate of the position. */
        float _Converted_y; /**< The converted Y coordinate of the position. */
        float _Converted_z; /**< The converted Z coordinate of the position. */

        float _Converted_Orientation_x; /**< The converted X orientation of the position. */
        float _Converted_Orientation_y; /**< The converted Y orientation of the position. */
        float _Converted_Orientation_z; /**< The converted Z orientation of the position. */

        float _TileSize; /**< The tile size. */
        Player *_ParentPlayer; /**< The parent player object. */
};