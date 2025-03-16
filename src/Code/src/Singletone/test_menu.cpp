#include "../../includes/Singletone/test_menu.h"
#include "../../includes/Singletone/works_menu.h"
#include "../../includes/Singletone/window_and_styles.h"
#include "../../includes/Singletone/names.h"
#include "../../includes/Singletone/color_table.h"
#include "../../includes/Singletone/learn_menu.h"
#include "../../includes/Singletone/loading.h"
#include "../../includes/Singletone/pc_mouse.h"

#include <cmath>

TestMenu* TestMenu::class_obj = NULL;

TestMenu::TestMenu () :
		_text_button (0),

		w_add (L"> "),

		i_up (5),
				i_between (4),
				i_left (20),

				f_text_size (5.4),
				f_wight_simbol (WorksMenu::getWidthSimvolBigFont () / WorksMenu::getBigFontScale () * f_text_size),
				f_time (0.0),
				f_score (0.0),

				V2f_image_size (146, 75),

				C_background (ColorTable::c10),
				C_question (ColorTable::c250),
				C_answer_select (ColorTable::c250),
				C_answer_unselect (ColorTable::c150),

				st_question (0),

				u_true (0),
				u_cout (0)
{
	RS_image.setSize (V2f_image_size);
	RS_image_long.setSize (Vector2f (
			WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getFactorY () - V2f_image_size.x,
			V2f_image_size.y
			));
	T_question.setFont (names::F_pixel);
	T_question.setFillColor (C_question);
	T_question.setCharacterSize (f_text_size * WindowAndStyles::getFactorY ());
	T_question.setStyle (Text::Bold);
}

TestMenu* TestMenu::getClass ()
{
	if (class_obj)
		return class_obj;

	class_obj = new TestMenu;
	return class_obj;
}

void TestMenu::destroy ()
{
	TestMenu* TM_ = getClass ();

	TM_->RS_image_long.setSize (Vector2f (
			unsigned (WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getFactorY () - TM_->V2f_image_size.x),
			TM_->V2f_image_size.y
			));

	if (LearnMenu::work and names::game_status == GameStatus::test)
	{
		if (TM_->st_question < LearnMenu::work->test.question.size ())
		{
			TM_->T_question.setString (names::GetStringOfHyphenation (
					LearnMenu::work->test.question[TM_->st_question].w_question,
					(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
							/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
							));
			for (size_t st (0); st < TM_->_text_button.size (); st++)
			{
				TM_->_text_button[st].textSetString (names::GetStringOfHyphenation (
						TM_->w_add + LearnMenu::work->test.question[TM_->st_question].answer[st].w_string,
						(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
								/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
								));
			}
		}
	}
}

void TestMenu::main ()
{
	TestMenu* TM_ = getClass ();

	if (names::game_status == GameStatus::test)
	{
		//нынешний
		if (TM_->st_question < LearnMenu::work->test.question.size ())
		{
			TM_->f_time += names::microsec * names::f_time;
		}

		TM_->RS_image.setScale (WindowAndStyles::getFactorY (), WindowAndStyles::getFactorY ());
		TM_->RS_image.setPosition (
				WorksMenu::getDownPanel ().getGlobalBounds ().left + WorksMenu::getDownPanel ().getGlobalBounds ().width
						- 1 * WindowAndStyles::getFactorY () - TM_->RS_image.getGlobalBounds ().width,
				WorksMenu::getDownPanel ().getGlobalBounds ().top + WorksMenu::getDownPanel ().getGlobalBounds ().height
						- 1 * WindowAndStyles::getFactorY () - TM_->RS_image.getGlobalBounds ().height
						);

		TM_->RS_image_long.setScale (WindowAndStyles::getFactorY (), WindowAndStyles::getFactorY ());
		TM_->RS_image_long.setPosition (
				WorksMenu::getDownPanel ().getPosition ().x,
				WorksMenu::getDownPanel ().getGlobalBounds ().top + WorksMenu::getDownPanel ().getGlobalBounds ().height
						- 1 * WindowAndStyles::getFactorY () - TM_->RS_image.getGlobalBounds ().height
						);

		TM_->T_question.setCharacterSize (TM_->f_text_size * WindowAndStyles::getFactorY ());
		TM_->T_question.setPosition (
				WorksMenu::getDownPanel ().getGlobalBounds ().left + (1 + TM_->i_left) * WindowAndStyles::getFactorY (),
				WorksMenu::getDownPanel ().getGlobalBounds ().top + (1 + TM_->i_up) * WindowAndStyles::getFactorY ()
						);

		for (size_t st (0); st < TM_->_text_button.size (); st++)
		{
			TM_->_text_button[st]._text.setCharacterSize (TM_->f_text_size * WindowAndStyles::getFactorY ());
			if (st == 0)
			{
				TM_->_text_button[st].setPosition (
						TM_->T_question.getPosition ().x,
						TM_->T_question.getPosition ().y + TM_->T_question.getGlobalBounds ().height + TM_->i_up * WindowAndStyles::getFactorY ()
								);
			}
			else
			{
				TM_->_text_button[st].setPosition (
						TM_->_text_button[st - 1]._text.getPosition ().x,
						TM_->_text_button[st - 1]._text.getPosition ().y + TM_->_text_button[st - 1]._text.getGlobalBounds ().height + TM_->i_between * WindowAndStyles::getFactorY ()
								);
			}

			if (TM_->st_question < LearnMenu::work->test.question.size ())
			{
				TM_->_text_button[st].setScale (WindowAndStyles::getFactorY ());
				TM_->_text_button[st].setPosition (TM_->_text_button[st]._text.getPosition ().x, TM_->_text_button[st]._text.getPosition ().y);
			}
		}
		if (TM_->st_question < LearnMenu::work->test.question.size ())
		{
			for (size_t st (0); st < TM_->_text_button.size (); st++)
			{
				if (PC_Mouse::getGlobalBounds ().intersects (TM_->_text_button[st]._text.getGlobalBounds ()))
				{
					TM_->_text_button[st].setStyle (Text::Bold);
					TM_->_text_button[st]._text.setFillColor (TM_->C_answer_select);
				}
				else
				{
					TM_->_text_button[st].setStyle (Text::Regular);
					TM_->_text_button[st]._text.setFillColor (TM_->C_answer_unselect);
				}
			}
		}

		//следующий

		if (TM_->st_question < LearnMenu::work->test.question.size () - 1)
		{
			for (size_t st (0); st < TM_->_text_button.size (); st++)
			{
				if (TM_->_text_button[st].pressed ())
				{
					WorksMenu::getRightTextUpPanel ().setString (to_wstring (unsigned (float (TM_->st_question + 1) / float (LearnMenu::work->test.question.size ()) * 100)) + L"%");

					for (size_t st0 (0);
							st0 < LearnMenu::work->test.question[TM_->st_question].answer.size ();
							st0++)
					{
						TM_->u_cout += LearnMenu::work->test.question[TM_->st_question].answer[st0].cost;
					}
					TM_->u_true += LearnMenu::work->test.question[TM_->st_question].answer[st].cost;
					TM_->st_question++;

					TM_->_text_button.resize (LearnMenu::work->test.question[TM_->st_question].answer.size ());

					TM_->T_question.setString (names::GetStringOfHyphenation (
							LearnMenu::work->test.question[TM_->st_question].w_question,
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
									/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
									));
					for (size_t st (0); st < TM_->_text_button.size (); st++)
					{
						TM_->_text_button[st]._text.setFont (names::F_pixel);
						TM_->_text_button[st].textSetString (names::GetStringOfHyphenation (
								TM_->w_add + LearnMenu::work->test.question[TM_->st_question].answer[st].w_string,
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
										));
						TM_->_text_button[st]._text.setFillColor (TM_->C_answer_unselect);
						TM_->_text_button[st].setSizeByText ();
						TM_->_text_button[st].setFillColor (Color::Transparent);
						TM_->_text_button[st].setString ("TM/button/answer" + to_string (st));
					}

					break;
				}
			}
		}
		else if (TM_->st_question < LearnMenu::work->test.question.size ())
		{
			for (size_t st (0); st < TM_->_text_button.size (); st++)
			{
				if (TM_->_text_button[st].pressed ())
				{
					WorksMenu::getRightTextUpPanel ().setString (L"результаты");

					for (size_t st0 (0);
							st0 < LearnMenu::work->test.question[TM_->st_question].answer.size ();
							st0++)
					{
						TM_->u_cout += LearnMenu::work->test.question[TM_->st_question].answer[st0].cost;
					}
					TM_->u_true += LearnMenu::work->test.question[TM_->st_question].answer[st].cost;
					TM_->st_question++;

					TM_->_text_button.resize (6);

					TM_->T_question.setString (names::GetStringOfHyphenation (
							L"Результаты теста",
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
									/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
									));

					TM_->f_score = float (TM_->u_true) / float (TM_->u_cout) * float (pow (20.0 * float (TM_->u_cout) / TM_->f_time, 0.1)) * 100.0;

					TM_->_text_button[0].textSetString (names::GetStringOfHyphenation (
							L"Пункт: результат сейчас (лучший результат)",
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
									/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
									));
					TM_->_text_button[0]._text.setFillColor (TM_->C_answer_unselect);
					TM_->_text_button[0].setStyle (Text::Italic);

					if (TM_->u_true > unsigned (LearnMenu::work->test.f_best_true * float (TM_->u_cout) / 100.0))
					{
						TM_->_text_button[1].textSetString (names::GetStringOfHyphenation (
								L"Верно отвечено: " + to_wstring (TM_->u_true)
										+ L" (" + to_wstring (unsigned (LearnMenu::work->test.f_best_true * float (TM_->u_cout) / 100.0)) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->_text_button[1]._text.setFillColor (TM_->C_answer_select);
						TM_->_text_button[1].setStyle (Text::Bold);
					}
					else
					{
						TM_->_text_button[1]._text.setFillColor (TM_->C_answer_unselect);
						TM_->_text_button[1].setStyle (Text::Regular);
						TM_->_text_button[1].textSetString (names::GetStringOfHyphenation (
								L"Верно отвечено: " + to_wstring (TM_->u_true)
										+ L" (" + to_wstring (unsigned (LearnMenu::work->test.f_best_true * float (TM_->u_cout) / 100.0)) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
										));
					}

					TM_->_text_button[2].textSetString (names::GetStringOfHyphenation (
							L"Всего заданий: " + to_wstring (TM_->u_cout),
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
									/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
									));
					TM_->_text_button[2]._text.setFillColor (TM_->C_answer_unselect);
					TM_->_text_button[2].setStyle (Text::Italic);

					if (float (TM_->u_true) / float (TM_->u_cout) * 100.0 > LearnMenu::work->test.f_best_true)
					{
						TM_->_text_button[3].textSetString (names::GetStringOfHyphenation (
								L"Верно %: " + to_wstring (float (TM_->u_true) / float (TM_->u_cout) * 100.0)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_true) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->_text_button[3]._text.setFillColor (TM_->C_answer_select);
						TM_->_text_button[3].setStyle (Text::Bold);
					}
					else
					{
						TM_->_text_button[3].textSetString (names::GetStringOfHyphenation (
								L"Верно %: " + to_wstring (float (TM_->u_true) / float (TM_->u_cout) * 100.0)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_true) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
										));
						TM_->_text_button[3]._text.setFillColor (TM_->C_answer_unselect);
						TM_->_text_button[3].setStyle (Text::Regular);
					}

					if (TM_->f_time < LearnMenu::work->test.f_best_time)
					{
						TM_->_text_button[4].textSetString (names::GetStringOfHyphenation (
								L"Время прохождения: " + to_wstring (TM_->f_time)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_time) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->_text_button[4]._text.setFillColor (TM_->C_answer_select);
						TM_->_text_button[4].setStyle (Text::Bold);
					}
					else
					{
						TM_->_text_button[4].textSetString (names::GetStringOfHyphenation (
								L"Время прохождения: " + to_wstring (TM_->f_time)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_time) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
										));
						TM_->_text_button[4]._text.setFillColor (TM_->C_answer_unselect);
						TM_->_text_button[4].setStyle (Text::Regular);
					}

					if (TM_->f_score > LearnMenu::work->test.f_best_score)
					{
						TM_->_text_button[5].textSetString (names::GetStringOfHyphenation (
								L"Результат: " + to_wstring (TM_->f_score)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_score) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->_text_button[5]._text.setFillColor (TM_->C_answer_select);
						TM_->_text_button[5].setStyle (Text::Bold);
					}
					else
					{
						TM_->_text_button[5].textSetString (names::GetStringOfHyphenation (
								L"Результат: " + to_wstring (TM_->f_score)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_score) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
										/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
										));
						TM_->_text_button[5]._text.setFillColor (TM_->C_answer_unselect);
						TM_->_text_button[5].setStyle (Text::Regular);
					}

					for (size_t st (0); st < TM_->_text_button.size (); st++)
					{
						TM_->_text_button[st]._text.setFont (names::F_pixel);
					}

					break;

				}
			}
		}
		else
		{
			if (PC_Mouse::isLeftPressed ())
			{
				if (float (TM_->u_true) / float (TM_->u_cout) * 100.0 > LearnMenu::work->test.f_best_true)
				{
					LearnMenu::work->test.f_best_true = float (TM_->u_true) / float (TM_->u_cout) * 100.0;
				}
				if (TM_->f_time < LearnMenu::work->test.f_best_time or LearnMenu::work->test.f_best_time == 0.0)
				{
					LearnMenu::work->test.f_best_time = TM_->f_time;
				}
				if (TM_->f_score > LearnMenu::work->test.f_best_score)
				{
					LearnMenu::work->test.f_best_score = TM_->f_score;
				}
				names::game_status = GameStatus::works_menu;
				WorksMenu::getMoveBlocks () = 0.0;
				LearnMenu::work->u_try += 1;
				WorksMenu::stringUpdate ();
			}
		}
	}
}

void TestMenu::setZeroQuestion ()
{
	TestMenu* TM_ = getClass ();

	WorksMenu::getDownPanel ().setFillColor (TM_->C_background);
	WorksMenu::getRightTextUpPanel ().setString (L"0%");

	TM_->u_true = 0;
	TM_->f_time = 0.0;
	TM_->f_score = 0.0;
	TM_->st_question = 0;
	TM_->u_cout = 0;

	TM_->_text_button.resize (LearnMenu::work->test.question[TM_->st_question].answer.size ());

	TM_->T_question.setString (names::GetStringOfHyphenation (
			LearnMenu::work->test.question[TM_->st_question].w_question,
			(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
					/ TM_->f_wight_simbol / WindowAndStyles::getFactorY () * 13 / 14
					));
	for (size_t st (0); st < TM_->_text_button.size (); st++)
	{
		TM_->_text_button[st]._text.setFont (names::F_pixel);
		TM_->_text_button[st].textSetString (names::GetStringOfHyphenation (
				TM_->w_add + LearnMenu::work->test.question[TM_->st_question].answer[st].w_string,
				(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->i_left * 2) * WindowAndStyles::getFactorY ())
						/ TM_->f_wight_simbol / WindowAndStyles::getFactorY ()
						));
		TM_->_text_button[st]._text.setFillColor (TM_->C_answer_unselect);
		TM_->_text_button[st]._text.setCharacterSize (TM_->f_text_size * WindowAndStyles::getFactorY ());
		TM_->_text_button[st].setSizeByText ();
		TM_->_text_button[st].setFillColor (Color::Transparent);
		TM_->_text_button[st].setString ("TM/button/answer" + to_string (st));
	}

	destroy ();
}

vector <TextButton>& TestMenu::getButtons ()
{
	return getClass ()->_text_button;
}

RectangleShape TestMenu::getRectangleShapeImage ()
{
	return getClass ()->RS_image;
}
RectangleShape TestMenu::getRectangleShape ()
{
	return getClass ()->RS_image_long;
}

Text TestMenu::getTextQuestion ()
{
	return getClass ()->T_question;
}

void TestMenu::setLanguageTexture (const Texture& T)
{
	TestMenu* TM_ = getClass ();

	TM_->RS_image.setTexture (&T);
	TM_->RS_image_long.setTexture (&T);
	TM_->RS_image_long.setTextureRect (IntRect (0, 0, 1, T.getSize ().y));
}
