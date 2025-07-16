#include "../../includes/Singletone/introduction.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

#include "../../../GetPixels/GPI_Introduction.h"

Introduction* Introduction::m_class_obj = 0;

const unsigned Introduction::m_u_NEW_PINGVINON = 5000;
const unsigned Introduction::m_u_REVERS = 5000;
const unsigned Introduction::m_u_EMOTION = 3000;
const unsigned Introduction::m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO = 54;
const unsigned Introduction::m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL = 9;
const unsigned Introduction::m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL = 6;
const unsigned Introduction::m_u_FRAME_FOR_LIGHT_OUT = 35;
const unsigned Introduction::m_u_FRAME_FOR_LIGHT_FULL_OUT = 43;
const Vector2f Introduction::m_V2f_PINGVINON_DEFOLT_SIZE = Vector2f (95, 95);
const float Introduction::m_f_PINGVINON_DEFOLT_Y = 61.0;
const float Introduction::m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION = 6.0;
RectangleShape Introduction::m_RS_anim = RectangleShape (Vector2f (300, 150));
RectangleShape Introduction::m_RS_light = RectangleShape (Vector2f (900, 150));
Texture Introduction::m_T_anim;
Texture Introduction::m_T_light;
vector<Pingvinon> Introduction::m_pingvonon = vector<Pingvinon> (2);
vector<AnimPingvinon> Introduction::m_anim_pingvinon = vector<AnimPingvinon> (5);
float Introduction::m_f_frame_for_fire_forest_souls_studio = 0.0;

Introduction::Introduction ()
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

Introduction* Introduction::getClass ()
{
	if (m_class_obj != 0)
		return m_class_obj;

	m_class_obj = new Introduction ();
	return m_class_obj;
}

void Introduction::main_if_introduction ()
{
	float f = WindowAndStyles::getFactorY ();

	if (m_f_frame_for_fire_forest_souls_studio == 0.0)
	{
		getClass ();

		names::LoadFromMemory (m_T_anim, studios_png, studios_png_size, "Images/Introduction/studios.png");

		m_RS_anim.setTexture (&m_T_anim);
		m_RS_anim.setFillColor (Color (255, 255, 255, 0));
		m_RS_anim.setTextureRect (IntRect (0,
		                                   0,
		                                   m_T_anim.getSize ().x / m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL,
		                                   m_T_anim.getSize ().y / m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL));

		names::LoadFromMemory (m_T_light, studio_light_png, studio_light_png_size, "Images/Introduction/studio_light.png");

		m_RS_light.setTexture (&m_T_light);
		m_RS_light.setFillColor (Color (255, 255, 255, 0));

		names::LoadFromMemory (m_anim_pingvinon[0].texture, emotion0_1_png, emotion0_1_png_size, "Images/Introduction/emotion0_1.png");
		names::LoadFromMemory (m_anim_pingvinon[1].texture, emotion0_1_png, emotion0_1_png_size, "Images/Introduction/emotion0_1.png");
		names::LoadFromMemory (m_anim_pingvinon[2].texture, emotion2_stay_png, emotion2_stay_png_size, "Images/Introduction/emotion2_stay.png");
		names::LoadFromMemory (m_anim_pingvinon[3].texture, emotion3_jump_png, emotion3_jump_png_size, "Images/Introduction/emotion3_jump.png");
		names::LoadFromMemory (m_anim_pingvinon[4].texture, emotion4_boom_png, emotion4_boom_png_size, "Images/Introduction/emotion4_boom.png");

		for (size_t st (0); st < 2; st++)
		{
			m_pingvonon[st].rectangle.setSize (m_V2f_PINGVINON_DEFOLT_SIZE);
			m_pingvonon[st].rectangle.setTexture (&m_anim_pingvinon[0].texture);
			m_pingvonon[st].rectangle.setTextureRect (IntRect (0, 0, m_V2f_PINGVINON_DEFOLT_SIZE.x, m_V2f_PINGVINON_DEFOLT_SIZE.y));
			m_pingvonon[st].u_anim_pingvinon = 0;
			m_pingvonon[st].f_posx = float (rand () % 300);
			m_pingvonon[st].i_flip = -1;
			m_pingvonon[st].f_frame = 0.0;
		}
	}

	m_f_frame_for_fire_forest_souls_studio += names::f_microsec * names::f_time * m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION;

	if (m_f_frame_for_fire_forest_souls_studio < m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO)
	{
		if (m_f_frame_for_fire_forest_souls_studio / m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION < 1)
		{
			m_RS_anim.setFillColor (Color (255, 255, 255, m_f_frame_for_fire_forest_souls_studio / m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION * 255));
			m_RS_light.setFillColor (Color (255, 255, 255, m_f_frame_for_fire_forest_souls_studio / m_f_SPEED_FIRE_FOREST_SOULS_STUDIO_ANIMATION * 255));
		}
		else if (m_f_frame_for_fire_forest_souls_studio < m_u_FRAME_FOR_LIGHT_OUT)
		{
			m_RS_anim.setFillColor (Color (255, 255, 255, 255));
			m_RS_light.setFillColor (Color (255, 255, 255, 255));
		}
		else if (m_f_frame_for_fire_forest_souls_studio < m_u_FRAME_FOR_LIGHT_FULL_OUT)
		{
			m_RS_anim.setFillColor (Color (255,
			                               255,
			                               255,
			                               255 - (m_f_frame_for_fire_forest_souls_studio - float(m_u_FRAME_FOR_LIGHT_OUT)) / float(m_u_FRAME_FOR_LIGHT_FULL_OUT - m_u_FRAME_FOR_LIGHT_OUT)));
		}
		else
		{
			m_RS_light.setFillColor (Color (255, 255, 255, 0));
		}

		m_RS_anim.setTextureRect (IntRect (
		    m_T_anim.getSize ().x / m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL * unsigned (m_f_frame_for_fire_forest_souls_studio / m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL),
		    m_T_anim.getSize ().y / m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL * (unsigned (m_f_frame_for_fire_forest_souls_studio) % m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL),
		    m_T_anim.getSize ().x / m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_HORIZONTAL,
		    m_T_anim.getSize ().y / m_u_COUT_FRAME_FIRE_FOREST_SOULS_STUDIO_VERTICAL));
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

	m_RS_anim.setScale (f, f);
	names::SetXCenterPosition (m_RS_anim, 0.0);
	m_RS_light.setScale (f, f);
	names::SetXCenterPosition (m_RS_light, 0.0);
}
void Introduction::main_if_loading_or_introduction ()
{
	float f = WindowAndStyles::getFactorY ();

	if (rand () % unsigned (m_u_NEW_PINGVINON / (names::f_time ? names::f_time : 1.0) + 1) == 0)
	{
		Pingvinon P;
		P.rectangle.setSize (m_V2f_PINGVINON_DEFOLT_SIZE);
		P.rectangle.setTexture (&m_anim_pingvinon[0].texture);
		P.rectangle.setTextureRect (IntRect (0, 0, m_V2f_PINGVINON_DEFOLT_SIZE.x, m_V2f_PINGVINON_DEFOLT_SIZE.y));
		P.u_anim_pingvinon = 0;
		if (rand () % 2 == 0)
			P.f_posx = WindowAndStyles::getGlobalBounds ().width / f;
		else
			P.f_posx = -m_V2f_PINGVINON_DEFOLT_SIZE.x;
		if (rand () % 2 == 0)
			P.i_flip = -1;
		else
			P.i_flip = 1;
		P.f_frame = 0.0;
		m_pingvonon.push_back (P);
	}

	for (size_t st (0); st < m_pingvonon.size (); st++)
	{
		// change anim
		if (m_pingvonon[st].u_anim_pingvinon == 0 and rand () % unsigned (m_u_EMOTION / (names::f_time ? names::f_time : 1) + 1) == 0)
		{
			m_pingvonon[st].f_frame = 0;
			m_pingvonon[st].u_anim_pingvinon = rand () % m_anim_pingvinon.size ();
			m_pingvonon[st].rectangle.setTexture (&m_anim_pingvinon[m_pingvonon[st].u_anim_pingvinon].texture);
		}
		// pos
		if (rand () % unsigned (m_u_REVERS / (names::f_time ? names::f_time : 1) + 1) == 0 and m_pingvonon[st].u_anim_pingvinon == 0)
		{
			m_pingvonon[st].i_flip *= -1;
		}
		m_pingvonon[st].f_posx += m_pingvonon[st].i_flip *
		                          m_anim_pingvinon[m_pingvonon[st].u_anim_pingvinon].f_move_speed * names::f_time;
		// anim
		m_pingvonon[st].f_frame += names::f_microsec * names::f_time;
		if (m_pingvonon[st].f_frame < m_anim_pingvinon[m_pingvonon[st].u_anim_pingvinon].f_frame_cout * m_anim_pingvinon[m_pingvonon[st].u_anim_pingvinon].f_animation_speed)
		{
			if (m_pingvonon[st].i_flip < 0)
				m_pingvonon[st].rectangle.setTextureRect (IntRect (
				    0,
				    m_V2f_PINGVINON_DEFOLT_SIZE.y * unsigned (m_pingvonon[st].f_frame / m_anim_pingvinon[m_pingvonon[st].u_anim_pingvinon].f_animation_speed),
				    m_V2f_PINGVINON_DEFOLT_SIZE.x,
				    m_V2f_PINGVINON_DEFOLT_SIZE.y));
			else
				m_pingvonon[st].rectangle.setTextureRect (IntRect (
				    m_V2f_PINGVINON_DEFOLT_SIZE.x,
				    m_V2f_PINGVINON_DEFOLT_SIZE.y * unsigned (m_pingvonon[st].f_frame / m_anim_pingvinon[m_pingvonon[st].u_anim_pingvinon].f_animation_speed),
				    m_V2f_PINGVINON_DEFOLT_SIZE.x * -1,
				    m_V2f_PINGVINON_DEFOLT_SIZE.y));
		}
		else if (m_pingvonon[st].u_anim_pingvinon != 0)
		{
			m_pingvonon[st].f_frame = 0.0;
			if (rand () % 2 == 0)
			{
				m_pingvonon[st].u_anim_pingvinon = 0;
				m_pingvonon[st].rectangle.setTexture (&m_anim_pingvinon[0].texture);
			}
		}
		else
		{
			m_pingvonon[st].f_frame = 0.0;
		}
		// transform
		m_pingvonon[st].rectangle.setScale (f, f);
		m_pingvonon[st].rectangle.setPosition (m_pingvonon[st].f_posx * f,
		                                       m_f_PINGVINON_DEFOLT_Y * f);
	}
}
void Introduction::main ()
{
	if (names::game_status == GameStatus::introduction)
	{
		main_if_introduction ();
	}

	if (names::game_status == GameStatus::loading or names::game_status == GameStatus::introduction or names::game_status == GameStatus::loading_to_main_menu)
	{
		main_if_loading_or_introduction ();
	}
}

// bool

// vector <Sprite&>

const RectangleShape& Introduction::getAnimSprite ()
{
	return m_RS_anim;
}
const RectangleShape& Introduction::getLightSprite ()
{
	return m_RS_light;
}

// vector <Pingvinon>&

vector<Pingvinon>& Introduction::getPingvinons ()
{
	return m_pingvonon;
}

// FloatRect

FloatRect Introduction::getGlobalBounds ()
{
	return m_RS_anim.getGlobalBounds ();
}

// size_t

size_t Introduction::size_sprites = 3;
