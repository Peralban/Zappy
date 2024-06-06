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
				ErrorHandling/check_return_value.c	\
				Server/zappy_network.c				\
				Server/server_loop.c				\
				Server/init_in_game_stuct.c			\
				Server/update_players.c				\
				Parsing/parse_args.c				\
				Parsing/move_args_to_struct.c		\
				lib/my_str_to_word_array.c			\
				lib/char_is_in_str.c				\
				lib/my_len_before_char.c			\
				lib/get_nbr_of_char.c				\
				Game/game_functions.c				\
				Game/game_command.c					\
				Game/look_around.c					\
				Game/inventory_function.c			\
				Game/launch_broadcast.c				\

TRUE_SRC 	= 	$(patsubst %,src/%, $(SRC))

OBJ			=	$(TRUE_SRC:.c=.o)

NAME		=	zappy_server

WARNINGS	=	-Wall -Wextra -Wshadow

INCLUDE		=	-I./include

VALGRIND	=	-g3

CFLAGS	=	$(INCLUDE) $(WARNINGS) $(VALGRIND)

#-------------- Tests Variables --------------#

TESTS_SRC		=	mainTest.c									\
					ClientListTests/tests_linked_list.c			\
					libTests/char_is_in_str_test.c				\
					libTests/get_nbr_of_char_test.c				\
					libTests/my_len_before_char_test.c			\
					libTests/my_str_to_word_array_test.c		\
					ErrorHandlingTests/check_return_value_test.c\
					ParsingTests/move_args_to_struct_test.c		\
					ParsingTests/parse_args_test.c				\
					ServerTests/init_in_game_stuct_test.c		\

TESTS_TRUE_SRC	=	$(patsubst %,Tests/src/%, $(TESTS_SRC)) \
					$(filter-out src/main.c, $(TRUE_SRC))

TESTS_LIBS		=	--coverage -lcriterion

TESTS_INCLUDE	=	$(INCLUDE) -I./Tests/src

TESTS_FLAGS		= $(TESTS_INCLUDE) $(WARNINGS) $(TESTS_LIBS)

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
	@printf "\033[1;35mObject files removed ✅\033[0m\n"

fclean:	clean
	rm -f $(NAME)
	rm -f unit_tests*
	rm -f *.gc*
	rm -f vgcore*
	rm -f *.so
	@printf "\033[1;35mBinary removed ✅\033[0m\n"

re: fclean all

tests_compile: fclean
	gcc -o unit_tests $(TESTS_TRUE_SRC) $(TESTS_FLAGS)
	@if [ -f unit_tests ]; then \
		printf "\033[1;32mTests compiled ✅\033[0m\n"; \
	else \
		printf "\033[1;31mTests compilation failed ❌\033[0m\n"; \
	fi

tests_launch:
	./unit_tests
	@printf "\033[1;35mNetWork Tests launched ✅\033[0m\n"

tests_run: tests_compile tests_launch
	@printf "\033[1;32mTests runned ✅\033[0m\n"
