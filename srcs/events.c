/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 01:44:16 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 13:25:10 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include "events.h"

int				check_events(t_rt *rt)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (0);
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
			{
				//rt->camera->pos.x += 1.0f;
				//rt->camera->pos.y += 1.0f;
				rt->camera->pos.z -= 0.01f;
				//rt->camera->lookatpoint.x += 1.0f;
				//rt->camera->lookatpoint.y += 1.0f;
				rt->camera->lookatpoint.z -= 0.01f;
				refresh_rt(rt);
			}

		}
	}
	return (1);
}
