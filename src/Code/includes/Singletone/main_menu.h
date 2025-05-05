#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

#include "../Classes/image_button.h"

using namespace sf;
using namespace std;

class MainMenu
{

	private:
		static MainMenu* class_obj;

		RectangleShape RS_popingvini;
		RectangleShape RS_title;

		ImageButton B_popingvinit;
		ImageButton B_sdatca;
		ImageButton B_wardrobe;

		unsigned u_cout_frame_popingvini;

		short int si_reverse;

		float f_frame_popingvini;
		float f_speed_anim_popingvini;
		float f_speed_move_ice;
		float f_chance_reverse;

		Vector2f V2f_popingvini_defoult;
		Vector2f V2f_popingvinit_button;
		Vector2f V2f_sdatca_button;
		Vector2f V2f_title;
		Vector2f V2f_wardrobe_button;
		Vector2f V2f_popingvini_size;
		Vector2f V2f_popingvinit_button_size;
		Vector2f V2f_sdatca_button_size;
		Vector2f V2f_title_size;
		Vector2f V2f_wardrobe_button_size;
		Vector2f V2f_background_size;
		Vector2f V2f_ice_size;

		vector<RectangleShape> RS_background;
		vector<RectangleShape> RS_ice;

		Color C_chice_button;

		Texture T_background;
		Texture T_ice;
		Texture T_popingvini;
		Texture T_title;

		MainMenu ();

		static void main_load ();
		static void main_transition ();
		static void main_transform ();

	protected:
		static MainMenu* getClass ();

	public:
		static void main ();

		static void destroy ();

		static vector<RectangleShape>& getBackground ();
		static vector<RectangleShape>& getIce ();

		static RectangleShape& getPopingvini ();
		static RectangleShape& getTitle ();

		static ImageButton& getPopingvinit ();
		static ImageButton& getSdatca ();
		static ImageButton& getWardrobe ();

		static Texture& getTextureBackground ();
		static Texture& getTextureIce ();
		static Texture& getTexturePopingvini ();
		static Texture& getTextureTitle ();
};

#endif
