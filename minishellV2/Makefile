# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: memahote <memahote@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 20:20:26 by memahote          #+#    #+#              #
#    Updated: 2024/02/14 22:35:25 by memahote         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


NAME = minishell

# ----- FOLDERS ----- #

INC_DIR		= 	includes/
LIB_DIR		= 	libft/
SRC_DIR		=	srcs/
PARSING_DIR	=	parsing/
BUILTINS_DIR = 	builtins/
EXEC_DIR	= 	execution/
ENV_DIR		=	environment/
SIGNAL_DIR	=	signals/
UTILS_DIR	=	utils/
OBJ_DIR		= 	obj/

# ----- FILES ----- #

LIST_SRC		= 	main.c 

PARSING_SRC		= parser.c tokenizer.c tokenizer_utils.c syntax_checker.c \
					expander.c last_check.c last_check_utils.c

ENV_SRC			= environment_lst.c

BUILTINS_SRC	= cd.c echo.c env.c exit.c export.c pwd.c unset.c

EXEC_SRC		= executer.c redir_handler.c heredoc_handler.c pipes_handler.c

SIGNAL_SRC		= signal.c handlers.c

UTILS_SRC		= main_utils.c parsing_utils.c execution_utils.c free_utils.c \
					builtins_utils.c builtins_utils_2.c 


# ----- SHORTCUTS ----- #

INC			= $(addprefix $(INC_DIR), minishell.h)
LIBFT       = $(addprefix $(LIB_DIR), libft.a)
ENV			= $(addprefix $(ENV_DIR), $(ENV_SRC))
PARSING		= $(addprefix $(PARSING_DIR), $(PARSING_SRC))
BUILTINS	= $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC))
EXEC		= $(addprefix $(EXEC_DIR), $(EXEC_SRC))
SIGNAL		= $(addprefix $(SIGNAL_DIR), $(SIGNAL_SRC))
UTILS		= $(addprefix $(UTILS_DIR), $(UTILS_SRC))
SRC			= $(addprefix $(SRC_DIR), $(LIST_SRC) $(ENV) $(PARSING) \
			 $(BUILTINS) $(EXEC) $(SIGNAL) $(UTILS))
OBJ         = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))
DEP			= $(patsubst %.c, $(OBJ_DIR)%.d, $(SRC))

# ----- Compiler -----

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g3
LFLAGS 		= -lreadline
DEP_FLAGS	= -MMD -MP
MKDIR		= mkdir -p
RM 			= rm -rf
MAKE 		= make -C

# ----------------------------------- RULES ------------------------------------

all:	$(NAME)


$(NAME):	$(LIBFT) $(OBJ)
			$(CC) $(FLAG) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft -lreadline


$(LIBFT):	FORCE
		$(MAKE) $(LIB_DIR)

-include $(DEP)

$(OBJ_DIR)%.o: %.c 
	$(MKDIR) $(@D)
	$(CC) $(FLAG) $(DEP_FLAGS) -I $(INC_DIR) -c $< -o $@

clean:		
			$(MAKE) $(LIB_DIR) clean
			${RM} $(OBJ_DIR)

fclean:		clean
			$(MAKE) $(LIB_DIR) fclean
			${RM} ${NAME}
			${RM} ${NAME_BONUS}

re:			fclean all

FORCE:

leaks: 		all
			touch valgrind.txt
			rm valgrind.txt
			echo "{" > valgrind_ignore_leaks.txt
			echo "leak readline" >> valgrind_ignore_leaks.txt
			echo "Memcheck:Leak" >> valgrind_ignore_leaks.txt
			echo "..." >> valgrind_ignore_leaks.txt
			echo "fun:readline" >> valgrind_ignore_leaks.txt
			echo "}" >> valgrind_ignore_leaks.txt
			echo "{" >> valgrind_ignore_leaks.txt
			echo "leak add_history" >> valgrind_ignore_leaks.txt
			echo "Memcheck:Leak" >> valgrind_ignore_leaks.txt
			echo "..." >> valgrind_ignore_leaks.txt
			echo "fun:add_history" >> valgrind_ignore_leaks.txt
			echo "}" >> valgrind_ignore_leaks.txt
			valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
					--show-leak-kinds=all --track-fds=yes \
					--show-mismatched-frees=yes --read-var-info=yes \
					--log-file=valgrind.txt -s ./${NAME}

.PHONY:         all clean fclean FORCE re 
