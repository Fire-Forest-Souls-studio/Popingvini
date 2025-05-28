#ifndef CODE_LANGUAGE_H_
#define CODE_LANGUAGE_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "image_button.h"
#include "work.h"

class Language
{
	public:
		string s_name;

		ImageButton image_button;

		vector<Work> work;

		Texture texture;

		Language (const string& name);

		void addWork (const Work& work);
};

#endif
