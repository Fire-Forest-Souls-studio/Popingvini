#ifndef CODE_WORK_H_
#define CODE_WORK_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "test.h"
#include "learn.h"

class Work
{
		// TODO: рефакторинг переменный по шаблону <m_TyPe_my_name>
		// TODO: добавить названия аргументам функций по шаблону <my_name>

	public:
		wstring w_name;
		wstring w_content;
		wstring w_type;

		unsigned u_try;

		Test test;

		Learn learn;

		Work ();
		Work (const wstring&, const wstring&, const wstring&, const wstring&);
		Work (const wstring&, const wstring&, const wstring&, const wstring&, const Test&);
};

#endif
