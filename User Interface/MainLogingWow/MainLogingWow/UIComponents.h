#include "p2Point.h"
#include "p2SString.h"

struct SDL_Texture;

class UIComponents
{
public:
	iPoint position;

public:
	UIComponents(int x, int y)
	{
		position.x = x;
		position.y = y;
	}
};

class UILabel : public UIComponents
{
public:
	p2SString title;

public:
	UILabel();
	UILabel(int x, int y, const char* text) : UIComponents(x, y), title(text) {};
};

class UIBox : public UIComponents
{
public:
	uint widht;
	uint height;
	SDL_Texture* img_box;

public:
	UIBox(int x, int y, uint widht, uint height, SDL_Texture* texture) : UIComponents(x, y), widht(widht), height(height), img_box(texture) {};
};

class UIButton : public UIBox
{
public:
	bool clicked;
	UILabel title;

public:
	UIButton(int x, int y, uint widht, uint height, SDL_Texture* texture, int label_x, int label_y, const char* text_title) : UIBox(x, y, widht, height, texture)
	{
		title.position.x = label_x;
		title.position.y = label_y;
		title.title.create(text_title);
	};

	void action();
};

class UIInput : public UIBox
{
public: 
	p2SString input_text;
	UILabel title;

public:
	UIInput(int x, int y, uint widht, uint height, SDL_Texture* texture, int label_x, int label_y, const char* text_title) : UIBox(x, y, widht, height, texture)
	{
		title.position.x = label_x;
		title.position.y = label_y;
		title.title.create(text_title);
	};

	const char* GetStr();
};