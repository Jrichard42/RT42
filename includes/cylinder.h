/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:17:41 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/09 14:19:05 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPEHRE_H
# define cylinder_H

# include "obj.h"

typedef struct	s_cylinder
{
	int			radius;
}				t_cylinder;

t_object		create_cylinder();

#endif
