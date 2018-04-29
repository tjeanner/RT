# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/08 17:59:46 by tjeanner          #+#    #+#              #
#    Updated: 2018/04/28 17:35:40 by vmercadi         ###   ########.fr        #
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
			norm_manip.c \
			update_and_copy.c \
			generator_json.c \
			generator_json2.c \
			parser_json.c \
			parser_init.c \
			parser.c \
			parser_fill_json.c \
			parser_function.c \
			parser_get_scene.c \
			parser_get_value.c \
			parser_get_value2.c \
			parser_valid_json.c \
			parser_free.c	\
			filter.c \
			filter2.c \
			raytracing.c \
			error_mgt.c \
			UI_button.c \
			UI_error.c \
			UI_help.c \
			UI_id.c \
			UI_init.c \
			UI_input.c \
			UI_main.c \
			UI_onglet.c \

#			UI_event.c

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
CFLAGS +=	-march=native -flto
CFLAGS +=	-g3 -fsanitize=address

SRCDIR =	srcs
INCDIR =	incs
OBJDIR =	objs
# SDLDIR =	~/Library/Frameworks

INCFILE = $(addprefix $(INCDIR)/,$(NAME).h)

OBJ =		$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

FT =		libft
FT_LNK =	-L $(FT) -lft
FT_INC =	-I $(addprefix $(FT)/,$(INCDIR))
FT_LIB =	$(addprefix $(FT)/,libft.a)

# SDL =		sdl/SDL2.framework/Headers
# SDL_LNK =	sdl/SDL2.framework/SDL2
# SDL_INC =	-I $(SDL)
SDL2LIB		= $(shell sdl2-config --libs) -L ~/.brew/Cellar/sdl2_ttf/2.0.14/lib/
SDL2CFLAGS	= $(shell sdl2-config --cflags) -I ~/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL
SDL2TTFLIB	= -lSDL2_ttf

ifeq "$(shell brew info sdl2 | grep -o 'Not installed')" "Not installed"
INSTALL1	= install1
else
INSTALL1	=
endif

ifeq "$(shell brew info sdl2_ttf | grep -o 'Not installed')" "Not installed"
INSTALL2	= install2
else
INSTALL2	=
endif

ifeq "$(shell brew info imagemagick | grep -o 'Not installed')" "Not installed"
INSTALL3	= install3
else
INSTALL3	=
endif

all: obj
	@echo "Libft all rule :"
	@make -C $(FT)
	@echo "\nRtv1 all rule :"
	@$(MAKE) $(NAME)
	@echo ""

obj: $(INSTALL1) $(INSTALL2) $(INSTALL3)
	@mkdir -p $(OBJDIR)
	# @rm -rf $(SDLDIR)
	# @mkdir -p $(SDLDIR)
	# @cp -R sdl/SDL2.framework ~/Library/Frameworks

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCFILE)
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) $(SDL_INC) -o $@ -c $< $(SDL2CFLAGS)

$(NAME): $(OBJ) $(FT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(SDL_LNK) $(FT_LNK) -lm -o $(NAME) $(SDL2LIB) $(SDL2TTFLIB)

install1:
	@brew install sdl2

install2:
	@brew install sdl_ttf

install3:
	@brew install imagemagick

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
