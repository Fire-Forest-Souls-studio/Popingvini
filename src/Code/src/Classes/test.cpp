#include "../../includes/Classes/test.h"

Test::Test () :
		f_best_true (0.0),
				f_best_time (0.0),
				f_best_score (0.0),

				question (0)
{
}

Test::Test (const vector <Question>& q) :
		f_best_true (0.0),
				f_best_time (0.0),
				f_best_score (0.0),

				question (q)
{
}
