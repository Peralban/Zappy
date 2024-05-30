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
		enum pieceType {BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK};
		enum pieceColor {BLACK, WHITE};
		enum quality {LowPoly, MidPoly, HighPoly};	

		chessPiece(IrrlichtDevice *device);
        ~chessPiece();

        void loadPiece(const char *path);
        void setCurrentQuality(quality newQuality);
		IAnimatedMesh* getPiece(pieceType type);

	private:
        IrrlichtDevice* Device;
		quality currentQuality;
		std::pair<scene::IAnimatedMesh*, quality> bishop;
		std::pair<scene::IAnimatedMesh*, quality> king;
		std::pair<scene::IAnimatedMesh*, quality> knight;
		std::pair<scene::IAnimatedMesh*, quality> pawn;
		std::pair<scene::IAnimatedMesh*, quality> queen;
		std::pair<scene::IAnimatedMesh*, quality> rook;
};
