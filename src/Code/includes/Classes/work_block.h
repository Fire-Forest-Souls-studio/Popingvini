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
		bool m_b_interect;

	public:
		Button button;

		RectangleShape RS_icon;
		RectangleShape RS_content;

		Text T_name;
		Text T_type;
		Text T_content;
		Text T_score;

		WorkBlock ();

		void build (size_t cout, const Work& work);
		void resize (const Work& work);
		void transition (const Work& work);
};

#endif
