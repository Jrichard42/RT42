/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:18:41 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/26 17:43:22 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "rt.h"
# include "ft_kvlexer.h"

typedef struct	s_texture
{
	char		name[11];
	int			width;
	int			height;
	t_vector3f	**data;
}				t_texture;

typedef struct	s_ptr_tex_type
{
	char		type[10];
	int			(*create)(t_kvlexer *, t_rt *, t_texture*);
}				t_ptr_tex_type;

int				create_tex(t_kvlexer *token, t_rt *rt);
int				search_tex(t_list *node, void *data);
int				tex_damier(t_kvlexer *token, t_rt *rt, t_texture *tex);


#endif
