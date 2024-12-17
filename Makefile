# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antauber <antauber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 08:19:19 by antauber          #+#    #+#              #
#    Updated: 2024/12/17 09:54:37 by antauber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

## ########################################################################## ##
#   INGREDIENTS																  ##
## ########################################################################## ##
# INC			header file locations
#
# SRCS_DIR		source directory
# SRCS			source files
#
# BUILD_DIR		build directory
# OBJS			object files
# DEPS			dependencies files

INC			:=	includes

SRCS_DIR	:=	srcs
SRCS		:=	pipex.c	utils.c	parsing.c processes.c
SRCS		:=	$(SRCS:%=$(SRCS_DIR)/%)


BUILD_DIR	:=	.build
OBJS		:=	$(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:=	$(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.d)

LIB_DIR		=	libft
LIBFT		=	libft/libft.a

## ########################################################################## ##
#   TOOLS																	  ##
## ########################################################################## ##
# CC			compiler
# CFLAGS		compiler flags
#
# RM			force recusfly remove
# DIR_UP		duplicate directory tree

MFLAG		=	--no-print-directory
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -MMD -MP

RM			:=	rm -rf
DIR_DUP		=	mkdir -p $(@D)

## ########################################################################## ##
#   FRONTEND																  ##
## ########################################################################## ##

AQUA	= \e[0;36m
YELLOW	= \e[1;33m
GREEN	= \e[1;32m
RED		= \e[1;31m
RESET 	= \e[0m

## ########################################################################## ##
#   RECIPES																	  ##
## ########################################################################## ##
# all			default goal
# $(NAME)		link .o -> archive file
# %.o			compilation .c -> .o
# clean			remove .o && directory tree
# fclean		remove .o && libft.a
# re			fclean && default goal


all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(AQUA)Compiling $(NAME)..................\n$(RESET)"
	@$(CC) $(CFLAGS) $^ -L$(LIB_DIR) -lft -o $@
	@echo "	$(GREEN)-----	$(NAME) successfully created	-----$(RESET)	\n"

$(LIBFT):
	@echo "$(AQUA)Compiling $(LIB_DIR)..................\n$(RESET)"
	@$(MAKE) $(MFLAG) -C $(LIB_DIR)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -I$(INC) -I$(LIB_DIR) -I$(MLX_DIR) -O3 -o $@ -c $<

clean:
	@$(MAKE) $(MFLAG) -C $(LIB_DIR) clean
	@$(RM) $(BUILD_DIR)
	@echo "	$(RED)-----	$(BUILD_DIR) successfully removed	-----$(RESET)	\n"

fclean: clean
	@$(MAKE) $(MFLAG) -C $(LIB_DIR) fclean
	@$(RM) $(NAME)
	@echo "	$(RED)-----	$(NAME) successfully removed	-----$(RESET)	\n"

re: fclean all

.PHONY: all bonus clean fclean re

-include $(DEPS)
