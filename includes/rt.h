/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:06:26 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/17 15:19:22 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <SDL2/SDL.h>
# include "camera.h"
# include "libft.h"
# include "libft_matrix.h"

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Texture		*text;
	SDL_Renderer	*rend;
	t_vector2f		size;
	int				pitch;
	int				wh[2];
	Uint32			*pixels;
	Uint32			format;
}					t_env;

typedef	struct		s_rt
{
	t_env			env;
	t_camera		camera;
	t_dlist			*objs;
}					t_rt;

t_rt				*create_rt(int x, int y, char *name);
void				refresh_rt(t_rt *rt);
void				render_rt(t_rt *rt);

#endif
