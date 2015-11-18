#include "creature.h"

class Pac : Creature {

private:
	double speed;
public:
	int lives;
	bool moving;
	double angle;
	double x,y,z; // wspolrzedne do poruszania sie po planszy
	Pac(int x, int y);
	~Pac();

	void Move();
	void Draw();
	void Pad();
	void Turn(int v);

};
