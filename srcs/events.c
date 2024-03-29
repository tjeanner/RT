/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 03:42:05 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	aliasing_ev(t_env *env, unsigned int sym)
{
	if (sym == SDLK_KP_MINUS && env->effects.alias > 1)
		env->effects.alias /= 2.0;
	if (sym == SDLK_KP_PLUS && env->effects.alias <= 4)
		env->effects.alias *= 2.0;
}

static int	events_obj_mod(t_env *env, unsigned int sym, SDL_Event event)
{
	if (sym == SDLK_MINUS && env->objs.curr >= 0)
	{
		if (env->objs.obj[env->objs.curr].radius > 0.6)
			env->objs.obj[env->objs.curr].radius -= 0.5;
	}
	else if (sym == SDLK_MINUS && env->objs.curr == -2)
		env->lums.lum[env->lums.curr].coef /= (
			env->lums.lum[env->lums.curr].coef > 0) ? 1.1000000 : 10;
	else if (sym == SDLK_EQUALS && env->objs.curr >= 0)
	{
		if (env->objs.obj[env->objs.curr].type == CONE &&
			env->objs.obj[env->objs.curr].radius < 89.5)
			env->objs.obj[env->objs.curr].radius += 0.5;
		else if (env->objs.obj[env->objs.curr].type != CONE)
			env->objs.obj[env->objs.curr].radius += 10;
	}
	else if (sym == SDLK_EQUALS && env->objs.curr == -2)
		env->lums.lum[env->lums.curr].coef *= 1.1000000;
	else if (event.type == SDL_KEYDOWN && (sym == SDLK_KP_MINUS
			|| sym == SDLK_KP_PLUS))
		aliasing_ev(env, sym);
	else
		return (0);
	return (1);
}

static int	events_random(t_env *env, unsigned int sym, SDL_Event event)
{
	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		|| event.type == SDL_QUIT)
	{
		ft_putendl("yolo");
		env->state = 1;
		return (0);
	}
	else if (event.type == SDL_KEYDOWN && sym == SDLK_m)
	{
		ft_memdel((void **)&env->objs.obj);
		ft_memdel((void **)&env->cams.cam);
		ft_memdel((void **)&env->lums.lum);
		free(env->effects.filter);
		j_init(env);
	}
	else if (event.type == SDL_KEYDOWN && sym == SDLK_END)
		j_scene_generator(env);
	else if (event.type == SDL_KEYDOWN && sym == SDLK_8)
		create_torus(env);
	else if (sym == SDLK_SPACE && event.key.state == SDL_RELEASED)
		env->screen.play = !env->screen.play;
	else
		return (0);
	return (1);
}

static int	prep_events(t_env *env, SDL_Event event)
{
	env->cams.cam[env->cams.curr].vcam =
		vect_norm(env->cams.cam[env->cams.curr].vcam);
	env->cams.cam[env->cams.curr].v2cam =
		vect_norm(env->cams.cam[env->cams.curr].v2cam);
	env->cams.cam[env->cams.curr].v3cam =
		vect_norm(env->cams.cam[env->cams.curr].v3cam);
	return (event.key.keysym.sym);
}

int			events(t_env *env)
{
	SDL_Event		event;
	unsigned int	sym;
	t_cam			*cam;
	t_obj			*obj;

	cam = &env->cams.cam[env->cams.curr];
	obj = &env->objs.obj[env->objs.curr];
	if (SDL_PollEvent(&event) != 0 || env->screen.play)
	{
		sym = prep_events(env, event);
		if (events_random(env, sym, event) || events_sel(env, event, sym))
			;
		else if (event.type == SDL_KEYDOWN && (events_obj_mod(env, sym, event)
			|| events_rotation(env, sym, &obj->norm)
			|| events_move(env, sym, cam, obj)))
			;
		else if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0)
			mouse_move(env, event, &env->cams.cam[env->cams.curr],
						&env->objs.obj[env->objs.curr]);
		else if (event.type == SDL_KEYDOWN && !move_events(env, sym))
			;
		ev_screen(env, event);
		thread_create(env);
	}
	return (1);
}
