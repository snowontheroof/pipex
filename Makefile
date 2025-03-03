NAME = pipex
CC = cc
CFLAGS = -Wextra -Wall -Werror
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

HEADERS = -I$(LIBFTDIR)
SRC = main.c open_files.c parsing.c parsing_utils.c processes.c utils.c exit_program.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	@make all -C $(LIBFTDIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(HEADERS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIBFTDIR)

fclean: clean
	@rm -rf $(NAME) $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re
