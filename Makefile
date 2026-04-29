# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efoyer <efoyer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/29 11:40:45 by efoyer            #+#    #+#              #
#    Updated: 2026/04/29 12:44:08 by efoyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	codexion

SRCDIR		=	src
OBJDIR		=	obj

SRC			=	init.c parsing.c \
				codexion.c
OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

HEADER		=	src/codexion.h

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread -g3 -I./includes

RM			=	rm -f
MKDIR		=	mkdir -p

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER) | $(OBJDIR)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
				$(MKDIR) $(OBJDIR)

clean:
				$(RM) $(OBJ)
				$(RM) -r $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re