# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 17:49:42 by skiam             #+#    #+#              #
#    Updated: 2024/07/25 18:49:19 by ahayon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	src/main.c\
				src/parsing/parsing.c\
				src/parsing/parsing_utils.c\
				src/parsing/parsing_utils_bis.c\
				src/parsing/parsing_map.c\
				src/parsing/get_texture.c\
				src/parsing/ft_split_cub.c\
				src/execution.c\
				src/ray_casting.c\
				src/draw.c\
				src/player_movement.c\
				src/handle_keys.c\
				src/handle_player.c\
				src/minimap_bonus.c\
				src/mouse_interaction_bonus.c\
				src/animated_sprites_bonus.c\
				src/door_bonus.c\
				src/render_window.c\
				src/execution_utils.c\
				src/clean.c\
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
	$(CC) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(FT_PRINTF) $(LIBFT) -lm

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