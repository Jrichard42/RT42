/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedurale.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:32:58 by abitoun           #+#    #+#             */
/*   Updated: 2017/02/25 18:33:00 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	PROCEDURALE_H
# define 	PROCEDURALE_H

# include "rt.h"
# include "obj.h"
# include "inter.h"
# include "ft_kvlexer.h"

t_vector3f		procedurale(t_inter *inter, float *coeffs, float *intensity);

#endif