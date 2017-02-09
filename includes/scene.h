/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:55:40 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/09 17:07:43 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "scene.h"

typedef struct  s_scene
{
	void        *data;
	void        (*calc)(struct s_scene *scene);
	void        (*draw)(struct s_scene *scene);
}               t_scene;

#endif
