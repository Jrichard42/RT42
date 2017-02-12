/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:35:37 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 19:05:11 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_matrix.h"
#include "libft.h"

void			init_identity(t_matrix *matrix)
{
	ft_bzero(matrix, sizeof(*matrix));
	matrix->tab[0][0] = 1.0;
	matrix->tab[1][1] = 1.0;
	matrix->tab[2][2] = 1.0;
	matrix->tab[3][3] = 1.0;
}

t_matrix		mult_matrix(t_matrix *m1, t_matrix *m2)
{
	int			i;
	int			j;
	int			i2;
	float		sum;
	t_matrix	new;

	j = 0;
	new = create_matrix();
	while (j < 4)
	{
		i2 = 0;
		while (i2 < 4)
		{
			i = 0;
			sum = 0;
			while (i < 4)
			{
				sum += m1->tab[j][i] * m2->tab[i][i2];
				++i;
			}
			new.tab[j][i2++] = sum;
		}
		++j;
	}
	return (new);
}

t_matrix		create_matrix(void)
{
	t_matrix	matrix;

	init_identity(&matrix);
	return (matrix);
}
