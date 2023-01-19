# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2023/01/20 06:14:30 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g3 -ggdb -fsanitize=address

LIBFT = ft_mylibft/libft.a
LIBFT_SRCS = ft_mylibft

MLX = cub3d/mlx/libmlx.dylib
MLX_SRCS = mlx

SRCS = raycasting/ft_raycasting.c ft_main.c
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
 	NAME = cub3d_bonus
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(addprefix $(SRCS_FOLDER), $(SRCS:.c=.o))
	cc $(CFLAGS) \
	-o ./$(NAME) \
	$(addprefix $(SRCS_FOLDER), $(SRCS)) \
	-Imlx -L$(MLX_SRCS) -lmlx -framework OpenGL -framework Appkit \
	-L$(LIBFT_SRCS) -lft

$(LIBFT):
	make -C $(LIBFT_SRCS) all

$(MLX):
	make all -C $(MLX_SRCS)

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
	make fclean -C $(LIBFT_SRCS)

re:
	make clean -C $(LIBFT_SRCS)
	make clean -C $(MLX_SRCS)
	$(MAKE) fclean
	$(MAKE) all

.PHONY: bonus all clean fclean re
