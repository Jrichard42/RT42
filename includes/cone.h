/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 18:25:44 by jrichard         ###   ########.fr       */
/*   Updated: 2017/02/10 13:46:34 by hpachy           ###   ########.fr       */
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
	int			angle;
	t_vector3f	dir;
}				t_cone;

t_obj			*create_cone(t_kvlexer *token, t_rt *rt);

#endif
