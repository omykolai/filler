/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:02:00 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/20 18:26:36 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/process.h"

void				push_cell(t_queue *q, int i, int j, int size)
{
	t_tuple *t;

	t = (t_tuple*)malloc(sizeof(t_tuple));
	t->x = i;
	t->y = j;
	ft_qpush(q, t, size);
}

static t_listval	*get_lval(int dist, t_cell_pos p, t_cell *c, t_qparams *q)
{
	t_listval	*res;
	t_listval	*val;

	res = (t_listval*)malloc(sizeof(t_listval));
	res->dist = dist;
	res->pos = p;
	if (q->cell->val == 0 || q->cell->cluster_num != q->cl_num)
	{
		val = find_val(q->cell->dists, q->cl_num, 30);
		if (val->pos != 30)
		{
			res->surr_level = val->surr_level * 0.7f;
			res->max_level = val->max_level;
			return (res);
		}
	}
	if (c->max_level)
	{
		res->surr_level = *c->max_level - c->surr_level;
		res->max_level = *c->max_level + 1;
		return (res);
	}
	res->max_level = 1;
	res->surr_level = 0;
	return (res);
}

static bool			lst_add_start(t_cell *c, t_cell_pos pos, t_qparams *p,
	int dist)
{
	ft_lstadd(&c->dists,
		ft_lstnew(get_lval(dist, pos, c, p), p->cl_num));
	return (true);
}

bool				lst_add_sorted(t_cell *c, t_cell_pos pos, t_qparams *p,
	int dist)
{
	t_list	*cur;
	t_list	*next;

	if (!c)
		return (false);
	cur = c->dists;
	if (!cur)
		return (lst_add_start(c, pos, p, dist));
	while (cur)
	{
		next = cur->next;
		if (next && (int)next->value_size == p->cl_num)
			return (false);
		if (!next || (int)next->value > dist)
		{
			cur->next = ft_lstnew(get_lval(dist, pos, c, p), p->cl_num);
			cur->next->next = next;
			return (true);
		}
		cur = next;
	}
	return (false);
}

t_listval			*find_val(t_list *dists, int cl_num, t_cell_pos p)
{
	t_listval	*res;

	while (dists)
	{
		if ((int)dists->value_size == cl_num)
			return ((t_listval*)dists->value);
		dists = dists->next;
	}
	res = (t_listval*)malloc(sizeof(t_listval));
	res->dist = 0;
	res->pos = p;
	return (res);
}
