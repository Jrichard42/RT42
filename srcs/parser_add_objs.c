/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 01:04:05 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 15:03:31 by hpachy           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "obj_types.h"
#include "parser.h"

#define SPHERE ((t_sphere *)sphere->data)
#define PLANE ((t_plane *)plane->data)

static int			search_key(t_list *node, void *data)
{
	if (!ft_strcmp(((t_kvlexer *)node->content)->key, (char *)data))
		return (1);
	return (0);
}

static t_vector3f	get_as_vector3f(t_kvlexer *token, char *str)
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

static int			get_as_float(t_kvlexer *token, char *str)
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

static t_material	get_material(t_kvlexer *token)
{
	t_list			*node;
	t_material		material;
	t_kvlexer		*mat_token;

	material.ambient = create_vector3f(0.33, 0.33, 0.33);
	material.diffuse = create_vector3f(0.33, 0.33, 0.33);
	material.specular = create_vector3f(0.33, 0.33, 0.33);
	material.shininess = 10;
	if ((node = ft_lstsearch(token->children->head, &search_key, "MATERIAL")))
	{
		mat_token = (t_kvlexer *)node->content;
		material.ambient = get_as_vector3f(mat_token, "AMBIENT");
		material.diffuse = get_as_vector3f(mat_token, "DIFFUSE");
		material.specular = get_as_vector3f(mat_token, "SPECULAR");
		material.shininess = get_as_float(mat_token, "SHININESS");
	}
	return (material);
}

static t_trans		get_trans(t_kvlexer *token)
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
}

int					add_sphere(t_kvlexer *token, t_raytracer *rt)
{
	t_obj			*sphere;

	if (!(sphere = create_sphere(get_as_vector3f(token, "POSITION"))))
		return (0);
	sphere->material = get_material(token);
	sphere->trans = get_trans(token);
	SPHERE->radius = get_as_float(token, "RADIUS");
	ft_lstadd(&rt->objs, ft_lstnew(sphere, sizeof(*sphere)));
	ft_memdel((void**)&sphere);
	return (1);
}

int					add_light(t_kvlexer *token, t_raytracer *rt)
{
	t_obj			*light;

	if (!(light = create_light(get_as_vector3f(token, "POSITION"))))
		return (0);
	ft_lstadd(&rt->lights, ft_lstnew(light, sizeof(*light)));
	ft_memdel((void**)&light);
	return (1);
}

int					add_camera(t_kvlexer *token, t_raytracer *rt)
{
	t_camera		camera;

	camera = create_camera(get_as_vector3f(token, "POSITION"),
			get_as_vector3f(token, "LOOKAT"), get_as_float(token, "FOV"),
			get_as_vector3f(token, "RESOLUTION"));
	rt->camera = camera;
	return (1);
}

int					add_plane(t_kvlexer *token, t_raytracer *rt)
{
	t_obj			*plane;

	if (!(plane = create_plane(get_as_vector3f(token, "POSITION"))))
		return (0);
	plane->material = get_material(token);
	plane->trans = get_trans(token);
	PLANE->normal = create_vector3f(0, 1, 0);
	ft_lstadd(&rt->objs, ft_lstnew(plane, sizeof(*plane)));
	ft_memdel((void **)&plane);
	return (1);
}

int					add_cylinder(t_kvlexer *token, t_raytracer *rt)
{
	t_obj			*cylinder;

	if (!(cylinder = create_cylinder(get_as_vector3f(token, "POSITION"))))
		return (0);
	cylinder->material = get_material(token);
	cylinder->trans = get_trans(token);
	ft_lstadd(&rt->objs, ft_lstnew(cylinder, sizeof(*cylinder)));
	ft_memdel((void **)&cylinder);
	return (1);
}

int					add_cone(t_kvlexer *token, t_raytracer *rt)
{
	t_obj			*cone;

	if (!(cone = create_cone(get_as_vector3f(token, "POSITION"))))
		return (0);
	cone->material = get_material(token);
	cone->trans = get_trans(token);
	ft_lstadd(&rt->objs, ft_lstnew(cone, sizeof(*cone)));
	ft_memdel((void **)&cone);
	return (1);
}
