# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbecht <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 12:36:18 by fbecht            #+#    #+#              #
#    Updated: 2023/06/13 12:36:21 by fbecht           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= philo

# Compiler
CC			= cc
CFLAGS		= -Werror -Wextra -Wall
SANIFLAG	= -fsanitize=thread -g

# Includes & Linking
INC			= -I ./includes
LINK		= -lpthread

# Sources
SRC_PATH	= srcs/
SRC_FILE	= check_input.c exit_philo.c init.c main.c output.c utils.c
SRC			= $(addprefix $(SRC_PATH), $(SRC_FILE))

# Objects
OBJ_PATH	= obj/
OBJ_FILE	= $(SRC_FILE:.c=.o)
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_FILE))

# RULES

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling philo..."
	@-$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LINK)
	@echo "\n\t\033[33;1;3mphilo ready\033[0m\n"

SANITIZE: $(OBJ)
	@echo "Compiling philo with fsanitize flag..."
	@-$(CC) $(CFLAGS) $(SANIFLAG) -o $(NAME) $(OBJ) $(INC) $(LINK)
	@echo "\n\t\033[33;1;3mphilo ready (with fsanitize)\033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@echo "Generating obj folders"
	@mkdir $(OBJ_PATH)

clean:
	@echo "Removing object files..."
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "Removing philo..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
