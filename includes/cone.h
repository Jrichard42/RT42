/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:20:46 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/19 09:38:06 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "rt.h"
# include "obj.h"
# include "quadratic.h"
# include "ft_kvlexer.h"

typedef struct	s_cone
{
	float		angle;
	t_vector3f	dir;
}				t_cone;

int				create_cone(t_kvlexer *token, t_rt *rt);

#endif
