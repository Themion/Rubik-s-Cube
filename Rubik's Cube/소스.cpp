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

		//index1 ���� index2��° �̿���
		int getBy(int index) { return this->by[index]; }

		//index1 ���� index2��° ���� ���
		int getEdge(int index) { return this->edge[index]; }

		//index1 ���� index2��° �ڳ� ���
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
		//�ڳ� ����� ��ġ
		int pos;
		//side[0]�� �ִ� ��
		int dir;
		//�ڳ� ����� �� ��
		//0 : ����, 1 : �޸�, 2 : ������
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
		//by[color] �鿡 ������ �� �̿� ���� ��
		int by[6][4] = { {5, 1, 4, 3}, {5, 2, 4, 0}, {5,  3, 4, 1}, {5,  0, 4, 2}, {0, 1, 2, 3}, {2,  1, 0, 3} };
		//by[color] �鿡 �����ϴ� �� ���� ���
		int edge[6][4] = { {8, 4, 0, 7}, {9, 5, 1, 4}, {10, 6, 2, 5}, {11, 7, 3, 6}, {0, 1, 2, 3}, {10, 9, 8, 11} };
		//by[color] �鿡 �����ϴ� �� �ڳ� ���
		int corner[6][4] = { {4, 0, 3, 7}, {5, 1, 0, 4}, {6,  2, 1, 5}, {7,  3, 2, 6}, {0, 1, 2, 3}, {5,  4, 7, 6} };

		for (int i = 0; i < 6; i++) color[i] = Color(by[i], edge[i], corner[i]);
	}
	
	void CW(int target)
	{
		//���� ����
		int temp, index = 0;
		class edgePiece **tEdge = new edgePiece*[4];
		class cornerPiece **tCorner = new cornerPiece*[4];


		//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
		for (int i = 0; i < 4; i++)
		{
			//���� �� ���� ����� ��ġ�� ����
			temp = color[target].getEdge(i);
			for (int j = 0; j < 12; j++)
			{
				//�ش� ��ġ�� �����ϴ� ���� ����� ã�Ҵٸ�
				if (temp == edge[j].getPos())
				{
					//����Ʈ�� �ش� ���� ����� �߰�
					tEdge[index++] = &edge[j];
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
			temp = color[target].getCorner(i);
			for (int j = 0; j < 8; j++)
			{
				//�ش� ��ġ�� �����ϴ� �ڳ� ����� ã�Ҵٸ�
				if (temp == corner[j].getPos())
				{
					//����Ʈ�� �ش� �ڳ� ����� �߰�
					tCorner[index++] = &corner[j];
					break;
				}
			}
			if (index == 4) break;
		}


		//���� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ� ���� ���� ����ų ��(i + 1��°)���� ����
			if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 1) % 4));
			//��ġ�� �� ĭ �ű��
			tEdge[i]->setPos(color[target].getEdge((i + 1) % 4));
		}


		//�ڳ� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ�
			if (tCorner[i]->getDir() != target)
			{
				//���� ����Ű�� ���� �Ǵ��Ͽ� ���� ���� ����ų ��(i + 1��° Ȥ�� �� + 1��°)���� ����
				if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 1) % 4));
				else tCorner[i]->setDir(color[target].getBy((i + 2) % 4));
			}
			//��ġ�� �� ĭ �ű��
			tCorner[i]->setPos(color[target].getCorner((i + 1) % 4));
		}
	}
	void ACW(int target)
	{
		//���� ����
		int temp, index = 0;
		class edgePiece **tEdge = new edgePiece*[4];
		class cornerPiece **tCorner = new cornerPiece*[4];

		//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
		for (int i = 0; i < 4; i++)
		{
			//���� �� ���� ����� ��ġ�� ����
			temp = color[target].getEdge(i);
			for (int j = 0; j < 12; j++)
			{
				//�ش� ��ġ�� �����ϴ� ���� ����� ã�Ҵٸ�
				if (temp == edge[j].getPos())
				{
					//����Ʈ�� �ش� ���� ����� �߰�
					tEdge[index++] = &edge[j];
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
			temp = color[target].getCorner(i);
			for (int j = 0; j < 8; j++)
			{
				//�ش� ��ġ�� �����ϴ� �ڳ� ����� ã�Ҵٸ�
				if (temp == corner[j].getPos())
				{
					//����Ʈ�� �ش� �ڳ� ����� �߰�
					tCorner[index++] = &corner[j];
					break;
				}
			}
			if (index == 4) break;
		}


		//���� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//������ �ش� ���� ������ �ʴ´ٸ� ���� ���� ����ų ��(i + 1��°)���� ����
			if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
			//��ġ�� �� ĭ �ű��
			tEdge[i]->setPos(color[target].getEdge((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
		}


		//�ڳ� ���� ��ġ�� ������ ����
		for (int i = 0; i < 4; i++)
		{
			//�켱 ������ �ش� ���� ������ �ʴ´ٸ�
			if (tCorner[i]->getDir() != target)
			{
				//���� ����Ű�� ���� �Ǵ��Ͽ� ���� ���� ����ų ��(i - 1��° Ȥ�� �� + 1��°)���� ����
				if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
				else tCorner[i]->setDir(color[target].getBy(i));
			}
			//��ġ�� �� ĭ �ű��
			tCorner[i]->setPos(color[target].getCorner((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
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

	//index1 ���� index2��° �̿���
	int getBy(int index) { return this->by[index]; }

	//index1 ���� index2��° ���� ���
	int getEdge(int index) { return this->edge[index]; }

	//index1 ���� index2��° �ڳ� ���
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
	//�ڳ� ����� ��ġ
	int pos;
	//side[0]�� �ִ� ��
	int dir;
	//�ڳ� ����� �� ��
	//0 : ����, 1 : �޸�, 2 : ������
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
	//by[color] �鿡 ������ �� �̿� ���� ��
	int by[6][4] = { {5, 1, 4, 3}, {5, 2, 4, 0}, {5,  3, 4, 1}, {5,  0, 4, 2}, {0, 1, 2, 3}, {2,  1, 0, 3} };
	//by[color] �鿡 �����ϴ� �� ���� ���
	int edge[6][4] = { {8, 4, 0, 7}, {9, 5, 1, 4}, {10, 6, 2, 5}, {11, 7, 3, 6}, {0, 1, 2, 3}, {10, 9, 8, 11} };
	//by[color] �鿡 �����ϴ� �� �ڳ� ���
	int corner[6][4] = { {4, 0, 3, 7}, {5, 1, 0, 4}, {6,  2, 1, 5}, {7,  3, 2, 6}, {0, 1, 2, 3}, {5,  4, 7, 6} };

	for (int i = 0; i < 6; i++) color[i] = Color(by[i], edge[i], corner[i]);
}

void CW(int target)
{
	//���� ����
	int temp, index = 0;
	class edgePiece **tEdge = new edgePiece*[4];
	class cornerPiece **tCorner = new cornerPiece*[4];


	//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
	for (int i = 0; i < 4; i++)
	{
		//���� �� ���� ����� ��ġ�� ����
		temp = color[target].getEdge(i);
		for (int j = 0; j < 12; j++)
		{
			//�ش� ��ġ�� �����ϴ� ���� ����� ã�Ҵٸ�
			if (temp == edge[j].getPos())
			{
				//����Ʈ�� �ش� ���� ����� �߰�
				tEdge[index++] = &edge[j];
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
		temp = color[target].getCorner(i);
		for (int j = 0; j < 8; j++)
		{
			//�ش� ��ġ�� �����ϴ� �ڳ� ����� ã�Ҵٸ�
			if (temp == corner[j].getPos())
			{
				//����Ʈ�� �ش� �ڳ� ����� �߰�
				tCorner[index++] = &corner[j];
				break;
			}
		}
		if (index == 4) break;
	}


	//���� ���� ��ġ�� ������ ����
	for (int i = 0; i < 4; i++)
	{
		//������ �ش� ���� ������ �ʴ´ٸ� ���� ���� ����ų ��(i + 1��°)���� ����
		if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 1) % 4));
		//��ġ�� �� ĭ �ű��
		tEdge[i]->setPos(color[target].getEdge((i + 1) % 4));
	}


	//�ڳ� ���� ��ġ�� ������ ����
	for (int i = 0; i < 4; i++)
	{
		//������ �ش� ���� ������ �ʴ´ٸ�
		if (tCorner[i]->getDir() != target)
		{
			//���� ����Ű�� ���� �Ǵ��Ͽ� ���� ���� ����ų ��(i + 1��° Ȥ�� �� + 1��°)���� ����
			if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 1) % 4));
			else tCorner[i]->setDir(color[target].getBy((i + 2) % 4));
		}
		//��ġ�� �� ĭ �ű��
		tCorner[i]->setPos(color[target].getCorner((i + 1) % 4));
	}
}
void ACW(int target)
{
	//���� ����
	int temp, index = 0;
	class edgePiece **tEdge = new edgePiece*[4];
	class cornerPiece **tCorner = new cornerPiece*[4];

	//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
	for (int i = 0; i < 4; i++)
	{
		//���� �� ���� ����� ��ġ�� ����
		temp = color[target].getEdge(i);
		for (int j = 0; j < 12; j++)
		{
			//�ش� ��ġ�� �����ϴ� ���� ����� ã�Ҵٸ�
			if (temp == edge[j].getPos())
			{
				//����Ʈ�� �ش� ���� ����� �߰�
				tEdge[index++] = &edge[j];
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
		temp = color[target].getCorner(i);
		for (int j = 0; j < 8; j++)
		{
			//�ش� ��ġ�� �����ϴ� �ڳ� ����� ã�Ҵٸ�
			if (temp == corner[j].getPos())
			{
				//����Ʈ�� �ش� �ڳ� ����� �߰�
				tCorner[index++] = &corner[j];
				break;
			}
		}
		if (index == 4) break;
	}


	//���� ���� ��ġ�� ������ ����
	for (int i = 0; i < 4; i++)
	{
		//������ �ش� ���� ������ �ʴ´ٸ� ���� ���� ����ų ��(i + 1��°)���� ����
		if (tEdge[i]->getDir() != target) tEdge[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
		//��ġ�� �� ĭ �ű��
		tEdge[i]->setPos(color[target].getEdge((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
	}


	//�ڳ� ���� ��ġ�� ������ ����
	for (int i = 0; i < 4; i++)
	{
		//�켱 ������ �ش� ���� ������ �ʴ´ٸ�
		if (tCorner[i]->getDir() != target)
		{
			//���� ����Ű�� ���� �Ǵ��Ͽ� ���� ���� ����ų ��(i - 1��° Ȥ�� �� + 1��°)���� ����
			if (tCorner[i]->getDir() == color[target].getBy(i)) tCorner[i]->setDir(color[target].getBy((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
			else tCorner[i]->setDir(color[target].getBy(i));
		}
		//��ġ�� �� ĭ �ű��
		tCorner[i]->setPos(color[target].getCorner((i + 3) % 4)); //((i + 3) % 4) �� ((i - 1) + 4) % 4�� ����
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