#include <iostream>

using namespace std;

/*
������������
������������
������������
��11������08������09������10����
�����֡������ġ���������������
������07������04������05������06
�����֡������ġ���������������
��03������00������01������02����
��������������
��������������
��������������
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

		//�� ���� ��
		int getSelf() { return this->self; }

		//�� ���� index��° �̿���
		int getBy(int index) { return this->by[index]; }

		//�� ���� index��° ���� ���
		int getEdge(int index) { return this->edge[index]; }

		//�� ���� index��° �ڳ� ���
		int getCorner(int index) { return this->corner[index]; }
	};
	class edgePiece
	{
	private:
		//���� ����� ��ġ
		int pos;

		//side[0]�� �ִ� ��
		int dir;

		//���� ����� �� ��
		//0 : ����, 1 : �ո�
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
		//�ڳ� ����� ��ġ
		int pos;

		//side[0]�� �ִ� ��
		int dir;

		//�ڳ� ����� �� ��
		//0 : ����, 1 : �޸�, 2 : ������
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
	//���� �ٶ󺸰� �ִ� ť���� ��
	//�ظ�� ������ ������� �ʴ´�
	int cubeFront = 0;

	//�� ������ ������ ť��(�����)
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
		//by[color] �鿡 ������ �� �̿� ���� ��
		int by[6][4] = { {5, 1, 4, 3}, {5, 2, 4, 0}, {5,  3, 4, 1}, {5,  0, 4, 2}, {0, 1, 2, 3}, {2,  1, 0, 3} };

		//by[color] �鿡 �����ϴ� �� ���� ���
		int edge[6][4] = { {8, 4, 0, 7}, {9, 5, 1, 4}, {10, 6, 2, 5}, {11, 7, 3, 6}, {0, 1, 2, 3}, {10, 9, 8, 11} };

		//by[color] �鿡 �����ϴ� �� �ڳ� ���
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
		//tColor�� ��� ������ ���� �����Ѵٸ� 1�� ���
		for (int i = 0; i < 4; i++) if (tEdge == tColor.getEdge(i)) return 1;

		//for���� ����� �� ã�� ���Ѵٸ� 0�� ���
		return 0;
	}
	int if_cornerIn(int tCorner, Color tColor)
	{
		//tColor�� ��� ������ ���� �����Ѵٸ� 1�� ���
		for (int i = 0; i < 4; i++) if (tCorner == tColor.getCorner(i)) return 1;

		//for���� ����� �� ã�� ���Ѵٸ� 0�� ���
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
		//���� ����
		int temp, index = 0;

		//������ �� ������ �ڳ�
		int tEdge[4], tCorner[4];

		//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
		for (int i = 0; i < 4; i++)
		{
			//ȸ���� ���� ������ ������ ������ ����
			tEdge[i] = find_edge_by_pos(this->getColor(target).getEdge(i));
		}
		//ȸ���� �鿡 �ش�Ǵ� �ڳ� ��� Ȯ��
		for (int i = 0; i < 4; i++)
		{
			//ȸ���� ���� �ڳʸ� ������ �ڳʷ� ����
			tCorner[i] = find_corner_by_pos(this->getColor(target).getCorner(i));
		}

		//���� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ�
			if (this->getEdge(tEdge[i]).getDir() != target)
			{
				//���� ���� ������ �Ű��ش�
				this->edge[tEdge[i]].setDir( this->getColor(target).getBy((i + 1) % 4) );
			}

			//��ġ�� �� ĭ �ű��
			this->edge[tEdge[i]].setPos( this->getColor(target).getEdge((i + 1) % 4) );
		}

		//�ڳ� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ�
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//���� i��° �ڳʰ� i��° �̿����� ����Ų�ٸ�
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i))
				{
					//����Ű�� ���� i + 1��° �̿������� ����
					this->corner[tCorner[i]].setDir( this->getColor(target).getBy((i + 1) % 4) );
				}

				//�׷��� �ʴٸ� i + 2��° �̿������� ����
				else this->corner[tCorner[i]].setDir( this->getColor(target).getBy((i + 2) % 4) );
			}
			//��ġ�� �� ĭ �ű��
			this->corner[tCorner[i]].setPos( this->getColor(target).getCorner((i + 1) % 4) );
		}
	}
	void ACW(int target)
	{
		//���� ����
		int temp, index = 0;

		//������ �� ������ �ڳ�
		int tEdge[4], tCorner[4];

		//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
		for (int i = 0; i < 4; i++)
		{
			//ȸ���� ���� ������ ������ ������ ����
			tEdge[i] = find_edge_by_pos(this->getColor(target).getEdge(i));
		}
		//ȸ���� �鿡 �ش�Ǵ� �ڳ� ��� Ȯ��
		for (int i = 0; i < 4; i++)
		{
			//ȸ���� ���� �ڳʸ� ������ �ڳʷ� ����
			tCorner[i] = find_corner_by_pos(this->getColor(target).getCorner(i));
		}

		//���� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ�
			if (this->getEdge(tEdge[i]).getDir() != target)
			{
				//���� ���� ������ �Ű��ش�
				this->edge[tEdge[i]].setDir( this->getColor(target).getBy((i + 3) % 4) );
			}

			//��ġ�� �� ĭ �ű��
			this->edge[tEdge[i]].setPos( this->getColor(target).getEdge((i + 3) % 4) );
		}

		//�ڳ� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ�
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//���� i��° �ڳʰ� i��° �̿����� ����Ų�ٸ�
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i))
				{
					//����Ű�� ���� i + 1��° �̿������� ����
					this->corner[tCorner[i]].setDir( this->getColor(target).getBy((i + 3) % 4) );
				}

				//�׷��� �ʴٸ� i��° �̿������� ����
				else this->corner[tCorner[i]].setDir( this->getColor(target).getBy(i) );
			}
			//��ġ�� �� ĭ �ű��
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
		//��� ���� ������ front�� ���� �� ��
		int k = 15 - this->getFront();

		for (int i = 0; i < 4; i++) k -= this->getColor(this->getFront()).getBy(i);

		CW(this->getColor(k).getSelf());
	}
	void Bp()
	{
		//��� ���� ������ front�� ���� �� ��
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

	//�����ʿ�
	void show()
	{
		//print[���� ��][��][��]
		//������ �� ���ϴ��� �ּ�
		int print[6][3][3];

		char col[6][10] = { "��", "��", "��", "��", "��", "��" };

		//�� ������ �������� �迭ȭ
		int pEdge[12];

		//�� �ڳ��� �������� �迭ȭ
		int pCorner[8];

		//0~3, 8~11�� ������ ���� ������ �� �� ����
		//��� �� ����. ����� ���� ��� 0���� 2���� ������ �ش�
		//temp[��][0 : ��/1 : ��]
		int eTemp[4][2] = { {0, 1}, {1, 2}, {2, 1}, {1, 0} };

		//�� �ڳ��� ���� ������ �� �� ����
		//��� �� ����. ����� ���� ��� 0���� 1��, 2���� 3���� ������ �ش�
		//temp[��][0 : ��/1 : ��]
		int cTemp[4][2] = { {0, 2}, {2, 2}, {2, 0}, {0, 0} };

		//�� ������ �������� �ε��� ������ ����
		for (int i = 0; i < 12; i++) pEdge[(int)this->getEdge(i).getPos()] = i;

		//�� �ڳ��� �������� �ε��� ������ ����
		for (int i = 0; i < 8; i++) pCorner[(int)this->getCorner(i).getPos()] = i;

		//�� ���� �ڳ� ����� ���� ����
		for (int i = 0; i < 6; i++) print[i][1][1] = i;

		//���� ��ϵ��� 0~3, 4~7, 8~11�� ���� �� �ִ�
		//�ڳ� ��ϵ��� 0~3, 4~7�� ���� �� �ִ�
		for (int i = 0; i < 4; i++)
		{
			//0~3�� ������ ���� ������ ��� ���� ���Ѵٸ�
			if (this->getEdge(pEdge[i]).getDir() == WHITE)
			{
				//�� �ڳ��� top(=side[0], dir)�� ��� ���� ������ ��ġ�� �ش�
				print[WHITE][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getTop();
				//�� �ڳ��� front(=side[1])�� �� ������ 3�� 2���� �ش�
				print[i][2][1] = this->getEdge(pEdge[i]).getFront();
			}

			//�׷��� ���� ��� ���ΰ� �ݴ��� ��쿡 �ش�
			else
			{
				print[WHITE][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getFront();
				print[i][2][1] = this->getEdge(pEdge[i]).getTop();
			}

			//eTemp[0] = {0, 1}�̰� eTemp[2] = {2, 1}�̴� ������ �� �κи� �ٲ��ش�
			swap(eTemp[0][0], eTemp[2][0]);


			//4~7��° ������ ���� ������ �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� ���Ѵٸ�
			if (this->getEdge(pEdge[i + 4]).getDir() == (int)this->getColor(i).getSelf())
			{
				//�� �ڳ��� top(=side[0], dir)�� ���� �� ���� 2�� 3���� �ش�
				print[i][1][2] = this->getEdge(pEdge[i + 4]).getTop();
				//�� �ڳ��� front(=side[1])�� ū ���� 2�� 1���� �ش�
				print[this->getColor(i).getBy(1)][1][0] = this->getEdge(pEdge[i + 4]).getFront();
			}

			//�׷��� ���� ��� ���ΰ� �ݴ��� ��쿡 �ش�
			else
			{
				print[this->getColor(i).getBy(1)][1][0] = this->getEdge(pEdge[i + 4]).getTop();
				print[i][1][2] = this->getEdge(pEdge[i + 4]).getFront();
			}


			//8~11�� ������ ���� ������ ����� ���� ���Ѵٸ�
			if (this->getEdge(pEdge[i + 8]).getDir() == YELLOW)
			{
				//�� �ڳ��� top(=side[0], dir)�� ��� ���� ������ ��ġ�� �ش�
				print[YELLOW][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getTop();
				//�� �ڳ��� front(=side[1])�� �� ������ 1�� 2���� �ش�
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getFront();
			}

			//�׷��� ���� ��� ���ΰ� �ݴ��� ��쿡 �ش�
			else
			{
				print[YELLOW][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getFront();
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getTop();
			}

			//���� �������� ���� ���� eTemp[0]�� eTemp[2]�� �� �κ��� �ٽ� �ٲ��ش�
			swap(eTemp[0][0], eTemp[2][0]);


			//0~3�� �ڳʿ� ���� ������ ��� ���� ���Ѵٸ�
			if (this->getCorner(pCorner[i]).getDir() == WHITE)
			{
				//�� �ڳ��� top(=side[0], dir)�� ��� ���� ������ ��ġ�� �ش�
				print[WHITE][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 1���� �ش�
				print[this->getColor(i).getBy(1)][2][0] = this->getCorner(pCorner[i]).getLeft();
				//�� �ڳ��� right(=side[2])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 3���� �ش�
				print[i][2][2] = this->getCorner(pCorner[i]).getRight();
			}

			//�׷��� �ʰ� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i]).getDir() == (i + 1) % 4)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 1���� �ش�
				print[this->getColor(i).getBy(1)][2][0] = this->getCorner(pCorner[i]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 3���� �ش�
				print[i][2][2] = this->getCorner(pCorner[i]).getLeft();
				//�� �ڳ��� right(=side[2])�� ��� ���� ������ ��ġ�� �ش�
				print[WHITE][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getRight();
			}

			//�׷��� �ʰ� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i]).getDir() == i)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 3���� �ش�
				print[i][2][2] = this->getCorner(pCorner[i]).getTop();
				//�� �ڳ��� left(=side[1])�� ��� ���� ������ ��ġ�� �ش�
				print[WHITE][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getLeft();
				//�� �ڳ��� right(=side[2])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 1���� �ش�
				print[this->getColor(i).getBy(1)][2][0] = this->getCorner(pCorner[i]).getRight();
			}

			//cTemp[0] = {0, 2}�̰� cTemp[1] = {2, 2}�̴� ������ �� �κи� �ٲ��ش�
			swap(cTemp[0][0], cTemp[1][0]);
			//cTemp[2] = {2, 0}�̰� cTemp[3] = {0, 0}�̴� ������ �� �κи� �ٲ��ش�
			swap(cTemp[2][0], cTemp[3][0]);

			//4~7�� �ڳʿ� ���� ������ ����� ���� ���Ѵٸ�
			if (this->getCorner(pCorner[i + 4]).getDir() == YELLOW)
			{
				//�� �ڳ��� top(=side[0], dir)�� ����� ���� ������ ��ġ�� �ش�
				print[YELLOW][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 1���� �ش�
				print[this->getColor(i).getBy(1)][0][0] = this->getCorner(pCorner[i + 4]).getRight();
				//�� �ڳ��� right(=side[2])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 3���� �ش�
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getLeft();
			}

			//�׷��� �ʰ� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i + 4]).getDir() == (i + 1) % 4)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 3���� �ش�
				print[this->getColor(i).getBy(1)][0][0] = this->getCorner(pCorner[i + 4]).getTop();
				//�� �ڳ��� left(=side[1])�� ����� ���� ������ ��ġ�� �ش�
				print[YELLOW][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getLeft();
				//�� �ڳ��� right(=side[2])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 1���� �ش�
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getRight();
			}

			//�׷��� �ʰ� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i + 4]).getDir() == i)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 1���� �ش�
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 3���� �ش�
				print[this->getColor(i).getBy(1)][0][0] = this->getCorner(pCorner[i + 4]).getLeft();
				//�� �ڳ��� right(=side[2])�� ����� ���� ������ ��ġ�� �ش�
				print[YELLOW][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getRight();
			}

			//���� �������� ���� ���� cTemp[0]�� cTemp[1]�� �� �κ�, cTemp[2]�� cTemp[3]�� �� �κ��� �ٽ� �ٲ��ش�
			swap(cTemp[0][0], cTemp[1][0]);
			swap(cTemp[2][0], cTemp[3][0]);
		}

		//����� ���� �� ���ϴ� �ּ��� �°� ���
		for (int i = 0; i < 3; i++) cout << "��������" << col[print[YELLOW][i][0]] << col[print[YELLOW][i][1]] << col[print[YELLOW][i][2]] << endl;
		cout << endl;

		//���� ����� �� ���ϴ� �ּ��� �°� ���
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << col[print[this->getColor(j).getBy(3)][i][0]]
					<< col[print[this->getColor(j).getBy(3)][i][1]]
					<< col[print[this->getColor(j).getBy(3)][i][2]] << "��";
			}

			cout << endl;
		}

		cout << endl;

		//��� ���� �� ���ϴ� �ּ��� �°� ���
		for (int i = 0; i < 3; i++) cout << "��������" << col[print[WHITE][i][0]] << col[print[WHITE][i][1]] << col[print[WHITE][i][2]] << endl;
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

	//1�� ũ�ν�
	void basic_step1()
	{
		//0~3�� ������ ���ڸ��� ��ġ��Ų�� (ũ�ν�)
		for (int i = 0; i < 4; i++)
		{
			//i���� ������ ��� �鿡�� ������ �߰� �� i���� 0�� ��ġ�� ������ �̵�
			for (int j = 0; j < 4; j++)
			{
				//j�� i�� ��, �� Ȯ���� ���� i���� ���� �ǳʶ�
				if (i == j) continue;

				//���� j �鿡 i��° ������ �߰��ߴٸ�
				if (if_edgeIn( this->getEdge(i).getPos(), this->getColor(j) ))
				{
					this->setFront(j);

					//0�� ��ġ�� ���
					//�� ��� �ش� ���� ���� ������ ���ڸ��� ���ƿ��� ����
					if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(0))
					{
						//������ �ش��ϴ� ���� 0�� ��ġ�� �� ������ ������ ȸ��
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) 
							this->U();
					}

					//j���� 1�� ��ġ�� ���
					//�� ��� �ش� ���� ������ ���ڸ��� ���ƿ��� �� ����
					else if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(1))
					{
						//0�� ��ġ�� �̾Ƴ� ��
						this->Fp();

						//������ �ش��ϴ� ���� 0�� ��ġ�� �� ������ ������ ȸ��
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) 
							this->U();

						//������ ��츦 ���� ���� ���󺹱�
						this->F();
					}

					//j���� 2�� ��ġ�� ���
					//�� ��� �ش� ���� ���� ������ ���ڸ��� ���ƿ��� ����
					else if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(2))
					{
						//0�� ��ġ�� �̾Ƴ� ��
						this->F2();

						//������ �ش��ϴ� ���� 0�� ��ġ�� �� ������ ������ ȸ��
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) 
							this->U();
					}

					break;
				}
			}

			this->setFront(i);

			//�� ������ ������ ������ ����Ű�� ���� ��
			if (this->getEdge(i).getDir() != this->getColor(this->getFront()).getSelf())
			{
				//���� n�� ȸ������ ������ �ùٸ� ��ġ�� ���´�
				while (this->getEdge(i).getPos() != this->getColor(this->getFront()).getEdge(2))
					this->F();
			}
			//�� ������ ������ �ո��� ����Ű�� ���� ��
			else
			{
				//���� n�� ȸ������ ũ�ν� ������ ����� �� �ִ� ��ġ�� �д�
				while (this->getEdge(i).getPos() != this->getColor(this->getFront()).getEdge(0))
					this->F();

				//U' R' F R
				this->Up(); this->Rp(); this->F(); this->R();
			}
		}

		//���������� ť���� ������ �ʱ�ȭ�Ѵ�
		this->setFront(BLUE);
	}
	//1�� �ڳ�
	void basic_step2()
	{
		//�ڳʰ� ���ڸ��� ���� �� continue��Ų��
		bool cont;

		//�� �ڳʸ� ���ڸ��� ��ġ��Ų��
		for (int i = 0; i < 4; i++)
		{
			cont = false;

			//�켱 �� �ڳʰ� 1���� �����ִ��� Ȯ��
			for (int j = 0; j < 4; j++)
			{
				//���� �ڳʰ� �߸��� 1�� ��ġ�� �����ְų�
				//������ �߸��� ���·� �������� ���
				if (this->getCorner(i).getPos() == this->getColor(j).getCorner(1))
				{
					//�ùٸ� ���, �ùٸ� ������ ���
					if ((i == j) && (this->getCorner(i).getDir() == WHITE))
					{
						//cont�� true�� �����
						cont = true;

						//for�� ���
						break;
					}

					//j�鿡 ����
					this->setFront(j);

					//F' U F
					this->Fp(); this->U(); this->F();

					//for�� ���
					break;
				}
			}

			//�ڳʰ� �ùٸ� ����/��ġ�� �ִٸ� continue
			if (cont) continue;

			this->setFront(i);

			//�� �ڳʰ� 1���� ���ų� 1������ �������� 3���� ���� ����
			//i�� �ڳʸ� ������ ����� �� �ִ� ��ġ�� �̵�
			while ( this->getCorner(i).getPos() != this->getColor(this->getFront()).getCorner(0) )
				this->U();

			//i�� �ڳ��� ������ i�� ���� ����Ű�� �ִٸ�
			if (this->getCorner(i).getDir() == this->getFront())
			{
				//U R U' R'
				this->U(); this->R(); this->Up(); this->Rp();
			}
			//i�� �ڳ��� ������ i + 1�� ���� ����Ű�� �ִٸ�
			else if (this->getCorner(i).getDir() == this->getColor(this->getFront()).getBy(1))
			{
				//R U R'
				this->R(); this->U(); this->Rp();
			}
			//i�� �ڳ��� ������ ���� ����Ű�� �ִٸ�
			else if (this->getCorner(i).getDir() == this->getColor(this->getFront()).getBy(0))
			{
				//F' L' U2 L F'
				this->Fp(); this->Lp(); this->U2(); this->L(); this->F();
			}
		}

		//���������� ť���� ������ �ʱ�ȭ�Ѵ�
		this->setFront(BLUE);
	}
	//2�� ����
	void basic_step3()
	{
		//������ ���ڸ��� ���� �� continue��Ų��
		bool cont;

		//4~7�� ������ ���ڸ��� ��ġ��Ų��
		for (int i = 0; i < 4; i++)
		{
			cont = false;

			//�켱 �� ������ 2���� �����ִ��� Ȯ��
			for (int j = 0; j < 4; j++)
			{
				//���� ������ 2���� �����ִٸ�
				if ( this->getEdge(i + 4).getPos() == this->getColor(j).getEdge(1) )
				{
					this->setFront(j);

					//������ �� �ڸ��� �ִ� ���
					if (i == j)
					{
						//������ �ٸ��ٸ� ������ �����ش�
						if ( this->getEdge(i + 4).getDir() != this->getColor(j).getSelf() )
						{
							//R2 U2 F R2 F' U2 R' U R'
							this->R2(); this->U2(); this->F(); this->R2(); this->Fp(); this->U2(); this->Rp(); this->U(); this->Rp();
						}

						//cont�� true�� �����ش�
						cont = true;
						break;
					}

					//�� �ڸ��� �ƴ� ��� ������ 3������ �� �ش�
					else
					{
						//R U' R' U' F' U F
						this->R(); this->Up(); this->Rp(); this->Up(); this->Fp(); this->U(); this->F();
					}
				}
			}

			//�ڳʰ� �ùٸ� ����/��ġ�� �ִٸ� continue
			if (cont) continue;

			//������ ������ ������ ���� ���
			if ( this->getEdge(i + 4).getDir() == this->getColor(i).getBy(0) )
			{
				//ť���� front�� ���� ������ �ٲ��ش�
				this->setFront( this->getColor(i).getBy(1) );

				//�� ������ ��ġ�� i�� 0�� ��ġ�� �̵��� ������ U'
				while ( this->getEdge(i + 4).getPos() != this->getColor(this->getFront()).getEdge(0) )
					U();

				//U' L' U L U F U' F'
				this->Up(); this->Lp(); this->U(); this->L(); this->U(); this->F(); this->Up(); this->Fp();
			}
			//������ ������ �� ������ ���� ���
			else
			{
				//ť���� front�� ���� ������ �ٲ��ش�
				this->setFront(i);

				//�� ������ ��ġ�� i�� 0�� ��ġ�� �̵��� ������ U
				while (this->getEdge(i + 4).getPos() != this->getColor(i).getEdge(0)) U();

				//U R U' R' U' F' U F
				this->U(); this->R(); this->Up(); this->Rp(); this->Up(); this->Fp(); this->U(); this->F();
			}
		}

		//���������� ť���� ������ �ʱ�ȭ�Ѵ�
		this->setFront(BLUE);
	}
	//3�� ũ�ν� (1��)
	void basic_step4()
	{
		//������ ����Ű�� �� ������ �ε���
		int theDir[2];

		int index = 0;

		//ť���� ����
		int head = this->getColor(this->getFront()).getBy(0);

		//������ �� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//���鿡 �����ϴ� ���� �� ������ ����Ű�� ������ �����Ѵٸ�
			if (this->getEdge(this->getColor(head).getEdge(i)).getDir() == head)
			{
				//�ش� ������ �ε����� theDir�� ����
				if (index < 2) theDir[index] = this->getColor(head).getEdge(i);
				index += 1;
			}
		}

		//������ ����Ű�� �ִ� ������ ���� 0�� ��
		if (index == 0)
		{
			//F U R U' R' F'
			this->F(); this->U(); this->R(); this->Up(); this->Rp(); this->Fp();
		}

		//������ ����Ű�� �ִ� ������ ���� 2�� ��
		if (index == 2)
		{
			//�� ������ ���� 2��� (=�� ������ �����Ѵٸ�)
			if (abs(this->getEdge(theDir[0]).getPos() - this->getEdge(theDir[1]).getPos()) == 2)
			{
				//�� ������ ��ġ�� �� ����� �ǵ��� ������ ȸ��
				if (this->getEdge(8).getDir() == head) this->U();

				//F R U R' U' F'
				this->F(); this->R(); this->U(); this->Rp(); this->Up(); this->Fp();
			}

			//�׷��� �ʴٸ� (=�� ������ �̿��Ѵٸ�)
			else
			{
				//�� ������ ��ġ�� �� ���� �ǵ��� ������ ȸ��
				//10�� ��ġ�� ������ 11�� ��ġ�� ������ ������ ����ų �� ���ܰ� �߻��ϹǷ�
				//������ �� ������ ��ġ�� ������ ����
				while (this->getEdge(theDir[0]).getPos() + this->getEdge(theDir[1]).getPos() != 21) this->U();

				//F U R U' R' F'
				this->F(); this->U(); this->R(); this->Up(); this->Rp(); this->Fp();
			}
		}

		//���������� ť���� ������ �ʱ�ȭ�Ѵ�
		this->setFront(BLUE);
	}
	//3�� ũ�ν� (2��)
	void basic_step5()
	{
		//���ڸ��� �� �� ������ �ε���
		int thePos[2];

		int index;

		//ť���� ����
		int head = this->getColor(this->getFront()).getBy(0);

		while (1)
		{
			//index�� �ʱ�ȭ
			index = 0;

			//������ �� ������ ����
			for (int i = 0; i < 4; i++)
			{
				//���鿡 �����ϴ� ���� �� ������ ����Ű�� ������ �����Ѵٸ�
				if (this->getEdge( this->getColor(head).getEdge(i) ).getPos() == this->getColor(head).getEdge(i))
				{
					//�ش� ������ �ε����� thePos�� ����
					if (index < 2) thePos[index] = this->getColor(head).getEdge(i);
					index += 1;
				}
			}

			//���ڸ��� ��ġ�ϴ� ������ ���� 2�� �̸��� �� U
			if (index < 2) this->U();

			//���ڸ��� ��ġ�ϴ� ������ ���� 2���� ��
			else if (index == 2)
			{

				//�� ������ ���� 2��� (=�� ������ �����Ѵٸ�)
				if ( abs( this->getEdge( thePos[0] ).getPos() - this->getEdge( thePos[1] ).getPos() ) == 2)
				{
					//������ ����� �� �ְ� ť���� ��ġ�� ����
					if (this->getEdge( thePos[0] ).getPos() % 2 != 0) 
						U();

					//L U L' U L U2 L'
					this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp();

					//���� ������ ����� �� �ְ� ť���� ��ġ�� ����
					this->setFront(this->getColor(this->getFront()).getBy(3));
				}

				//�׷��� �ʴٸ� (=�� ������ �̿��Ѵٸ�)
				else
				{
					//���ܻ��� ó��
					if (thePos[0] + thePos[1] == 21) swap(thePos[0], thePos[1]);

					//������ ����� �� �ְ� ť���� ��ġ�� ����
					while (thePos[0] != this->getColor( this->getFront() ).getEdge(0)) 
						this->setFront(this->getColor( this->getFront() ).getBy(1));
				}

				//L U L' U L U2 L' U
				this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp(); this->U();

				//���� while���� ��������Ƿ� while���� ���
				break;
			}

			else if (index == 4)
			{
				//������ �Ϸ�Ǿ����Ƿ� �Լ��� ����
				return;
			}
		}
	}
	//3�� �ڳ� ���� ���߱�
	void basic_step6()
	{
		//������ ����� ������ �ڳ��� ��
		int count = 0;

		//�� �ڳ��� ����
		int orient[4];

		//�� �ڳ��� ����� �׿� ���� count�� ���� ����
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//������ j��° �ڳ��� ���� ��ġ�� ������ i��° �ڳ��� ���� ��ġ�� ��
				if (this->getColor(YELLOW).getCorner(i) == this->getCorner( this->getColor(YELLOW).getCorner(j) ).getPos())
				{
					//j��° �ڳ��� ������ orient�� i�� ���
					orient[i] = this->getCorner( this->getColor(YELLOW).getCorner(j) ).getDir();
					break;
				}
			}
			if (orient[i] == YELLOW) count += 1;
		}

		//count�� 0�� ���
		if (count == 0)
		{
			//������ ���� �� �ڳ� �̿��� �ڳ��� �ε���(orient�� ���)
			int temp[2];

			//�� �ڳʿ� ����
			for (int i = 0; i < 4; i++)
			{
				//�� �ڳʿ� �� ���� �ڳ��� ������ ���ٸ�
				if (orient[i] == orient[(i + 1) % 4])
				{
					//�� �ڳʰ� �����ϴ� �������� �ո��� ����
					this->setFront( this->getColor(YELLOW).getBy((i + 1) % 4) );

					//������ �ڳ��� �ε����� temp�� ����
					temp[0] = (i + 2) % 4;
					temp[1] = (i + 3) % 4;

					//������ �� �ڳ��� ������ ���� ��
					if ( orient[ temp[0] ] == orient[ temp[1] ] )
					{
						//F R U R' U' R U R' U' R U R' U' F'
						this->F();  this->R();  this->U(); this->Rp(); this->Up(); this->R();  this->U();
						this->Rp(); this->Up(); this->R(); this->U();  this->Rp(); this->Up(); this->Fp();
					}

					//������ �� �ڳ��� ������ �ٸ� ��
					else
					{
						//L U L' U L U2 L' U L U L' U L U2 L' U
						this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp(); this->U();
						this->L(); this->U(); this->Lp(); this->U(); this->L(); this->U2(); this->Lp(); this->U();
					}

					//�Լ� ����
					return;
				}
			}
		}

		//count�� 1�� ��
		else if (count == 1)
		{
			//count�� �� ������ ã�� ������ orient�� �ε����� �Է�
			for (int i = 0; i < 4; i++)
			{
				//�� ������ ã�� ������ ã�Ҵٸ�
				if ( orient[i] == YELLOW )
				{
					//count�� �� �ε����� ���
					count = i;
					break;
				}
			}

			//�ش� �ڳ� �ٷ� ���� �ڳ��� ������ count��° �����̶��
			if ( orient[ (count + 3) % 4 ] == this->getColor(YELLOW).getBy(count) )
			{
				//count��° �������� �ո��� �̵�
				this->setFront( this->getColor(YELLOW).getBy(count) );
				//R U' L' U R' U' L U
				this->R(); this->Up(); this->Lp(); this->U(); this->Rp(); this->Up(); this->L(); this->U();

				//�Լ� ����
				return;
			}

			//�ش� �ڳ� �ٷ� ���� �ڳ��� ������ count+1��° �����̶��
			else if ( orient[ (count + 1) % 4 ] == this->getColor(YELLOW).getBy((count + 1) % 4) )
			{
				//count + 1��° �������� �ո��� �̵�
				this->setFront( this->getColor(YELLOW).getBy( (count + 1) % 4 ) );
				//L' U R U' L U R' U'
				this->Lp(); this->U(); this->R(); this->Up(); this->L(); this->U(); this->Rp(); this->Up();

				//�Լ� ����
				return;
			}
		}

		//count�� 2�� ��
		else if (count == 2)
		{
			//������ YELLOW�� �ƴ� �� �ڳ��� �ε���(orient�� ���)
			int temp[2];

			//count�� �ӽ� ������ ���
			count = 0;

			//�� �ڳʿ� ����
			for (int i = 0; i < 4; i++)
			{
				//�� �ڳ��� ������ YELLOW�� �ƴ϶��
				if (orient[i] != YELLOW)
				{
					//�ش� �ڳ��� �ε����� temp�� ����
					temp[count++] = i;
				}

				//count�� �ݵ�� 2���� ���ߴ� ���⼭ break
				if (count == 2) break;
			}

			//�� �ڳʰ� ���� �����ϰ� ������
			if (abs(temp[0] - temp[1]) == 2)
			{
				//��� ���鿡 ����
				for (int i = 0; i < 4; i++)
				{
					//�� �ڳʰ� ���� i, i+3��° ���� ����Ų�ٸ�
					if ( ( orient[ temp[0] ] == this->getColor(YELLOW).getBy(i) ) 
					  && ( orient[ temp[1] ] == this->getColor(YELLOW).getBy( (i + 3) % 4 ) ) )
					{
						//ť���� �ո��� i+2��° ������ ��´�
						this->setFront(this->getColor(YELLOW).getBy((i + 2) % 4));

						//���� �������� �Ѿ��
						break;
					}

					else if ( ( orient[ temp[0] ] == this->getColor(YELLOW).getBy(i) ) 
						   && ( orient[ temp[1] ] == this->getColor(YELLOW).getBy( (i + 1) % 4 ) ) )
					{
						//ť���� �ո��� i+1��° ������ ��´�
						this->setFront( this->getColor(YELLOW).getBy( (i + 3) % 4 ) );

						//���� �������� �Ѿ��
						break;
					}
				}

				//R' F' L' F R F' L F
				this->Rp(); this->Fp(); this->Lp(); this->F(); this->R(); this->Fp(); this->L(); this->F();

				//�Լ� ����
				return;
			}

			//�� �ڳʰ� ���� �̿��Ѵٸ�
			else
			{
				//���� ó��
				if ((temp[0] == 0) && (temp[1] == 3))
				{
					//���� ���� ������ ������ �ո��� �ٲ۴�
					this->setFront( this->getColor(YELLOW).getBy(1) );
				}

				else
				{
					//���� ���� temp[1]�� ���� ������ �ո��� �ٲ۴�
					this->setFront( this->getColor(YELLOW).getBy( (temp[1] + 1) % 4 ) );
				}

				//������ YELLOW�� �ƴ� �� �ڳ��� ������ ���ٸ�
				if (orient[temp[0]] == orient[temp[1]])
				{
					//F2 D' F U2 F' D F U2 F
					this->F2(); this->Dp(); this->F(); this->U2(); this->Fp(); this->D(); this->F(); this->U2(); this->F();
				}

				//������ YELLOW�� �ƴ� �� �ڳ��� ������ �ٸ��ٸ�
				else
				{
					//R' F' L F R F' L' F
					this->Rp(); this->Fp(); this->L(); this->F(); this->R(); this->Fp(); this->Lp(); this->F();
				}
			}
		}

		//�� �ܿ� count�� �ݵ�� 4
		else return;
	}
	//3�� �ڳ� ��ġ ���߱�
	void basic_step7()
	{
		//��ġ�� ����� ������ �ڳ��� ��ġ
		int count = 0;

		//�� �ڳ��� ��ġ
		int pos[4];

		//�� �ڳ��� ��ġ�� �׿� ���� count�� ���� ����
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//�� �ڳ��� ���� ��ġ�� pos�� ���
				pos[i] = find_corner_by_pos( this->getColor(YELLOW).getCorner(i) );
			}

			//�� �ڳʰ� ���ڸ��� ���� ��� count�� pos[i]�� ����
			if ( pos[i] == this->getColor(YELLOW).getCorner(i) ) count = pos[i];
		}

		//��� �ڳ��� ��ġ�� �߸��Ǿ� ���� ���
		if (count == 0)
		{
			//�ڳ��� ��ġ�� �밢������ �ٲ�� ���� ��
			if ( pos[0] == this->getColor(YELLOW).getCorner(2) )
			{
				this->R2(); this->L2(); this->U2(); this->R2(); this->L2(); this->U();
				this->R2(); this->L2(); this->U2(); this->R2(); this->L2(); this->U();
			}

			//�ڳ��� ��ġ�� �����ϰ� �ٲ�� ���� ��
			else
			{
				//�� �鿡 ����
				for (int i = 0; i < 4; i++)
				{
					//�ش� ���� �ո����� ����
					this->setFront( this->getColor(YELLOW).getBy(i) );

					//�� ���� 0��° �ڳʿ� 3��° �ڳ��� ��ġ�� �ٲ�� �ִٸ�
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

		//�� �ڳ��� ��ġ�� ���� ���
		else
		{
			//�� ���鿡 ����
			for (int i = 0; i < 4; i++)
			{
				//�ش� ������ �ո����� �ϰ�
				this->setFront( this->getColor(YELLOW).getBy(i) );

				//�� ���� 3�� �ڳʰ� ���ڸ��� �����Ѵٸ�
				if ( find_corner_by_pos( this->getColor( getFront() ).getCorner(3) ) == count ) break;
			}

			//�ո��� 0�� �ڳ��� ��ġ�� ����
			int left = find_corner_by_pos( this->getColor( this->getFront() ).getCorner(0) );

			//�ո��� 0�� �ڳ��� ��ġ�� �������� 0���� ���
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
������������
������������
������������
��11������08������09������10����
�����֡������ġ���������������
������07������04������05������06
�����֡������ġ���������������
��03������00������01������02����
��������������
��������������
��������������
*/