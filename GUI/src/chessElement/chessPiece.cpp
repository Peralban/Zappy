/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#include "chessPiece.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include "player/player.hpp"
#include <iostream>

chessPiece::chessPiece(irrlichtWindow *window)
{
    if (window == nullptr) {
        std::cerr << "chessPiece: Error: given parent window is Null" << std::endl;
        exit(84);
    }
    _ParentWindow = window;
    _SceneManager = window->getSceneManager();
    _Device = window->getDevice();
    _Driver = window->getDriver();
    _DefaultTexture = window->getTextureLoader()->createGetTexture(155, 155, 155, 255, "Default");
}


chessPiece::~chessPiece()
{
    if (_Pawn)
        _Pawn->drop();
    if (_King)
        _King->drop();
    if (_Queen)
        _Queen->drop();
    if (_Rook)
        _Rook->drop();
    if (_Bishop)
        _Bishop->drop();
    if (_Knight)
        _Knight->drop();
    if (_Piece)
        _Piece->drop();
    if (_DefaultTexture)
        _DefaultTexture->drop();
}

void chessPiece::loadPiece(quality choosedQuality)
{
    std::string qualityStr = (choosedQuality == LOW) ? "LowPoly" : (choosedQuality == MID) ? "MidPoly" : "HighPoly";
    std::string path = ("./GUI/assets/obj/obj" + qualityStr).c_str();

    std::vector<irr::scene::IAnimatedMesh*> meshes;
    for (const std::string& piecePath : _PiecePaths) {
        std::string fullPath = path + piecePath;
        irr::scene::IAnimatedMesh* mesh = _ParentWindow->getObjLoader()->loadObj(fullPath.c_str());
        if (!mesh) {
            std::cerr << "Error: Could not load chess piece: " << fullPath << std::endl;
            exit(84);
        }
        meshes.push_back(mesh);
    }

    if (meshes.size() != _PiecePaths.size()) {
        std::cerr << "Error: Could not load chess piece" << std::endl;
        exit(84);
    }

    _Pawn = meshes[0];
    _King = meshes[1];
    _Queen = meshes[2];
    _Rook = meshes[3];
    _Bishop = meshes[4];
    _Knight = meshes[5];
    
    std::cout << "Chess piece loaded" << std::endl;
}

void chessPiece::setCurrentQuality(quality newQuality)
{
    if (newQuality == _CurrentQuality)
        return;
    _CurrentQuality = newQuality;
    loadPiece(newQuality);
}

irr::scene::IAnimatedMeshSceneNode *chessPiece::placePiece(irr::scene::IAnimatedMesh *pieceToPlace, irr::core::vector3df position, irr::core::vector3df rotation, Player *Player)
{
    if (_SceneManager == nullptr) {
        std::cerr << "placePiece: Error: Scene manager is not set." << std::endl;
        exit(84);
    }
    if (pieceToPlace == nullptr) {
        std::cerr << "placePiece: Error: Piece to place is null." << std::endl;
        exit(84);
    }
    irr::scene::IAnimatedMeshSceneNode* pawnNode = _SceneManager->addAnimatedMeshSceneNode(pieceToPlace);
    if (pawnNode) {
        pawnNode->setPosition(position); // Adjust position as needed
        pawnNode->setRotation(rotation);
        pawnNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pawnNode->setMaterialType(irr::video::EMT_SOLID);
        pawnNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        if (Player != nullptr && Player->getTeam() != nullptr && Player->getTeam()->getColor() != nullptr) {
            pawnNode->setMaterialTexture(0, Player->getTeam()->getColor());
        } else {
            pawnNode->setMaterialTexture(0, _DefaultTexture);
            std::cerr << "placePiece: Warning: Player or team is null, using default texture." << std::endl;
        }

    } else {
        std::cerr << "placePiece: Error: Could not create mesh scene node for pawn." << std::endl;
        _Device->drop();
        return nullptr;
    }
    return pawnNode;
}

irr::scene::IAnimatedMesh *chessPiece::getPiece(pieceType type)
{
    switch (type) {
    case PAWN:
        return _Pawn;
    case KING:
        return _King;
    case QUEEN:
        return _Queen;
    case ROOK:
        return _Rook;
    case BISHOP:
        return _Bishop;
    case KNIGHT:
        return _Knight;
    }
    return nullptr;
}
