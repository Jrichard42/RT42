/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 14:19:28 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/16 15:00:53 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "light.h"
#include "apply_color.h"
#include "obj.h"
#include "ray.h"
#include "inter.h"
#include "camera.h"

t_vector3f			sampling(t_rt *rt,
							t_vector2f pixel,
							float sampling)
{
	t_vector2f		pixel_tmp;
	t_ray			vp_point;
	t_vector2f		inc;
	t_vector3f		color;

	inc.y = 1;
	pixel_tmp = pixel;
	color = create_vector3f(0, 0, 0);
	while (inc.y <= sampling)
	{
		inc.x = 1;
		while (inc.x <= sampling)
		{
			pixel = create_vector2f(pixel_tmp.x + (1.0f / inc.x++),
				pixel_tmp.y + (1.0f / inc.y));
			vp_point.start = rt->camera->pos;
			vp_point.dir = get_viewplanepoint(rt->camera, &pixel);
			vp_point.dir = normalize_vector3f(sub_vector3f(vp_point.dir,
				vp_point.start));
			vp_point.ir = 1.0;
			color = add_vector3f(color, apply_light(rt, &vp_point, 0));
		}
		++inc.y;
	}
	return (clamp_vector3f(div_vector3f(color, powf(sampling, 2.0)), 0, 255));
}
