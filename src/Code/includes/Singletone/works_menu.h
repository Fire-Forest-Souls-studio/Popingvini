#ifndef CODE_WORKS_MENU_H_
#define CODE_WORKS_MENU_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "../Classes/button.h"
#include "../Classes/language.h"
#include "../Classes/work_block.h"

class WorksMenu
{
	private:

		static WorksMenu* class_obj;

		Text T_up_panel_left;
		Text T_up_panel_middle;
		Text T_up_panel_right;

		Button B_up_panel;

		RectangleShape RS_down_panel;

		float f_big_font_scale;
		float f_middle_big_font_scale;
		float f_middle_small_font_scale;
		float f_small_font_scale;
		float f_move_blocks;
		float f_speed_move_blocks;
		float f_width_simvol_big_font;
		float f_width_simvol_middle_big_font;
		float f_width_simvol_middle_small_font;
		float f_width_simvol_small_font;

		int i_out_up;
		int i_out_left;
		int i_out_between;
		int i_in_up;
		int i_in_left;
		int i_in_between;
		int i_block_up;
		int i_block_left;
		int i_block_between;

		Texture texture;

		RenderTexture render_texture;

		View view;

		Vector2f V2f_size_up_panel;
		Vector2f V2f_size_down_panel;
		Vector2f V2f_size_block_icon;

		vector <WorkBlock> work_block;

		WorksMenu ();

		static void resizeWindow ();
		static void main_load ();
		static void main_all ();
		static void main_works_menu ();
		static void main_transitionOf ();

	protected:

		static WorksMenu* getClass ();

	public:

		static Language* language;

		static void destroy ();
		static void setLanguage (Language*);
		static void main ();
		static void start ();
		static void clear ();
		static void setMoveBlocks (float);
		static void stringUpdate ();

		static Button& getUpPanel ();

		static Text& getLeftTextUpPanel ();
		static Text& getMiddleTextUpPanel ();
		static Text& getRightTextUpPanel ();

		static RenderTexture& getRender ();

		static RectangleShape& getDownPanel ();

		static int getIOutUp ();
		static int getIOutLeft ();
		static int getIOutBetween ();
		static int getIInUp ();
		static int getIInLeft ();
		static int getIInBetween ();
		static int getBlockUp ();
		static int getBlockLeft ();
		static int getBlockBetween ();

		static Vector2f getSizeBlockIcon ();
		static Vector2f getSizeDownPanel ();

		static Texture& getTexture ();

		static float getBigFontScale ();
		static float getMiddleBigFontScale ();
		static float getMiddleSmallFontScale ();
		static float getSmallFontScale ();
		static float getWidthSimvolBigFont ();
		static float getWidthSimvolMiddleBigFont ();
		static float getWidthSimvolMiddleSmallFont ();
		static float getWidthSimvolSmallFont ();
		static float& getMoveBlocks ();
};

#endif
