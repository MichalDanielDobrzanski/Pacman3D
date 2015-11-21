#include <utility>
#include "creature.h"

class Ghost : public Creature {

private:

public:
	// general ghost info:
	int index;
	bool frightened;
	bool chase;
	bool scatter;
	Ghost(int x, int y);

	// scattering functionality:
	int scatterTileX;
	int scatterTileY;

	// targeting functionality:
	int targetTileX;
	int targetTileY;
	int TargetPythagoras(int agle); 

	//  visual appearance:
	virtual void Draw(); // unique ghost look

	// map location and inference mechanisms:	
	void onTileChange() override;
	void onTileCenter() override;
	bool WallCheck(int angle);
	

};
