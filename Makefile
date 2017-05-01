#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/18 02:18:30 by lmenigau          #+#    #+#             *#
#*   Updated: 2017/05/02 01:51:03 by lmenigau         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	= lmenigau.filler
SRC		= filler.c algo.c piece.c reading.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -Ilibft/
LFLAGS	= -lft
LDFLAGS	= -Llibft/
LIBDIR	= libft/
LIB		:= $(LIBDIR)/libft.a

.PHONY	:	all clean fclean re lib

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(LIB)
			$(CC) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o $@ $(OBJ)

$(LIB)	:	$(LIBDIR)
			$(MAKE) -C $(LIBDIR)

clean	:
			$(RM) $(OBJ)
			$(MAKE) -C $(LIBDIR) fclean

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
