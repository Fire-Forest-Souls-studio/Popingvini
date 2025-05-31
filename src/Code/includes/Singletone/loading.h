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
		static Loading* m_class_obj;

		Loading ();

	protected:
		RectangleShape m_rectangle_shape;

		Texture m_texture;

		Text m_text;
		Text m_T_load;

		float m_f_frame_transition;
		float m_f_transition_speed;
		float m_f_text_size;
		float m_f_speed_rotate;

		Color m_C_text_color;

		vector<Texture*> m_load_texture;

		vector<void const*> m_load_void_const;

		vector<unsigned long> m_load_unsigned_long;

		vector<string> m_load_string;

		vector<wstring> m_w_text;

		wstring m_w_load;

		Vector2f m_V2f_text_position;
		Vector2f m_V2f_text_load_position;

		unsigned m_u_load_number;
		unsigned m_u_symbols_in_line;

		bool m_b_load;

		string m_s_file_name;

		ofstream m_o_file;
		ifstream m_i_file;

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
