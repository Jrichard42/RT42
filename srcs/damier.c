/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 15:16:37 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/27 14:37:32 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_kvlexer.h"
#include "texture.h"
#include "parser.h"
#include "libft_matrix.h"

static void		fill_texture_damier(t_texture *tex, int case_size, t_vector3f *color_1, t_vector3f *color_2)
{
	t_vector2i	count;
	t_vector2i	nb_case;
	t_vector2i 	tmp_pos;

	count.y = 0;
	nb_case.x = tex->width / case_size;
	nb_case.y = tex->height / case_size;
	while (count.y < nb_case.y)
	{
		count.x = 0;
		while (count.x < nb_case.x)
		{
			tmp_pos.y = 0;
			while (tmp_pos.y < case_size)
			{
				tmp_pos.x = 0;
				while (tmp_pos.x < case_size)
				{
					if (count.x % 2 == 0 && count.y % 2 == 0)
						tex->data[tmp_pos.y + (count.y * case_size)][tmp_pos.x + (count.x * case_size)] = *color_1;
					else if (count.x % 2 != 0 && count.y % 2 == 0)
						tex->data[tmp_pos.y + (count.y * case_size)][tmp_pos.x + (count.x * case_size)] = *color_2;
					else if (count.x % 2 == 0 && count.y % 2 != 0)
						tex->data[tmp_pos.y + (count.y * case_size)][tmp_pos.x + (count.x * case_size)] = *color_2;
					else if (count.x % 2 != 0 && count.y % 2 != 0)
						tex->data[tmp_pos.y + (count.y * case_size)][tmp_pos.x + (count.x * case_size)] = *color_1;
					++tmp_pos.x;
				}
				++tmp_pos.y;
			}
			++count.x;
		}
		++count.y;
	}
}

int				tex_damier(t_kvlexer *token, t_rt *rt, t_texture *tex)
{
	t_vector2f	size_tmp;
	t_vector3f	case_color_1;
	t_vector3f	case_color_2;
	int			y;
	int			case_size;

	y = 0;
	if (get_as_vector2f(token, "SIZE", &size_tmp) == 0)
		return((int)ft_error("The DAMIER should contain a field SIZE"));
	if (get_as_vector3f(token, "COLOR_1", &case_color_1) == 0)
		return((int)ft_error("The DAMIER should contain a field COLOR_1"));
	if (get_as_vector3f(token, "COLOR_2", &case_color_2) == 0)
		return((int)ft_error("The DAMIER should contain a field COLOR_2"));
	if (get_as_int(token, "CASE_SIZE", &case_size) == 0)
		return((int)ft_error("The DAMIER should contain a field CASE_SIZE"));
	tex->width = size_tmp.x;
	tex->height = size_tmp.y;
	tex->data = malloc(sizeof(t_vector3f *) * tex->height);
	while (y < tex->height)
	{
		tex->data[y] = malloc(sizeof(t_vector3f) * tex->width);
		y++;
	}
	fill_texture_damier(tex, case_size, &case_color_1, &case_color_2);
	return (1);
}
