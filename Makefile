# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 12:03:02 by jbrousse          #+#    #+#              #
#    Updated: 2024/03/11 12:37:58 by jbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################
##  COMPILE	  ##
################

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

#################
##   INCLUDE   ##
#################

INCLUDE_LIST	=	./includes/
INCLUDE			=	$(addprefix -I, $(INCLUDE_LIST))


#################
##   SOURCES   ##
#################

SRC_DIR				=	sources/

SRC_LIST			=
SRC					=	$(addprefix $(SRC_DIR), $(SRC_LIST))

##################
##   OBJ/NAME   ##
##################

NAME		=	philo

NORM_LOG	:=	norme_log

OBJ_DIR		=	objects/
OBJ_LIST	=	$(addprefix $(OBJ_DIR), $(SRC_LIST:.c=.o))

#################
##	 COLORS	   ##
#################

COLOR_RESET		=	\033[0m
COLOR_GREEN		=	\033[32m
COLOR_RED		=	\033[31m
COLOR_BLUE		=	\033[34m

#################
##    RULES    ##
#################



all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	@echo "$(COLOR_BLUE)Compile $<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_LIST)
	@echo "$(COLOR_BLUE)Compile $(NAME)$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJ_LIST) -o $(NAME)

clean:
	@echo "$(COLOR_RED)Delete objects$(COLOR_RESET)"
	@rm -rf $(OBJ_DIR) $(NORM_LOG)

fclean: clean
	@echo "$(COLOR_RED)Delete $(NAME)$(COLOR_RESET)"
	@rm -f $(NAME)

norme:
	@echo "$(COLOR_BLUE)Norminette...$(COLOR_RESET)"
	@norminette $(SRC) $(INCLUDES) > $(NORM_LOG) ; \
	if grep -q "Error" $(NORM_LOG); then \
		echo "$(COLOR_RED)Norme : KO!$(COLOR_RESET)"; \
	else \
		echo "$(COLOR_GREEN)Norme : OK!$(COLOR_RESET)"; \
	fi; \

re: fclean all

.PHONY: all clean fclean re norme