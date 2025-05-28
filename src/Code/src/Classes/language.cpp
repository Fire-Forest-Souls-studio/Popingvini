#include "../../includes/Classes/language.h"

Language::Language (const string& s)
    : s_name (s),

      image_button ("L/button/" + s),

      work (0)
{
}

void Language::addWork (const Work& W)
{
	work.push_back (W);
}
