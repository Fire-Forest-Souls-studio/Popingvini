#ifndef CODE_TEST_H_
#define CODE_TEST_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#include "question.h"

class Test
{
	public:

		float f_best_true;
		float f_best_time;
		float f_best_score;

		vector <Question> question;

		Test ();
		Test (const vector <Question>&);
};

#endif
