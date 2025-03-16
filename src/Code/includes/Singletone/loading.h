#ifndef LOADING_H_
#define LOADING_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

class Loading
{
	private:

		static Loading* class_obj;

		Loading ();

	protected:

		RectangleShape rectangle_shape_obj;

		Texture texture_obj;

		Text text_obj;
		Text T_load;

		float f_frame_transition;
		float f_transition_speed;
		float f_text_size;
		float f_speed_rotate;

		Color C_text_color;

		vector <Texture*> load_texture;

		vector <void const*> load_void_const;

		vector <unsigned long> load_unsigned_long;

		vector <string> load_string;

		vector <wstring> w_text;

		wstring w_load;

		Vector2f V2f_text_position;
		Vector2f V2f_text_load_position;

		unsigned u_load_number;
		unsigned u_symbols_in_line;

		bool b_load;

		string s_file_name;

		ofstream o_file;
		ifstream i_file;

		static Loading* getClass ();

	public:

		static void main ();
		static void write ();

		static RectangleShape& getSprite ();

		static Text& getSpriteText ();
		static Text& getLoadText ();

		static float getFrameTransition ();

		static bool getLoad ();
};

#endif /* LOADING_H_ */
