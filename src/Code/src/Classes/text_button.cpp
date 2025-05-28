#include "../../includes/Classes/text_button.h"
#include "../../includes/Singletone/window_and_styles.h"

void TextButton::setText (const string& s)
{
	_text.setString (s);
}

void TextButton::setSizeByText ()
{
	m_rectangle_shape.setSize (Vector2f (
	    _text.getLocalBounds ().width / WindowAndStyles::getFactorY (),
	    _text.getLocalBounds ().height / WindowAndStyles::getFactorY ()));
}

void TextButton::textSetString (const String& S)
{
	_text.setString (S);
	setSizeByText ();
}

void TextButton::setStyle (Uint32 U32)
{
	_text.setStyle (U32);
	setSizeByText ();
}

void TextButton::setPosition (const float& fx, const float& fy)
{
	Button::setPosition (fx, fy);
	_text.setPosition (fx, fy);
}
