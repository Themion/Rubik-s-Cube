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

	void CW(int target)
	{
		//���� ����
		int temp, index = 0;

		int tEdge[4], tCorner[4];

		//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
		for (int i = 0; i < 4; i++)
		{
			//���� �� ���� ����� ��ġ�� ����
			temp = this->getColor(target).getEdge(i);

			for (int j = 0; j < 12; j++)
			{
				//�ش� ��ġ�� �����ϴ� ���� ����� ã�Ҵٸ�
				if (temp == this->getEdge(j).getPos())
				{
					//����Ʈ�� �ش� ���� ����� �߰�
					tEdge[index++] = j;
					break;
				}
			}

			if (index == 4) break;
		}

		//ȸ���� �鿡 �ش�Ǵ� �ڳ� ��� Ȯ��
		index = 0;

		for (int i = 0; i < 4; i++)
		{
			//���� �� �ڳ� ����� ��ġ�� ����
			temp = this->getColor(target).getCorner(i);

			for (int j = 0; j < 8; j++)
			{
				//�ش� ��ġ�� �����ϴ� �ڳ� ����� ã�Ҵٸ�
				if (temp == this->getCorner(j).getPos())
				{
					//����Ʈ�� �ش� �ڳ� ����� �߰�
					tCorner[index++] = j;
					break;
				}
			}
			
			if (index == 4) break;
		}

		//���� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ� ���� ���� ����ų ��(i + 1��°)���� ����
			if (this->getEdge(tEdge[i]).getDir() != target) this->edge[tEdge[i]].setDir(this->getColor(target).getBy((i + 1) % 4));
			//��ġ�� �� ĭ �ű��
			this->edge[tEdge[i]].setPos(this->getColor(target).getEdge((i + 1) % 4));
		}

		//�ڳ� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ�
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//���� ����Ű�� ���� �Ǵ��Ͽ� ���� ���� ����ų ��(i + 1��° Ȥ�� �� + 1��°)���� ����
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i)) this->corner[tCorner[i]].setDir(this->getColor(target).getBy((i + 1) % 4));
				else this->corner[tCorner[i]].setDir(this->getColor(target).getBy((i + 2) % 4));
			}
			//��ġ�� �� ĭ �ű��
			this->corner[tCorner[i]].setPos(this->getColor(target).getCorner((i + 1) % 4));
			bool k = false;
		}
	}
	void ACW(int target)
	{
		//���� ����
		int temp, index = 0;

		int tEdge[4], tCorner[4];

		//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
		for (int i = 0; i < 4; i++)
		{
			//���� �� ���� ����� ��ġ�� ����
			temp = this->getColor(target).getEdge(i);

			for (int j = 0; j < 12; j++)
			{
				//�ش� ��ġ�� �����ϴ� ���� ����� ã�Ҵٸ�
				if (temp == getEdge(j).getPos())
				{
					//����Ʈ�� �ش� ���� ����� �߰�
					tEdge[index++] = j;
					break;
				}
			}

			if (index == 4) break;
		}

		//ȸ���� �鿡 �ش�Ǵ� �ڳ� ��� Ȯ��
		index = 0;

		for (int i = 0; i < 4; i++)
		{
			//���� �� �ڳ� ����� ��ġ�� ����
			temp = this->getColor(target).getCorner(i);

			for (int j = 0; j < 8; j++)
			{
				//�ش� ��ġ�� �����ϴ� �ڳ� ����� ã�Ҵٸ�
				if (temp == this->getCorner(j).getPos())
				{
					//����Ʈ�� �ش� �ڳ� ����� �߰�
					tCorner[index++] = j;
					break;
				}
			}

			if (index == 4) break;
		}

		//���� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ� ���� ���� ����ų ��(i - 1��°)���� ���� : ((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
			if (this->getEdge(tEdge[i]).getDir() != target) this->edge[tEdge[i]].setDir(this->getColor(target).getBy((i + 3) % 4));
			//��ġ�� �� ĭ �ű��
			this->edge[tEdge[i]].setPos(this->getColor(target).getEdge((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
		}

		//�ڳ� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//�켱 ������ �ش� ���� ������ �ʴ´ٸ�
			if (this->getCorner(tCorner[i]).getDir() != target)
			{
				//���� ����Ű�� ���� �Ǵ��Ͽ� ���� ���� ����ų ��(i - 1��° Ȥ�� �� + 1��°)���� ���� : ((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
				if (this->getCorner(tCorner[i]).getDir() == this->getColor(target).getBy(i)) this->corner[tCorner[i]].setDir(this->getColor(target).getBy((i + 3) % 4));
				else this->corner[tCorner[i]].setDir(this->getColor(target).getBy(i));
			}
			//��ġ�� �� ĭ �ű��
			this->corner[tCorner[i]].setPos(this->getColor(target).getCorner((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
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
		CW(this->getColor(this->getFront()).getSelf());
	}
	void Fp()
	{
		ACW(this->getColor(this->getFront()).getSelf());
	}
	void F2() 
	{
		F(); F(); 
	}
	
	void B()
	{
		CW(this->getColor((this->getFront() + 2) % 4).getSelf());
	}
	void Bp()
	{
		ACW(this->getColor((this->getFront() + 2) % 4).getSelf());
	}
	void B2()
	{
		B(); B();
	}

	void U()
	{
		CW(YELLOW);
	}
	void Up()
	{
		ACW(YELLOW);
	}
	void U2()
	{
		U(); U();
	}

	void D()
	{
		CW(WHITE);
	}
	void Dp()
	{
		ACW(WHITE);
	}
	void D2()
	{
		D(); D();
	}

	void visualize()
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
				print[4][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getTop();
				//�� �ڳ��� front(=side[1])�� �� ������ 3�� 2���� �ش�
				print[i][2][1] = this->getEdge(pEdge[i]).getFront();
			}

			//�׷��� ���� ��� ���ΰ� �ݴ��� ��쿡 �ش�
			else
			{
				print[4][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i]).getFront();
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
				print[(i + 1) % 4][1][0] = this->getEdge(pEdge[i + 4]).getFront();
			}

			//�׷��� ���� ��� ���ΰ� �ݴ��� ��쿡 �ش�
			else
			{
				print[(i + 1) % 4][1][0] = this->getEdge(pEdge[i + 4]).getTop();
				print[i][1][2] = this->getEdge(pEdge[i + 4]).getFront();
			}


			//8~11�� ������ ���� ������ ����� ���� ���Ѵٸ�
			if (this->getEdge(pEdge[i + 8]).getDir() == YELLOW)
			{
				//�� �ڳ��� top(=side[0], dir)�� ��� ���� ������ ��ġ�� �ش�
				print[5][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getTop();
				//�� �ڳ��� front(=side[1])�� �� ������ 1�� 2���� �ش�
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getFront();
			}

			//�׷��� ���� ��� ���ΰ� �ݴ��� ��쿡 �ش�
			else
			{
				print[5][eTemp[i][0]][eTemp[i][1]] = this->getEdge(pEdge[i + 8]).getFront();
				print[i][0][1] = this->getEdge(pEdge[i + 8]).getTop();
			}

			//���� �������� ���� ���� eTemp[0]�� eTemp[2]�� �� �κ��� �ٽ� �ٲ��ش�
			swap(eTemp[0][0], eTemp[2][0]);


			//0~3�� �ڳʿ� ���� ������ ��� ���� ���Ѵٸ�
			if (this->getCorner(pCorner[i]).getDir() == WHITE)
			{
				//�� �ڳ��� top(=side[0], dir)�� ��� ���� ������ ��ġ�� �ش�
				print[4][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 1���� �ش�
				print[(i + 1) % 4][2][0] = this->getCorner(pCorner[i]).getLeft();
				//�� �ڳ��� right(=side[2])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 3���� �ش�
				print[i][2][2] = this->getCorner(pCorner[i]).getRight();
			}

			//�׷��� �ʰ� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i]).getDir() == (i + 1) % 4)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 1���� �ش�
				print[(i + 1) % 4][2][0] = this->getCorner(pCorner[i]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 3���� �ش�
				print[i][2][2] = this->getCorner(pCorner[i]).getLeft();
				//�� �ڳ��� right(=side[2])�� ��� ���� ������ ��ġ�� �ش�
				print[4][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getRight();
			}

			//�׷��� �ʰ� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i]).getDir() == i)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 3���� �ش�
				print[i][2][2] = this->getCorner(pCorner[i]).getTop();
				//�� �ڳ��� left(=side[1])�� ��� ���� ������ ��ġ�� �ش�
				print[4][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i]).getLeft();
				//�� �ڳ��� right(=side[2])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 1���� �ش�
				print[(i + 1) % 4][2][0] = this->getCorner(pCorner[i]).getRight();
			}

			//cTemp[0] = {0, 2}�̰� cTemp[1] = {2, 2}�̴� ������ �� �κи� �ٲ��ش�
			swap(cTemp[0][0], cTemp[1][0]);
			//cTemp[2] = {2, 0}�̰� cTemp[3] = {0, 0}�̴� ������ �� �κи� �ٲ��ش�
			swap(cTemp[2][0], cTemp[3][0]);

			//4~7�� �ڳʿ� ���� ������ ����� ���� ���Ѵٸ�
			if (this->getCorner(pCorner[i + 4]).getDir() == YELLOW)
			{
				//�� �ڳ��� top(=side[0], dir)�� ����� ���� ������ ��ġ�� �ش�
				print[5][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 1���� �ش�
				print[(i + 1) % 4][0][0] = this->getCorner(pCorner[i + 4]).getRight();
				//�� �ڳ��� right(=side[2])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 3���� �ش�
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getLeft();
			}

			//�׷��� �ʰ� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i + 4]).getDir() == (i + 1) % 4)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 3���� �ش�
				print[(i + 1) % 4][0][0] = this->getCorner(pCorner[i + 4]).getTop();
				//�� �ڳ��� left(=side[1])�� ����� ���� ������ ��ġ�� �ش�
				print[5][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getLeft();
				//�� �ڳ��� right(=side[2])�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 1���� �ش�
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getRight();
			}
			
			//�׷��� �ʰ� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� ���Ѵٸ�
			else if (this->getCorner(pCorner[i + 4]).getDir() == i)
			{
				//�� �ڳ��� top(=side[0], dir)�� �� ���� ��(�� ORANGE-BLUE������ �� ū ��) ���� 3�� 1���� �ش�
				print[i][0][2] = this->getCorner(pCorner[i + 4]).getTop();
				//�� �ڳ��� left(=side[1])�� �� ū ��(�� ORANGE-BLUE������ �� ���� ��) ���� 3�� 3���� �ش�
				print[(i + 1) % 4][0][0] = this->getCorner(pCorner[i + 4]).getLeft();
				//�� �ڳ��� right(=side[2])�� ����� ���� ������ ��ġ�� �ش�
				print[5][cTemp[i][0]][cTemp[i][1]] = this->getCorner(pCorner[i + 4]).getRight();
			}
			
			//���� �������� ���� ���� cTemp[0]�� cTemp[1]�� �� �κ�, cTemp[2]�� cTemp[3]�� �� �κ��� �ٽ� �ٲ��ش�
			swap(cTemp[0][0], cTemp[1][0]);
			swap(cTemp[2][0], cTemp[3][0]);
		}

		int i = print[0][2][0];

		//����� ���� �� ���ϴ� �ּ��� �°� ���
		for (int i = 0; i < 3; i++) cout << "��������" << col[print[5][i][0]] << col[print[5][i][1]] << col[print[5][i][2]] << endl;
		cout << endl;

		//���� ����� �� ���ϴ� �ּ��� �°� ���
		for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 4; j++) cout << col[print[(j + 3) % 4][i][0]] << col[print[(j + 3) % 4][i][1]] << col[print[(j + 3) % 4][i][2]] << "��";

				cout << endl;
			}

		cout << endl;

		//��� ���� �� ���ϴ� �ּ��� �°� ���
		for (int i = 0; i < 3; i++) cout << "��������" << col[print[4][i][0]] << col[print[4][i][1]] << col[print[4][i][2]] << endl;
		cout << endl << endl;
	}

	void basic_step1()
	{
		//0~3�� ������ ���ڸ��� ��ġ��Ų�� (ũ�ν�)
		for (int i = 0; i < 4; i++)
		{
			//i���� ������ ��� �鿡�� ������ �߰� �� i���� 0�� ��ġ�� ������ �̵�
			for (int j = 0; j < 4; j++)
			{
				//j�� i�� ��, �� Ȯ���� ���� i���� ���� ��Ƽ��
				if (i == j) continue;

				//���� j �鿡 i��° ������ �߰��ߴٸ�
				if (if_edgeIn(this->getEdge(i).getPos(), this->getColor(j)))
				{
					this->setFront(j);

					//0�� ��ġ�� ���
					if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(0))
					{
						//UUUU...
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) this->U();
					}

					//j���� 1�� ��ġ�� ���
					else if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(1))
					{
						//F' UUUU... F
						this->Fp();
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) this->U();
						this->F();
					}

					//j���� 2�� ��ġ�� ���
					else if (this->getEdge(i).getPos() == this->getColor(this->getFront()).getEdge(2))
					{
						//F2 UUUU... F2
						this->F2();
						while (this->getEdge(i).getPos() != this->getColor(i).getEdge(0)) this->U();
						this->F2();
					}

					break;
				}
			}

			this->setFront(i);

			//0~3�� ������ dir�� color[i]�� ����Ű�� ���� ���� ��(�ùٸ� ��)
			if (this->getEdge(i).getDir() != this->getColor(this->getFront()).getSelf())
			{
				//���� n�� ȸ������ ������ �ùٸ� ��ġ�� ���´�
				while (this->getEdge(i).getPos() != this->getColor(this->getFront()).getEdge(2)) this->F();
			}

			//0~3�� ������ dir�� color[i]�� ����Ű�� ���� ��(�ٲ�� �� ��)
			else
			{
				//���� n�� ȸ������ ũ�ν� ������ ����� �� �ִ� ��ġ�� �д�
				while (this->getEdge(i).getPos() != this->getColor(this->getFront()).getEdge(0)) this->F();
				//U' R' F R
				this->Up(); this->Rp(); this->F(); this->R();
			}
		}
	}
	void basic_step2()
	{
		//1~3�� �ڳʸ� ���ڸ��� ��ġ��Ų��
		for (int i = 0; i < 4; i++)
		{
			//�켱 �� �ڳʰ� 1���� �����ִ��� Ȯ��
			for (int j = 0; j < 4; j++)
			{
				//���� �ڳʰ� �߸��� 1�� ��ġ�� �����ְų�
				//������ �߸��� ���·� �������� ���
				if (this->getCorner(i).getPos() == this->getColor(j).getCorner(1))
				{
					//�ùٸ� ���, �ùٸ� ������ ��� ������
					if ((i == j) && (this->getCorner(i).getDir() == WHITE)) break;

					this->setFront(j);

					//F' U F
					Fp(); U(); F();
					break;
				}
			}

			this->setFront(i);
		
			//�� �ڳʰ� 1���� ���ų� 1������ �������� 3���� ���� ����
			//i�� �ڳʸ� ������ ����� �� �ִ� ��ġ�� �̵�
			while (this->getCorner(i).getPos() != this->getColor(this->getFront()).getCorner(0)) this->U();

			//i�� �ڳ��� ������ i�� ���� ����Ű�� �ִٸ�
			if (this->getCorner(i).getDir() == this->getFront())
			{
				//U R U' R'
				this->U(); this->R(); this->Up(); this->Rp();
			}

			//i�� �ڳ��� ������ i+1�� ���� ����Ű�� �ִٸ�
			else if (this->getCorner(i).getDir() == (this->getFront() + 1) % 4)
			{
				//R U R'
				this->R(); this->U(); this->Rp();
			}

			//i�� �ڳ��� ������ ���� ����Ű�� �ִٸ�
			else if (this->getCorner(i).getDir() == YELLOW)
			{
				//F' L' U2 L F'
				this->Fp(); this->Lp(); this->U2(); this->L(); this->F();
			}
		}
	}
};

int main()
{
	class three_by_three cube;

	//Ȯ�ο� ��ũ����
	cube.R(); cube.D(); cube.R2(); cube.Up(); cube.Fp();
	cube.U(); cube.Rp(); cube.Lp(); cube.F(); cube.Bp();
	cube.Lp(); cube.D2(); cube.Up(); cube.Rp(); cube.U();
	cube.F2(); cube.U2(); cube.L2(); cube.R2(); cube.Bp();
	cube.Dp(); cube.U();  cube.D2(); cube.Lp(); cube.R();

	cube.basic_step1();
	cube.basic_step2();
	cube.visualize();

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