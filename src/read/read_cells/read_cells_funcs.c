/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cells_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:04:51 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 14:40:28 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../includes/read.h"
#include "../../../get_next_line/get_next_line.h"

char		*init_row(char **line, void **cells, int m, t_ctype t)
{
	char	*iline;

	get_next_line(0, line);
	if (!*line)
		return (NULL);
	if (!*(t_cell**)cells)
		*(t_cell**)cells = (t_cell*)malloc(sizeof(t_cell) * m);
	if (t == C_MAP)
	{
		iline = *line;
		next_int(&iline);
		return (iline);
	}
	return (*line);
}

int			next_cell(char **str, const char c[3])
{
	++*str;
	if (ft_tolower(*(*str - 1)) == c[0])
		return (0);
	if (ft_tolower(*(*str - 1)) == c[1])
		return (c[2] > 0 ? -1 : 1);
	if (ft_tolower(*(*str - 1)) == c[2] && c[2] > 0)
		return (-2);
	return (-3);
}

bool		set_cell(int *cell, int val)
{
	*cell = val;
	return (val != -3);
}
