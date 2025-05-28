#ifndef CODE_TEXT_BUTTON_H
#define CODE_TEXT_BUTTON_H

#include "button.h"

class TextButton : public Button
{
	public:
		Text text;

		using Button::Button;

		void setText (const string& text);
		void setSizeByText ();
		void textSetString (const String& text);
		void setStyle (Uint32 style);

		void setPosition (const float& x, const float& y) override;
};

#endif
