/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:06:19 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/20 18:29:27 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/process.h"

static inline void	set_cell_dist(t_list *dists)
{
	int		d;
	int		k;

	while (dists)
	{
		d = ((t_listval*)dists->value)->dist;
		k = dists->value_size;
		dict_addcat(&g_pval.op_dists[k], g_max_dist - d, 1.f +
			(g_max_dist - d) * (((t_listval*)dists->value)->surr_level /
			(float)((t_listval*)dists->value)->max_level));
		dists = dists->next;
	}
}

int					count_dist_opponnent(void)
{
	int				i;
	int				j;
	int				max;
	int				res;
	t_dictionary	*d;

	i = -1;
	res = 0;
	while (++i < g_m->cluster_count)
	{
		j = -1;
		max = 0;
		d = &g_pval.op_dists[i];
		while (++j < d->count)
		{
			if (d->vals[d->keys[j]] * d->keys[j] > max)
				max = d->vals[d->keys[j]] * d->keys[j];
			d->vals[d->keys[j]] = 0;
		}
		d->count = 0;
		res += max;
	}
	return (res);
}

int					count_dist_border(t_dictionary *d)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (++i < d->count)
	{
		res += d->vals[d->keys[i]];
		d->vals[d->keys[i]] = 0;
	}
	d->count = 0;
	return (res);
}

int					piece_count_val(void)
{
	int		val;

	val = 1;
	val += count_dist_border(&g_pval.left);
	val += count_dist_border(&g_pval.right);
	val += count_dist_border(&g_pval.top);
	val += count_dist_border(&g_pval.bottom);
	val += count_dist_border(&g_pval.topleft);
	val += count_dist_border(&g_pval.topright);
	val += count_dist_border(&g_pval.botleft);
	val += count_dist_border(&g_pval.botright);
	val += count_dist_opponnent();
	return (val);
}

void				process_cell(int i, int j)
{
	t_cell	*c;
	int		idown;

	idown = i - j > 0 ? g_m->m + i - j - 1 : j - i;
	c = &g_m->cells[i][j];
	set_cell_dist(c->dists);
	dict_addmax(&g_pval.left, i, c->bord.left);
	dict_addmax(&g_pval.right, i, c->bord.right);
	dict_addmax(&g_pval.top, j, c->bord.top);
	dict_addmax(&g_pval.bottom, j, c->bord.bottom);
	dict_addmax(&g_pval.topleft, idown, c->bord.topleft);
	dict_addmax(&g_pval.topright, i + j, c->bord.topright);
	dict_addmax(&g_pval.botleft, i + j, c->bord.botleft);
	dict_addmax(&g_pval.botright, idown, c->bord.botright);
}
