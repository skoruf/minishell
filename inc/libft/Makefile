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
AR     = ar rcs
CFLAGS = -Wall -Wextra -Werror
NAME   = libft.a
CFILES = ft_is_alnum_alpha_ascii_digit_print.c\
		 ft_mem_chr_cmp_cpy_move_set.c\
		 ft_putfd_char_endl_nbr_str.c\
		 ft_str_len_chr_rchr_iteri_mapi.c\
		 ft_str_dup_join_lcat_lcpy_ncmp.c\
		 ft_str_join_trim_with_free.c\
		 ft_bzero_calloc_strnstr_tolower_toupper.c\
		 ft_atoi_itoa.c\
		 ft_substr.c\
		 ft_strtrim.c\
		 ft_split.c\
		 ft_printf.c\
		 ft_wrappers.c\
		 get_next_line.c
OFILES = $(CFILES:.c=.o)
BCFILES= ft_lst_new_addfront_addback_size_last.c\
		 ft_lst_delone_clear_iter_map.c
BOFILES= $(BCFILES:.c=.o)
DEPS   = libft.h ft_printf.h
%.o	: %.c $(DEPS)
	@cc $(CFLAGS) $< $@
	
all: $(NAME)

$(NAME): $(OFILES)
	@$(AR) $(NAME) $(OFILES)
	
bonus: $(BOFILES) 
	@$(AR) $(NAME) $(BOFILES)
	
clean:
	@rm -f $(OFILES) $(BOFILES)
fclean:	clean
	@rm -f $(NAME)
re: fclean all
.PHONY:  all bonus clean fclean re

