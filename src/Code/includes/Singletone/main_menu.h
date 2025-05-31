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
		static MainMenu* m_class_obj;

		RectangleShape m_RS_popingvini;
		RectangleShape m_RS_title;

		ImageButton m_B_popingvinit;
		ImageButton m_B_sdatca;
		ImageButton m_B_wardrobe;

		unsigned m_u_cout_frame_popingvini;

		short int m_si_reverse;

		float m_f_frame_popingvini;
		float m_f_speed_anim_popingvini;
		float m_f_speed_move_ice;
		float m_f_chance_reverse;

		Vector2f m_V2f_popingvini_defoult;
		Vector2f m_V2f_popingvinit_button;
		Vector2f m_V2f_sdatca_button;
		Vector2f m_V2f_title;
		Vector2f m_V2f_wardrobe_button;
		Vector2f m_V2f_popingvini_size;
		Vector2f m_V2f_popingvinit_button_size;
		Vector2f m_V2f_sdatca_button_size;
		Vector2f m_V2f_title_size;
		Vector2f m_V2f_wardrobe_button_size;
		Vector2f m_V2f_background_size;
		Vector2f m_V2f_ice_size;

		vector<RectangleShape> m_RS_background;
		vector<RectangleShape> m_RS_ice;

		Color m_C_chice_button;

		Texture m_T_background;
		Texture m_T_ice;
		Texture m_T_popingvini;
		Texture m_T_title;

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
