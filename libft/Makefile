# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: radler <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 18:33:34 by radler            #+#    #+#              #
#    Updated: 2018/06/21 21:20:27 by radler           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE = ft_printf.h

FLAG = -Wall -Werror -Wextra

SRCS = argform.c argtype1.c argtype2.c argtype3.c argtype4.c ft_itoa_base.c \
	ft_printf.c handleflag.c hashtag.c minsize.c precision.c spaceplus.c \
	zero.c ft_is.c

OBJET = $(SRCS:.c=.o)

$(NAME): $(SRCS)
	@make -C libft
	@mv libft/libft.a ./$(NAME)
	@gcc $(FLAG) -c $(SRCS)
	@ar rc $(NAME) $(OBJET)
	@ranlib $(NAME)
	@echo "\033[32mft_printf.......[OK]\033[0m"

all: $(NAME)

clean:
	@make clean -C libft
	@rm -f $(OBJET)
	@echo "\033[31mft_printf.......[clean]\033[0m"

fclean:
	@make fclean -C libft
	@rm -f $(OBJET)
	@rm -f $(NAME)
	@echo "\033[31mft_printf.......[fclean]\033[0m"

re:fclean all

lib: $(NAME) clean
