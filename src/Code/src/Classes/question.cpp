#include "../../includes/Classes/question.h"

Question::Question () :
		answer (0),

		w_question (L"")
{
}

Question::Question (const wstring& w, const vector <Answer>& a) :
		answer (a),

		w_question (w)
{
}
