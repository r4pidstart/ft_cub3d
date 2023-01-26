# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joowpark <joowpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 14:51:43 by joowpark          #+#    #+#              #
#    Updated: 2023/01/26 13:35:43 by joowpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= test
CC= cc
SRC = ft_dfs_check.o ft_free.o ft_get_something.o ft_make_map.o \
	  ft_maps.o ft_node.o ft_parse.o ft_set_map.o ft_string.o \
	  ft_check_lines.o
LIBFT= ../ft_mylibft/libft.a
OFLAGS =
CFLAGS += $(OFLAGS) -c
CFLAGS +=  -Wall -Wextra -Werror
CFLAGS +=  -I ./include
#FFLAG =  -fsanitize=address

TARGETS = $(NAME)

all : $(TARGETS)

$(TARGETS): $(SRC) $(LIBFT)
	$(CC) -o $@ $^ -g $(FFLAG)

%.o : %.c
	$(CC) $(CFLAGS) $^ -o $@ -g $(FFLAG)

.PHONY : clean
clean:
	rm -f ${SRC}

.PHONY : fclean

fclean : clean
	rm -f ${NAME}

.PHONY : re
re : 
	make fclean
	make all
