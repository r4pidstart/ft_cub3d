# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2023/01/31 17:55:28 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -g3 -ggdb -fsanitize=address

LIBFT = ft_mylibft/libft.a
LIBFT_SRCS = ft_mylibft

MLX = libmlx.dylib
MLX_SRCS = mlx

SRCS = raycasting/ft_raycasting.c raycasting/ft_raycasting_utils.c raycasting/ft_raycasting_calc.c \
	parse/ft_check_lines.c parse/ft_dfs_check.c parse/ft_free.c parse/ft_get_something.c parse/ft_make_map.c \
	parse/ft_maps.c parse/ft_node.c parse/ft_parse.c parse/ft_set_map.c parse/ft_string.c \
	ft_main.c ft_keyhook.c
SRCS_FOLDER = 

uname := $(shell uname -p)
ifeq ($(uname), arm)
	# __LDFLAGS=""
	# __CPPFLAGS=""
else
	# __LDFLAGS=""
	# __CPPFLAGS=""
endif

BNAME = cub3d_bonus

ifdef BONUS
 	NAME = cub3D_bonus
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(addprefix $(SRCS_FOLDER), $(SRCS:.c=.o))
	cc $(CFLAGS) \
	-o ./$(NAME) \
	$(addprefix $(SRCS_FOLDER), $(SRCS)) \
	-Imlx -L. -lmlx -framework OpenGL -framework Appkit \
	-L$(LIBFT_SRCS) -lft

$(LIBFT):
	make -C $(LIBFT_SRCS) all -j 8

$(MLX):
	make all -C $(MLX_SRCS)
	mv mlx/libmlx.dylib ./libmlx.dylib

%.o: %.c
	cc $(CFLAGS) -c $^ -o $@

bonus:
	$(MAKE) BONUS=1

clean:
	rm -rf */*.o
	rm -rf *.o
	make clean -C $(LIBFT_SRCS)
	make clean -C $(MLX_SRCS)
	
fclean: clean
	rm -rf $(NAME) $(BNAME)
	rm -rf $(MLX)
	make fclean -C $(LIBFT_SRCS)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: bonus all clean fclean re
