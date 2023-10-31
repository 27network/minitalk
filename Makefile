# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 21:19:50 by kiroussa          #+#    #+#              #
#    Updated: 2023/10/25 18:58:07 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT			= libft.a
LIBFT_SRC		= libft

NAME			= minitalk

INCLUDES		= ./

CLIENT_SRC		= client.c
SERVER_SRC		= server.c
CLIENT_OBJ		= $(CLIENT_SRC:.c=.o)
SERVER_OBJ		= $(SERVER_SRC:.c=.o)

BONUS_CLIENT	= client_bonus.c
BONUS_SERVER	= server_bonus.c
BONUS_CLIENT_OBJ= $(BONUS_CLIENT:.c=.o)
BONUS_SERVER_OBJ= $(BONUS_SERVER:.c=.o)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
COPTS			= -fPIC -I $(INCLUDES) -I $(LIBFT_SRC)/include

all:			$(NAME)

$(NAME):		$(LIBFT) server client

bonus:			$(LIBFT) server_bonus client_bonus

client: 		$(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(CLIENT_OBJ) -o client $(LIBFT_SRC)/$(LIBFT)

server: 		$(SERVER_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(SERVER_OBJ) -o server $(LIBFT_SRC)/$(LIBFT)

client_bonus: 	$(BONUS_CLIENT_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(BONUS_CLIENT_OBJ) -o client_bonus $(LIBFT_SRC)/$(LIBFT)

server_bonus: 	$(BONUS_SERVER_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(BONUS_SERVER_OBJ) -o server_bonus $(LIBFT_SRC)/$(LIBFT)

$(LIBFT): 
	make -C $(LIBFT_SRC)

%.o:			%.c
	$(CC) $(CFLAGS) $(COPTS) -c $< -o $@

clean:
	make -C $(LIBFT_SRC) clean
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) 
	rm -f $(BONUS_CLIENT_OBJ) $(BONUS_SERVER_OBJ)

fclean:			clean
	make -C $(LIBFT_SRC) fclean
	rm -f client server
	rm -f client_bonus server_bonus

re:				fclean all

.PHONY:			all bonus $(NAME) clean fclean re
