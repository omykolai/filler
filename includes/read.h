/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:30:55 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 14:44:58 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H
# include <stdbool.h>
# include "filler.h"

typedef enum	e_ctype
{
	C_MAP,
	C_PIECE
}				t_ctype;

typedef struct	s_direct
{
	t_tuple		*horiz;
	t_tuple		*vert;
	t_tuple		*diag_up;
	t_tuple		*diag_down;
}				t_direct;

extern t_direct	g_direct;

bool			read_map(t_map *m);
bool			read_piece(t_piece *p);
void			adjust_piece(t_piece *p);

int				next_int(char **str);
int				next_cell(char **str, const char c[3]);
void			flush_line(void);

bool			set_cell(int *cell, int val);
void			set_cell_pos(t_map *m, int i, int j);
void			sections_set(t_map *m, int i, int j);
void			sections_init(t_map *m, t_list **pl_node, t_list **op_node);
void			set_direction_start(t_map *m, int i, int j, bool is_op);
char			*init_row(char **line, void **cells, int m, t_ctype t);

#endif
