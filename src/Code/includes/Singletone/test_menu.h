/*
 * Copyright 2025 Fire-Forest-Souls-studio
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef CODE_TEST_MENU_H_
#define CODE_TEST_MENU_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "../Classes/text_button.h"

class TestMenu
{
		// TODO: добавить названия аргументам функций по шаблону <my_name>

	private:
		static TestMenu* class_obj;

		Text m_T_question;

		vector<TextButton> m_text_button;

		RectangleShape m_RS_image;
		RectangleShape m_RS_image_long;

		const wstring m_w_ADD;

		const int m_i_UP;
		const int m_i_BETWEEN;
		const int m_i_LEFT;

		const float m_f_TEXT_SIZE;
		const float m_f_WIGHT_SIMBOL;
		float m_f_time;
		float m_f_score;

		const Vector2f m_V2f_IMAGE_SIZE;

		const Color m_C_BACKGROUND;
		const Color m_C_QUESTION;
		const Color m_C_ANSWER_SELECT;
		const Color m_C_ANSWER_UNSELECT;

		size_t m_st_question;

		unsigned m_u_true;
		unsigned m_u_cout;

		TestMenu ();

	protected:
		static TestMenu* getClass ();

	public:
		static void destroy ();
		static void main ();
		static void setZeroQuestion ();
		static void setLanguageTexture (const Texture&);

		static vector<TextButton>& getButtons ();

		static RectangleShape getRectangleShapeImage ();
		static RectangleShape getRectangleShape ();

		static Text getTextQuestion ();
};

#endif
