#include "ghost.h"

class GhostRed : public Ghost
{

private:

public:
	GhostRed(int x,int y);
	~GhostRed();

	void Draw() override; // my unique look
	void Move() override; // my unique movement

	void onTileChange() override;

};
