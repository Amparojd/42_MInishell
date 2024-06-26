# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 17:33:48 by mlezcano          #+#    #+#              #
#    Updated: 2024/03/31 17:25:46 by mlezcano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SHELL		=	/bin/bash

#compiler

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I
RM			=	rm -f
AR			=	ar rcs
ECHO		=	echo -e

#directories

INCLUDE		=	inc/
SRC_DIR 	=	src/
OBJ_DIR		=	obj/

#output 

NAME		=	libft.a

#colors

DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

#src directories

LIBFT_DIR	=	libft/
GNL_DIR		=	gnl/
FTPRINTF_DIR	= ft_printf/

#src files

LIBFT		=	ft_bzero ft_isalnum ft_isalpha ft_isascii \
	   		  ft_isdigit ft_isprint ft_memcpy ft_memmove \
	  		  ft_memset ft_strlen ft_tolower ft_toupper \
	   		  ft_strlcpy ft_strlcat ft_strchr ft_strrchr \
	   		  ft_strncmp ft_memchr ft_memcmp ft_strnstr \
	   		  ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin \
	   		  ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
			  ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
			  ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus \
			  ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
			  ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus \
			  matrixdup free_arr ft_strcmp ft_ispace ft_strjoin_free ft_is_space

GNL			=	get_next_line get_next_line_utils

FTPRINTF	=	ft_printf ft_alpha ft_numeric

#src files combination 

SRC_FILES	= 	$(addprefix $(LIBFT_DIR),$(LIBFT)) \
				$(addprefix $(GNL_DIR),$(GNL)) \
				$(addprefix $(FTPRINTF_DIR),$(FTPRINTF))

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

#Cache flag 

OBJF		=	.cache_exists

TOTAL_SRCS  =	$(words $(SRC))
COMPILE_CNT =	0

#Target list

start:
			@make all

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@$(ECHO) "$(GREEN)[LIBFT]$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			@$(eval COMPILE_CNT=$(shell echo $$(($(COMPILE_CNT)+1))))
			@printf "$(GRAY)[LIBFT]    $(DEF_COLOR) $(DEF_COLOR)$(GREEN) [%s] [%s]\r" \
				"$(shell echo $$((($(COMPILE_CNT)*100)/$(TOTAL_SRCS))))%" \
				"$(shell seq -s '#' $(shell echo $$((($(COMPILE_CNT)*20)/$(TOTAL_SRCS)))) | tr -d '[:digit:]')"

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(LIBFT_DIR)
			@mkdir -p $(OBJ_DIR)$(GNL_DIR)
			@mkdir -p $(OBJ_DIR)$(FTPRINTF_DIR)
			@touch $(OBJF)

clean:
			@$(RM) -r $(OBJ_DIR)
			@$(RM) $(OBJF)
			@echo -e -n "$(BLUE)[LIBFT]:\tobject files$(DEF_COLOR)$(CYAN)  => Clean!$(DEF_COLOR)\n"

fclean:		clean
			@$(RM) $(NAME)
			@echo -e -n "$(BLUE)[LIBFT]:\texec. files$(DEF_COLOR)$(CYAN)   => Clean!$(DEF_COLOR)\n"

re:			fclean all
			@echo -e -n "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)\n"

#phony rules

.PHONY:		all clean fclean re 
