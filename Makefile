# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/17 15:38:14 by tkiselev          #+#    #+#              #
#    Updated: 2018/05/20 18:20:01 by tkiselev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc -Wall -Wextra -Werror
NAME=tkiselev.filler
VISUALIZATOR=visualizator
LIBA=libft.a
LIBFT_PATH=libft
SRCS=arrays.c piece.c piece2.c staff.c tkiselev_filler.c preparation.c
V_SCRS=$(addprefix visualize/,visual.c visual_prepare.c visual_staff.c)

all: $(NAME) $(VISUALIZATOR)

$(VISUALIZATOR): $(V_SRCS)
	$(CC) $(V_SRCS) -I ../$(LIBFT_PATH) ../$(LIBFT_PATH)/$(LIBA) -lncurses -o $(VISUALIZATOR)

$(NAME): $(LIBA) $(SRCS)
	$(CC) -o $(NAME) $(SRCS) -L $(LIBFT_PATH) -lft -I $(LIBFT_PATH)

$(LIBA):
	make -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)

fclean: 
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all
