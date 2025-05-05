#include "../../includes/Singletone/learn_menu.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/color_table.h"
#include "../../includes/Singletone/test_menu.h"

LearnMenu* LearnMenu::class_obj = NULL;

Work* LearnMenu::work = NULL;

LearnMenu::LearnMenu ()
    : button_obj ("LM/button/next"),

      f_text_size (4.875),
      f_left0 (13.0),
      f_left1 (10.0),
      f_left2 (8.0)
{
	rectangle_shape_obj.setFillColor (ColorTable::c25);
	rectangle_shape_obj.setOutlineColor (ColorTable::c25a175);
	rectangle_shape_obj.setOutlineThickness (f_left1);
	rectangle_shape_obj.setSize (Vector2f (
	    WorksMenu::getDownPanel ().getGlobalBounds ().width / WindowAndStyles::getFactorY () - 2 - f_left0 * 2,
	    WorksMenu::getDownPanel ().getGlobalBounds ().height / WindowAndStyles::getFactorY () - 2));
	text_obj.setFont (names::F_pixel);
	text_obj.setFillColor (ColorTable::c100);
	text_obj.setCharacterSize (f_text_size);
}

LearnMenu* LearnMenu::getClass ()
{
	if (class_obj)
		return class_obj;

	class_obj = new LearnMenu;
	return class_obj;
}

void LearnMenu::destroy ()
{
	LearnMenu* LM_ = getClass ();

	LM_->rectangle_shape_obj.setSize (Vector2f (
	    WorksMenu::getSizeDownPanel ().x - (LM_->f_left0 + LM_->f_left1) * 2,
	    WorksMenu::getSizeDownPanel ().y));
	if (work)
	{
		LM_->text_obj.setString (names::GetStringOfHyphenation (
		    work->learn.w_text,
		    (WorksMenu::getSizeDownPanel ().x - (LM_->f_left0 + LM_->f_left1 + LM_->f_left2) * 2) / (WorksMenu::getWidthSimvolBigFont () / WorksMenu::getBigFontScale () * LM_->f_text_size)));
	}
}

void LearnMenu::main ()
{
	LearnMenu* LM_ = getClass ();

	if (Loading::getLoad ())
	{
		LM_->button_obj.setTexture ();
		LM_->button_obj.setSize (Vector2f (LM_->button_obj.getTexture ().getSize ()));
		destroy ();
	}
	else if (names::game_status == GameStatus::learn)
	{
		LM_->rectangle_shape_obj.setScale (WindowAndStyles::getFactorY (), WindowAndStyles::getFactorY ());
		LM_->rectangle_shape_obj.setPosition (
		    WorksMenu::getDownPanel ().getPosition ().x + (LM_->f_left0 + LM_->f_left1) * WindowAndStyles::getFactorY (),
		    WorksMenu::getDownPanel ().getPosition ().y);
		LM_->button_obj.setScale (WindowAndStyles::getFactorY ());
		LM_->button_obj.setPosition (
		    WindowAndStyles::getGlobalBounds ().width * 0.5 - LM_->button_obj.getGlobalBounds ().width * 0.5,
		    WindowAndStyles::getGlobalBounds ().height - LM_->button_obj.getGlobalBounds ().height);
		LM_->text_obj.setCharacterSize (WindowAndStyles::getFactorY () * LM_->f_text_size);
		LM_->text_obj.setPosition (
		    WorksMenu::getDownPanel ().getPosition ().x + (LM_->f_left0 + LM_->f_left1 + LM_->f_left2) * WindowAndStyles::getFactorY (),
		    WorksMenu::getDownPanel ().getPosition ().y + (LM_->f_left2 + WorksMenu::getMoveBlocks ()) * WindowAndStyles::getFactorY ());

		if (LM_->button_obj.pressed ())
		{
			names::game_status = GameStatus::test;
			WorksMenu::getMoveBlocks () = 0.0;
			TestMenu::setZeroQuestion ();
		}
	}
}

ImageButton& LearnMenu::getButton ()
{
	return getClass ()->button_obj;
}

RectangleShape LearnMenu::getRectangleShape ()
{
	return getClass ()->rectangle_shape_obj;
}

void LearnMenu::setWork (Work& W)
{
	LearnMenu* LM_ = getClass ();

	work = &W;

	LM_->text_obj.setString (names::GetStringOfHyphenation (
	    work->learn.w_text,
	    (WorksMenu::getSizeDownPanel ().x - (LM_->f_left0 + LM_->f_left1 + LM_->f_left2) * 2) / (WorksMenu::getWidthSimvolBigFont () / WorksMenu::getBigFontScale () * LM_->f_text_size)));
}

Text LearnMenu::getText ()
{
	return getClass ()->text_obj;
}
