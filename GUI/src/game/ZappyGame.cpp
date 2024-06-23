/*
** EPITECH PROJECT, 2024
** GUI
** File description:
** ZappyGame
*/

#include "ZappyGame.hpp"
#include "../zappyIrrlicht/irrlichtWindow.hpp"
#include "../player/player.hpp"
#include <random>

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
    delete _chessPieces;
    delete _chessBoard;
    delete _serverDataParser;
    for (auto& pair : _playerList) {
        delete pair.second;
    }
    for (auto& pair : _teamsList) {
        delete pair.second;
    }
}

void ZappyGame::linkWithDevice(irrlichtWindow *parentDevice)
{
    if (parentDevice == nullptr) {
        throw NullableParentDevice();
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
    team->setColor(this->_ParentDevice->getTextureLoader()->createGetTexture(Red, Green, Blue, Alpha, teamName), teamName);
    team->setTeamName(teams);
    this->_teamsList[teams] = team;
}

void ZappyGame::setServerDataParser(ServerDataParser *serverDataParser)
{
    if (serverDataParser == nullptr) {
        throw NullableServerDataParser();
    }
    this->_serverDataParser = serverDataParser;
}

void ZappyGame::loadChessPieces()
{
    this->_chessPieces = new chessPiece(this->_ParentDevice);
    if (this->_chessPieces == nullptr) {
        throw UnableCreateChessPiece();
    }
    if (this->_ParentDevice == nullptr) {
        throw UnsetParentDevice();
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
        throw UnsetParentDevice();
    }
    return this->_ParentDevice;
}

void ZappyGame::addPlayer(std::string name)
{    
    if (this->getPlayer(name) != nullptr)
        return;
    Player *player = new Player(this, name);
    if (player == nullptr) {
        throw UnableCreatePlayer();
    }
    player->playerInit();
    this->_playerList[name] = player;
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
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 255); // define the range

    this->addPlayer(args[1]);
    Player *player = this->getPlayer(args[1]);
    player->playerInit();
    player->getPlayerPosition()->setPos(std::stoi(args[2]), std::stoi(args[3]), 1);
    player->setOrientation(std::stoi(args[4]));
    player->setLevel(std::stoi(args[5]));
    Team *newteam = this->createGetTeam(args[6], distr(gen), distr(gen), distr(gen), 255);
    player->setTeam(newteam);
    Tile *tile = this->_chessBoard->getMap()[std::stoi(args[2])][std::stoi(args[3])];
    tile->setPlayer(tile->getPlayer() + 1);
    tile->setEgg(tile->getEgg() - 1);
    this->_ParentDevice->getEventReceiver()->addPlayer(_playerList[args[1]]);
}

void ZappyGame::broadcastMessage(std::string cmd)
{
    //pbc #n message\n
    std::vector<std::string> args = split(cmd, ' ');

    Player *player = this->getPlayer(args[1]);
    player->setBroadcastMessage(args[2]);
}

void ZappyGame::deletePlayer(std::string name)
{
    if (this->_playerList.find(name) == this->_playerList.end()) {
        std::cout << "removePlayer: Warning: Player not found" << std::endl;
        return;
    }

    this->getParentDevice()->getEventReceiver()->remmovePlayerByName(name);
    delete this->_playerList[name];
    this->_playerList.erase(name);
}

void ZappyGame::deletePlayer(Player *player)
{
    if (player == nullptr) {
        std::cout << "removePlayer: Warning: Player is nullptr" << std::endl;
        return;
    }
    this->deletePlayer(player->getName());
}

void ZappyGame::playerDie(std::string cmd)
{
    //pdi #n\n
    std::vector<std::string> args = split(cmd, ' ');

    Tile *tile = this->_chessBoard->getMap()[this->getPlayer(args[1])->getPlayerPosition()->getX()][this->getPlayer(args[1])->getPlayerPosition()->getY()];
    tile->setPlayer(tile->getPlayer() - 1);
    this->deletePlayer(args[1]);
}

void ZappyGame::newEgg(std::string cmd)
{
    //enw #e #n X Y\n
    std::vector<std::string> args = split(cmd, ' ');

    Tile *tile = this->_chessBoard->getMap()[std::stoi(args[3])][std::stoi(args[4])];
    tile->setEgg(tile->getEgg() + 1);
}

void ZappyGame::updatePlayerPos(std::string cmd)
{
    //ppo #n X Y O\n
    std::vector<std::string> args = split(cmd, ' ');

    Player *player = this->getPlayer(args[1]);
    player->getPlayerPosition()->setPos(std::stoi(args[2]), std::stoi(args[3]), 1);
    player->setOrientation(args[4] == "N" ? 0 : args[4] == "E" ? 1 : args[4] == "S" ? 2 : 3);
    player->updatePlayerPos();
}

void ZappyGame::updatePlayerLevel(std::string cmd)
{
    //plv #n L\n
    std::vector<std::string> args = split(cmd, ' ');

    Player *player = this->getPlayer(args[1]);
    player->setLevel(std::stoi(args[2]));
    player->updateLevel();
}

void ZappyGame::updatePlayerInventory(std::string cmd)
{
    //pin #n X Y T1 T2 T3 T4 T5 T6 T7\n
    std::vector<std::string> args = split(cmd, ' ');

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
}

void ZappyGame::setTimeUnit(int timeUnit)
{
    this->_TimeUnit = timeUnit;
}

int ZappyGame::getTimeUnit()
{
    if (this->_TimeUnit == 0)
        return 10;
    return this->_TimeUnit;
}

int ZappyGame::getPlatformWidth()
{
    return this->_PlatformX;
}

int ZappyGame::getPlatformHeight()
{
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

void ZappyGame::playerTake(std::string cmd)
{
    //pgt #n T\n
    std::vector <std::string> args = split(cmd, ' ');
    this->_chessBoard->getMap()[this->getPlayer(args[1])->getPlayerPosition()->getX()][this->getPlayer(args[1])->getPlayerPosition()->getY()]->dropRessource(args[2]);

    this->getPlayer(args[1])->takeResource(args[2]);
}

void ZappyGame::playerDrop(std::string cmd)
{
    //pdr #n T\n
    std::vector <std::string> args = split(cmd, ' ');
    this->_chessBoard->getMap()[this->getPlayer(args[1])->getPlayerPosition()->getX()][this->getPlayer(args[1])->getPlayerPosition()->getY()]->takeRessource(args[2]);

    this->getPlayer(args[1])->dropResource(args[2]);
}

ServerDataParser *ZappyGame::getServerDataParser()
{
    if (this->_serverDataParser == nullptr) {
        throw UnsetServerDataParser();
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
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 255); // define the range

        while (this->_teamsList.find(std::to_string(Red)) != this->_teamsList.end() &&
        this->_teamsList.find(std::to_string(Green)) != this->_teamsList.end() &&
        this->_teamsList.find(std::to_string(Blue)) != this->_teamsList.end()) {
            Red = distr(gen); // generate random numbers
            Green = distr(gen);
            Blue = distr(gen);
            Alpha = 255;
        }
        this->createTeam(teamName, Red, Green, Blue, Alpha);
    }
    return this->_teamsList[teamName];
}
