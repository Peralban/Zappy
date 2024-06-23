##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NETWORK_MAKEFILE = Makefile_Network.mk
GUI_MAKEFILE = Makefile_GUI.mk
AI_MAKEFILE = Makefile_AI.mk

.PHONY: all clean fclean re

.SILENT: all clean fclean re

all: zappy_server zappy_ai zappy_gui

zappy_server:
	@$(MAKE) -f $(NETWORK_MAKEFILE) -C Network
	@if [ -f Network/zappy_server ]; then \
  		mv Network/zappy_server .; \
  		printf "\033[1;32mServer compiled & moved ✅\033[0m\n"; \
	else \
		printf "\033[1;31mProblem with Server compilation ❌\033[0m\n"; \
	fi

zappy_ai:
	@$(MAKE) -f $(AI_MAKEFILE) -C AI
	@if [ -f AI/zappy_ai ]; then \
  		mv AI/zappy_ai .; \
  		printf "\033[1;32mAI compiled & moved ✅\033[0m\n"; \
	else \
		printf "\033[1;31mProblem with AI compilation ❌\033[0m\n"; \
	fi

zappy_gui:
	@$(MAKE) -f $(GUI_MAKEFILE) -C GUI
	@if [ -f GUI/zappy_gui ]; then \
  		mv GUI/zappy_gui .; \
  		printf "\033[1;32mGUI compiled & moved ✅\033[0m\n"; \
	else \
		printf "\033[1;31mProblem with GUI compilation ❌\033[0m\n"; \
	fi

clean:
	@$(MAKE) -f $(NETWORK_MAKEFILE) -C Network clean
	@$(MAKE) -f $(GUI_MAKEFILE) -C GUI clean
	@$(MAKE) -f $(AI_MAKEFILE) -C AI clean

fclean:
	@$(MAKE) -f $(NETWORK_MAKEFILE) -C Network fclean
	@$(MAKE) -f $(GUI_MAKEFILE) -C GUI fclean
	@$(MAKE) -f $(AI_MAKEFILE) -C AI fclean
	rm -f unit_tests*
	rm -f *.gc*
	rm -f vgcore*
	rm -f zappy_server
	rm -f zappy_ai
	rm -f zappy_gui

re: fclean zappy_ai zappy_server zappy_gui

tests_run:
	@$(MAKE) -f $(NETWORK_MAKEFILE) -C Network tests_run
	@$(MAKE) -f $(GUI_MAKEFILE) -C GUI tests_run
	@$(MAKE) -f $(AI_MAKEFILE) -C AI tests_run
	gcovr --exclude Network/Tests --exclude GUI/Tests --exclude AI/Tests
	@printf "\033[1;32mCoverage generated ✅\033[0m\n"

#-------------- Docs --------------#

doc:
	@which doxygen >/dev/null 2>&1 || { printf "\033[1;31mDoxygen is not installed. Aborting.\nInstall doxygen\033[0m\n"; exit 1; }
	@which pdflatex >/dev/null 2>&1 || { printf "\033[1;31mpdflatex is not installed. Aborting.\nInstall texlive-scheme-full\033[0m\n"; exit 1; }
	@doxygen Doc/AI/Doxyfile
	@mv ./Doc/doxygen ./Doc/AI
	@make -C Doc/AI/doxygen/latex
	@mv Doc/AI/doxygen/latex/refman.pdf ./Doc/ZappyAIDevDocumentation.pdf
	@doxygen Doc/Network/Doxyfile
	@mv ./Doc/doxygen ./Doc/Network
	@make -C Doc/Network/doxygen/latex
	@mv Doc/Network/doxygen/latex/refman.pdf ./Doc/ZappyNetworkDevDocumentation.pdf
	@doxygen Doc/GUI/Doxyfile
	@mv ./Doc/doxygen ./Doc/GUI
	@make -C Doc/GUI/doxygen/latex
	@mv Doc/GUI/doxygen/latex/refman.pdf ./Doc/ZappyGUIDevDocumentation.pdf
	@printf "\033[1;35mDocumentation generated ✅\033[0m\n"

doc_clean:
	@rm -rf Doc/AI/doxygen
	@rm -rf Doc/Network/doxygen
	@rm -rf Doc/GUI/doxygen
	@rm -f Doc/*.pdf
	@printf "\033[1;35mDocumentation removed ✅\033[0m\n"

doc_re: doc_clean doc
