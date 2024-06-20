/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#include "ZappyGame.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include "../player/player.hpp"

ZappyGame::ZappyGame()
{
    this->_chessPieces = nullptr;
    this->_ParentDevice = nullptr;
    this->_chessBoard = nullptr;
    this->_serverDataParser = nullptr;
    this->_PlatformX = 0;
    this->_PlatformY = 0;
    this->_TileSize = 0;
    this->_TimeUnit = 0;
}

ZappyGame::~ZappyGame()
{
}

void ZappyGame::linkWithDevice(irrlichtWindow *parentDevice)
{
    if (parentDevice == nullptr) {
        std::cerr << "trying to link with device but given parentDevice is null" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_ParentDevice = parentDevice;
    this->initServerEvents();
    this->_chessBoard = new chessBoard(this);
    this->_chessBoard->setParentWindow(parentDevice);
}

void ZappyGame::createTeam(std::string teams, int Red, int Green, int Blue, int Alpha)
{
    Team *team = new Team();
    std::string teamName = teams + "_color";
    team->setColor(this->_ParentDevice->getTextureLoader()->createGetTexture(Red, Green, Blue, Alpha), teamName);
    team->setTeamName(teams);
    this->_teamsList[teams] = team;
}

void ZappyGame::setServerDataParser(ServerDataParser *serverDataParser)
{
    if (serverDataParser == nullptr) {
        std::cerr << "trying to set ServerDataParser but given serverDataParser is null" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_serverDataParser = serverDataParser;
}

void ZappyGame::loadChessPieces()
{
    this->_chessPieces = new chessPiece(this->_ParentDevice);
    if (this->_chessPieces == nullptr) {
        std::cerr << "loadChessPieces: Error: Couldn't create chessPieces" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (this->_ParentDevice == nullptr) {
        std::cerr << "loadChessPieces: Error: ParentDevice is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_chessPieces->loadPiece(this->_ParentDevice->getQuality());
}

void ZappyGame::initServerEvents()
{
    this->_serverDataParser = new ServerDataParser(this);
}

chessPiece *ZappyGame::getChessPieces()
{
    if (this->_chessPieces == nullptr)
        this->loadChessPieces();
    return this->_chessPieces;
}

irrlichtWindow *ZappyGame::getParentDevice()
{
    if (this->_ParentDevice == nullptr) {
        std::cerr << "getParentDevice: Error: ParentDevice is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_ParentDevice;
}

void ZappyGame::addPlayer(std::string name)
{    
    if (this->getPlayer(name) != nullptr)
        return;
    Player *player = new Player(this, name);
    if (player == nullptr) {
        std::cerr << "addPlayer: Error: Couldn't create player" << std::endl;
        exit(EXIT_FAILURE);
    }
    player->playerInit();
    this->_playerList[name] = player;
}

void ZappyGame::setPlatformSize(int x, int y)
{
    this->_PlatformX = x;
    this->_PlatformY = y;
}

void ZappyGame::setPlatformWidth(int x)
{
    this->_PlatformX = x;
    if (this->_chessBoard != nullptr)
        this->_chessBoard->setWidth(x);
    else
        std::cout << "setPlatformWidth: Warning: ChessBoard is not setted so platform with only settend on zappygame" << std::endl;
}

void ZappyGame::setPlatformHeight(int y)
{
    this->_PlatformY = y;
    if (this->_chessBoard != nullptr)
        this->_chessBoard->setHeight(y);
    else
        std::cout << "setPlatformHeight: Warning: ChessBoard is not setted so platform height only settend on zappygame" << std::endl;
}

void ZappyGame::setTileSize(float tileSize)
{
    this->_TileSize = tileSize;
    if (this->_chessBoard != nullptr)
        this->_chessBoard->setTileSize(tileSize);
    else
        std::cout << "setTileSize: Warning: ChessBoard is not setted so tileSize only settend on zappygame" << std::endl;
}

void ZappyGame::setTimeUnit(int timeUnit)
{
    this->_TimeUnit = timeUnit;
}

int ZappyGame::getTimeUnit()
{
    if (this->_TimeUnit == 0) {
        std::cout << "getTimeUnit: Warning: TimeUnit is not setted returning default 100" << std::endl;
        return 100;
    }
    return this->_TimeUnit;
}

int ZappyGame::getPlatformWidth()
{
    if (this->_PlatformX == 0) {
        std::cout << "getPlatformWidth: Warning: PlatformWidth is not setted returning default 10" << std::endl;
        return 10;
    }
    return this->_PlatformX;
}

int ZappyGame::getPlatformHeight()
{
    if (this->_PlatformY == 0) {
        std::cout << "getPlatformHeight: Warning: PlatformHeight is not setted returning default 10" << std::endl;
        return 10;
    }
    return this->_PlatformY;
}

float ZappyGame::getTileSize()
{
    if (this->_TileSize == 0) {
        std::cout << "getTileSize: Warning: TileSize is not setted returning default 10" << std::endl;
        return 10;
    }
    return this->_TileSize;
}

std::map<std::string, Player*> *ZappyGame::getPlayerList()
{
    if (this->_playerList.empty())
        std::cout << "getPlayerList: WARNING : PlayerList is empty" << std::endl;
    return &this->_playerList;
}

Player *ZappyGame::getPlayer(std::string name)
{
    if (this->_playerList.empty()) {
        std::cout << "getPlayer: WARNING : PlayerList is empty but trying to get a player by name" << std::endl;
        return nullptr;
    }
    if (this->_playerList.find(name) == this->_playerList.end()) {
        std::cout << "getPlayer: WARNING : Player not found returning nullptr" << std::endl;
        return nullptr;
    }
    return this->_playerList[name];
}

ServerDataParser *ZappyGame::getServerDataParser()
{
    if (this->_serverDataParser == nullptr) {
        std::cerr << "getServerDataParser: Error: ServerDataParser is not setted" << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_serverDataParser;
}

chessBoard *ZappyGame::getChessBoard()
{
    return this->_chessBoard;
}

Team *ZappyGame::getTeamFromName(std::string teamName)
{
    if (this->_teamsList.find(teamName) == this->_teamsList.end()) {
        std::cout << "getTeam: Warning: Team not found returning nullptr" << std::endl;
        return nullptr;
    }
    return this->_teamsList[teamName];
}

std::map<std::string, Team*> *ZappyGame::getTeamsList()
{
    return &this->_teamsList;
}

Team *ZappyGame::createGetTeam(std::string teamName, int Red, int Green, int Blue, int Alpha)
{
    if (this->_teamsList.find(teamName) == this->_teamsList.end()) {
        this->createTeam(teamName, Red, Green, Blue, Alpha);
    }
    return this->_teamsList[teamName];
}
