#pragma once
#include "Rectangle.h"

enum hiddenItemType
{
	spartanHelmetToCollect,
	coins,
	emptyBlock
};

class blockWithObject : public Rectangle
{
public:
	blockWithObject(const Window &window, float pos_x, float pos_y, int width, int height, const string &picture,
		int hiddenItemType, bool visibility);
	~blockWithObject();

	void drawBlock();
	void updateBlock();
	void bumpUpBlock();
	bool isItemVisible();
	bool isBlockVisible();
	
private:
	hiddenItemType hiddenObject;
	bool bumpUp, bumped, itemVisible, blockVisible;
	int currentAnimationFrame;
	SDL_Rect clip;
};