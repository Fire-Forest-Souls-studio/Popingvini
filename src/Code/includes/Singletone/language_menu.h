#ifndef LANGUAGE_MENU_H_
#define LANGUAGE_MENU_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

#include "../Classes/language.h"

class LanguageMenu
{
		// TODO: рефакторинг переменный по шаблону <m_TyPe_my_name>
		// TODO: добавить названия аргументам функций по шаблону <my_name>

	private:
		Language L_python;

		LanguageMenu ();

		static LanguageMenu* class_obj;

	protected:
		static LanguageMenu* getClass ();

		static void main_load ();
		static void main_main ();
		static void main_transitionOf ();

	public:
		static void main ();

		static ImageButton& getPythonButton ();

		static Language& getPython ();
};

#endif
