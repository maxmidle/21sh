NAME = 21sh

INCLUDE = 21sh.h

FLAG = -Wall -Wextra -Werror

SRCS = 21sh.c run_bin.c read_line.c tilde.c env.c env_verif.c cd.c echo.c \
	dollar.c run_cmd.c handle_line.c chain_list.c ft_is.c

OBJS = $(SRCS:.c=.o)

LIB = -L libft -lft

all: $(NAME)

$(NAME): $(SRCS)
	@make -C libft
	@gcc $(FLAG) -c $(SRCS)
	@gcc $(FLAG) -o $(NAME) $(OBJS) $(LIB)
	@echo "\033[32m21sh............[OK]\033[0m"

clean:
	@rm -f $(OBJS)
	@make clean -C libft
	@echo "\033[31m21sh............[clean]\033[0m"

fclean:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	@make fclean -C libft
	@echo "\033[31m21sh............[fclean]\033[0m"

re: fclean all	
