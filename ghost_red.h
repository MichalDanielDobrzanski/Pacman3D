#include "ghost.h"

class GhostRed : public Ghost
{

public:
	GhostRed(int x,int y);
	~GhostRed();

	void Draw() override; // my unique look
	//void Move() override; // my unique movement

};
