NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRC = 	tokenizer/utils.c \
		tokenizer/lexer.c \
		tokenizer/outils.c \
		tokenizer/lexer_utils.c \
		tokenizer/token_utils.c \
		tokenizer/expand.c \
		tokenizer/token.c \
		garbage_collector/garbage.c \
		syntax/syntax_error.c  \
		signals/ft_signals.c \
		signals/ft_signals2.c \
		tree_parser/tree_helper.c \
		tree_parser/build_tree.c \
		tree_parser/sorting_things.c \
		builtins/builtins_utils.c \
		builtins/ft_builtins.c \
		builtins/ft_env.c \
		builtins/ft_export.c \
		builtins/ft_export_utils.c \
		builtins/builtins_utils2.c \
		builtins/builtins_utils3.c \
		builtins/cd_utils.c \
		execution/executer_utils.c \
		execution/heredoc.c \
		execution/executer_utils2.c \
		execution/executer_outils.c \
		execution/executer_helpers.c \
		execution/executer_help.c \
		execution/executer.c \
		space.c \
		mossa3id.c \
		main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.SECONDARY: