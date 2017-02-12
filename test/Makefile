# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/14 16:32:32 by jrichard          #+#    #+#              #
#    Updated: 2017/02/12 16:57:06 by jrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fractol
LIBFT			= lib/libft/
LIBFT_MATRIX	= lib/libft_matrix/

SRCDIR			= srcs/
INCDIR			= includes/

SRC 			= main.c thpool.c
OBJ				= $(SRC:.c=.o)
CFLAGS			= -Wall -Wextra -Ofast -pthread

all: $(LIBFT) $(LIBFT_MATRIX) $(NAME)

$(LIBFT):
	@$(MAKE) -C $@

$(LIBFT_MATRIX):
	@$(MAKE) -C $@

$(NAME): $(OBJ)
	gcc -o $@ $^ -L$(LIBFT) -L$(LIBFT_MATRIX) -lft -lft_matrix -lmlx -framework OpenGL -framework AppKit

%.o: $(SRCDIR)%.c
	gcc -o $@ -c $< $(CFLAGS) -I$(INCDIR) -I$(LIBFT) -I$(LIBFT_MATRIX)

clean:
	rm -rf $(OBJ)
	@$(MAKE) clean -C $(LIBFT)
	@$(MAKE) clean -C $(LIBFT_MATRIX)

fclean: clean 
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) fclean -C $(LIBFT_MATRIX)

re: fclean all

.PHONY: $(LIBFT)

.PHONY: $(LIBFT_MATRIX)
