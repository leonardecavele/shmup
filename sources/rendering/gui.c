/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:26:36 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/30 18:30:20 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "game.h"
#include <math.h>

static void display_hp(int hp, int x)
{
	if (hp == HERO_HP)
	{
		attron(COLOR_PAIR(1));
		for (int i = 0; i < HERO_MAX_HP; ++i)
		{
			mvprintw(0, (x >> 2) + HERO_MAX_HP + i, "%c", (i < hp ? HERO : ' '));
		}
		attroff(COLOR_PAIR(1));
	}
	else if (hp > (HERO_MAX_HP >> 1))
	{
		attron(COLOR_PAIR(3));
		for (int i = 0; i < HERO_MAX_HP; ++i)
		{
			mvprintw(0, (x >> 2) + HERO_MAX_HP + i, "%c", (i < hp ? HERO : ' '));
		}
		attroff(COLOR_PAIR(3));
	}
	else
	{
		attron(COLOR_PAIR(2));
		for (int i = 0; i < HERO_MAX_HP; ++i)
		{
			mvprintw(0, (x >> 2) + HERO_MAX_HP + i, "%c", (i < hp ? HERO : ' '));
		}
		attroff(COLOR_PAIR(2));
	}
}

static void display_score(int score, int x)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(5));
	mvprintw(0, (x >> 1) - 1, "%d %c", score, KEY);
	attroff(COLOR_PAIR(5));
	attroff(A_BOLD);
}

static void display_ammo(int ammo, int x)
{
	if (ammo == MAX_PROJECTILES)
	{
		attron(COLOR_PAIR(1));
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			mvprintw(0, (x >> 1) + (x >> 2) - (MAX_PROJECTILES) + i, "%c", (i < ammo ? 'Z' : ' '));
		}
		attroff(COLOR_PAIR(1));
	}
	else if (ammo > (MAX_PROJECTILES >> 1))
	{
		attron(COLOR_PAIR(3));
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			mvprintw(0, (x >> 1) + (x >> 2) - (MAX_PROJECTILES) + i, "%c", (i < ammo ? 'Z' : ' '));
		}
		attroff(COLOR_PAIR(3));
	}
	else
	{
		attron(COLOR_PAIR(2));
		for (int i = 0; i < MAX_PROJECTILES; ++i)
		{
			mvprintw(0, (x >> 1) + (x >> 2) - (MAX_PROJECTILES) + i, "%c", (i < ammo ? 'Z' : ' '));
		}
		attroff(COLOR_PAIR(2));
	}
}

extern void	display_gui(t_game *game)
{
	int x, y, hp, score, ammo;
	getmaxyx(stdscr, y, x);
	(void)y;

	hp = game->entities[0].hp;
	score = game->score;
	ammo = MAX_PROJECTILES - game->entities[0].active_proj_qty;

	display_hp(hp, x);
	display_score(score, x);
	display_ammo(ammo, x);
	
	// munitions
	// boss_hp
	// attack direction
}
