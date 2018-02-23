/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:36:47 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/16 13:30:46 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/read.h"

static inline void	reset_vertical_pos(t_cell **c, int i, int j, int cellval)
{
	if (i > 0 && c[i - 1][j].val == cellval)
	{
		c[i][j].pos &= ~TOP;
		c[i - 1][j].pos &= ~BOTTOM;
	}
}

static inline void	reset_horizontal_pos(t_cell **c, int i, int j, int cellval)
{
	if (j > 0 && c[i][j - 1].val == cellval)
	{
		c[i][j].pos &= ~LEFT;
		c[i][j - 1].pos &= ~RIGHT;
	}
}

static void			set_cell_position(t_map *m, int i, int j, int cellval)
{
	if (m->cells[i][j].val == cellval)
	{
		m->cells[i][j].pos = POS_ALL;
		reset_horizontal_pos(m->cells, i, j, cellval);
		reset_vertical_pos(m->cells, i, j, cellval);
		set_direction_start(m, i, j, cellval == m->opponent_cell);
	}
}

void				set_cell_pos(t_map *m, int i, int j)
{
	m->cells[i][j].pos = POS_NONE;
	set_cell_position(m, i, j, m->player_cell);
	set_cell_position(m, i, j, m->opponent_cell);
}

void				piece_cell_pos(t_piece *p, int i, int j)
{
	if (p->cells[i][j].val == 1)
	{
		p->cells[i][j].pos = POS_ALL;
		reset_horizontal_pos(p->cells, i, j, 1);
		reset_vertical_pos(p->cells, i, j, 1);
	}
	else
		p->cells[i][j].pos = POS_NONE;
}
