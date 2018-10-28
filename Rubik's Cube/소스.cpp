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
		int side[2];

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
		int side[3];

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
	//현재 바라보고 있는 큐브의 면
	//밑면과 윗면은 고려하지 않는다
	int cubeFront = 0;

	//다 맞춰진 상태의 큐브(참고용)
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

	void setFront(int front) { this->cubeFront = front; }

	int getFront() { return this->cubeFront; }
	int getRight() { return this->getColor(this->getFront()).getBy(1); }
	int getLeft()  { return this->getColor(this->getFront()).getBy(3); }

	Color getColor(int index) { return this->color[index]; }
	edgePiece getEdge(int index) { return this->edge[index]; }
	cornerPiece getCorner(int index) { return this->corner[index]; }

	int if_edgeIn(int tEdge, Color tColor)
	{
		//tColor의 모든 엣지에 대해 존재한다면 1을 출력
		for (int i = 0; i < 4; i++) if (tEdge == tColor.getEdge(i)) return 1;

		//for문을 벗어났을 때 찾지 못한다면 0을 출력
		return 0;
	}
	int if_cornerIn(int tCorner, Color tColor)
	{
		//tColor의 모든 엣지에 대해 존재한다면 1을 출력
		for (int i = 0; i < 4; i++) if (tCorner == tColor.getCorner(i)) return 1;

		//for문을 벗어났을 때 찾지 못한다면 0을 출력
		return 0;
	}

	int find_edge_by_pos(int pos)
	{
		for (int i = 0; i < 12; i++) if (this->getEdge(i).getPos() == pos) return i;
	}
	int find_corner_by_pos(int pos)
	{
		for (int i = 0; i < 8; i++) if (this->getCorner(i).getPos() == pos) return i;
	}

	void CW(int target)
	{
		//변수 선언
		int temp, index = 0;

		//움직일 네 엣지와 코너
		int tEdge[4], tCorner[4];

		//회전할 면에 해당되는 엣지 블록 특정
		for (int i = 0; i < 4; i++)
		{
			//회전할 면의 엣지를 움직일 엣지로 설정
			tEdge[i] = find_edge_by_pos(this->getColor(target).getEdge(i));
		}
		//회전할 면에 해당되는 코너 블록 확정
		for (int i = 0; i < 4; i++)
		{
			//회전할 면의 코너를 움직일 코너로 설정
			tCorner[i] = find_corner_by_pos(this->getColor(target).getCorner(i));
		}

		//엣지 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면
			if (this->getEdge(tEdge[i]).getDir() != target)
			{
				//엣지 블럭의 방향을 옮겨준다
				this->edge[tEdge[i]].setDir( this->getColor(target).getBy((i + 1) % 4) );
			}

			//위치를 한 칸 옮긴다
			this->edge[tEdge[i]].setPos( this->getColor(target).getEdge((i + 1) % 4) );
		}

		//코너 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//만일 i번째 코너가 i번째 이웃면을 가리킨다면
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i))
				{
					//가리키는 면을 i + 1번째 이웃면으로 변경
					this->corner[tCorner[i]].setDir( this->getColor(target).getBy((i + 1) % 4) );
				}

				//그렇지 않다면 i + 2번째 이웃면으로 변경
				else this->corner[tCorner[i]].setDir( this->getColor(target).getBy((i + 2) % 4) );
			}
			//위치를 한 칸 옮긴다
			this->corner[tCorner[i]].setPos( this->getColor(target).getCorner((i + 1) % 4) );
		}
	}
	void ACW(int target)
	{
		//변수 선언
		int temp, index = 0;

		//움직일 네 엣지와 코너
		int tEdge[4], tCorner[4];

		//회전할 면에 해당되는 엣지 블록 특정
		for (int i = 0; i < 4; i++)
		{
			//회전할 면의 엣지를 움직일 엣지로 설정
			tEdge[i] = find_edge_by_pos(this->getColor(target).getEdge(i));
		}
		//회전할 면에 해당되는 코너 블록 확정
		for (int i = 0; i < 4; i++)
		{
			//회전할 면의 코너를 움직일 코너로 설정
			tCorner[i] = find_corner_by_pos(this->getColor(target).getCorner(i));
		}

		//엣지 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면
			if (this->getEdge(tEdge[i]).getDir() != target)
			{
				//엣지 블럭의 방향을 옮겨준다
				this->edge[tEdge[i]].setDir( this->getColor(target).getBy((i + 3) % 4) );
			}

			//위치를 한 칸 옮긴다
			this->edge[tEdge[i]].setPos( this->getColor(target).getEdge((i + 3) % 4) );
		}

		//코너 블럭의 위치와 방향을 변경
		for (int i = 0; i < 4; i++)
		{
			//방향이 해당 면을 향하지 않는다면
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//만일 i번째 코너가 i번째 이웃면을 가리킨다면
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i))
				{
					//가리키는 면을 i + 1번째 이웃면으로 변경
					this->corner[tCorner[i]].setDir( this->getColor(target).getBy((i + 3) % 4) );
				}

				//그렇지 않다면 i번째 이웃면으로 변경
				else this->corner[tCorner[i]].setDir( this->getColor(target).getBy(i) );
			}
			//위치를 한 칸 옮긴다
			this->corner[tCorner[i]].setPos( this->getColor(target).getCorner((i + 3) % 4) );
		}
	}

	void L()
	{
		CW(this->getColor(this->getFront()).getBy(3));
	}
	void Lp()
	{
		ACW(this->getColor(this->getFront()).getBy(3));
	}
	void L2()
	{
		L(); L();
	}

	void R()
	{
		CW(this->getColor(this->getFront()).getBy(1));
	}
	void Rp()
	{
		ACW(this->getColor(this->getFront()).getBy(1));
	}
	void R2()
	{
		R(); R();
	}

	void F()
	{
		CW(this->getFront());
	}
	void Fp()
	{
		ACW(this->getFront());
	}
	void F2()
	{
		F(); F();
	}

	void B()
	{
		//모든 색의 값에서 front의 색을 뺀 것
		int k = 15 - this->getFront();

		for (int i = 0; i < 4; i++) k -= this->getColor(this->getFront()).getBy(i);

		CW(this->getColor(k).getSelf());
	}
	void Bp()
	{
		//모든 색의 값에서 front의 색을 뺀 것
		int k = 15 - this->getFront();

		for (int i = 0; i < 4; i++) k -= this->getColor(this->getFront()).getBy(i);

		ACW(this->getColor(k).getSelf());
	}
	void B2()
	{
		B(); B();
	}

	void U()
	{
		CW(this->getColor(this->getFront()).getBy(0));
	}
	void Up()
	{
		ACW(this->getColor(this->getFront()).getBy(0));
	}
	void U2()
	{
		U(); U();
	}

	void D()
	{
		CW(this->getColor(this->getFront()).getBy(2));
	}
	void Dp()
	{
		ACW(this->getColor(this->getFront()).getBy(2));
	}
	void D2()
	{
		D(); D();
	}

	//수정필요
	void show()
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
				print[WHITE][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getTop();
				//각 코너의 front(=side[1])은 각 옆면의 3행 2열에 해당
				print[i][2][1] = this->getEdge(pEdge[i]).getFront();
			}

			//그렇지 않을 경우 서로가 반대의 경우에 해당
			else
			{
				print[WHITE][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getFront();
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
				print[this->getColor(i).getBy(1)][1][0] = this->getEdge(pEdge[i + 4]).getFront();
			}

			//그렇지 않을 경우 서로가 반대의 경우에 해당
			else
			{
				print[this->getColor(i).getBy(1)][1][0] = this->getEdge(pEdge[i + 4]).getTop();
				print[i][1][2] = this->getEdge(pEdge[i + 4]).getFront();
			}


			//8~11번 엣지에 대해 방향이 노란색 면을 향한다면
			if (this->getEdge(pEdge[i + 8]).getDir() == YELLOW)
			{
				//각 코너의 top(=side[0], dir)은 노란 면의 정해진 위치에 해당
				print[YELLOW][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getTop();
				//각 코너의 front(=side[1])은 각 옆면의 1행 2열에 해당
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getFront();
			}

			//그렇지 않을 경우 서로가 반대의 경우에 해당
			else
			{
				print[YELLOW][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getFront();
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getTop();
			}

			//다음 루프에서 쓰기 위해 eTemp[0]과 eTemp[2]의 앞 부분을 다시 바꿔준다
			swap(eTemp[0][0], eTemp[2][0]);


			//0~3번 코너에 대해 방향이 흰색 면을 향한다면
			if (this->getCorner(pCorner[i]).getDir() == WHITE)
			{
				//각 코너의 top(=side[0], dir)은 흰색 면의 정해진 위치에 해당
				print[WHITE][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getTop();
				//각 코너의 left(=side[1])은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 1열에 해당
				print[this->getColor(i).getBy(1)][2][0] = this->getCorner(pCorner[i]).getLeft();
				//각 코너의 right(=side[2])는 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 3열에 해당
				print[i][2][2] = this->getCorner(pCorner[i]).getRight();
			}

			//그렇지 않고 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i]).getDir() == (i + 1) % 4)
			{
				//각 코너의 top(=side[0], dir)은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 1열에 해당
				print[this->getColor(i).getBy(1)][2][0] = this->getCorner(pCorner[i]).getTop();
				//각 코너의 left(=side[1])은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 3열에 해당
				print[i][2][2] = this->getCorner(pCorner[i]).getLeft();
				//각 코너의 right(=side[2])는 흰색 면의 정해진 위치에 해당
				print[WHITE][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getRight();
			}

			//그렇지 않고 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i]).getDir() == i)
			{
				//각 코너의 top(=side[0], dir)은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 3열에 해당
				print[i][2][2] = this->getCorner(pCorner[i]).getTop();
				//각 코너의 left(=side[1])은 흰색 면의 정해진 위치에 해당
				print[WHITE][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getLeft();
				//각 코너의 right(=side[2])는 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 1열에 해당
				print[this->getColor(i).getBy(1)][2][0] = this->getCorner(pCorner[i]).getRight();
			}

			//cTemp[0] = {0, 2}이고 cTemp[1] = {2, 2}이니 서로의 앞 부분만 바꿔준다
			swap(cTemp[0][0], cTemp[1][0]);
			//cTemp[2] = {2, 0}이고 cTemp[3] = {0, 0}이니 서로의 앞 부분만 바꿔준다
			swap(cTemp[2][0], cTemp[3][0]);

			//4~7번 코너에 대해 방향이 노란색 면을 향한다면
			if (this->getCorner(pCorner[i + 4]).getDir() == YELLOW)
			{
				//각 코너의 top(=side[0], dir)은 노란색 면의 정해진 위치에 해당
				print[YELLOW][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getTop();
				//각 코너의 left(=side[1])은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 1열에 해당
				print[this->getColor(i).getBy(1)][0][0] = this->getCorner(pCorner[i + 4]).getRight();
				//각 코너의 right(=side[2])는 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 3열에 해당
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getLeft();
			}

			//그렇지 않고 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i + 4]).getDir() == (i + 1) % 4)
			{
				//각 코너의 top(=side[0], dir)은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 3열에 해당
				print[this->getColor(i).getBy(1)][0][0] = this->getCorner(pCorner[i + 4]).getTop();
				//각 코너의 left(=side[1])은 노란색 면의 정해진 위치에 해당
				print[YELLOW][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getLeft();
				//각 코너의 right(=side[2])는 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 1열에 해당
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getRight();
			}

			//그렇지 않고 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면을 향한다면
			else if (this->getCorner(pCorner[i + 4]).getDir() == i)
			{
				//각 코너의 top(=side[0], dir)은 더 작은 쪽(단 ORANGE-BLUE에서는 더 큰 쪽) 면의 3행 1열에 해당
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getTop();
				//각 코너의 left(=side[1])은 더 큰 쪽(단 ORANGE-BLUE에서는 더 작은 쪽) 면의 3행 3열에 해당
				print[this->getColor(i).getBy(1)][0][0] = this->getCorner(pCorner[i + 4]).getLeft();
				//각 코너의 right(=side[2])는 노란색 면의 정해진 위치에 해당
				print[YELLOW][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getRight();
			}

			//다음 루프에서 쓰기 위해 cTemp[0]과 cTemp[1]의 앞 부분, cTemp[2]과 cTemp[3]의 앞 부분을 다시 바꿔준다
			swap(cTemp[0][0], cTemp[1][0]);
			swap(cTemp[2][0], cTemp[3][0]);
		}

		//노란색 면을 맨 상하단 주석에 맞게 출력
		for (int i = 0; i < 3; i++) cout << "　　　　" << col[print[YELLOW][i][0]] << col[print[YELLOW][i][1]] << col[print[YELLOW][i][2]] << endl;
		cout << endl;

		//옆쪽 면들을 맨 상하단 주석에 맞게 출력
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << col[print[this->getColor(j).getBy(3)][i][0]]
					<< col[print[this->getColor(j).getBy(3)][i][1]]
					<< col[print[this->getColor(j).getBy(3)][i][2]] << "　";
			}

			cout << endl;
		}

		cout << endl;

		//흰색 면을 맨 상하단 주석에 맞게 출력
		for (int i = 0; i < 3; i++) cout << "　　　　" << col[print[WHITE][i][0]] << col[print[WHITE][i][1]] << col[print[WHITE][i][2]] << endl;
		cout << endl << endl;
	}

	void shuffle()
	{
		U(); F(); Dp(); R();
		Dp(); L(); Dp(); Rp();
		Up(); Fp(); Up(); R();
		D(); R(); Dp(); Lp();
		D(); B(); Dp(); L();
		B(); Lp(); Up(); B();
		U();
	}

	//1층 크로스
	void basic_step1()
	{
		//0~3번 엣지를 제자리에 위치시킨다 (크로스)
		for (int i = 0; i < 4; i++)
		{
			//i면을 제외한 모든 면에서 엣지를 발견 시 i면의 0번 위치로 엣지를 이동
			for (int j = 0; j < 4; j++)
			{
				//j가 i일 때, 즉 확인할 면이 i면일 때는 건너뜀
				if (i == j) continue;

				//만일 j 면에 i번째 엣지를 발견했다면
				if (if_edgeIn( this->getEdge(i).getPos(), this->getColor(j) ))
				{
					this->setFront(j);

					//0번 위치일 경우
					//이 경우 해당 면은 아직 엣지가 제자리에 돌아오지 않음
					if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(0))
					{
						//엣지가 해당하는 면의 0번 위치로 갈 때까지 윗면을 회전
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) 
							this->U();
					}

					//j면의 1번 위치일 경우
					//이 경우 해당 면은 엣지가 제자리에 돌아왔을 수 있음
					else if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(1))
					{
						//0번 위치로 뽑아낸 뒤
						this->Fp();

						//엣지가 해당하는 면의 0번 위치로 갈 때까지 윗면을 회전
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) 
							this->U();

						//만일의 경우를 위해 면을 원상복귀
						this->F();
					}

					//j면의 2번 위치일 경우
					//이 경우 해당 면은 아직 엣지가 제자리에 돌아오지 않음
					else if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(2))
					{
						//0번 위치로 뽑아낸 뒤
						this->F2();

						//엣지가 해당하는 면의 0번 위치로 갈 때까지 윗면을 회전
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) 
							this->U();
					}

					break;
				}
			}

			this->setFront(i);

			//각 엣지의 방향이 윗면을 가리키고 있을 때
			if (this->getEdge(i).getDir() != this->getColor(this->getFront()).getSelf())
			{
				//면을 n번 회전시켜 엣지를 올바른 위치에 놓는다
				while (this->getEdge(i).getPos() != this->getColor(this->getFront()).getEdge(2))
					this->F();
			}
			//각 엣지의 방향이 앞면을 가리키고 있을 때
			else
			{
				//면을 n번 회전시켜 크로스 공식을 사용할 수 있는 위치에 둔다
				while (this->getEdge(i).getPos() != this->getColor(this->getFront()).getEdge(0))
					this->F();

				//U' R' F R
				this->Up(); this->Rp(); this->F(); this->R();
			}
		}

		//마지막으로 큐브의 방향을 초기화한다
		this->setFront(BLUE);
	}
	//1층 코너
	void basic_step2()
	{
		//코너가 제자리에 있을 때 continue시킨다
		bool cont;

		//각 코너를 제자리에 위치시킨다
		for (int i = 0; i < 4; i++)
		{
			cont = false;

			//우선 각 코너가 1층에 끼어있는지 확인
			for (int j = 0; j < 4; j++)
			{
				//만약 코너가 잘못된 1층 위치에 끼어있거나
				//방향이 잘못된 상태로 끼어있을 경우
				if (this->getCorner(i).getPos() == this->getColor(j).getCorner(1))
				{
					//올바른 장소, 올바른 방향일 경우
					if ((i == j) && (this->getCorner(i).getDir() == WHITE))
					{
						//cont를 true로 맞춘다
						cont = true;

						//for문 통과
						break;
					}

					//j면에 대해
					this->setFront(j);

					//F' U F
					this->Fp(); this->U(); this->F();

					//for문 통과
					break;
				}
			}

			//코너가 올바른 방향/위치에 있다면 continue
			if (cont) continue;

			this->setFront(i);

			//각 코너가 1층에 없거나 1층에서 나왔으면 3층에 있을 것임
			//i번 코너를 공식을 사용할 수 있는 위치로 이동
			while ( this->getCorner(i).getPos() != this->getColor(this->getFront()).getCorner(0) )
				this->U();

			//i번 코너의 방향이 i번 면을 가리키고 있다면
			if (this->getCorner(i).getDir() == this->getFront())
			{
				//U R U' R'
				this->U(); this->R(); this->Up(); this->Rp();
			}
			//i번 코너의 방향이 i + 1번 면을 가리키고 있다면
			else if (this->getCorner(i).getDir() == this->getColor(this->getFront()).getBy(1))
			{
				//R U R'
				this->R(); this->U(); this->Rp();
			}
			//i번 코너의 방향이 위를 가리키고 있다면
			else if (this->getCorner(i).getDir() == this->getColor(this->getFront()).getBy(0))
			{
				//F' L' U2 L F'
				this->Fp(); this->Lp(); this->U2(); this->L(); this->F();
			}
		}

		//마지막으로 큐브의 방향을 초기화한다
		this->setFront(BLUE);
	}
	//2층 엣지
	void basic_step3()
	{
		//엣지가 제자리에 있을 때 continue시킨다
		bool cont;

		//4~7번 엣지를 제자리에 위치시킨다
		for (int i = 0; i < 4; i++)
		{
			cont = false;

			//우선 각 엣지가 2층에 끼어있는지 확인
			for (int j = 0; j < 4; j++)
			{
				//만일 엣지가 2층에 끼어있다면
				if ( this->getEdge(i + 4).getPos() == this->getColor(j).getEdge(1) )
				{
					this->setFront(j);

					//엣지가 제 자리에 있는 경우
					if (i == j)
					{
						//방향이 다르다면 방향을 고쳐준다
						if ( this->getEdge(i + 4).getDir() != this->getColor(j).getSelf() )
						{
							//R2 U2 F R2 F' U2 R' U R'
							this->R2(); this->U2(); this->F(); this->R2(); this->Fp(); this->U2(); this->Rp(); this->U(); this->Rp();
						}

						//cont를 true로 맞춰준다
						cont = true;
						break;
					}

					//제 자리가 아닌 경우 엣지를 3층으로 빼 준다
					else
					{
						//R U' R' U' F' U F
						this->R(); this->Up(); this->Rp(); this->Up(); this->Fp(); this->U(); this->F();
					}
				}
			}

			//코너가 올바른 방향/위치에 있다면 continue
			if (cont) continue;

			//엣지의 방향이 윗면을 향할 경우
			if ( this->getEdge(i + 4).getDir() == this->getColor(i).getBy(0) )
			{
				//큐브의 front를 왼쪽 면으로 바꿔준다
				this->setFront( this->getColor(i).getBy(1) );

				//각 엣지의 위치가 i의 0번 위치로 이동할 때까지 U'
				while ( this->getEdge(i + 4).getPos() != this->getColor(this->getFront()).getEdge(0) )
					U();

				//U' L' U L U F U' F'
				this->Up(); this->Lp(); this->U(); this->L(); this->U(); this->F(); this->Up(); this->Fp();
			}
			//엣지의 방향이 각 옆면을 향할 경우
			else
			{
				//큐브의 front를 현재 면으로 바꿔준다
				this->setFront(i);

				//각 엣지의 위치가 i의 0번 위치로 이동할 때까지 U
				while (this->getEdge(i + 4).getPos() != this->getColor(i).getEdge(0)) U();

				//U R U' R' U' F' U F
				this->U(); this->R(); this->Up(); this->Rp(); this->Up(); this->Fp(); this->U(); this->F();
			}
		}

		//마지막으로 큐브의 방향을 초기화한다
		this->setFront(BLUE);
	}
	//3층 크로스 (1차)
	void basic_step4()
	{
		//윗면을 가리키는 두 엣지의 인덱스
		int theDir[2];

		int index = 0;

		//큐브의 윗면
		int head = this->getColor(this->getFront()).getBy(0);

		//윗면의 각 엣지에 대해
		for (int i = 0; i < 4; i++)
		{
			//윗면에 존재하는 엣지 중 윗면을 가리키는 엣지가 존재한다면
			if (this->getEdge(this->getColor(head).getEdge(i)).getDir() == head)
			{
				//해당 엣지의 인덱스를 theDir에 저장
				if (index < 2) theDir[index] = this->getColor(head).getEdge(i);
				index += 1;
			}
		}

		//윗면을 가리키고 있는 엣지의 수가 0일 때
		if (index == 0)
		{
			//F U R U' R' F'
			this->F(); this->U(); this->R(); this->Up(); this->Rp(); this->Fp();
		}

		//윗면을 가리키고 있는 엣지의 수가 2일 때
		if (index == 2)
		{
			//두 엣지의 차가 2라면 (=두 엣지가 마주한다면)
			if (abs(this->getEdge(theDir[0]).getPos() - this->getEdge(theDir[1]).getPos()) == 2)
			{
				//두 엣지의 위치가 ㅡ 모양이 되도록 윗면을 회전
				if (this->getEdge(8).getDir() == head) this->U();

				//F R U R' U' F'
				this->F(); this->R(); this->U(); this->Rp(); this->Up(); this->Fp();
			}

			//그렇지 않다면 (=두 엣지가 이웃한다면)
			else
			{
				//두 엣지의 위치가 ┘ 꼴이 되도록 윗면을 회전
				//10번 위치의 엣지와 11번 위치의 엣지가 윗면을 가리킬 때 예외가 발생하므로
				//조건을 두 엣지의 위치의 합으로 설정
				while (this->getEdge(theDir[0]).getPos() + this->getEdge(theDir[1]).getPos() != 21) this->U();

				//F U R U' R' F'
				this->F(); this->U(); this->R(); this->Up(); this->Rp(); this->Fp();
			}
		}

		//마지막으로 큐브의 방향을 초기화한다
		this->setFront(BLUE);
	}
	//3층 크로스 (2차)
	void basic_step5()
	{
		//제자리에 들어간 두 엣지의 인덱스
		int thePos[2];

		int index;

		//큐브의 윗면
		int head = this->getColor(this->getFront()).getBy(0);

		while (1)
		{
			//index를 초기화
			index = 0;

			//윗면의 각 엣지에 대해
			for (int i = 0; i < 4; i++)
			{
				//윗면에 존재하는 엣지 중 윗면을 가리키는 엣지가 존재한다면
				if (this->getEdge( this->getColor(head).getEdge(i) ).getPos() == this->getColor(head).getEdge(i))
				{
					//해당 엣지의 인덱스를 thePos에 저장
					if (index < 2) thePos[index] = this->getColor(head).getEdge(i);
					index += 1;
				}
			}

			//제자리에 위치하는 엣지의 수가 2개 미만일 때 U
			if (index < 2) this->U();

			//제자리에 위치하는 엣지의 수가 2개일 때
			else if (index == 2)
			{

				//두 엣지의 차가 2라면 (=두 엣지가 마주한다면)
				if ( abs( this->getEdge( thePos[0] ).getPos() - this->getEdge( thePos[1] ).getPos() ) == 2)
				{
					//공식을 사용할 수 있게 큐브의 위치를 조정
					if (this->getEdge( thePos[0] ).getPos() % 2 != 0) 
						U();

					//L U L' U L U2 L'
					this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp();

					//다음 공식을 사용할 수 있게 큐브의 위치를 조정
					this->setFront(this->getColor(this->getFront()).getBy(3));
				}

				//그렇지 않다면 (=두 엣지가 이웃한다면)
				else
				{
					//예외사항 처리
					if (thePos[0] + thePos[1] == 21) swap(thePos[0], thePos[1]);

					//공식을 사용할 수 있게 큐브의 위치를 조정
					while (thePos[0] != this->getColor( this->getFront() ).getEdge(0)) 
						this->setFront(this->getColor( this->getFront() ).getBy(1));
				}

				//L U L' U L U2 L' U
				this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp(); this->U();

				//무한 while문을 사용했으므로 while문을 벗어남
				break;
			}

			else if (index == 4)
			{
				//정리가 완료되었으므로 함수를 종료
				return;
			}
		}
	}
	//3층 코너 방향 맞추기
	void basic_step6()
	{
		//방향이 제대로 들어맞은 코너의 수
		int count = 0;

		//각 코너의 방향
		int orient[4];

		//각 코너의 방향과 그에 따른 count의 값을 지정
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//윗면의 j번째 코너의 현재 위치가 윗면의 i번째 코너의 원래 위치일 때
				if (this->getColor(YELLOW).getCorner(i) == this->getCorner( this->getColor(YELLOW).getCorner(j) ).getPos())
				{
					//j번째 코너의 방향을 orient의 i에 기록
					orient[i] = this->getCorner( this->getColor(YELLOW).getCorner(j) ).getDir();
					break;
				}
			}
			if (orient[i] == YELLOW) count += 1;
		}

		//count가 0일 경우
		if (count == 0)
		{
			//방향이 같은 두 코너 이외의 코너의 인덱스(orient에 사용)
			int temp[2];

			//각 코너에 대해
			for (int i = 0; i < 4; i++)
			{
				//그 코너와 그 다음 코너의 방향이 같다면
				if (orient[i] == orient[(i + 1) % 4])
				{
					//두 코너가 존재하는 옆면으로 앞면을 설절
					this->setFront( this->getColor(YELLOW).getBy((i + 1) % 4) );

					//나머지 코너의 인덱스는 temp에 저장
					temp[0] = (i + 2) % 4;
					temp[1] = (i + 3) % 4;

					//나머지 두 코너의 방향이 같을 때
					if ( orient[ temp[0] ] == orient[ temp[1] ] )
					{
						//F R U R' U' R U R' U' R U R' U' F'
						this->F();  this->R();  this->U(); this->Rp(); this->Up(); this->R();  this->U();
						this->Rp(); this->Up(); this->R(); this->U();  this->Rp(); this->Up(); this->Fp();
					}

					//나머지 두 코너의 방향이 다를 때
					else
					{
						//L U L' U L U2 L' U L U L' U L U2 L' U
						this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp(); this->U();
						this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp(); this->U();
					}

					//함수 종료
					return;
				}
			}
		}

		//count가 1일 때
		else if (count == 1)
		{
			//count에 제 방향을 찾은 조각의 orient의 인덱스를 입력
			for (int i = 0; i < 4; i++)
			{
				//제 방향을 찾은 조각을 찾았다면
				if ( orient[i] == YELLOW )
				{
					//count에 그 인덱스를 기록
					count = i;
					break;
				}
			}

			//해당 코너 바로 이전 코너의 방향이 count번째 옆면이라면
			if ( orient[ (count + 3) % 4 ] == this->getColor(YELLOW).getBy(count) )
			{
				//count번째 옆면으로 앞면을 이동
				this->setFront( this->getColor(YELLOW).getBy(count) );
				//R U' L' U R' U' L U
				this->R(); this->Up(); this->Lp(); this->U(); this->Rp(); this->Up(); this->L(); this->U();

				//함수 종료
				return;
			}

			//해당 코너 바로 다음 코너의 방향이 count+1번째 옆면이라면
			else if ( orient[ (count + 1) % 4 ] == this->getColor(YELLOW).getBy((count + 1) % 4) )
			{
				//count + 1번째 옆면으로 앞면을 이동
				this->setFront( this->getColor(YELLOW).getBy( (count + 1) % 4 ) );
				//L' U R U' L U R' U'
				this->Lp(); this->U(); this->R(); this->Up(); this->L(); this->U(); this->Rp(); this->Up();

				//함수 종료
				return;
			}
		}

		//count가 2일 때
		else if (count == 2)
		{
			//방향이 YELLOW가 아닌 두 코너의 인덱스(orient에 사용)
			int temp[2];

			//count는 임시 변수로 사용
			count = 0;

			//각 코너에 대해
			for (int i = 0; i < 4; i++)
			{
				//그 코너의 방향이 YELLOW가 아니라면
				if (orient[i] != YELLOW)
				{
					//해당 코너의 인덱스를 temp에 저장
					temp[count++] = i;
				}

				//count는 반드시 2에서 멈추니 여기서 break
				if (count == 2) break;
			}

			//두 코너가 서로 마주하고 있으면
			if (abs(temp[0] - temp[1]) == 2)
			{
				//모든 옆면에 대해
				for (int i = 0; i < 4; i++)
				{
					//두 코너가 각각 i, i+3번째 면을 가리킨다면
					if ( ( orient[ temp[0] ] == this->getColor(YELLOW).getBy(i) ) 
					  && ( orient[ temp[1] ] == this->getColor(YELLOW).getBy( (i + 3) % 4 ) ) )
					{
						//큐브의 앞면을 i+2번째 면으로 잡는다
						this->setFront(this->getColor(YELLOW).getBy((i + 2) % 4));

						//이후 공식으로 넘어간다
						break;
					}

					else if ( ( orient[ temp[0] ] == this->getColor(YELLOW).getBy(i) ) 
						   && ( orient[ temp[1] ] == this->getColor(YELLOW).getBy( (i + 1) % 4 ) ) )
					{
						//큐브의 앞면을 i+1번째 면으로 잡는다
						this->setFront( this->getColor(YELLOW).getBy( (i + 3) % 4 ) );

						//이후 공식으로 넘어간다
						break;
					}
				}

				//R' F' L' F R F' L F
				this->Rp(); this->Fp(); this->Lp(); this->F(); this->R(); this->Fp(); this->L(); this->F();

				//함수 종료
				return;
			}

			//두 코너가 서로 이웃한다면
			else
			{
				//예외 처리
				if ((temp[0] == 0) && (temp[1] == 3))
				{
					//윗면 기준 오른쪽 면으로 앞면을 바꾼다
					this->setFront( this->getColor(YELLOW).getBy(1) );
				}

				else
				{
					//윗면 기준 temp[1]의 다음 면으로 앞면을 바꾼다
					this->setFront( this->getColor(YELLOW).getBy( (temp[1] + 1) % 4 ) );
				}

				//방향이 YELLOW가 아닌 두 코너의 방향이 같다면
				if (orient[temp[0]] == orient[temp[1]])
				{
					//F2 D' F U2 F' D F U2 F
					this->F2(); this->Dp(); this->F(); this->U2(); this->Fp(); this->D(); this->F(); this->U2(); this->F();
				}

				//방향이 YELLOW가 아닌 두 코너의 방향이 다르다면
				else
				{
					//R' F' L F R F' L' F
					this->Rp(); this->Fp(); this->L(); this->F(); this->R(); this->Fp(); this->Lp(); this->F();
				}
			}
		}

		//그 외에 count는 반드시 4
		else return;
	}
	//3층 코너 위치 맞추기
	void basic_step7()
	{
		//위치가 제대로 들어맞은 코너의 위치
		int count = 0;

		//각 코너의 위치
		int pos[4];

		//각 코너의 위치와 그에 따른 count의 값을 지정
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//각 코너의 현재 위치를 pos에 기록
				pos[i] = find_corner_by_pos( this->getColor(YELLOW).getCorner(i) );
			}

			//각 코너가 제자리에 있을 경우 count를 pos[i]로 지정
			if ( pos[i] == this->getColor(YELLOW).getCorner(i) ) count = pos[i];
		}

		//모든 코너의 위치가 잘못되어 있을 경우
		if (count == 0)
		{
			//코너의 위치가 대각선으로 바뀌어 있을 때
			if ( pos[0] == this->getColor(YELLOW).getCorner(2) )
			{
				this->R2(); this->L2(); this->U2(); this->R2(); this->L2(); this->U();
				this->R2(); this->L2(); this->U2(); this->R2(); this->L2(); this->U();
			}

			//코너의 위치가 평행하게 바뀌어 있을 때
			else
			{
				//각 면에 대해
				for (int i = 0; i < 4; i++)
				{
					//해당 면을 앞면으로 지정
					this->setFront( this->getColor(YELLOW).getBy(i) );

					//각 면의 0번째 코너와 3번째 코너의 위치가 바뀌어 있다면
					if ( this->getColor( getFront() ).getCorner(0) == find_corner_by_pos( this->getColor( getFront() ).getCorner(3) ) )
					{
						//R' F' L' F R F' L F R' F' L F R F' L' F
						this->Rp(); this->Fp(); this->Lp(); this->F(); this->R(); this->Fp(); this->L();  this->F();
						this->Rp(); this->Fp(); this->L();  this->F(); this->R(); this->Fp(); this->Lp(); this->F();

						break;
					}
				}
			}
		}

		//한 코너의 위치가 맞을 경우
		else
		{
			//각 옆면에 대해
			for (int i = 0; i < 4; i++)
			{
				//해당 옆면을 앞면으로 하고
				this->setFront( this->getColor(YELLOW).getBy(i) );

				//그 면의 3번 코너가 제자리에 존재한다면
				if ( find_corner_by_pos( this->getColor( getFront() ).getCorner(3) ) == count ) break;
			}

			//앞면의 0번 코너의 위치를 저장
			int left = find_corner_by_pos( this->getColor( this->getFront() ).getCorner(0) );

			//앞면의 0번 코너의 위치가 오른면의 0번일 경우
			if ( left == this->getColor( this->getRight() ).getCorner(0) )
			{
				//B L' B R2 B' L B R2 B2
				this->B(); this->Lp(); this->B(); this->R2(); this->Bp(); this->L(); this->B(); this->R2(); this->B2();
			}

			else
			{
				//B2 R2 B' L' B R2 B' L B'
				this->B2(); this->R2(); this->Bp(); this->Lp(); this->B(); this->R2(); this->Bp(); this->L(); this->Bp();
			}
		}
	}

	void basic_sort()
	{
		this->basic_step1();
		this->show();
		this->basic_step2();
		this->show();
		this->basic_step3();
		this->show();
		this->basic_step4();
		this->show();
		this->basic_step5();
		this->show();
		this->basic_step6();
		this->show();
		this->basic_step7();
		this->show();
	}
};

int main()
{
	class three_by_three cube;

	cube.shuffle();
	cube.basic_sort();

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