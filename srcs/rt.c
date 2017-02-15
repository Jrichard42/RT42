/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <dbreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:15:07 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/15 17:17:04 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			refresh(t_rt *rt)
{
		SDL_QueryTexture(rt.env->win, &rt.env->size, NULL, &rt.env->wh[0], &rt.env->wh[1]);
		SDL_LockTexture(rt.env->text, NULL, (void**)&rt.env->pixels, &rt.env->pitch);
		render_pic(rt);
		SDL_UnlockTexture(rt.env->text);
}

void			render(t_rt *rt)
{
		SDL_RenderClear(rt->env->rend);
		SDL_RenderCopy(rt->env->rend, rt->env->text, NULL, NULL);
		SDL_RenderPresent(rt->env->rend);
}

t_rt			*create_rt(int x, int y, char *name)
{
	t_rt		*rt;

	if (!(rt = ft_memalloc(sizeof(*rt))))
		exit(1);  //TODO check
	rt->env.size.x = 1300;
	rt->env.size.y = 1300;
	if (parser(name, rt) == -1) // fonction parser TODO
		return (-1);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_exit(3, "sdl init failed"); // check
	rt->env->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			x, y,
			SDL_WINDOW_SHOWN); //check defines
	rt->env->rend = SDL_CreateRenderer(rt->env->win, -1, SDL_RENDERER_ACCELERATED);
	rt->env->win = SDL_CreateTexture(rt->env->rend, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			x + 1, y + 1); //check_defines
	if (!(rt->env->win && rt->env->text && rt->env->rend))
		ft_exit(3, "renderer init failed"); // check
	return (rt);
}
