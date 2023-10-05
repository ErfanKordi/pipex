NAME	= pipex
SRCS	= pipex.c
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g
LIBFTDIR = My_C_Library
LIBFT	= $(LIBFTDIR)/libft.a

all:	$(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -L$(LIBFTDIR) -lft $(SRCS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

fclean:	clean
	make fclean -C $(LIBFTDIR)
	$(RM) $(NAME)

re:		fclean $(NAME)


.PHONY:	all clean fclean re bonus
