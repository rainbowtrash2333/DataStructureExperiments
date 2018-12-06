#include "pch.h"
#include <String>
#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include <windows.h>

using namespace std;

typedef enum { black, gray, yellow, blue, red, orange, purple }Color;

typedef struct {
	Color color;
	int row;
	int col;

}Grid;

typedef struct GridNode {
	Grid data;
	struct GridNode* next;
}GridNode;

class GridList {
private:
	GridNode* head;
	GridNode* tail;
	int length;
public:
	GridList() {
		head = tail = new GridNode;
		length = 0;
	}

	GridNode*  getHead() {
		return this->head;
	}

	int getLength() {
		return this->length;
	}
	void addNode(Grid data) {
		tail->data = data;
		length++;
		tail->next = new GridNode;
		if (tail->next == NULL) {
			cout << "next分配失败" << endl;
			exit(1);

		}
		//test
		//cout << "addNode row col " << data.row << " " << data.col << endl;

		tail = tail->next;
	}

	bool isEmpty() {
		return (length == 0);
	}

	Grid getData() {
		Grid g = head->data;
		head = head->next;
		length--;
		return g;
	}

	Grid getDataRandomly() {
		srand((unsigned)time(NULL));
		int n = (rand() % length);
		Grid g;
	
		for (int i = 0; i <= n; i++)
		{
			g = getData();
			addNode(g);
		}
		g = getData();
		return g;
	}
};

class Maze {
private:
	int row;
	int col;
	int numOfYellow;
	Grid **grids;
	GridList BlueList;
	GridList RedList;
	Grid *end;
	Grid * person;

public:
	bool isWin;
	Maze(int row, int col) {
		isWin = false;
		//动态分配二维数组
		this->col = col;
		this->row = row;
		numOfYellow = 0;
		grids = new Grid *[row + 2];
		if (grids == NULL) {
			cout << "grids 内存失败" << endl;
			exit(1);
		}

		for (int i = 0; i < this->row + 2; i++) {
			grids[i] = new Grid[this->col + 2];
			if (grids[i] == NULL) {
				cout << "grids[i] 内存失败" << endl;
			}
		}
		//初始化数据
		for (int i = 0; i < row + 2; i++)
		{
			for (int j = 0; j < col + 2; ++j) {
				grids[i][j].row = i;
				grids[i][j].col = j;
				if (i == 0 || i == row + 1 || j == 0 || j == col + 1) {
					grids[i][j].color = black;
				}

				else if ((i % 2 == 1) && (j % 2 == 1)) {
					grids[i][j].color = yellow;
					numOfYellow++;
				}



				else {
					grids[i][j].color = gray;
					;
				}
			}
		}
		create();

	}

	void create() {
		grids[1][1].color = red;
		numOfYellow--;
		Grid *g;
		g = &grids[1][1];
		int s = 0;
		while (numOfYellow != 0) {
			
			enBlue(g);

			g = enRed(BlueList.getDataRandomly());
			
			if (!check(g)) {
				cout << "g溢出" << endl;
				cout << s++ << "row col" << g->row << " " << g->col << endl;
			}
		}
		person = &grids[1][0];
		person->color = orange;
		end = &grids[row][col + 1];
		grids[row][col].color = purple;
		grids[row-1][col].color = purple;
		grids[row-1][col+1].color = purple;
		 
		end->color = purple;
	}

	bool check(Grid *g) {
		if (g == NULL) {
			return true;
		}
		int row = g->row;
		int col = g->col;
		if (row < this->row+1 && row > 0) {
			if (col < this->col + 1 && col > 0) {
				return true;
			}
		}
		return false;
	}

	void addBlue(Grid *g) {

		if (check(g)) {
			if (g->color == gray) {
				g->color = blue;
				BlueList.addNode(*g);
			}
		}
	}

	// 输入红色，标记蓝色
	void enBlue(Grid* g) {
		if (g != NULL)
		{
			int row = g->row;
			int col = g->col;
			Grid * foo;
			foo= &grids[row][col - 1];
			addBlue(foo);
			foo = &grids[row][col + 1];
			addBlue(foo);
			foo = &grids[row + 1][col];
			addBlue(foo);
			foo = &grids[row - 1][col];
			addBlue(foo);

		}

	}



	Grid* enRed(Grid g) {


		//int row = g.row;
		//int col = g.col;

		//return addRed(&grids[row][col]);
		int row = g.row;
		int col = g.col;
		if (row != this->row) {
			grids[row][col].color = red;
			if (grids[row - 1][col].color == red && grids[row + 1][col].color == red)
			{
				grids[row][col].color = gray;
				return NULL;
			}

			else if (grids[row + 1][col].color == red && grids[row - 1][col].color == yellow)
			{
				grids[row - 1][col].color = red;
				numOfYellow--;
				return &grids[row - 1][col];
			}
			else if (grids[row - 1][col].color == red && grids[row + 1][col].color == yellow)
			{
				grids[row + 1][col].color = red;
				numOfYellow--;
				return &grids[row + 1][col];
			}


		}
		if (g.col != this->col && g.col != 1) {
			grids[row][col].color = red;
			if (grids[row][col - 1].color == red && grids[row][col + 1].color == red)
			{
				grids[row][col].color = gray;
				return NULL;
			}

			else if (grids[row][col + 1].color == red && grids[row][col - 1].color == yellow)
			{
				numOfYellow--;
				grids[row][col - 1].color = red;
				return &grids[row][col - 1];

			}
			else if (grids[row][col - 1].color == red && grids[row][col + 1].color == yellow)
			{
				numOfYellow--;
				grids[row][col + 1].color = red;
				return &grids[row][col + 1];
			}
		}
		return NULL;
	}

	void show() {
		HANDLE  hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//光标移动到( x, y )
		COORD pos;
		pos.X = 0;
		pos.Y = 0;
		SetConsoleCursorPosition(hConsole, pos);
		// 隐藏光标 
		CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
		for (int i = 0; i < row + 2; i++)
		{
			for (int j = 0; j < col + 2; ++j) {
				switch (grids[i][j].color)
				{
				case orange:
					SetConsoleTextAttribute(hConsole, 187);
					cout << "*";
					break;
				
				case purple:
					SetConsoleTextAttribute(hConsole,153 );
					cout << "#";
					break;
				case black:
					SetConsoleTextAttribute(hConsole, 77);
					cout << "#";
					break;
				case gray:
					SetConsoleTextAttribute(hConsole, 77);
					cout << "#";
					break;
				case blue:
					SetConsoleTextAttribute(hConsole, 77);
					cout << "#";
					break;
				case red:
					SetConsoleTextAttribute(hConsole, 126);
					cout << "#";
					break;
				default:
					break;
				}
			}
			SetConsoleTextAttribute(hConsole, 1);

			cout << endl;
		}
	}

	bool move(Grid *g) {
		if (g->color == red) {
			person->color = red;
			person = g;
			person->color = orange;
			return true;
		}
		if (g->color == purple) {
			isWin = true;
		}
		return false;
	}

	void move2(char input) {
		switch (input)
		{
		case 'w':
			move(&(grids[person->row - 1][person->col]));
			break;
		case 's':
			move(&(grids[person->row + 1][person->col]));
			break;
		case 'a':
			move((person - 1));
			break;
		case 'd':
			move((person + 1));
			break;
		default:
			break;
		}
	}

	void updata() {
		char input;
		while (_kbhit()) {
			input = _getch();
			switch (input)
			{
			case 'w':
				move(&(grids[person->row-1][person->col]));
				break;
			case 's':
				move(&(grids[person->row + 1][person->col]));
				break;
			case 'a':
				move((person - 1));
				break;
			case 'd':
				move((person + 1));
				break;
			default:
				break;
			}
		}
	}

	void automatic(char& foo, char& bar) {
		//char foo = 'd';
		//char bar = 'w';
		bool flag;
		switch (foo)
		{
		case 'w':
			if (move(&(grids[person->row - 1][person->col]))) {
				foo = 'd';
				bar = 'w';
			}
			else {
				if (!move((person - 1))) {
					foo = 'a';
					bar = 's';
				}
			}
			
			break;
		case 's':
			 flag = move(&(grids[person->row + 1][person->col]));
			//cout << flag << endl;
			//system("pause");
			if (flag) {
				foo = 'a';
				bar = 's';
			}
			else {
				if (!move((person + 1))) {
					foo = 'd';
					bar = 'w';
				}
			}
			break;
		case 'a':
			if (move((person - 1))) {
				foo = 'w';
				bar = 'a';
			}
			else {
				if (!move(&(grids[person->row + 1][person->col]))) {
					foo = 's';
					bar = 'd';
				}
			}
			break;
		case 'd':
			if (move((person + 1))) {
				foo = 's';
				bar = 'd';
			}
			else {
				if (!move(&(grids[person->row - 1][person->col]))) {
					foo = 'w';
					bar = 'a';
				}
			}
			break;
		default:
			break;
		}


	}
};


int main()
{
	system("COLOR 07");
	int row, col;
	cout << "输入行 列:";
	
	cin >> row >> col;

	Maze maze(row, col);
	cout << "选择模式:\n\t 1.自动\n\t 2.手动\n";
	int input;
	cin >> input;
	char foo = 'd';
	char bar = 's';
	if (input == 1) {
		while (!maze.isWin) {
			maze.show();
			maze.automatic(foo, bar);
			Sleep(10);
		}
	}
	else {
		while (!maze.isWin) {
			maze.show();
			maze.updata();
		}
	}
	cout << "game over" << endl;
}




//
//#include <windows.h>   // WinApi header
//
//using namespace std;    // std::cout, std::cin

//int main()
//{
//	HANDLE  hConsole;
//	int k;
//
//	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	// you can loop k higher to see more color choices
//	for (k = 1; k < 255; k++)
//	{
//		// pick the colorattribute k you want
//		SetConsoleTextAttribute(hConsole, k);
//		cout << k << " I want to be nice today!" << endl;
//	}
//
//	cin.get(); // wait
//	return 0;
//}
