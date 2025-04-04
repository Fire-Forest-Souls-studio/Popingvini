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
		m_text_button (0),

		m_w_ADD (L"> "),

		m_i_UP (5),
				m_i_BETWEEN (4),
				m_i_LEFT (20),

				m_f_TEXT_SIZE (5.4),
				m_f_WIGHT_SIMBOL (WorksMenu::getWidthSimvolBigFont () / WorksMenu::getBigFontScale () * m_f_TEXT_SIZE),
				m_f_time (0.0),
				m_f_score (0.0),

				m_V2f_IMAGE_SIZE (146, 75),

				m_C_BACKGROUND (ColorTable::c10),
				m_C_QUESTION (ColorTable::c250),
				m_C_ANSWER_SELECT (ColorTable::c250),
				m_C_ANSWER_UNSELECT (ColorTable::c150),

				m_st_question (0),

				m_u_true (0),
				m_u_cout (0)
{
	m_RS_image.setSize (m_V2f_IMAGE_SIZE);
	m_RS_image_long.setSize (Vector2f (
			WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getFactorY () - m_V2f_IMAGE_SIZE.x,
			m_V2f_IMAGE_SIZE.y
			));
	m_T_question.setFont (names::F_pixel);
	m_T_question.setFillColor (m_C_QUESTION);
	m_T_question.setCharacterSize (m_f_TEXT_SIZE * WindowAndStyles::getFactorY ());
	m_T_question.setStyle (Text::Bold);
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

	TM_->m_RS_image_long.setSize (Vector2f (
			unsigned (WindowAndStyles::getGlobalBounds ().width / WindowAndStyles::getFactorY () - TM_->m_V2f_IMAGE_SIZE.x),
			TM_->m_V2f_IMAGE_SIZE.y
			));

	if (LearnMenu::work and names::game_status == GameStatus::test)
	{
		if (TM_->m_st_question < LearnMenu::work->test.question.size ())
		{
			TM_->m_T_question.setString (names::GetStringOfHyphenation (
					LearnMenu::work->test.question[TM_->m_st_question].w_question,
					(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
							/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
							));
			for (size_t st (0); st < TM_->m_text_button.size (); st++)
			{
				TM_->m_text_button[st].textSetString (names::GetStringOfHyphenation (
						TM_->m_w_ADD + LearnMenu::work->test.question[TM_->m_st_question].answer[st].w_string,
						(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
								/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
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
		if (TM_->m_st_question < LearnMenu::work->test.question.size ())
		{
			TM_->m_f_time += names::microsec * names::f_time;
		}

		TM_->m_RS_image.setScale (WindowAndStyles::getFactorY (), WindowAndStyles::getFactorY ());
		TM_->m_RS_image.setPosition (
				WorksMenu::getDownPanel ().getGlobalBounds ().left + WorksMenu::getDownPanel ().getGlobalBounds ().width
						- 1 * WindowAndStyles::getFactorY () - TM_->m_RS_image.getGlobalBounds ().width,
				WorksMenu::getDownPanel ().getGlobalBounds ().top + WorksMenu::getDownPanel ().getGlobalBounds ().height
						- 1 * WindowAndStyles::getFactorY () - TM_->m_RS_image.getGlobalBounds ().height
						);

		TM_->m_RS_image_long.setScale (WindowAndStyles::getFactorY (), WindowAndStyles::getFactorY ());
		TM_->m_RS_image_long.setPosition (
				WorksMenu::getDownPanel ().getPosition ().x,
				WorksMenu::getDownPanel ().getGlobalBounds ().top + WorksMenu::getDownPanel ().getGlobalBounds ().height
						- 1 * WindowAndStyles::getFactorY () - TM_->m_RS_image.getGlobalBounds ().height
						);

		TM_->m_T_question.setCharacterSize (TM_->m_f_TEXT_SIZE * WindowAndStyles::getFactorY ());
		TM_->m_T_question.setPosition (
				WorksMenu::getDownPanel ().getGlobalBounds ().left + (1 + TM_->m_i_LEFT) * WindowAndStyles::getFactorY (),
				WorksMenu::getDownPanel ().getGlobalBounds ().top + (1 + TM_->m_i_UP) * WindowAndStyles::getFactorY ()
						);

		for (size_t st (0); st < TM_->m_text_button.size (); st++)
		{
			TM_->m_text_button[st]._text.setCharacterSize (TM_->m_f_TEXT_SIZE * WindowAndStyles::getFactorY ());
			if (st == 0)
			{
				TM_->m_text_button[st].setPosition (
						TM_->m_T_question.getPosition ().x,
						TM_->m_T_question.getPosition ().y + TM_->m_T_question.getGlobalBounds ().height + TM_->m_i_UP * WindowAndStyles::getFactorY ()
								);
			}
			else
			{
				TM_->m_text_button[st].setPosition (
						TM_->m_text_button[st - 1]._text.getPosition ().x,
						TM_->m_text_button[st - 1]._text.getPosition ().y + TM_->m_text_button[st - 1]._text.getGlobalBounds ().height + TM_->m_i_BETWEEN * WindowAndStyles::getFactorY ()
								);
			}

			if (TM_->m_st_question < LearnMenu::work->test.question.size ())
			{
				TM_->m_text_button[st].setScale (WindowAndStyles::getFactorY ());
				TM_->m_text_button[st].setPosition (TM_->m_text_button[st]._text.getPosition ().x, TM_->m_text_button[st]._text.getPosition ().y);
			}
		}
		if (TM_->m_st_question < LearnMenu::work->test.question.size ())
		{
			for (size_t st (0); st < TM_->m_text_button.size (); st++)
			{
				if (PC_Mouse::getGlobalBounds ().intersects (TM_->m_text_button[st]._text.getGlobalBounds ()))
				{
					TM_->m_text_button[st].setStyle (Text::Bold);
					TM_->m_text_button[st]._text.setFillColor (TM_->m_C_ANSWER_SELECT);
				}
				else
				{
					TM_->m_text_button[st].setStyle (Text::Regular);
					TM_->m_text_button[st]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
				}
			}
		}

		//следующий

		if (TM_->m_st_question < LearnMenu::work->test.question.size () - 1)
		{
			for (size_t st (0); st < TM_->m_text_button.size (); st++)
			{
				if (TM_->m_text_button[st].pressed ())
				{
					WorksMenu::getRightTextUpPanel ().setString (to_wstring (unsigned (float (TM_->m_st_question + 1) / float (LearnMenu::work->test.question.size ()) * 100)) + L"%");

					for (size_t st0 (0);
							st0 < LearnMenu::work->test.question[TM_->m_st_question].answer.size ();
							st0++)
					{
						TM_->m_u_cout += LearnMenu::work->test.question[TM_->m_st_question].answer[st0].cost;
					}
					TM_->m_u_true += LearnMenu::work->test.question[TM_->m_st_question].answer[st].cost;
					TM_->m_st_question++;

					TM_->m_text_button.resize (LearnMenu::work->test.question[TM_->m_st_question].answer.size ());

					TM_->m_T_question.setString (names::GetStringOfHyphenation (
							LearnMenu::work->test.question[TM_->m_st_question].w_question,
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
									/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
									));
					for (size_t st (0); st < TM_->m_text_button.size (); st++)
					{
						TM_->m_text_button[st]._text.setFont (names::F_pixel);
						TM_->m_text_button[st].textSetString (names::GetStringOfHyphenation (
								TM_->m_w_ADD + LearnMenu::work->test.question[TM_->m_st_question].answer[st].w_string,
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
										));
						TM_->m_text_button[st]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
						TM_->m_text_button[st].setSizeByText ();
						TM_->m_text_button[st].setFillColor (Color::Transparent);
						TM_->m_text_button[st].setString ("TM/button/answer" + to_string (st));
					}

					break;
				}
			}
		}
		else if (TM_->m_st_question < LearnMenu::work->test.question.size ())
		{
			for (size_t st (0); st < TM_->m_text_button.size (); st++)
			{
				if (TM_->m_text_button[st].pressed ())
				{
					WorksMenu::getRightTextUpPanel ().setString (L"результаты");

					for (size_t st0 (0);
							st0 < LearnMenu::work->test.question[TM_->m_st_question].answer.size ();
							st0++)
					{
						TM_->m_u_cout += LearnMenu::work->test.question[TM_->m_st_question].answer[st0].cost;
					}
					TM_->m_u_true += LearnMenu::work->test.question[TM_->m_st_question].answer[st].cost;
					TM_->m_st_question++;

					TM_->m_text_button.resize (6);

					TM_->m_T_question.setString (names::GetStringOfHyphenation (
							L"Результаты теста",
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
									/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
									));

					TM_->m_f_score = float (TM_->m_u_true) / float (TM_->m_u_cout) * float (pow (20.0 * float (TM_->m_u_cout) / TM_->m_f_time, 0.1)) * 100.0;

					TM_->m_text_button[0].textSetString (names::GetStringOfHyphenation (
							L"Пункт: результат сейчас (лучший результат)",
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
									/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
									));
					TM_->m_text_button[0]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
					TM_->m_text_button[0].setStyle (Text::Italic);

					if (TM_->m_u_true > unsigned (LearnMenu::work->test.f_best_true * float (TM_->m_u_cout) / 100.0))
					{
						TM_->m_text_button[1].textSetString (names::GetStringOfHyphenation (
								L"Верно отвечено: " + to_wstring (TM_->m_u_true)
										+ L" (" + to_wstring (unsigned (LearnMenu::work->test.f_best_true * float (TM_->m_u_cout) / 100.0)) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->m_text_button[1]._text.setFillColor (TM_->m_C_ANSWER_SELECT);
						TM_->m_text_button[1].setStyle (Text::Bold);
					}
					else
					{
						TM_->m_text_button[1]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
						TM_->m_text_button[1].setStyle (Text::Regular);
						TM_->m_text_button[1].textSetString (names::GetStringOfHyphenation (
								L"Верно отвечено: " + to_wstring (TM_->m_u_true)
										+ L" (" + to_wstring (unsigned (LearnMenu::work->test.f_best_true * float (TM_->m_u_cout) / 100.0)) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
										));
					}

					TM_->m_text_button[2].textSetString (names::GetStringOfHyphenation (
							L"Всего заданий: " + to_wstring (TM_->m_u_cout),
							(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
									/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
									));
					TM_->m_text_button[2]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
					TM_->m_text_button[2].setStyle (Text::Italic);

					if (float (TM_->m_u_true) / float (TM_->m_u_cout) * 100.0 > LearnMenu::work->test.f_best_true)
					{
						TM_->m_text_button[3].textSetString (names::GetStringOfHyphenation (
								L"Верно %: " + to_wstring (float (TM_->m_u_true) / float (TM_->m_u_cout) * 100.0)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_true) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->m_text_button[3]._text.setFillColor (TM_->m_C_ANSWER_SELECT);
						TM_->m_text_button[3].setStyle (Text::Bold);
					}
					else
					{
						TM_->m_text_button[3].textSetString (names::GetStringOfHyphenation (
								L"Верно %: " + to_wstring (float (TM_->m_u_true) / float (TM_->m_u_cout) * 100.0)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_true) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
										));
						TM_->m_text_button[3]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
						TM_->m_text_button[3].setStyle (Text::Regular);
					}

					if (TM_->m_f_time < LearnMenu::work->test.f_best_time)
					{
						TM_->m_text_button[4].textSetString (names::GetStringOfHyphenation (
								L"Время прохождения: " + to_wstring (TM_->m_f_time)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_time) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->m_text_button[4]._text.setFillColor (TM_->m_C_ANSWER_SELECT);
						TM_->m_text_button[4].setStyle (Text::Bold);
					}
					else
					{
						TM_->m_text_button[4].textSetString (names::GetStringOfHyphenation (
								L"Время прохождения: " + to_wstring (TM_->m_f_time)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_time) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
										));
						TM_->m_text_button[4]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
						TM_->m_text_button[4].setStyle (Text::Regular);
					}

					if (TM_->m_f_score > LearnMenu::work->test.f_best_score)
					{
						TM_->m_text_button[5].textSetString (names::GetStringOfHyphenation (
								L"Результат: " + to_wstring (TM_->m_f_score)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_score) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
										));
						TM_->m_text_button[5]._text.setFillColor (TM_->m_C_ANSWER_SELECT);
						TM_->m_text_button[5].setStyle (Text::Bold);
					}
					else
					{
						TM_->m_text_button[5].textSetString (names::GetStringOfHyphenation (
								L"Результат: " + to_wstring (TM_->m_f_score)
										+ L" (" + to_wstring (LearnMenu::work->test.f_best_score) + L")",
								(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
										/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
										));
						TM_->m_text_button[5]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
						TM_->m_text_button[5].setStyle (Text::Regular);
					}

					for (size_t st (0); st < TM_->m_text_button.size (); st++)
					{
						TM_->m_text_button[st]._text.setFont (names::F_pixel);
					}

					break;

				}
			}
		}
		else
		{
			if (PC_Mouse::isLeftPressed ())
			{
				if (float (TM_->m_u_true) / float (TM_->m_u_cout) * 100.0 > LearnMenu::work->test.f_best_true)
				{
					LearnMenu::work->test.f_best_true = float (TM_->m_u_true) / float (TM_->m_u_cout) * 100.0;
				}
				if (TM_->m_f_time < LearnMenu::work->test.f_best_time or LearnMenu::work->test.f_best_time == 0.0)
				{
					LearnMenu::work->test.f_best_time = TM_->m_f_time;
				}
				if (TM_->m_f_score > LearnMenu::work->test.f_best_score)
				{
					LearnMenu::work->test.f_best_score = TM_->m_f_score;
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

	WorksMenu::getDownPanel ().setFillColor (TM_->m_C_BACKGROUND);
	WorksMenu::getRightTextUpPanel ().setString (L"0%");

	TM_->m_u_true = 0;
	TM_->m_f_time = 0.0;
	TM_->m_f_score = 0.0;
	TM_->m_st_question = 0;
	TM_->m_u_cout = 0;

	TM_->m_text_button.resize (LearnMenu::work->test.question[TM_->m_st_question].answer.size ());

	TM_->m_T_question.setString (names::GetStringOfHyphenation (
			LearnMenu::work->test.question[TM_->m_st_question].w_question,
			(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
					/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY () * 13 / 14
					));
	for (size_t st (0); st < TM_->m_text_button.size (); st++)
	{
		TM_->m_text_button[st]._text.setFont (names::F_pixel);
		TM_->m_text_button[st].textSetString (names::GetStringOfHyphenation (
				TM_->m_w_ADD + LearnMenu::work->test.question[TM_->m_st_question].answer[st].w_string,
				(WorksMenu::getDownPanel ().getGlobalBounds ().width - (2 + TM_->m_i_LEFT * 2) * WindowAndStyles::getFactorY ())
						/ TM_->m_f_WIGHT_SIMBOL / WindowAndStyles::getFactorY ()
						));
		TM_->m_text_button[st]._text.setFillColor (TM_->m_C_ANSWER_UNSELECT);
		TM_->m_text_button[st]._text.setCharacterSize (TM_->m_f_TEXT_SIZE * WindowAndStyles::getFactorY ());
		TM_->m_text_button[st].setSizeByText ();
		TM_->m_text_button[st].setFillColor (Color::Transparent);
		TM_->m_text_button[st].setString ("TM/button/answer" + to_string (st));
	}

	destroy ();
}

vector <TextButton>& TestMenu::getButtons ()
{
	return getClass ()->m_text_button;
}

RectangleShape TestMenu::getRectangleShapeImage ()
{
	return getClass ()->m_RS_image;
}
RectangleShape TestMenu::getRectangleShape ()
{
	return getClass ()->m_RS_image_long;
}

Text TestMenu::getTextQuestion ()
{
	return getClass ()->m_T_question;
}

void TestMenu::setLanguageTexture (const Texture& T)
{
	TestMenu* TM_ = getClass ();

	TM_->m_RS_image.setTexture (&T);
	TM_->m_RS_image_long.setTexture (&T);
	TM_->m_RS_image_long.setTextureRect (IntRect (0, 0, 1, T.getSize ().y));
}
