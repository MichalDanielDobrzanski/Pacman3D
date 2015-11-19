
class GameBoard {

private:
public:
	static const int DIM_X = 30;
	static const int DIM_Y = 15;

	static const int CENTER_X = DIM_X / 2;
	static const int CENTER_Y = (DIM_Y + 1) / 2;
	static const int CENTER_Z = 0;

	double wallThickness;

	static int initial_map[DIM_Y][DIM_X];
	int coinsCount;
	
	GameBoard();

	void Draw();

	bool consume(int x, int y);
	bool isWall(int x, int y);
	


};