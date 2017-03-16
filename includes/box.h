/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:53:34 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/16 13:37:30 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_H
# define BOX_H

# include "rt.h"
# include "obj.h"
# include "ft_kvlexer.h"
# include "parser.h"
# include "libft.h"
# include "equation.h"

typedef struct	s_box
{
	t_vector3f	min;
	t_vector3f	max;
}				t_box;

int				create_box(t_kvlexer *token, t_rt *rt);
#endif
