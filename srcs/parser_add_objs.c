/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 01:04:05 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/18 19:38:32 by jrichard         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "parser.h"

static int			search_key(t_list *node, void *data)
{
	if (!ft_strcmp(((t_kvlexer *)node->content)->key, (char *)data))
		return (1);
	return (0);
}

t_vector3f			get_as_vector3f(t_kvlexer *token, char *str)
{
	t_list			*node;
	t_kvlexer		*field;
	char			*tmp;
	t_vector3f		vector;

	vector = create_vector3f(1, 1, 1);
	if ((node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
		{
			vector.x = ft_atof(field->value);
			tmp = ft_strchr(field->value, ',');
			if (tmp && *(++tmp))
				vector.y = ft_atof(tmp);
			tmp = ft_strchr(tmp, ',');
			if (tmp && *(++tmp))
				vector.z = ft_atof(tmp);
		}
	}
	return (vector);
}

float				get_as_float(t_kvlexer *token, char *str)
{
	t_list			*node;
	t_kvlexer		*field;
	float			ret_float;

	ret_float = 100;
	if ((node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
			ret_float = ft_atof(field->value);
	}
	return (ret_float);
}

t_material			get_material(t_kvlexer *token)
{
	t_list			*node;
	t_material		material;
	t_kvlexer		*mat_token;

	material.ka = 0.33;
	material.kd = 0.33;
	material.ks = 0.33;
	material.sh = 10;
	material.ir = 0.0;
	if ((node = ft_lstsearch(token->children->head, &search_key, "MATERIAL")))
	{
		mat_token = (t_kvlexer *)node->content;
		material.ka = get_as_float(mat_token, "AMBIENT");
		material.kd = get_as_float(mat_token, "DIFFUSE");
		material.ks = get_as_float(mat_token, "SPECULAR");
		material.sh = get_as_float(mat_token, "SHININESS");
		material.ir = get_as_float(mat_token, "IR");
	}
	return (material);
}

/*t_trans				get_trans(t_kvlexer *token)
{
	t_trans			trans;
	t_vector3f		translation;
	t_vector3f		scale;
	t_vector3f		rotation;

	trans.trans_ray = create_matrix();
	trans.trans_dir = create_matrix();
	trans.trans_coll = create_matrix();
	trans.trans_normal = create_matrix();
	translation = get_as_vector3f(token, "POSITION");
	scale = get_as_vector3f(token, "SCALE");
	rotation = get_as_vector3f(token, "ROTATION");
	
	trans.trans_ray = translation_matrix(&trans.trans_ray, mult_vector3f(translation, -1.0));
	trans.trans_ray = rotation_x_matrix(&trans.trans_ray, -rotation.x);
	trans.trans_ray = rotation_y_matrix(&trans.trans_ray, -rotation.y);
	trans.trans_ray = rotation_z_matrix(&trans.trans_ray, -rotation.z);
	trans.trans_ray = scale_matrix(&trans.trans_ray, create_vector3f(1.0 / scale.x, 1.0 / scale.y, 1.0 / scale.z));
	
	trans.trans_dir = rotation_x_matrix(&trans.trans_dir, -rotation.x);
	trans.trans_dir = rotation_y_matrix(&trans.trans_dir, -rotation.y);
	trans.trans_dir = rotation_z_matrix(&trans.trans_dir, -rotation.z);
	trans.trans_dir = scale_matrix(&trans.trans_dir, create_vector3f(1.0 / scale.x, 1.0 / scale.y, 1.0 / scale.z));
	
	trans.trans_coll = scale_matrix(&trans.trans_coll, scale);	
	trans.trans_coll = rotation_z_matrix(&trans.trans_coll, rotation.z);
	trans.trans_coll = rotation_y_matrix(&trans.trans_coll, rotation.y);
	trans.trans_coll = rotation_x_matrix(&trans.trans_coll, rotation.x);
	trans.trans_coll = translation_matrix(&trans.trans_coll, translation);

	trans.trans_normal = scale_matrix(&trans.trans_normal, create_vector3f(1.0 / scale.x, 1.0 / scale.y, 1.0 / scale.z));
	trans.trans_normal = rotation_z_matrix(&trans.trans_normal, rotation.z);
	trans.trans_normal = rotation_y_matrix(&trans.trans_normal, rotation.y);
	trans.trans_normal = rotation_x_matrix(&trans.trans_normal, rotation.x);
	
	return (trans);
}*/
