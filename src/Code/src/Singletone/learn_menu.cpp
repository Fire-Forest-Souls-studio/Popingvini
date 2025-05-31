#include "../../includes/Singletone/learn_menu.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/color_table.h"
#include "../../includes/Singletone/test_menu.h"

LearnMenu* LearnMenu::m_class_obj = NULL;

Work* LearnMenu::work = NULL;

LearnMenu::LearnMenu ()
    : m_button ("LM/button/next"),

      m_f_text_size (4.875),
      m_f_left0 (13.0),
      m_f_left1 (10.0),
      m_f_left2 (8.0)
{
	m_rectangle_shape.setFillColor (ColorTable::c25);
	m_rectangle_shape.setOutlineColor (ColorTable::c25a175);
	m_rectangle_shape.setOutlineThickness (m_f_left1);
	m_rectangle_shape.setSize (Vector2f (
	    WorksMenu::getDownPanel ().getGlobalBounds ().width / WindowAndStyles::getFactorY () - 2 - m_f_left0 * 2,
	    WorksMenu::getDownPanel ().getGlobalBounds ().height / WindowAndStyles::getFactorY () - 2));
	m_text.setFont (names::F_pixel);
	m_text.setFillColor (ColorTable::c100);
	m_text.setCharacterSize (m_f_text_size);
}

LearnMenu* LearnMenu::getClass ()
{
	if (m_class_obj)
		return m_class_obj;

	m_class_obj = new LearnMenu;
	return m_class_obj;
}

void LearnMenu::destroy ()
{
	LearnMenu* LM_ = getClass ();

	LM_->m_rectangle_shape.setSize (Vector2f (
	    WorksMenu::getSizeDownPanel ().x - (LM_->m_f_left0 + LM_->m_f_left1) * 2,
	    WorksMenu::getSizeDownPanel ().y));
	if (work)
	{
		LM_->m_text.setString (names::GetStringOfHyphenation (
		    work->learn.w_text,
		    (WorksMenu::getSizeDownPanel ().x - (LM_->m_f_left0 + LM_->m_f_left1 + LM_->m_f_left2) * 2) / (WorksMenu::getWidthSimvolBigFont () / WorksMenu::getBigFontScale () * LM_->m_f_text_size)));
	}
}

void LearnMenu::main ()
{
	LearnMenu* LM_ = getClass ();

	if (Loading::getLoad ())
	{
		LM_->m_button.setTexture ();
		LM_->m_button.setSize (Vector2f (LM_->m_button.getTexture ().getSize ()));
		destroy ();
	}
	else if (names::game_status == GameStatus::learn)
	{
		LM_->m_rectangle_shape.setScale (WindowAndStyles::getFactorY (), WindowAndStyles::getFactorY ());
		LM_->m_rectangle_shape.setPosition (
		    WorksMenu::getDownPanel ().getPosition ().x + (LM_->m_f_left0 + LM_->m_f_left1) * WindowAndStyles::getFactorY (),
		    WorksMenu::getDownPanel ().getPosition ().y);
		LM_->m_button.setScale (WindowAndStyles::getFactorY ());
		LM_->m_button.setPosition (
		    WindowAndStyles::getGlobalBounds ().width * 0.5 - LM_->m_button.getGlobalBounds ().width * 0.5,
		    WindowAndStyles::getGlobalBounds ().height - LM_->m_button.getGlobalBounds ().height);
		LM_->m_text.setCharacterSize (WindowAndStyles::getFactorY () * LM_->m_f_text_size);
		LM_->m_text.setPosition (
		    WorksMenu::getDownPanel ().getPosition ().x + (LM_->m_f_left0 + LM_->m_f_left1 + LM_->m_f_left2) * WindowAndStyles::getFactorY (),
		    WorksMenu::getDownPanel ().getPosition ().y + (LM_->m_f_left2 + WorksMenu::getMoveBlocks ()) * WindowAndStyles::getFactorY ());

		if (LM_->m_button.pressed ())
		{
			names::game_status = GameStatus::test;
			WorksMenu::getMoveBlocks () = 0.0;
			TestMenu::setZeroQuestion ();
		}
	}
}

ImageButton& LearnMenu::getButton ()
{
	return getClass ()->m_button;
}

RectangleShape LearnMenu::getRectangleShape ()
{
	return getClass ()->m_rectangle_shape;
}

void LearnMenu::setWork (Work& W)
{
	LearnMenu* LM_ = getClass ();

	work = &W;

	LM_->m_text.setString (names::GetStringOfHyphenation (
	    work->learn.w_text,
	    (WorksMenu::getSizeDownPanel ().x - (LM_->m_f_left0 + LM_->m_f_left1 + LM_->m_f_left2) * 2) / (WorksMenu::getWidthSimvolBigFont () / WorksMenu::getBigFontScale () * LM_->m_f_text_size)));
}

Text LearnMenu::getText ()
{
	return getClass ()->m_text;
}
