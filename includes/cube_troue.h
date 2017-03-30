/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_troue.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:15:26 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/30 14:15:27 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_TROUE_H
# define CUBE_TROUE_H

# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"

typedef	struct	s_cube_troue
{
	float		circle;
}				t_cube_troue;

int				create_cube_troue(t_kvlexer *token, t_rt *rt);

#endif
