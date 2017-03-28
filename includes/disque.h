/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disaue.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:08:19 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/28 15:08:20 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISQUE_H
# define DISQUE_H
# include "rt.h"
# include "quadratic.h"
# include "ft_kvlexer.h"

typedef struct	s_disque
{
	float		radius;
	t_vector3f	dir;
}				t_disque;

int				create_disque(t_kvlexer *token, t_rt *rt);

#endif
