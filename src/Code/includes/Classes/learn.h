#ifndef CODE_LEARN_H_
#define CODE_LEARN_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Learn
{
		// TODO: рефакторинг переменный по шаблону <m_TyPe_my_name>
		// TODO: добавить названия аргументам функций по шаблону <my_name>

	public:
		wstring w_text;

		Learn ();
		Learn (const wstring&);
};

#endif
