/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:06:26 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/12 18:47:10 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

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

t_rt				create_rt();
void				loop(t_rt *rt); // en att

#endif
