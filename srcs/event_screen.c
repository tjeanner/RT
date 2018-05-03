/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:44:31 by vmercadi          #+#    #+#             */
/*   Updated: 2018/05/03 04:01:57 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Dans After effect : File->import->import multiple files | ET BIM une vidéo.
** Ou make film
*/

void	ev_screen(t_env *env, SDL_Event event)
{
	int		ev;

	ev = event.key.keysym.sym;
	if (ev == SDLK_x)
		ev_screenshot(env);
	else if (ev == SDLK_z)
		env->screen.rec = !env->screen.rec;
}

/*
** Take a screenshot and save it with current date and time
** bmp to jpg : find . -type f -name '*.bmp' -exec convert {} {}.jpg \;
*/

void	ev_screenshot(t_env *env)
{
	SDL_Renderer	*renderer;
	SDL_Surface		*screen;
	char			*name;

	name = ft_strdup("/tmp/Screenshots/Screenshot");
	name = ft_strjoin(name, ft_itoa(env->screen.time++));
	name = ft_strjoin(name, ".bmp");
	renderer = SDL_GetRenderer(env->display.win);
	screen = SDL_CreateRGBSurface(0, WIN_X, WIN_Y,
						32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
											screen->pixels, screen->pitch);
	SDL_SaveBMP(screen, name);
	ft_strdel(&name);
	SDL_FreeSurface(screen);
}
