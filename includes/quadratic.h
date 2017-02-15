/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:56:22 by abitoun           #+#    #+#             */
/*   Updated: 2017/02/15 17:56:23 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRATIC_H
# define	QUADRATIC_H

typedef struct	s_quadratic
{
	float		a;
	float		b;
	float		c;
	float		result;
	float		delta;
	float		sol_1;
	float		sol_2;
	t_vector	tmp;
}				t_quadratic

#endif