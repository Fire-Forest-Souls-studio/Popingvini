#ifndef CODE_INTRODUCTION_H_
#define CODE_INTRODUCTION_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

//start

struct AnimPingvinon
{
		Texture T;
		float f_move_speed;
		float f_frame_cout;
		float f_animation_speed;
};
struct Pingvinon
{
		RectangleShape RS;
		unsigned u_anim_pingvinon;
		int i_flip;
		float f_posx;
		float f_frame;
};

class Introduction
{

	private:

		static Introduction *class_obj;

		Introduction ();

	protected:

		vector <RectangleShape> rectsangle_shape_obj;

		vector <Texture> texture_obj;

		vector <Pingvinon> pingvonon_obj;

		vector <AnimPingvinon> anim_pingvinon_obj;

		float f_frame;
		float f_time_to_swim_out;
		float f_need_time_sinse_swim_out;
		float f_time_since_clic;
		float f_need_time_since_clic;
		float f_pingvinon_defolt_y;
		float f_speed_blackfire_studio_animation;
		float f_frame_for_blackfire_studio;

		Vector2f V2f_pingvinon_defolt_size;

		unsigned u_new_pingvinon;
		unsigned u_revers;
		unsigned u_emotion;
		unsigned u_cout_frame_blackfire_studio;

		static void main_if_introduction ();
		static void main_if_loading_or_introduction ();

	public:

		static Introduction* getClass ();

		static void main ();

		static vector <RectangleShape>& getSprite ();
		static vector <Pingvinon>& getPingvinons ();

		static FloatRect getGlobalBounds ();

		static size_t size_sprites;

};

#endif
