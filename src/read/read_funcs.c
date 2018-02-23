/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:18:29 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 15:05:40 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/filler.h"
#include "../../get_next_line/get_next_line.h"

void		flush_line(void)
{
	char	*line;

	get_next_line(0, &line);
	free(line);
}

int			next_int(char **str)
{
	int n;

	if (!ft_isdigit(**str))
		return (-1);
	n = ft_atoi(*str);
	while (ft_isdigit(**str))
		++*str;
	++*str;
	return (n);
}
