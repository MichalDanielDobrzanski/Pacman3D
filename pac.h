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

	// abilities:
	bool Consume();

	// visual:
	void Draw();

	// movement:
	void Move();
	void Turn(int v);
	void Pad();
	bool WallCheck();
	void PadAndMove(int a);

};
