/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#include "chessPiece.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include <iostream>

chessPiece::chessPiece(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device)
{
    _SceneManager = sceneManager;
    _Device = device;
    _Driver = driver;
    _WhiteTexture = _Driver->getTexture("./GUI/assets/White.png");
    _BlackTexture = _Driver->getTexture("./GUI/assets/Black.png");
    if (!_WhiteTexture || !_BlackTexture) {
        std::cerr << "Error: Could not load textures" << std::endl;
        exit(84);
    }
}

chessPiece::chessPiece(irrlichtWindow *window)
{
    _SceneManager = window->getSceneManager();
    _Device = window->getDevice();
    _Driver = window->getDriver();
    _WhiteTexture = _Driver->getTexture("./GUI/assets/White.png");
    _BlackTexture = _Driver->getTexture("./GUI/assets/Black.png");
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

    std::string pawnPath = std::string(path) + "/Pawn.obj";
    std::string kingPath = std::string(path) + "/King.obj";
    std::string queenPath = std::string(path) + "/Queen.obj";
    std::string rookPath = std::string(path) + "/Rook.obj";
    std::string bishopPath = std::string(path) + "/Bishop.obj";
    std::string knightPath = std::string(path) + "/Knight.obj";

    irr::scene::IAnimatedMesh* pawnMesh = _SceneManager->getMesh(pawnPath.c_str());
    irr::scene::IAnimatedMesh* kingMesh = _SceneManager->getMesh(kingPath.c_str());
    irr::scene::IAnimatedMesh* queenMesh = _SceneManager->getMesh(queenPath.c_str());
    irr::scene::IAnimatedMesh* rookMesh = _SceneManager->getMesh(rookPath.c_str());
    irr::scene::IAnimatedMesh* bishopMesh = _SceneManager->getMesh(bishopPath.c_str());
    irr::scene::IAnimatedMesh* knightMesh = _SceneManager->getMesh(knightPath.c_str());


    if (!pawnMesh || !kingMesh || !queenMesh || !rookMesh || !bishopMesh || !knightMesh) {
        std::cerr << "Error: Could not load chess piece" << std::endl;
        exit(84);
    }

    _Pawn = pawnMesh;
    _King = kingMesh;
    _Queen = queenMesh;
    _Rook = rookMesh;
    _Bishop = bishopMesh;
    _Knight = knightMesh;
    
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
