/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 12:49:13 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/24 15:19:58 by jrichard         ###   ########.fr       */
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

static int		create_mat2(t_kvlexer *token, t_rt *rt, t_material *mat)
{
	(void)rt;
	ft_strncpy(mat->name, token->value, 10);
	if (ft_strlen(token->value) > 10)
	{
		ft_putstr("The MATERIAL name ");
		ft_putstr(token->value);
		ft_putstr(" is too long (10 characters max), it will be shortened to ");
		ft_putendl(mat->name);
	}
	if (!get_as_vector3f(token, "AMBIENT", &(mat->ka)))
		return ((int)ft_error("The MATERIAL should contain a field AMBIENT"));
	if (!get_as_vector3f(token, "DIFFUSE", &(mat->kd)))
		return ((int)ft_error("The MATERIAL should contain a field DIFFUSE"));
	if (!get_as_vector3f(token, "SPECULAR", &(mat->ks)))
		return ((int)ft_error("The MATERIAL should contain a field SPECULAR"));
	if (!get_as_int(token, "SHININESS", &(mat->sh)))
		return ((int)ft_error("The MATERIAL should contain a field SHININESS"));
	if (!get_as_float(token, "IR", &(mat->ir)))
		return ((int)ft_error("The MATERIAL should contain a field IR"));
	return (1);
}

int				create_mat(t_kvlexer *token, t_rt *rt)
{
	t_material	mat;
	t_list		*node;

	if (token->value)
	{
		if (!create_mat2(token, rt, &mat))
			return (0);
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
	return (1);
}
