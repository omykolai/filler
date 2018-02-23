/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:39:04 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/22 13:46:39 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "filler.h"

extern t_queue		*g_qop;
extern t_queue		*g_qpl;
extern t_queue		*g_qpiece[17];

typedef struct	s_result
{
	t_tuple		position;
	int			value;
}				t_result;

typedef	struct	s_listval
{
	int			dist;
	t_cell_pos	pos;
	int			surr_level;
	int			max_level;
}				t_listval;

typedef struct	s_qparams
{
	t_listval	*val;
	int			cl_num;
	t_cell		*cell;
	t_cell_pos	valid_pos;
}				t_qparams;

typedef struct	s_dictionary
{
	t_list		**cells;
	float		*vals;
	int			*keys;
	int			count;
}				t_dictionary;

typedef struct	s_piece_val
{
	t_dictionary	left;
	t_dictionary	right;
	t_dictionary	top;
	t_dictionary	bottom;
	t_dictionary	topleft;
	t_dictionary	topright;
	t_dictionary	botleft;
	t_dictionary	botright;
	t_dictionary	*op_dists;
}				t_piece_val;

typedef struct	s_diag_vals
{
	t_tuple		imax;
	t_tuple		imin;
	t_tuple		jmax;
	t_tuple		jmin;
	t_queue		*pivotals;
}				t_diag_vals;

extern t_piece_val	g_pval;
extern t_map		*g_m;
extern t_piece		*g_p;
extern int			g_max_dist;

void			process_result(t_tuple *t, t_result *res);
void			process_else_result(t_tuple *t, t_result *res);
void			process_cell(int i, int j);
void			qpush_opponent_surrounds(t_map *m, int i, int j, int cl_num);
void			qpush_player_surrounds(t_map *m, int i, int j);
void			set_piece_queue(t_piece *p);
void			push_cell(t_queue *q, int i, int j, int size);
void			mat_foreach(void (*f)(), void *mat, int n, int m);
void			set_clusters_num(t_map *m);
void			init_diag_vals(void);
void			set_diag_vals(t_map *m, int i, int j);
t_queue			*set_pivotal_cells(void);
void			best_surround(t_map *m, t_queue *pivotals);
void			set_direction_dist(t_map *m, t_cell *c, int i, int j);
void			piece_cell_pos(t_piece *p, int i, int j);
bool			lst_add_sorted(t_cell *c, t_cell_pos pos, t_qparams *p, int dist
);
bool			check_piece(int x, int y);
int				count_dist_opponnent(void);
int				count_dist_border(t_dictionary *d);
int				piece_count_val(void);
t_listval		*find_val(t_list *dists, int cl_num, t_cell_pos p);
void			pval_init(t_map *m, bool only_count);
void			dict_addcat(t_dictionary *d, int k, float v);
void			dict_addmax(t_dictionary *d, int k, float v);

#endif
