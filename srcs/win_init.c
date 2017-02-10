/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <dbreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:15:07 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/10 16:24:06 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		texture_refresh(t_env *env, t_rt *rt)
{
		SDL_QueryTexture(env->win, &env->size, NULL, &env->wh[0], &env->wh[1]);
		SDL_LockTexture(env->text, NULL, (void**)&env->pixels, &env->pitch);
		render_pic(rt);
		SDL_UnlockTexture(env->text);
}

static void		render(t_env *env)
{
		SDL_RenderClear(env->rend);
		SDL_RenderCopy(env->rend, env->text, NULL, NULL);
		SDL_RenderPresent(env->rend);
}

void			loop(t_rt *rt)		// a move 
{
	SDL_Event	ev;

	texture_refresh(rt->env, rt);
	while (1)
	{
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				exit(0);
		}
		render(rt->env);
	}
}

void			win_init(t_rt *rt)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_exit(3, "sdl init failed");
	rt->env.win = SDL_CreateWindow("rtv1", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIN_MAX_X,
			WIN_MAX_Y,
			SDL_WINDOW_SHOWN);
	rt->env.rend = SDL_CreateRenderer(s.win, -1, SDL_RENDERER_ACCELERATED);
	rt->env.win = SDL_CreateTexture(s.ren, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			WIN_MAX_X + 1, WIN_MAX_Y + 1);
	if (!(rt->env.win && rt->env.text && rt->env.rend))
		ft_exit(3, "renderer init failed");
}
