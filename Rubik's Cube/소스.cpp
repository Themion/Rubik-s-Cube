#include <iostream>

using namespace std;

constexpr auto BLUE = 0;
constexpr auto RED = 1;
constexpr auto GREEN = 2;
constexpr auto ORANGE = 3;
constexpr auto WHITE = 4;
constexpr auto YELLOW = 5;

/*
class three_by_three
{
	class Color
	{
	private:
		int by[4];
		int edge[4];
		int corner[4];

		void copy(int target[], int origin[]) { for (int i = 0; i < 4; i++) target[i] = origin[i]; }

	public:
		Color() {}

		Color(int by[], int edge[], int corner[])
		{
			this->copy(this->by, by);
			this->copy(this->edge, edge);
			this->copy(this->corner, corner);
		}

		//index1 면의 index2번째 이웃면
		int getBy(int index) { return this->by[index]; }

		//index1 면의 index2번째 엣지 블록
		int getEdge(int index) { return this->edge[index]; }

		//index1 면의 index2번째 코너 블록
		int getCorner(int index) { return this->corner[index]; }
	};
	class edgePiece
	{
	private:
		//엣지 블록의 위치
		int pos;
		//side[0]이 있는 면
		int dir;
		//엣지 블록의 두 면
		//0 : 윗면, 1 : 앞면
		int *side = new int[2];
	public:
		edgePiece() {}
		edgePiece(int pos, int top, int front)
		{
			this->pos = pos;
			this->dir = top;
			this->side[0] = top;
			this->side[1] = front;
		}
		void setPos(int pos) { this->pos = pos; }
		void setDir(int dir) { this->dir = dir; }
		int getPos() { return this->pos; }
		int getDir() { return this->dir; }
		int getTop() { return this->side[0]; }
		int getFront() { return this->side[1]; }
	};
	class cornerPiece
	{
	private:
		//코너 블록의 위치
		int pos;
		//side[0]이 있는 면
		int dir;
		//코너 블록의 세 면
		//0 : 윗면, 1 : 왼면, 2 : 오른면
		int *side = new int[3];
	public:
		cornerPiece() {}
		cornerPiece(int pos, int top, int left, int right)
		{
			this->pos = pos;
			this->dir = top;
			this->side[0] = top;
			this->side[1] = left;
			this->side[2] = right;
		}
		void setPos(int pos) { this->pos = pos; }
		void setDir(int dir) { this->dir = dir; }

		int getPos() { return this->pos; }
		int getDir() { return this->dir; }
		int getTop() { return this->side[0]; }
		int getLeft() { return this->side[1]; }
		int getRight() { return this->side[2]; }
	};

private:
	class Color color[6];
	class edgePiece edge[12] =
	{
		edgePiece(0, WHITE,  BLUE), edgePiece(1, WHITE,  RED),   edgePiece(2,  WHITE,  GREEN),  edgePiece(3,  WHITE,  ORANGE),
		edgePiece(4, BLUE,   RED),  edgePiece(5, RED,    GREEN), edgePiece(6,  GREEN,  ORANGE), edgePiece(7,  ORANGE, BLUE),
		edgePiece(8, YELLOW, BLUE), edgePiece(9, YELLOW, RED),   edgePiece(10, YELLOW, GREEN),  edgePiece(11, YELLOW, ORANGE)
	};
	class cornerPiece corner[8] =
	{
		cornerPiece(0, WHITE,  RED,  BLUE), cornerPiece(1, WHITE,  GREEN, RED),   cornerPiece(2, WHITE,  ORANGE, GREEN),  cornerPiece(3, WHITE,  BLUE,   ORANGE),
		cornerPiece(4, YELLOW, BLUE, RED),  cornerPiece(5, YELLOW, RED,   GREEN), cornerPiece(6, YELLOW, GREEN,  ORANGE), cornerPiece(7, YELLOW, ORANGE, BLUE)
	};

public:
	three_by_three()
	{
		//by[color] 면에 인접한 네 이웃 면의 색
		int by[6][4] = { {5, 1, 4, 3}, {5, 2, 4, 0}, {5,  3, 4, 1}, {5,  0, 4, 2}, {0, 1, 2, 3}, {2,  1, 0, 3} };
		//by[color] 면에 존재하는 네 엣지 블록
		int edge[6][4] = { {8, 4, 0, 7}, {9, 5, 1, 4}, {10, 6, 2, 5}, {11, 7, 3, 6}, {0, 1, 2, 3}, {10, 9, 8, 11} };
		//by[color] 면에 존재하는 네 코너 블록
		int corner[6][4] = { {4, 0, 3, 7}, {5, 1, 0, 4}, {6,  2, 1, 5}, {7,  3, 2, 6}, {0, 1, 2, 3}, {5,  4, 7, 6} };

		for (int i = 0; i < 6; i++) color[i] = Color(by[i], edge[i], corner[i]);
	}
	
	void CW(int target)
	{
		//변수 선언
		int temp, index = 0;
		class edgePiece **tEdge = new edgePiece*[4];
		class cornerPiece **tCorner = new cornerPiece*[4];


		//회전할 면에 해당되는 엣지 블록 특정
		for (int i = 0; i < 4; i++)
		{
			//면의 네 엣지 블록의 위치를 지정
			temp = color[target].getEdge(i);
			for (int j = 0; j < 12; j++)
			{
				//해당 위치에 존재하는 엣지 블록을 찾았다면
				if (temp == edge[j].getPos())
				{
					//리스트에 해당 엣지 블록을 추가
					tEdge[index++] = &edge[j];
					break;
				}
			}
			if (index == 4) break;
		}


		//회전할 면에 해당되는 코너 블록 확정
		index = 0;
		for (int i = 0; i < 4; i++)
		{
			//면의 네 코너 블록의 위치를 지정
			temp = color[target].getCorner(i);
			for (int j = 0; j < 8; j++)
			{
				//해당 위치에 존재하는 코너 블록을 찾았다면
				if (temp == corner[j].getPos())
				{
					//리스트에 해당 코너 블록을 추가
					tCorner[index++] = &corner[j];
					break;
				}
			}
			if (index == 4) break;
		}


		//엣지 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면 변경 이후 가리킬 면(i + 1번째)으로 변경
			if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 1) % 4));
			//위치를 한 칸 옮긴다
			tEdge[i]->setPos(color[target].getEdge((i + 1) % 4));
		}


		//코너 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면
			if (tCorner[i]->getDir() != target)
			{
				//현재 가리키는 면을 판단하여 변경 이후 가리킬 면(i + 1번째 혹은 그 + 1번째)으로 변경
				if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 1) % 4));
				else tCorner[i]->setDir(color[target].getBy((i + 2) % 4));
			}
			//위치를 한 칸 옮긴다
			tCorner[i]->setPos(color[target].getCorner((i + 1) % 4));
		}
	}
	void ACW(int target)
	{
		//변수 선언
		int temp, index = 0;
		class edgePiece **tEdge = new edgePiece*[4];
		class cornerPiece **tCorner = new cornerPiece*[4];

		//회전할 면에 해당되는 엣지 블록 특정
		for (int i = 0; i < 4; i++)
		{
			//면의 네 엣지 블록의 위치를 지정
			temp = color[target].getEdge(i);
			for (int j = 0; j < 12; j++)
			{
				//해당 위치에 존재하는 엣지 블록을 찾았다면
				if (temp == edge[j].getPos())
				{
					//리스트에 해당 엣지 블록을 추가
					tEdge[index++] = &edge[j];
					break;
				}
			}
			if (index == 4) break;
		}

		//회전할 면에 해당되는 코너 블록 확정
		index = 0;
		for (int i = 0; i < 4; i++)
		{
			//면의 네 코너 블록의 위치를 지정
			temp = color[target].getCorner(i);
			for (int j = 0; j < 8; j++)
			{
				//해당 위치에 존재하는 코너 블록을 찾았다면
				if (temp == corner[j].getPos())
				{
					//리스트에 해당 코너 블록을 추가
					tCorner[index++] = &corner[j];
					break;
				}
			}
			if (index == 4) break;
		}


		//엣지 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면 변경 이후 가리킬 면(i + 1번째)으로 변경
			if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
			//위치를 한 칸 옮긴다
			tEdge[i]->setPos(color[target].getEdge((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
		}


		//코너 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//우선 방향이 해당 면을 향하지 않는다면
			if (tCorner[i]->getDir() != target)
			{
				//현재 가리키는 면을 판단하여 변경 이후 가리킬 면(i - 1번째 혹은 그 + 1번째)으로 변경
				if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
				else tCorner[i]->setDir(color[target].getBy(i));
			}
			//위치를 한 칸 옮긴다
			tCorner[i]->setPos(color[target].getCorner((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
		}

		for (int i = 0; i < 4; i++)
		{
			cout << tEdge[i]->getPos() << ' ';
		}

		cout << endl;

		for (int i = 0; i < 4; i++)
		{
			cout << tEdge[i]->getDir() << ' ';
		}

		cout << endl;

		for (int i = 0; i < 4; i++)
		{
			cout << tCorner[i]->getPos() << ' ';
		}

		cout << endl;

		for (int i = 0; i < 4; i++)
		{
			cout << tCorner[i]->getDir() << ' ';
		}

		cout << endl;
	}
};
*/

class Color
{
private:
	int by[4];
	int edge[4];
	int corner[4];

	void copy(int target[], int origin[]) { for (int i = 0; i < 4; i++) target[i] = origin[i]; }
		
public:
	Color() {}

	Color(int by[], int edge[], int corner[])
	{
		this->copy(this->by, by);
		this->copy(this->edge, edge);
		this->copy(this->corner, corner);
	}

	//index1 면의 index2번째 이웃면
	int getBy(int index) { return this->by[index]; }

	//index1 면의 index2번째 엣지 블록
	int getEdge(int index) { return this->edge[index]; }

	//index1 면의 index2번째 코너 블록
	int getCorner(int index) { return this->corner[index]; }
};
class edgePiece
{
private:
	//엣지 블록의 위치
	int pos;
	//side[0]이 있는 면
	int dir;
	//엣지 블록의 두 면
	//0 : 윗면, 1 : 앞면
	int *side = new int[2];
public:
	edgePiece() {}
	edgePiece(int pos, int top, int front)
	{
		this->pos = pos;
		this->dir = top;
		this->side[0] = top;
		this->side[1] = front;
	}
	void setPos(int pos) { this->pos = pos; }
	void setDir(int dir) { this->dir = dir; }
	int getPos() { return this->pos; }
	int getDir() { return this->dir; }
	int getTop() { return this->side[0]; }
	int getFront() { return this->side[1]; }
};
class cornerPiece
{
private:
	//코너 블록의 위치
	int pos;
	//side[0]이 있는 면
	int dir;
	//코너 블록의 세 면
	//0 : 윗면, 1 : 왼면, 2 : 오른면
	int *side = new int[3];
public:
	cornerPiece() {}
	cornerPiece(int pos, int top, int left, int right)
	{
		this->pos = pos;
		this->dir = top;
		this->side[0] = top;
		this->side[1] = left;
		this->side[2] = right;
	}
	void setPos(int pos) { this->pos = pos; }
	void setDir(int dir) { this->dir = dir; }

	int getPos() { return this->pos; }
	int getDir() { return this->dir; }
	int getTop() { return this->side[0]; }
	int getLeft() { return this->side[1]; }
	int getRight() { return this->side[2]; }
};

class Color color[6];
class edgePiece edge[12] =
{
	edgePiece(0, WHITE,  BLUE), edgePiece(1, WHITE,  RED),   edgePiece(2,  WHITE,  GREEN),  edgePiece(3,  WHITE,  ORANGE),
	edgePiece(4, BLUE,   RED),  edgePiece(5, RED,    GREEN), edgePiece(6,  GREEN,  ORANGE), edgePiece(7,  ORANGE, BLUE),
	edgePiece(8, YELLOW, BLUE), edgePiece(9, YELLOW, RED),   edgePiece(10, YELLOW, GREEN),  edgePiece(11, YELLOW, ORANGE)
};
class cornerPiece corner[8] =
{
	cornerPiece(0, WHITE,  RED,  BLUE), cornerPiece(1, WHITE,  GREEN, RED),   cornerPiece(2, WHITE,  ORANGE, GREEN),  cornerPiece(3, WHITE,  BLUE,   ORANGE),
	cornerPiece(4, YELLOW, BLUE, RED),  cornerPiece(5, YELLOW, RED,   GREEN), cornerPiece(6, YELLOW, GREEN,  ORANGE), cornerPiece(7, YELLOW, ORANGE, BLUE)
};

void init(Color *color)
{
	//by[color] 면에 인접한 네 이웃 면의 색
	int by[6][4] = { {5, 1, 4, 3}, {5, 2, 4, 0}, {5,  3, 4, 1}, {5,  0, 4, 2}, {0, 1, 2, 3}, {2,  1, 0, 3} };
	//by[color] 면에 존재하는 네 엣지 블록
	int edge[6][4] = { {8, 4, 0, 7}, {9, 5, 1, 4}, {10, 6, 2, 5}, {11, 7, 3, 6}, {0, 1, 2, 3}, {10, 9, 8, 11} };
	//by[color] 면에 존재하는 네 코너 블록
	int corner[6][4] = { {4, 0, 3, 7}, {5, 1, 0, 4}, {6,  2, 1, 5}, {7,  3, 2, 6}, {0, 1, 2, 3}, {5,  4, 7, 6} };

	for (int i = 0; i < 6; i++) color[i] = Color(by[i], edge[i], corner[i]);
}

void CW(int target)
{
	//변수 선언
	int temp, index = 0;
	class edgePiece **tEdge = new edgePiece*[4];
	class cornerPiece **tCorner = new cornerPiece*[4];


	//회전할 면에 해당되는 엣지 블록 특정
	for (int i = 0; i < 4; i++)
	{
		//면의 네 엣지 블록의 위치를 지정
		temp = color[target].getEdge(i);
		for (int j = 0; j < 12; j++)
		{
			//해당 위치에 존재하는 엣지 블록을 찾았다면
			if (temp == edge[j].getPos())
			{
				//리스트에 해당 엣지 블록을 추가
				tEdge[index++] = &edge[j];
				break;
			}
		}
		if (index == 4) break;
	}


	//회전할 면에 해당되는 코너 블록 확정
	index = 0;
	for (int i = 0; i < 4; i++)
	{
		//면의 네 코너 블록의 위치를 지정
		temp = color[target].getCorner(i);
		for (int j = 0; j < 8; j++)
		{
			//해당 위치에 존재하는 코너 블록을 찾았다면
			if (temp == corner[j].getPos())
			{
				//리스트에 해당 코너 블록을 추가
				tCorner[index++] = &corner[j];
				break;
			}
		}
		if (index == 4) break;
	}


	//엣지 블럭의 위치와 방향을 변경
	for (int i = 0; i < 4; i++)
	{
		//방향이 해당 면을 향하지 않는다면 변경 이후 가리킬 면(i + 1번째)으로 변경
		if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 1) % 4));
		//위치를 한 칸 옮긴다
		tEdge[i]->setPos(color[target].getEdge((i + 1) % 4));
	}


	//코너 블럭의 위치와 방향을 변경
	for (int i = 0; i < 4; i++)
	{
		//방향이 해당 면을 향하지 않는다면
		if (tCorner[i]->getDir() != target)
		{
			//현재 가리키는 면을 판단하여 변경 이후 가리킬 면(i + 1번째 혹은 그 + 1번째)으로 변경
			if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 1) % 4));
			else tCorner[i]->setDir(color[target].getBy((i + 2) % 4));
		}
		//위치를 한 칸 옮긴다
		tCorner[i]->setPos(color[target].getCorner((i + 1) % 4));
	}
}
void ACW(int target)
{
	//변수 선언
	int temp, index = 0;
	class edgePiece **tEdge = new edgePiece*[4];
	class cornerPiece **tCorner = new cornerPiece*[4];

	//회전할 면에 해당되는 엣지 블록 특정
	for (int i = 0; i < 4; i++)
	{
		//면의 네 엣지 블록의 위치를 지정
		temp = color[target].getEdge(i);
		for (int j = 0; j < 12; j++)
		{
			//해당 위치에 존재하는 엣지 블록을 찾았다면
			if (temp == edge[j].getPos())
			{
				//리스트에 해당 엣지 블록을 추가
				tEdge[index++] = &edge[j];
				break;
			}
		}
		if (index == 4) break;
	}

	//회전할 면에 해당되는 코너 블록 확정
	index = 0;
	for (int i = 0; i < 4; i++)
	{
		//면의 네 코너 블록의 위치를 지정
		temp = color[target].getCorner(i);
		for (int j = 0; j < 8; j++)
		{
			//해당 위치에 존재하는 코너 블록을 찾았다면
			if (temp == corner[j].getPos())
			{
				//리스트에 해당 코너 블록을 추가
				tCorner[index++] = &corner[j];
				break;
			}
		}
		if (index == 4) break;
	}


	//엣지 블럭의 위치와 방향을 변경
	for (int i = 0; i < 4; i++)
	{
		//방향이 해당 면을 향하지 않는다면 변경 이후 가리킬 면(i + 1번째)으로 변경
		if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
		//위치를 한 칸 옮긴다
		tEdge[i]->setPos(color[target].getEdge((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
	}


	//코너 블럭의 위치와 방향을 변경
	for (int i = 0; i < 4; i++)
	{
		//우선 방향이 해당 면을 향하지 않는다면
		if (tCorner[i]->getDir() != target)
		{
			//현재 가리키는 면을 판단하여 변경 이후 가리킬 면(i - 1번째 혹은 그 + 1번째)으로 변경
			if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
			else tCorner[i]->setDir(color[target].getBy(i));
		}
		//위치를 한 칸 옮긴다
		tCorner[i]->setPos(color[target].getCorner((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
	}

	for (int i = 0; i < 4; i++)
	{
		cout << tEdge[i]->getPos() << ' ';
	}

	cout << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << tEdge[i]->getDir() << ' ';
	}

	cout << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << tCorner[i]->getPos() << ' ';
	}

	cout << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << tCorner[i]->getDir() << ' ';
	}

	cout << endl;
}

int main()
{
	init(color);
	ACW(BLUE);
	int i;
	cin >> i;
}

/*
　　　　노노노
　　　　노노노
　　　　노노노
　11　ㅇ　08　ㅁ　09　ㅂ　10　ㅅ
주주주　파파파　빨빨빨　초초초
주주주07파파파04빨빨빨05초초초06
주주주　파파파　빨빨빨　초초초
　03　ㄹ　00　ㄱ　01　ㄴ　02　ㄷ
　　　　흰흰흰
　　　　흰흰흰
　　　　흰흰흰
*/