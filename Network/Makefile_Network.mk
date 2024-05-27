##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

#-------------- Main Variables --------------#

SRC		= 		main.c								\
				ClientList/client_list.c			\
				ClientList/client_list_bis.c		\
				ErrorHandling/return_error_str.c	\
				ErrorHandling/check_return_value.c	\
				Server/server_loop.c				\
				Server/zappy_network.c				\
				Parsing/parse_args.c				\

TRUE_SRC 	= 	$(patsubst %,src/%, $(SRC))

OBJ			=	$(TRUE_SRC:.c=.o)

NAME		=	zappy_server

WARNINGS	=	-Wall -Wextra -Wshadow

INCLUDE		=	-I./include

VALGRIND	= -g3

CFLAGS	=	$(INCLUDE) $(WARNINGS) #$(VALGRIND)

#-------------- Tests Variables --------------#

TESTS_SRC		=	mainTest.c						\
					ClientList/tests_linked_list.c	\

TESTS_TRUE_SRC	=	$(patsubst %,Tests/src/%, $(TESTS_SRC)) \
					$(filter-out src/main.c, $(TRUE_SRC))

TESTS_FLAGS		=	--coverage -lcriterion

#-------------- Phony & Silent Rules --------------#

.PHONY: all clean fclean re tests_launch tests_run tests_compile

.SILENT: clean fclean re tests_launch tests_run tests_compile

#-------------- Rules --------------#

all:	$(NAME)

$(NAME):	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)
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
	printf "\033[1;35mBinary removed ✅\033[0m\n"

re: fclean all

tests_compile: fclean
	$(info $(TESTS_TRUE_SRC))
	@echo $(TESTS_TRUE_SRC)
	gcc -o unit_tests $(TESTS_TRUE_SRC) $(CFLAGS) $(TESTS_FLAGS)
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
