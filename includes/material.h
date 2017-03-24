/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 12:48:18 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/23 15:09:15 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

#include "rt.h"
#include "ft_kvlexer.h"

typedef	struct	s_material
{
	char		name[11];
	float		ka;
	float		kd;
	float		ks;
	int			sh;
	float		ir;
}				t_material;

int				create_mat(t_kvlexer *token, t_rt *rt);
int				search_mat(t_list *node, void *data);

#endif
