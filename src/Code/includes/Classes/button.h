#ifndef CODE_BUTTON_H_
#define CODE_BUTTON_H_

#include <./SFML/Window.hpp>
#include <./SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Button
{

	protected:

		RectangleShape _rectangle_shape;

		Text text_obj;

		Color C_outline;

	public:

		Button ();
		Button (const string&);

		void setSize (const Vector2f&);
		void setFillColor (const Color&);
		void setScale (const float&);
		void setString (const string&);
		void setOutline (const Color&);

		virtual void setPosition (const float&, const float&);

		FloatRect getGlobalBounds ();

		const RectangleShape& getRectangleShape () const;

		const Text& getText () const;

		bool interect () const;
		bool pressed () const;

		const Vector2f getPosition () const;
};

#endif
