/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#include "chessElement/chessPiece.hpp"

chessPiece::chessPiece(IrrlichtDevice *device)
{
    Device = device;
    currentQuality = LowPoly;
    loadPiece("./assets/objLowPoly");
}

chessPiece::~chessPiece()
{
}

void chessPiece::loadPiece(const char *path)
{
    std::string pawnPath = std::string(path) + "/Pawn.obj";
    std::string kingPath = std::string(path) + "/King.obj";
    std::string queenPath = std::string(path) + "/Queen.obj";
    std::string rookPath = std::string(path) + "/Rook.obj";
    std::string bishopPath = std::string(path) + "/Bishop.obj";
    std::string knightPath = std::string(path) + "/Knight.obj";

    pawn = std::make_pair(Device->getSceneManager()->getMesh(pawnPath.c_str()), currentQuality);
    king = std::make_pair(Device->getSceneManager()->getMesh(kingPath.c_str()), currentQuality);
    queen = std::make_pair(Device->getSceneManager()->getMesh(queenPath.c_str()), currentQuality);
    rook = std::make_pair(Device->getSceneManager()->getMesh(rookPath.c_str()), currentQuality);
    bishop = std::make_pair(Device->getSceneManager()->getMesh(bishopPath.c_str()), currentQuality);
    knight = std::make_pair(Device->getSceneManager()->getMesh(knightPath.c_str()), currentQuality);
}

void chessPiece::setCurrentQuality(quality newQuality)
{
    if (newQuality == currentQuality)
        return;
    currentQuality = newQuality;
    loadPiece(("./assets/obj" + std::to_string(newQuality)).c_str());
}

IAnimatedMesh *chessPiece::getPiece(pieceType type)
{
    switch (type) {
    case PAWN:
        return pawn.first;
    case KING:
        return king.first;
    case QUEEN:
        return queen.first;
    case ROOK:
        return rook.first;
    case BISHOP:
        return bishop.first;
    case KNIGHT:
        return knight.first;
    }
    return nullptr;
}
