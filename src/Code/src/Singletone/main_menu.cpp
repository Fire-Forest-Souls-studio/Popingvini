#include "../../includes/Singletone/main_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/loading.h"

// private

MainMenu* MainMenu::m_class_obj = NULL;

MainMenu::MainMenu ()
    : m_B_popingvinit ("MM/button/popingvinit"),
      m_B_sdatca ("MM/button/sdatca"),
      m_B_wardrobe ("MM/button/wardrobe"),

      m_u_cout_frame_popingvini (19),

      m_si_reverse (-1),

      m_f_frame_popingvini (0.0),
      m_f_speed_anim_popingvini (5.0),
      m_f_speed_move_ice (0.003),
      m_f_chance_reverse (10000),

      m_V2f_popingvini_defoult (255, 82),
      m_V2f_popingvinit_button (146, 75),
      m_V2f_sdatca_button (146, 96),
      m_V2f_title (146, 15),
      m_V2f_wardrobe_button (54, -16),
      m_V2f_popingvini_size (74, 54),
      m_V2f_popingvinit_button_size (117, 20),
      m_V2f_sdatca_button_size (73, 20),
      m_V2f_title_size (140, 48),
      m_V2f_wardrobe_button_size (17, 16),
      m_V2f_background_size (500, 150),
      m_V2f_ice_size (500, 150),

      m_RS_background (int (WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getGlobalBounds ().height /
                          (m_V2f_background_size.x / WindowAndStyles::getPixelsSizeY ())) +
                     2),
      m_RS_ice (m_RS_background.size ()),

      m_C_chice_button (166, 194, 222, 255)
{
	for (size_t st (0); st < m_RS_background.size (); st++)
	{
		m_RS_background[st].setSize (m_V2f_background_size);
		m_RS_ice[st].setSize (m_V2f_ice_size);
	}
	m_RS_popingvini.setSize (m_V2f_popingvini_size);
	m_B_popingvinit.setSize (m_V2f_popingvinit_button_size);
	m_B_sdatca.setSize (m_V2f_sdatca_button_size);
	m_RS_title.setSize (m_V2f_title_size);
	m_B_wardrobe.setSize (m_V2f_wardrobe_button_size);
}

// protected

MainMenu* MainMenu::getClass ()
{
	if (m_class_obj != NULL)
		return m_class_obj;

	m_class_obj = new MainMenu ();
	return m_class_obj;
}

void MainMenu::main_load ()
{
	MainMenu* MM_ = getClass ();

	if (Loading::getLoad ())
	{
		destroy ();
		MM_->m_B_popingvinit.setTexture ();
		MM_->m_B_sdatca.setTexture ();
		MM_->m_RS_title.setTexture (&MM_->m_T_title);
		MM_->m_RS_popingvini.setTexture (&MM_->m_T_popingvini);
		MM_->m_RS_popingvini.setTextureRect (IntRect (
		    0,
		    0,
		    MM_->m_V2f_popingvini_size.x,
		    MM_->m_V2f_popingvini_size.y));
		MM_->m_B_wardrobe.setTexture ();
	}
}
void MainMenu::main_transition ()
{
	MainMenu* MM_ = getClass ();

	if (names::game_status == GameStatus::loading_to_main_menu)
	{
		for (size_t st (0); st < MM_->m_RS_background.size (); st++)
		{
			MM_->m_RS_background[st].setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
			MM_->m_RS_ice[st].setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		MM_->m_RS_title.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->m_B_popingvinit.getGlobalBounds ()))
		{
			MM_->m_B_popingvinit.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		else
		{
			MM_->m_B_popingvinit.setFillColor (Color (
			    MM_->m_C_chice_button.r,
			    MM_->m_C_chice_button.g,
			    MM_->m_C_chice_button.b,
			    255 - Loading::getFrameTransition ()));
		}
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->m_B_sdatca.getGlobalBounds ()))
		{
			MM_->m_B_sdatca.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		else
		{
			MM_->m_B_sdatca.setFillColor (Color (
			    MM_->m_C_chice_button.r,
			    MM_->m_C_chice_button.g,
			    MM_->m_C_chice_button.b,
			    255 - Loading::getFrameTransition ()));
		}
		MM_->m_RS_popingvini.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->m_B_wardrobe.getGlobalBounds ()))
		{
			MM_->m_B_wardrobe.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		else
		{
			MM_->m_B_wardrobe.setFillColor (Color (
			    MM_->m_C_chice_button.r,
			    MM_->m_C_chice_button.g,
			    MM_->m_C_chice_button.b,
			    255 - Loading::getFrameTransition ()));
		}
	}
}
void MainMenu::main_transform ()
{
	MainMenu* MM_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (names::game_status == GameStatus::loading_to_main_menu or names::game_status == GameStatus::main_menu or names::game_status == GameStatus::main_menu_to_person_menu or names::game_status == GameStatus::works_menu_to_main_menu)
	{

		MM_->m_B_popingvinit.setScale (f);
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->m_B_popingvinit.getGlobalBounds ()))
		{
			MM_->m_B_popingvinit.setPosition (
			    MM_->m_RS_background[0].getPosition ().x + MM_->m_V2f_popingvinit_button.x * f,
			    MM_->m_RS_background[0].getPosition ().y + (MM_->m_V2f_popingvinit_button.y + 1) * f);
			if (names::game_status == GameStatus::main_menu)
			{
				MM_->m_B_popingvinit.setFillColor (MM_->m_C_chice_button);
				if (PC_Mouse::isLeftPressed () and Loading::getFrameTransition () == 0.0)
				{
					names::game_status = GameStatus::main_menu_to_person_menu;
				}
			}
		}
		else
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->m_B_popingvinit.setFillColor (Color (255, 255, 255, 255));
			MM_->m_B_popingvinit.setPosition (
			    MM_->m_RS_background[0].getPosition ().x + MM_->m_V2f_popingvinit_button.x * f,
			    MM_->m_RS_background[0].getPosition ().y + MM_->m_V2f_popingvinit_button.y * f);
		}
		MM_->m_B_sdatca.setScale (f);
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->m_B_sdatca.getGlobalBounds ()))
		{
			MM_->m_B_sdatca.setPosition (
			    MM_->m_RS_background[0].getPosition ().x + MM_->m_V2f_sdatca_button.x * f,
			    MM_->m_RS_background[0].getPosition ().y + (MM_->m_V2f_sdatca_button.y + 1) * f);
			if (names::game_status == GameStatus::main_menu)
			{
				MM_->m_B_sdatca.setFillColor (MM_->m_C_chice_button);
				if (PC_Mouse::isLeftPressed () and Loading::getFrameTransition () == 0.0)
				{
					WindowAndStyles::close ();
				}
			}
		}
		else
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->m_B_sdatca.setFillColor (Color (255, 255, 255, 255));
			MM_->m_B_sdatca.setPosition (
			    MM_->m_RS_background[0].getPosition ().x + MM_->m_V2f_sdatca_button.x * f,
			    MM_->m_RS_background[0].getPosition ().y + MM_->m_V2f_sdatca_button.y * f);
		}
		MM_->m_RS_title.setScale (f, f);
		MM_->m_RS_title.setPosition (MM_->m_RS_background[0].getPosition ().x + MM_->m_V2f_title.x * f,
		                           MM_->m_RS_background[0].getPosition ().y + MM_->m_V2f_title.y * f);
		for (size_t st (0); st < MM_->m_RS_background.size (); st++)
		{
			MM_->m_RS_background[st].setScale (f, f);
			if (st == 0)
			{
				names::SetXCenterPosition (MM_->m_RS_background[st], 0);
			}
			else if (st % 2 == 0)
			{
				MM_->m_RS_background[st].setPosition (MM_->m_RS_background[0].getPosition ().x - MM_->m_RS_background[0].getGlobalBounds ().width * st * 0.5, 0);
			}
			else
			{
				MM_->m_RS_background[st].setPosition (MM_->m_RS_background[0].getPosition ().x + MM_->m_RS_background[0].getGlobalBounds ().width * (st + 1) * 0.5, 0);
			}
			MM_->m_RS_ice[st].setScale (f, f);
			MM_->m_RS_ice[st].setPosition (MM_->m_RS_background[st].getPosition ());
		}

		if (rand () % unsigned (MM_->m_f_chance_reverse / (names::f_time ? names::f_time : 1) + 1) == 0)
		{
			MM_->m_si_reverse *= -1;
		}
		MM_->m_V2f_popingvini_defoult = Vector2f (MM_->m_V2f_popingvini_defoult.x + MM_->m_f_speed_move_ice * MM_->m_si_reverse, MM_->m_V2f_popingvini_defoult.y);
		MM_->m_f_frame_popingvini += MM_->m_f_speed_anim_popingvini * names::f_microsec * names::f_time;
		if (MM_->m_f_frame_popingvini > MM_->m_u_cout_frame_popingvini)
		{
			MM_->m_f_frame_popingvini = 0.0;
		}
		else
		{
			MM_->m_RS_popingvini.setTextureRect (IntRect (
			    0,
			    MM_->m_V2f_popingvini_size.y * unsigned (MM_->m_f_frame_popingvini),
			    MM_->m_V2f_popingvini_size.x,
			    MM_->m_V2f_popingvini_size.y));
		}
		MM_->m_RS_popingvini.setScale (f, f);
		MM_->m_RS_popingvini.setPosition (
		    MM_->m_RS_background[0].getPosition ().x + MM_->m_V2f_popingvini_defoult.x * f,
		    MM_->m_V2f_popingvini_defoult.y * f);
		MM_->m_B_wardrobe.setScale (f);
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->m_B_wardrobe.getGlobalBounds ()))
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->m_B_wardrobe.setFillColor (MM_->m_C_chice_button);
			MM_->m_B_wardrobe.setPosition (
			    MM_->m_RS_popingvini.getPosition ().x + MM_->m_V2f_wardrobe_button.x * f,
			    MM_->m_RS_popingvini.getPosition ().y + (MM_->m_V2f_wardrobe_button.y + 1) * f);
		}
		else
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->m_B_wardrobe.setFillColor (Color (255, 255, 255, 255));
			MM_->m_B_wardrobe.setPosition (
			    MM_->m_RS_popingvini.getPosition ().x + MM_->m_V2f_wardrobe_button.x * f,
			    MM_->m_RS_popingvini.getPosition ().y + MM_->m_V2f_wardrobe_button.y * f);
		}
	}
}

// public
// void

void MainMenu::main ()
{
	main_load ();

	main_transform ();

	main_transition ();
}
void MainMenu::destroy ()
{
	MainMenu* MM_ = getClass ();

	MM_->m_RS_background.resize (int (WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getGlobalBounds ().height /
	                                (MM_->m_V2f_background_size.x / WindowAndStyles::getPixelsSizeY ())) +
	                           2);
	MM_->m_RS_ice.resize (MM_->m_RS_background.size ());

	for (size_t st (0); st < MM_->m_RS_background.size (); st++)
	{
		MM_->m_RS_background[st].setSize (MM_->m_V2f_background_size);
		MM_->m_RS_background[st].setTexture (&MM_->m_T_background, true);
		MM_->m_RS_ice[st].setSize (MM_->m_V2f_ice_size);
		MM_->m_RS_ice[st].setTexture (&MM_->m_T_ice, true);
	}
}

// RectangleShape&

vector<RectangleShape>& MainMenu::getBackground ()
{
	return getClass ()->m_RS_background;
}
vector<RectangleShape>& MainMenu::getIce ()
{
	return getClass ()->m_RS_ice;
}
RectangleShape& MainMenu::getTitle ()
{
	return getClass ()->m_RS_title;
}
RectangleShape& MainMenu::getPopingvini ()
{
	return getClass ()->m_RS_popingvini;
}

// Button&

ImageButton& MainMenu::getPopingvinit ()
{
	return getClass ()->m_B_popingvinit;
}
ImageButton& MainMenu::getSdatca ()
{
	return getClass ()->m_B_sdatca;
}
ImageButton& MainMenu::getWardrobe ()
{
	return getClass ()->m_B_wardrobe;
}

// Texture&

Texture& MainMenu::getTextureBackground ()
{
	return getClass ()->m_T_background;
}
Texture& MainMenu::getTextureIce ()
{
	return getClass ()->m_T_ice;
}
Texture& MainMenu::getTextureTitle ()
{
	return getClass ()->m_T_title;
}
Texture& MainMenu::getTexturePopingvini ()
{
	return getClass ()->m_T_popingvini;
}
