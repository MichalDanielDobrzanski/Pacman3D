
class Ghost {

private:

public:
	int index;

	bool moving;
	bool frightened;
	bool chase;
	bool scatter;

	int scatterX;
	int scatterY;

	double speed;
	double angle;
	double x,y,z;
	Ghost(int x, int y);

	void BasicMove();
	virtual void Move() {};
	virtual void Draw();
};
