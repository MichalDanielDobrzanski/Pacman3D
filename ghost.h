#include "creature.h"

class Ghost : Creature {

private:

public:
	bool frightened;
	double x,y,z;
	Ghost();

	void Move(void);
	void Draw(void);
};
