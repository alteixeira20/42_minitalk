# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 16:36:58 by paalexan          #+#    #+#              #
#    Updated: 2025/03/08 18:51:43 by paalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler & Flags
CC					:= cc
CFLAGS				:= -Wall -Werror -Wextra -g
VFLAGS				:= --leak-check=full --show-leak-kinds=all --track-origins=yes

# Directories
SRC_DIR				:= src
OBJ_DIR				:= obj
RESULTS_DIR			:= results

# Libft
LIBFT_REPO			:= https://github.com/alteixeira20/42_libft.git
LIBFT_DIR			:= libft
LIBFT				:= $(LIBFT_DIR)/libft.a

# Source Files
SRC_SERVER			:= $(SRC_DIR)/server.c
SRC_CLIENT			:= $(SRC_DIR)/client.c

OBJ_SERVER			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_SERVER))
OBJ_CLIENT			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_CLIENT))

# Executables
SERVER				:= server
CLIENT				:= client

# Tester
GET_PID_CMD			:= $(shell pgrep -f server)
TEST_FILE			:= test_cases.txt

# Targets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rules
all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(ORANGE)$(PREFIX)$(RESET) Cloning $(BOLD)Libft$(RESET) and waiting for compilation..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR) > /dev/null 2>&1; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --silent > /dev/null 2>&1
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Libft$(RESET) compiled $(GREEN)successfully$(RESET)."

$(SERVER): $(OBJ_SERVER) $(OBJ_UTILS)
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_UTILS) $(LIBFT) -o $(SERVER)
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Server$(RESET) compiled $(GREEN)successfully$(RESET)."

$(CLIENT): $(OBJ_CLIENT) $(OBJ_UTILS)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(OBJ_UTILS) $(LIBFT) -o $(CLIENT)
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Client$(RESET) compiled $(GREEN)successfully$(RESET)."

# Testing Rules
start_server:
	@mkdir -p $(RESULTS_DIR)
	@touch $(RESULTS_DIR)/server.out
	@echo "$(ORANGE)$(PREFIX)$(RESET) Starting server and logging to $(ORANGE)$(RESULTS_DIR)/server.out$(RESET)."
	@stdbuf -oL ./$(SERVER) > $(RESULTS_DIR)/server.out 2>&1 & echo $$! > $(RESULTS_DIR)/server.pid
	@sleep 1
	@while [ ! -s "$(RESULTS_DIR)/server.out" ]; do \
		echo "$(ORANGE)$(PREFIX)$(RESET) Waiting for server to start..."; \
		sleep 0.2; \
	done
	@if [ -f $(RESULTS_DIR)/server.pid ]; then \
		PID=$$(cat $(RESULTS_DIR)/server.pid); \
		if ps -p $$PID > /dev/null 2>&1; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Server is running on process $(ORANGE)$$PID$(RESET)."; \
		fi; \
	fi

stop_server:
	@if [ -f $(RESULTS_DIR)/server.pid ]; then \
		PID=$$(cat $(RESULTS_DIR)/server.pid); \
		if ps -p $$PID > /dev/null 2>&1; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Server stopped on process $(ORANGE)$$PID$(RESET)."; \
			kill -9 $$PID; \
		fi; \
		rm -f $(RESULTS_DIR)/server.pid; \
	fi

tester: $(SERVER) $(CLIENT)

	@if [ ! -f "$(TEST_FILE)" ]; then \
		echo "$(ORANGE)$(PREFIX)$(RESET) File $(RED)$(TEST_FILE)$(RESET) is missing!"; \
		exit 1; \
	fi
	@if [ -f "$(RESULTS_DIR)/server.pid" ]; then \
		PID=$$(cat $(RESULTS_DIR)/server.pid); \
		if ps -p $$PID > /dev/null 2>&1; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Server is already running on process $(ORANGE)$$PID$(RESET)."; \
			$(MAKE) stop_server --silent; \
			$(MAKE) start_server --silent; \
		fi; \
	else \
		$(MAKE) start_server --silent; \
	fi
	@sleep 1
	@echo "$(ORANGE)$(PREFIX)$(RESET) Running tests from $(ORANGE)$(TEST_FILE)$(RESET)..."
	@awk '{print NR, length($$0), $$0}' $(TEST_FILE) | while read -r test_id test_length test_msg; do \
		SERVER_PID=$$(cat $(RESULTS_DIR)/server.pid); \
		echo "$(ORANGE)$(PREFIX)$(RESET) Test ID: $$test_id | Length: $$test_length"; \
		echo "$(GREY)$$test_msg"; \
		./$(CLIENT) $$SERVER_PID "$$test_msg"; \
		sleep 2; \
	done
	@sleep 2
	@sync
	@echo "$(ORANGE)$(PREFIX)$(RESET) Comparing diferences between $(ORANGE)test_cases.txt$(RESET) and $(ORANGE)server.out$(RESET)..."
	@tail -n +2 $(RESULTS_DIR)/server.out | diff -u $(TEST_FILE) - > $(RESULTS_DIR)/diff.log; \
	if [ $$? -eq 0 ]; then \
		echo "$(ORANGE)$(PREFIX)$(RESET) All Tests $(GREEN)PASSED$(RESET) congratulations!"; \
	else \
		echo "$(ORANGE)$(PREFIX)$(RESET) Some tests $(RED)FAILED!$(RESET). For more information consult $(ORANGE)$(RESULTS_DIR)/diff.log"; \
	fi; \
	$(MAKE) stop_server --silent

clean:
	@rm -rf $(OBJ_DIR) $(RESULTS_DIR)
	@rm -f $(SERVER) $(CLIENT)
	@echo "$(ORANGE)$(PREFIX)$(RESET) All executables and objects were cleaned $(GREEN)successfully$(RESET)."

fclean: clean stop_server
	@rm -rf $(LIBFT_DIR)
	@echo "$(ORANGE)$(PREFIX)$(RESET) Libft was cleaned $(GREEN)successfully$(RESET)."

re: fclean all

# Colors
PREFIX	:= $(shell tput bold)[MiniTalk]
BOLD 	:= $(shell tput bold)
GREEN	:= $(shell tput setaf 2)
RED  	:= $(shell tput setaf 1)
YELLOW	:= $(shell tput setaf 3)
RESET	:= $(shell tput sgr0)
GREY	:= $(shell tput setaf 8)
ORANGE	:= $(shell tput setaf 214)

.PHONY: all clean fclean re tester start_server stop_server valgrind_test
