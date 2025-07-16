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

struct AnimPingvinon
{
		Texture texture;
		float f_move_speed;
		float f_frame_cout;
		float f_animation_speed;
};
struct Pingvinon
{
		RectangleShape rectangle;
		unsigned u_anim_pingvinon;
		int i_flip;
		float f_posx;
		float f_frame;
};

class Introduction
{
	private:
		static Introduction* m_class_obj;

		Introduction ();

	protected:
		static const unsigned m_u_NEW_PINGVINON;
		static const unsigned m_u_REVERS;
		static const unsigned m_u_EMOTION;
		static const unsigned m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO;
		static const unsigned m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL;
		static const unsigned m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL;
		static const unsigned m_u_FRAME_FOR_LIGHT_OUT;
		static const unsigned m_u_FRAME_FOR_LIGHT_FULL_OUT;
		static const Vector2f m_V2f_PINGVINON_DEFOLT_SIZE;
		static const float m_f_PINGVINON_DEFOLT_Y;
		static const float m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION;
		static RectangleShape m_RS_anim;
		static RectangleShape m_RS_light;
		static Texture m_T_anim;
		static Texture m_T_light;
		static vector<Pingvinon> m_pingvonon;
		static vector<AnimPingvinon> m_anim_pingvinon;
		static float m_f_frame_for_fire_forest_souls_studio;

		static void main_if_introduction ();
		static void main_if_loading_or_introduction ();

	public:
		static Introduction* getClass ();

		static void main ();

		static RectangleShape& getSprite ();
		static const RectangleShape& getAnimSprite ();
		static const RectangleShape& getLightSprite ();

		static vector<Pingvinon>& getPingvinons ();

		static FloatRect getGlobalBounds ();

		static size_t size_sprites;
};

#endif
