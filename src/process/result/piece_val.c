/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:44:54 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/20 18:09:37 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/process.h"

static inline void	dict_init(t_dictionary *a, int n, bool only_count)
{
	a->count = 0;
	if (only_count)
		return ;
	a->vals = (float*)ft_memalloc(sizeof(float) * n);
	a->keys = (int*)ft_memalloc(sizeof(int) * n);
}

static void			dict_set_key(t_dictionary *a, int k)
{
	int		i;

	i = -1;
	while (++i < a->count && a->keys[i] != k)
		;
	if (i == a->count)
	{
		++a->count;
		a->keys[i] = k;
	}
}

void				pval_init(t_map *m, bool only_count)
{
	int	i;

	dict_init(&g_pval.left, m->n, only_count);
	dict_init(&g_pval.right, m->n, only_count);
	dict_init(&g_pval.top, m->m, only_count);
	dict_init(&g_pval.bottom, m->m, only_count);
	dict_init(&g_pval.topleft, m->n + m->m - 1, only_count);
	dict_init(&g_pval.topright, m->n + m->m - 1, only_count);
	dict_init(&g_pval.botleft, m->n + m->m - 1, only_count);
	dict_init(&g_pval.botright, m->n + m->m - 1, only_count);
	g_pval.op_dists = (t_dictionary*)malloc(sizeof(t_dictionary)
		* m->cluster_count);
	i = -1;
	while (++i < m->cluster_count)
		dict_init(&g_pval.op_dists[i], m->n > m->m ? m->n : m->m, only_count);
}

void				dict_addcat(t_dictionary *d, int k, float v)
{
	dict_set_key(d, k);
	d->vals[k] += v;
}

void				dict_addmax(t_dictionary *d, int k, float v)
{
	dict_set_key(d, k);
	if (d->vals[k] < v)
		d->vals[k] = v;
}
