# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/23 04:51:21 by hbouchet          #+#    #+#              #
#    Updated: 2018/05/02 16:10:26 by hbouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

SRC =			ft_memset.c					\
				ft_freedoublearray.c		\
				ft_bzero.c					\
				ft_memcpy.c					\
				ft_memccpy.c				\
				ft_memmove.c				\
				ft_memchr.c					\
				ft_memcmp.c					\
				ft_strlen.c					\
				ft_strdup.c					\
				ft_strcpy.c					\
				ft_strncpy.c				\
				ft_strcat.c					\
				ft_strncat.c				\
				ft_strlcat.c				\
				ft_strchr.c					\
				ft_strrchr.c				\
				ft_strstr.c					\
				ft_strnstr.c				\
				ft_strcmp.c					\
				ft_strncmp.c				\
				ft_atoi.c					\
				ft_isalpha.c				\
				ft_isdigit.c				\
				ft_isalnum.c				\
				ft_isascii.c				\
				ft_isprint.c				\
				ft_toupper.c				\
				ft_strtolower.c				\
				ft_tolower.c				\
				ft_memalloc.c				\
				ft_memdel.c					\
				ft_strnew.c					\
				ft_strdel.c					\
				ft_strclr.c					\
				ft_striter.c				\
				ft_striteri.c				\
				ft_strmap.c					\
				ft_strmapi.c				\
				ft_strequ.c					\
				ft_strnequ.c				\
				ft_strsub.c					\
				ft_strjoin.c				\
				ft_strjoinfree.c			\
				ft_strtrim.c				\
				ft_strsplit.c				\
				ft_itoa.c					\
				ft_putchar.c				\
				ft_putchar_fd.c				\
				ft_putstr.c					\
				ft_putstr_fd.c				\
				ft_putendl.c				\
				ft_putendl_fd.c				\
				ft_putnbr.c					\
				ft_putnbr_fd.c				\
				ft_lstnew.c					\
				ft_lstdelone.c				\
				ft_lstdel.c					\
				ft_lstadd.c					\
				ft_lstiter.c				\
				ft_lstmap.c					\
				ft_putnbrbase.c				\
				ft_putnbrbase_fd.c			\
				ft_itoabase.c				\
				ft_sqrt.c					\
				ft_bubble_sort.c			\
				get_next_line.c				\
				ft_pow.c					\
				ft_atof.c					\
				ft_puterr.c					\

CC =			gcc
CFLAGS =	-Wall -Wextra -Werror #-Igsl/include
CFLAGS +=	-Ofast -march=native -flto
#CFLAGS +=	-g3 -fsanitize=address
#LFLAGS =	-Lgsl/lib -lgsl #-lgslcblas

SRCDIR =		srcs
INCDIR =		incs
OBJDIR =		objs

INCFILE =		$(addprefix $(INCDIR)/,$(NAME:.a=.h))

OBJ =			$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all:			obj
				@$(MAKE) $(NAME)

obj:
				@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(INCFILE)
				$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME):		$(OBJ)
				@echo ""
				ar rc $(NAME) $(OBJ)
				@echo ""
				ranlib $(NAME)

norme:
				@norminette $(addprefix $(SRCDIR)/,$(SRC))
				@norminette $(INCFILE)

clean:
				rm -rf $(OBJDIR)

fclean:			clean
				rm -f $(NAME)

re:				fclean all
