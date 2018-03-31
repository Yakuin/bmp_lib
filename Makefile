NAME =	bmp_gen

SRC =	bmp_gen.c

OBJ =	$(SRC:.c=.o)

FLG = 	-Wextra -Wall -Werror

CFLAGS = -g


$(NAME): $(OBJ)
	@echo "Compiling..."
	@gcc -c $(FLG) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Done !"

debug:
	@echo "Compiling (DEBUG SYMBOLS)..."
	@gcc -g -c $(FLG) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Done !"

clean:
	@echo "Deleting object files..."
	@rm -f $(OBJ)
	@echo "Done !"

fclean: clean
	@echo "Deleting executable..."
	@rm -f $(NAME)
	@echo "Done !"

re: fclean all