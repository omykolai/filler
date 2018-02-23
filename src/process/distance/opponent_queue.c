/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opponent_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 18:28:22 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/20 15:26:10 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/process.h"

static inline bool	cell_init(t_cell *c, t_cell_pos pos, t_qparams *p)
{
	if (c->val == 0)
		if (lst_add_sorted(c, pos, p, p->val->dist + 1))
		{
			p->valid_pos |= pos;
			return (true);
		}
	return (false);
}

static void			qpush_corners(t_map *m, int i, int j, t_qparams *p)
{
	if ((p->valid_pos & LEFT) && (p->valid_pos & TOP) && j > 0 && i > 0)
	{
		if (cell_init(&m->cells[i - 1][j - 1], LEFT | TOP, p))
			push_cell(g_qop, i - 1, j - 1, p->cl_num);
	}
	if ((p->valid_pos & RIGHT) && (p->valid_pos & TOP)
		&& i > 0 && j < m->m - 1)
	{
		if (cell_init(&m->cells[i - 1][j + 1], RIGHT | TOP, p))
			push_cell(g_qop, i - 1, j + 1, p->cl_num);
	}
	if ((p->valid_pos & LEFT) && (p->valid_pos & BOTTOM) && i < m->n - 1
		&& j > 0)
	{
		if (cell_init(&m->cells[i + 1][j - 1], LEFT | BOTTOM, p))
			push_cell(g_qop, i + 1, j - 1, p->cl_num);
	}
	if ((p->valid_pos & RIGHT) && (p->valid_pos & BOTTOM)
		&& i < m->n - 1 && j < m->m - 1)
		if (cell_init(&m->cells[i + 1][j + 1], RIGHT | BOTTOM, p))
			push_cell(g_qop, i + 1, j + 1, p->cl_num);
}

void				qpush_opponent_surrounds(t_map *m, int i, int j, int cl_num)
{
	t_qparams	p;

	p.cell = &m->cells[i][j];
	p.val = find_val(p.cell->dists, cl_num, p.cell->pos);
	p.valid_pos = POS_NONE;
	p.cl_num = cl_num;
	if ((p.val->pos & LEFT) && j > 0)
	{
		if (cell_init(&m->cells[i][j - 1], LEFT, &p))
			push_cell(g_qop, i, j - 1, cl_num);
	}
	if ((p.val->pos & RIGHT) && j < m->m - 1)
	{
		if (cell_init(&m->cells[i][j + 1], RIGHT, &p))
			push_cell(g_qop, i, j + 1, cl_num);
	}
	if ((p.val->pos & TOP) && i > 0)
	{
		if (cell_init(&m->cells[i - 1][j], TOP, &p))
			push_cell(g_qop, i - 1, j, cl_num);
	}
	if ((p.val->pos & BOTTOM) && i < m->n - 1)
		if (cell_init(&m->cells[i + 1][j], BOTTOM, &p))
			push_cell(g_qop, i + 1, j, cl_num);
	qpush_corners(m, i, j, &p);
}
