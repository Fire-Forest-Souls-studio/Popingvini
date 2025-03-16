#ifndef CODE_WORK_BLOCK_H_
#define CODE_WORK_BLOCK_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "../Classes/button.h"
#include "../Classes/work.h"

class WorkBlock
{
	protected:

		bool b_interect;

	public:

		Button button;

		RectangleShape RS_icon;
		RectangleShape RS_content;

		Text T_name;
		Text T_type;
		Text T_content;
		Text T_score;

		WorkBlock ();

		void build (size_t, const Work&);
		void resize (const Work&);
		void transition (const Work&);
};

#endif
