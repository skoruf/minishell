# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 11:52:00 by gwalchsh          #+#    #+#              #
#    Updated: 2023/09/06 11:52:01 by gwalchsh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC     = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = $(CFLAGS) -lreadline
NAME   = minishell
FILES  = utils_list.c \
		minishell.c \
		pwd.c \
		cd.c \
		env.c \
		echo.c \
		export.c \
		export2.c \
		lexing.c \
		insert_env.c \
		insert_env2.c \
		insert_env3.c \
		tokenize.c \
		parsing.c \
		env_utils.c \
		utils.c \
		lexing2.c \
		cmd_table.c \
		cmd_table2.c \
		cmd_table3.c \
		quotes.c \
		exec.c \
		exec2.c \
		exec3.c \
		exec4.c \
		redirect.c \
		init.c \
		init2.c \
		unset.c \
		sort_env.c \
		heredoc.c \
		signal.c \
		ft_atoll.c \
		protect.c \
		exit.c
CFILES = $(addprefix src/, $(FILES))
OFILES = $(addprefix obj/, $(FILES:.c=.o))
DEPS   = inc/minishell.h inc/libft/libft.h
obj/%.o	: src/%.c $(DEPS)
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OFILES)
	@make all -C ./inc/libft
	@$(CC) -o $(NAME) $(OFILES) $(LFLAGS) ./inc/libft/libft.a

clean:
	@make clean -C ./inc/libft
	@rm -f $(OFILES)
	@if [ -d "obj" ]; then rmdir obj; fi

fclean: clean
	@rm -f ./inc/libft/libft.a
	@rm -f $(NAME)
re: fclean all
.PHONY:  all clean fclean re
