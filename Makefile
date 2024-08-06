# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 17:49:42 by skiam             #+#    #+#              #
#    Updated: 2024/08/06 19:20:57 by ahayon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	mandatory/main.c\
				mandatory/parsing/parsing.c\
				mandatory/parsing/parsing_utils.c\
				mandatory/parsing/parsing_utils_bis.c\
				mandatory/parsing/parsing_map.c\
				mandatory/parsing/get_texture.c\
				mandatory/parsing/ft_split_cub.c\
				mandatory/execution.c\
				mandatory/ray_casting.c\
				mandatory/draw.c\
				mandatory/player_movement.c\
				mandatory/handle_keys.c\
				mandatory/handle_player.c\
				mandatory/render_window.c\
				mandatory/execution_utils.c\
				mandatory/clean.c\
				
BONUS_SRCS	=	bonus/main_bonus.c\
				bonus/parsing/parsing_bonus.c\
				bonus/parsing/parsing_utils_bonus.c\
				bonus/parsing/parsing_utils_bis_bonus.c\
				bonus/parsing/parsing_map_bonus.c\
				bonus/parsing/get_texture_bonus.c\
				bonus/parsing/ft_split_cub_bonus.c\
				bonus/execution_bonus.c\
				bonus/ray_casting_bonus.c\
				bonus/draw_bonus.c\
				bonus/player_movement_bonus.c\
				bonus/handle_keys_bonus.c\
				bonus/handle_player_bonus.c\
				bonus/minimap_bonus.c\
				bonus/mouse_interaction_bonus.c\
				bonus/animated_sprites_bonus.c\
				bonus/animated_sprites_bis_bonus.c\
				bonus/door_bonus.c\
				bonus/render_window_bonus.c\
				bonus/execution_utils_bonus.c\
				bonus/clean_bonus.c\
				

OBJS		= ${SRCS:.c=.o}
BONUS_OBJS	= ${BONUS_SRCS:.c=.o}

NAME		= cub3d
NAME_BONUS	= cub3d_bonus

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
%.o: %.c cub3d_bonus.h
	$(CC) -o $@ -c $< $(INCLUDES)

bonus: ${NAME_BONUS} 

${NAME_BONUS}: $(BONUS_OBJS) $(MLX_LIB) $(LIBFT) $(FT_PRINTF)
	$(CC) -o $(NAME_BONUS) $(BONUS_OBJS) $(MLX_FLAGS) $(FT_PRINTF) $(LIBFT) -lm
	
	
clean:
	rm -f ${OBJS} ${BONUS_OBJS}
	make -C mlx clean
	make -C libs/libft clean
	make -C libs/ft_printf clean

fclean:		clean
	rm -f ${NAME} ${NAME_BONUS}
	make -C mlx clean
	make -C libs/libft fclean
	make -C libs/ft_printf fclean

re:			fclean all

.PHONY:		all clean fclean re