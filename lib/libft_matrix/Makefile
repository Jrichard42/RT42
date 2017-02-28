# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/12 13:12:34 by jrichard          #+#    #+#              #
#    Updated: 2017/02/25 13:07:39 by jrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_matrix.a

SRC = ft_matrix.c ft_vector2d.c ft_vector2f.c ft_vector3d.c ft_vector3f.c \
	  ft_vector2d2.c ft_vector2f2.c ft_vector3d2.c ft_vector3f2.c ft_vector2d3.c \
	  ft_vector2f3.c ft_vector3d3.c ft_vector3f3.c transformation.c

INC_DIR = .

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
	gcc -c $(SRC) $(CFLAGS) -I$(INC_DIR)
	ar rc $@ $(OBJ)
	ranlib $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
