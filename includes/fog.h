/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:06:12 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/28 15:06:15 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOG_H
# define FOG_H
# include "rt.h"
# include "inter.h"
# include "ft_kvlexer.h"
# include "parser.h"

int				create_fog(t_kvlexer *token, t_rt *rt);
t_vector3f		fog(t_rt *rt, t_inter *inter, t_vector3f color);

#endif
