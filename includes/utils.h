/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbreton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:10:51 by dbreton           #+#    #+#             */
/*   Updated: 2017/02/17 19:15:05 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef FLT_EPSILON
#  define FLT_EPSILON 14.99E-02F
# endif

char		almost_equal_relative(float a, float b);

#endif
