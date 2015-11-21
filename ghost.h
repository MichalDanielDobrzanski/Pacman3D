#include <utility>
#include "creature.h"

class Ghost : public Creature {

private:

public:
	int index;

	bool frightened;
	bool chase;
	bool scatter;

	int targetTileX;
	int targetTileY;

	int scatterX;
	int scatterY;

	Ghost(int x, int y);

	virtual void Move(); // this ghost movement will be replaced by the specific one.
	virtual void Draw(); // unique ghost look

	bool WallCheck(int a);
	bool WallStop();

	bool AtTurn();
	
	int inter;
	bool isAtIntersection();
	void IntersectionDecision();

	double Rotate(double chng);
	std::pair<int,int> NextTile(int angle);

	double GetLeftAngle(double angdir);
	double GetRightAngle(double angdir);
	double TargetPythagoras(int x, int y);

	
};
