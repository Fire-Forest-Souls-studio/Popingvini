#ifndef CODE_NAMES_H_
#define CODE_NAMES_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace sf;

// start

enum GameStatus
{
	introduction = 0,
	loading,
	loading_to_main_menu,
	main_menu,
	main_menu_to_person_menu,
	person_menu,
	language_menu,
	works_menu,
	works_menu_to_main_menu,
	learn,
	test
};

class names
{

	public:
		static bool b_hitboxes_is_drawn;
		static bool b_shader_is_on;

		static Clock C_clock;

		static Event E_event;

		static float f_time;
		static float f_microsec;
		static float f_font_hitbox_scale;
		static float f_lifting_hitbox_text;

		static Color C_font_hitbox;

		static Font F_pixel;

		static unsigned u_factor_of_resolution;

		static GameStatus game_status;

		static string s_path;

		static void LoadFromMemory (Texture& texture, void const* data, unsigned long size, const string& filename, bool two_tipes_for_shader = false);
		static void LoadFromMemory (Font& font, void const* data, unsigned long size, const string& filename);
		static void LoadFromMemory (Image& image, void const* data, unsigned long size, const string& filename);
		static void LoadFromMemory (SoundBuffer& sound_buffer, void const* data, unsigned long size, const string& filename);
		static void LoadFromMemory (Shader& shader, const string& shader_text, const string& filename);
		static void SetXCenterPosition (Text& text, const float& y);
		static void SetXCenterPosition (RectangleShape& rectangleshape, float y);
		static void SetPath (char* argv);

		static string GetStringOfHyphenation (const string& string, int max);
		static wstring GetStringOfHyphenation (const wstring& wstring, int max);
};

#endif
