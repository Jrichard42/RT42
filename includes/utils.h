/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:10:51 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/25 14:52:48 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <float.h>
# ifndef FLT_EPSILON
#  define FLT_EPSILON 1.19209290E-07F
# endif

char		almost_equal_relative(float a, float b);

#endif
