#ifndef CREATURE_H
#define CREATURE_H

class Creature
{
private:

	void calcCurrentTile(); // calculate current tile
	bool atCenter; // synchronizing boolean. Invoke onTileCenter only once!
	bool isCenterTile();

public:
	
	virtual ~Creature() {};
	Creature(int x, int y, float z);

	float x, y, z;  // wspolrzedne do poruszania sie po planszy
	int tileX;
	int tileY;

	int lives;
	double angle;
	double speed;
	bool moving;

	void Move();
	void Pad();
	void PadToCenter(); // makes creature put in the center of the current tile.

	virtual void onTileChange() {}; // on step for a new tile
	virtual void onTileCenter() {}; // when in tile center

};

#endif