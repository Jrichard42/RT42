/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:18:41 by abitoun           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/03/30 19:14:44 by jrichard         ###   ########.fr       */
=======
/*   Updated: 2017/03/30 17:42:03 by jrichard         ###   ########.fr       */
>>>>>>> 506c03b7047b32355bce118244c4f099c0e18cbd
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
	int			(*create)(t_kvlexer*, t_texture*);
}				t_ptr_tex_type;

int				create_tex(t_kvlexer *token, t_rt *rt);
int				search_tex(t_list *node, void *data);
int				malloc_tex(t_texture *tex);
void			del_tex(void *data, size_t size);
int				check_type_tex(t_kvlexer *token, t_texture *tex);
int				damier_tex(t_kvlexer *token, t_texture *tex);
int				marble_tex(t_kvlexer *token, t_texture *tex);
int				sky_tex(t_kvlexer *token, t_texture *tex);
int				wood_tex(t_kvlexer *token, t_texture *tex);
<<<<<<< HEAD
t_vector3f		get_tex_point(t_texture *tex, float u, float v);
=======
t_vector3f		get_tex_point(t_texture tex, float u, float v);
>>>>>>> 506c03b7047b32355bce118244c4f099c0e18cbd

#endif
