NAME	= pipex
SRCS	= pipex.c utils.c
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
LIBFTDIR = My_C_Library
LIBFT	= $(LIBFTDIR)/libft.a

OBJ := $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -L$(LIBFTDIR) -lft $(SRCS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFTDIR)
	$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re bonus
