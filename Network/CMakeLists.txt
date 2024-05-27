cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Zappy_Server)

# Add the executable
add_executable(Zappy_Server
    src/main.c
    src/ClientList/client_list.c
    src/ClientList/client_list_bis.c
    src/ErrorHandling/return_error_str.c
    src/ErrorHandling/check_return_value.c
    src/Server/server_loop.c
    src/Server/zappy_network.c
    src/Parsing/parse_args.c
)

# Specify the C standard
set(CMAKE_C_STANDARD 11)

# Add the include directories
include_directories(include)

# Add the compiler warnings
target_compile_options(Zappy_Server PRIVATE -Wall -Wextra -Wshadow)
