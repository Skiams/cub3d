# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skiam <skiam@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 17:49:42 by skiam             #+#    #+#              #
#    Updated: 2024/07/16 21:38:29 by skiam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c\
				parsing.c\
				parsing_utils.c\
				parsing_utils_bis.c\
				parsing_map.c\
				ft_split_cub.c\
#BONUS_SRCS
				

OBJS		= ${SRCS:.c=.o}
##BONUS_OBJS	= ${BONUS_SRCS:.c=.o}

NAME		= cub3d
#NAME_BONUS	= 

CC			= cc -g3 -Wall -Wextra -Werror

INCLUDES = -I. -I/usr/include -Imlx -Ilibs/ft_printf -Ilibs/libft 

LIBFT = libs/libft/libft.a
FT_PRINTF = libs/ft_printf/libftprintf.a
MLX_LIB = mlx/libmlx_Linux.a
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

all: ${NAME}

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT) $(FT_PRINTF)
	$(CC) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(FT_PRINTF) $(LIBFT)

$(MLX_LIB):
	make -C mlx

$(FT_PRINTF):
	make -C libs/ft_printf

$(LIBFT):
	make -C libs/libft

%.o: %.c cub3d.h
	$(CC) -o $@ -c $< $(INCLUDES)

	
clean:
	rm -f ${OBJS}
	make -C mlx clean
	make -C libs/libft clean
	make -C libs/ft_printf clean

fclean:		clean
	rm -f ${NAME}
	make -C mlx clean
	make -C libs/libft fclean
	make -C libs/ft_printf fclean

re:			fclean all

.PHONY:		all clean fclean re