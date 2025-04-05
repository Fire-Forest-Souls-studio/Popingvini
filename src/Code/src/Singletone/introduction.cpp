#include "../../includes/Singletone/introduction.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

#include "../../../GetPixels/GPI_Introduction.h"

//private

Introduction* Introduction::class_obj = 0;

Introduction::Introduction () :
		m_rectsangle_shape (Vector2f (300, 150)),

		m_pingvonon (2),

		m_anim_pingvinon (5),

				m_f_PINGVINON_DEFOLT_Y (61.0),
				m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION (6.0),
				m_f_frame_for_fire_forest_souls_studio (0.0),

				m_V2f_PINGVINON_DEFOLT_SIZE (95, 95),

				m_u_NEW_PINGVINON (5000),
				m_u_REVERS (5000),
				m_u_EMOTION (3000),
				m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO (54),
				m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL (9),
				m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL (6)
{
	m_anim_pingvinon[0].f_animation_speed = 0.1;
	m_anim_pingvinon[0].f_frame_cout = 10.0;
	m_anim_pingvinon[0].f_move_speed = 0.01;
	m_anim_pingvinon[1].f_animation_speed = 0.066666667;
	m_anim_pingvinon[1].f_frame_cout = 8.0;
	m_anim_pingvinon[1].f_move_speed = 0.02;
	m_anim_pingvinon[2].f_animation_speed = 0.1;
	m_anim_pingvinon[2].f_frame_cout = 7.0;
	m_anim_pingvinon[2].f_move_speed = 0.0;
	m_anim_pingvinon[3].f_animation_speed = 0.1;
	m_anim_pingvinon[3].f_frame_cout = 14.0;
	m_anim_pingvinon[3].f_move_speed = 0.0;
	m_anim_pingvinon[4].f_animation_speed = 0.1;
	m_anim_pingvinon[4].f_frame_cout = 20.0;
	m_anim_pingvinon[4].f_move_speed = 0.0;
}

//public
//Introduction*

Introduction* Introduction::getClass ()
{
	if (class_obj != 0)
		return class_obj;

	class_obj = new Introduction ();
	return class_obj;
}

//void

void Introduction::main_if_introduction ()
{
	Introduction* I_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	//loadFromMemory

	if (I_->m_f_frame_for_fire_forest_souls_studio == 0.0)
	{

		//introduction

		names::LoadFromMemory (I_->m_texture, studios_png, studios_png_size, "Images/Introduction/studios.png");

		I_->m_rectsangle_shape.setTexture (&I_->m_texture);
		I_->m_rectsangle_shape.setFillColor (Color (255, 255, 255, 0));
		I_->m_rectsangle_shape.setTextureRect (IntRect (
				0,
				0,
				I_->m_texture.getSize ().x / I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL,
				I_->m_texture.getSize ().y / I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL
						));

		//popingvinons

		names::LoadFromMemory (I_->m_anim_pingvinon[0].T, emotion0_1_png, emotion0_1_png_size, "Images/Introduction/emotion0_1.png");
		names::LoadFromMemory (I_->m_anim_pingvinon[1].T, emotion0_1_png, emotion0_1_png_size, "Images/Introduction/emotion0_1.png");
		names::LoadFromMemory (I_->m_anim_pingvinon[2].T, emotion2_stay_png, emotion2_stay_png_size, "Images/Introduction/emotion2_stay.png");
		names::LoadFromMemory (I_->m_anim_pingvinon[3].T, emotion3_jump_png, emotion3_jump_png_size, "Images/Introduction/emotion3_jump.png");
		names::LoadFromMemory (I_->m_anim_pingvinon[4].T, emotion4_boom_png, emotion4_boom_png_size, "Images/Introduction/emotion4_boom.png");

		for (size_t st (0); st < 2; st++)
		{
			I_->m_pingvonon[st].RS.setSize (I_->m_V2f_PINGVINON_DEFOLT_SIZE);
			I_->m_pingvonon[st].RS.setTexture (&I_->m_anim_pingvinon[0].T);
			I_->m_pingvonon[st].RS.setTextureRect (IntRect (0, 0, I_->m_V2f_PINGVINON_DEFOLT_SIZE.x, I_->m_V2f_PINGVINON_DEFOLT_SIZE.y));
			I_->m_pingvonon[st].u_anim_pingvinon = 0;
			I_->m_pingvonon[st].f_posx = float (rand () % 300);
			I_->m_pingvonon[st].i_flip = -1;
			I_->m_pingvonon[st].f_frame = 0.0;
		}
	}

	//анимация

	I_->m_f_frame_for_fire_forest_souls_studio += names::microsec * names::f_time * I_->m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION;

	if (I_->m_f_frame_for_fire_forest_souls_studio < I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO)
	{
		if (I_->m_f_frame_for_fire_forest_souls_studio / I_->m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION < 1)
		{
			I_->m_rectsangle_shape.setFillColor (Color (255, 255, 255, I_->m_f_frame_for_fire_forest_souls_studio / I_->m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION * 255));
		}
		else
		{
			I_->m_rectsangle_shape.setFillColor (Color (255, 255, 255, 255));
		}

		I_->m_rectsangle_shape.setTextureRect (IntRect (
				I_->m_texture.getSize ().x / I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL
						* unsigned (I_->m_f_frame_for_fire_forest_souls_studio / I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL),
				I_->m_texture.getSize ().y / I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL
						* (unsigned (I_->m_f_frame_for_fire_forest_souls_studio) % I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL),
				I_->m_texture.getSize ().x / I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL,
				I_->m_texture.getSize ().y / I_->m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL
						));
	}
	else
	{
		cout << "ccc" << endl;
		names::game_status = GameStatus::loading;
	}

	if (Keyboard::isKeyPressed (Keyboard::Space))
	{
		names::game_status = GameStatus::loading;
	}

	//трансформ

	I_->m_rectsangle_shape.setScale (f, f);
	names::SetXCenterPosition (I_->m_rectsangle_shape, 0.0);

}
void Introduction::main_if_loading_or_introduction ()
{
	Introduction* I_ = getClass ();
	float f = WindowAndStyles::getFactorY ();

	if (rand () % unsigned (I_->m_u_NEW_PINGVINON / (
			names::f_time ? names::f_time : 1.0) + 1) == 0)
	{
		Pingvinon P;
		P.RS.setSize (I_->m_V2f_PINGVINON_DEFOLT_SIZE);
		P.RS.setTexture (&I_->m_anim_pingvinon[0].T);
		P.RS.setTextureRect (IntRect (0, 0, I_->m_V2f_PINGVINON_DEFOLT_SIZE.x, I_->m_V2f_PINGVINON_DEFOLT_SIZE.y));
		P.u_anim_pingvinon = 0;
		if (rand () % 2 == 0)
			P.f_posx = WindowAndStyles::getGlobalBounds ().width / f;
		else
			P.f_posx = -I_->m_V2f_PINGVINON_DEFOLT_SIZE.x;
		if (rand () % 2 == 0)
			P.i_flip = -1;
		else
			P.i_flip = 1;
		P.f_frame = 0.0;
		I_->m_pingvonon.push_back (P);
	}

	for (size_t st (0); st < I_->m_pingvonon.size (); st++)
	{
		//change anim
		if (I_->m_pingvonon[st].u_anim_pingvinon == 0 and rand () % unsigned (I_->m_u_EMOTION / (
				names::f_time ? names::f_time : 1) + 1) == 0)
		{
			I_->m_pingvonon[st].f_frame = 0;
			I_->m_pingvonon[st].u_anim_pingvinon = rand () % I_->m_anim_pingvinon.size ();
			I_->m_pingvonon[st].RS.setTexture (&I_->m_anim_pingvinon[I_->m_pingvonon[st].u_anim_pingvinon].T);
		}
		//pos
		if (rand () % unsigned (I_->m_u_REVERS / (names::f_time ? names::f_time : 1) + 1) == 0
				and I_->m_pingvonon[st].u_anim_pingvinon == 0)
		{
			I_->m_pingvonon[st].i_flip *= -1;
		}
		I_->m_pingvonon[st].f_posx += I_->m_pingvonon[st].i_flip *
				I_->m_anim_pingvinon[I_->m_pingvonon[st].u_anim_pingvinon].f_move_speed * names::f_time;
		//anim
		I_->m_pingvonon[st].f_frame += names::microsec * names::f_time;
		if (I_->m_pingvonon[st].f_frame < I_->m_anim_pingvinon[I_->m_pingvonon[st].u_anim_pingvinon].f_frame_cout
				* I_->m_anim_pingvinon[I_->m_pingvonon[st].u_anim_pingvinon].f_animation_speed)
		{
			if (I_->m_pingvonon[st].i_flip < 0)
				I_->m_pingvonon[st].RS.setTextureRect (IntRect (
						0,
						I_->m_V2f_PINGVINON_DEFOLT_SIZE.y * unsigned (I_->m_pingvonon[st].f_frame / I_->m_anim_pingvinon[I_->m_pingvonon[st].u_anim_pingvinon].f_animation_speed),
						I_->m_V2f_PINGVINON_DEFOLT_SIZE.x,
						I_->m_V2f_PINGVINON_DEFOLT_SIZE.y));
			else
				I_->m_pingvonon[st].RS.setTextureRect (IntRect (
						I_->m_V2f_PINGVINON_DEFOLT_SIZE.x,
						I_->m_V2f_PINGVINON_DEFOLT_SIZE.y * unsigned (I_->m_pingvonon[st].f_frame / I_->m_anim_pingvinon[I_->m_pingvonon[st].u_anim_pingvinon].f_animation_speed),
						I_->m_V2f_PINGVINON_DEFOLT_SIZE.x * -1,
						I_->m_V2f_PINGVINON_DEFOLT_SIZE.y));
		}
		else if (I_->m_pingvonon[st].u_anim_pingvinon != 0)
		{
			I_->m_pingvonon[st].f_frame = 0.0;
			if (rand () % 2 == 0)
			{
				I_->m_pingvonon[st].u_anim_pingvinon = 0;
				I_->m_pingvonon[st].RS.setTexture (&I_->m_anim_pingvinon[0].T);
			}
		}
		else
		{
			I_->m_pingvonon[st].f_frame = 0.0;
		}
		//transform
		I_->m_pingvonon[st].RS.setScale (f, f);
		I_->m_pingvonon[st].RS.setPosition (I_->m_pingvonon[st].f_posx * f,
				I_->m_f_PINGVINON_DEFOLT_Y * f);
	}
}
void Introduction::main ()
{
	if (names::game_status == GameStatus::introduction)
	{
		main_if_introduction ();
	}

	if (names::game_status == GameStatus::loading
			or names::game_status == GameStatus::introduction
			or names::game_status == GameStatus::loading_to_main_menu)
	{
		main_if_loading_or_introduction ();
	}
}

//bool

//vector <Sprite&>

RectangleShape& Introduction::getSprite ()
{
	return getClass ()->m_rectsangle_shape;
}

//vector <Pingvinon>&

vector <Pingvinon>& Introduction::getPingvinons ()
{
	return getClass ()->m_pingvonon;
}

//FloatRect

FloatRect Introduction::getGlobalBounds ()
{
	return getClass ()->m_rectsangle_shape.getGlobalBounds ();
}

//size_t

size_t Introduction::size_sprites = 3;
