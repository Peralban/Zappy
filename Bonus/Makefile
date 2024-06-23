##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

# Define the target and source files
TARGET = UltimateTester
SRCS = tester.cpp

# Define the compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -lIrrlicht

define progress_bar
	@echo -n "["
	@for i in $(shell seq 1 $(1)); do \
		echo -n "#"; \
	done
	@for i in $(shell seq $(1) 10); do \
		echo -n " "; \
	done
	@echo -n "]"
	@echo -n " $(2)%"
	@echo -ne "\r"
endef

# Define the build target
$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) -o $@ $^
	@$(call progress_bar,10,100)

.PHONY: clean

clean:
	@rm -f $(TARGET)