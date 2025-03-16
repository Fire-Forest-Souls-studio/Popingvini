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
	private:

		static TestMenu* class_obj;

		Text T_question;

		vector <TextButton> _text_button;

		RectangleShape RS_image;
		RectangleShape RS_image_long;

		wstring w_add;

		int i_up;
		int i_between;
		int i_left;

		float f_text_size;
		float f_wight_simbol;
		float f_time;
		float f_score;

		Vector2f V2f_image_size;

		Color C_background;
		Color C_question;
		Color C_answer_select;
		Color C_answer_unselect;

		size_t st_question;

		unsigned u_true;
		unsigned u_cout;

		TestMenu ();

	protected:

		static TestMenu* getClass ();

	public:

		static void destroy ();
		static void main ();
		static void setZeroQuestion ();
		static void setLanguageTexture (const Texture&);

		static vector <TextButton>& getButtons ();

		static RectangleShape getRectangleShapeImage ();
		static RectangleShape getRectangleShape ();

		static Text getTextQuestion ();
};

#endif
