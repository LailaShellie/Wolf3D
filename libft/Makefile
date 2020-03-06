# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lshellie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 19:27:10 by lshellie          #+#    #+#              #
#    Updated: 2019/06/02 13:17:36 by lshellie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFILE = ft_isalpha.c ft_lstadd.c ft_lstnew.c ft_memcpy.c ft_putchar_fd.c \
		ft_putstr.c ft_strcmp.c ft_striter.c ft_strmap.c ft_strnequ.c \
		ft_strstr.c ft_isascii.c ft_lstdel.c ft_memalloc.c ft_memdel.c \
		ft_putendl.c ft_putstr_fd.c ft_strcpy.c ft_striteri.c ft_strmapi.c \
		ft_strnew.c ft_strsub.c ft_atoi.c ft_isdigit.c ft_lstdelone.c \
		ft_memccpy.c ft_memmove.c ft_putendl_fd.c ft_strcat.c ft_strdel.c \
		ft_strjoin.c ft_strncat.c ft_strnstr.c ft_strtrim.c ft_bzero.c \
		ft_isprint.c ft_lstiter.c ft_memchr.c ft_memset.c ft_putnbr.c \
		ft_strchr.c ft_strdup.c ft_strlcat.c ft_strncmp.c ft_strrchr.c \
		ft_tolower.c ft_isalnum.c ft_lstmap.c ft_memcmp.c \
		ft_putchar.c ft_putnbr_fd.c ft_strclr.c ft_strequ.c \
		ft_strlen.c ft_strncpy.c ft_strsplit.c ft_toupper.c ft_sqrt.c \
		ft_strstr_kmp.c ft_zfunc.c ft_is_prime.c ft_gcd.c ft_fast_bin_pow.c ft_fast_bit_pow.c \
		get_next_line.c ft_abs.c ft_free_mas.c ft_itoa.c ft_atod.c ft_isnumber.c \
		ft_trim_stop.c count_split.c

OFILE = $(CFILE:.c=.o)

HFILE = libft.h

all: $(NAME)

$(NAME): $(OFILE)
	@ar rc $(NAME) $(OFILE)
	@ranlib $(NAME)

%.o: %.c $(HFILE)
	@gcc -Wall -Werror -Wextra -g3 -I $(HFILE) -c $< -o $@

clean:
	@/bin/rm -f $(OFILE)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
