/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Items
*/

#pragma once

#include "irrlicht/irrlicht.h"
#include "../interface/AError.hpp"
#include <vector>

class chessBoard;

/**
 * @brief The Tile class represents a tile in a chessboard.
 */
class Tile {
public:
    /**
     * @brief Default constructor for the Tile class.
     */
    Tile();

    /**
     * @brief Constructor for the Tile class.
     * @param ParentChessBoard A pointer to the chessBoard object that is used as the parent chessboard.
     * @param tileTexture A pointer to the ITexture object for the tile texture.
     * @param x The x-coordinate of the tile.
     * @param y The y-coordinate of the tile.
     * @param z The z-coordinate of the tile.
     * @param tileSize The size of the tile.
     */
    Tile(chessBoard *ParentChessBoard, irr::video::ITexture* tileTexture, int x = -1, int y = -1, int z = -1, float tileSize = -1);

    /**
     * @brief Destructor for the Tile class.
     */
    ~Tile();

    /**
     * @brief Links the tile to its parent chessboard.
     * @param ParentChessBoard A pointer to the chessBoard object that is used as the parent chessboard.
     */
    void linkToParent(chessBoard *ParentChessBoard);

    /**
     * @brief Initializes the tile.
     */
    void initTile();

    /**
     * @brief Sets the texture of the tile.
     * @param tileTexture A pointer to the ITexture object for the tile texture.
     */
    void setTexture(irr::video::ITexture* tileTexture);

    /**
     * @brief Sets the position of the tile.
     * @param x The x-coordinate of the tile.
     * @param y The y-coordinate of the tile.
     * @param z The z-coordinate of the tile.
     */
    void setPos(int x = -1, int y = -1, int z = -1);

    /**
     * @brief Sets the size of the tile.
     * @param tileSize The size of the tile.
     */
    void setTileSize(float tileSize = -1);

    /**
     * @brief Creates the tile.
     */
    void createTile();

    /**
     * @brief Sets the inventory of the tile.
     * @param food The amount of food in the inventory.
     * @param linemate The amount of linemate in the inventory.
     * @param deraumere The amount of deraumere in the inventory.
     * @param sibur The amount of sibur in the inventory.
     * @param mendiane The amount of mendiane in the inventory.
     * @param phiras The amount of phiras in the inventory.
     * @param thystame The amount of thystame in the inventory.
     */
    void setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);

    /**
     * @brief Prints the inventory of the tile.
     */
    void printInventory();

    /**
     * @brief Sets the player on the tile.
     * @param player The player on the tile.
     */
    void setPlayer(int player);

    /**
     * @brief Sets the egg on the tile.
     * @param egg The egg on the tile.
     */
    void setEgg(int egg);

    /**
     * @brief Gets the node of the tile.
     * @return The node of the tile.
     */
    irr::scene::ISceneNode *getNode();

    /**
     * @brief Gets the player on the tile.
     * @return The player on the tile.
     */
    int getPlayer();

    /**
     * @brief Gets the egg on the tile.
     * @return The egg on the tile.
     */
    int getEgg();

    int getPositionX();
    int getPositionY();
    int getPositionZ();

    std::vector<int> getInventory();

    /**
     * @brief Gets the parent chessboard of the tile.
     * @return The parent chessboard of the tile.
     */
    chessBoard *getParentChessBoard();

    /**
     * @brief Takes a ressource for the tile.
     * @param ressource
     */
    void takeRessource(std::string ressource);

    /**
     * @brief the tile drop a ressource.
     * @param ressource
     */
    void dropRessource(std::string ressource);

    void resetInventory();

    class UnsetParentChessboard : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "given parent chessboard is null".
             * 
             * occured when the parent chessboard is null and you try to initialise the tile by calling initTile() or setting the parent chessboard .
             */
            UnsetParentChessboard() : AError("given parent chessboard is null") {}
        };
    
    class UnsetTileTexture : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "given tile texture is null".
             * 
             * occured when the tile texture is null and you try to set the texture by calling setTexture().
             */
            UnsetTileTexture() : AError("given tile texture is null") {}
        };

    class UnsetIrrlichVar : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "One of the Value that link tiles to irrlich isn't correctly setted".
             * 
             * occured when the irrlicht device, driver or scene manager is null and you try to create the tile.
             */
            UnsetIrrlichVar() : AError("One of the Value that link tiles to irrlich isn't correctly setted") {}
        };
    
    class UnsetPos : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "One coordinate of the tile isn't correctly setted".
             * 
             * occured when the x, y or z coordinate is not setted and you try to create the tile.
             */
            UnsetPos() : AError("One coordinate of the tile isn't correctly setted") {}
        };
    
    class UnsetTileSize : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Tile size isn't correctly setted".
             * 
             * occured when the tile size is not setted and you try to create the tile.
             */
            UnsetTileSize() : AError("Tile size isn't correctly setted") {}
        };
    
    class UnsetNode : public AError {
        public:
            /**
             * @brief Display an error message.
             * @param message The error message to display. Defaults to "Node isn't correctly setted".
             * 
             * occured when the node is null and you try to create the tile.
             */
            UnsetNode() : AError("Node isn't correctly setted") {}
        };

private:
    int _food; ///< The amount of food in the tile's inventory.
    int _linemate; ///< The amount of linemate in the tile's inventory.
    int _deraumere; ///< The amount of deraumere in the tile's inventory.
    int _sibur; ///< The amount of sibur in the tile's inventory.
    int _mendiane; ///< The amount of mendiane in the tile's inventory.
    int _phiras; ///< The amount of phiras in the tile's inventory.
    int _thystame; ///< The amount of thystame in the tile's inventory.
    int _player; ///< The player on the tile.
    int _egg; ///< The egg on the tile.

    int _X; ///< The x-coordinate of the tile.
    int _Y; ///< The y-coordinate of the tile.
    int _Z; ///< The z-coordinate of the tile.
    float _TileSize; ///< The size of the tile.

    chessBoard *_ParentChessBoard; ///< A pointer to the chessBoard object that is used as the parent chessboard.

    irr::video::ITexture *_TileTexture; ///< A pointer to the ITexture object for the tile texture.
    irr::scene::ISceneNode *_Node; ///< A pointer to the ISceneNode object for scene management.

    irr::scene::ISceneManager *_SceneManager; ///< A pointer to the ISceneManager object for scene management.
    irr::video::IVideoDriver *_Driver; ///< A pointer to the IVideoDriver object for video rendering.
    irr::IrrlichtDevice *_Device; ///< A pointer to the IrrlichtDevice object for device management.
};
