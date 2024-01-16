NAME = minitalk

NAME_CLIENT = client

NAME_SERVER = server

SOURCE_CLIENT = client.c

SOURCE_SERVER = server.c

OBJECTS_CLIENT = $(SOURCE_CLIENT:.c=.o)

OBJECTS_SERVER = $(SOURCE_SERVER:.c=.o)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -g -Wall -Werror -Wextra -fsanitize=address

RMFLAGS = -rf

all : $(NAME)

$(NAME) : $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT) : $(OBJECTS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_SERVER) : $(OBJECTS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :  
	make -C $(LIBFT_DIR)

clean :
	rm $(RMFLAGS) $(OBJECTS_CLIENT) $(OBJECTS_SERVER)
	make -C $(LIBFT_DIR) clean 

fclean : clean
	rm $(RMFLAGS) $(NAME_CLIENT) $(NAME_SERVER)
	make -C $(LIBFT_DIR) fclean

re : fclean all

PHONY = all clean fclean re

