/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:18:16 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 14:34:23 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../get_next_line/get_next_line.h"
#include "../../includes/read.h"

static bool		read_board_info(int *n, int *m, char *preword)
{
	char	*line;
	char	*iline;

	get_next_line(0, &line);
	if (line)
	{
		iline = line + ft_strlen(preword);
		*n = next_int(&iline);
		*m = next_int(&iline);
		free(line);
	}
	else
		return (false);
	return (*n >= 0 && *m >= 0);
}

void			read_player_info(t_map *m)
{
	char	*line;
	int		player;

	m->cells = NULL;
	get_next_line(0, &line);
	if (line && (ft_strlen(line) <= 10 || !ft_isdigit(line[11])))
	{
		player = line[10] - '0';
		free(line);
		if (player == 1 || player == 2)
		{
			m->player_cell = -player;
			m->opponent_cell = -(player == 1 ? 2 : 1);
			return ;
		}
	}
	ft_putstr("Bad player info\n");
	exit(EXIT_FAILURE);
}

bool			set_map(t_map *m, t_piece *p)
{
	if (!read_board_info(&m->n, &m->m, "Plateau "))
		return (false);
	if (!read_map(m))
		return (false);
	if (!read_board_info(&p->n, &p->m, "Piece "))
		return (false);
	if (!read_piece(p))
		return (false);
	return (true);
}
