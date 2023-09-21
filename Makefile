NAME		=	pipex
SRC 		= $(wildcard *.c)
OBJ			= $(SRC:.c=.o)
FLAGS 		= -Wall -Wextra -Werror #-g3 -fsanitize=address
RM 			= rm -f
CC 			= cc

%.o : %.c Makefile
	$(CC) $(FLAGS) -c $< -o $@ 

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean : 
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re