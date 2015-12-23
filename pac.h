#include "creature.h"

class Pac : public Creature {

public:
	double z;
	Pac(int x, int y);
	~Pac();

	// abilities:
	bool Consume();

	// visual:
	void Draw();

	// movement:
	void Turn(int v);
	void Pad();
	bool WallCheck();
	void PadAndMove(int a);

	// info:
	void onTileChange() override;
	void onTileCenter() override;

	// next tile prediction:
	int getNextTileX(int dist);
	int getNextTileY(int dist);

};
