/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:10:00 by jrichard          #+#    #+#             */
/*   Updated: 2016/11/05 18:11:15 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int nb, int fd)
{
	long	tmp;

	tmp = (long)nb;
	if (tmp < 0)
	{
		ft_putchar_fd('-', fd);
		tmp *= -1;
	}
	if (tmp >= 10)
	{
		ft_putnbr_fd(tmp / 10, fd);
		ft_putnbr_fd(tmp % 10, fd);
	}
	else
		ft_putchar_fd(tmp + '0', fd);
}
