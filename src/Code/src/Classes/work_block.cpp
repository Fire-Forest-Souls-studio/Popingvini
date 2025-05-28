#include "../../includes/Classes/work_block.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/person_menu.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/color_table.h"

WorkBlock::WorkBlock ()
    : m_b_interect (false)
{
}

void WorkBlock::build (size_t st, const Work& W)
{
	float f = WindowAndStyles::getFactorY ();

	RS_icon.setSize (WorksMenu::getSizeBlockIcon ());
	RS_icon.setFillColor (Color::Transparent);
	T_name.setString (names::GetStringOfHyphenation (W.w_name, 28 / WorksMenu::getWidthSimvolBigFont ()));
	T_name.setFont (names::F_pixel);
	T_name.setFillColor (Color::Transparent);
	T_name.setCharacterSize (WorksMenu::getBigFontScale ());
	T_type.setString (W.w_type);
	T_type.setFont (names::F_pixel);
	T_type.setFillColor (Color::Transparent);
	T_type.setCharacterSize (WorksMenu::getMiddleBigFontScale ());
	T_content.setString (names::GetStringOfHyphenation (
	    W.w_content,
	    (WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2 - 1) / WorksMenu::getWidthSimvolMiddleSmallFont ()));
	T_content.setFont (names::F_pixel);
	T_content.setFillColor (Color::Transparent);
	T_content.setCharacterSize (WorksMenu::getMiddleSmallFontScale () * f);
	RS_content.setSize (Vector2f (
	    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2,
	    T_content.getGlobalBounds ().height / f + 4));
	RS_content.setFillColor (Color::Transparent);
	RS_content.setOutlineThickness (1);
	RS_content.setOutlineColor (Color::Transparent);
	T_score.setString (names::GetStringOfHyphenation (
	    L"Score: " + to_wstring (W.test.f_best_score) + L"\tBest true: " + to_wstring (W.test.f_best_true) + L"%" + L"\tBest time: " + to_wstring (W.test.f_best_time) + L" c",
	    (RS_icon.getSize ().x + WorksMenu::getIInBetween () + RS_content.getSize ().x + 2) / WorksMenu::getWidthSimvolSmallFont ()));
	T_score.setFont (names::F_pixel);
	T_score.setFillColor (Color::Transparent);
	T_score.setCharacterSize (WorksMenu::getSmallFontScale () * f);
	button.setString ("WM/button/work" + to_string (st));
	button.setFillColor (Color::Transparent);
	button.setOutline (Color::Transparent);
	if (WorksMenu::getSizeBlockIcon ().y > RS_content.getSize ().y)
	{
		button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + WorksMenu::getSizeBlockIcon ().y + WorksMenu::getBlockBetween () + T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
	else
	{
		button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + 1 + RS_content.getSize ().y + 1 + WorksMenu::getBlockBetween () + T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
}

void WorkBlock::resize (const Work& W)
{
	float f = WindowAndStyles::getFactorY ();

	T_name.setString (names::GetStringOfHyphenation (W.w_name, 28 / WorksMenu::getWidthSimvolBigFont ()));
	T_type.setString (W.w_type);
	T_content.setString (names::GetStringOfHyphenation (
	    W.w_content,
	    (WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2 - 1) / WorksMenu::getWidthSimvolMiddleSmallFont ()));
	T_content.setCharacterSize (WorksMenu::getMiddleSmallFontScale () * f);
	RS_content.setSize (Vector2f (
	    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2,
	    T_content.getGlobalBounds ().height / f + 4));
	T_score.setString (names::GetStringOfHyphenation (
	    L"Score: " + to_wstring (W.test.f_best_score) + L"     Best true: " + to_wstring (W.test.f_best_true) + L"%" + L"     Best time: " + to_wstring (W.test.f_best_time * names::microsec) + L"c",
	    (RS_icon.getSize ().x + WorksMenu::getIInBetween () + RS_content.getSize ().x + 2) / WorksMenu::getWidthSimvolSmallFont ()));
	T_score.setCharacterSize (WorksMenu::getSmallFontScale () * f);
	if (WorksMenu::getSizeBlockIcon ().y > RS_content.getSize ().y)
	{
		button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + WorksMenu::getSizeBlockIcon ().y + WorksMenu::getBlockBetween () + T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
	else
	{
		button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + 1 + RS_content.getSize ().y + 1 + WorksMenu::getBlockBetween () + T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
}

void WorkBlock::transition (const Work& W)
{
	float& f = PersonMenu::getFrameTransition ();
	Color& C = PersonMenu::getButtonColor ();

	if (button.interect () or W.u_try != 0)
	{
		m_b_interect = true;

		button.setFillColor (Color (
		    ColorTable::a75.r,
		    ColorTable::a75.g,
		    ColorTable::a75.b,
		    f / 255.0 * ColorTable::a75.a));
		button.setOutline (Color (
		    ColorTable::c50.r,
		    ColorTable::c50.g,
		    ColorTable::c50.b,
		    f));
		RS_icon.setFillColor (Color (255, 255, 255, f));
		T_name.setFillColor (Color (
		    ColorTable::c200.r,
		    ColorTable::c200.g,
		    ColorTable::c200.b,
		    f));
		T_type.setFillColor (Color (
		    ColorTable::c125.r,
		    ColorTable::c125.g,
		    ColorTable::c125.b,
		    f));
		T_content.setFillColor (Color (
		    ColorTable::c150.r,
		    ColorTable::c150.g,
		    ColorTable::c150.b,
		    f));
		RS_content.setFillColor (Color (
		    ColorTable::c25.r,
		    ColorTable::c25.g,
		    ColorTable::c25.b,
		    f));
		RS_content.setOutlineColor (Color (
		    ColorTable::c75.r,
		    ColorTable::c75.g,
		    ColorTable::c75.b,
		    f));
		T_score.setFillColor (Color (
		    ColorTable::c100.r,
		    ColorTable::c100.g,
		    ColorTable::c100.b,
		    f));
	}
	else if (m_b_interect or f < 255.0)
	{
		m_b_interect = false;

		button.setFillColor (Color (
		    ColorTable::a75.r * C.r / 255.0,
		    ColorTable::a75.g * C.g / 255.0,
		    ColorTable::a75.b * C.b / 255.0,
		    f / 255.0 * ColorTable::a75.a));
		button.setOutline (Color (
		    ColorTable::c50.r * C.r / 255.0,
		    ColorTable::c50.g * C.g / 255.0,
		    ColorTable::c50.b * C.b / 255.0,
		    f));
		RS_icon.setFillColor (Color (
		    C.r,
		    C.g,
		    C.b,
		    f));
		T_name.setFillColor (Color (
		    ColorTable::c200.r * C.r / 255.0,
		    ColorTable::c200.g * C.g / 255.0,
		    ColorTable::c200.b * C.b / 255.0,
		    f));
		T_type.setFillColor (Color (
		    ColorTable::c125.r * C.r / 255.0,
		    ColorTable::c125.g * C.g / 255.0,
		    ColorTable::c125.b * C.b / 255.0,
		    f));
		T_content.setFillColor (Color (
		    ColorTable::c150.r * C.r / 255.0,
		    ColorTable::c150.g * C.g / 255.0,
		    ColorTable::c150.b * C.b / 255.0,
		    f));
		RS_content.setFillColor (Color (
		    ColorTable::c25.r * C.r / 255.0,
		    ColorTable::c25.g * C.g / 255.0,
		    ColorTable::c25.b * C.b / 255.0,
		    f));
		RS_content.setOutlineColor (Color (
		    ColorTable::c75.r * C.r / 255.0,
		    ColorTable::c75.g * C.g / 255.0,
		    ColorTable::c75.b * C.b / 255.0,
		    f));
		T_score.setFillColor (Color (
		    ColorTable::c100.r * C.r / 255.0,
		    ColorTable::c100.g * C.g / 255.0,
		    ColorTable::c100.b * C.b / 255.0,
		    f));
	}
}
