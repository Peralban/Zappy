##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

#-------------- Main Variables --------------#

SRC		= 		objFile/objLoader.cpp       \
				chessElement/chessBoard.cpp \
				chessElement/chessPiece.cpp \
				event/eventHandler.cpp \
				zappyIrrlicht/irrlichtWindow.cpp       \
				main.cpp


TRUE_SRC 	= 	$(patsubst %,src/%, $(SRC))

OBJ			=	$(TRUE_SRC:.cpp=.o)

NAME		=	zappy_gui

WARNINGS	=	#-Wall -Wextra -Wshadow

IRRLICHTPATH = /home/smalluwu/Documents/Irrlicht/

# -I../../include  -L../../lib/Linux
INCLUDE		=	-I./include -I/usr/X11R6/include -I$(IRRLICHTPATH)include

VALGRIND	=

LIBS		= -L$(IRRLICHTPATH)lib/Linux -lIrrlicht -L/usr/X11R6/lib -lGL -lXxf86vm -lXext -lX11 -lXcursor

CXXFLAGS	=	$(INCLUDE) $(WARNINGS) $(LIBS) -O3 -ffast-math #$(VALGRIND)

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
