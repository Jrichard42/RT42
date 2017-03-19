/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 12:49:13 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/19 18:34:28 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "parser.h"
#include "libft.h"

int				search_mat(t_list *node, void *data)
{
	if (!ft_strcmp(((t_material *)node->content)->name, (char *)data))
		return (1);
	return (0);
}

static void		base_mat(t_material *mat)
{
	mat->ka = 0.3;
	mat->kd = 0.3;
	mat->ks = 0.3;
	mat->sh = 10;
	mat->ir = 1.0;
}

void			create_mat(t_kvlexer *token, t_rt *rt)
{
	t_material	mat;
	t_list		*node;

	if (token->value)
	{
		base_mat(&mat);
		ft_strncpy(mat.name, token->value, 10);
		get_as_float(token, "AMBIENT", &(mat.ka));
		get_as_float(token, "DIFFUSE", &(mat.kd));
		get_as_float(token, "SPECULAR", &(mat.ks));
		get_as_int(token, "SHININESS", &(mat.sh));
		get_as_float(token, "IR", &(mat.ir));
		if (rt->materials && (node = ft_lstsearch(rt->materials->head, &search_mat, mat.name)))
		{
			((t_material *)node->content)->ka = mat.ka;
			((t_material *)node->content)->kd = mat.kd;
			((t_material *)node->content)->ks = mat.ks;
			((t_material *)node->content)->sh = mat.sh;
			((t_material *)node->content)->ir = mat.ir;
		}
		else
			ft_lstadd(&rt->materials, ft_lstnew(&mat, sizeof(mat)));
	}
	else
		ft_error("Materials in the material file should have a name");
}
