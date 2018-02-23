/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:33:29 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 14:48:27 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/process.h"

t_queue	*g_qpiece[17];

static void		q_init(void)
{
	int i;

	i = -1;
	while (++i < 17)
		g_qpiece[i] = ft_qnew();
}

static void		qpush_piece(t_piece *p, int i, int j)
{
	t_cell	*c;

	c = &p->cells[i][j];
	if ((c->pos & TOP) && (c->pos & LEFT))
		push_cell(g_qpiece[BOTTOM | RIGHT], i, j, 0);
	else if ((c->pos & TOP) && (c->pos & RIGHT))
		push_cell(g_qpiece[BOTTOM | LEFT], i, j, 0);
	else if ((c->pos & BOTTOM) && (c->pos & LEFT))
		push_cell(g_qpiece[TOP | RIGHT], i, j, 0);
	else if ((c->pos & BOTTOM) && (c->pos & RIGHT))
		push_cell(g_qpiece[TOP | LEFT], i, j, 0);
	else if (c->pos & LEFT)
		push_cell(g_qpiece[RIGHT], i, j, 0);
	else if (c->pos & RIGHT)
		push_cell(g_qpiece[LEFT], i, j, 0);
	else if (c->pos & TOP)
		push_cell(g_qpiece[BOTTOM], i, j, 0);
	else if (c->pos & BOTTOM)
		push_cell(g_qpiece[TOP], i, j, 0);
	else if (c->val == 1)
		push_cell(g_qpiece[16], i, j, 0);
}

void			set_piece_queue(t_piece *p)
{
	q_init();
	mat_foreach(piece_cell_pos, p, p->n, p->m);
	mat_foreach(qpush_piece, p, p->n, p->m);
}
