/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:50:04 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/09 14:50:06 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLY_COLOR_H
# define APPLY_COLOR_H

int				get_color_value(t_vector3f c);
void			put_in_image(t_rt *rt, int x, int y, t_vector3f *color);
void			apply_light(t_rt *rt, t_ray *ray, t_vector3f *color, t_inter *inter);

#endif
