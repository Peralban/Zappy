##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

SRC			= 		main.cpp

TRUE_SRC 	= 		$(patsubst %,src/%, $(SRC))

OBJ			= 		$(TRUE_SRC:.cpp=.o)

NAME		= 		zappy_ai

WARNINGS	= 		-Wall -Wextra -Wshadow

INCLUDE		= 		-I./include

VALGRIND	= 		-g3

LIBS		=

CXXFLAGS	= $(INCLUDE) $(WARNINGS)

.PHONY: all clean fclean re

.SILENT: clean fclean re

all:
	@g++ -o $(NAME) $(TRUE_SRC) $(CXXFLAGS)
	@if [ -f $(NAME) ]; then \
		printf "\033[1;32mCompilation completed ✅\033[0m\n"; \
	else \
		printf "\033[1;31mCompilation failed ❌\033[0m\n"; \
	fi

clean:
	@rm -f $(OBJ)
	@if [ ! -f $(OBJ) ]; then \
		printf "\033[1;32mObject files deleted ✅\033[0m\n"; \
	else \
		printf "\033[1;31mObject files deletion failed ❌\033[0m\n"; \
	fi

fclean: clean
	@rm -f $(NAME)
	@if [ ! -f $(NAME) ]; then \
		printf "\033[1;32mBinary deleted ✅\033[0m\n"; \
	else \
		printf "\033[1;31mBinary deletion failed ❌\033[0m\n"; \
	fi

re: fclean all

# Tests

tests_compile:
	@g++ -o unit_tests $(TEST_TRUE_SRC) $(TESTS_FLAGS)
	@if [ -f unit_tests ]; then \
		printf "\033[1;32mTests compilation completed ✅\033[0m\n"; \
	else \
		printf "\033[1;31mTests compilation failed ❌\033[0m\n"; \
	fi

tests_launch:
	@./unit_tests
	@if [ $$? -eq 0 ]; then \
		printf "\033[1;32mTests passed ✅\033[0m\n"; \
	else \
		printf "\033[1;31mTests failed ❌\033[0m\n"; \
	fi

tests_run: #tests_compile tests_launch