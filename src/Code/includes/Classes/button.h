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
		RectangleShape m_rectangle_shape;

		Text m_text;

		Color m_C_outline;

	public:
		Button ();
		Button (const string& name);

		void setSize (const Vector2f& size);
		void setFillColor (const Color& color);
		void setScale (const float& factor);
		void setString (const string& name);
		void setOutline (const Color& color);

		virtual void setPosition (const float& x, const float& y);

		FloatRect getGlobalBounds ();

		const RectangleShape& getRectangleShape () const;

		const Text& getText () const;

		bool interect () const;
		bool pressed () const;

		const Vector2f getPosition () const;
};

#endif
