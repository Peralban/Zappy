/**
 * @file items.hpp
 * @brief Contains the declaration of the items class and related enums and exceptions.
 */

#pragma once

#include "irrlicht/irrlicht.h"
#include "chessElement/chessBoard.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"
#include <array>

/**
 * @enum itemsEnum
 * @brief Enumerations for different types of items.
 */
enum itemsEnum {
    FOOD,       ///< Food item
    LINEMATE,   ///< Linemate item
    DERAUMERE,  ///< Deraumere item
    SIBUR,      ///< Sibur item
    MENDIANE,   ///< Mendiane item
    PHIRAS,     ///< Phiras item
    THYSTAME    ///< Thystame item
};

/**
 * @class items
 * @brief Represents the items in the game.
 */
class items
{
public:
    /**
     * @brief Default constructor.
     */
    items();

    /**
     * @brief Constructor with parent chessboard.
     * @param ParentChessboard The parent chessboard object.
     */
    items(chessBoard *ParentChessboard);

    /**
     * @brief Destructor.
     */
    ~items();

    /**
     * @brief Initializes the items object.
     */
    void initItemsObj();

    /**
     * @brief Sets the parent chessboard.
     * @param ParentchessBoard The parent chessboard object.
     */
    void setParentchessBoard(chessBoard *ParentchessBoard);

    /**
     * @brief Updates the map with new tiles.
     * @param map The new map with tiles.
     */
    void updateMap(std::vector<std::vector<Tile *>> map);

    /**
     * @brief Updates the mesh with new inventory.
     * @param node The node to update.
     * @param inventory The new inventory.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    void updateMesh(std::array<irr::scene::IAnimatedMeshSceneNode *, 8> node, std::vector<int> inventory, int x, int y);

    /**
     * @brief Compares the inventory and mesh inventory.
     * @param inventory
     * @param meshInventory
     * @param eggInInventory
     * @return A vector of booleans that represent the differences between the two inventories.
     */
    std::vector<bool> CompareInvAndMesh(std::vector<int> inventory, std::vector<int> &meshInventory, int eggInInventory);

    /**
     * @brief Gets the mesh inventory.
     * @param node The node to get the inventory from.
     * @return The mesh inventory.
     */
    std::vector<int> getMeshInventory(std::array<irr::scene::IAnimatedMeshSceneNode *, 8> node);


    /**
     * @brief Checks if the inventory is the same.
     * @param inventory The inventory to check.
     * @return True if the inventory is the same, false otherwise.
     */
    bool isSameInventory(std::vector<bool> inventory);

    /**
     * @brief Updates the text.
     * @param tile
     * @param inventory
     * @param debug
     */
    void updateText(Tile *tile, std::vector<int> inventory, bool debug);

    /**
     * @class UnsetParentchessBoard
     * @brief Exception class for unset parent chessboard.
     */
    class UnsetParentchessBoard : public AError {
    public:
        /**
         * @brief Constructor.
         */
        UnsetParentchessBoard() : AError("Parent chessBoard is not set") {}
    };

    /**
     * @class UnsetTile
     * @brief Exception class for unset tile.
     */
    class UnsetTile : public AError {
    public:
        /**
         * @brief Constructor.
         */
        UnsetTile() : AError("Tile is not set") {}
    };

    /**
     * @class UnsetNode
     * @brief Exception class for unset node.
     */
    class UnsetNode : public AError {
    public:
        /**
         * @brief Constructor.
         */
        UnsetNode() : AError("Node is not set") {}
    };

    /**
     * @class UnsetItem
     * @brief Exception class for unset item.
     */
    class UnsetItem : public AError {
    public:
        /**
         * @brief Constructor.
         */
        UnsetItem() : AError("Item is not set") {}
    };

    /**
     * @class UnsetDevice
     * @brief Exception class for unset device.
     */
    class UnsetDevice : public AError {
    public:
        /**
         * @brief Constructor.
         */
        UnsetDevice() : AError("Device is not set") {}
    };

    /**
     * @class UnsetDriver
     * @brief Exception class for unset driver.
     */
    class UnsetDriver : public AError {
    public:
        /**
         * @brief Constructor.
         */
        UnsetDriver() : AError("Driver is not set") {}
    };

    /**
     * @class UnsetFont
     * @brief Exception class for unset font.
     */
    class UnsetFont : public AError {
        public:
            /**
             * @brief Constructor.
             */
            UnsetFont() : AError("Font is not set") {}
    };

private:
    irr::scene::IAnimatedMesh * _Food;             ///< The food obj file
    irr::scene::IAnimatedMesh * _Linemate;         ///< The coal obj file
    irr::scene::IAnimatedMesh * _Deraumere;        ///< The iron obj file
    irr::scene::IAnimatedMesh * _Sibur;            ///< The gold obj file
    irr::scene::IAnimatedMesh * _Mendiane;         ///< The emerald obj file
    irr::scene::IAnimatedMesh * _Phiras;           ///< The diamond obj file
    irr::scene::IAnimatedMesh * _Thystame;         ///< The netherite obj file
    irr::scene::IAnimatedMesh * _Egg;              ///< The egg obj file

    int countX;
    int countY;
    int countZ;

    std::vector<std::vector<irr::scene::ITextSceneNode *>> _TextNode; ///< The inventory of the items.

    std::vector<std::vector<std::array<irr::scene::IAnimatedMeshSceneNode *, 8>>> _ItemNode; ///< The node for the item.

    std::vector<std::vector<std::vector<int>>> _DisplayNode; ///< The node for the display.

    chessBoard *_ParentchessBoard;                 ///< A pointer to the chessBoard object that contains the items.

    irr::gui::IGUIFont *_Font;                      ///< A pointer to the IGUIFont object for font rendering.

    irr::scene::ISceneManager *_SceneManager;      ///< A pointer to the ISceneManager object for scene management.
    irr::video::IVideoDriver *_Driver;              ///< A pointer to the IVideoDriver object for video rendering.
    irr::IrrlichtDevice *_Device;                   ///< A pointer to the IrrlichtDevice object for device management.
};