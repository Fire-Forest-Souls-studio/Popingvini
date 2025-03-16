#include "../../includes/Singletone/introduction.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"

#include "../../../GetPixels/GPI_Introduction.h"

//private

Introduction* Introduction::class_obj = 0;

Introduction::Introduction () :
		rectsangle_shape_obj (size_sprites),

		texture_obj (size_sprites),

		pingvonon_obj (2),

		anim_pingvinon_obj (5),

		f_frame (0.0),
				f_time_to_swim_out (3.0),
				f_need_time_sinse_swim_out (5.0),
				f_time_since_clic (0.0),
				f_need_time_since_clic (0.5),
				f_pingvinon_defolt_y (61.0),
				f_speed_blackfire_studio_animation (6.5),
				f_frame_for_blackfire_studio (0.0),

				V2f_pingvinon_defolt_size (95, 95),

				u_new_pingvinon (5000),
				u_revers (5000),
				u_emotion (3000),
				u_cout_frame_blackfire_studio (14)
{
	rectsangle_shape_obj[0].setSize (Vector2f (300, 150));
	rectsangle_shape_obj[1].setSize (Vector2f (300, 150));
	rectsangle_shape_obj[2].setSize (Vector2f (300, 150));

	anim_pingvinon_obj[0].f_animation_speed = 0.1;
	anim_pingvinon_obj[0].f_frame_cout = 10.0;
	anim_pingvinon_obj[0].f_move_speed = 0.01;
	anim_pingvinon_obj[1].f_animation_speed = 0.066666667;
	anim_pingvinon_obj[1].f_frame_cout = 8.0;
	anim_pingvinon_obj[1].f_move_speed = 0.02;
	anim_pingvinon_obj[2].f_animation_speed = 0.1;
	anim_pingvinon_obj[2].f_frame_cout = 7.0;
	anim_pingvinon_obj[2].f_move_speed = 0.0;
	anim_pingvinon_obj[3].f_animation_speed = 0.1;
	anim_pingvinon_obj[3].f_frame_cout = 14.0;
	anim_pingvinon_obj[3].f_move_speed = 0.0;
	anim_pingvinon_obj[4].f_animation_speed = 0.1;
	anim_pingvinon_obj[4].f_frame_cout = 20.0;
	anim_pingvinon_obj[4].f_move_speed = 0.0;
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
	float f = WindowAndStyles::getFactorY();

	//loadFromMemory

	if (I_->f_frame == 0.0)
	{

		//introduction

		names::LoadFromMemory (I_->texture_obj[0], blackfire_studio_png, blackfire_studio_png_size, "Images/Introduction/blackfire_studio.png");

		I_->rectsangle_shape_obj[0].setTexture (&I_->texture_obj[0]);
		I_->rectsangle_shape_obj[0].setFillColor (Color (255, 255, 255, 0));
		I_->rectsangle_shape_obj[0].setTextureRect (IntRect (0, 0,
				I_->texture_obj[0].getSize ().x,
				I_->texture_obj[0].getSize ().y / I_->u_cout_frame_blackfire_studio));

		names::LoadFromMemory (I_->texture_obj[1], gnome_studio_png, gnome_studio_png_size, "Images/Introduction/gnome_studio.png");

		I_->rectsangle_shape_obj[1].setTexture (&I_->texture_obj[1]);
		I_->rectsangle_shape_obj[1].setFillColor (Color (255, 255, 255, 0));

		names::LoadFromMemory (I_->texture_obj[2], popingvini_studio_png, popingvini_studio_png_size, "Images/Introduction/popingvini_studio.png");

		I_->rectsangle_shape_obj[2].setTexture (&I_->texture_obj[2]);
		I_->rectsangle_shape_obj[2].setFillColor (Color (255, 255, 255, 0));

		//popingvinons

		names::LoadFromMemory (I_->anim_pingvinon_obj[0].T, emotion0_1_png, emotion0_1_png_size, "Images/Introduction/emotion0_1.png");
		names::LoadFromMemory (I_->anim_pingvinon_obj[1].T, emotion0_1_png, emotion0_1_png_size, "Images/Introduction/emotion0_1.png");
		names::LoadFromMemory (I_->anim_pingvinon_obj[2].T, emotion2_stay_png, emotion2_stay_png_size, "Images/Introduction/emotion2_stay.png");
		names::LoadFromMemory (I_->anim_pingvinon_obj[3].T, emotion3_jump_png, emotion3_jump_png_size, "Images/Introduction/emotion3_jump.png");
		names::LoadFromMemory (I_->anim_pingvinon_obj[4].T, emotion4_boom_png, emotion4_boom_png_size, "Images/Introduction/emotion4_boom.png");

		for (size_t st (0); st < 2; st++)
		{
			I_->pingvonon_obj[st].RS.setSize (I_->V2f_pingvinon_defolt_size);
			I_->pingvonon_obj[st].RS.setTexture (&I_->anim_pingvinon_obj[0].T);
			I_->pingvonon_obj[st].RS.setTextureRect (IntRect (0, 0, I_->V2f_pingvinon_defolt_size.x, I_->V2f_pingvinon_defolt_size.y));
			I_->pingvonon_obj[st].u_anim_pingvinon = 0;
			I_->pingvonon_obj[st].f_posx = float (rand () % 300);
			I_->pingvonon_obj[st].i_flip = -1;
			I_->pingvonon_obj[st].f_frame = 0.0;
		}
	}

	//анимация

	I_->f_frame += names::microsec * names::f_time;
	I_->f_time_since_clic += names::microsec * names::f_time;

	if (I_->f_frame <= I_->f_time_to_swim_out * 2 + I_->f_need_time_sinse_swim_out)
	{
		if (I_->f_frame < I_->f_time_to_swim_out)
		{
			I_->rectsangle_shape_obj[0].setFillColor (Color (255, 255, 255, I_->f_frame * 255 / I_->f_time_to_swim_out));
			WindowAndStyles::setColor (Color (
					WindowAndStyles::getDefoultColor ().r - I_->f_frame * WindowAndStyles::getDefoultColor ().r / I_->f_time_to_swim_out,
					WindowAndStyles::getDefoultColor ().g - I_->f_frame * WindowAndStyles::getDefoultColor ().g / I_->f_time_to_swim_out,
					WindowAndStyles::getDefoultColor ().b - I_->f_frame * WindowAndStyles::getDefoultColor ().b / I_->f_time_to_swim_out,
					255));
		}
		else if (I_->f_frame < I_->f_time_to_swim_out + I_->f_need_time_sinse_swim_out)
		{
			I_->rectsangle_shape_obj[0].setFillColor (Color (255, 255, 255, 255));
			WindowAndStyles::setColor (Color (0, 0, 0, 255));
		}
		else if (I_->f_frame < I_->f_time_to_swim_out * 2 + I_->f_need_time_sinse_swim_out)
		{
			I_->rectsangle_shape_obj[0].setFillColor (Color (255, 255, 255,
					255 - ( (I_->f_frame - I_->f_time_to_swim_out - I_->f_need_time_sinse_swim_out) * 255 / I_->f_time_to_swim_out)));
			WindowAndStyles::setColor (Color (
					(I_->f_frame - I_->f_time_to_swim_out - I_->f_need_time_sinse_swim_out) * WindowAndStyles::getDefoultColor ().r / I_->f_time_to_swim_out,
					(I_->f_frame - I_->f_time_to_swim_out - I_->f_need_time_sinse_swim_out) * WindowAndStyles::getDefoultColor ().g / I_->f_time_to_swim_out,
					(I_->f_frame - I_->f_time_to_swim_out - I_->f_need_time_sinse_swim_out) * WindowAndStyles::getDefoultColor ().b / I_->f_time_to_swim_out,
					255));
		}
		else
		{
			I_->rectsangle_shape_obj[0].setFillColor (Color (255, 255, 255, 0));
			WindowAndStyles::setColor (Color (0, 0, 0, 0));
		}

		I_->f_frame_for_blackfire_studio += 0.001 * names::f_time;
		if (I_->f_frame_for_blackfire_studio > I_->u_cout_frame_blackfire_studio / I_->f_speed_blackfire_studio_animation)
		{
			I_->f_frame_for_blackfire_studio = 0;
		}
		I_->rectsangle_shape_obj[0].setTextureRect (IntRect (
				0,
				I_->texture_obj[0].getSize ().y / I_->u_cout_frame_blackfire_studio * unsigned (I_->f_frame_for_blackfire_studio * I_->f_speed_blackfire_studio_animation),
				I_->texture_obj[0].getSize ().x,
				I_->texture_obj[0].getSize ().y / I_->u_cout_frame_blackfire_studio));
	}
	else if (I_->f_frame <= I_->f_time_to_swim_out * 4 + I_->f_need_time_sinse_swim_out * 2)
	{
		if (I_->f_frame < I_->f_time_to_swim_out * 3 + I_->f_need_time_sinse_swim_out)
		{
			I_->rectsangle_shape_obj[1].setFillColor (Color (255, 255, 255, (I_->f_frame - I_->f_time_to_swim_out * 2 - I_->f_need_time_sinse_swim_out) * 255 / I_->f_time_to_swim_out));
			WindowAndStyles::setColor (Color (0, 0, 0, 0));
		}
		else if (I_->f_frame < I_->f_time_to_swim_out * 3 + I_->f_need_time_sinse_swim_out * 2)
		{
			I_->rectsangle_shape_obj[1].setFillColor (Color (255, 255, 255, 255));
		}
		else if (I_->f_frame < I_->f_time_to_swim_out * 4 + I_->f_need_time_sinse_swim_out * 2)
		{
			I_->rectsangle_shape_obj[1].setFillColor (Color (255, 255, 255,
					255 - ( (I_->f_frame - I_->f_time_to_swim_out * 3 - I_->f_need_time_sinse_swim_out * 2) * 255 / I_->f_time_to_swim_out)));
		}
		else
		{
			I_->rectsangle_shape_obj[1].setFillColor (Color (255, 255, 255, 0));
		}
	}
	else if (I_->f_frame <= I_->f_time_to_swim_out * 6 + I_->f_need_time_sinse_swim_out * 3)
	{
		if (I_->f_frame < I_->f_time_to_swim_out * 5 + I_->f_need_time_sinse_swim_out * 2)
		{
			I_->rectsangle_shape_obj[2].setFillColor (Color (255, 255, 255, (I_->f_frame - I_->f_time_to_swim_out * 4 - I_->f_need_time_sinse_swim_out * 2) * 255 / I_->f_time_to_swim_out));
		}
		else if (I_->f_frame < I_->f_time_to_swim_out * 5 + I_->f_need_time_sinse_swim_out * 3)
		{
			I_->rectsangle_shape_obj[2].setFillColor (Color (255, 255, 255, 255));
		}
		else if (I_->f_frame < I_->f_time_to_swim_out * 6 + I_->f_need_time_sinse_swim_out * 3)
		{
			I_->rectsangle_shape_obj[2].setFillColor (Color (255, 255, 255,
					255 - ( (I_->f_frame - I_->f_time_to_swim_out * 5 - I_->f_need_time_sinse_swim_out * 3) * 255 / I_->f_time_to_swim_out)));
		}
		else
		{
			I_->rectsangle_shape_obj[2].setFillColor (Color (255, 255, 255, 0));
		}
	}
	else
	{
		names::game_status = GameStatus::loading;
	}

	if (Keyboard::isKeyPressed (Keyboard::Space) and I_->f_time_since_clic > I_->f_need_time_since_clic)
	{
		I_->f_frame = I_->f_time_to_swim_out * 6 + I_->f_need_time_sinse_swim_out * 3;
		I_->f_time_since_clic = 0;
		WindowAndStyles::setColor (Color (0, 0, 0, 0));
	}

	//трансформ

	for (size_t st (0); st < 3; st++)
	{
		I_->rectsangle_shape_obj[st].setScale (f, f);
		names::SetXCenterPosition (I_->rectsangle_shape_obj[st], 0.0);
	}

}
void Introduction::main_if_loading_or_introduction ()
{
	Introduction* I_ = getClass ();
	float f = WindowAndStyles::getFactorY();

	if (rand () % unsigned (I_->u_new_pingvinon / (
			names::f_time ? names::f_time : 1.0) + 1) == 0)
	{
		Pingvinon P;
		P.RS.setSize (I_->V2f_pingvinon_defolt_size);
		P.RS.setTexture (&I_->anim_pingvinon_obj[0].T);
		P.RS.setTextureRect (IntRect (0, 0, I_->V2f_pingvinon_defolt_size.x, I_->V2f_pingvinon_defolt_size.y));
		P.u_anim_pingvinon = 0;
		if (rand () % 2 == 0)
			P.f_posx = WindowAndStyles::getGlobalBounds ().width / f;
		else
			P.f_posx = -I_->V2f_pingvinon_defolt_size.x;
		if (rand () % 2 == 0)
			P.i_flip = -1;
		else
			P.i_flip = 1;
		P.f_frame = 0.0;
		I_->pingvonon_obj.push_back (P);
	}

	for (size_t st (0); st < I_->pingvonon_obj.size (); st++)
	{
		//change anim
		if (I_->pingvonon_obj[st].u_anim_pingvinon == 0 and rand () % unsigned (I_->u_emotion / (
				names::f_time ? names::f_time : 1) + 1) == 0)
		{
			I_->pingvonon_obj[st].f_frame = 0;
			I_->pingvonon_obj[st].u_anim_pingvinon = rand () % I_->anim_pingvinon_obj.size ();
			I_->pingvonon_obj[st].RS.setTexture (&I_->anim_pingvinon_obj[I_->pingvonon_obj[st].u_anim_pingvinon].T);
		}
		//pos
		if (rand () % unsigned (I_->u_revers / (names::f_time ? names::f_time : 1) + 1) == 0
				and I_->pingvonon_obj[st].u_anim_pingvinon == 0)
		{
			I_->pingvonon_obj[st].i_flip *= -1;
		}
		I_->pingvonon_obj[st].f_posx += I_->pingvonon_obj[st].i_flip *
				I_->anim_pingvinon_obj[I_->pingvonon_obj[st].u_anim_pingvinon].f_move_speed * names::f_time;
		//anim
		I_->pingvonon_obj[st].f_frame += names::microsec * names::f_time;
		if (I_->pingvonon_obj[st].f_frame < I_->anim_pingvinon_obj[I_->pingvonon_obj[st].u_anim_pingvinon].f_frame_cout
				* I_->anim_pingvinon_obj[I_->pingvonon_obj[st].u_anim_pingvinon].f_animation_speed)
		{
			if (I_->pingvonon_obj[st].i_flip < 0)
				I_->pingvonon_obj[st].RS.setTextureRect (IntRect (
						0,
						I_->V2f_pingvinon_defolt_size.y * unsigned (I_->pingvonon_obj[st].f_frame / I_->anim_pingvinon_obj[I_->pingvonon_obj[st].u_anim_pingvinon].f_animation_speed),
						I_->V2f_pingvinon_defolt_size.x,
						I_->V2f_pingvinon_defolt_size.y));
			else
				I_->pingvonon_obj[st].RS.setTextureRect (IntRect (
						I_->V2f_pingvinon_defolt_size.x,
						I_->V2f_pingvinon_defolt_size.y * unsigned (I_->pingvonon_obj[st].f_frame / I_->anim_pingvinon_obj[I_->pingvonon_obj[st].u_anim_pingvinon].f_animation_speed),
						I_->V2f_pingvinon_defolt_size.x * -1,
						I_->V2f_pingvinon_defolt_size.y));
		}
		else if (I_->pingvonon_obj[st].u_anim_pingvinon != 0)
		{
			I_->pingvonon_obj[st].f_frame = 0.0;
			if (rand () % 2 == 0)
			{
				I_->pingvonon_obj[st].u_anim_pingvinon = 0;
				I_->pingvonon_obj[st].RS.setTexture (&I_->anim_pingvinon_obj[0].T);
			}
		}
		else
		{
			I_->pingvonon_obj[st].f_frame = 0.0;
		}
		//transform
		I_->pingvonon_obj[st].RS.setScale (f, f);
		I_->pingvonon_obj[st].RS.setPosition (I_->pingvonon_obj[st].f_posx * f,
				I_->f_pingvinon_defolt_y * f);
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

vector <RectangleShape>& Introduction::getSprite ()
{
	return getClass ()->rectsangle_shape_obj;
}

//vector <Pingvinon>&

vector <Pingvinon>& Introduction::getPingvinons ()
{
	return getClass ()->pingvonon_obj;
}

//FloatRect

FloatRect Introduction::getGlobalBounds ()
{
	return getClass ()->rectsangle_shape_obj[0].getGlobalBounds ();
}

//size_t

size_t Introduction::size_sprites = 3;
