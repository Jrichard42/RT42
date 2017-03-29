/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:18:41 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/28 15:30:46 by jrichard         ###   ########.fr       */
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
	int			(*create)(t_kvlexer *, t_texture*);
}				t_ptr_tex_type;

int				create_tex(t_kvlexer *token, t_rt *rt);
int				search_tex(t_list *node, void *data);
int				check_type_tex(t_kvlexer *token, t_texture *tex);
int				damier_tex(t_kvlexer *token, t_texture *tex);
int				marble_tex(t_kvlexer *token, t_texture *tex);
int				sky_tex(t_kvlexer *token, t_texture *tex);
int				wood_tex(t_kvlexer *token, t_texture *tex);
int				malloc_tex(t_texture *tex);
t_vector3f		get_tex_point(t_texture tex, float u, float v);

#endif
