/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:56:44 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/22 21:44:31 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/filler.h"
#include "ft_printf/includes/ft_printf.h"

int		main(void)
{
	t_map		m;
	t_piece		p;
	t_tuple		result;

	read_player_info(&m);
	while (set_map(&m, &p))
	{
		result = process(&m, &p);
		ft_printf("%d %d\n", result.x, result.y);
	}
	return (0);
}
