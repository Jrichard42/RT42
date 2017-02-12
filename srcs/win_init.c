/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <dbreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:15:07 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/12 18:44:38 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			texture_refresh(t_rt *rt)
{
		SDL_QueryTexture(rt.env->win, &rt.env->size, NULL, &rt.env->wh[0], &rt.env->wh[1]);
		SDL_LockTexture(rt.env->text, NULL, (void**)&rt.env->pixels, &rt.env->pitch);
		render_pic(rt);
		SDL_UnlockTexture(rt.env->text);
}

void			render(t_env *env)
{
		SDL_RenderClear(env->rend);
		SDL_RenderCopy(env->rend, env->text, NULL, NULL);
		SDL_RenderPresent(env->rend);
}

void			win_init(t_rt *rt)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_exit(3, "sdl init failed"); // check
	rt.env->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIN_MAX_X,
			WIN_MAX_Y,
			SDL_WINDOW_SHOWN); //check defines
	rt.env->rend = SDL_CreateRenderer(rt.env->win, -1, SDL_RENDERER_ACCELERATED);
	rt.env->win = SDL_CreateTexture(rt.env->rend, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			WIN_MAX_X + 1, WIN_MAX_Y + 1); //check_defines
	if (!(rt.env->win && rt.env->text && rt.env->rend))
		ft_exit(3, "renderer init failed"); // check
}
