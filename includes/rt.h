/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:06:26 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/10 15:53:17 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

typedef struct	s_env
{
	SDL_Window	*win;
	SDL_Texture	*text;
	SDL_RENDERE	*rend;
	t_vector2f	*size;
}				t_env;

typedef	struct	s_rt
{
	t_env		env;
	t_camera	camera;
	t_dlist		*objs;
}				t_rt;

t_rt			create_rt();

#endif
