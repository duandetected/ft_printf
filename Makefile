
NAME = libftprintf.a

SRC =   ft_printf.c \
        functions.c \
        output_functions.c

OBJ = $(SRC:.c=.o)

LIBOBJ = libft/*.o

HEAD = -I ft_printf.h

CFLAGS = -c -Wall -Wextra -Werror

LIBINC = -I libft/libft.h -L./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	ar rc $(NAME) $(OBJ) $(LIBOBJ)
	ranlib $(NAME)

%.o: %.c
	gcc $(HEAD) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all