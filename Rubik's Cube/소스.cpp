#include <iostream>

using namespace std;

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

constexpr auto BLUE = 0;
constexpr auto RED = 1;
constexpr auto GREEN = 2;
constexpr auto ORANGE = 3;
constexpr auto WHITE = 4;
constexpr auto YELLOW = 5;

class three_by_three
{
	class Color
	{
	private:
		int self;
		int by[4];
		int edge[4];
		int corner[4];

		void copy(int target[], int origin[]) { for (int i = 0; i < 4; i++) target[i] = origin[i]; }

	public:
		Color() {}
		Color(int self, int by[], int edge[], int corner[])
		{
			this->self = self;
			this->copy(this->by, by);
			this->copy(this->edge, edge);
			this->copy(this->corner, corner);
		}

		//각 면의 색
		int getSelf() { return this->self; }

		//각 면의 index번째 이웃면
		int getBy(int index) { return this->by[index]; }

		//각 면의 index번째 엣지 블록
		int getEdge(int index) { return this->edge[index]; }

		//각 면의 index번째 코너 블록
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

		for (int i = 0; i < 6; i++) color[i] = Color(i, by[i], edge[i], corner[i]);
	}
	
	Color getColor(int index) { return this->color[index]; }
	edgePiece getEdge(int index) { return this->edge[index]; }
	cornerPiece getCorner(int index) { return this->corner[index]; }

	void CW(int target)
	{
		//변수 선언
		int temp, index = 0;

		int tEdge[4], tCorner[4];

		//회전할 면에 해당되는 엣지 블록 특정
		for (int i = 0; i < 4; i++)
		{
			//면의 네 엣지 블록의 위치를 지정
			temp = this->getColor(target).getEdge(i);

			for (int j = 0; j < 12; j++)
			{
				//해당 위치에 존재하는 엣지 블록을 찾았다면
				if (temp == this->getEdge(j).getPos())
				{
					//리스트에 해당 엣지 블록을 추가
					tEdge[index++] = j;
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
			temp = this->getColor(target).getCorner(i);

			for (int j = 0; j < 8; j++)
			{
				//해당 위치에 존재하는 코너 블록을 찾았다면
				if (temp == this->getCorner(j).getPos())
				{
					//리스트에 해당 코너 블록을 추가
					tCorner[index++] = j;
					break;
				}
			}
			
			if (index == 4) break;
		}

		//엣지 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면 변경 이후 가리킬 면(i + 1번째)으로 변경
			if (this->getEdge(tEdge[i]).getDir() != target) this->edge[tEdge[i]].setDir(this->getColor(target).getBy((i + 1) % 4));
			//위치를 한 칸 옮긴다
			this->edge[tEdge[i]].setPos(this->getColor(target).getEdge((i + 1) % 4));
		}

		//코너 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//현재 가리키는 면을 판단하여 변경 이후 가리킬 면(i + 1번째 혹은 그 + 1번째)으로 변경
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i)) this->corner[tCorner[i]].setDir(this->getColor(target).getBy((i + 1) % 4));
				else this->corner[tCorner[i]].setDir(this->getColor(target).getBy((i + 2) % 4));
			}
			//위치를 한 칸 옮긴다
			this->corner[tCorner[i]].setPos(this->getColor(target).getCorner((i + 1) % 4));
			bool k = false;
		}
	}
	void ACW(int target)
	{
		//변수 선언
		int temp, index = 0;

		int tEdge[4], tCorner[4];

		//회전할 면에 해당되는 엣지 블록 특정
		for (int i = 0; i < 4; i++)
		{
			//면의 네 엣지 블록의 위치를 지정
			temp = this->getColor(target).getEdge(i);

			for (int j = 0; j < 12; j++)
			{
				//해당 위치에 존재하는 엣지 블록을 찾았다면
				if (temp == getEdge(j).getPos())
				{
					//리스트에 해당 엣지 블록을 추가
					tEdge[index++] = j;
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
			temp = this->getColor(target).getCorner(i);

			for (int j = 0; j < 8; j++)
			{
				//해당 위치에 존재하는 코너 블록을 찾았다면
				if (temp == this->getCorner(j).getPos())
				{
					//리스트에 해당 코너 블록을 추가
					tCorner[index++] = j;
					break;
				}
			}

			if (index == 4) break;
		}

		//엣지 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면 변경 이후 가리킬 면(i - 1번째)으로 변경 : ((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
			if (this->getEdge(tEdge[i]).getDir() != target) this->edge[tEdge[i]].setDir(this->getColor(target).getBy((i + 3) % 4));
			//위치를 한 칸 옮긴다
			this->edge[tEdge[i]].setPos(this->getColor(target).getEdge((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
		}

		//코너 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//우선 방향이 해당 면을 향하지 않는다면
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//현재 가리키는 면을 판단하여 변경 이후 가리킬 면(i - 1번째 혹은 그 + 1번째)으로 변경 : ((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i)) this->corner[tCorner[i]].setDir(this->getColor(target).getBy((i + 3) % 4));
				else this->corner[tCorner[i]].setDir(this->getColor(target).getBy(i));
			}
			//위치를 한 칸 옮긴다
			this->corner[tCorner[i]].setPos(this->getColor(target).getCorner((i + 3) % 4)); //((i + 3) % 4) 는 ((i - 1) + 4) % 4의 변형
		}
	}

	void visualize()
	{
		//print[면의 색][행][렬]
		//기준은 맨 상하단의 주석
		int print[6][3][3];

		char col[6][10] = { "파", "빨", "초", "주", "흰", "노" };

		//각 엣지의 포지션을 배열화
		int pEdge[12];

		//각 코너의 포지션을 배열화
		int pCorner[8];

		//0~3, 8~11번 엣지의 색을 대입할 때 쓸 변수
		//흰색 면 기준. 노란색 면의 경우 0번과 2번을 교대해 준다
		//temp[색][0 : 행/1 : 열]
		int eTemp[4][2] = { {0, 1}, {1, 2}, {2, 1}, {1, 0} };

		//각 코너의 색을 대입할 때 쓸 변수
		//흰색 면 기준. 노란색 면의 경우 0번과 1번, 2번과 3번을 교대해 준다
		//temp[색][0 : 행/1 : 열]
		int cTemp[4][2] = { {0, 2}, {2, 2}, {2, 0}, {0, 0} };

		//각 엣지의 포지션을 인덱스 순으로 삽입
		for (int i = 0; i < 12; i++) pEdge[(int)this->getEdge(i).getPos()] = i;

		//각 코너의 포지션을 인덱스 순으로 삽입
		for (int i = 0; i < 8; i++) pCorner[(int)this->getCorner(i).getPos()] = i;

		//각 면의 코너 블록의 색을 삽입
		for (int i = 0; i < 6; i++) print[i][1][1] = i;

		//엣지 블록들은 0~3, 4~7, 8~11로 묶을 수 있다
		//코너 블록들은 0~3, 4~7로 묶을 수 있다
		for (int i = 0; i < 4; i++)
		{
			//0~3번 엣지에 대해 방향이 흰색 면을 향한다면
			if (this->getEdge(pEdge[i]).getDir() == WHITE)
			{
				//각 코너의 top(=side[0], dir)은 흰색 면의 정해진 위치에 해당
				print[4][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getTop();
				//각 코너의 front(=side[1])은 각 옆면의 3행 2열에 해당
				print[i][2][1] = this->getEdge(pEdge[i]).getFront();
			}

			//그렇지 않을 경우 서로가 반대의 경우에 해당
			else
			{
				print[4][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getFront();
				print[i][2][1] = this->getEdge(pEdge[i]).getTop();
			}

			//eTemp[0] = {0, 1}이고 eTemp[2] = {2, 1}이니 서로의 앞 부분만 바꿔준다
			swap(eTemp[0][0], eTemp[2][0]);


			//4~7번째 엣지에 대해 방향이 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면을 향한다면
			if (this->getEdge(pEdge[i + 4]).getDir() == (int)this->getColor(i).getSelf())
			{
				//각 코너의 top(=side[0], dir)은 작은 쪽 면의 2행 3열에 해당
				print[i][1][2] = this->getEdge(pEdge[i + 4]).getTop();
				//각 코너의 front(=side[1])은 큰 면의 2행 1열에 해당
				print[(i + 1) % 4][1][0] = this->getEdge(pEdge[i + 4]).getFront();
			}

			//그렇지 않을 경우 서로가 반대의 경우에 해당
			else
			{
				print[(i + 1) % 4][1][0] = this->getEdge(pEdge[i + 4]).getTop();
				print[i][1][2] = this->getEdge(pEdge[i + 4]).getFront();
			}


			//8~11번 엣지에 대해 방향이 노란색 면을 향한다면
			if (this->getEdge(pEdge[i + 8]).getDir() == YELLOW)
			{
				//각 코너의 top(=side[0], dir)은 노란 면의 정해진 위치에 해당
				print[5][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getTop();
				//각 코너의 front(=side[1])은 각 옆면의 1행 2열에 해당
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getFront();
			}

			//그렇지 않을 경우 서로가 반대의 경우에 해당
			else
			{
				print[5][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getFront();
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getTop();
			}

			//다음 루프에서 쓰기 위해 eTemp[0]과 eTemp[2]의 앞 부분을 다시 바꿔준다
			swap(eTemp[0][0], eTemp[2][0]);


			//0~3번 코너에 대해 방향이 흰색 면을 향한다면
			if (this->getCorner(pCorner[i]).getDir() == WHITE)
			{
				//각 코너의 top(=side[0], dir)은 흰색 면의 정해진 위치에 해당
				print[4][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getTop();
				//각 코너의 left(=side[1])은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 1열에 해당
				print[(i + 1) % 4][2][0] = this->getCorner(pCorner[i]).getLeft();
				//각 코너의 right(=side[2])는 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 3열에 해당
				print[i][2][2] = this->getCorner(pCorner[i]).getRight();
			}

			//그렇지 않고 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i]).getDir() == (i + 1))
			{
				//각 코너의 top(=side[0], dir)은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 1열에 해당
				print[(i + 1) % 4][2][0] = this->getCorner(pCorner[i]).getTop();
				//각 코너의 left(=side[1])은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 3열에 해당
				print[i][2][2] = this->getCorner(pCorner[i]).getLeft();
				//각 코너의 right(=side[2])는 흰색 면의 정해진 위치에 해당
				print[4][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getRight();
			}

			//그렇지 않고 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i]).getDir() == i)
			{
				//각 코너의 top(=side[0], dir)은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 3열에 해당
				print[i][2][2] = this->getCorner(pCorner[i]).getTop();
				//각 코너의 left(=side[1])은 흰색 면의 정해진 위치에 해당
				print[4][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getLeft();
				//각 코너의 right(=side[2])는 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 1열에 해당
				print[(i + 1) % 4][2][0] = this->getCorner(pCorner[i]).getRight();
			}

			//cTemp[0] = {0, 2}이고 cTemp[1] = {2, 2}이니 서로의 앞 부분만 바꿔준다
			swap(cTemp[0][0], cTemp[1][0]);
			//cTemp[2] = {2, 0}이고 cTemp[3] = {0, 0}이니 서로의 앞 부분만 바꿔준다
			swap(cTemp[2][0], cTemp[3][0]);

			//4~7번 코너에 대해 방향이 노란색 면을 향한다면
			if (this->getCorner(pCorner[i + 4]).getDir() == YELLOW)
			{
				//각 코너의 top(=side[0], dir)은 노란색 면의 정해진 위치에 해당
				print[5][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getTop();
				//각 코너의 left(=side[1])은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 1열에 해당
				print[(i + 1) % 4][0][0] = this->getCorner(pCorner[i + 4]).getRight();
				//각 코너의 right(=side[2])는 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 3열에 해당
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getLeft();
			}

			//그렇지 않고 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i + 4]).getDir() == (i + 1))
			{
				//각 코너의 top(=side[0], dir)은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 3열에 해당
				print[(i + 1) % 4][0][0] = this->getCorner(pCorner[i + 4]).getTop();
				//각 코너의 left(=side[1])은 노란색 면의 정해진 위치에 해당
				print[5][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getLeft();
				//각 코너의 right(=side[2])는 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 1열에 해당
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getRight();
			}
			
			//그렇지 않고 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i + 4]).getDir() == i)
			{
				//각 코너의 top(=side[0], dir)은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 1열에 해당
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getTop();
				//각 코너의 left(=side[1])은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 3열에 해당
				print[(i + 1) % 4][0][0] = this->getCorner(pCorner[i + 4]).getLeft();
				//각 코너의 right(=side[2])는 노란색 면의 정해진 위치에 해당
				print[5][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getRight();
			}
			
			//다음 루프에서 쓰기 위해 cTemp[0]과 cTemp[1]의 앞 부분, cTemp[2]과 cTemp[3]의 앞 부분을 다시 바꿔준다
			swap(cTemp[0][0], cTemp[1][0]);
			swap(cTemp[2][0], cTemp[3][0]);
		}

		
		//노란색 면을 맨 상하단 주석에 맞게 출력
		for (int i = 0; i < 3; i++) cout << "　　　　" << col[print[5][i][0]] << col[print[5][i][1]] << col[print[5][i][2]] << endl;
		cout << endl;

		//옆쪽 면들을 맨 상하단 주석에 맞게 출력
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << col[print[(j + 3) % 4][i][0]] << col[print[(j + 3) % 4][i][1]] << col[print[(j + 3) % 4][i][2]] << "　";
			}

			cout << endl;
		}

		cout << endl;

		//흰색 면을 맨 상하단 주석에 맞게 출력
		for (int i = 0; i < 3; i++) cout << "　　　　" << col[print[4][i][0]] << col[print[4][i][1]] << col[print[4][i][2]] << endl;
		cout << endl << endl;
		
	}
};

int main()
{
	class three_by_three cube;

	//구상중

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