#ifndef CODE_LEARN_MENU_H_
#define CODE_LEARN_MENU_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "../Classes/image_button.h"
#include "../Classes/work.h"

class LearnMenu
{
	private:
		static LearnMenu* m_class_obj;

		RectangleShape m_rectangle_shape;

		Text m_text;

		ImageButton m_button;

		float m_f_text_size;
		float m_f_left0;
		float m_f_left1;
		float m_f_left2;

		LearnMenu ();

	protected:
		static LearnMenu* getClass ();

	public:
		static Work* work;

		static void destroy ();
		static void main ();
		static void setWork (Work& work);

		static ImageButton& getButton ();

		static RectangleShape getRectangleShape ();

		static Text getText ();
};

#endif
