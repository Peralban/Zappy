/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <vector>
#include <string>

class irrlichtWindow;

/**
 * @brief An enumeration of the possible types of chess pieces.
 * the type will determine the OBJ file used to render the chess pieces.
*/
enum pieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

/**
 * @brief An enumeration of the possible qualities of the chess pieces.
 * the quality will determine the number of polygons used to render the chess pieces.
*/
enum quality {
    LOW,
    MID,
    HIGH
};

/**
 * @brief An enumeration of the possible team colors.
 * this list can be extended to include more colors.
*/
enum teamColor {
    DEFAULT,
    BLACK,
    WHITE,
    RED,
    GREEN,
    BLUE
};

/**
 * @class chessPiece
 * @brief A class that represents a chess piece.
 *
 * This class is used to represent a chess piece and contains functions to load, place, and get chess pieces.
 */
class chessPiece {
	public:
        /**
         * @brief Constructs a chess piece object.
         *
         * This constructor initializes a chess piece object with the given parameters.
         *
         * @param window A pointer to the irrlichtWindow object that will be used as the parent window.
         */
        chessPiece(irrlichtWindow *window);

        /**
         * @brief Destroys the chess piece object.
         *
         * This destructor destroys the chess piece object and frees up any resources used by it.
         */
        ~chessPiece();

        /**
         * @brief Loads a chess piece.
         *
         * This function loads every chess piece OBJ file with the specified quality.
         *
         * @param choosedQuality The quality of the chess piece to load.
         */
        void loadPiece(quality choosedQuality = LOW);

        /**
         * @brief Initializes the textures for the chess pieces.
         *
         * This function initializes the textures for the chess pieces by loading the .png files.
         */
        void initTextures();

        /**
         * @brief Sets the current quality of the chess pieces.
         *
         * This function sets the current quality of the chess pieces to the specified quality.
         *
         * @param newQuality The new quality to set the chess pieces to.
         */
        void setCurrentQuality(quality newQuality = LOW);

        /**
         * @brief Places a chess piece on the board.
         *
         * This function places a chess piece on the board at the specified position and rotation.
         *
         * @param pieceToPlace The chess piece to place on the board.
         * @param position The position to place the chess piece at.
         * @param rotation The rotation to place the chess piece at.
         * @param color The color of the chess piece.
         * @return The scene node of the placed chess piece.
         */
        irr::scene::IAnimatedMeshSceneNode *placePiece(irr::scene::IAnimatedMesh *pieceToPlace, irr::core::vector3df position, irr::core::vector3df rotation, teamColor color);

        /**
         * @brief Gets a chess piece.
         *
         * This function returns a chess piece of the specified type.
         *
         * @param type The type of the chess piece to get.
         * @return The chess piece of the specified type.
         */
		irr::scene::IAnimatedMesh* getPiece(pieceType type = PAWN);

private:
    irrlichtWindow *_ParentWindow; ///< A pointer to the irrlichtWindow object that is used as the parent window.

    const std::vector<std::string> _PiecePaths = {"/Pawn.obj", "/King.obj", "/Queen.obj" , "/Rook.obj", "/Bishop.obj", "/Knight.obj"}; ///< The paths to the chess piece OBJ files.

    irr::scene::ISceneManager *_SceneManager; ///< A pointer to the irr::scene::ISceneManager object for scene management.
    irr::video::IVideoDriver *_Driver; ///< A pointer to the irr::video::IVideoDriver object for video rendering.
    irr::IrrlichtDevice *_Device; ///< A pointer to the irr::IrrlichtDevice object for device management.

    irr::scene::IAnimatedMeshSceneNode *_Piece; ///< A pointer to the irr::scene::IAnimatedMeshSceneNode object for the chess piece.

    irr::scene::IAnimatedMesh* _Bishop; ///< A pointer to the bishop chess piece.
    irr::scene::IAnimatedMesh* _King; ///< A pointer to the king chess piece.
    irr::scene::IAnimatedMesh* _Knight; ///< A pointer to the knight chess piece.
    irr::scene::IAnimatedMesh* _Pawn; ///< A pointer to the pawn chess piece.
    irr::scene::IAnimatedMesh* _Queen; ///< A pointer to the queen chess piece.
    irr::scene::IAnimatedMesh* _Rook; ///< A pointer to the rook chess piece;

    irr::video::ITexture* _WhiteTexture; ///< A pointer to the white texture used for rendering the tiles.
    irr::video::ITexture* _BlackTexture; ///< A pointer to the black texture used for rendering the tiles.

    quality _CurrentQuality; ///< The current quality of the chess pieces.
};
