/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:03:48 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/17 18:13:20 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/process.h"

static bool	check_cell(int i, int j, int *pl_count)
{
	if (i >= g_m->n || j >= g_m->m || i < 0 || j < 0)
		return (false);
	if (g_m->cells[i][j].val == g_m->player_cell)
		++*pl_count;
	else if (g_m->cells[i][j].val != 0)
		return (false);
	return (*pl_count < 2);
}

bool		check_piece(int x, int y)
{
	t_tuple s;
	int		i;
	int		j;
	int		pl_count;

	if (x < 0 || y < 0)
		return (false);
	i = -1;
	pl_count = 0;
	while (++i < g_p->n)
	{
		s = g_p->piece_section[i];
		j = s.x - 1;
		while (j != -2 && ++j <= s.y)
			if (!check_cell(i + x, j + y, &pl_count))
				return (false);
	}
	return (pl_count == 1);
}
