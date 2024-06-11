
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
	@cp $(MAIN_PY) $(TARGET)
	@chmod 777 $(TARGET)

clean:
	rm -rf src/__pycache__

fclean: clean
	@rm -f $(TARGET)

re: fclean all

test_compile:

tests_launch:

tests_run:
	python3 -m unittest Tests/test.py

.PHONY: all clean fclean re tests_run tests_launch test_compile
