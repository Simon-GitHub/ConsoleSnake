#pragma once
#include"Console.h"
#include<deque>
#include<vector>
using std::deque;

class CSnake
{
	struct Point
	{
		int x;
		int y;
		Point(int x_, int y_) : x{ x_ }, y{ y_ }
		{}
		Point()
		{}
		bool operator==(Point point) const
		{
			return x == point.x && y == point.y;
		}
	};

private:
	deque<Point> m_snake;		//�����������ÿ���������
	Direction m_direction;		//�ߵ�ǰǰ������
	Point m_food;				//ʳ�����ڵ�����
	Point m_last_tail;			//������һ��λ��ʱβ��������
	
	int m_score{ 0 };
	int m_level{ 1 };

public:
	CSnake();
	void SnakeForward();	//��ǰ��
	bool GaneOver() const;		//��Ϸ�����ж�
	void DrawSnake() const;		//����������
	void ClearSnake() const;	//����������
	void MoveSnake(Direction direction);
	bool CreateFood();		//����ʳ��
	void DrawFood();		//����ʳ��
	void ClearFood();		//����ʳ��
	bool SnakeHitFood();	//�ж����Ƿ���ײ��ʳ��
	void SnakeEatFood();	//�߳Ե�ʳ��
	int GetIntervalTime() const;	//���ݵ�ǰ�ȼ�������ʱ�䣨��λ��ms��

	void DrawFram() const;	//���Ʊ߿�
	void ShowInfo() const;	//��ʾ��Ϸ��Ϣ

private:
	bool IsPiontInSnake(const Point& point);		//�ж�һ�����Ƿ�λ���ߵ�������

};

CSnake::CSnake()
{
	system("mode con:cols=64 lines=27");
	m_snake.clear();
	m_snake.emplace_back(10, 9);
	m_snake.emplace_back(10, 10);
	m_snake.emplace_back(10, 11);
	m_direction = UP;
	CreateFood();
}

void CSnake::SnakeForward()
{
	Point point;
	switch (m_direction)
	{
	case UP:
		point.x = m_snake.front().x;
		point.y = m_snake.front().y - 1;
		break;
	case DOWN:
		point.x = m_snake.front().x;
		point.y = m_snake.front().y + 1;
		break;
	case LEFT:
		point.x = m_snake.front().x - 1;
		point.y = m_snake.front().y;
		break;
	case RIGHT:
		point.x = m_snake.front().x + 1;
		point.y = m_snake.front().y;
		break;
	default:
		break;
	}
	m_snake.push_front(point);
	m_last_tail = m_snake.back();	//����β��������
	m_snake.pop_back();
}

void CSnake::DrawSnake() const
{
	for (auto& point : m_snake)
	{
		if (point == m_snake.front())
			PrintCell(point.x + BOARD_X, point.y + BOARD_Y, RED);
		else
			PrintCell(point.x + BOARD_X, point.y + BOARD_Y, CYAN);
	}
}

void CSnake::ClearSnake() const
{
	for (auto& point : m_snake)
	{
		ClearString(point.x + BOARD_X, point.y + BOARD_Y, 2);
	}
}

void CSnake::MoveSnake(Direction direction)
{
	switch (direction)
	{
	case UP:
		if (m_direction == DOWN) return;
		break;
	case DOWN:
		if (m_direction == UP) return;
		break;
	case LEFT:
		if (m_direction == RIGHT) return;
		break;
	case RIGHT:
		if (m_direction == LEFT) return;
		break;
	}
	m_direction = direction;
	SnakeForward();
}

bool CSnake::CreateFood()
{
	if (m_snake.size() >= WIDTH*HIGHT)		//�������峤�ȴ��ڻ���ڽ��������ʱ�޷�����ʳ�����false
		return false;
	bool food_illegal;		//ʳ��λ���ǷǷ���־

	int cell_num = WIDTH * HIGHT - m_snake.size();		//�Ϸ���ʳ��λ������
	//����ʳ��λ�õ�����
	SYSTEMTIME current_time;
	GetLocalTime(&current_time);			//��ȡ��ǰʱ��
	srand(current_time.wMilliseconds);		//�õ�ǰʱ��ĺ��������ò��������������
	int food_index = rand() % cell_num;
	int cur_index = -1;

	//������õĸ����е�food_index�����ӵľ���λ��
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HIGHT; j++)
		{
			if (!IsPiontInSnake(Point(i, j)))
				cur_index++;
			if (cur_index >= food_index)
			{
				m_food = Point(i, j);
				return true;
			}
		}
	}

	return false;
	//while (true)
	//{
	//	food_illegal = false;
	//	m_food.x = rand() % WIDTH;
	//	m_food.y = rand() % HIGHT;
	//	for (auto& point : m_snake)
	//	{
	//		if (point == m_food)
	//		{
	//			food_illegal = true;	//�����ǰ�����������κ�һ������ʳ���λ�ã���ʳ��λ�ò��Ϸ�
	//			break;
	//		}
	//	}
	//	if (!food_illegal) break;
	//}
	//return true;
}

void CSnake::DrawFood()
{
	PrintCell(m_food.x + BOARD_X, m_food.y + BOARD_Y, YELLOW);
}

void CSnake::ClearFood()
{
	ClearString(m_food.x + BOARD_X, m_food.y + BOARD_Y, 2);
}

bool CSnake::SnakeHitFood()
{
	return m_snake.front() == m_food;
}

void CSnake::SnakeEatFood()
{
	m_snake.push_back(m_last_tail);		//�Ե�ʳ����������峤��
	m_score ++;
	m_level = m_score / 20 + 1;
}

inline int CSnake::GetIntervalTime() const
{
	switch (m_level)
	{
	case 1: return 1000;
	case 2: return 800;
	case 3: return 650;
	case 4: return 500;
	case 5: return 400;
	case 6: return 320;
	case 7: return 250;
	case 8: return 190;
	default: return 150;
	}
}

bool CSnake::GaneOver() const
{
	return m_snake.front().x >= WIDTH || m_snake.front().x < 0 || m_snake.front().y >= HIGHT || m_snake.front().y < 0;
}

void CSnake::DrawFram() const
{
	//�������±߽�
	for(int i{ 0 }; i <= WIDTH+1; i++)
	{
		PrintString(L"��", i, BOARD_Y - 1, GRAY);
		PrintString(L"��", i, BOARD_Y + HIGHT, GRAY);
	}
	//�������ұ߽�
	for(int i{ BOARD_Y }; i < BOARD_Y + HIGHT; i++)
	{
		PrintString(L"��", BOARD_X - 1, i, GRAY);
		PrintString(L"��", BOARD_X + WIDTH, i, GRAY);
	}
}

void CSnake::ShowInfo() const
{
	PrintString(L"̰���� V0.1", 0, 0, WHITE);
	PrintString(L"�÷֣�", 0, 1, WHITE);
	PrintInt(m_score, 3, 1, CYAN);
	PrintString(L"�ȼ���", 6, 1, WHITE);
	PrintInt(m_level, 9, 1, CYAN);
}

bool CSnake::IsPiontInSnake(const Point & point)
{
	for (auto& a_point : m_snake)
	{
		if (a_point == point)
		{
			return true;
		}
	}
}
