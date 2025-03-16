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
