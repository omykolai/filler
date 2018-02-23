/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:40:59 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/22 13:50:26 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/process.h"

t_queue				*g_qop;
t_queue				*g_qpl;

static void			set_cl_num_recursive(t_map *m, int i, int j)
{
	if (m->cells[i][j].val == m->opponent_cell)
	{
		if (m->cells[i][j].cluster_num == -1)
		{
			m->cells[i][j].cluster_num = m->cluster_count;
			if (m->cells[i][j].pos != POS_NONE)
			{
				push_cell(g_qop, i, j, m->cluster_count);
				set_diag_vals(m, i, j);
			}
			if (i < m->n - 1)
				set_cl_num_recursive(m, i + 1, j);
			if (i > 0)
				set_cl_num_recursive(m, i - 1, j);
			if (j < m->m - 1)
				set_cl_num_recursive(m, i, j + 1);
			if (i > 0)
				set_cl_num_recursive(m, i, j - 1);
		}
	}
}

static void			set_best_surround(t_map *m)
{
	t_queue	*pivotals;

	pivotals = set_pivotal_cells();
	best_surround(m, pivotals);
}

static void			cell_cluster_num(t_map *m, int i, int j)
{
	t_cell		*cell;

	cell = &m->cells[i][j];
	if (cell->val == m->opponent_cell)
	{
		if (cell->cluster_num == -1)
		{
			init_diag_vals();
			set_cl_num_recursive(m, i, j);
			set_best_surround(m);
			++m->cluster_count;
		}
	}
	else if (cell->val == m->player_cell)
	{
		if (cell->pos != POS_NONE)
			push_cell(g_qpl, i, j, 0);
	}
	else
		set_direction_dist(m, cell, i, j);
}

void				set_clusters_num(t_map *m)
{
	g_qop = ft_qnew();
	g_qpl = ft_qnew();
	mat_foreach(cell_cluster_num, m, m->n, m->m);
}
