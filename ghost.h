#include <utility>

class Ghost {

private:

public:
	int index;

	bool moving;
	bool frightened;
	bool chase;
	bool scatter;

	int targetX;
	int targetY;

	int scatterX;
	int scatterY;

	double speed;
	double angle;
	double x,y,z;

	Ghost(int x, int y);

	void BasicMove();
	// specific ghost movement
	virtual void Move() {};

	bool WallCheck(int a);
	bool WallStop();

	bool AtTurn();

	bool isAtIntersection();
	void IntersectionDecision();

	double Rotate(double chng);
	std::pair<int,int> NextTile(int angle);

	double GetLeftAngle(double angdir);
	double GetRightAngle(double angdir);
	double TargetPythagoras(double x, double y);

	virtual void Draw();
};
