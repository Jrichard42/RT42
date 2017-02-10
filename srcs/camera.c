/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:37:11 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/10 16:01:05 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_vector3f	get_viewplanepoint(t_camera *camera, t_vector2f *pixel)
{

}

void	create_camera(t_kvlexer *token, t_rt *rt)
{
	rt->camera.c = get_as_vector3f(token, "POSITION");
	rt->camera.lookatpoint = get_as_vector3f(token, "LOOKAT");
	rt->camera.fov = get_as_float(token, "FOV");
}
