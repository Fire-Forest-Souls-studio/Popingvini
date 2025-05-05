/*
 * Copyright 2025 Fire-Forest-Souls-studio
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef CODE_WINDOW_AND_STYLES_H_
#define CODE_WINDOW_AND_STYLES_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

#include "../../includes/Classes/button.h"

using namespace sf;
using namespace std;

// start

enum StyleWindow
{
	Default = 0, // 0
	Fullscreen   // 1
};

class WindowAndStyles
{
	private:
		WindowAndStyles ();

		static WindowAndStyles* class_obj;

		const Vector2f m_f_SIZE_PIX;

		RectangleShape m_rectangle_shape;

		RenderWindow m_render_window;

		RenderTexture m_render_texture;

		StyleWindow m_style_window;

		VideoMode m_video_mode;

		View m_view;

		float m_f_time_since_clicking;

		wstring m_w_game_name;

		const Color m_C_DEFOLT_WINDOW;
		Color m_C_clear_color;

		Image m_image;

		static void main_time_work ();
		static void main_F11 ();
		static void main_event ();
		static void clear_clear ();
		static void clear_rectangle ();
		static void clear_draw ();
		static void clear_display ();
		static void main_destroy ();
		static void draw (const Button&);

	protected:
		static WindowAndStyles* getClass ();

	public:
		static void start ();
		static void main ();
		static void clear ();
		static void setColor (Color);
		static void close ();

		static bool isOpen ();
		static bool hasFocus ();

		static float getFactorX ();
		static float getFactorY ();
		static float getPixelsSizeX ();
		static float getPixelsSizeY ();

		static Window& getWindow ();

		static FloatRect getGlobalBounds ();

		static Color getDefoultColor ();
};

#endif /* WINDOW_AND_STYLES_H_ */
