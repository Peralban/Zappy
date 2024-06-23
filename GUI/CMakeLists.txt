cmake_minimum_required(VERSION 3.10)

# Set the project name
project(zappy_gui)

# Add the executable
add_executable(Zappy_Server
    src/chessElement/chessBoard.cpp
    src/chessElement/chessPiece.cpp
    src/chessElement/tiles.cpp
    src/items/items.cpp
    src/loader/objLoader.cpp
    src/loader/textureLoader.cpp
    src/event/irrlichtEventHandler.cpp
    src/event/serverDataReceiver.cpp
    src/zappyIrrlicht/irrlichtWindow.cpp
    src/networkGui/guiClient.cpp
    src/player/team.cpp
    src/core/Core.cpp
    src/player/player.cpp
    src/player/playerPosition.cpp
    src/game/ZappyGame.cpp
    src/main.cpp
)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the include directories
include_directories(
    src/chessElement
    src/items
    src/loader
    src/event
    src/zappyIrrlicht
    src/networkGui
    src/player
    src/core
    src/game
)

# Add the compiler warnings
target_compile_options(Zappy_Server PRIVATE -Wall -Wextra -Wshadow)

# Link the Irrlicht library
target_link_libraries(Zappy_Server PRIVATE Irrlicht)