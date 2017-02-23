/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libequ.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:27:40 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/02/21 14:27:45 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBEQU_H
# define LIBEQU_H
# include <math.h>

typedef struct	s_res
{
	int			nb;
	float		x1;
	float		x2;
	float		x3;
	float		x4;
}				t_res;

typedef struct	s_equ
{
	float		bs;
	float		aa;
	float		ma;
	float		bb;
	float		cc;
	float		mc;
	float		k;
	float		u;
	float		vt;
	float		p;
	float		q;
	float		del;
	float		alpha;
	float		kos;
	float		r;
}				t_equ;

int				sgn(float x);
float			absf(float x);
float			uv(float delta, float q, float sg);
t_res			equationpoly(float *val, int lenght);
t_res			equationpoly1(float a, float b);
t_res			equationpoly2(float a, float b, float c);
t_res			equationpoly3(float a, float b, float c, float d);
t_res			equationpoly4(float *val);

#endif
