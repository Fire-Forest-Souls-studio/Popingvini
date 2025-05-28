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

Loading* Loading::class_obj = NULL;

Loading::Loading ()
    : f_frame_transition (0.0),
      f_transition_speed (255.0 / 2.0),
      f_text_size (8.0),
      f_speed_rotate (1.0),

      C_text_color (255, 255, 255, 255),

      load_texture (0),

      load_void_const (0),

      load_unsigned_long (0),

      load_string (0),

      w_text (11),

      w_load (L"-"),

      V2f_text_position (200.0, 27.0),
      V2f_text_load_position (255.0, 120.0),

      u_load_number (0),
      u_symbols_in_line (15),

      b_load (false),

      s_file_name (names::s_path + "saving.FireForestSouls-Popingvini")
{
	rectangle_shape_obj.setSize (Vector2f (350, 150));

	w_text[0] = names::GetStringOfHyphenation (
	    L"Пожелание: Если ты хочешь предложить нам идею пиши в тг!",
	    u_symbols_in_line);
	w_text[1] = names::GetStringOfHyphenation (
	    L"Совет: Делай перерывы по правилу 31: 3 часа работаешь, 1 отдыхаешь",
	    u_symbols_in_line);
	w_text[2] = names::GetStringOfHyphenation (
	    L"Совет: Если у тебя возникла какая-либо ошибка - напиши одному из разработчиков в тг",
	    u_symbols_in_line);
	w_text[3] = names::GetStringOfHyphenation (
	    L"Удачи тебе!",
	    u_symbols_in_line);
	w_text[4] = names::GetStringOfHyphenation (
	    L"О! Ты зашёл!? Мой день сделан!",
	    u_symbols_in_line);
	w_text[5] = names::GetStringOfHyphenation (
	    L"Чтобы пропустить вступление, просто нажми на пробел во время него!!!",
	    u_symbols_in_line);
	w_text[6] = names::GetStringOfHyphenation (
	    L"Чтобы выйти из программы, можно нажать Esc",
	    u_symbols_in_line);
	w_text[7] = names::GetStringOfHyphenation (
	    L"Попингвини ждёт тебя каждый день!",
	    u_symbols_in_line);
	w_text[8] = names::GetStringOfHyphenation (
	    L"ТЫ можешь присоединиться к ТЕСТИРОВКЕ БЕТА ВЕРСИЙ, просто написав разработчику в тг",
	    u_symbols_in_line);
	w_text[9] = names::GetStringOfHyphenation (
	    L"Ты можешь сделать свой текстурпак для Попингвини! Инструкция есть в тг канале Попингвини",
	    u_symbols_in_line);
	w_text[10] = names::GetStringOfHyphenation (
	    L"Если ты создаёшь контент по Попингвини (ролики/посты/текстурпаки/...), отправляй его (или ссылку на него) в комментарии в тг канале Попингвини",
	    u_symbols_in_line);

	text_obj.setString (w_text[rand () % w_text.size ()]);
	text_obj.setCharacterSize (f_text_size);
	text_obj.setFont (names::F_pixel);
	text_obj.setFillColor (Color (C_text_color.r, C_text_color.g, C_text_color.b, 0));

	T_load.setString (w_load);
	T_load.setCharacterSize (f_text_size);
	T_load.setFont (names::F_pixel);
	T_load.setFillColor (Color (C_text_color.r, C_text_color.g, C_text_color.b, 0));

	load_texture.push_back (&MainMenu::getTextureBackground ());
	load_void_const.push_back (menu_background_png);
	load_unsigned_long.push_back (menu_background_png_size);
	load_string.push_back ("Images/Main_menu/menu_background.png");
	load_texture.push_back (&MainMenu::getTextureIce ());
	load_void_const.push_back (menu_ice_png);
	load_unsigned_long.push_back (menu_ice_png_size);
	load_string.push_back ("Images/Main_menu/menu_ice.png");
	load_texture.push_back (&MainMenu::getPopingvinit ().getTexture ());
	load_void_const.push_back (popingvinit_png);
	load_unsigned_long.push_back (popingvinit_png_size);
	load_string.push_back ("Images/Main_menu/popingvinit.png");
	load_texture.push_back (&MainMenu::getSdatca ().getTexture ());
	load_void_const.push_back (sdatca_png);
	load_unsigned_long.push_back (sdatca_png_size);
	load_string.push_back ("Images/Main_menu/sdatca.png");
	load_texture.push_back (&MainMenu::getTextureTitle ());
	load_void_const.push_back (title_png);
	load_unsigned_long.push_back (title_png_size);
	load_string.push_back ("Images/Main_menu/title.png");
	load_texture.push_back (&MainMenu::getTexturePopingvini ());
	load_void_const.push_back (popingvini_png);
	load_unsigned_long.push_back (popingvini_png_size);
	load_string.push_back ("Images/Main_menu/popingvini.png");
	load_texture.push_back (&MainMenu::getWardrobe ().getTexture ());
	load_void_const.push_back (wardrobe_button_png);
	load_unsigned_long.push_back (wardrobe_button_png_size);
	load_string.push_back ("Images/Main_menu/wardrobe_button.png");
	load_texture.push_back (&PersonMenu::getTextureBackground ());
	load_void_const.push_back (person_menu_background_png);
	load_unsigned_long.push_back (person_menu_background_png_size);
	load_string.push_back ("Images/Person_menu/person_menu_background.png");
	load_texture.push_back (&PersonMenu::getCustom ().getTexture ());
	load_void_const.push_back (custom_png);
	load_unsigned_long.push_back (custom_png_size);
	load_string.push_back ("Images/Person_menu/custom.png");
	load_texture.push_back (&PersonMenu::getIntegrated ().getTexture ());
	load_void_const.push_back (integrated_png);
	load_unsigned_long.push_back (integrated_png_size);
	load_string.push_back ("Images/Person_menu/integrated.png");
	load_texture.push_back (&LanguageMenu::getPythonButton ().getTexture ());
	load_void_const.push_back (python_png);
	load_unsigned_long.push_back (python_png_size);
	load_string.push_back ("Images/Language_menu/python.png");
	load_texture.push_back (&WorksMenu::getTexture ());
	load_void_const.push_back (work_icon_png);
	load_unsigned_long.push_back (work_icon_png_size);
	load_string.push_back ("Images/Works_menu/work_icon.png");
	load_texture.push_back (&LearnMenu::getButton ().getTexture ());
	load_void_const.push_back (next_button_png);
	load_unsigned_long.push_back (next_button_png_size);
	load_string.push_back ("Images/Learn_menu/next_button.png");
	load_texture.push_back (&LanguageMenu::getPython ().texture);
	load_void_const.push_back (test_background_py_png);
	load_unsigned_long.push_back (test_background_py_png_size);
	load_string.push_back ("Images/Learn_menu/test_background_py.png");
}

// public
// Loading*

Loading* Loading::getClass ()
{
	if (class_obj != NULL)
		return class_obj;

	class_obj = new Loading ();
	return class_obj;
}

// void

void Loading::main ()
{
	Loading* L_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (names::game_status == GameStatus::loading)
	{

		if (L_->f_frame_transition == 0.0)
		{
			names::LoadFromMemory (L_->texture_obj, loading_background_png, loading_background_png_size, "Images/Loading/loading_background.png");

			L_->rectangle_shape_obj.setTexture (&L_->texture_obj);
			L_->rectangle_shape_obj.setFillColor (Color (255, 255, 255, 0));
		}

		if (L_->f_frame_transition < 255.0)
		{
			L_->f_frame_transition += L_->f_transition_speed * names::f_time * names::microsec;

			L_->rectangle_shape_obj.setFillColor (Color (255, 255, 255, L_->f_frame_transition));
			L_->text_obj.setFillColor (Color (
			    L_->C_text_color.r,
			    L_->C_text_color.g,
			    L_->C_text_color.b,
			    L_->f_frame_transition));
			L_->T_load.setFillColor (Color (
			    L_->C_text_color.r,
			    L_->C_text_color.g,
			    L_->C_text_color.b,
			    L_->f_frame_transition));
		}
		else if (L_->f_frame_transition != 255.0)
		{
			L_->rectangle_shape_obj.setFillColor (Color (255, 255, 255, 255));
			L_->text_obj.setFillColor (Color (
			    L_->C_text_color.r,
			    L_->C_text_color.g,
			    L_->C_text_color.b,
			    255));
			L_->T_load.setFillColor (Color (
			    L_->C_text_color.r,
			    L_->C_text_color.g,
			    L_->C_text_color.b,
			    255));
			L_->f_frame_transition = 255.0;
		}
	}

	if (names::game_status == GameStatus::loading or names::game_status == GameStatus::loading_to_main_menu)
	{
		// трансформ
		// фон

		L_->T_load.setPosition (L_->rectangle_shape_obj.getPosition ().x + L_->V2f_text_load_position.x * f,
		                        L_->V2f_text_load_position.y * f);
		L_->T_load.setCharacterSize (L_->f_text_size * f);
		L_->T_load.rotate (1 / L_->f_speed_rotate * names::f_time);

		L_->rectangle_shape_obj.setScale (f, f);
		names::SetXCenterPosition (L_->rectangle_shape_obj, 0);

		L_->text_obj.setPosition (L_->rectangle_shape_obj.getPosition ().x + L_->V2f_text_position.x * f,
		                          L_->V2f_text_position.y * f);
		L_->text_obj.setCharacterSize (L_->f_text_size * f);
	}

	if (names::game_status == GameStatus::loading)
	{
		// loading

		if (L_->f_frame_transition == 255.0)
		{
			if (L_->b_load)
			{
				size_t st_read_size (0);

				L_->i_file.open (L_->s_file_name, ios::out | ios::binary);
				L_->i_file.read ((char*)&st_read_size, sizeof (size_t));
				for (size_t st (0); st < LanguageMenu::getPython ().work.size (); st++)
				{
					if (st < st_read_size)
					{
						L_->i_file.read ((char*)&LanguageMenu::getPython ().work[st].u_try, sizeof (unsigned));
						L_->i_file.read ((char*)&LanguageMenu::getPython ().work[st].test.f_best_score, sizeof (float));
						L_->i_file.read ((char*)&LanguageMenu::getPython ().work[st].test.f_best_true, sizeof (float));
						L_->i_file.read ((char*)&LanguageMenu::getPython ().work[st].test.f_best_time, sizeof (float));
					}
				}
				L_->i_file.close ();

				L_->b_load = false;
				names::game_status = GameStatus::loading_to_main_menu;
			}
			else if (L_->u_load_number < L_->load_texture.size ())
			{
				names::LoadFromMemory (*L_->load_texture[L_->u_load_number], L_->load_void_const[L_->u_load_number],
				                       L_->load_unsigned_long[L_->u_load_number], L_->load_string[L_->u_load_number]);
				L_->u_load_number++;
			}
			else
			{
				L_->b_load = true;
			}
		}
	}

	if (names::game_status == GameStatus::loading_to_main_menu)
	{

		if (L_->f_frame_transition > 0.0)
		{
			L_->f_frame_transition -= names::microsec * L_->f_transition_speed * names::f_time;

			L_->rectangle_shape_obj.setFillColor (Color (255, 255, 255, L_->f_frame_transition));
			L_->text_obj.setFillColor (Color (
			    L_->C_text_color.r,
			    L_->C_text_color.g,
			    L_->C_text_color.b,
			    L_->f_frame_transition));
			L_->T_load.setFillColor (Color (
			    L_->C_text_color.r,
			    L_->C_text_color.g,
			    L_->C_text_color.b,
			    L_->f_frame_transition));
		}
		else
		{
			names::game_status = GameStatus::main_menu;
			L_->f_frame_transition = 0.0;
		}
	}
}

void Loading::write ()
{
	Loading* L_ = getClass ();

	size_t st_write_size (LanguageMenu::getPython ().work.size ());

	L_->o_file.open (L_->s_file_name, ios::out | ios::binary | std::ios::trunc);
	L_->o_file.write ((char*)&st_write_size, sizeof (size_t));
	for (size_t st (0); st < LanguageMenu::getPython ().work.size (); st++)
	{
		L_->o_file.write ((char*)&LanguageMenu::getPython ().work[st].u_try, sizeof (unsigned));
		L_->o_file.write ((char*)&LanguageMenu::getPython ().work[st].test.f_best_score, sizeof (float));
		L_->o_file.write ((char*)&LanguageMenu::getPython ().work[st].test.f_best_true, sizeof (float));
		L_->o_file.write ((char*)&LanguageMenu::getPython ().work[st].test.f_best_time, sizeof (float));
	}

	L_->o_file.close ();
}

// RectangleShape&

RectangleShape& Loading::getSprite ()
{
	return getClass ()->rectangle_shape_obj;
}

// Text&

Text& Loading::getSpriteText ()
{
	return getClass ()->text_obj;
}
Text& Loading::getLoadText ()
{
	return getClass ()->T_load;
}

// float

float Loading::getFrameTransition ()
{
	return getClass ()->f_frame_transition;
}

// bool

bool Loading::getLoad ()
{
	return getClass ()->b_load;
}
