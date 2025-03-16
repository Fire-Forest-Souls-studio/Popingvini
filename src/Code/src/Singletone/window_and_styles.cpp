#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/introduction.h"
#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/error_class.h"
#include "../../includes/Singletone/main_menu.h"
#include "../../includes/Singletone/person_menu.h"
#include "../../includes/Singletone/language_menu.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/learn_menu.h"
#include "../../includes/Singletone/test_menu.h"

#include "../../../GetPixels/GPI.h"

//private

WindowAndStyles* WindowAndStyles::class_obj = NULL;

WindowAndStyles::WindowAndStyles () :
		f_size_pix (300.0, 150.0),

		rectangle_shape_obj (f_size_pix),

		now (Default),

		f_time_since_clicking (0),

		w_game_name (L"Попингвини"),

		C_defolt_window (22, 23, 26, 255),
				C_clear_color (0, 0, 0, 255)
{
}

//protected
//void
void WindowAndStyles::main_time_work ()
{
	names::f_time = names::C_clock.restart ().asMicroseconds ();
	if (WindowAndStyles::hasFocus ())
	{
		names::f_time = names::f_time * 0.001;
	}
	else
	{
		names::f_time = 0.0;
	}
}
void WindowAndStyles::main_F11 ()
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->f_time_since_clicking += names::microsec * names::f_time;

	if (Keyboard::isKeyPressed (Keyboard::F11)
			and WAS_->f_time_since_clicking > 1.0
			and WAS_->window_obj.hasFocus ())
	{
		if (WAS_->now == Default)
		{
			WAS_->videomode_obj = VideoMode::getFullscreenModes ()[0];
			WAS_->render_texture_obj.create (
					WAS_->videomode_obj.width / names::u_factor_of_resolution,
					WAS_->videomode_obj.height / names::u_factor_of_resolution
							);
			WAS_->window_obj.create (
					VideoMode (WAS_->videomode_obj.width, WAS_->videomode_obj.height),
					WAS_->w_game_name,
					Style::Fullscreen
					);

			WAS_->camera.setCenter (Vector2f (
					static_cast <float> (WAS_->videomode_obj.width) * 0.5,
					static_cast <float> (WAS_->videomode_obj.height) * 0.5
							));
			WAS_->camera.setSize (Vector2f (
					static_cast <float> (WAS_->videomode_obj.width),
					static_cast <float> (WAS_->videomode_obj.height)
					));
			WAS_->render_texture_obj.setView (WAS_->camera);
			WAS_->window_obj.setView (WAS_->camera);

			main_destroy ();

			WAS_->now = Fullscreen;
			WAS_->f_time_since_clicking = 0.0;
		}
		else if (WAS_->now == Fullscreen)
		{
			WAS_->videomode_obj = VideoMode::getDesktopMode ();
			WAS_->window_obj.create (
					VideoMode (WAS_->videomode_obj.width, WAS_->videomode_obj.height),
					WAS_->w_game_name,
					Style::Default
					);
			WAS_->render_texture_obj.create (
					static_cast <float> (WAS_->window_obj.getSize ().x) / names::u_factor_of_resolution,
					static_cast <float> (WAS_->window_obj.getSize ().y) / names::u_factor_of_resolution
							);

			WAS_->camera.setCenter (Vector2f (
					static_cast <float> (WAS_->window_obj.getSize ().x) * 0.5,
					static_cast <float> (WAS_->window_obj.getSize ().y) * 0.5
							));
			WAS_->camera.setSize (Vector2f (
					static_cast <float> (WAS_->window_obj.getSize ().x),
					static_cast <float> (WAS_->window_obj.getSize ().y)
					));
			WAS_->render_texture_obj.setView (WAS_->camera);
			WAS_->window_obj.setView (WAS_->camera);

			main_destroy ();

			WAS_->now = Default;
			WAS_->f_time_since_clicking = 0;
		}
	}

}
void WindowAndStyles::main_event ()
{
	WindowAndStyles* WAS_ = getClass ();

	while (WAS_->window_obj.pollEvent (names::E_event))
	{
		if (names::E_event.type == Event::Closed or (WindowAndStyles::hasFocus () and Keyboard::isKeyPressed (Keyboard::Escape)))
		{
			close ();
		}
		if (names::E_event.type == Event::MouseWheelScrolled)
		{
			if (names::E_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{
				WorksMenu::setMoveBlocks (names::E_event.mouseWheelScroll.delta);
			}
		}
	}
	if (names::E_event.type == sf::Event::Resized)
	{
		WindowAndStyles* WAS_ = getClass ();

		//camera
		WAS_->camera.setCenter (Vector2f (
				static_cast <float> (names::E_event.size.width) * 0.5,
				static_cast <float> (names::E_event.size.height) * 0.5
						));
		WAS_->camera.setSize (Vector2f (
				static_cast <float> (names::E_event.size.width),
				static_cast <float> (names::E_event.size.height)
				));
		WAS_->render_texture_obj.create (
				WAS_->camera.getSize ().x / names::u_factor_of_resolution,
				WAS_->camera.getSize ().y / names::u_factor_of_resolution
						);
		WAS_->render_texture_obj.setView (WAS_->camera);
		WAS_->window_obj.setView (WAS_->camera);

		main_destroy ();
	}
}
void WindowAndStyles::clear_clear ()
{
	WindowAndStyles* WAS_ = getClass ();
	if (WAS_->C_clear_color.a > 250)
	{
		WAS_->render_texture_obj.clear (WAS_->C_clear_color);
		WAS_->window_obj.clear (WAS_->C_clear_color);
	}
	else
	{
		WAS_->render_texture_obj.clear (WAS_->C_defolt_window);
		WAS_->window_obj.clear (WAS_->C_defolt_window);
	}
}
void WindowAndStyles::clear_rectangle ()
{
	WindowAndStyles* WAS_ = getClass ();
	WAS_->rectangle_shape_obj.setSize (Vector2f (WAS_->camera.getSize ()));
	WAS_->rectangle_shape_obj.setPosition (WAS_->camera.getCenter ().x - WAS_->camera.getSize ().x * 0.5,
			WAS_->camera.getCenter ().y - WAS_->camera.getSize ().y * 0.5);
}
void WindowAndStyles::clear_draw ()
{
	WindowAndStyles* WAS_ = getClass ();
	bool b_introduction (names::game_status == GameStatus::introduction);
	bool b_loading (names::game_status == GameStatus::loading);
	bool b_loading_to_main_menu (names::game_status == GameStatus::loading_to_main_menu);
	bool b_main_menu (names::game_status == GameStatus::main_menu);
	bool b_main_menu_to_person_menu (names::game_status == GameStatus::main_menu_to_person_menu);
	bool b_language_menu (names::game_status == GameStatus::language_menu);
	bool b_person_menu (names::game_status == GameStatus::person_menu);
	bool b_works_menu_to_main_menu (names::game_status == GameStatus::works_menu_to_main_menu);
	bool b_works_menu (names::game_status == GameStatus::works_menu);
	bool b_learn (names::game_status == GameStatus::learn);
	bool b_test (names::game_status == GameStatus::test);
	vector <Pingvinon>& P_ = Introduction::getPingvinons ();
	vector <RectangleShape>& RS_MM_ = MainMenu::getBackground ();
	vector <Text>& T_ = Error_class::getText ();
	RectangleShape& RS_WM_ = WorksMenu::getDownPanel ();

//boxes

	if (b_introduction)
	{
		for (size_t st (0); st < Introduction::size_sprites; st++)
		{
			WAS_->render_texture_obj.draw (Introduction::getSprite ()[st]);
		}
		for (size_t st (0); st < P_.size (); st++)
		{
			if (P_[st].RS.getGlobalBounds ().intersects (WAS_->rectangle_shape_obj.getGlobalBounds ()))
			{
				WAS_->render_texture_obj.draw (P_[st].RS);
			}
		}
	}
	else if (b_loading or b_loading_to_main_menu)
	{
		for (size_t st (0); st < P_.size (); st++)
		{
			if (P_[st].RS.getGlobalBounds ().intersects (WAS_->rectangle_shape_obj.getGlobalBounds ()))
			{
				WAS_->render_texture_obj.draw (P_[st].RS);
			}
		}
		WAS_->render_texture_obj.draw (Loading::getSprite ());
		WAS_->render_texture_obj.draw (Loading::getSpriteText ());
		WAS_->render_texture_obj.draw (Loading::getLoadText ());
	}

	if (b_loading_to_main_menu or b_main_menu or b_main_menu_to_person_menu or b_works_menu_to_main_menu)
	{
		for (size_t st (0); st < RS_MM_.size (); st++)
		{
			if (RS_MM_[st].getGlobalBounds ().intersects (WAS_->rectangle_shape_obj.getGlobalBounds ()))
			{
				WAS_->render_texture_obj.draw (RS_MM_[st]);
			}
		}
		draw (MainMenu::getPopingvinit ());
		draw (MainMenu::getSdatca ());
		if (MainMenu::getPopingvini ().getGlobalBounds ().intersects (WAS_->rectangle_shape_obj.getGlobalBounds ()))
		{
			WAS_->render_texture_obj.draw (MainMenu::getPopingvini ());
		}
		draw (MainMenu::getWardrobe ());
		WAS_->render_texture_obj.draw (MainMenu::getTitle ());
		for (size_t st (0); st < RS_MM_.size (); st++)
		{
			WAS_->render_texture_obj.draw (MainMenu::getIce ()[st]);
		}
	}

	if (b_main_menu_to_person_menu or b_person_menu or b_language_menu or b_works_menu or b_learn or b_test or b_works_menu_to_main_menu)
	{
		for (size_t st (0); st < PersonMenu::getBackground ().size (); st++)
		{
			WAS_->render_texture_obj.draw (PersonMenu::getBackground ()[st]);
		}
	}
	if (b_main_menu_to_person_menu or b_person_menu or b_language_menu)
	{
		draw (PersonMenu::getCustom ());
		draw (PersonMenu::getIntegrated ());
	}

	if (b_language_menu or b_works_menu)
	{
		draw (LanguageMenu::getPythonButton ());
	}

	if (b_works_menu or b_works_menu_to_main_menu)
	{
		WAS_->render_texture_obj.draw (WorksMenu::getMiddleTextUpPanel ());
	}

	if (b_works_menu or b_test or b_learn or b_works_menu_to_main_menu)
	{
		draw (WorksMenu::getUpPanel ());
		WAS_->render_texture_obj.draw (WorksMenu::getLeftTextUpPanel ());
		WAS_->render_texture_obj.draw (WorksMenu::getRightTextUpPanel ());
		WAS_->render_texture_obj.draw (WorksMenu::getDownPanel ());
		Sprite S (WorksMenu::getRender ().getTexture ());
		S.setPosition (
				RS_WM_.getPosition ().x,
				RS_WM_.getPosition ().y
				);
		WAS_->render_texture_obj.draw (S);
	}

//hitboxes

	if (names::b_hitboxes_is_drawn)
	{
		if (PC_Mouse::getGlobalBounds ().intersects (WAS_->rectangle_shape_obj.getGlobalBounds ()))
		{
			WAS_->render_texture_obj.draw (PC_Mouse::getHitBox ());
			WAS_->render_texture_obj.draw (PC_Mouse::getTextBox ());
		}
	}

//errors
	WAS_->render_texture_obj.draw (Error_class::getRectangleShape ());
	for (size_t st (0); st < T_.size (); st++)
	{
		WAS_->render_texture_obj.draw (T_[st]);
	}
}
void WindowAndStyles::clear_display ()
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->render_texture_obj.display ();
	Sprite S (WAS_->render_texture_obj.getTexture ());
	S.setScale (names::u_factor_of_resolution, names::u_factor_of_resolution);
	WAS_->window_obj.draw (S);
	WAS_->window_obj.display ();
}

//public
//WindowAndStyles*

WindowAndStyles* WindowAndStyles::getClass ()
{
	if (class_obj)
		return class_obj;

	class_obj = new WindowAndStyles ();
	return class_obj;
}

//void

void WindowAndStyles::start ()
{
	WindowAndStyles* WAS_ = getClass ();

	names::LoadFromMemory (WAS_->image_obj, icon_png, icon_png_size, "Images/icon.png");

	WAS_->videomode_obj = VideoMode::getDesktopMode ();

	WAS_->window_obj.create (
			VideoMode (WAS_->videomode_obj.width, WAS_->videomode_obj.height),
			WAS_->w_game_name
			);
	WAS_->render_texture_obj.create (
			static_cast <float> (WAS_->window_obj.getSize ().x) / names::u_factor_of_resolution,
			static_cast <float> (WAS_->window_obj.getSize ().y) / names::u_factor_of_resolution
					);
	WAS_->now = Default;
	WAS_->window_obj.setIcon (WAS_->image_obj.getSize ().x, WAS_->image_obj.getSize ().y,
			WAS_->image_obj.getPixelsPtr ());

//camera
	WAS_->camera.setCenter (Vector2f (
			static_cast <float> (WAS_->window_obj.getSize ().x) * 0.5,
			static_cast <float> (WAS_->window_obj.getSize ().y) * 0.5
					));
	WAS_->camera.setSize (Vector2f (
			static_cast <float> (WAS_->window_obj.getSize ().x),
			static_cast <float> (WAS_->window_obj.getSize ().y)
			));
	WAS_->render_texture_obj.setView (WAS_->camera);
	WAS_->window_obj.setView (WAS_->camera);
}
void WindowAndStyles::main ()
{
//time work
	main_time_work ();

//F11
	main_F11 ();

//close
	main_event ();
}
void WindowAndStyles::clear ()
{
//clear
	clear_clear ();

//rectangle
	clear_rectangle ();

//draw
	clear_draw ();

//display
	clear_display ();
}
void WindowAndStyles::setColor (Color C)
{
	WindowAndStyles* WAS_ = getClass ();
	WAS_->C_clear_color = C;
}

//bool

bool WindowAndStyles::isOpen ()
{
	return getClass ()->window_obj.isOpen ();
}
bool WindowAndStyles::hasFocus ()
{
	return getClass ()->window_obj.hasFocus ();
}

//float

float WindowAndStyles::getFactorX ()
{
	WindowAndStyles* WAS_ = getClass ();
	return WAS_->rectangle_shape_obj.getGlobalBounds ().width / WAS_->f_size_pix.x;
}
float WindowAndStyles::getFactorY ()
{
	WindowAndStyles* WAS_ = getClass ();
	return WAS_->rectangle_shape_obj.getGlobalBounds ().height / WAS_->f_size_pix.y;
}
float WindowAndStyles::getPixelsSizeX ()
{
	return getClass ()->f_size_pix.x;
}
float WindowAndStyles::getPixelsSizeY ()
{
	return getClass ()->f_size_pix.y;
}

//Window&

Window& WindowAndStyles::getWindow ()
{
	return getClass ()->window_obj;
}

//FloatRect

FloatRect WindowAndStyles::getGlobalBounds ()
{
	return getClass ()->rectangle_shape_obj.getGlobalBounds ();
}

//Color

Color WindowAndStyles::getDefoultColor ()
{
	return getClass ()->C_defolt_window;
}

void WindowAndStyles::main_destroy ()
{
	MainMenu::destroy ();
	PersonMenu::destroy ();
	WorksMenu::destroy ();
	LearnMenu::destroy ();
	TestMenu::destroy ();
}

void WindowAndStyles::draw (const Button& B)
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->render_texture_obj.draw (B.getRectangleShape ());
	if (names::b_hitboxes_is_drawn)
	{
		WAS_->render_texture_obj.draw (B.getText ());
	}
}

void WindowAndStyles::close ()
{
	Loading::write ();
	getClass ()->window_obj.close ();
}
