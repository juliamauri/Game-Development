#include "UIComponents.h"
#include "p2List.h"

class UIManager
{
private:
	p2List<UIComponents*> components;
	SDL_Texture* atlas;

public:
	void Start();
	void Update();
	void CleanUp();

	UIComponents* addUIComponent();
};