NAME =	bmp_gen

SRC =	bmp_gen.c

OBJ =	$(SRC:.c=.o)

FLG = -Wextra -Wall -Werror

CFLAGS = -g

$(NAME): $(OBJ)
	@echo "Compiling BMP Generator..."
	@gcc -g -c -Ofast $(FLG) $(SRC)
	@gcc -g -o $(NAME) $(OBJ)
	@echo "Done !"

all: $(NAME)

clean:
	@echo "Deleting object files..."
	@rm -f $(OBJ)
	@echo "Done !"

fclean: clean
	@echo "Deleting executable..."
	@rm -f $(NAME)
	@echo "Done !"

re: fclean all

.PHONY: all clean fclean re