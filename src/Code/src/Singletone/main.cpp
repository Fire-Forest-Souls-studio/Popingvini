/*
 * Copyright 2025 Fire-Forest-Souls-studio
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

// TODO: добавить ссылку на GitHub студии

#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/pc_mouse.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/introduction.h"
#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/error_class.h"
#include "../../includes/Singletone/main_menu.h"
#include "../../includes/Singletone/person_menu.h"
#include "../../includes/Singletone/language_menu.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/learn_menu.h"
#include "../../includes/Singletone/test_menu.h"

#include "../../../GetPixels/GPS.h"

int main (int argc, char* argv[0])
{
	srand (time (NULL));
	names::LoadFromMemory (names::F_pixel, pixel_font_by_BLACKFIRE_otf, pixel_font_by_BLACKFIRE_otf_size, "Shrift/pixel_font_by_BLACKFIRE.otf");
	names::SetPath (argv[0]);

	WindowAndStyles::start ();
	WorksMenu::start ();

	while (WindowAndStyles::isOpen ())
	{
		WindowAndStyles::main ();
		if (names::f_time != 0.0)
		{
			PC_Mouse::main ();
			Introduction::main ();
		}
		Loading::main ();
		if (names::f_time != 0.0)
		{
			Error_class::main ();
			MainMenu::main ();
			PersonMenu::main ();
			LanguageMenu::main ();
			WorksMenu::main ();
			LearnMenu::main ();
			TestMenu::main ();
		}

		WorksMenu::clear ();
		WindowAndStyles::clear ();
	}

	return 0;
}
