/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:32:18 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 14:40:06 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/read.h"

static bool	read_piece_row(t_piece *p, int i, char *line, const char c[3])
{
	int		j;

	j = -1;
	p->piece_section[i].x = -1;
	p->piece_section[i].y = p->m - 1;
	while (++j < p->m)
	{
		if (!set_cell(&p->cells[i][j].val, next_cell(&line, c)))
			return (false);
		if (p->cells[i][j].val)
		{
			if (p->piece_section[i].x == -1)
				p->piece_section[i].x = j;
			p->piece_section[i].y = p->m - 1;
		}
		else if (p->piece_section[i].y == p->m - 1)
			p->piece_section[i].y = j - 1;
	}
	return (true);
}

bool		read_piece(t_piece *p)
{
	const char	c[] = { '.', '*', -1 };
	char		*line;
	char		*iline;
	int			i;
	bool		res;

	p->cells = (t_cell**)ft_memalloc(sizeof(t_cell*) * p->n);
	p->piece_section = (t_tuple*)malloc(sizeof(t_tuple) * p->n);
	i = -1;
	while (++i < p->n)
	{
		if (!(iline = init_row(&line, (void**)&p->cells[i], p->m, C_PIECE)))
			return (false);
		res = read_piece_row(p, i, iline, c);
		free(line);
		if (!res)
			return (false);
	}
	return (true);
}
