#include <iostream>

using namespace std;

constexpr auto BLUE = 0;
constexpr auto RED = 1;
constexpr auto GREEN = 2;
constexpr auto ORANGE = 3;
constexpr auto WHITE = 4;
constexpr auto YELLOW = 5;

//큐브의 각 면의 색
int color[6] = { BLUE, RED, GREEN, ORANGE, WHITE, YELLOW };

class Cube
{
private:
	//by[color] 면에 인접한 네 이웃 면의 색
	int by[6][4]     = { {5, 1, 4, 3}, {5, 2, 4, 0}, {5,  3, 4, 1}, {5,  0, 4, 2}, {0, 1, 2, 3}, {2,  1, 0, 3} };

	//by[color] 면에 존재하는 네 엣지 블록
	int edge[6][4]   = { {8, 4, 0, 7}, {9, 5, 1, 4}, {10, 6, 2, 5}, {11, 7, 3, 6}, {0, 1, 2, 3}, {10, 9, 8, 11} };

	//by[color] 면에 존재하는 네 코너 블록
	int corner[6][4] = { {4, 0, 3, 7}, {5, 1, 0, 4}, {6,  2, 1, 5}, {7,  3, 2, 6}, {0, 1, 2, 3}, {5,  4, 7, 6} };

public:
	Cube() {}

	//index1 면의 index2번째 이웃면
	int getBy(int index1, int index2) { return this->by[index1][index2]; }

	//index1 면의 index2번째 엣지 블록
	int getEdge(int index1, int index2) { return this->edge[index1][index2]; }

	//index1 면의 index2번째 코너 블록
	int getCorner(int index1, int index2) { return this->corner[index1][index2]; }
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

class Cube cube;
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
		temp = cube.getEdge(target, i);

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
		temp = cube.getCorner(target, i);

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
	//바꾸느라 없어질 리스트의 0번 위치를 미리 저장
	temp = tEdge[0]->getPos();

	//리스트의 3번까지 행한다면 3번의 위치를 다시 변경해야 한다
	for (int i = 0; i < 3; i++)
	{
		//우선 방향이 해당 면을 향하지 않는다면 변경 이후 가리킬 면으로 변경
		if (tEdge[i]->getDir() != target) tEdge[i]->setDir(cube.getBy(target, i + 1));
		//위치를 한 칸 옮긴다
		tEdge[i]->setPos(tEdge[i + 1]->getPos());
	}

	//for문의 행동을 그대로 복사
	if (tEdge[3]->getDir() != target) tEdge[3]->setDir(cube.getBy(target, 0));
	tEdge[3]->setPos(temp);

	//코너 블럭의 위치와 방향을 변경
	//바꾸느라 없어질 리스트의 0번 위치를 미리 저장
	temp = tCorner[0]->getPos();

	//리스트의 3번까지 행한다면 3번의 위치를 다시 변경해야 한다
	for (int i = 0; i < 3; i++)
	{
		//우선 방향이 해당 면을 향하지 않는다면
		if (tCorner[i]->getDir() != target)
		{
			//현재 가리키는 면을 판단하여 다음 면을 가리키게 만든다
			if(tCorner[i]->getDir() == cube.getBy(target, i)) tCorner[i]->setDir(cube.getBy(target, i + 1));
			else tCorner[i]->setDir(cube.getBy(target, (i + 2) % 4));
		}

		//위치를 한 칸 옮긴다
		tCorner[i]->setPos(tCorner[i + 1]->getPos());
	}

	//for문의 행동을 그대로 복사
	if (tCorner[3]->getDir() != target)
	{
		if (tCorner[3]->getDir() == cube.getBy(target, 3)) tCorner[3]->setDir(cube.getBy(target, 0));
		else tCorner[3]->setDir(cube.getBy(target, 1));
	}
	tCorner[3]->setPos(temp);
}

int main()
{
	//
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