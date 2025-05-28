#include "../../includes/Classes/text_button.h"
#include "../../includes/Singletone/window_and_styles.h"

void TextButton::setText (const string& s)
{
	text.setString (s);
}

void TextButton::setSizeByText ()
{
	m_rectangle_shape.setSize (Vector2f (
	    text.getLocalBounds ().width / WindowAndStyles::getFactorY (),
	    text.getLocalBounds ().height / WindowAndStyles::getFactorY ()));
}

void TextButton::textSetString (const String& S)
{
	text.setString (S);
	setSizeByText ();
}

void TextButton::setStyle (Uint32 U32)
{
	text.setStyle (U32);
	setSizeByText ();
}

void TextButton::setPosition (const float& fx, const float& fy)
{
	Button::setPosition (fx, fy);
	text.setPosition (fx, fy);
}
