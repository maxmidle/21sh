NAME = 21sh

INCLUDE = sh.h

FLAG = -Wall -Wextra -Werror

TERMCAP = termcap/tc_readline.c termcap/tc_copypaste.c termcap/tc_stop.c \
	termcap/tc_write.c termcap/tc_endhome.c termcap/tc_history.c \
	termcap/tc_move.c termcap/tc_readhd.c

TERMOBJS = tc_readline.o tc_copypaste.o tc_stop.o tc_write.o tc_endhome.o \
	tc_history.o tc_move.o tc_readhd.o

SRCS = sh.c run_bin.c read_line.c tilde.c env.c env_verif.c cd.c echo.c \
	dollar.c run_cmd.c handle_line.c chain_list.c chain_list2.c ft_is.c \
	run_proc_cmd.c file_fun.c quote.c free_chain.c syntax.c

OBJS = $(SRCS:.c=.o) $(TERMOBJS)

LIB = -L libft -lft

all: $(NAME)

$(NAME): $(SRCS) $(TERMCAP)
	@make -C libft
	@gcc $(FLAG) -c $(SRCS) $(TERMCAP)
	@gcc $(FLAG) -o $(NAME) $(OBJS) $(LIB) -l termcap
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
