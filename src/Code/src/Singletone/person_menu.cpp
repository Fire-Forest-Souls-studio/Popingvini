#include "../../includes/Singletone/person_menu.h"
#include "../../includes/Singletone/main_menu.h"
#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

PersonMenu* PersonMenu::m_class_obj = NULL;

PersonMenu::PersonMenu ()
    : m_RS_background (MainMenu::getBackground ().size ()),

      m_B_custom ("PM/button/custom"),
      m_B_integrated ("PM/button/integrated"),

      m_f_speed_move (35.0),
      m_f_frame_transition (0.0),
      m_f_speed_transition (255.0 / 1.5),
      m_f_frame_animation (0.0),
      m_f_speed_animation (6.0),
      m_f_y_position_background (150),

      m_V2f_background_size (500.0, 300.0),
      m_V2f_button_size (42, 42),
      m_V2f_button_spacing (21, 14),

      m_C_button_color (18, 42, 59, 255),

      m_u_cout_frames (8)
{
	for (size_t st (0); st < m_RS_background.size (); st++)
	{
		m_RS_background[st].setSize (m_V2f_background_size);
	}
	m_B_custom.setSize (m_V2f_button_size);
	m_B_integrated.setSize (m_V2f_button_size);
}

PersonMenu* PersonMenu::getClass ()
{
	if (m_class_obj != NULL)
		return m_class_obj;

	m_class_obj = new PersonMenu ();
	return m_class_obj;
}

void PersonMenu::destroy ()
{
	PersonMenu* PM_ = getClass ();

	PM_->m_RS_background.resize (int (WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getGlobalBounds ().height /
	                                (PM_->m_V2f_background_size.x / WindowAndStyles::getPixelsSizeY ())) +
	                           2);

	for (size_t st (0); st < PM_->m_RS_background.size (); st++)
	{
		PM_->m_RS_background[st].setSize (PM_->m_V2f_background_size);
		PM_->m_RS_background[st].setTexture (&PM_->m_T_background);
		PM_->m_RS_background[st].setTextureRect (IntRect (0, 0, PM_->m_V2f_background_size.x, PM_->m_V2f_background_size.y));
	}
}

void PersonMenu::main_load ()
{
	PersonMenu* PM_ = getClass ();

	if (Loading::getLoad ())
	{
		for (size_t st (0); st < PM_->m_RS_background.size (); st++)
		{
			PM_->m_RS_background[st].setTexture (&PM_->m_T_background);
			PM_->m_RS_background[st].setTextureRect (IntRect (0, 0, PM_->m_V2f_background_size.x, PM_->m_V2f_background_size.y));
		}
		PM_->m_B_custom.setTexture ();
		PM_->m_B_integrated.setTexture ();
		PM_->m_B_custom.setFillColor (Color (255, 255, 255, 0));
		PM_->m_B_integrated.setFillColor (Color (255, 255, 255, 0));
	}
}

void PersonMenu::main_transitionTo ()
{
	PersonMenu* PM_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (names::game_status == GameStatus::main_menu_to_person_menu)
	{
		for (size_t st (0); st < PM_->m_RS_background.size (); st++)
		{
			PM_->m_RS_background[st].setScale (f, f);
		}
		PM_->m_B_custom.setScale (f);
		PM_->m_B_integrated.setScale (f);

		if (PM_->m_f_y_position_background > -WindowAndStyles::getPixelsSizeY ())
		{
			PM_->m_f_frame_animation += PM_->m_f_speed_animation * names::f_microsec * names::f_time;
			if (PM_->m_f_frame_animation > PM_->m_u_cout_frames)
			{
				PM_->m_f_frame_animation = 0.0;
			}

			PM_->m_f_y_position_background -= PM_->m_f_speed_move * names::f_microsec * names::f_time;
			for (size_t st (0); st < PM_->m_RS_background.size (); st++)
			{
				PM_->m_RS_background[st].setTextureRect (IntRect (
				    0,
				    PM_->m_T_background.getSize ().y / PM_->m_u_cout_frames * unsigned (PM_->m_f_frame_animation),
				    PM_->m_T_background.getSize ().x,
				    PM_->m_T_background.getSize ().y / PM_->m_u_cout_frames));

				PM_->m_RS_background[st].setScale (f, f);
				if (st == 0)
				{
					names::SetXCenterPosition (PM_->m_RS_background[st], PM_->m_f_y_position_background * f);
				}
				else if (st % 2 == 0)
				{
					PM_->m_RS_background[st].setPosition (
					    PM_->m_RS_background[0].getPosition ().x - PM_->m_RS_background[0].getGlobalBounds ().width * st * 0.5,
					    PM_->m_f_y_position_background * f);
				}
				else
				{
					PM_->m_RS_background[st].setPosition (
					    PM_->m_RS_background[0].getPosition ().x + PM_->m_RS_background[0].getGlobalBounds ().width * (st + 1) * 0.5,
					    PM_->m_f_y_position_background * f);
				}
			}

			PM_->m_B_custom.setFillColor (Color (0.0, 0.0, 0.0, 0.0));
			PM_->m_B_integrated.setFillColor (Color (0.0, 0.0, 0.0, 0.0));
		}
		else
		{
			names::game_status = GameStatus::person_menu;
		}
	}
	if (names::game_status == GameStatus::works_menu_to_main_menu)
	{
		for (size_t st (0); st < PM_->m_RS_background.size (); st++)
		{
			PM_->m_RS_background[st].setScale (f, f);
		}
		if (PM_->m_f_y_position_background < WindowAndStyles::getPixelsSizeY ())
		{
			PM_->m_f_frame_animation += PM_->m_f_speed_animation * names::f_microsec * names::f_time;
			if (PM_->m_f_frame_animation > PM_->m_u_cout_frames)
			{
				PM_->m_f_frame_animation = 0.0;
			}

			PM_->m_f_y_position_background += PM_->m_f_speed_move * names::f_microsec * names::f_time;
			for (size_t st (0); st < PM_->m_RS_background.size (); st++)
			{
				PM_->m_RS_background[st].setTextureRect (IntRect (
				    0,
				    PM_->m_T_background.getSize ().y / PM_->m_u_cout_frames * unsigned (PM_->m_f_frame_animation),
				    PM_->m_T_background.getSize ().x,
				    PM_->m_T_background.getSize ().y / PM_->m_u_cout_frames));
				if (st == 0)
				{
					names::SetXCenterPosition (PM_->m_RS_background[st], PM_->m_f_y_position_background * f);
				}
				else if (st % 2 == 0)
				{
					PM_->m_RS_background[st].setPosition (
					    PM_->m_RS_background[0].getPosition ().x - PM_->m_RS_background[0].getGlobalBounds ().width * st * 0.5,
					    PM_->m_f_y_position_background * f);
				}
				else
				{
					PM_->m_RS_background[st].setPosition (
					    PM_->m_RS_background[0].getPosition ().x + PM_->m_RS_background[0].getGlobalBounds ().width * (st + 1) * 0.5,
					    PM_->m_f_y_position_background * f);
				}
			}
		}
		else
		{
			PM_->m_f_frame_transition = 0.0;
			names::game_status = GameStatus::main_menu;
		}
	}
}

void PersonMenu::main_main ()
{
	PersonMenu* PM_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (names::game_status == GameStatus::person_menu)
	{
		if (PM_->m_f_frame_transition < 255.0)
		{
			PM_->m_f_frame_transition += PM_->m_f_speed_transition * names::f_time * names::f_microsec;
			if (PM_->m_B_custom.interect ())
			{
				PM_->m_B_custom.setFillColor (Color (255, 255, 255, PM_->m_f_frame_transition));
			}
			else
			{
				PM_->m_B_custom.setFillColor (Color (
				    PM_->m_C_button_color.r,
				    PM_->m_C_button_color.g,
				    PM_->m_C_button_color.b,
				    PM_->m_f_frame_transition));
			}
			if (PM_->m_B_integrated.interect ())
			{
				PM_->m_B_integrated.setFillColor (Color (255, 255, 255, PM_->m_f_frame_transition));
			}
			else
			{
				PM_->m_B_integrated.setFillColor (Color (
				    PM_->m_C_button_color.r,
				    PM_->m_C_button_color.g,
				    PM_->m_C_button_color.b,
				    PM_->m_f_frame_transition));
			}
		}
		else if (PM_->m_f_frame_transition != 255.0)
		{
			PM_->m_f_frame_transition = 255.0;
		}
		else
		{
			if (PM_->m_B_custom.interect ())
			{
				PM_->m_B_custom.setFillColor (Color (255, 255, 255, 255));
			}
			else
			{
				PM_->m_B_custom.setFillColor (Color (
				    PM_->m_C_button_color.r,
				    PM_->m_C_button_color.g,
				    PM_->m_C_button_color.b,
				    255));
			}
			if (PM_->m_B_integrated.interect ())
			{
				PM_->m_B_integrated.setFillColor (Color (255, 255, 255, 255));
			}
			else
			{
				PM_->m_B_integrated.setFillColor (Color (
				    PM_->m_C_button_color.r,
				    PM_->m_C_button_color.g,
				    PM_->m_C_button_color.b,
				    255));
			}
		}

		PM_->m_B_custom.setScale (f);
		PM_->m_B_integrated.setScale (f);

		PM_->m_B_custom.setPosition (
		    WindowAndStyles::getGlobalBounds ().width * 0.5 - (PM_->m_V2f_button_spacing.x * 0.5 + PM_->m_V2f_button_size.x) * f,
		    WindowAndStyles::getGlobalBounds ().height * 0.5 - PM_->m_V2f_button_size.y * f * 0.5);
		PM_->m_B_integrated.setPosition (
		    WindowAndStyles::getGlobalBounds ().width * 0.5 + (PM_->m_V2f_button_spacing.x * 0.5) * f,
		    WindowAndStyles::getGlobalBounds ().height * 0.5 - PM_->m_V2f_button_size.y * f * 0.5);

		if (PM_->m_B_integrated.pressed () and PM_->m_f_frame_transition == 255.0)
		{
			names::game_status = GameStatus::language_menu;
		}
	}
}

void PersonMenu::main_transitionOf ()
{
	PersonMenu* PM_ = getClass ();

	if (names::game_status == GameStatus::language_menu)
	{
		if (PM_->m_f_frame_transition > 0.0)
		{
			PM_->m_f_frame_transition -= PM_->m_f_speed_transition * names::f_time * names::f_microsec;
			PM_->m_B_custom.setFillColor (Color (
			    PM_->m_B_custom.getRectangleShape ().getFillColor ().r,
			    PM_->m_B_custom.getRectangleShape ().getFillColor ().g,
			    PM_->m_B_custom.getRectangleShape ().getFillColor ().b,
			    PM_->m_f_frame_transition));
			PM_->m_B_integrated.setFillColor (Color (
			    PM_->m_B_integrated.getRectangleShape ().getFillColor ().r,
			    PM_->m_B_integrated.getRectangleShape ().getFillColor ().g,
			    PM_->m_B_integrated.getRectangleShape ().getFillColor ().b,
			    PM_->m_f_frame_transition));
		}
		else if (PM_->m_f_frame_transition != 0.0)
		{
			PM_->m_f_frame_transition = 0.0;
			PM_->m_B_custom.setFillColor (Color (
			    PM_->m_B_custom.getRectangleShape ().getFillColor ().r,
			    PM_->m_B_custom.getRectangleShape ().getFillColor ().g,
			    PM_->m_B_custom.getRectangleShape ().getFillColor ().b,
			    PM_->m_f_frame_transition));
			PM_->m_B_integrated.setFillColor (Color (
			    PM_->m_B_integrated.getRectangleShape ().getFillColor ().r,
			    PM_->m_B_integrated.getRectangleShape ().getFillColor ().g,
			    PM_->m_B_integrated.getRectangleShape ().getFillColor ().b,
			    PM_->m_f_frame_transition));
		}
	}
}

void PersonMenu::main_forAllMenu ()
{
	PersonMenu* PM_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (names::game_status == GameStatus::person_menu or names::game_status == GameStatus::language_menu or names::game_status == GameStatus::works_menu or names::game_status == GameStatus::learn or names::game_status == GameStatus::test)
	{
		PM_->m_f_frame_animation += PM_->m_f_speed_animation * names::f_microsec * names::f_time;
		if (PM_->m_f_frame_animation > PM_->m_u_cout_frames)
		{
			PM_->m_f_frame_animation = 0.0;
		}

		for (size_t st (0); st < PM_->m_RS_background.size (); st++)
		{
			PM_->m_RS_background[st].setTextureRect (IntRect (
			    0,
			    PM_->m_T_background.getSize ().y / PM_->m_u_cout_frames * unsigned (PM_->m_f_frame_animation),
			    PM_->m_T_background.getSize ().x,
			    PM_->m_T_background.getSize ().y / PM_->m_u_cout_frames));
			PM_->m_RS_background[st].setScale (f, f);
			if (st == 0)
			{
				names::SetXCenterPosition (PM_->m_RS_background[st], -WindowAndStyles::getGlobalBounds ().height);
			}
			else if (st % 2 == 0)
			{
				PM_->m_RS_background[st].setPosition (
				    PM_->m_RS_background[0].getPosition ().x - PM_->m_RS_background[0].getGlobalBounds ().width * st * 0.5,
				    -WindowAndStyles::getGlobalBounds ().height);
			}
			else
			{
				PM_->m_RS_background[st].setPosition (
				    PM_->m_RS_background[0].getPosition ().x + PM_->m_RS_background[0].getGlobalBounds ().width * (st + 1) * 0.5,
				    -WindowAndStyles::getGlobalBounds ().height);
			}
		}
	}
}

void PersonMenu::main ()
{
	main_load ();

	main_transitionTo ();

	main_main ();

	main_transitionOf ();

	main_forAllMenu ();
}

vector<RectangleShape>& PersonMenu::getBackground ()
{
	return getClass ()->m_RS_background;
}

Texture& PersonMenu::getTextureBackground ()
{
	return getClass ()->m_T_background;
}

ImageButton& PersonMenu::getCustom ()
{
	return getClass ()->m_B_custom;
}

ImageButton& PersonMenu::getIntegrated ()
{
	return getClass ()->m_B_integrated;
}

Vector2f& PersonMenu::getButtonSize ()
{
	return getClass ()->m_V2f_button_size;
}

Color& PersonMenu::getButtonColor ()
{
	return getClass ()->m_C_button_color;
}

float& PersonMenu::getFrameTransition ()
{
	return getClass ()->m_f_frame_transition;
}

float& PersonMenu::getSpeedTransition ()
{
	return getClass ()->m_f_speed_transition;
}
