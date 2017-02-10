/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 09:10:02 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/27 02:40:09 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_errors(const char **s, int *minus)
{
	if (!**s)
		return (-1);
	while (**s && ft_isspace(**s))
		++*s;
	if (!ft_isdigit(**s) && **s != '-' && **s != '+')
		return (-1);
	if (**s == '+')
		++*s;
	else if (**s == '-')
	{
		++*s;
		*minus = -1;
	}
	if (!ft_isdigit(**s))
		return (-1);
	return (0);
}

double		ft_atof(const char *s)
{
	double	ret;
	int		minus;
	int		div;

	ret = 0;
	minus = 1;
	div = 0;
	if (parse_errors(&s, &minus) == -1)
		return (0);
	ret = (int)(*s - 48);
	if (minus == -1)
		ret = -ret;
	while (ft_isdigit(*++s))
		ret = ret * 10 + (int)(*s - 48) * minus;
	if (*s == '.')
	{
		while (ft_isdigit(*++s))
		{
			ret = ret * 10 + (int)(*s - 48) * minus;
			++div;
		}
	}
	while (div-- > 0)
		ret *= 0.1;
	return (ret);
}
