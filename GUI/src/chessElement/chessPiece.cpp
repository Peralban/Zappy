/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#include "chessPiece.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>

chessPiece::chessPiece(irrlichtWindow *window)
{
    _ParentWindow = window;
    _SceneManager = window->getSceneManager();
    _Device = window->getDevice();
    _Driver = window->getDriver();
    _WhiteTexture = window->getTextureLoader()->loadTexture("./GUI/assets/White.png");
    _BlackTexture = window->getTextureLoader()->loadTexture("./GUI/assets/Black.png");
    if (!_WhiteTexture || !_BlackTexture) {
        std::cerr << "Error: Could not load textures" << std::endl;
        exit(84);
    }
}

chessPiece::~chessPiece()
{
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

irr::scene::IAnimatedMeshSceneNode *chessPiece::placePiece(irr::scene::IAnimatedMesh *pieceToPlace, irr::core::vector3df position, irr::core::vector3df rotation, teamColor color = DEFAULT)
{
    irr::scene::IAnimatedMeshSceneNode* pawnNode = _SceneManager->addAnimatedMeshSceneNode(pieceToPlace);
    if (pawnNode) {
        pawnNode->setPosition(position); // Adjust position as needed
        pawnNode->setRotation(rotation);
        pawnNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        if (color == WHITE) {
            std::cout << "white" << std::endl;
            pawnNode->setMaterialTexture(0, _WhiteTexture);
        } else {
            std::cout << "black" << std::endl;
            pawnNode->setMaterialTexture(0, _BlackTexture);
        }
        pawnNode->setMaterialType(irr::video::EMT_SOLID);
        pawnNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    } else {
        std::cerr << "Error: Could not create mesh scene node for pawn." << std::endl;
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
