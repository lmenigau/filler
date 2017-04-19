/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 02:35:32 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/19 22:26:29 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE	(4096 * 16)

typedef	 struct	s_vec
{
	int		x;
	int		y;
}				t_vec;

typedef	 struct	s_psize
{
	int		x;
	int		y;
	int		header_length;
}				t_psize;

typedef struct	s_map
{
	char	buff[BUFF_SIZE];

	char	player_char;
	size_t	buff_size;
	t_psize	size;
	size_t	buff_length;
}				t_map;
#endif