# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/14 16:32:32 by jrichard          #+#    #+#              #
#    Updated: 2017/02/17 19:40:46 by jrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= rtv1
LIBFT			= lib/libft/
LIBFTMATRIX		= lib/libft_matrix/
SDL				= sdl/SDL/lib

SRCDIR			= srcs/
INCDIR			= includes/
SDLINCDIR		= sdl/SDL/include

SRC 			= camera.c cylinder.c light.c parser.c plane.c sphere.c cone.c events.c \
				  main.c parser_add_objs.c rt.c
OBJ				= $(SRC:.c=.o)
CFLAGS			= -Wall -Wextra -Ofast

all: $(LIBFT) $(LIBFTMATRIX) $(NAME)

$(LIBFT):
	@$(MAKE) -C $@

$(LIBFTMATRIX):
	@$(MAKE) -C $@

$(NAME): $(OBJ)
	gcc -o $@ $^ -L$(LIBFT) -L$(LIBFTMATRIX) -L$(SDL) -lft -lft_matrix -lSDL2 -lSDL2main

%.o: $(SRCDIR)%.c
	gcc -o $@ -c $< $(CFLAGS) -I$(INCDIR) -I$(LIBFT) -I$(LIBFTMATRIX) -I$(SDLINCDIR)

clean:
	rm -rf $(OBJ)
	@$(MAKE) clean -C $(LIBFT)
	@$(MAKE) clean -C $(LIBFTMATRIX)

fclean: clean 
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) fclean -C $(LIBFTMATRIX)

re: fclean all

.PHONY: $(LIBFT)

.PHONY: $(LIBFTMATRIX)
