CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =  src/main.c \
		src/parser/parser.c \
		src/parser/parser_utils.c \
		src/parser/parser_set_cmd.c \
		src/lexer/lexer.c \
		src/cmd/cmd_destroy.c \
		src/cmd/cmd_init.c \
		src/utils/memory_utils.c \
		src/utils/utils.c \
		src/utils/bool_utils.c \
		src/utils/extract_utils.c \
		src/expander/expand.c


LIBFT_DIR = external/libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADERS = include

OBJS    = $(SRCS:.c=.o)

INCLUDES = -I$(HEADERS) -I$(LIBFT_DIR)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(LIBFT)

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