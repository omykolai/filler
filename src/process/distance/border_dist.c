/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:25:41 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/15 17:43:37 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/read.h"

static inline void	set_direct(t_tuple *t, int val, bool is_op)
{
	if (!t->x)
	{
		if (!is_op)
			t->x = -1;
		else
			t->x = val + 1;
	}
	t->y = is_op ? val + 1 : 0;
}

static inline bool	check_bord(int bord, int val)
{
	if (val > 0 && bord > val + 1)
		return (true);
	if (val < 0 && bord < 0 && bord > val - 1)
		return (true);
	return (false);
}

static inline int	min(int a, int b)
{
	return (a > b ? b : a);
}

void				set_direction_start(t_map *m, int i, int j, bool is_op)
{
	int	idown;

	idown = i - j > 0 ? m->m + i - j - 1 : j - i;
	set_direct(g_direct.vert + j, i, is_op);
	set_direct(g_direct.horiz + i, j, is_op);
	set_direct(g_direct.diag_up + i + j, i, is_op);
	set_direct(g_direct.diag_down + idown, i, is_op);
	ft_bzero(&m->cells[i][j].bord, sizeof(t_border));
}

void				set_direction_dist(t_map *m, t_cell *c, int i, int j)
{
	int	idown;

	idown = i - j > 0 ? m->m + i - j - 1 : j - i;
	if (check_bord(g_direct.vert[j].x, i))
		c->bord.top = i;
	else if (check_bord(-g_direct.vert[j].y, -i))
		c->bord.bottom = m->n - i - 1;
	if (check_bord(g_direct.horiz[i].x, j))
		c->bord.left = j;
	else if (check_bord(-g_direct.horiz[i].y, -j))
		c->bord.right = m->m - j - 1;
	if (check_bord(g_direct.diag_up[i + j].x, i))
		c->bord.topright = min(i, m->m - j - 1);
	else if (check_bord(-g_direct.diag_up[i + j].y, -i))
		c->bord.botleft = min(m->n - i - 1, j);
	if (check_bord(g_direct.diag_down[idown].x, i))
		c->bord.topleft = min(i, j);
	else if (check_bord(-g_direct.diag_down[idown].y, -i))
		c->bord.botright = min(m->m - j - 1, m->n - i - 1);
}
