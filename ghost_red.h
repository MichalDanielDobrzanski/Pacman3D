#include "ghost.h"

class GhostRed : public Ghost
{

private:

public:

	int targetX;
	int targetY;

	GhostRed(int x,int y);
	~GhostRed();

	void Draw() override;
	void Move() override;

};
