#ifndef CODE_TEXT_BUTTON_H
#define CODE_TEXT_BUTTON_H

#include "button.h"

class TextButton : public Button
{
		// TODO: рефакторинг переменный по шаблону <m_TyPe_my_name>
		// TODO: добавить названия аргументам функций по шаблону <my_name>

	public:
		Text _text;

		using Button::Button;

		void setText (const string&);
		void setSizeByText ();
		void textSetString (const String&);
		void setStyle (Uint32);

		void setPosition (const float&, const float&) override;
};

#endif
