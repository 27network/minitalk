# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 21:19:50 by kiroussa          #+#    #+#              #
#    Updated: 2023/11/21 17:40:08 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_SRC		= libft
LIBFT			= $(LIBFT_SRC)/build/output/libft.a

NAME			= minitalk

INCLUDES		= ./include
SRC_FOLDER		= src

CLIENT_SRC		= main.c
SERVER_SRC		= main.c \
				  buffer.c

COMMON_SRC		= rle/rle.c \
				  compress.c

BONUS_CLIENT_SRC:= $(CLIENT_SRC:.c=_bonus.c)
BONUS_SERVER_SRC:= $(SERVER_SRC:.c=_bonus.c)

CLIENT_SRC		:= $(addprefix $(SRC_FOLDER)/client/, $(CLIENT_SRC))
CLIENT_OBJ		= $(CLIENT_SRC:.c=.o)
SERVER_SRC		:= $(addprefix $(SRC_FOLDER)/server/, $(SERVER_SRC))
SERVER_OBJ		= $(SERVER_SRC:.c=.o)

COMMON_SRC		:= $(addprefix $(SRC_FOLDER)/common/, $(COMMON_SRC))
COMMON_OBJ		= $(COMMON_SRC:.c=.o)

BONUS_CLIENT_SRC:= $(addprefix $(SRC_FOLDER)_bonus/client/, $(BONUS_CLIENT_SRC))
BONUS_CLIENT_OBJ= $(BONUS_CLIENT_SRC:.c=.o)
BONUS_SERVER_SRC:= $(addprefix $(SRC_FOLDER)_bonus/server/, $(BONUS_SERVER_SRC))
BONUS_SERVER_OBJ= $(BONUS_SERVER_SRC:.c=.o)

CLIENT_OBJ		+= $(COMMON_OBJ)
SERVER_OBJ		+= $(COMMON_OBJ)
BONUS_CLIENT_OBJ+= $(COMMON_OBJ)
BONUS_SERVER_OBJ+= $(COMMON_OBJ)

CC				= clang
CFLAGS			= -Wall -Wextra -Werror -g3
COPTS			= -I $(INCLUDES) -I $(LIBFT_SRC)/include

all:			$(NAME)

$(NAME):		$(LIBFT) server client

bonus:			$(LIBFT) server_bonus client_bonus

client: 		$(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(CLIENT_OBJ) -o client $(LIBFT)

server: 		$(SERVER_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(SERVER_OBJ) -o server $(LIBFT)

client_bonus: 	$(BONUS_CLIENT_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(BONUS_CLIENT_OBJ) -o client_bonus $(LIBFT)

server_bonus: 	$(BONUS_SERVER_OBJ)
	$(CC) $(CFLAGS) $(COPTS) $(BONUS_SERVER_OBJ) -o server_bonus $(LIBFT)

$(LIBFT): 
	make -C $(LIBFT_SRC) -j$(shell nproc) CFLAGS="$(CFLAGS)"

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
