#ifndef PERSON_MENU_H_
#define PERSON_MENU_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

#include "../Classes/image_button.h"

using namespace sf;
using namespace std;

class PersonMenu
{

	private:

		vector <RectangleShape> RS_background;

		ImageButton B_custom;
		ImageButton B_integrated;

		Texture T_background;

		float f_speed_move;
		float f_frame_transition;
		float f_speed_transition;
		float f_frame_animation;
		float f_speed_animation;
		float f_y_position_background;

		Vector2f V2f_background_size;
		Vector2f V2f_button_size;
		Vector2f V2f_button_spacing;

		Color C_button_color;

		unsigned u_cout_frames;

		PersonMenu ();

		static PersonMenu* class_obj;

		static void main_load ();
		static void main_transitionTo ();
		static void main_main ();
		static void main_transitionOf ();
		static void main_forAllMenu ();

	protected:

		static PersonMenu* getClass ();

	public:

		static void destroy ();
		static void main ();

		static vector <RectangleShape>& getBackground ();

		static Texture& getTextureBackground ();

		static ImageButton& getCustom ();
		static ImageButton& getIntegrated ();

		static Vector2f& getButtonSize ();

		static Color& getButtonColor ();

		static float& getFrameTransition ();
		static float& getSpeedTransition ();
};

#endif
