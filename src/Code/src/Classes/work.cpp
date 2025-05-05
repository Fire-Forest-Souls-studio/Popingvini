#include "../../includes/Classes/work.h"

Work::Work ()
    : u_try (0)
{
}

Work::Work (const wstring& w0, const wstring& w1, const wstring& w2, const wstring& w3)
    : w_name (w0),
      w_content (w1),
      w_type (w2),

      u_try (0),

      learn (w3)
{
}

Work::Work (const wstring& w0, const wstring& w1, const wstring& w2, const wstring& w3, const Test& t)
    : w_name (w0),
      w_content (w1),
      w_type (w2),

      u_try (0),

      test (t),

      learn (w3)
{
}
