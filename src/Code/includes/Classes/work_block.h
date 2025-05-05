/*
 * Copyright 2025 Fire-Forest-Souls-studio
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

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
		bool _b_interect;

	public:
		Button _button;

		RectangleShape _RS_icon;
		RectangleShape _RS_content;

		Text _T_name;
		Text _T_type;
		Text _T_content;
		Text _T_score;

		WorkBlock ();

		void build (size_t, const Work&);
		void resize (const Work&);
		void transition (const Work&);
};

#endif
