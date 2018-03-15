# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/08 17:59:46 by tjeanner          #+#    #+#              #
#    Updated: 2018/03/15 11:43:26 by hbouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		rtv1

SRC =		main.c \
			vector_math.c \
			useless_functions.c \
			events.c \
			events_sel.c \
			events_rotation.c \
			events_move.c \
			color_math.c \
			distances_functions.c \
			parser.c \
			fill_env.c \
			get_scene.c \
			norm_manip.c \
			update_and_copy.c \
			generator.c \
			parser_json.c \
			fill_json.c \
			parse_function.c \
			get_scene_json.c \
			get_value_json.c \
			valid_json.c \

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -Ofast -march=native -flto -g3 -fsanitize=address 

SRCDIR =	srcs
INCDIR =	incs
OBJDIR =	objs
SDLDIR =	~/Library/Frameworks

INCFILE = $(addprefix $(INCDIR)/,$(NAME).h)

OBJ =		$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

FT =		libft
FT_LNK =	-L $(FT) -lft
FT_INC =	-I $(addprefix $(FT)/,$(INCDIR))
FT_LIB =	$(addprefix $(FT)/,libft.a)

SDL =		sdl/SDL2.framework/Headers
SDL_LNK =	sdl/SDL2.framework/SDL2
SDL_INC =	-I $(SDL)

all: obj
	@echo "Libft all rule :"
	@make -C $(FT)
	@echo "\nRtv1 all rule :"
	@$(MAKE) $(NAME)
	@echo ""

obj:
	@mkdir -p $(OBJDIR)
	@rm -rf $(SDLDIR)
	@mkdir -p $(SDLDIR)
	@cp -R sdl/SDL2.framework ~/Library/Frameworks

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCFILE)
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) $(SDL_INC) -o $@ -c $<

$(NAME): $(OBJ) $(FT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(SDL_LNK) $(FT_LNK) -lm -o $(NAME)

norme:
	@norminette $(addprefix $(SRCDIR)/,$(SRC))
	@norminette $(addprefix $(INCDIR)/,$(NAME).h)
	@make norme -C libft
	@echo ""
	cat -e auteur

clean:
	@echo "Rtv1 clean rule :"
	rm -rf $(OBJDIR)
	@echo "\nLibft clean rule :"
	@make -C $(FT) clean
	@echo ""

fclean:
	@echo "Rtv1 fclean rule :"
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	@echo "\nLibft fclean rule :"
	@make -C $(FT) fclean

re: fclean all
