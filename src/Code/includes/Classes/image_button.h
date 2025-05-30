#ifndef CODE_IMAGE_BUTTON_H
#define CODE_IMAGE_BUTTON_H

#include "button.h"

class ImageButton : public Button
{
	private:
		Texture m_texture;

	public:
		using Button::Button;

		void setTexture ();

		Texture& getTexture ();
};

#endif
