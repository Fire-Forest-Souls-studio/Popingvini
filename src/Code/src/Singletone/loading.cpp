#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/main_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/person_menu.h"
#include "../../includes/Singletone/language_menu.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/learn_menu.h"

#include "../../../GetPixels/GPI_Loading.h"
#include "../../../GetPixels/GPI_Main_menu.h"
#include "../../../GetPixels/GPI_Person_menu.h"
#include "../../../GetPixels/GPI_Language_menu.h"
#include "../../../GetPixels/GPI_Works_menu.h"
#include "../../../GetPixels/GPI_Learn_menu.h"
#include "../../../GetPixels/GPI_Test_menu.h"

// private

Loading* Loading::m_class_obj = NULL;

Loading::Loading ()
    : m_f_frame_transition (0.0),
      m_f_transition_speed (255.0 / 2.0),
      m_f_text_size (8.0),
      m_f_speed_rotate (1.0),

      m_C_text_color (255, 255, 255, 255),

      m_load_texture (0),

      m_load_void_const (0),

      m_load_unsigned_long (0),

      m_load_string (0),

      m_w_text (11),

      m_w_load (L"-"),

      m_V2f_text_position (200.0, 27.0),
      m_V2f_text_load_position (255.0, 120.0),

      m_u_load_number (0),
      m_u_symbols_in_line (15),

      m_b_load (false),

      m_s_file_name (names::s_path + "saving.FireForestSouls-Popingvini")
{
	m_rectangle_shape.setSize (Vector2f (350, 150));

	m_w_text[0] = names::GetStringOfHyphenation (
	    L"Пожелание: Если ты хочешь предложить нам идею пиши в тг!",
	    m_u_symbols_in_line);
	m_w_text[1] = names::GetStringOfHyphenation (
	    L"Совет: Делай перерывы по правилу 31: 3 часа работаешь, 1 отдыхаешь",
	    m_u_symbols_in_line);
	m_w_text[2] = names::GetStringOfHyphenation (
	    L"Совет: Если у тебя возникла какая-либо ошибка - напиши одному из разработчиков в тг",
	    m_u_symbols_in_line);
	m_w_text[3] = names::GetStringOfHyphenation (
	    L"Удачи тебе!",
	    m_u_symbols_in_line);
	m_w_text[4] = names::GetStringOfHyphenation (
	    L"О! Ты зашёл!? Мой день сделан!",
	    m_u_symbols_in_line);
	m_w_text[5] = names::GetStringOfHyphenation (
	    L"Чтобы пропустить вступление, просто нажми на пробел во время него!!!",
	    m_u_symbols_in_line);
	m_w_text[6] = names::GetStringOfHyphenation (
	    L"Чтобы выйти из программы, можно нажать Esc",
	    m_u_symbols_in_line);
	m_w_text[7] = names::GetStringOfHyphenation (
	    L"Попингвини ждёт тебя каждый день!",
	    m_u_symbols_in_line);
	m_w_text[8] = names::GetStringOfHyphenation (
	    L"ТЫ можешь присоединиться к ТЕСТИРОВКЕ БЕТА ВЕРСИЙ, просто написав разработчику в тг",
	    m_u_symbols_in_line);
	m_w_text[9] = names::GetStringOfHyphenation (
	    L"Ты можешь сделать свой текстурпак для Попингвини! Инструкция есть в тг канале Попингвини",
	    m_u_symbols_in_line);
	m_w_text[10] = names::GetStringOfHyphenation (
	    L"Если ты создаёшь контент по Попингвини (ролики/посты/текстурпаки/...), отправляй его (или ссылку на него) в комментарии в тг канале Попингвини",
	    m_u_symbols_in_line);

	m_text.setString (m_w_text[rand () % m_w_text.size ()]);
	m_text.setCharacterSize (m_f_text_size);
	m_text.setFont (names::F_pixel);
	m_text.setFillColor (Color (m_C_text_color.r, m_C_text_color.g, m_C_text_color.b, 0));

	m_T_load.setString (m_w_load);
	m_T_load.setCharacterSize (m_f_text_size);
	m_T_load.setFont (names::F_pixel);
	m_T_load.setFillColor (Color (m_C_text_color.r, m_C_text_color.g, m_C_text_color.b, 0));

	m_load_texture.push_back (&MainMenu::getTextureBackground ());
	m_load_void_const.push_back (menu_background_png);
	m_load_unsigned_long.push_back (menu_background_png_size);
	m_load_string.push_back ("Images/Main_menu/menu_background.png");
	m_load_texture.push_back (&MainMenu::getTextureIce ());
	m_load_void_const.push_back (menu_ice_png);
	m_load_unsigned_long.push_back (menu_ice_png_size);
	m_load_string.push_back ("Images/Main_menu/menu_ice.png");
	m_load_texture.push_back (&MainMenu::getPopingvinit ().getTexture ());
	m_load_void_const.push_back (popingvinit_png);
	m_load_unsigned_long.push_back (popingvinit_png_size);
	m_load_string.push_back ("Images/Main_menu/popingvinit.png");
	m_load_texture.push_back (&MainMenu::getSdatca ().getTexture ());
	m_load_void_const.push_back (sdatca_png);
	m_load_unsigned_long.push_back (sdatca_png_size);
	m_load_string.push_back ("Images/Main_menu/sdatca.png");
	m_load_texture.push_back (&MainMenu::getTextureTitle ());
	m_load_void_const.push_back (title_png);
	m_load_unsigned_long.push_back (title_png_size);
	m_load_string.push_back ("Images/Main_menu/title.png");
	m_load_texture.push_back (&MainMenu::getTexturePopingvini ());
	m_load_void_const.push_back (popingvini_png);
	m_load_unsigned_long.push_back (popingvini_png_size);
	m_load_string.push_back ("Images/Main_menu/popingvini.png");
	m_load_texture.push_back (&MainMenu::getWardrobe ().getTexture ());
	m_load_void_const.push_back (wardrobe_button_png);
	m_load_unsigned_long.push_back (wardrobe_button_png_size);
	m_load_string.push_back ("Images/Main_menu/wardrobe_button.png");
	m_load_texture.push_back (&PersonMenu::getTextureBackground ());
	m_load_void_const.push_back (person_menu_background_png);
	m_load_unsigned_long.push_back (person_menu_background_png_size);
	m_load_string.push_back ("Images/Person_menu/person_menu_background.png");
	m_load_texture.push_back (&PersonMenu::getCustom ().getTexture ());
	m_load_void_const.push_back (custom_png);
	m_load_unsigned_long.push_back (custom_png_size);
	m_load_string.push_back ("Images/Person_menu/custom.png");
	m_load_texture.push_back (&PersonMenu::getIntegrated ().getTexture ());
	m_load_void_const.push_back (integrated_png);
	m_load_unsigned_long.push_back (integrated_png_size);
	m_load_string.push_back ("Images/Person_menu/integrated.png");
	m_load_texture.push_back (&LanguageMenu::getPythonButton ().getTexture ());
	m_load_void_const.push_back (python_png);
	m_load_unsigned_long.push_back (python_png_size);
	m_load_string.push_back ("Images/Language_menu/python.png");
	m_load_texture.push_back (&WorksMenu::getTexture ());
	m_load_void_const.push_back (work_icon_png);
	m_load_unsigned_long.push_back (work_icon_png_size);
	m_load_string.push_back ("Images/Works_menu/work_icon.png");
	m_load_texture.push_back (&LearnMenu::getButton ().getTexture ());
	m_load_void_const.push_back (next_button_png);
	m_load_unsigned_long.push_back (next_button_png_size);
	m_load_string.push_back ("Images/Learn_menu/next_button.png");
	m_load_texture.push_back (&LanguageMenu::getPython ().texture);
	m_load_void_const.push_back (test_background_py_png);
	m_load_unsigned_long.push_back (test_background_py_png_size);
	m_load_string.push_back ("Images/Learn_menu/test_background_py.png");
}

// public
// Loading*

Loading* Loading::getClass ()
{
	if (m_class_obj != NULL)
		return m_class_obj;

	m_class_obj = new Loading ();
	return m_class_obj;
}

// void

void Loading::main ()
{
	Loading* L_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (names::game_status == GameStatus::loading)
	{

		if (L_->m_f_frame_transition == 0.0)
		{
			names::LoadFromMemory (L_->m_texture, loading_background_png, loading_background_png_size, "Images/Loading/loading_background.png");

			L_->m_rectangle_shape.setTexture (&L_->m_texture);
			L_->m_rectangle_shape.setFillColor (Color (255, 255, 255, 0));
		}

		if (L_->m_f_frame_transition < 255.0)
		{
			L_->m_f_frame_transition += L_->m_f_transition_speed * names::f_time * names::f_microsec;

			L_->m_rectangle_shape.setFillColor (Color (255, 255, 255, L_->m_f_frame_transition));
			L_->m_text.setFillColor (Color (
			    L_->m_C_text_color.r,
			    L_->m_C_text_color.g,
			    L_->m_C_text_color.b,
			    L_->m_f_frame_transition));
			L_->m_T_load.setFillColor (Color (
			    L_->m_C_text_color.r,
			    L_->m_C_text_color.g,
			    L_->m_C_text_color.b,
			    L_->m_f_frame_transition));
		}
		else if (L_->m_f_frame_transition != 255.0)
		{
			L_->m_rectangle_shape.setFillColor (Color (255, 255, 255, 255));
			L_->m_text.setFillColor (Color (
			    L_->m_C_text_color.r,
			    L_->m_C_text_color.g,
			    L_->m_C_text_color.b,
			    255));
			L_->m_T_load.setFillColor (Color (
			    L_->m_C_text_color.r,
			    L_->m_C_text_color.g,
			    L_->m_C_text_color.b,
			    255));
			L_->m_f_frame_transition = 255.0;
		}
	}

	if (names::game_status == GameStatus::loading or names::game_status == GameStatus::loading_to_main_menu)
	{
		// трансформ
		// фон

		L_->m_T_load.setPosition (L_->m_rectangle_shape.getPosition ().x + L_->m_V2f_text_load_position.x * f,
		                        L_->m_V2f_text_load_position.y * f);
		L_->m_T_load.setCharacterSize (L_->m_f_text_size * f);
		L_->m_T_load.rotate (1 / L_->m_f_speed_rotate * names::f_time);

		L_->m_rectangle_shape.setScale (f, f);
		names::SetXCenterPosition (L_->m_rectangle_shape, 0);

		L_->m_text.setPosition (L_->m_rectangle_shape.getPosition ().x + L_->m_V2f_text_position.x * f,
		                          L_->m_V2f_text_position.y * f);
		L_->m_text.setCharacterSize (L_->m_f_text_size * f);
	}

	if (names::game_status == GameStatus::loading)
	{
		// loading

		if (L_->m_f_frame_transition == 255.0)
		{
			if (L_->m_b_load)
			{
				size_t st_read_size (0);

				L_->m_i_file.open (L_->m_s_file_name, ios::out | ios::binary);
				L_->m_i_file.read ((char*)&st_read_size, sizeof (size_t));
				for (size_t st (0); st < LanguageMenu::getPython ().work.size (); st++)
				{
					if (st < st_read_size)
					{
						L_->m_i_file.read ((char*)&LanguageMenu::getPython ().work[st].u_try, sizeof (unsigned));
						L_->m_i_file.read ((char*)&LanguageMenu::getPython ().work[st].test.f_best_score, sizeof (float));
						L_->m_i_file.read ((char*)&LanguageMenu::getPython ().work[st].test.f_best_true, sizeof (float));
						L_->m_i_file.read ((char*)&LanguageMenu::getPython ().work[st].test.f_best_time, sizeof (float));
					}
				}
				L_->m_i_file.close ();

				L_->m_b_load = false;
				names::game_status = GameStatus::loading_to_main_menu;
			}
			else if (L_->m_u_load_number < L_->m_load_texture.size ())
			{
				names::LoadFromMemory (*L_->m_load_texture[L_->m_u_load_number], L_->m_load_void_const[L_->m_u_load_number],
				                       L_->m_load_unsigned_long[L_->m_u_load_number], L_->m_load_string[L_->m_u_load_number]);
				L_->m_u_load_number++;
			}
			else
			{
				L_->m_b_load = true;
			}
		}
	}

	if (names::game_status == GameStatus::loading_to_main_menu)
	{

		if (L_->m_f_frame_transition > 0.0)
		{
			L_->m_f_frame_transition -= names::f_microsec * L_->m_f_transition_speed * names::f_time;

			L_->m_rectangle_shape.setFillColor (Color (255, 255, 255, L_->m_f_frame_transition));
			L_->m_text.setFillColor (Color (
			    L_->m_C_text_color.r,
			    L_->m_C_text_color.g,
			    L_->m_C_text_color.b,
			    L_->m_f_frame_transition));
			L_->m_T_load.setFillColor (Color (
			    L_->m_C_text_color.r,
			    L_->m_C_text_color.g,
			    L_->m_C_text_color.b,
			    L_->m_f_frame_transition));
		}
		else
		{
			names::game_status = GameStatus::main_menu;
			L_->m_f_frame_transition = 0.0;
		}
	}
}

void Loading::write ()
{
	Loading* L_ = getClass ();

	size_t st_write_size (LanguageMenu::getPython ().work.size ());

	L_->m_o_file.open (L_->m_s_file_name, ios::out | ios::binary | std::ios::trunc);
	L_->m_o_file.write ((char*)&st_write_size, sizeof (size_t));
	for (size_t st (0); st < LanguageMenu::getPython ().work.size (); st++)
	{
		L_->m_o_file.write ((char*)&LanguageMenu::getPython ().work[st].u_try, sizeof (unsigned));
		L_->m_o_file.write ((char*)&LanguageMenu::getPython ().work[st].test.f_best_score, sizeof (float));
		L_->m_o_file.write ((char*)&LanguageMenu::getPython ().work[st].test.f_best_true, sizeof (float));
		L_->m_o_file.write ((char*)&LanguageMenu::getPython ().work[st].test.f_best_time, sizeof (float));
	}

	L_->m_o_file.close ();
}

// RectangleShape&

RectangleShape& Loading::getSprite ()
{
	return getClass ()->m_rectangle_shape;
}

// Text&

Text& Loading::getSpriteText ()
{
	return getClass ()->m_text;
}
Text& Loading::getLoadText ()
{
	return getClass ()->m_T_load;
}

// float

float Loading::getFrameTransition ()
{
	return getClass ()->m_f_frame_transition;
}

// bool

bool Loading::getLoad ()
{
	return getClass ()->m_b_load;
}
