/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 18:45:39 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "obj.h"
# include "rt.h"
# include "ft_kvlexer.h"

typedef struct	s_plane
{
	t_vector3f	dir;
	float		damier;
	t_vector3f	color1;
	t_vector3f	color2;
}				t_plane;

int				create_plane(t_kvlexer *token, t_rt *rt);

#endif
