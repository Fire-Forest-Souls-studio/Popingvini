#include "../../includes/Singletone/works_menu.h"

#include "../../includes/Singletone/color_table.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/person_menu.h"
#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/learn_menu.h"
#include "../../includes/Singletone/test_menu.h"

WorksMenu* WorksMenu::class_obj = NULL;

Language* WorksMenu::language = NULL;

WorksMenu::WorksMenu ()
    : _B_up_panel ("WM/button/up_panel"),

      _f_BIG_FONT_SCALE (6.0),
      _f_MIDDLE_BIG_FONT_SCALE (8.0),
      _f_MIDDLE_SMALL_FONT_SCALE (3.75),
      _f_SMALL_FONT_SCALE (3.0),
      _f_SPEED_MOVE_BLOCKS (5.0),
      _f_WIGHT_SIMVOL_BIG_FONT (3.264367816),
      _f_WIGHT_SIMVOL_MIDDLE_BIG_FONT (_f_WIGHT_SIMVOL_BIG_FONT / _f_BIG_FONT_SCALE * _f_MIDDLE_BIG_FONT_SCALE),
      _f_WIGHT_SIMVOL_MIDDLE_SMALL_FONT (_f_WIGHT_SIMVOL_BIG_FONT / _f_BIG_FONT_SCALE * _f_MIDDLE_SMALL_FONT_SCALE),
      _f_WIGHT_SIMVOL_SMALL_FONT (_f_WIGHT_SIMVOL_BIG_FONT / _f_BIG_FONT_SCALE * _f_SMALL_FONT_SCALE),
      _f_move_blocks (0.0),

      _i_OUT_UP (5),
      _i_OUT_LEFT (15),
      _i_OUT_BETWEEN (3),
      _i_IN_UP (1),
      _i_IN_LEFT (1),
      _i_IN_BETWEEN (3),
      _i_BLOCK_UP (3),
      _i_BLOCK_LEFT (3),
      _i_BLOCK_BETWEEN (2),

      _V2f_size_up_panel (0, 8),
      _V2f_size_down_panel (0, 0),
      _V2f_size_block_icon (43, 38),

      _work_block (0)
{
	_B_up_panel.setSize (_V2f_size_up_panel);
	_B_up_panel.setFillColor (Color::Transparent);
	_B_up_panel.setOutline (Color::Transparent);
	_T_up_panel_left.setFillColor (Color::Transparent);
	_T_up_panel_left.setFont (names::F_pixel);
	_T_up_panel_middle.setFillColor (Color::Transparent);
	_T_up_panel_middle.setFont (names::F_pixel);
	_T_up_panel_middle.setString (L"<-");
	_T_up_panel_right.setFillColor (Color::Transparent);
	_T_up_panel_right.setFont (names::F_pixel);
	_RS_down_panel.setFillColor (Color::Transparent);
	_RS_down_panel.setOutlineColor (Color::Transparent);
	_RS_down_panel.setOutlineThickness (1);
}

WorksMenu* WorksMenu::getClass ()
{
	if (class_obj)
		return class_obj;

	class_obj = new WorksMenu ();
	return class_obj;
}

void WorksMenu::destroy ()
{
	WorksMenu* WM_ = getClass ();

	float f = WindowAndStyles::getFactorY ();

	WM_->_V2f_size_up_panel = Vector2f (
	    WindowAndStyles::getGlobalBounds ().width / f - WM_->_i_OUT_LEFT * 2 - 2,
	    WM_->_V2f_size_up_panel.y);
	WM_->_B_up_panel.setSize (WM_->_V2f_size_up_panel);

	resizeWindow ();

	if (language)
	{
		for (size_t st (0); st < language->work.size (); st++)
		{
			WM_->_work_block[st].resize (language->work[st]);
		}
	}
}
void WorksMenu::main ()
{
	main_load ();
	main_all ();
	main_works_menu ();
	main_transitionOf ();
}

void WorksMenu::setLanguage (Language* L)
{
	WorksMenu* WM_ = getClass ();

	language = L;
	WM_->_work_block.resize (language->work.size ());
	for (size_t st (0); st < language->work.size (); st++)
	{
		WM_->_work_block[st].build (st, language->work[st]);
		WM_->_work_block[st]._RS_icon.setTexture (&WM_->_texture);
	}

	stringUpdate ();
}

void WorksMenu::start ()
{
	resizeWindow ();
}

void WorksMenu::clear ()
{
	bool b = names::b_hitboxes_is_drawn;
	GameStatus GS = names::game_status;
	WorksMenu* WM_ = getClass ();

	WM_->_render_texture.clear (Color::Transparent);

	if (language)
	{
		if (GS == GameStatus::works_menu or GS == GameStatus::works_menu_to_main_menu)
		{
			for (size_t st (0); st < language->work.size (); st++)
			{
				if (WM_->_work_block[st]._button.getRectangleShape ().getGlobalBounds ().intersects (WindowAndStyles::getGlobalBounds ()))
				{
					WM_->_render_texture.draw (WM_->_work_block[st]._button.getRectangleShape ());
					if (b)
					{
						WM_->_render_texture.draw (WM_->_work_block[st]._button.getText ());
					}
					WM_->_render_texture.draw (WM_->_work_block[st]._RS_icon);
					WM_->_render_texture.draw (WM_->_work_block[st]._T_name);
					WM_->_render_texture.draw (WM_->_work_block[st]._T_type);
					WM_->_render_texture.draw (WM_->_work_block[st]._RS_content);
					WM_->_render_texture.draw (WM_->_work_block[st]._T_content);
					WM_->_render_texture.draw (WM_->_work_block[st]._T_score);
				}
			}
		}
		else if (GS == GameStatus::learn)
		{
			WM_->_render_texture.draw (LearnMenu::getRectangleShape ());
			WM_->_render_texture.draw (LearnMenu::getText ());
			WM_->_render_texture.draw (LearnMenu::getButton ().getRectangleShape ());
			WM_->_render_texture.draw (LearnMenu::getButton ().getText ());
		}
		else if (GS == GameStatus::test)
		{
			WM_->_render_texture.draw (TestMenu::getRectangleShape ());
			WM_->_render_texture.draw (TestMenu::getRectangleShapeImage ());
			WM_->_render_texture.draw (TestMenu::getTextQuestion ());
			for (size_t st (0); st < TestMenu::getButtons ().size (); st++)
			{
				WM_->_render_texture.draw (TestMenu::getButtons ()[st]._text);
				if (names::b_hitboxes_is_drawn)
				{
					WM_->_render_texture.draw (TestMenu::getButtons ()[st].getRectangleShape ());
					WM_->_render_texture.draw (TestMenu::getButtons ()[st].getText ());
				}
			}
		}
	}

	WM_->_render_texture.display ();
}

Button& WorksMenu::getUpPanel ()
{
	return getClass ()->_B_up_panel;
}

Text& WorksMenu::getLeftTextUpPanel ()
{
	return getClass ()->_T_up_panel_left;
}
Text& WorksMenu::getMiddleTextUpPanel ()
{
	return getClass ()->_T_up_panel_middle;
}
Text& WorksMenu::getRightTextUpPanel ()
{
	return getClass ()->_T_up_panel_right;
}

RenderTexture& WorksMenu::getRender ()
{
	return getClass ()->_render_texture;
}

RectangleShape& WorksMenu::getDownPanel ()
{
	return getClass ()->_RS_down_panel;
}

void WorksMenu::resizeWindow ()
{
	float f = WindowAndStyles::getFactorY ();

	WorksMenu* WM_ = getClass ();

	WM_->_V2f_size_down_panel = Vector2f (
	    WindowAndStyles::getGlobalBounds ().width / f - WM_->_i_OUT_LEFT * 2 - 2,
	    WindowAndStyles::getPixelsSizeY () - WM_->_i_OUT_UP - 2 - WM_->_V2f_size_up_panel.y - WM_->_i_OUT_BETWEEN * 2 - 2);
	WM_->_RS_down_panel.setSize (WM_->_V2f_size_down_panel);
	WM_->_render_texture.create (
	    WM_->_V2f_size_down_panel.x * f,
	    WM_->_V2f_size_down_panel.y * f);

	WM_->_view.setCenter (Vector2f (
	    (WM_->_V2f_size_down_panel.x * 0.5 +
	     WM_->_i_OUT_LEFT + 1) *
	        f,
	    (WM_->_V2f_size_down_panel.y * 0.5 +
	     WM_->_i_OUT_UP + 2 + WM_->_i_OUT_BETWEEN + 1 + WM_->_V2f_size_up_panel.y) *
	        f));

	WM_->_view.setSize (
	    (WM_->_V2f_size_down_panel.x + 2) * f,
	    (WM_->_V2f_size_down_panel.y + 2) * f);
	WM_->_render_texture.setView (WM_->_view);
}

int WorksMenu::getIOutUp ()
{
	return getClass ()->_i_OUT_UP;
}
int WorksMenu::getIOutLeft ()
{
	return getClass ()->_i_OUT_LEFT;
}
int WorksMenu::getIOutBetween ()
{
	return getClass ()->_i_OUT_BETWEEN;
}
int WorksMenu::getIInUp ()
{
	return getClass ()->_i_IN_UP;
}
int WorksMenu::getIInLeft ()
{
	return getClass ()->_i_IN_LEFT;
}
int WorksMenu::getIInBetween ()
{
	return getClass ()->_i_IN_BETWEEN;
}

void WorksMenu::setMoveBlocks (float f)
{
	WorksMenu* WM_ = getClass ();

	if (names::game_status == GameStatus::works_menu or names::game_status == GameStatus::works_menu_to_main_menu)
	{
		if ((f > 0 and WM_->_work_block[0]._button.getGlobalBounds ().top < WM_->_RS_down_panel.getPosition ().y) or (f < 0 and WM_->_work_block[WM_->_work_block.size () - 1]._button.getGlobalBounds ().top + WM_->_work_block[WM_->_work_block.size () - 1]._button.getGlobalBounds ().height > WM_->_RS_down_panel.getPosition ().y + WM_->_RS_down_panel.getGlobalBounds ().height))
		{
			WM_->_f_move_blocks += f * WM_->_f_SPEED_MOVE_BLOCKS;
		}
	}
	else if (names::game_status == GameStatus::learn)
	{
		if ((f > 0 and LearnMenu::getText ().getGlobalBounds ().top - WM_->_RS_down_panel.getGlobalBounds ().height * 0.5 < WM_->_RS_down_panel.getPosition ().y) or (f < 0 and LearnMenu::getText ().getGlobalBounds ().top + LearnMenu::getText ().getGlobalBounds ().height + WM_->_RS_down_panel.getGlobalBounds ().height * 0.5 > WM_->_RS_down_panel.getPosition ().y + WM_->_RS_down_panel.getGlobalBounds ().height))
		{
			WM_->_f_move_blocks += f * WM_->_f_SPEED_MOVE_BLOCKS;
		}
	}
	else if (names::game_status == GameStatus::test)
	{
		if ((f > 0 and TestMenu::getTextQuestion ().getGlobalBounds ().top - WM_->_RS_down_panel.getGlobalBounds ().height * 0.5 < WM_->_RS_down_panel.getPosition ().y) or (f < 0 and TestMenu::getButtons ()[TestMenu::getButtons ().size () - 1].getGlobalBounds ().top + TestMenu::getButtons ()[TestMenu::getButtons ().size () - 1].getGlobalBounds ().height + WM_->_RS_down_panel.getGlobalBounds ().height * 0.5 > WM_->_RS_down_panel.getPosition ().y + WM_->_RS_down_panel.getGlobalBounds ().height))
		{
			WM_->_f_move_blocks += f * WM_->_f_SPEED_MOVE_BLOCKS;
		}
	}
}

Vector2f WorksMenu::getSizeBlockIcon ()
{
	return getClass ()->_V2f_size_block_icon;
}

Texture& WorksMenu::getTexture ()
{
	return getClass ()->_texture;
}

int WorksMenu::getBlockUp ()
{
	return getClass ()->_i_BLOCK_UP;
}
int WorksMenu::getBlockLeft ()
{
	return getClass ()->_i_BLOCK_LEFT;
}
int WorksMenu::getBlockBetween ()
{
	return getClass ()->_i_BLOCK_BETWEEN;
}

float WorksMenu::getBigFontScale ()
{
	return getClass ()->_f_BIG_FONT_SCALE;
}
float WorksMenu::getMiddleBigFontScale ()
{
	return getClass ()->_f_MIDDLE_BIG_FONT_SCALE;
}
float WorksMenu::getMiddleSmallFontScale ()
{
	return getClass ()->_f_MIDDLE_SMALL_FONT_SCALE;
}
float WorksMenu::getSmallFontScale ()
{
	return getClass ()->_f_SMALL_FONT_SCALE;
}
float WorksMenu::getWidthSimvolBigFont ()
{
	return getClass ()->_f_WIGHT_SIMVOL_BIG_FONT;
}
float WorksMenu::getWidthSimvolMiddleBigFont ()
{
	return getClass ()->_f_WIGHT_SIMVOL_MIDDLE_BIG_FONT;
}
float WorksMenu::getWidthSimvolMiddleSmallFont ()
{
	return getClass ()->_f_WIGHT_SIMVOL_MIDDLE_SMALL_FONT;
}
float WorksMenu::getWidthSimvolSmallFont ()
{
	return getClass ()->_f_WIGHT_SIMVOL_SMALL_FONT;
}

void WorksMenu::main_load ()
{
	if (Loading::getLoad ())
	{
		destroy ();
	}
}
void WorksMenu::main_all ()
{
	WorksMenu* WM_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (names::game_status == GameStatus::works_menu or names::game_status == GameStatus::test or names::game_status == GameStatus::learn or names::game_status == GameStatus::works_menu_to_main_menu)
	{

		WM_->_B_up_panel.setScale (f);
		WM_->_B_up_panel.setPosition (
		    (WM_->_i_OUT_LEFT + 1) * f,
		    (WM_->_i_OUT_UP + 1) * f);

		WM_->_T_up_panel_left.setCharacterSize (WM_->_f_BIG_FONT_SCALE * f);
		WM_->_T_up_panel_left.setPosition (
		    WM_->_B_up_panel.getGlobalBounds ().left + 2 * f,
		    WM_->_B_up_panel.getGlobalBounds ().top + 1 * f);

		WM_->_T_up_panel_right.setCharacterSize (WM_->_f_BIG_FONT_SCALE * f);
		WM_->_T_up_panel_right.setPosition (
		    WM_->_B_up_panel.getGlobalBounds ().left + WM_->_B_up_panel.getGlobalBounds ().width - 2 * f - WM_->_T_up_panel_right.getGlobalBounds ().width,
		    WM_->_B_up_panel.getGlobalBounds ().top + 1 * f);

		if (Keyboard::isKeyPressed (Keyboard::F11))
		{
			resizeWindow ();
		}

		WM_->_RS_down_panel.setScale (f, f);
		WM_->_RS_down_panel.setPosition (
		    (WM_->_i_OUT_LEFT + 1) * f,
		    (WM_->_i_OUT_UP + 1 + WM_->_V2f_size_up_panel.y + 1 + WM_->_i_OUT_BETWEEN + 1) * f);
	}
}
void WorksMenu::main_works_menu ()
{
	bool b = names::game_status == GameStatus::works_menu;
	float f_factor_y = WindowAndStyles::getFactorY ();
	float& f_frame_transition = PersonMenu::getFrameTransition ();
	WorksMenu* WM_ = getClass ();
	GameStatus& GS = names::game_status;

	if (b or GS == GameStatus::works_menu_to_main_menu)
	{
		if (b)
		{
			if (f_frame_transition < 255.0)
			{
				WM_->_B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, f_frame_transition / 255.0 * ColorTable::c25a75.a));
				WM_->_B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, f_frame_transition));
				WM_->_T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, f_frame_transition));
				WM_->_T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, f_frame_transition));
				WM_->_T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, f_frame_transition));
				WM_->_RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, f_frame_transition / 255.0 * ColorTable::c25a75.a));
				WM_->_RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, f_frame_transition));
			}
			else if (f_frame_transition != 255.0)
			{
				f_frame_transition = 255.0;
				WM_->_B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 75.0));
				WM_->_B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 255.0));
				WM_->_T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 255.0));
				WM_->_T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, 255.0));
				WM_->_T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 255.0));
				WM_->_RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 75.0));
				WM_->_RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 255.0));
			}
			else
			{
				for (size_t st (0); st < WM_->_work_block.size (); st++)
				{
					if (WM_->_work_block[st]._button.pressed ())
					{
						GS = GameStatus::learn;
						LearnMenu::setWork (language->work[st]);
						WM_->_T_up_panel_left.setString ("Integrated/" + language->s_name + "/" + language->work[st].w_name);
						break;
					}
				}
			}

			if (WM_->_B_up_panel.pressed ())
			{
				GS = GameStatus::works_menu_to_main_menu;
			}
		}
		for (size_t st (0); st < language->work.size (); st++)
		{
			WM_->_work_block[st].transition (language->work[st]);
		}

		WM_->_T_up_panel_middle.setCharacterSize (WM_->_f_BIG_FONT_SCALE * f_factor_y);
		names::SetXCenterPosition (WM_->_T_up_panel_middle, WM_->_B_up_panel.getGlobalBounds ().top + 1.0 * f_factor_y);

		for (size_t st (0); st < language->work.size (); st++)
		{
			WM_->_work_block[st]._button.setScale (f_factor_y);
			if (st == 0)
			{
				WM_->_work_block[st]._button.setPosition (
				    (WM_->_i_OUT_LEFT + 1.0 + WM_->_i_IN_LEFT + 1.0) * f_factor_y,
				    (WM_->_i_OUT_UP + 1.0 + WM_->_V2f_size_up_panel.y + 1.0 + WM_->_i_OUT_BETWEEN + 1.0 + WM_->_i_IN_UP + 1.0 + WM_->_f_move_blocks) * f_factor_y);
			}
			else
			{
				WM_->_work_block[st]._button.setPosition (
				    WM_->_work_block[st - 1]._button.getGlobalBounds ().left + 1.0 * f_factor_y,
				    WM_->_work_block[st - 1]._button.getGlobalBounds ().top + WM_->_work_block[st - 1]._button.getGlobalBounds ().height + (WM_->_i_IN_BETWEEN + 1.0) * f_factor_y);
			}
			WM_->_work_block[st]._RS_icon.setScale (f_factor_y, f_factor_y);
			WM_->_work_block[st]._RS_icon.setPosition (
			    WM_->_work_block[st]._button.getGlobalBounds ().left + (1.0 + WM_->_i_BLOCK_LEFT + 1.0) * f_factor_y,
			    WM_->_work_block[st]._button.getGlobalBounds ().top + (1.0 + WM_->_i_BLOCK_UP + 1.0) * f_factor_y);
			WM_->_work_block[st]._T_name.setCharacterSize (WM_->_f_BIG_FONT_SCALE * f_factor_y);
			WM_->_work_block[st]._T_name.setPosition (
			    WM_->_work_block[st]._RS_icon.getGlobalBounds ().left + (WM_->_work_block[st]._RS_icon.getGlobalBounds ().width - 4.0 * f_factor_y) * 0.5 - WM_->_work_block[st]._T_name.getGlobalBounds ().width * 0.5,
			    WM_->_work_block[st]._RS_icon.getGlobalBounds ().top + (WM_->_work_block[st]._RS_icon.getGlobalBounds ().height - 8.0 * f_factor_y) * 0.5 - WM_->_work_block[st]._T_name.getGlobalBounds ().height * 0.5);
			WM_->_work_block[st]._T_type.setCharacterSize (WM_->_f_MIDDLE_BIG_FONT_SCALE * f_factor_y);
			WM_->_work_block[st]._T_type.setPosition (
			    WM_->_work_block[st]._RS_icon.getGlobalBounds ().left + (WM_->_work_block[st]._RS_icon.getGlobalBounds ().width - 4.0 * f_factor_y) * 0.5 - WM_->_work_block[st]._T_type.getGlobalBounds ().width * 0.5,
			    WM_->_work_block[st]._RS_icon.getPosition ().y + WM_->_work_block[st]._RS_icon.getGlobalBounds ().height - 3.5 * f_factor_y - WM_->_work_block[st]._T_type.getGlobalBounds ().height);
			WM_->_work_block[st]._RS_content.setScale (f_factor_y, f_factor_y);
			WM_->_work_block[st]._RS_content.setPosition (
			    WM_->_work_block[st]._RS_icon.getGlobalBounds ().left + WM_->_work_block[st]._RS_icon.getGlobalBounds ().width + (WM_->_i_BLOCK_BETWEEN + 1.0) * f_factor_y,
			    WM_->_work_block[st]._RS_icon.getPosition ().y + 1.0 * f_factor_y);
			WM_->_work_block[st]._T_content.setCharacterSize (WM_->_f_MIDDLE_SMALL_FONT_SCALE * f_factor_y);
			WM_->_work_block[st]._T_content.setPosition (
			    WM_->_work_block[st]._RS_content.getPosition ().x + 1.0 * f_factor_y,
			    WM_->_work_block[st]._RS_content.getPosition ().y + 1.0 * f_factor_y);
			WM_->_work_block[st]._T_score.setCharacterSize (WM_->_f_SMALL_FONT_SCALE * f_factor_y);
			WM_->_work_block[st]._T_score.setPosition (
			    WM_->_work_block[st]._button.getGlobalBounds ().left + (1.0 + WM_->_i_BLOCK_LEFT) * f_factor_y,
			    WM_->_work_block[st]._button.getGlobalBounds ().top + WM_->_work_block[st]._button.getGlobalBounds ().height - (1.0 + WM_->_i_BLOCK_UP) * f_factor_y - WM_->_work_block[st]._T_score.getGlobalBounds ().height);
		}

		if (GS == GameStatus::learn)
		{
			WM_->_f_move_blocks = 0.0;
		}
	}
}
void WorksMenu::main_transitionOf ()
{
	WorksMenu* WM_ = getClass ();

	if (names::game_status == GameStatus::works_menu_to_main_menu)
	{
		if (PersonMenu::getFrameTransition () > 0.0)
		{
			PersonMenu::getFrameTransition () -= PersonMenu::getSpeedTransition () * names::microsec * names::f_time;
			WM_->_B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, PersonMenu::getFrameTransition () / 255.0 * ColorTable::c25a75.a));
			WM_->_B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, PersonMenu::getFrameTransition ()));
			WM_->_T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, PersonMenu::getFrameTransition ()));
			WM_->_T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, PersonMenu::getFrameTransition ()));
			WM_->_T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, PersonMenu::getFrameTransition ()));
			WM_->_RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, PersonMenu::getFrameTransition () / 255.0 * ColorTable::c25a75.a));
			WM_->_RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, PersonMenu::getFrameTransition ()));
		}
		else
		{
			PersonMenu::getFrameTransition () = 0.0;
			WM_->_B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 0.0));
			WM_->_B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 0.0));
			WM_->_T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 0.0));
			WM_->_T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, 0.0));
			WM_->_T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 0.0));
			WM_->_RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 0.0));
			WM_->_RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 0.0));
		}
	}
}

Vector2f WorksMenu::getSizeDownPanel ()
{
	return getClass ()->_V2f_size_down_panel;
}

float& WorksMenu::getMoveBlocks ()
{
	return getClass ()->_f_move_blocks;
}

void WorksMenu::stringUpdate ()
{
	WorksMenu* WM_ = getClass ();

	WM_->_T_up_panel_left.setString ("Integrated/" + language->s_name);

	unsigned u (0);
	for (size_t st (0); st < language->work.size (); st++)
	{
		if (language->work[st].u_try)
		{
			u++;
		}
	}
	WM_->_T_up_panel_right.setString (to_wstring (unsigned (float (u) / float (language->work.size ()) * 100)) + L"%");

	for (size_t st (0); st < WM_->_work_block.size (); st++)
	{
		WM_->_work_block[st].build (st, language->work[st]);
	}
}
