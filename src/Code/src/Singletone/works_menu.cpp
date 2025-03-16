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

WorksMenu::WorksMenu () :
		B_up_panel ("WM/button/up_panel"),

		f_big_font_scale (6.0),
				f_middle_big_font_scale (8.0),
				f_middle_small_font_scale (3.75),
				f_small_font_scale (3.0),
				f_move_blocks (0.0),
				f_speed_move_blocks (5.0),
				f_width_simvol_big_font (3.264367816),
				f_width_simvol_middle_big_font (f_width_simvol_big_font / f_big_font_scale * f_middle_big_font_scale),
				f_width_simvol_middle_small_font (f_width_simvol_big_font / f_big_font_scale * f_middle_small_font_scale),
				f_width_simvol_small_font (f_width_simvol_big_font / f_big_font_scale * f_move_blocks),

				i_out_up (5),
				i_out_left (15),
				i_out_between (3),
				i_in_up (1),
				i_in_left (1),
				i_in_between (3),
				i_block_up (3),
				i_block_left (3),
				i_block_between (2),

				V2f_size_up_panel (0, 8),
				V2f_size_down_panel (0, 0),
				V2f_size_block_icon (43, 38),

				work_block (0)
{
	B_up_panel.setSize (V2f_size_up_panel);
	B_up_panel.setFillColor (Color::Transparent);
	B_up_panel.setOutline (Color::Transparent);
	T_up_panel_left.setFillColor (Color::Transparent);
	T_up_panel_left.setFont (names::F_pixel);
	T_up_panel_middle.setFillColor (Color::Transparent);
	T_up_panel_middle.setFont (names::F_pixel);
	T_up_panel_middle.setString (L"<-");
	T_up_panel_right.setFillColor (Color::Transparent);
	T_up_panel_right.setFont (names::F_pixel);
	RS_down_panel.setFillColor (Color::Transparent);
	RS_down_panel.setOutlineColor (Color::Transparent);
	RS_down_panel.setOutlineThickness (1);
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

	WM_->V2f_size_up_panel = Vector2f (
			WindowAndStyles::getGlobalBounds ().width / f - WM_->i_out_left * 2 - 2,
			WM_->V2f_size_up_panel.y
			);
	WM_->B_up_panel.setSize (WM_->V2f_size_up_panel);

	resizeWindow ();

	if (language)
	{
		for (size_t st (0); st < language->work.size (); st++)
		{
			WM_->work_block[st].resize (language->work[st]);
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
	WM_->work_block.resize (language->work.size ());
	for (size_t st (0); st < language->work.size (); st++)
	{
		WM_->work_block[st].build (st, language->work[st]);
		WM_->work_block[st].RS_icon.setTexture (&WM_->texture);
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

	WM_->render_texture.clear (Color::Transparent);

	if (language)
	{
		if (GS == GameStatus::works_menu
				or GS == GameStatus::works_menu_to_main_menu)
		{
			for (size_t st (0); st < language->work.size (); st++)
			{
				if (WM_->work_block[st].button.getRectangleShape ().getGlobalBounds ().intersects (WindowAndStyles::getGlobalBounds ()))
				{
					WM_->render_texture.draw (WM_->work_block[st].button.getRectangleShape ());
					if (b)
					{
						WM_->render_texture.draw (WM_->work_block[st].button.getText ());
					}
					WM_->render_texture.draw (WM_->work_block[st].RS_icon);
					WM_->render_texture.draw (WM_->work_block[st].T_name);
					WM_->render_texture.draw (WM_->work_block[st].T_type);
					WM_->render_texture.draw (WM_->work_block[st].RS_content);
					WM_->render_texture.draw (WM_->work_block[st].T_content);
					WM_->render_texture.draw (WM_->work_block[st].T_score);
				}
			}
		}
		else if (GS == GameStatus::learn)
		{
			WM_->render_texture.draw (LearnMenu::getRectangleShape ());
			WM_->render_texture.draw (LearnMenu::getText ());
			WM_->render_texture.draw (LearnMenu::getButton ().getRectangleShape ());
			WM_->render_texture.draw (LearnMenu::getButton ().getText ());
		}
		else if (GS == GameStatus::test)
		{
			WM_->render_texture.draw (TestMenu::getRectangleShape ());
			WM_->render_texture.draw (TestMenu::getRectangleShapeImage ());
			WM_->render_texture.draw (TestMenu::getTextQuestion ());
			for (size_t st (0); st < TestMenu::getButtons ().size (); st++)
			{
				WM_->render_texture.draw (TestMenu::getButtons ()[st]._text);
				if (names::b_hitboxes_is_drawn)
				{
					WM_->render_texture.draw (TestMenu::getButtons ()[st].getRectangleShape ());
					WM_->render_texture.draw (TestMenu::getButtons ()[st].getText ());
				}
			}
		}
	}

	WM_->render_texture.display ();
}

Button& WorksMenu::getUpPanel ()
{
	return getClass ()->B_up_panel;
}

Text& WorksMenu::getLeftTextUpPanel ()
{
	return getClass ()->T_up_panel_left;
}
Text& WorksMenu::getMiddleTextUpPanel ()
{
	return getClass ()->T_up_panel_middle;
}
Text& WorksMenu::getRightTextUpPanel ()
{
	return getClass ()->T_up_panel_right;
}

RenderTexture& WorksMenu::getRender ()
{
	return getClass ()->render_texture;
}

RectangleShape& WorksMenu::getDownPanel ()
{
	return getClass ()->RS_down_panel;
}

void WorksMenu::resizeWindow ()
{
	float f = WindowAndStyles::getFactorY ();

	WorksMenu* WM_ = getClass ();

	WM_->V2f_size_down_panel = Vector2f (
			WindowAndStyles::getGlobalBounds ().width / f - WM_->i_out_left * 2 - 2,
			WindowAndStyles::getPixelsSizeY () - WM_->i_out_up - 2 - WM_->V2f_size_up_panel.y - WM_->i_out_between * 2 - 2
					);
	WM_->RS_down_panel.setSize (WM_->V2f_size_down_panel);
	WM_->render_texture.create (
			WM_->V2f_size_down_panel.x * f,
			WM_->V2f_size_down_panel.y * f
					);

	WM_->view.setCenter (Vector2f (
			(WM_->V2f_size_down_panel.x * 0.5 +
					WM_->i_out_left + 1)
					* f,
			(WM_->V2f_size_down_panel.y * 0.5 +
					WM_->i_out_up + 2 + WM_->i_out_between + 1 + WM_->V2f_size_up_panel.y)
					* f
					));

	WM_->view.setSize (
			(WM_->V2f_size_down_panel.x + 2) * f,
			(WM_->V2f_size_down_panel.y + 2) * f
					);
	WM_->render_texture.setView (WM_->view);
}

int WorksMenu::getIOutUp ()
{
	return getClass ()->i_out_up;
}
int WorksMenu::getIOutLeft ()
{
	return getClass ()->i_out_left;
}
int WorksMenu::getIOutBetween ()
{
	return getClass ()->i_out_between;
}
int WorksMenu::getIInUp ()
{
	return getClass ()->i_in_up;
}
int WorksMenu::getIInLeft ()
{
	return getClass ()->i_in_left;
}
int WorksMenu::getIInBetween ()
{
	return getClass ()->i_in_between;
}

void WorksMenu::setMoveBlocks (float f)
{
	WorksMenu* WM_ = getClass ();

	if (names::game_status == GameStatus::works_menu
			or names::game_status == GameStatus::works_menu_to_main_menu)
	{
		if ( (f > 0
				and WM_->work_block[0].button.getGlobalBounds ().top
						< WM_->RS_down_panel.getPosition ().y)
				or (f < 0
						and WM_->work_block[WM_->work_block.size () - 1].button.getGlobalBounds ().top
								+ WM_->work_block[WM_->work_block.size () - 1].button.getGlobalBounds ().height
								> WM_->RS_down_panel.getPosition ().y
										+ WM_->RS_down_panel.getGlobalBounds ().height))
		{
			WM_->f_move_blocks += f * WM_->f_speed_move_blocks;
		}
	}
	else if (names::game_status == GameStatus::learn)
	{
		if ( (f > 0
				and LearnMenu::getText ().getGlobalBounds ().top - WM_->RS_down_panel.getGlobalBounds ().height * 0.5
						< WM_->RS_down_panel.getPosition ().y)
				or (f < 0
						and LearnMenu::getText ().getGlobalBounds ().top + LearnMenu::getText ().getGlobalBounds ().height
								+ WM_->RS_down_panel.getGlobalBounds ().height * 0.5
								> WM_->RS_down_panel.getPosition ().y
										+ WM_->RS_down_panel.getGlobalBounds ().height))
		{
			WM_->f_move_blocks += f * WM_->f_speed_move_blocks;
		}
	}
	else if (names::game_status == GameStatus::test)
	{
		if ( (f > 0
				and TestMenu::getTextQuestion ().getGlobalBounds ().top - WM_->RS_down_panel.getGlobalBounds ().height * 0.5
						< WM_->RS_down_panel.getPosition ().y)
				or (f < 0
						and TestMenu::getButtons ()[TestMenu::getButtons ().size () - 1].getGlobalBounds ().top
								+ TestMenu::getButtons ()[TestMenu::getButtons ().size () - 1].getGlobalBounds ().height
								+ WM_->RS_down_panel.getGlobalBounds ().height * 0.5
								> WM_->RS_down_panel.getPosition ().y
										+ WM_->RS_down_panel.getGlobalBounds ().height))
		{
			WM_->f_move_blocks += f * WM_->f_speed_move_blocks;
		}
	}
}

Vector2f WorksMenu::getSizeBlockIcon ()
{
	return getClass ()->V2f_size_block_icon;
}

Texture& WorksMenu::getTexture ()
{
	return getClass ()->texture;
}

int WorksMenu::getBlockUp ()
{
	return getClass ()->i_block_up;
}
int WorksMenu::getBlockLeft ()
{
	return getClass ()->i_block_left;
}
int WorksMenu::getBlockBetween ()
{
	return getClass ()->i_block_between;
}

float WorksMenu::getBigFontScale ()
{
	return getClass ()->f_big_font_scale;
}
float WorksMenu::getMiddleBigFontScale ()
{
	return getClass ()->f_middle_big_font_scale;
}
float WorksMenu::getMiddleSmallFontScale ()
{
	return getClass ()->f_middle_small_font_scale;
}
float WorksMenu::getSmallFontScale ()
{
	return getClass ()->f_small_font_scale;
}
float WorksMenu::getWidthSimvolBigFont ()
{
	return getClass ()->f_width_simvol_big_font;
}
float WorksMenu::getWidthSimvolMiddleBigFont ()
{
	return getClass ()->f_width_simvol_middle_big_font;
}
float WorksMenu::getWidthSimvolMiddleSmallFont ()
{
	return getClass ()->f_width_simvol_middle_small_font;
}
float WorksMenu::getWidthSimvolSmallFont ()
{
	return getClass ()->f_width_simvol_small_font;
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

	if (names::game_status == GameStatus::works_menu
			or names::game_status == GameStatus::test
			or names::game_status == GameStatus::learn
			or names::game_status == GameStatus::works_menu_to_main_menu)
	{

		WM_->B_up_panel.setScale (f);
		WM_->B_up_panel.setPosition (
				(WM_->i_out_left + 1) * f,
				(WM_->i_out_up + 1) * f
						);

		WM_->T_up_panel_left.setCharacterSize (WM_->f_big_font_scale * f);
		WM_->T_up_panel_left.setPosition (
				WM_->B_up_panel.getGlobalBounds ().left + 2 * f,
				WM_->B_up_panel.getGlobalBounds ().top + 1 * f
						);

		WM_->T_up_panel_right.setCharacterSize (WM_->f_big_font_scale * f);
		WM_->T_up_panel_right.setPosition (
				WM_->B_up_panel.getGlobalBounds ().left + WM_->B_up_panel.getGlobalBounds ().width
						- 2 * f - WM_->T_up_panel_right.getGlobalBounds ().width,
				WM_->B_up_panel.getGlobalBounds ().top + 1 * f
						);

		if (Keyboard::isKeyPressed (Keyboard::F11))
		{
			resizeWindow ();
		}

		WM_->RS_down_panel.setScale (f, f);
		WM_->RS_down_panel.setPosition (
				(WM_->i_out_left + 1) * f,
				(WM_->i_out_up + 1 + WM_->V2f_size_up_panel.y + 1 + WM_->i_out_between + 1) * f
						);
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
				WM_->B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, f_frame_transition / 255.0 * ColorTable::c25a75.a));
				WM_->B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, f_frame_transition));
				WM_->T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, f_frame_transition));
				WM_->T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, f_frame_transition));
				WM_->T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, f_frame_transition));
				WM_->RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, f_frame_transition / 255.0 * ColorTable::c25a75.a));
				WM_->RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, f_frame_transition));
			}
			else if (f_frame_transition != 255.0)
			{
				f_frame_transition = 255.0;
				WM_->B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 75.0));
				WM_->B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 255.0));
				WM_->T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 255.0));
				WM_->T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, 255.0));
				WM_->T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 255.0));
				WM_->RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 75.0));
				WM_->RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 255.0));
			}
			else
			{
				for (size_t st (0); st < WM_->work_block.size (); st++)
				{
					if (WM_->work_block[st].button.pressed ())
					{
						GS = GameStatus::learn;
						LearnMenu::setWork (language->work[st]);
						WM_->T_up_panel_left.setString ("Integrated/" + language->s_name + "/" + language->work[st].w_name);
						break;
					}
				}
			}

			if (WM_->B_up_panel.pressed ())
			{
				GS = GameStatus::works_menu_to_main_menu;
			}
		}
		for (size_t st (0); st < language->work.size (); st++)
		{
			WM_->work_block[st].transition (language->work[st]);
		}

		WM_->T_up_panel_middle.setCharacterSize (WM_->f_big_font_scale * f_factor_y);
		names::SetXCenterPosition (WM_->T_up_panel_middle, WM_->B_up_panel.getGlobalBounds ().top + 1.0 * f_factor_y);

		for (size_t st (0); st < language->work.size (); st++)
		{
			WM_->work_block[st].button.setScale (f_factor_y);
			if (st == 0)
			{
				WM_->work_block[st].button.setPosition (
						(WM_->i_out_left + 1.0 + WM_->i_in_left + 1.0) * f_factor_y,
						(WM_->i_out_up + 1.0 + WM_->V2f_size_up_panel.y + 1.0 + WM_->i_out_between + 1.0 + WM_->i_in_up + 1.0 + WM_->f_move_blocks)
								* f_factor_y
								);
			}
			else
			{
				WM_->work_block[st].button.setPosition (
						WM_->work_block[st - 1].button.getGlobalBounds ().left + 1.0 * f_factor_y,
						WM_->work_block[st - 1].button.getGlobalBounds ().top + WM_->work_block[st - 1].button.getGlobalBounds ().height
								+ (WM_->i_in_between + 1.0) * f_factor_y
										);
			}
			WM_->work_block[st].RS_icon.setScale (f_factor_y, f_factor_y);
			WM_->work_block[st].RS_icon.setPosition (
					WM_->work_block[st].button.getGlobalBounds ().left + (1.0 + WM_->i_block_left + 1.0) * f_factor_y,
					WM_->work_block[st].button.getGlobalBounds ().top + (1.0 + WM_->i_block_up + 1.0) * f_factor_y
							);
			WM_->work_block[st].T_name.setCharacterSize (WM_->f_big_font_scale * f_factor_y);
			WM_->work_block[st].T_name.setPosition (
					WM_->work_block[st].RS_icon.getGlobalBounds ().left
							+ (WM_->work_block[st].RS_icon.getGlobalBounds ().width - 4.0 * f_factor_y) * 0.5
							- WM_->work_block[st].T_name.getGlobalBounds ().width * 0.5,
					WM_->work_block[st].RS_icon.getGlobalBounds ().top
							+ (WM_->work_block[st].RS_icon.getGlobalBounds ().height - 8.0 * f_factor_y) * 0.5
							- WM_->work_block[st].T_name.getGlobalBounds ().height * 0.5
									);
			WM_->work_block[st].T_type.setCharacterSize (WM_->f_middle_big_font_scale * f_factor_y);
			WM_->work_block[st].T_type.setPosition (
					WM_->work_block[st].RS_icon.getGlobalBounds ().left
							+ (WM_->work_block[st].RS_icon.getGlobalBounds ().width - 4.0 * f_factor_y) * 0.5
							- WM_->work_block[st].T_type.getGlobalBounds ().width * 0.5,
					WM_->work_block[st].RS_icon.getPosition ().y
							+ WM_->work_block[st].RS_icon.getGlobalBounds ().height - 3.5 * f_factor_y
							- WM_->work_block[st].T_type.getGlobalBounds ().height
							);
			WM_->work_block[st].RS_content.setScale (f_factor_y, f_factor_y);
			WM_->work_block[st].RS_content.setPosition (
					WM_->work_block[st].RS_icon.getGlobalBounds ().left
							+ WM_->work_block[st].RS_icon.getGlobalBounds ().width
							+ (WM_->i_block_between + 1.0) * f_factor_y,
					WM_->work_block[st].RS_icon.getPosition ().y
							+ 1.0 * f_factor_y
									);
			WM_->work_block[st].T_content.setCharacterSize (WM_->f_middle_small_font_scale * f_factor_y);
			WM_->work_block[st].T_content.setPosition (
					WM_->work_block[st].RS_content.getPosition ().x + 1.0 * f_factor_y,
					WM_->work_block[st].RS_content.getPosition ().y + 1.0 * f_factor_y
							);
			WM_->work_block[st].T_score.setCharacterSize (WM_->f_small_font_scale * f_factor_y);
			WM_->work_block[st].T_score.setPosition (
					WM_->work_block[st].button.getGlobalBounds ().left + (1.0 + WM_->i_block_left) * f_factor_y,
					WM_->work_block[st].button.getGlobalBounds ().top + WM_->work_block[st].button.getGlobalBounds ().height
							- (1.0 + WM_->i_block_up) * f_factor_y - WM_->work_block[st].T_score.getGlobalBounds ().height
							);
		}

		if (GS == GameStatus::learn)
		{
			WM_->f_move_blocks = 0.0;
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
			WM_->B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, PersonMenu::getFrameTransition () / 255.0 * ColorTable::c25a75.a));
			WM_->B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, PersonMenu::getFrameTransition ()));
			WM_->T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, PersonMenu::getFrameTransition ()));
			WM_->T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, PersonMenu::getFrameTransition ()));
			WM_->T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, PersonMenu::getFrameTransition ()));
			WM_->RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, PersonMenu::getFrameTransition () / 255.0 * ColorTable::c25a75.a));
			WM_->RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, PersonMenu::getFrameTransition ()));
		}
		else
		{
			PersonMenu::getFrameTransition () = 0.0;
			WM_->B_up_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 0.0));
			WM_->B_up_panel.setOutline (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 0.0));
			WM_->T_up_panel_left.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 0.0));
			WM_->T_up_panel_middle.setFillColor (Color (ColorTable::g137b204.r, ColorTable::g137b204.g, ColorTable::g137b204.b, 0.0));
			WM_->T_up_panel_right.setFillColor (Color (ColorTable::c100.r, ColorTable::c100.g, ColorTable::c100.b, 0.0));
			WM_->RS_down_panel.setFillColor (Color (ColorTable::c25a75.r, ColorTable::c25a75.g, ColorTable::c25a75.b, 0.0));
			WM_->RS_down_panel.setOutlineColor (Color (ColorTable::c75.r, ColorTable::c75.g, ColorTable::c75.b, 0.0));
		}
	}
}

Vector2f WorksMenu::getSizeDownPanel ()
{
	return getClass ()->V2f_size_down_panel;
}

float& WorksMenu::getMoveBlocks ()
{
	return getClass ()->f_move_blocks;
}

void WorksMenu::stringUpdate ()
{
	WorksMenu* WM_ = getClass ();

	WM_->T_up_panel_left.setString ("Integrated/" + language->s_name);

	unsigned u (0);
	for (size_t st (0); st < language->work.size (); st++)
	{
		if (language->work[st].u_try)
		{
			u++;
		}
	}
	WM_->T_up_panel_right.setString (to_wstring (unsigned (float (u) / float (language->work.size ()) * 100)) + L"%");

	for (size_t st (0); st < WM_->work_block.size (); st++)
	{
		WM_->work_block[st].build (st, language->work[st]);
	}
}
