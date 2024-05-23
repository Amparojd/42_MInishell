# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 20:28:42 by mlezcano          #+#    #+#              #
#    Updated: 2024/04/11 18:09:55 by mlezcano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#compiler
CC			=	gcc
CFLAGS		=	-Werror -Wextra -Wall
ECHO		=	echo
RM			=	rm -rf -r

#output
NAME		=	minishell

#directories
LIBFT_PATH 	=	libft/
SRC_DIR 	=	src/
OBJ_DIR		=	obj/
INC_PATH 	=	inc/

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

#source files
SRC			=	minishell.c \
				signals/signals_interact.c \
				signals/signals_no_interact.c \
				lexer/lexer_main.c \
				lexer/quot_stx_errors.c \
				lexer/chunk_reader.c \
				lexer/manage_token_list.c \
				lexer/stx_errors.c \
				expander/expander_main.c \
				expander/scan.c \
				expander/process_quotes.c \
				expander/quote_eraser.c \
				expander/process_variables.c \
				expander/extract_var_name.c \
				expander/extract_var_value.c \
				expander/get_variable_str.c  \
				expander/heredoc_expander.c \
				parser/parser_main.c \
				parser/cmd_container_creat.c \
				parser/parser_words.c \
				parser/parser_input.c \
				parser/parser_trunc.c \
				parser/heredoc.c \
				parser/parser_append.c \
				parser/parser_pipe.c \
				parser/parser_utils/cmd_arg_filler.c \
				parser/parser_utils/cmd_arg_filler_utils.c \
				parser/parser_utils/heredoc_utils.c \
				parser/parser_utils/parser_general_utils.c \
				parser/parser_utils/cmd_list_cleaner.c \
				env/env.c env/env_built.c \
				env/env_handlers.c \
				env/mslvl.c \
				builtins/export_builtin.c \
				builtins/unset_builtin.c \
				builtins/cd_builtin.c \
				builtins/env_builtin.c \
				builtins/pwd_builtin.c \
				builtins/echo_builtin.c \
				builtins/echo_builtin2.c \
				builtins/exit_builtin.c \
				executer/execute.c \
				executer/command_exec.c \
				executer/execute_utils.c \
				executer/parse_path.c \
				redirections/pipe_controls.c \
				redirections/io_controls.c \
				utils/exit.c \
				utils/errors.c \
				utils/init_data.c \
				utils/free_data.c  
							
SRCS		=	$(addprefix $(SRC_DIR), $(SRC))
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ))
INC			=	-I $(INC_PATH) -I $(LIBFT_PATH)
LIBFT		=	libft/libft.a

#valgrind
VALGRIND        = valgrind
VALGRIND_OPT    += --suppressions=readline.supp
VALGRIND_OPT    += --trace-children=yes
VALGRIND_OPT    += --track-origins=yes
VALGRIND_OPT    += --track-fds=yes
VALGRIND_OPT    += --leak-check=full
VALGRIND_OPT    += --show-leak-kinds=all

#readlene flags
LDFLAGS		=	-L/Users/$(USER)/.brew/opt/readline/lib 
CPPFLAGS	=	-I/Users/$(USER)/.brew/opt/readline/include 

#make rules	
TOTAL_SRCS  =	$(words $(SRC))
COMPILE_CNT =	0

all: 			$(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR) 
				@mkdir -p $(addprefix $(OBJ_DIR), $(dir $(SRC)))

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
				@$(eval COMPILE_CNT=$(shell echo $$(($(COMPILE_CNT)+1))))
				@printf "$(GRAY)[minishell]$(DEF_COLOR) $(DEF_COLOR)$(GREEN) [%s] [%s]\r" \
					"$(shell echo $$((($(COMPILE_CNT)*100)/$(TOTAL_SRCS))))%" \
					"$(shell seq -s '#' $(shell echo $$((($(COMPILE_CNT)*20)/$(TOTAL_SRCS)))) | tr -d '[:digit:]')"

$(NAME): $(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(LDFLAGS) $(CPPFLAGS) -lreadline
				@$(ECHO) "$(GREEN)[minishell]$(DEF_COLOR)"
				@$(ECHO) "$$ANSELMO"
				@$(ECHO) "$(BLUE)------------------------------------------------------$(DEF_COLOR)" 
				@$(ECHO) "$(RED)AnShellmo V 1.0. Copyright© 2024. All rights reserved.$(DEF_COLOR)" 

valgrind:		$(OBJ_DIR) $(LIBFT) $(NAME)
				@$(VALGRIND)	$(VALGRIND_OPT)	./$(NAME)
			
$(LIBFT):
				@make -C $(LIBFT_PATH)
    
clean:
				@make clean -C $(LIBFT_PATH)
				@$(RM) $(OBJ_DIR) 
				@$(ECHO) "$(BLUE)[AnShellmo]:\tobject files$(DEF_COLOR)$(CYAN)  => Clean!$(DEF_COLOR)"
		
fclean: 	
				@make -C libft fclean 
				@$(RM) $(NAME)
				@$(RM) $(OBJ_DIR)
				@$(ECHO) "$(BLUE)[AnShellmo]:\tobject files$(DEF_COLOR)$(CYAN)  => Clean!$(DEF_COLOR)"
				@$(ECHO) "$(BLUE)[AnShellmo]:\texec. files$(DEF_COLOR)$(CYAN)   => Clean!$(DEF_COLOR)"

re: 			fclean all
				@$(ECHO) "$(BLUE)    (Everything cleaned and rebuilt for Anshellmo!)$(DEF_COLOR)"

#banner
anselmo:
				@echo "$$ANSELMO"

define ANSELMO
     _          ____  _          _ _
    / \   _ __ / ___|| |__   ___| | |_ __ ___   ___ 
   / _ \ | '_  \___ \| '_ \ / _ \ | | '_ ` _ \ / _ \ 
  / ___ \| | | |___) | | | |  __/ | | | | | | | (_) | 
 /_/   \_\_| |_|____/|_| |_|\___|_|_|_| |_| |_|\___/ 
endef

export ANSELMO
				
#phony rules
.PHONY:			all re clean fclean anselmo valgrind