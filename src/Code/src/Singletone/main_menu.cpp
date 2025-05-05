#include "../../includes/Singletone/main_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/loading.h"

// private

MainMenu* MainMenu::class_obj = NULL;

MainMenu::MainMenu ()
    : B_popingvinit ("MM/button/popingvinit"),
      B_sdatca ("MM/button/sdatca"),
      B_wardrobe ("MM/button/wardrobe"),

      u_cout_frame_popingvini (19),

      si_reverse (-1),

      f_frame_popingvini (0.0),
      f_speed_anim_popingvini (5.0),
      f_speed_move_ice (0.003),
      f_chance_reverse (10000),

      V2f_popingvini_defoult (255, 82),
      V2f_popingvinit_button (146, 75),
      V2f_sdatca_button (146, 96),
      V2f_title (146, 15),
      V2f_wardrobe_button (54, -16),
      V2f_popingvini_size (74, 54),
      V2f_popingvinit_button_size (117, 20),
      V2f_sdatca_button_size (73, 20),
      V2f_title_size (140, 48),
      V2f_wardrobe_button_size (17, 16),
      V2f_background_size (500, 150),
      V2f_ice_size (500, 150),

      RS_background (int (WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getGlobalBounds ().height /
                          (V2f_background_size.x / WindowAndStyles::getPixelsSizeY ())) +
                     2),
      RS_ice (RS_background.size ()),

      C_chice_button (166, 194, 222, 255)
{
	for (size_t st (0); st < RS_background.size (); st++)
	{
		RS_background[st].setSize (V2f_background_size);
		RS_ice[st].setSize (V2f_ice_size);
	}
	RS_popingvini.setSize (V2f_popingvini_size);
	B_popingvinit.setSize (V2f_popingvinit_button_size);
	B_sdatca.setSize (V2f_sdatca_button_size);
	RS_title.setSize (V2f_title_size);
	B_wardrobe.setSize (V2f_wardrobe_button_size);
}

// protected

MainMenu* MainMenu::getClass ()
{
	if (class_obj != NULL)
		return class_obj;

	class_obj = new MainMenu ();
	return class_obj;
}

void MainMenu::main_load ()
{
	MainMenu* MM_ = getClass ();

	if (Loading::getLoad ())
	{
		destroy ();
		MM_->B_popingvinit.setTexture ();
		MM_->B_sdatca.setTexture ();
		MM_->RS_title.setTexture (&MM_->T_title);
		MM_->RS_popingvini.setTexture (&MM_->T_popingvini);
		MM_->RS_popingvini.setTextureRect (IntRect (
		    0,
		    0,
		    MM_->V2f_popingvini_size.x,
		    MM_->V2f_popingvini_size.y));
		MM_->B_wardrobe.setTexture ();
	}
}
void MainMenu::main_transition ()
{
	MainMenu* MM_ = getClass ();

	if (names::game_status == GameStatus::loading_to_main_menu)
	{
		for (size_t st (0); st < MM_->RS_background.size (); st++)
		{
			MM_->RS_background[st].setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
			MM_->RS_ice[st].setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		MM_->RS_title.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->B_popingvinit.getGlobalBounds ()))
		{
			MM_->B_popingvinit.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		else
		{
			MM_->B_popingvinit.setFillColor (Color (
			    MM_->C_chice_button.r,
			    MM_->C_chice_button.g,
			    MM_->C_chice_button.b,
			    255 - Loading::getFrameTransition ()));
		}
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->B_sdatca.getGlobalBounds ()))
		{
			MM_->B_sdatca.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		else
		{
			MM_->B_sdatca.setFillColor (Color (
			    MM_->C_chice_button.r,
			    MM_->C_chice_button.g,
			    MM_->C_chice_button.b,
			    255 - Loading::getFrameTransition ()));
		}
		MM_->RS_popingvini.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->B_wardrobe.getGlobalBounds ()))
		{
			MM_->B_wardrobe.setFillColor (Color (255, 255, 255, 255 - Loading::getFrameTransition ()));
		}
		else
		{
			MM_->B_wardrobe.setFillColor (Color (
			    MM_->C_chice_button.r,
			    MM_->C_chice_button.g,
			    MM_->C_chice_button.b,
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

		MM_->B_popingvinit.setScale (f);
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->B_popingvinit.getGlobalBounds ()))
		{
			MM_->B_popingvinit.setPosition (
			    MM_->RS_background[0].getPosition ().x + MM_->V2f_popingvinit_button.x * f,
			    MM_->RS_background[0].getPosition ().y + (MM_->V2f_popingvinit_button.y + 1) * f);
			if (names::game_status == GameStatus::main_menu)
			{
				MM_->B_popingvinit.setFillColor (MM_->C_chice_button);
				if (PC_Mouse::isLeftPressed () and Loading::getFrameTransition () == 0.0)
				{
					names::game_status = GameStatus::main_menu_to_person_menu;
				}
			}
		}
		else
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->B_popingvinit.setFillColor (Color (255, 255, 255, 255));
			MM_->B_popingvinit.setPosition (
			    MM_->RS_background[0].getPosition ().x + MM_->V2f_popingvinit_button.x * f,
			    MM_->RS_background[0].getPosition ().y + MM_->V2f_popingvinit_button.y * f);
		}
		MM_->B_sdatca.setScale (f);
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->B_sdatca.getGlobalBounds ()))
		{
			MM_->B_sdatca.setPosition (
			    MM_->RS_background[0].getPosition ().x + MM_->V2f_sdatca_button.x * f,
			    MM_->RS_background[0].getPosition ().y + (MM_->V2f_sdatca_button.y + 1) * f);
			if (names::game_status == GameStatus::main_menu)
			{
				MM_->B_sdatca.setFillColor (MM_->C_chice_button);
				if (PC_Mouse::isLeftPressed () and Loading::getFrameTransition () == 0.0)
				{
					WindowAndStyles::close ();
				}
			}
		}
		else
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->B_sdatca.setFillColor (Color (255, 255, 255, 255));
			MM_->B_sdatca.setPosition (
			    MM_->RS_background[0].getPosition ().x + MM_->V2f_sdatca_button.x * f,
			    MM_->RS_background[0].getPosition ().y + MM_->V2f_sdatca_button.y * f);
		}
		MM_->RS_title.setScale (f, f);
		MM_->RS_title.setPosition (MM_->RS_background[0].getPosition ().x + MM_->V2f_title.x * f,
		                           MM_->RS_background[0].getPosition ().y + MM_->V2f_title.y * f);
		for (size_t st (0); st < MM_->RS_background.size (); st++)
		{
			MM_->RS_background[st].setScale (f, f);
			if (st == 0)
			{
				names::SetXCenterPosition (MM_->RS_background[st], 0);
			}
			else if (st % 2 == 0)
			{
				MM_->RS_background[st].setPosition (MM_->RS_background[0].getPosition ().x - MM_->RS_background[0].getGlobalBounds ().width * st * 0.5, 0);
			}
			else
			{
				MM_->RS_background[st].setPosition (MM_->RS_background[0].getPosition ().x + MM_->RS_background[0].getGlobalBounds ().width * (st + 1) * 0.5, 0);
			}
			MM_->RS_ice[st].setScale (f, f);
			MM_->RS_ice[st].setPosition (MM_->RS_background[st].getPosition ());
		}

		if (rand () % unsigned (MM_->f_chance_reverse / (names::f_time ? names::f_time : 1) + 1) == 0)
		{
			MM_->si_reverse *= -1;
		}
		MM_->V2f_popingvini_defoult = Vector2f (MM_->V2f_popingvini_defoult.x + MM_->f_speed_move_ice * MM_->si_reverse, MM_->V2f_popingvini_defoult.y);
		MM_->f_frame_popingvini += MM_->f_speed_anim_popingvini * names::microsec * names::f_time;
		if (MM_->f_frame_popingvini > MM_->u_cout_frame_popingvini)
		{
			MM_->f_frame_popingvini = 0.0;
		}
		else
		{
			MM_->RS_popingvini.setTextureRect (IntRect (
			    0,
			    MM_->V2f_popingvini_size.y * unsigned (MM_->f_frame_popingvini),
			    MM_->V2f_popingvini_size.x,
			    MM_->V2f_popingvini_size.y));
		}
		MM_->RS_popingvini.setScale (f, f);
		MM_->RS_popingvini.setPosition (
		    MM_->RS_background[0].getPosition ().x + MM_->V2f_popingvini_defoult.x * f,
		    MM_->V2f_popingvini_defoult.y * f);
		MM_->B_wardrobe.setScale (f);
		if (PC_Mouse::getGlobalBounds ().intersects (MM_->B_wardrobe.getGlobalBounds ()))
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->B_wardrobe.setFillColor (MM_->C_chice_button);
			MM_->B_wardrobe.setPosition (
			    MM_->RS_popingvini.getPosition ().x + MM_->V2f_wardrobe_button.x * f,
			    MM_->RS_popingvini.getPosition ().y + (MM_->V2f_wardrobe_button.y + 1) * f);
		}
		else
		{
			if (names::game_status == GameStatus::main_menu)
				MM_->B_wardrobe.setFillColor (Color (255, 255, 255, 255));
			MM_->B_wardrobe.setPosition (
			    MM_->RS_popingvini.getPosition ().x + MM_->V2f_wardrobe_button.x * f,
			    MM_->RS_popingvini.getPosition ().y + MM_->V2f_wardrobe_button.y * f);
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

	MM_->RS_background.resize (int (WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getGlobalBounds ().height /
	                                (MM_->V2f_background_size.x / WindowAndStyles::getPixelsSizeY ())) +
	                           2);
	MM_->RS_ice.resize (MM_->RS_background.size ());

	for (size_t st (0); st < MM_->RS_background.size (); st++)
	{
		MM_->RS_background[st].setSize (MM_->V2f_background_size);
		MM_->RS_background[st].setTexture (&MM_->T_background, true);
		MM_->RS_ice[st].setSize (MM_->V2f_ice_size);
		MM_->RS_ice[st].setTexture (&MM_->T_ice, true);
	}
}

// RectangleShape&

vector<RectangleShape>& MainMenu::getBackground ()
{
	return getClass ()->RS_background;
}
vector<RectangleShape>& MainMenu::getIce ()
{
	return getClass ()->RS_ice;
}
RectangleShape& MainMenu::getTitle ()
{
	return getClass ()->RS_title;
}
RectangleShape& MainMenu::getPopingvini ()
{
	return getClass ()->RS_popingvini;
}

// Button&

ImageButton& MainMenu::getPopingvinit ()
{
	return getClass ()->B_popingvinit;
}
ImageButton& MainMenu::getSdatca ()
{
	return getClass ()->B_sdatca;
}
ImageButton& MainMenu::getWardrobe ()
{
	return getClass ()->B_wardrobe;
}

// Texture&

Texture& MainMenu::getTextureBackground ()
{
	return getClass ()->T_background;
}
Texture& MainMenu::getTextureIce ()
{
	return getClass ()->T_ice;
}
Texture& MainMenu::getTextureTitle ()
{
	return getClass ()->T_title;
}
Texture& MainMenu::getTexturePopingvini ()
{
	return getClass ()->T_popingvini;
}
