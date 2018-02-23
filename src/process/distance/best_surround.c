/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_surround.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:51:11 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/22 21:12:56 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/process.h"

static float	*g_max_lev;
static t_queue	*g_pivotals;

static inline bool		set_cell_level(t_cell *c, int lev)
{
	c->surr_level = lev;
	c->max_level = g_max_lev;
	*g_max_lev = lev;
	return (true);
}

static inline t_tuple	*new_tuple(int x, int y)
{
	t_tuple *t;

	t = (t_tuple*)malloc(sizeof(t_tuple));
	t->x = x;
	t->y = y;
	return (t);
}

static bool				cell_level(t_map *m, int i, int j, int lev)
{
	if (i >= 0 && j >= 0 && i < m->n && j < m->m)
		if (m->cells[i][j].val == 0 && !m->cells[i][j].max_level)
		{
			if (i != 0 && m->cells[i - 1][j].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
			if (j != 0 && m->cells[i][j - 1].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
			if (i != m->n - 1 && m->cells[i + 1][j].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
			if (j != m->m - 1 && m->cells[i][j + 1].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
			if (i != 0 && j != 0 &&
				m->cells[i - 1][j - 1].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
			if (i != m->n - 1 && j != m->m - 1 &&
				m->cells[i + 1][j + 1].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
			if (i != m->n - 1 && j != 0 &&
				m->cells[i + 1][j - 1].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
			if (i != 0 && j != m->m - 1 &&
				m->cells[i - 1][j + 1].val == m->opponent_cell)
				return (set_cell_level(&m->cells[i][j], lev));
		}
	return (false);
}

static void				next_cell(t_map *m, int i, int j, int lev)
{
	if (i < 0 || j < 0)
		return ;
	if (cell_level(m, i - 1, j, lev))
		ft_qpush(g_pivotals, new_tuple(i - 1, j), lev + 1);
	if (cell_level(m, i, j - 1, lev))
		ft_qpush(g_pivotals, new_tuple(i, j - 1), lev + 1);
	if (cell_level(m, i + 1, j, lev))
		ft_qpush(g_pivotals, new_tuple(i + 1, j), lev + 1);
	if (cell_level(m, i, j + 1, lev))
		ft_qpush(g_pivotals, new_tuple(i, j + 1), lev + 1);
}

void					best_surround(t_map *m, t_queue *pivotals)
{
	t_tuple *t;
	t_list	*node;

	g_max_lev = (float*)ft_memalloc(sizeof(float));
	g_pivotals = pivotals;
	while ((node = ft_qpopnode(g_pivotals)))
	{
		t = (t_tuple*)node->value;
		next_cell(m, t->x, t->y, node->value_size);
	}
	free(g_pivotals);
}
