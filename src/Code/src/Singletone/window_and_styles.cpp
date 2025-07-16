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

// private

WindowAndStyles* WindowAndStyles::m_class_obj = NULL;

WindowAndStyles::WindowAndStyles ()
    : m_f_SIZE_PIX (300.0, 150.0),

      m_rectangle_shape (m_f_SIZE_PIX),

      m_style_window (Default),

      m_f_time_since_clicking (0),

      m_w_game_name (L"Попингвини"),

      m_C_DEFOLT_WINDOW (22, 23, 26, 255),
      m_C_clear_color (0, 0, 0, 255)
{
}

// protected
// void
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

	WAS_->m_f_time_since_clicking += names::f_microsec * names::f_time;

	if (Keyboard::isKeyPressed (Keyboard::F11) and WAS_->m_f_time_since_clicking > 1.0 and WAS_->m_render_window.hasFocus ())
	{
		if (WAS_->m_style_window == Default)
		{
			WAS_->m_video_mode = VideoMode::getFullscreenModes ()[0];
			WAS_->m_render_texture.create (
			    WAS_->m_video_mode.width / names::u_factor_of_resolution,
			    WAS_->m_video_mode.height / names::u_factor_of_resolution);
			WAS_->m_render_window.create (
			    VideoMode (WAS_->m_video_mode.width, WAS_->m_video_mode.height),
			    WAS_->m_w_game_name,
			    Style::Fullscreen);

			WAS_->m_view.setCenter (Vector2f (
			    static_cast<float> (WAS_->m_video_mode.width) * 0.5,
			    static_cast<float> (WAS_->m_video_mode.height) * 0.5));
			WAS_->m_view.setSize (Vector2f (
			    static_cast<float> (WAS_->m_video_mode.width),
			    static_cast<float> (WAS_->m_video_mode.height)));
			WAS_->m_render_texture.setView (WAS_->m_view);
			WAS_->m_render_window.setView (WAS_->m_view);

			main_destroy ();

			WAS_->m_style_window = Fullscreen;
			WAS_->m_f_time_since_clicking = 0.0;
		}
		else if (WAS_->m_style_window == Fullscreen)
		{
			WAS_->m_video_mode = VideoMode::getDesktopMode ();
			WAS_->m_render_window.create (
			    VideoMode (WAS_->m_video_mode.width, WAS_->m_video_mode.height),
			    WAS_->m_w_game_name,
			    Style::Default);
			WAS_->m_render_texture.create (
			    static_cast<float> (WAS_->m_render_window.getSize ().x) / names::u_factor_of_resolution,
			    static_cast<float> (WAS_->m_render_window.getSize ().y) / names::u_factor_of_resolution);

			WAS_->m_view.setCenter (Vector2f (
			    static_cast<float> (WAS_->m_render_window.getSize ().x) * 0.5,
			    static_cast<float> (WAS_->m_render_window.getSize ().y) * 0.5));
			WAS_->m_view.setSize (Vector2f (
			    static_cast<float> (WAS_->m_render_window.getSize ().x),
			    static_cast<float> (WAS_->m_render_window.getSize ().y)));
			WAS_->m_render_texture.setView (WAS_->m_view);
			WAS_->m_render_window.setView (WAS_->m_view);

			main_destroy ();

			WAS_->m_style_window = Default;
			WAS_->m_f_time_since_clicking = 0;
		}
	}
}
void WindowAndStyles::main_event ()
{
	WindowAndStyles* WAS_ = getClass ();

	while (WAS_->m_render_window.pollEvent (names::E_event))
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

		//_view
		WAS_->m_view.setCenter (Vector2f (
		    static_cast<float> (names::E_event.size.width) * 0.5,
		    static_cast<float> (names::E_event.size.height) * 0.5));
		WAS_->m_view.setSize (Vector2f (
		    static_cast<float> (names::E_event.size.width),
		    static_cast<float> (names::E_event.size.height)));
		WAS_->m_render_texture.create (
		    WAS_->m_view.getSize ().x / names::u_factor_of_resolution,
		    WAS_->m_view.getSize ().y / names::u_factor_of_resolution);
		WAS_->m_render_texture.setView (WAS_->m_view);
		WAS_->m_render_window.setView (WAS_->m_view);

		main_destroy ();
	}
}
void WindowAndStyles::clear_clear ()
{
	WindowAndStyles* WAS_ = getClass ();
	if (WAS_->m_C_clear_color.a > 250)
	{
		WAS_->m_render_texture.clear (WAS_->m_C_clear_color);
		WAS_->m_render_window.clear (WAS_->m_C_clear_color);
	}
	else
	{
		WAS_->m_render_texture.clear (WAS_->m_C_DEFOLT_WINDOW);
		WAS_->m_render_window.clear (WAS_->m_C_DEFOLT_WINDOW);
	}
}
void WindowAndStyles::clear_rectangle ()
{
	WindowAndStyles* WAS_ = getClass ();
	WAS_->m_rectangle_shape.setSize (Vector2f (WAS_->m_view.getSize ()));
	WAS_->m_rectangle_shape.setPosition (WAS_->m_view.getCenter ().x - WAS_->m_view.getSize ().x * 0.5,
	                                     WAS_->m_view.getCenter ().y - WAS_->m_view.getSize ().y * 0.5);
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
	vector<Pingvinon>& P_ = Introduction::getPingvinons ();
	vector<RectangleShape>& RS_MM_ = MainMenu::getBackground ();
	vector<Text>& T_ = Error_class::getText ();
	RectangleShape& RS_WM_ = WorksMenu::getDownPanel ();

	// boxes

	if (b_introduction)
	{
		WAS_->m_render_texture.draw (Introduction::getAnimSprite ());
		for (size_t st (0); st < P_.size (); st++)
		{
			if (P_[st].rectangle.getGlobalBounds ().intersects (WAS_->m_rectangle_shape.getGlobalBounds ()))
			{
				WAS_->m_render_texture.draw (P_[st].rectangle);
			}
		}
		WAS_->m_render_texture.draw (Introduction::getLightSprite ());
	}
	else if (b_loading or b_loading_to_main_menu)
	{
		for (size_t st (0); st < P_.size (); st++)
		{
			if (P_[st].rectangle.getGlobalBounds ().intersects (WAS_->m_rectangle_shape.getGlobalBounds ()))
			{
				WAS_->m_render_texture.draw (P_[st].rectangle);
			}
		}
		WAS_->m_render_texture.draw (Loading::getSprite ());
		WAS_->m_render_texture.draw (Loading::getSpriteText ());
		WAS_->m_render_texture.draw (Loading::getLoadText ());
	}

	if (b_loading_to_main_menu or b_main_menu or b_main_menu_to_person_menu or b_works_menu_to_main_menu)
	{
		for (size_t st (0); st < RS_MM_.size (); st++)
		{
			if (RS_MM_[st].getGlobalBounds ().intersects (WAS_->m_rectangle_shape.getGlobalBounds ()))
			{
				WAS_->m_render_texture.draw (RS_MM_[st]);
			}
		}
		draw (MainMenu::getPopingvinit ());
		draw (MainMenu::getSdatca ());
		if (MainMenu::getPopingvini ().getGlobalBounds ().intersects (WAS_->m_rectangle_shape.getGlobalBounds ()))
		{
			WAS_->m_render_texture.draw (MainMenu::getPopingvini ());
		}
		draw (MainMenu::getWardrobe ());
		WAS_->m_render_texture.draw (MainMenu::getTitle ());
		for (size_t st (0); st < RS_MM_.size (); st++)
		{
			WAS_->m_render_texture.draw (MainMenu::getIce ()[st]);
		}
	}

	if (b_main_menu_to_person_menu or b_person_menu or b_language_menu or b_works_menu or b_learn or b_test or b_works_menu_to_main_menu)
	{
		for (size_t st (0); st < PersonMenu::getBackground ().size (); st++)
		{
			WAS_->m_render_texture.draw (PersonMenu::getBackground ()[st]);
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
		WAS_->m_render_texture.draw (WorksMenu::getMiddleTextUpPanel ());
	}

	if (b_works_menu or b_test or b_learn or b_works_menu_to_main_menu)
	{
		draw (WorksMenu::getUpPanel ());
		WAS_->m_render_texture.draw (WorksMenu::getLeftTextUpPanel ());
		WAS_->m_render_texture.draw (WorksMenu::getRightTextUpPanel ());
		WAS_->m_render_texture.draw (WorksMenu::getDownPanel ());
		Sprite S (WorksMenu::getRender ().getTexture ());
		S.setPosition (
		    RS_WM_.getPosition ().x,
		    RS_WM_.getPosition ().y);
		WAS_->m_render_texture.draw (S);
	}

	// hitboxes

	if (names::b_hitboxes_is_drawn)
	{
		if (PC_Mouse::getGlobalBounds ().intersects (WAS_->m_rectangle_shape.getGlobalBounds ()))
		{
			WAS_->m_render_texture.draw (PC_Mouse::getHitBox ());
			WAS_->m_render_texture.draw (PC_Mouse::getTextBox ());
		}
	}

	// errors
	WAS_->m_render_texture.draw (Error_class::getRectangleShape ());
	for (size_t st (0); st < T_.size (); st++)
	{
		WAS_->m_render_texture.draw (T_[st]);
	}
}
void WindowAndStyles::clear_display ()
{
	WindowAndStyles* WAS_ = getClass ();

	WAS_->m_render_texture.display ();
	Sprite S (WAS_->m_render_texture.getTexture ());
	S.setScale (names::u_factor_of_resolution, names::u_factor_of_resolution);
	WAS_->m_render_window.draw (S);
	WAS_->m_render_window.display ();
}

// public
// WindowAndStyles*

WindowAndStyles* WindowAndStyles::getClass ()
{
	if (m_class_obj)
		return m_class_obj;

	m_class_obj = new WindowAndStyles ();
	return m_class_obj;
}

// void

void WindowAndStyles::start ()
{
	WindowAndStyles* WAS_ = getClass ();

	names::LoadFromMemory (WAS_->m_image, icon_png, icon_png_size, "Images/icon.png");

	WAS_->m_video_mode = VideoMode::getDesktopMode ();

	WAS_->m_render_window.create (
	    VideoMode (WAS_->m_video_mode.width, WAS_->m_video_mode.height),
	    WAS_->m_w_game_name);
	WAS_->m_render_texture.create (
	    static_cast<float> (WAS_->m_render_window.getSize ().x) / names::u_factor_of_resolution,
	    static_cast<float> (WAS_->m_render_window.getSize ().y) / names::u_factor_of_resolution);
	WAS_->m_style_window = Default;
	WAS_->m_render_window.setIcon (WAS_->m_image.getSize ().x, WAS_->m_image.getSize ().y,
	                               WAS_->m_image.getPixelsPtr ());

	//_view
	WAS_->m_view.setCenter (Vector2f (
	    static_cast<float> (WAS_->m_render_window.getSize ().x) * 0.5,
	    static_cast<float> (WAS_->m_render_window.getSize ().y) * 0.5));
	WAS_->m_view.setSize (Vector2f (
	    static_cast<float> (WAS_->m_render_window.getSize ().x),
	    static_cast<float> (WAS_->m_render_window.getSize ().y)));
	WAS_->m_render_texture.setView (WAS_->m_view);
	WAS_->m_render_window.setView (WAS_->m_view);
}
void WindowAndStyles::main ()
{
	// time work
	main_time_work ();

	// F11
	main_F11 ();

	// close
	main_event ();
}
void WindowAndStyles::clear ()
{
	// clear
	clear_clear ();

	// rectangle
	clear_rectangle ();

	// draw
	clear_draw ();

	// display
	clear_display ();
}
void WindowAndStyles::setColor (Color C)
{
	WindowAndStyles* WAS_ = getClass ();
	WAS_->m_C_clear_color = C;
}

// bool

bool WindowAndStyles::isOpen ()
{
	return getClass ()->m_render_window.isOpen ();
}
bool WindowAndStyles::hasFocus ()
{
	return getClass ()->m_render_window.hasFocus ();
}

// float

float WindowAndStyles::getFactorX ()
{
	WindowAndStyles* WAS_ = getClass ();
	return WAS_->m_rectangle_shape.getGlobalBounds ().width / WAS_->m_f_SIZE_PIX.x;
}
float WindowAndStyles::getFactorY ()
{
	const WindowAndStyles* WAS_ = getClass ();
	return WAS_->m_rectangle_shape.getSize ().y / WAS_->m_f_SIZE_PIX.y;
}
float WindowAndStyles::getPixelsSizeX ()
{
	return getClass ()->m_f_SIZE_PIX.x;
}
float WindowAndStyles::getPixelsSizeY ()
{
	return getClass ()->m_f_SIZE_PIX.y;
}

// Window&

Window& WindowAndStyles::getWindow ()
{
	return getClass ()->m_render_window;
}

// FloatRect

FloatRect WindowAndStyles::getGlobalBounds ()
{
	return getClass ()->m_rectangle_shape.getGlobalBounds ();
}

// Color

Color WindowAndStyles::getDefoultColor ()
{
	return getClass ()->m_C_DEFOLT_WINDOW;
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

	WAS_->m_render_texture.draw (B.getRectangleShape ());
	if (names::b_hitboxes_is_drawn)
	{
		WAS_->m_render_texture.draw (B.getText ());
	}
}

void WindowAndStyles::close ()
{
	Loading::write ();
	getClass ()->m_render_window.close ();
}
