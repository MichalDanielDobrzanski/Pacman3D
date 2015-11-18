class GameBoard {

private:


public:

	static const int DIM_X;
	static const int DIM_Y;
	static const int CENTER_X;
	static const int CENTER_Y;
	static const int CENTER_Z;

	double wallThickness;

	int coinsCount;

	GameBoard();

	void Draw();

	bool consume(int x, int y);
	bool isWall(int x, int y);
	

};