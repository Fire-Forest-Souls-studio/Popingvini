/*
 * Copyright 2025 Fire-Forest-Souls-studio
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef CODE_WORKS_MENU_H_
#define CODE_WORKS_MENU_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "../Classes/button.h"
#include "../Classes/language.h"
#include "../Classes/work_block.h"

class WorksMenu
{
	private:
		static WorksMenu* class_obj;

		Text _T_up_panel_left;
		Text _T_up_panel_middle;
		Text _T_up_panel_right;

		Button _B_up_panel;

		RectangleShape _RS_down_panel;

		const float _f_BIG_FONT_SCALE;
		const float _f_MIDDLE_BIG_FONT_SCALE;
		const float _f_MIDDLE_SMALL_FONT_SCALE;
		const float _f_SMALL_FONT_SCALE;
		const float _f_SPEED_MOVE_BLOCKS;
		const float _f_WIGHT_SIMVOL_BIG_FONT;
		const float _f_WIGHT_SIMVOL_MIDDLE_BIG_FONT;
		const float _f_WIGHT_SIMVOL_MIDDLE_SMALL_FONT;
		const float _f_WIGHT_SIMVOL_SMALL_FONT;
		float _f_move_blocks;

		const int _i_OUT_UP;
		const int _i_OUT_LEFT;
		const int _i_OUT_BETWEEN;
		const int _i_IN_UP;
		const int _i_IN_LEFT;
		const int _i_IN_BETWEEN;
		const int _i_BLOCK_UP;
		const int _i_BLOCK_LEFT;
		const int _i_BLOCK_BETWEEN;

		Texture _texture;

		RenderTexture _render_texture;

		View _view;

		Vector2f _V2f_size_up_panel;
		Vector2f _V2f_size_down_panel;
		Vector2f _V2f_size_block_icon;

		vector<WorkBlock> _work_block;

		WorksMenu ();

		static void resizeWindow ();
		static void main_load ();
		static void main_all ();
		static void main_works_menu ();
		static void main_transitionOf ();

	protected:
		static WorksMenu* getClass ();

	public:
		static Language* language;

		static void destroy ();
		static void setLanguage (Language*);
		static void main ();
		static void start ();
		static void clear ();
		static void setMoveBlocks (float);
		static void stringUpdate ();

		static Button& getUpPanel ();

		static Text& getLeftTextUpPanel ();
		static Text& getMiddleTextUpPanel ();
		static Text& getRightTextUpPanel ();

		static RenderTexture& getRender ();

		static RectangleShape& getDownPanel ();

		static int getIOutUp ();
		static int getIOutLeft ();
		static int getIOutBetween ();
		static int getIInUp ();
		static int getIInLeft ();
		static int getIInBetween ();
		static int getBlockUp ();
		static int getBlockLeft ();
		static int getBlockBetween ();

		static Vector2f getSizeBlockIcon ();
		static Vector2f getSizeDownPanel ();

		static Texture& getTexture ();

		static float getBigFontScale ();
		static float getMiddleBigFontScale ();
		static float getMiddleSmallFontScale ();
		static float getSmallFontScale ();
		static float getWidthSimvolBigFont ();
		static float getWidthSimvolMiddleBigFont ();
		static float getWidthSimvolMiddleSmallFont ();
		static float getWidthSimvolSmallFont ();
		static float& getMoveBlocks ();
};

#endif
