#include "p2Point.h"
#include "p2SString.h"

struct SDL_Texture;
struct _TTF_Font;

struct SDL_Rect
{
	int x;
	int y;
	int w;
	int h;
};

enum UIComponent_TYPE
{
	LABEL,
	BUTTON,
	INPUT
};

class UIComponents
{
public:
	SDL_Rect rect_position;
	SDL_Rect rect_atlas;
	UIComponent_TYPE type;

public:
	UIComponents(int pos_x, int pos_y, UIComponent_TYPE type)
	{
		rect_position.x = pos_x;
		rect_position.y = pos_y;
		this->type = type;
	}

	UIComponents(int pos_x, int pos_y,int pos_w, int pos_h, int atlas_x, int atlas_y, int atlas_w, int atlas_h,UIComponent_TYPE type)
	{
		rect_position.x = pos_x;
		rect_position.y = pos_y;
		rect_position.w = pos_w;
		rect_position.h = pos_h;

		rect_atlas.x = atlas_x;
		rect_atlas.y = atlas_y;
		rect_atlas.w = atlas_w;
		rect_atlas.h = atlas_h;

		this->type = type;
	}

	UIComponents(SDL_Rect position, SDL_Rect atlas, UIComponent_TYPE type) : rect_position(position), rect_atlas(atlas), type(type) { }
};

class UILabel : public UIComponents
{
public:
	p2SString text;
	_TTF_Font*  font;

public:
	UILabel();
	UILabel(int pos_x, int pos_y, const char* text) : UIComponents(pos_x, pos_y, UIComponent_TYPE::LABEL), text(text) {}
};

class UIButton : public UIComponents
{
public:
	bool clicked;
	UILabel title;

public:
	UIButton(int pos_x, int pos_y, int pos_w, int pos_h, int atlas_x, int atlas_y, int atlas_w, int atlas_h, int label_x, int label_y, const char* text_title) : UIComponents(pos_x,pos_y,pos_w,pos_h,atlas_x,atlas_y, atlas_w,atlas_h, UIComponent_TYPE::BUTTON)
	{
		title.rect_position.x = label_x;
		title.rect_position.y = label_y;
		title.text.create(text_title);
	}

	UIButton(SDL_Rect position, SDL_Rect atlas, int label_x, int label_y, const char* text_title) : UIComponents(position, atlas, UIComponent_TYPE::BUTTON)
	{
		title.rect_position.x = label_x;
		title.rect_position.y = label_y;
		title.text.create(text_title);
	}

	void action();
};

class UIInput : public UIComponents
{
public: 
	p2SString input_text;
	UILabel title;

public:
	UIInput(int pos_x, int pos_y, int pos_w, int pos_h, int atlas_x, int atlas_y, int atlas_w, int atlas_h, int label_x, int label_y, const char* text_title) : UIComponents(pos_x, pos_y, pos_w, pos_h, atlas_x, atlas_y, atlas_w, atlas_h, UIComponent_TYPE::INPUT)
	{
		title.rect_position.x = label_x;
		title.rect_position.y = label_y;
		title.text.create(text_title);
	}

	UIInput(SDL_Rect position, SDL_Rect atlas, int label_x, int label_y, const char* text_title) : UIComponents(position, atlas, UIComponent_TYPE::INPUT)
	{
		title.rect_position.x = label_x;
		title.rect_position.y = label_y;
		title.text.create(text_title);
	}

	const char* GetStr();
};