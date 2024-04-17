################################## VARIABLES ###################################

NAME			= minishell

# ----- FOLDERS ----- #

INC_DIR		= 	includes/
LIB_DIR		= 	libft/
SRC_DIR		=	srcs/
LEXER_DIR	=	lexer/
PARSER_DIR	=	parser/
BUILTINS_DIR = builtins/
EXEC_DIR	= exec/
OBJ_DIR		= 	obj/


# ----- FILES ----- #

LIST_SRC	= 	main.c 

LEXER_SRC	=	lexer.c lexer_utils.c list_minishell.c check_syntax.c \
				check_quote_input.c tokenizer.c

PARSER_SRC	=	parser.c redir_list.c print_fc.c parse_token_utils.c \
				parser_utils.c

BUILTINS_SRC = ft_pwd.c ft_echo.c ft_env.c new_export.c ft_unset.c \
				ft_cd.c ft_export_nothing.c env_utils.c

EXEC_SRC	= exec.c get_path.c exec_cmd.c do_redir.c

# ----- SHORTCUTS ----- #

INC			= $(addprefix $(INC_DIR), minishell.h)
LIBFT       = $(addprefix $(LIB_DIR), libft.a)
LEXER		= $(addprefix $(LEXER_DIR), $(LEXER_SRC))
PARSER		= $(addprefix $(PARSER_DIR), $(PARSER_SRC))
BUILTINS	= $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC))
EXEC		= $(addprefix $(EXEC_DIR), $(EXEC_SRC))
SRC			= $(addprefix $(SRC_DIR), $(LIST_SRC) $(LEXER) $(PARSER) $(BUILTINS) $(EXEC))
OBJ         = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))
DEP			= $(patsubst %.c, $(OBJ_DIR)%.d, $(SRC))

# ----- Compiler -----

CC				= cc
RM				= rm -rf
FLAG			= -Wall -Wextra -Werror -g3 
DEP_FLAGS		= -MMD -MP
MKDIR           = mkdir -p
MAKE            = make -C

################################## RULES ###################################

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
