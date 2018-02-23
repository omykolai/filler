/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:37:50 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 14:48:15 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/process.h"

static void			process_piece(int x, int y, t_result *res)
{
	t_tuple s;
	int		i;
	int		j;
	int		val;

	i = -1;
	while (++i < g_p->n)
	{
		s = g_p->piece_section[i];
		j = s.x - 1;
		while (j != -2 && ++j <= s.y)
			process_cell(i + x, j + y);
	}
	val = piece_count_val();
	if (res->value < val)
	{
		res->value = val;
		res->position.x = x;
		res->position.y = y;
	}
}

static void			process_queue(t_cell *c, t_tuple *tm, t_cell_pos p,
	t_result *res)
{
	t_list	*node;
	t_tuple *tp;

	if ((c->pos & p) || p == CENTR)
	{
		node = g_qpiece[p]->first;
		while (node)
		{
			tp = (t_tuple*)node->value;
			if (check_piece(tm->x - tp->x, tm->y - tp->y))
				process_piece(tm->x - tp->x, tm->y - tp->y, res);
			node = node->next;
		}
	}
}

void				process_result(t_tuple *t, t_result *res)
{
	t_cell	*c;

	c = &g_m->cells[t->x][t->y];
	process_queue(c, t, LEFT, res);
	process_queue(c, t, RIGHT, res);
	process_queue(c, t, TOP, res);
	process_queue(c, t, BOTTOM, res);
	process_queue(c, t, TOP | LEFT, res);
	process_queue(c, t, TOP | RIGHT, res);
	process_queue(c, t, BOTTOM | LEFT, res);
	process_queue(c, t, BOTTOM | RIGHT, res);
}

void				process_else_result(t_tuple *t, t_result *res)
{
	t_cell	*c;

	c = &g_m->cells[t->x][t->y];
	process_queue(c, t, CENTR, res);
}
