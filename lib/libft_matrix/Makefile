# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/12 13:12:34 by jrichard          #+#    #+#              #
#    Updated: 2017/01/12 13:35:49 by jrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_matrix.a

SRC = ft_matrix.c ft_vector2d.c ft_vector2f.c ft_vector3d.c ft_vector3f.c transformation.c

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
