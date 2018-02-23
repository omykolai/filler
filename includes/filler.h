/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:43:46 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/20 18:24:09 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include <stdbool.h>
# include "../libft/libft.h"
# include "structs.h"

typedef struct	s_cell
{
	int			val;
	int			cluster_num;
	int			depth;
	float		surr_level;
	float		*max_level;
	t_cell_pos	pos;
	t_list		*dists;
	t_border	bord;
}				t_cell;

typedef struct	s_map
{
	int			m;
	int			n;
	int			player_cell;
	int			opponent_cell;
	int			cluster_count;
	t_cell		**cells;
}				t_map;

typedef struct	s_piece
{
	int			m;
	int			n;
	t_cell		**cells;
	t_tuple		*piece_section;
}				t_piece;

void			read_player_info(t_map *m);
bool			set_map(t_map *m, t_piece *p);
t_tuple			process(t_map *m, t_piece *p);
void			free_cells(t_cell **cells, int n);

void			exit_error(char *m);

#endif
