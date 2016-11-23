#include "Entity.h"
#include "UIComponents.h"
#include "p2List.h"

class UIManager : public Entity
{
private:
	p2List<UIComponents*> components;

public:
	void Update();
	void draw();

	UILabel* addLabel();
	UIButton* addButton();
	UIInput* addInput();
};