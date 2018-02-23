/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:03:14 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/17 17:31:16 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/process.h"

t_piece_val		g_pval;
t_map			*g_m;
t_piece			*g_p;
int				g_max_dist;

static void			set_opponent_distance(t_map *m)
{
	t_list	*node;
	t_tuple	*t;

	while ((node = ft_qpopnode(g_qop)))
	{
		t = (t_tuple*)node->value;
		qpush_opponent_surrounds(m, t->x, t->y, node->value_size);
	}
}

static void			set_player_queue(t_map *m)
{
	t_list	*node;
	t_tuple *t;

	node = g_qpl->first;
	while (node)
	{
		t = (t_tuple*)node->value;
		qpush_player_surrounds(m, t->x, t->y);
		node = node->next;
	}
}

static void			result_init(t_result *res, t_map *m, t_piece *p, t_list **n)
{
	*n = g_qpl->first;
	g_m = m;
	g_p = p;
	g_max_dist = (m->n > m->m ? m->n : m->m);
	res->position.x = 0;
	res->position.y = 0;
	res->value = INT_MIN;
}

t_tuple				process(t_map *m, t_piece *p)
{
	t_result	res;
	t_list		*node;
	t_tuple		*t;

	set_clusters_num(m);
	set_opponent_distance(m);
	set_player_queue(m);
	set_piece_queue(p);
	result_init(&res, m, p, &node);
	pval_init(m, false);
	while (node)
	{
		t = (t_tuple*)node->value;
		process_result(t, &res);
		node = node->next;
	}
	while (res.value < 0 && (t = (t_tuple*)ft_qpop(g_qpl)))
		process_else_result(t, &res);
	return (res.position);
}

void				mat_foreach(void (*f)(), void *mat, int n, int m)
{
	int i;
	int j;

	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < m)
			f(mat, i, j);
	}
}
