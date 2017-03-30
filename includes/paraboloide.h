/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloide.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:20:17 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/30 15:24:30 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARABOLOIDE_H
# define PARABOLOIDE_H

# include "equation.h"
# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"
# include "parser.h"
# include "libft.h"

typedef struct	s_paraboloide
{
	t_vector3f	dir;
	float		curve;
}				t_paraboloide;

int				create_paraboloide(t_kvlexer *token, t_rt *rt);

#endif
