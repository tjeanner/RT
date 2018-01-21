# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/08 17:59:46 by tjeanner          #+#    #+#              #
#    Updated: 2018/01/22 00:40:50 by tjeanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		rtv1

SRC =		main.c \
			vector_math.c \
			useless_functions.c \

CC =		gcc
FLAGS =		-Wall -Wextra -Werror -g3

SRCDIR =	./srcs
INCDIR =	./incs
OBJDIR =	./obj

OBJ =		$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

FT =		./libft
FT_LNK =	-L $(FT) -lft
FT_INC =	-I $(FT)
FT_LIB =	$(addprefix $(FT)/,libft.a)

SDL =		./sdl/SDL2.framework/Headers
SDL_LNK =	./sdl/SDL2.framework/SDL2
SDL_INC =	-I $(SDL)

all: $(NAME)

$(FT_LIB) :
	@make -C $(FT)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(FLAGS) $(FT_INC) -I $(INCDIR) $(SDL_INC) -o $@ -c $<

$(NAME): $(FT_LIB) obj $(OBJ)
	$(CC) $(OBJ) $(SDL_LNK) $(FT_LNK) -lm -o $(NAME)

norme:
	@norminette $(FT)/srcs
	@norminette $(FT)/includes
	@norminette $(addprefix $(SRCDIR)/,$(SRC))
	@norminette $(addprefix $(INCDIR)/,$(NAME).h)
	cat -e auteur

clean:
	rm -rf $(OBJDIR)
	@make -C $(FT) clean

fclean:
	rm -rf $(LLDB)
	rm -rf $(SANI)
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	@make -C $(FT) fclean

re: fclean all

ultra: re clean
