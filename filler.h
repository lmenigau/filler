/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 02:35:32 by lmenigau          #+#    #+#             */
/*   Updated: 2017/05/01 23:33:49 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <sys/types.h>
# include <unistd.h>
# include <sys/uio.h>
# include "libft.h"

typedef struct	s_vec
{
	int		x;
	int		y;
}				t_vec;

typedef struct	s_psize
{
	int		x;
	int		y;
	int		header_length;
}				t_psize;

typedef struct	s_bound
{
	t_vec	start;
	t_vec	size;
}				t_bound;

typedef struct	s_piece
{
	char		*buff;
	t_bound		bound;
	t_psize		size;
}				t_piece;

typedef struct	s_map
{
	char	*buff;
	char	player_char;
	char	enemy_char;
	t_psize	size;
}				t_map;

int				iter_piece(t_map *map, t_piece *piece, t_vec pos);
t_bound			normalise_piece(char *buff, t_psize piece_size);
t_vec			place(t_map *map, t_piece *piece);
int				read_input(char *buff, size_t max_read);
char			read_player(t_map *map);
t_psize			parse_header(size_t offset);
t_vec			find_enemy(t_map *map, char *map_buff, t_vec pos);
#endif
