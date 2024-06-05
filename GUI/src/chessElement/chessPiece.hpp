/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#pragma once

#include <irrlicht/irrlicht.h>

class irrlichtWindow;

enum pieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING};

enum quality {
    LOW,
    MID,
    HIGH
};

enum teamColor {
    DEFAULT,
    BLACK,
    WHITE,
    RED,
    GREEN,
    BLUE
};

class chessPiece {
	public:
        chessPiece(irr::scene::ISceneManager *sceneManager = nullptr, irr::video::IVideoDriver *driver = nullptr, irr::IrrlichtDevice *device = nullptr);
        chessPiece(irrlichtWindow *window);
        ~chessPiece();

        void loadPiece(quality choosedQuality);
        void initTextures();
        void setCurrentQuality(quality newQuality);
        irr::scene::IAnimatedMeshSceneNode *placePiece(irr::scene::IAnimatedMesh *pieceToPlace, irr::core::vector3df position, irr::core::vector3df rotation, teamColor color);
		irr::scene::IAnimatedMesh* getPiece(pieceType type);

private:
    irr::scene::ISceneManager *_SceneManager;
    irr::video::IVideoDriver *_Driver;
    irr::IrrlichtDevice *_Device;
    irr::scene::IAnimatedMeshSceneNode *_Piece;
    irr::scene::IAnimatedMesh* _Bishop;
    irr::scene::IAnimatedMesh* _King;
    irr::scene::IAnimatedMesh* _Knight;
    irr::scene::IAnimatedMesh* _Pawn;
    irr::scene::IAnimatedMesh* _Queen;
    irr::scene::IAnimatedMesh* _Rook;
    irr::video::ITexture* _WhiteTexture;
    irr::video::ITexture* _BlackTexture;
    quality _CurrentQuality;
};
