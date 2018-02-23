/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:32:05 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/20 13:49:04 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/read.h"

t_direct	g_direct;

static void	init_map_params(t_map *m)
{
	int	diag_n;

	m->cluster_count = 0;
	diag_n = (m->m + m->n - 1);
	if (m->cells)
	{
		ft_bzero(g_direct.horiz, m->n);
		ft_bzero(g_direct.vert, m->m);
		ft_bzero(g_direct.diag_up, diag_n);
		ft_bzero(g_direct.diag_down, diag_n);
	}
	else
	{
		m->cells = (t_cell**)ft_memalloc(sizeof(t_cell*) * m->n);
		g_direct.horiz = (t_tuple*)ft_memalloc(sizeof(t_tuple) * m->n);
		g_direct.vert = (t_tuple*)ft_memalloc(sizeof(t_tuple) * m->m);
		g_direct.diag_up = (t_tuple*)ft_memalloc(sizeof(t_tuple) * diag_n);
		g_direct.diag_down = (t_tuple*)ft_memalloc(sizeof(t_tuple) * diag_n);
	}
}

static bool	read_map_row(t_map *m, int i, char *line, const char c[3])
{
	int			j;
	t_cell		*cells;

	j = -1;
	cells = m->cells[i];
	while (++j < m->m)
	{
		cells[j].dists = NULL;
		cells[j].cluster_num = -1;
		cells[j].depth = 0;
		cells[j].max_level = NULL;
		if (!set_cell(&cells[j].val, next_cell(&line, c)))
			return (false);
		set_cell_pos(m, i, j);
	}
	return (true);
}

bool		read_map(t_map *m)
{
	const char	c[] = { '.', 'o', 'x' };
	char		*line;
	char		*iline;
	int			i;
	bool		res;

	init_map_params(m);
	flush_line();
	i = -1;
	while (++i < m->n)
	{
		if (!(iline = init_row(&line, (void**)&m->cells[i], m->m, C_MAP)))
			return (false);
		res = read_map_row(m, i, iline, c);
		free(line);
		if (!res)
			return (false);
	}
	return (true);
}
