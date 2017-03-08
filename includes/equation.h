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
	double		x1;
	double		x2;
	double		x3;
	double		x4;
}				t_res;

typedef struct	s_equ
{
	double		bs;
	double		aa;
	double		ma;
	double		bb;
	double		cc;
	double		mc;
	double		k;
	double		u;
	double		vt;
	double		p;
	double		q;
	double		del;
	double		alpha;
	double		kos;
	double		r;
}				t_equ;

int				sgn(double x);
double			absf(double x);
double			uv(double delta, double q, double sg);
t_res			equationpoly1(float a, float b);
t_res			equationpoly2(float a, float b, float c);
t_res			equationpoly3(double a, double b, double c, double d);
t_res			equationpoly4(double *val);

#endif
