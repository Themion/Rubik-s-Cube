#include <iostream>

using namespace std;

constexpr auto BLUE = 0;
constexpr auto RED = 1;
constexpr auto GREEN = 2;
constexpr auto ORANGE = 3;
constexpr auto WHITE = 4;
constexpr auto YELLOW = 5;

//ť���� �� ���� ��
int color[6] = { BLUE, RED, GREEN, ORANGE, WHITE, YELLOW };

class Cube
{
private:
	//by[color] �鿡 ������ �� �̿� ���� ��
	int by[6][4]     = { {5, 1, 4, 3}, {5, 2, 4, 0}, {5,  3, 4, 1}, {5,  0, 4, 2}, {0, 1, 2, 3}, {2,  1, 0, 3} };

	//by[color] �鿡 �����ϴ� �� ���� ���
	int edge[6][4]   = { {8, 4, 0, 7}, {9, 5, 1, 4}, {10, 6, 2, 5}, {11, 7, 3, 6}, {0, 1, 2, 3}, {10, 9, 8, 11} };

	//by[color] �鿡 �����ϴ� �� �ڳ� ���
	int corner[6][4] = { {4, 0, 3, 7}, {5, 1, 0, 4}, {6,  2, 1, 5}, {7,  3, 2, 6}, {0, 1, 2, 3}, {5,  4, 7, 6} };

public:
	Cube() {}

	//index1 ���� index2��° �̿���
	int getBy(int index1, int index2) { return this->by[index1][index2]; }

	//index1 ���� index2��° ���� ���
	int getEdge(int index1, int index2) { return this->edge[index1][index2]; }

	//index1 ���� index2��° �ڳ� ���
	int getCorner(int index1, int index2) { return this->corner[index1][index2]; }
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
	//���� ����
	int temp, index = 0;

	class edgePiece **tEdge = new edgePiece*[4];
	class cornerPiece **tCorner = new cornerPiece*[4];

	//ȸ���� �鿡 �ش�Ǵ� ���� ��� Ư��
	for (int i = 0; i < 4; i++)
	{
		//���� �� ���� ����� ��ġ�� ����
		temp = cube.getEdge(target, i);

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
		temp = cube.getCorner(target, i);

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
	//�ٲٴ��� ������ ����Ʈ�� 0�� ��ġ�� �̸� ����
	temp = tEdge[0]->getPos();

	//����Ʈ�� 3������ ���Ѵٸ� 3���� ��ġ�� �ٽ� �����ؾ� �Ѵ�
	for (int i = 0; i < 3; i++)
	{
		//�켱 ������ �ش� ���� ������ �ʴ´ٸ� ���� ���� ����ų ������ ����
		if (tEdge[i]->getDir() != target) tEdge[i]->setDir(cube.getBy(target, i + 1));
		//��ġ�� �� ĭ �ű��
		tEdge[i]->setPos(tEdge[i + 1]->getPos());
	}

	//for���� �ൿ�� �״�� ����
	if (tEdge[3]->getDir() != target) tEdge[3]->setDir(cube.getBy(target, 0));
	tEdge[3]->setPos(temp);

	//�ڳ� ���� ��ġ�� ������ ����
	//�ٲٴ��� ������ ����Ʈ�� 0�� ��ġ�� �̸� ����
	temp = tCorner[0]->getPos();

	//����Ʈ�� 3������ ���Ѵٸ� 3���� ��ġ�� �ٽ� �����ؾ� �Ѵ�
	for (int i = 0; i < 3; i++)
	{
		//�켱 ������ �ش� ���� ������ �ʴ´ٸ�
		if (tCorner[i]->getDir() != target)
		{
			//���� ����Ű�� ���� �Ǵ��Ͽ� ���� ���� ����Ű�� �����
			if(tCorner[i]->getDir() == cube.getBy(target, i)) tCorner[i]->setDir(cube.getBy(target, i + 1));
			else tCorner[i]->setDir(cube.getBy(target, (i + 2) % 4));
		}

		//��ġ�� �� ĭ �ű��
		tCorner[i]->setPos(tCorner[i + 1]->getPos());
	}

	//for���� �ൿ�� �״�� ����
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