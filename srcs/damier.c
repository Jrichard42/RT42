/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 15:16:37 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/28 15:29:15 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ft_kvlexer.h"
#include "texture.h"
#include "parser.h"
#include "libft_matrix.h"

static void		check_error_damier_annex(t_vector2f *size_tmp)
{
	if (size_tmp->y < 10)
	{
		size_tmp->y = 10;
		ft_putstr("The X_SIZE are inferior to 10\n");
	}
	if (size_tmp->y > 2000)
	{
		size_tmp->y = 2000;
		ft_putstr("The X_SIZE are superior to 10\n");
	}
}

static void		check_error_damier(t_vector2f *size_tmp, int *case_size)
{
	if (*case_size <= 0)
	{
		*case_size = 1;
		ft_putstr("The CASE_SIZE are inferior or equal to 0\n");
	}
	if (*case_size > 1000)
	{
		*case_size = 1000;
		ft_putstr("The CASE_SIZE are superior to 1000\n");
	}
	if (size_tmp->x < 10)
	{
		size_tmp->x = 10;
		ft_putstr("The X_SIZE are inferior to 10\n");
	}
	if (size_tmp->x > 1000)
	{
		size_tmp->x = 1000;
		ft_putstr("The X_SIZE are superior to 10\n");
	}
	check_error_damier_annex(size_tmp);
}

static int		fill_texture_damier_annex(t_vector2i *count)
{
	if (count->x % 2 == 0 && count->y % 2 == 0)
		return (0);
	else if (count->x % 2 != 0 && count->y % 2 == 0)
		return (1);
	else if (count->x % 2 == 0 && count->y % 2 != 0)
		return (1);
	else if (count->x % 2 != 0 && count->y % 2 != 0)
		return (0);
	return (0);
}

static void		fill_texture_damier(t_texture *tex,
									int case_size,
									t_vector3f *color)
{
	t_vector2i	count;
	t_vector2i	nb_case;
	t_vector2i	tmp_pos;

	count.y = -1;
	nb_case.x = tex->width / case_size;
	nb_case.y = tex->height / case_size;
	while (++count.y < nb_case.y)
	{
		count.x = -1;
		while (++count.x < nb_case.x)
		{
			tmp_pos.y = 0;
			while (tmp_pos.y < case_size)
			{
				tmp_pos.x = 0;
				while (tmp_pos.x < case_size)
					tex->data[tmp_pos.y + (count.y * case_size)]
					[tmp_pos.x++ + (count.x * case_size)] =
					color[fill_texture_damier_annex(&count)];
				++tmp_pos.y;
			}
		}
	}
}

int				damier_tex(t_kvlexer *token, t_texture *tex)
{
	t_vector2f	size_tmp;
	t_vector3f	case_color[2];
	int			y;
	int			case_size;

	y = 0;
	if (get_as_vector2f(token, "SIZE", &size_tmp) == 0)
		return ((int)ft_error("The DAMIER should contain a field SIZE"));
	if (get_as_vector3f(token, "COLOR_1", &case_color[0]) == 0)
		return ((int)ft_error("The DAMIER should contain a field COLOR_1"));
	if (get_as_vector3f(token, "COLOR_2", &case_color[1]) == 0)
		return ((int)ft_error("The DAMIER should contain a field COLOR_2"));
	if (get_as_int(token, "CASE_SIZE", &case_size) == 0)
		return ((int)ft_error("The DAMIER should contain a field CASE_SIZE"));
	check_error_damier(&size_tmp, &case_size);
	tex->width = size_tmp.x;
	tex->height = size_tmp.y;
	if (!malloc_tex(tex))
		return (0);
	fill_texture_damier(tex, case_size, case_color);
	return (1);
}
