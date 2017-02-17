/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/17 20:07:02 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define light_H

# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"

typedef struct	s_light
{
	t_vector3f	color;
}				t_light;

int				create_light(t_kvlexer *token, t_rt *rt);

#endif
