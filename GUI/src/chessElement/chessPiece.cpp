/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** chessPiece
*/

#include "chessElement/chessPiece.hpp"
#include "zappyIrrlicht/irrlichtWindow.hpp"

chessPiece::chessPiece(ISceneManager *sceneManager = nullptr, IVideoDriver *driver = nullptr, IrrlichtDevice *device = nullptr)
{
    _SceneManager = sceneManager;
    _Device = device;
    _Driver = driver;
    _WhiteTexture = _Driver->getTexture("./assets/White.png");
    _BlackTexture = _Driver->getTexture("./assets/Black.png");
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
    _WhiteTexture = _Driver->getTexture("./assets/White.png");
    _BlackTexture = _Driver->getTexture("./assets/Black.png");
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
    std::string path = ("./assets/obj/obj" + qualityStr).c_str();

    std::string pawnPath = std::string(path) + "/Pawn.obj";
    std::string kingPath = std::string(path) + "/King.obj";
    std::string queenPath = std::string(path) + "/Queen.obj";
    std::string rookPath = std::string(path) + "/Rook.obj";
    std::string bishopPath = std::string(path) + "/Bishop.obj";
    std::string knightPath = std::string(path) + "/Knight.obj";

    std::cout << pawnPath << std::endl;
    if (!std::filesystem::exists(pawnPath) || !std::filesystem::exists(kingPath) || !std::filesystem::exists(queenPath) || !std::filesystem::exists(rookPath) || !std::filesystem::exists(bishopPath) || !std::filesystem::exists(knightPath)) {
        std::cerr << "Error: Could not find chess piece files" << std::endl;
        exit(84);
    }

    IAnimatedMesh* pawnMesh = _SceneManager->getMesh(pawnPath.c_str());
    IAnimatedMesh* kingMesh = _SceneManager->getMesh(kingPath.c_str());
    IAnimatedMesh* queenMesh = _SceneManager->getMesh(queenPath.c_str());
    IAnimatedMesh* rookMesh = _SceneManager->getMesh(rookPath.c_str());
    IAnimatedMesh* bishopMesh = _SceneManager->getMesh(bishopPath.c_str());
    IAnimatedMesh* knightMesh = _SceneManager->getMesh(knightPath.c_str());


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

IAnimatedMeshSceneNode *chessPiece::placePiece(IAnimatedMesh *pieceToPlace, vector3df position, teamColor color = DEFAULT)
{
    std::cout << "placePiece" << std::endl;
    IAnimatedMeshSceneNode* pawnNode = _SceneManager->addAnimatedMeshSceneNode(pieceToPlace);
    if (pawnNode) {
        pawnNode->setPosition(position); // Adjust position as needed
        pawnNode->setMaterialFlag(EMF_LIGHTING, false);
        if (color == WHITE) {
            std::cout << "white" << std::endl;
            pawnNode->setMaterialTexture(0, _WhiteTexture);
        } else {
            std::cout << "black" << std::endl;
            pawnNode->setMaterialTexture(0, _BlackTexture);
        }
        pawnNode->setMaterialType(video::EMT_SOLID);
        pawnNode->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);
    } else {
        std::cerr << "Error: Could not create mesh scene node for pawn." << std::endl;
        _Device->drop();
        return nullptr;
    }
    return pawnNode;
}

IAnimatedMesh *chessPiece::getPiece(pieceType type)
{
    std::cout << "getPiece" << std::endl;
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
