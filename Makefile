CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =  src/main.c \
		src/parser/lexer.c \
		src/free/free.c

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