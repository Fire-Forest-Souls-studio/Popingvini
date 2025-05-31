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
		vector<RectangleShape> m_RS_background;

		ImageButton m_B_custom;
		ImageButton m_B_integrated;

		Texture m_T_background;

		float m_f_speed_move;
		float m_f_frame_transition;
		float m_f_speed_transition;
		float m_f_frame_animation;
		float m_f_speed_animation;
		float m_f_y_position_background;

		Vector2f m_V2f_background_size;
		Vector2f m_V2f_button_size;
		Vector2f m_V2f_button_spacing;

		Color m_C_button_color;

		unsigned m_u_cout_frames;

		PersonMenu ();

		static PersonMenu* m_class_obj;

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

		static vector<RectangleShape>& getBackground ();

		static Texture& getTextureBackground ();

		static ImageButton& getCustom ();
		static ImageButton& getIntegrated ();

		static Vector2f& getButtonSize ();

		static Color& getButtonColor ();

		static float& getFrameTransition ();
		static float& getSpeedTransition ();
};

#endif
