/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivotal_cells.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:56:15 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/22 13:51:02 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/process.h"

static t_diag_vals	g_diagvals;

static inline void	set_pos(t_tuple *pos, int i, int j)
{
	pos->x = i;
	pos->y = j;
}

static bool			is_border(t_map *m, int i, int j)
{
	if (i != 0 && m->cells[i - 1][j].val != m->opponent_cell)
		return (true);
	if (j != 0 && m->cells[i][j - 1].val != m->opponent_cell)
		return (true);
	if (i != m->n - 1 && m->cells[i + 1][j].val != m->opponent_cell)
		return (true);
	if (j != m->m - 1 && m->cells[i][j + 1].val != m->opponent_cell)
		return (true);
	return (false);
}

void				init_diag_vals(void)
{
	g_diagvals.jmax.x = -1;
	g_diagvals.imax.y = -1;
	g_diagvals.imin.x = -1;
	g_diagvals.imin.y = -1;
	g_diagvals.jmax.x = -1;
	g_diagvals.jmax.y = -1;
	g_diagvals.jmin.x = -1;
	g_diagvals.jmin.y = -1;
	g_diagvals.pivotals = ft_qnew();
}

void				set_diag_vals(t_map *m, int i, int j)
{
	t_tuple t;

	if (i == 0 || j == 0 || i == m->n - 1 || j == m->m - 1)
		if (is_border(m, i, j))
		{
			set_pos(&t, i, j);
			ft_qpush(g_diagvals.pivotals, &t, sizeof(t_tuple));
		}
	if (i <= g_diagvals.imin.x || g_diagvals.imin.x == -1)
		set_pos(&g_diagvals.imin, i, j);
	if (i >= g_diagvals.imax.x || g_diagvals.imax.x == -1)
		set_pos(&g_diagvals.imax, i, j);
	if (j <= g_diagvals.jmin.y || g_diagvals.jmin.x == -1)
		set_pos(&g_diagvals.jmin, i, j);
	if (j >= g_diagvals.jmax.y || g_diagvals.jmax.x == -1)
		set_pos(&g_diagvals.jmax, i, j);
}

t_queue				*set_pivotal_cells(void)
{
	int		idif;
	int		jdif;

	if (!g_diagvals.pivotals->first)
	{
		idif = g_diagvals.imax.x - g_diagvals.imin.x;
		jdif = g_diagvals.jmax.y - g_diagvals.jmin.y;
		if (idif < jdif)
		{
			g_diagvals.imin = g_diagvals.jmin;
			g_diagvals.imax = g_diagvals.jmax;
		}
		ft_qpushcopy(g_diagvals.pivotals, &g_diagvals.imin, sizeof(t_tuple));
		ft_qpushcopy(g_diagvals.pivotals, &g_diagvals.imax, sizeof(t_tuple));
	}
	return (g_diagvals.pivotals);
}
