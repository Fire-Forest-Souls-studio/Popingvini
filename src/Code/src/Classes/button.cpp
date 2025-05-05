#include "../../includes/Classes/button.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"

Button::Button ()
    : C_outline (Color (0, 0, 0, 0.0))
{
}

Button::Button (const string& s)
    : C_outline (Color (0, 0, 0, 0.0))
{
	text_obj.setString (s);
	text_obj.setCharacterSize (names::f_font_hitbox_scale);
	text_obj.setFont (names::F_pixel);
	text_obj.setFillColor (names::C_font_hitbox);
	_rectangle_shape.setOutlineColor (names::C_font_hitbox);
	_rectangle_shape.setOutlineThickness (1);
}

void Button::setSize (const Vector2f& V2f)
{
	_rectangle_shape.setSize (V2f);
}

void Button::setFillColor (const Color& C)
{
	_rectangle_shape.setFillColor (C);
}

void Button::setScale (const float& f)
{
	_rectangle_shape.setScale (f, f);
	if (names::b_hitboxes_is_drawn)
	{
		_rectangle_shape.setOutlineThickness (1);
		_rectangle_shape.setOutlineColor (names::C_font_hitbox);
		text_obj.setCharacterSize (f * names::f_font_hitbox_scale);
	}
	else if (C_outline.a == 0.0)
	{
		_rectangle_shape.setOutlineThickness (0.0);
		text_obj.setCharacterSize (0);
	}
	else
	{
		_rectangle_shape.setOutlineThickness (1);
		_rectangle_shape.setOutlineColor (C_outline);
		text_obj.setCharacterSize (0);
	}
}

void Button::setPosition (const float& fx, const float& fy)
{
	_rectangle_shape.setPosition (fx, fy);
	text_obj.setPosition (fx + _rectangle_shape.getGlobalBounds ().width * 0.5 - text_obj.getGlobalBounds ().width * 0.5,
	                      fy - text_obj.getGlobalBounds ().height * names::f_lifting_hitbox_text);
}

void Button::setString (const string& s)
{
	text_obj.setString (s);
	text_obj.setCharacterSize (names::f_font_hitbox_scale);
	text_obj.setFont (names::F_pixel);
	text_obj.setFillColor (names::C_font_hitbox);
	_rectangle_shape.setOutlineColor (names::C_font_hitbox);
	_rectangle_shape.setOutlineThickness (1);
}

FloatRect Button::getGlobalBounds ()
{
	return _rectangle_shape.getGlobalBounds ();
}

const RectangleShape& Button::getRectangleShape () const
{
	return _rectangle_shape;
}

const Text& Button::getText () const
{
	return text_obj;
}

bool Button::interect () const
{
	return PC_Mouse::getGlobalBounds ().intersects (_rectangle_shape.getGlobalBounds ());
}

bool Button::pressed () const
{
	return (PC_Mouse::getGlobalBounds ().intersects (_rectangle_shape.getGlobalBounds ()) and PC_Mouse::isLeftPressed ());
}

void Button::setOutline (const Color& C)
{
	C_outline = C;
}

const Vector2f Button::getPosition () const
{
	return _rectangle_shape.getPosition ();
}
