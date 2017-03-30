# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/14 16:32:32 by jrichard          #+#    #+#              #
#    Updated: 2017/03/28 15:23:21 by jrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= rt
LIBFT			= lib/libft/
LIBFTMATRIX		= lib/libft_matrix/
SDL				= sdl/SDL/lib
SDL_PATH		= $(shell pwd)/sdl/SDL

SRCDIR			= srcs/
INCDIR			= includes/
SDLINCDIR		= sdl/SDL/include

SRC 			= 	main.c \
					camera.c \
					cone.c \
					cone_2.c \
					cylinder.c \
					cylinder_2.c \
					light.c \
					plane.c \
					paraboloide.c \
					sphere.c \
					events.c \
					parser.c \
					parser_get_type.c \
					parser_get_type2.c \
					parser_get_light.c \
					parser_get_material.c \
					parser_get_texture.c \
					material.c \
					texture.c \
					texture_2.c \
					damier.c \
					rt.c \
					utils.c \
					torus.c \
					torus_2.c \
					box.c \
					equationpoly1.c \
					equationpoly2.c \
					equationpoly3.c \
					equationpoly4.c \
					thread_manager.c \
					triangle.c \
					tetraedre.c \
					tetraedre_2.c \
					pyramide.c \
					pyramide_2.c \
					inter.c \
					apply_color.c \
					apply_color_2.c \
					sampling.c \
					normal_polygone.c \
					reflexion.c \
					refraction.c \
					light_2.c \
					cylinder_mapping.c \
					bruit_perlin.c \
					hsl_to_rgb.c \
					texture.c \
					disque.c \
					fog.c \
					wood.c \
					marble.c \
					sky.c \
					half_sphere.c \
					cut_cylinder.c \
					cut_cone.c \
					cut_sphere.c \
					cube_troue.c \


OBJ				= $(SRC:.c=.o)
CFLAGS			= -Wall -Wextra -pthread -Ofast

all: $(LIBFT) $(LIBFTMATRIX) $(NAME)

$(LIBFT):
	@$(MAKE) -C $@

$(LIBFTMATRIX):
	@$(MAKE) -C $@

$(NAME): $(OBJ)
	gcc -o $@ $^ -L$(LIBFT) -L$(LIBFTMATRIX) -L$(SDL) -lft -lft_matrix -lSDL2 -lm -framework opencl

%.o: $(SRCDIR)%.c
	gcc -o $@ $(CFLAGS) -c $< -I$(INCDIR) -I$(LIBFT) -I$(LIBFTMATRIX) -I$(SDLINCDIR)

clean:
	rm -rf $(OBJ)
	@$(MAKE) clean -C $(LIBFT)
	@$(MAKE) clean -C $(LIBFTMATRIX)

fclean: clean 
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) fclean -C $(LIBFTMATRIX)

re: fclean all

sdl :
	echo $(SDL_PATH)
	cd sdl/SDL2-2.0.5; \
		./configure --prefix=$(SDL_PATH) &&	make && make install

.PHONY: $(LIBFT)

.PHONY: $(LIBFTMATRIX)

.PHONY: sdl
