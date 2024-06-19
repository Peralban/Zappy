cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Zappy_Server)

# Add the executable
add_executable(Zappy_Server
    src/main.c
    src/ClientList/client_list.c
    src/ClientList/client_list_bis.c
    src/ErrorHandling/check_return_value.c
    src/Server/init_in_game_stuct.c
    src/Server/zappy_network.c
    src/Server/server_loop.c
    src/Parsing/parse_args.c
    src/Parsing/move_args_to_struct.c
    src/lib/my_str_to_word_array.c
        src/Game/game_command_bis.c
        src/Game/game_command.c
        src/Game/egg_hatching.c
        src/Game/game_functions.c
        src/Server/update_players.c
        src/Game/game_tick.c
        src/Server/complete_server.c
)

# Specify the C standard
set(CMAKE_C_STANDARD 11)

# Add the include directories
include_directories(include)

# Add the compiler warnings
target_compile_options(Zappy_Server PRIVATE -Wall -Wextra -Wshadow)
