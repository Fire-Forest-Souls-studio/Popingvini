/*
 * Copyright 2025 Fire-Forest-Souls-studio
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef CODE_INTRODUCTION_H_
#define CODE_INTRODUCTION_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

//start

struct AnimPingvinon
{
		Texture T;
		float f_move_speed;
		float f_frame_cout;
		float f_animation_speed;
};
struct Pingvinon
{
		RectangleShape RS;
		unsigned u_anim_pingvinon;
		int i_flip;
		float f_posx;
		float f_frame;
};

class Introduction
{

	private:

		static Introduction *class_obj;

		Introduction ();

	protected:

		RectangleShape m_rectsangle_shape;

		Texture m_texture;

		vector <Pingvinon> m_pingvonon;

		vector <AnimPingvinon> m_anim_pingvinon;

		const float m_f_PINGVINON_DEFOLT_Y;
		const float m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION;
		float m_f_frame_for_fire_forest_souls_studio;

		const Vector2f m_V2f_PINGVINON_DEFOLT_SIZE;

		const unsigned m_u_NEW_PINGVINON;
		const unsigned m_u_REVERS;
		const unsigned m_u_EMOTION;
		const unsigned m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO;
		const unsigned m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL;
		const unsigned m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL;

		static void main_if_introduction ();
		static void main_if_loading_or_introduction ();

	public:

		static Introduction* getClass ();

		static void main ();

		static RectangleShape& getSprite ();
		static vector <Pingvinon>& getPingvinons ();

		static FloatRect getGlobalBounds ();

		static size_t size_sprites;

};

#endif
