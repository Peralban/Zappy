/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#pragma once

#include "main.hpp"

class chessPiece {
	public:
        chessPiece(ISceneManager *smgr, IVideoDriver *_Driver, IrrlichtDevice *_Device);
        ~chessPiece();

        void loadPiece(const char *path);
        void initTextures();
        void setCurrentQuality(quality newQuality);
        IAnimatedMeshSceneNode *placePiece(IAnimatedMesh *pieceToPlace, vector3df position, pieceColor color);
		IAnimatedMesh* getPiece(pieceType type);

	private:
        ISceneManager *_SceneManager;
        IVideoDriver *_Driver;
        IrrlichtDevice *_Device;
        IAnimatedMeshSceneNode *_Piece;
		quality _CurrentQuality;
		scene::IAnimatedMesh* _Bishop;
		scene::IAnimatedMesh* _King;
		scene::IAnimatedMesh* _Knight;
		scene::IAnimatedMesh* _Pawn;
		scene::IAnimatedMesh* _Queen;
		scene::IAnimatedMesh* _Rook;
        ITexture* whiteTexture;
        ITexture* blackTexture;
};
