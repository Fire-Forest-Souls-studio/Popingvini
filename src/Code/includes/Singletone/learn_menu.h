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

		static LearnMenu* class_obj;

		RectangleShape rectangle_shape_obj;

		Text text_obj;

		ImageButton button_obj;

		float f_text_size;
		float f_left0;
		float f_left1;
		float f_left2;

		LearnMenu ();

	protected:

		static LearnMenu* getClass ();

	public:

		static Work* work;

		static void destroy ();
		static void main ();
		static void setWork (Work&);

		static ImageButton& getButton ();

		static RectangleShape getRectangleShape ();

		static Text getText ();
};

#endif
