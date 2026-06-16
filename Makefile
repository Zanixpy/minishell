CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =  src/main.c \
		src/parser/parser.c \
		src/parser/parser_set_cmd.c \
		src/parser/parser_set_cmd_utils.c \
		src/parser/parser_error.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils.c \
		src/shell_cmd/shell_cmd_destroy.c \
		src/shell_cmd/shell_cmd_init.c \
		src/utils/memory_utils.c \
		src/utils/utils.c \
		src/utils/bool_utils.c \
		src/utils/extract_utils.c \
		src/utils/fd_utils.c \
		src/expander/expand.c \
		src/execute/execute.c \
		src/execute/execution_utils.c \
		src/execute/exec.c \
		src/execute/execute_pipe.c \
		src/execute/execute_utils_2.c \
		src/execute/execute_external.c \
		src/execute/execute_cmd.c \
		src/execute/heredoc.c \
		src/execute/signals.c \
		src/execute/execute_error.c \
		src/built_in_cmds/cd.c \
		src/built_in_cmds/echo.c \
		src/built_in_cmds/env.c \
		src/built_in_cmds/exit.c \
		src/built_in_cmds/export.c \
		src/built_in_cmds/pwd.c \
		src/built_in_cmds/unset.c \
		src/built_in_cmds/built_in_utils.c \
		src/built_in_cmds/built_in_error.c \
		
LIBFT_DIR = external/libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADERS = include

OBJS    = $(SRCS:.c=.o)

INCLUDES = -I$(HEADERS) -I$(LIBFT_DIR)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline  $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all re fclean clean