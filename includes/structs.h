/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:53:25 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 14:25:09 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_tuple
{
	int			x;
	int			y;
}				t_tuple;

typedef struct	s_cluster
{
	t_tuple		cell;
	t_tuple		last_section;
}				t_cluster;

typedef struct	s_border
{
	int			top;
	int			bottom;
	int			left;
	int			right;
	int			topleft;
	int			topright;
	int			botleft;
	int			botright;
}				t_border;

typedef enum	e_cell_pos
{
	POS_NONE = 0,
	POS_ALL = 15,
	LEFT = 1,
	TOP = 2,
	RIGHT = 4,
	BOTTOM = 8,
	CENTR = 16
}				t_cell_pos;

#endif
