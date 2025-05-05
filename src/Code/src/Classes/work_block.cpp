#include "../../includes/Classes/work_block.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/person_menu.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/color_table.h"

WorkBlock::WorkBlock ()
    : _b_interect (false)
{
}

void WorkBlock::build (size_t st, const Work& W)
{
	float f = WindowAndStyles::getFactorY ();

	_RS_icon.setSize (WorksMenu::getSizeBlockIcon ());
	_RS_icon.setFillColor (Color::Transparent);
	_T_name.setString (names::GetStringOfHyphenation (W.w_name, 28 / WorksMenu::getWidthSimvolBigFont ()));
	_T_name.setFont (names::F_pixel);
	_T_name.setFillColor (Color::Transparent);
	_T_name.setCharacterSize (WorksMenu::getBigFontScale ());
	_T_type.setString (W.w_type);
	_T_type.setFont (names::F_pixel);
	_T_type.setFillColor (Color::Transparent);
	_T_type.setCharacterSize (WorksMenu::getMiddleBigFontScale ());
	_T_content.setString (names::GetStringOfHyphenation (
	    W.w_content,
	    (WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2 - 1) / WorksMenu::getWidthSimvolMiddleSmallFont ()));
	_T_content.setFont (names::F_pixel);
	_T_content.setFillColor (Color::Transparent);
	_T_content.setCharacterSize (WorksMenu::getMiddleSmallFontScale () * f);
	_RS_content.setSize (Vector2f (
	    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2,
	    _T_content.getGlobalBounds ().height / f + 4));
	_RS_content.setFillColor (Color::Transparent);
	_RS_content.setOutlineThickness (1);
	_RS_content.setOutlineColor (Color::Transparent);
	_T_score.setString (names::GetStringOfHyphenation (
	    L"Score: " + to_wstring (W.test.f_best_score) + L"\tBest true: " + to_wstring (W.test.f_best_true) + L"%" + L"\tBest time: " + to_wstring (W.test.f_best_time) + L" c",
	    (_RS_icon.getSize ().x + WorksMenu::getIInBetween () + _RS_content.getSize ().x + 2) / WorksMenu::getWidthSimvolSmallFont ()));
	_T_score.setFont (names::F_pixel);
	_T_score.setFillColor (Color::Transparent);
	_T_score.setCharacterSize (WorksMenu::getSmallFontScale () * f);
	_button.setString ("WM/button/work" + to_string (st));
	_button.setFillColor (Color::Transparent);
	_button.setOutline (Color::Transparent);
	if (WorksMenu::getSizeBlockIcon ().y > _RS_content.getSize ().y)
	{
		_button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + WorksMenu::getSizeBlockIcon ().y + WorksMenu::getBlockBetween () + _T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
	else
	{
		_button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + 1 + _RS_content.getSize ().y + 1 + WorksMenu::getBlockBetween () + _T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
}

void WorkBlock::resize (const Work& W)
{
	float f = WindowAndStyles::getFactorY ();

	_T_name.setString (names::GetStringOfHyphenation (W.w_name, 28 / WorksMenu::getWidthSimvolBigFont ()));
	_T_type.setString (W.w_type);
	_T_content.setString (names::GetStringOfHyphenation (
	    W.w_content,
	    (WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2 - 1) / WorksMenu::getWidthSimvolMiddleSmallFont ()));
	_T_content.setCharacterSize (WorksMenu::getMiddleSmallFontScale () * f);
	_RS_content.setSize (Vector2f (
	    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2 - WorksMenu::getBlockLeft () * 2 - WorksMenu::getSizeBlockIcon ().x - WorksMenu::getBlockBetween () - 2,
	    _T_content.getGlobalBounds ().height / f + 4));
	_T_score.setString (names::GetStringOfHyphenation (
	    L"Score: " + to_wstring (W.test.f_best_score) + L"     Best true: " + to_wstring (W.test.f_best_true) + L"%" + L"     Best time: " + to_wstring (W.test.f_best_time * names::microsec) + L"c",
	    (_RS_icon.getSize ().x + WorksMenu::getIInBetween () + _RS_content.getSize ().x + 2) / WorksMenu::getWidthSimvolSmallFont ()));
	_T_score.setCharacterSize (WorksMenu::getSmallFontScale () * f);
	if (WorksMenu::getSizeBlockIcon ().y > _RS_content.getSize ().y)
	{
		_button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + WorksMenu::getSizeBlockIcon ().y + WorksMenu::getBlockBetween () + _T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
	else
	{
		_button.setSize (Vector2f (
		    WindowAndStyles::getGlobalBounds ().width / f - WorksMenu::getIOutLeft () * 2 - 2 - WorksMenu::getIInLeft () * 2 - 2,
		    WorksMenu::getBlockUp () + 1 + _RS_content.getSize ().y + 1 + WorksMenu::getBlockBetween () + _T_score.getGlobalBounds ().height / f + WorksMenu::getBlockUp ()));
	}
}

void WorkBlock::transition (const Work& W)
{
	float& f = PersonMenu::getFrameTransition ();
	Color& C = PersonMenu::getButtonColor ();

	if (_button.interect () or W.u_try != 0)
	{
		_b_interect = true;

		_button.setFillColor (Color (
		    ColorTable::a75.r,
		    ColorTable::a75.g,
		    ColorTable::a75.b,
		    f / 255.0 * ColorTable::a75.a));
		_button.setOutline (Color (
		    ColorTable::c50.r,
		    ColorTable::c50.g,
		    ColorTable::c50.b,
		    f));
		_RS_icon.setFillColor (Color (255, 255, 255, f));
		_T_name.setFillColor (Color (
		    ColorTable::c200.r,
		    ColorTable::c200.g,
		    ColorTable::c200.b,
		    f));
		_T_type.setFillColor (Color (
		    ColorTable::c125.r,
		    ColorTable::c125.g,
		    ColorTable::c125.b,
		    f));
		_T_content.setFillColor (Color (
		    ColorTable::c150.r,
		    ColorTable::c150.g,
		    ColorTable::c150.b,
		    f));
		_RS_content.setFillColor (Color (
		    ColorTable::c25.r,
		    ColorTable::c25.g,
		    ColorTable::c25.b,
		    f));
		_RS_content.setOutlineColor (Color (
		    ColorTable::c75.r,
		    ColorTable::c75.g,
		    ColorTable::c75.b,
		    f));
		_T_score.setFillColor (Color (
		    ColorTable::c100.r,
		    ColorTable::c100.g,
		    ColorTable::c100.b,
		    f));
	}
	else if (_b_interect or f < 255.0)
	{
		_b_interect = false;

		_button.setFillColor (Color (
		    ColorTable::a75.r * C.r / 255.0,
		    ColorTable::a75.g * C.g / 255.0,
		    ColorTable::a75.b * C.b / 255.0,
		    f / 255.0 * ColorTable::a75.a));
		_button.setOutline (Color (
		    ColorTable::c50.r * C.r / 255.0,
		    ColorTable::c50.g * C.g / 255.0,
		    ColorTable::c50.b * C.b / 255.0,
		    f));
		_RS_icon.setFillColor (Color (
		    C.r,
		    C.g,
		    C.b,
		    f));
		_T_name.setFillColor (Color (
		    ColorTable::c200.r * C.r / 255.0,
		    ColorTable::c200.g * C.g / 255.0,
		    ColorTable::c200.b * C.b / 255.0,
		    f));
		_T_type.setFillColor (Color (
		    ColorTable::c125.r * C.r / 255.0,
		    ColorTable::c125.g * C.g / 255.0,
		    ColorTable::c125.b * C.b / 255.0,
		    f));
		_T_content.setFillColor (Color (
		    ColorTable::c150.r * C.r / 255.0,
		    ColorTable::c150.g * C.g / 255.0,
		    ColorTable::c150.b * C.b / 255.0,
		    f));
		_RS_content.setFillColor (Color (
		    ColorTable::c25.r * C.r / 255.0,
		    ColorTable::c25.g * C.g / 255.0,
		    ColorTable::c25.b * C.b / 255.0,
		    f));
		_RS_content.setOutlineColor (Color (
		    ColorTable::c75.r * C.r / 255.0,
		    ColorTable::c75.g * C.g / 255.0,
		    ColorTable::c75.b * C.b / 255.0,
		    f));
		_T_score.setFillColor (Color (
		    ColorTable::c100.r * C.r / 255.0,
		    ColorTable::c100.g * C.g / 255.0,
		    ColorTable::c100.b * C.b / 255.0,
		    f));
	}
}
