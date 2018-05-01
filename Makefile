# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/08 17:59:46 by tjeanner          #+#    #+#              #
#    Updated: 2018/05/01 18:17:22 by vmercadi         ###   ########.fr        #
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
			parseur_obj.c \

			# action.c	\

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror #-Igsl/include
CFLAGS +=	-Ofast -march=native -flto
#CFLAGS +=	-g3 #-fsanitize=address
#LFLAGS =	-Lgsl/lib -lgsl #-lgslcblas

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

ifeq "$(shell brew info imagemagick | grep -o 'Not installed')" "Not installed"
MAGICK	= magick
else
MAGICK	=
endif

all: obj
	@echo "Libft all rule :"
	@make -C $(FT)
	@echo "\nRtv1 all rule :"
	@$(MAKE) $(NAME)
	@echo ""

obj: $(MAGICK)
	@mkdir -p $(OBJDIR)
	@rm -rf $(SDLDIR)
	@mkdir -p $(SDLDIR)
	@cp -R sdl/SDL2.framework ~/Library/Frameworks

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCFILE)
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) $(SDL_INC) -o $@ -c $<

$(NAME): $(OBJ) $(FT_LIB)
	$(CC) $(LFLAGS) $(OBJ) $(SDL_LNK) $(FT_LNK) -lm -o $(NAME)

magick:
	@brew install imagemagick

film:
	@mkdir -p /tmp/Screenshots/videos
	@brew install ffmpeg
	@find /tmp/Screenshots/ -type f -name '*.bmp' -exec convert {} {}.jpg \;
	@ffmpeg -r 25 -f image2 -s 960x720 -i /tmp/Screenshots/Screenshot%d.bmp.jpg \
	-vcodec libx264 -crf 25  -pix_fmt yuv420p /tmp/Screenshots/videos/$(TIME).mp4
	@rm /tmp/Screenshots/*.bmp
	@echo "\033[32;3mA video have been created in /tmp/Screenshots/videos/ !\x1b[0m"

cleanfilm:
	@rm -rf /tmp/Screenshots

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
