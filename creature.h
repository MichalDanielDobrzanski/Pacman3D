// klasa abstrakcyjna do dziedziczenia
class Creature {

private:

public:
	int lives;
	double x,y; // wspolrzedne do poruszania sie po planszy
	double angle;
	
	Creature() {};	
	~Creature() {};

	virtual void Move() =0;
	virtual void Draw() =0;

};
