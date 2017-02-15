/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:25:19 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/09 13:25:20 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_H
# define INTER_H

typedef	struct	s_inter
{
	t_vector3f	impact;
	t_vector3f	normal;
	float		distance;
	t_obj		*obj;
}				t_inter;

#endif
