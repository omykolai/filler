/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:07:41 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/17 18:18:46 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/process.h"

static void	qpush_player(t_map *m, t_cell *src, int i, int j)
{
	t_cell	*c;

	if (i >= m->n || j >= m->m || i < 0 || j < 0)
		return ;
	c = &m->cells[i][j];
	if (c->val == m->player_cell)
	{
		if (c->pos == POS_NONE)
		{
			c->depth = src->depth + 1;
			push_cell(g_qpl, i, j, 0);
		}
		if (c->depth > src->depth)
			c->pos |= src->pos;
	}
}

void		qpush_player_surrounds(t_map *m, int i, int j)
{
	t_cell		*c;
	int			k;
	int			n;

	c = &m->cells[i][j];
	k = -2;
	while (++k < 2)
	{
		n = -2;
		while (++n < 2)
			qpush_player(m, c, i + n, j + k);
	}
}
