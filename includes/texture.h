/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:18:41 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/24 17:49:33 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "rt.h"
# include "ft_kvlexer.h"

typedef struct	s_texture
{
	char		name[11];
	t_vector2i	size;
	t_vector3f	**data;
}				t_texture;

int				create_tex(t_kvlexer *token, t_rt *rt);
int				search_tex(t_list *node, void *data);

#endif
