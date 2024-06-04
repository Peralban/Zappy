##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

#-------------- Main Variables --------------#

SRC		=       chessElement/chessBoard.cpp 		\
				chessElement/chessPiece.cpp 		\
				event/irrlichtEventHandler.cpp 		\
				zappyIrrlicht/irrlichtWindow.cpp    \
				player/playerInventory.cpp  		\
				player/team.cpp     				\
				player/player.cpp   				\
				player/playerPosition.cpp   		\
				game/ZappyGame.cpp					\
				main.cpp


TRUE_SRC 	= 	$(patsubst %,src/%, $(SRC))

OBJ			=	$(TRUE_SRC:.cpp=.o)

NAME		=	zappy_gui

WARNINGS	=	-Wall -Wextra -Wshadow

INCLUDE		=	-I./src

VALGRIND	= -g3

LIBS		= -lIrrlicht

CXXFLAGS	=	$(INCLUDE) $(WARNINGS) $(LIBS) #$(VALGRIND)

#-------------- Tests Variables --------------#

TESTS_SRC		=	mainTests.cpp

TESTS_TRUE_SRC	=	$(patsubst %,Tests/src/%, $(TEST_SRC))	\
					$(filter-out src/main.cpp, $(TRUE_SRC))

TESTS_FLAGS		=	--coverage -lcriterion

#-------------- Phony & Silent Rules --------------#

.PHONY: all clean fclean re tests_launch tests_run tests_compile

.SILENT: clean fclean re tests_launch tests_run tests_compile

#-------------- Rules --------------#

all:	$(NAME)

$(NAME):	$(OBJ)
	@g++ -o $(NAME) $(OBJ) $(CXXFLAGS)
	@if [ -f $(NAME) ]; then \
		printf "\033[1;32mCompilation completed ✅\033[0m\n"; \
	else \
		printf "\033[1;31mCompilation failed ❌\033[0m\n"; \
	fi


clean:
	rm -f $(OBJ)
	printf "\033[1;35mObject files removed ✅\033[0m\n"

fclean:	clean
	rm -f $(NAME)
	rm -f unit_tests*
	rm -f *.gc*
	rm -f vgcore*
	rm -f *.so
	printf "\033[1;35mFiles removed ✅\033[0m\n"

re:	fclean all
	printf "\033[1;35mRecompiled ✅\033[0m\n"

#-------------- Tests --------------#

tests_compile: fclean
	g++ -fopenmp -o unit_tests $(TESTS_TRUE_SRC) $(TESTS_FLAGS)
	@if [ -f unit_tests ]; then \
		printf "\033[1;32mTests compiled ✅\033[0m\n"; \
	else \
		printf "\033[1;31mTests compilation failed ❌\033[0m\n"; \
	fi

tests_launch:
	./unit_tests
	printf "\033[1;35mTests launched ✅\033[0m\n"
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches
	printf "\033[1;35mCoverage generated ✅\033[0m\n"

tests_run: tests_compile tests_launch
	printf "\033[1;32mTests runned ✅\033[0m\n"
