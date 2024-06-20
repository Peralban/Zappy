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
    this->_chessBoard = new chessBoard(this);
    this->_chessBoard->setParentWindow(parentDevice);
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
    this->_playerList.push_back(std::make_pair(name, player));
}

static std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


void ZappyGame::newPlayer(std::string cmd)
{
    //pnw #n X Y O L N\n
    std::vector<std::string> args = split(cmd, ' ');

    if (args.size() != 8) {
        std::cerr << "newPlayer: Error: pnw command should have 8 arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->addPlayer(args[1]);
    Player *player = this->getPlayer(args[1]);
    player->getPlayerPosition()->setPos(std::stoi(args[2]), std::stoi(args[3]));
    player->setOrientation(std::stoi(args[4]));
    player->setLevel(std::stoi(args[5]));
    player->getTeam()->setTeamName(args[6]);
    Tile *tile = this->_chessBoard->getMap()[std::stoi(args[2])][std::stoi(args[3])];
    tile->setPlayer(tile->getPlayer() + 1);
    tile->setEgg(tile->getEgg() - 1);
}

void ZappyGame::broadcastMessage(std::string cmd)
{
    //pbc #n message\n
    std::vector<std::string> args = split(cmd, ' ');

    if (args.size() != 3) {
        std::cerr << "broadcastMessage: Error: pbc command should have 3 arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    Player *player = this->getPlayer(args[1]);
    player->setBroadcastMessage(args[2]);
}

void ZappyGame::newEgg(std::string cmd)
{
    //enw #e #n X Y\n
    std::vector<std::string> args = split(cmd, ' ');

    if (args.size() != 5) {
        std::cerr << "newEgg: Error: enw command should have 5 arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    Tile *tile = this->_chessBoard->getMap()[std::stoi(args[3])][std::stoi(args[4])];
    tile->setEgg(tile->getEgg() + 1);
}

void ZappyGame::updatePlayerPos(std::string cmd)
{
    //ppo #n X Y O\n
    std::vector<std::string> args = split(cmd, ' ');

    if (args.size() != 5) {
        std::cerr << "updatePlayerPos: Error: ppo command should have 5 arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    Player *player = this->getPlayer(args[1]);
    player->getPlayerPosition()->setPos(std::stoi(args[2]), std::stoi(args[3]));
    player->setOrientation(std::stoi(args[4]));
}

void ZappyGame::updatePlayerLevel(std::string cmd)
{
    //plv #n L\n
    std::vector<std::string> args = split(cmd, ' ');

    if (args.size() != 3) {
        std::cerr << "updatePlayerLevel: Error: plv command should have 3 arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    Player *player = this->getPlayer(args[1]);
    player->setLevel(std::stoi(args[2]));
}

void ZappyGame::updatePlayerInventory(std::string cmd)
{
    //pin #n X Y T1 T2 T3 T4 T5 T6 T7\n
    std::vector<std::string> args = split(cmd, ' ');

    if (args.size() != 12) {
        std::cerr << "updatePlayerInventory: Error: pin command should have 12 arguments" << std::endl;
        exit(EXIT_FAILURE);
    }
    Player *player = this->getPlayer(args[1]);
    player->setInventory(std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]), std::stoi(args[7]), std::stoi(args[8]), std::stoi(args[9]), std::stoi(args[10]));
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

std::vector<std::pair<std::string, Player*>> *ZappyGame::getPlayerList()
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
    for (auto &player : this->_playerList) {
        if (player.first == name) {
            return player.second;
        }
    }
    return nullptr;
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
