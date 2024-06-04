
##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

SRC_DIR = src
MAIN_PY = $(SRC_DIR)/main.py
TARGET = zappy_ai

all: $(TARGET)

$(TARGET): $(MAIN_PY)
	cp $(MAIN_PY) $(TARGET)
	chmod 777 $(TARGET)

tests_run:
	@echo ""

clean:
	rm -rf src/__pycache__

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re tests_run
