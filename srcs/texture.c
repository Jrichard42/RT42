//
// Created by Drien BRETON on 3/22/17.
//

#include <math.h>
#include <stdlib.h>
#include "texture.h"
#include "camera.h"
# include "libft.h"
# include "libft_matrix.h"

static t_vector3f			**create_texture_tab(const int w, const int h, const char *type)
{
	t_vector3f	**texture;
	t_vector2f	point;

	point.y = -1;
	if (!(texture = (t_vector3f **)malloc(sizeof(t_vector3f *) * h)))
		return (NULL);
	while (++point.y < h)
	{
		point.x = -1;
		if (!(texture[(int)point.y] = (t_vector3f *)malloc(sizeof(t_vector3f) * w)))
			return (NULL);
		while (++point.x < w)
			texture[(int)point.y][(int)point.x] = bruit_perlin(point, type);
	}
	return (texture);
}

t_tex			create_texture(const int w, const int h, const char *type)
{
	t_tex		tex;

	if (w > 0 && h > 0)
	{
		tex.height = h - 1;
		tex.width = w - 1;
		tex.data = create_texture_tab(w, h, type);
	}
	else
		tex.data = NULL;
	return (tex);
}

t_vector3f		get_tex_point(t_tex tex, float u, float v)
{
	t_vector3f	color;
	int			x;
	int 		y;

	if (u < 0.0f)
		x = (int)(((1.0f - ((int)u - u))) * tex.width);
	else
		x = (int)(u * tex.width);
	if (v < 0.0f)
		y = (int)(((1.0f - ((int)v - v))) * tex.height);
	else
		y = (int)(v * tex.height);
	color = tex.data[y % tex.height][x % tex.width];

	return (color);
}