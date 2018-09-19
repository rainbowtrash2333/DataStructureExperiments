/*           复数四则运算计算器         */
/*             开发平台：win10          */
/*              开发语言：C语言         */
/*                作者：Twikura         */

#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>
#include"experiment1.h"

//窗口大小
#define high 13

//全局变量 
complex_num num1;
complex_num num2;
complex_num result;
bool stop;
char  symbol;

//光标移动到( x, y ) 
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// 隐藏光标 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//初始化数据
void startup() {
	symbol = ' ';
	num1.a = 0;
	num1.b = 0;
	num2.a = 0;
	num2.b = 0;
	result.a = 0;
	result.b = 0;
	stop = false;
}

//输入复数，返回一个字符串
char* toString(complex_num num) {
	static char s[100];
	char bar1[55];
	char bar2[55];

	char foo[] = " + ";
	if (num.b < 0) {
		strcpy_s(foo, " - ");
		num.b = -num.b;
	}
	sprintf_s(bar1, "%f", num.a);
	sprintf_s(bar2, "%f", num.b);
	strcat_s(bar1, foo);
	strcat_s(bar1, bar2);
	strcat_s(bar1, "i");
	strcpy_s(s, bar1);
	return   s;
}

//readme
void readme() {
	printf("用法须知：\n");
	printf("1.必须吧输入法切换为英文，不然BUG跳到您怀疑人生；\n");
	printf("2.如果出现窗口跳动的情况，拉高控制台窗口的高度；\n");
	printf("3.键盘输入复数1的实部，空格后输入虚部，然后输入+-*/，接着即可输入复数2，最后回车或=输出结果\n");
	printf("4.支持的符号为/[0-9]|[+-=\\*\\/\\.]|(enter)|(space)/\n");
	printf("5.Copyright  Twikura@gmail.com\n");
}

//打印图形 
void show() {
	gotoxy(0, 0);
	HideCursor();
	for (int i = 0; i < high + 1; i++) {

		switch (i)
		{
		case 0:
			printf("复数四则运算器");
			break;
		case 2:
			printf("复数1：");
			break;
		case 3:
			printf("%s", toString(num1));
			break;
		case 5:
			printf("运算符：%c", symbol);
			break;
		case 7:
			printf("复数2：");
			break;
		case 8:
			printf("%s", toString(num2));
			break;
		case 10:
			printf("结果：");
			break;
		case 11:
			printf("%s", toString(result));
			break;
		default:
			break;
		}


		printf("\n");
	}
	readme();
}

//接受用户输入
bool hit() {
	char input;
	static int foobar = 1;
	static	bool isPoint = false;//是否输入小数点
	static	bool isSymbol = false;//是否输入算术符
	static	bool isSpace = false;//是否输入空格
	complex_num *num;
	while (_kbhit()) {
		input = _getch();

		if (isSymbol) {
			num = &num2;
		}
		else
			num = &num1;
		//有效输入
		//如果输入数字,写入num
		if (input == 0) break;
		if (input > 47 && input < 58) {
			//是否有输入小数点
			if (isPoint) {
				if (isSpace) {
					num->b = num->b + (input - '0') * pow(0.1, foobar++);
				}
				else {
					num->a = num->a + (input - '0') * pow(0.1, foobar++);
				}
			}
			else {
				if (isSpace) {
					num->b = num->b * 10.0 + (input - '0');

				}
				else {
					num->a = num->a * 10.0 + (input - '0');

				}
			}
		}
		
		else if (input == '.') {
			isPoint = true;
		}

		else if (input == ' ') {
			isPoint = false;
			isSpace = true;
			foobar = 1;
		}
		else if (input == '+' || input == '-' || input == '*' || input == '/') {
			isPoint = false;
			isSymbol = true;
			isSpace = false;
			symbol = input;
			foobar = 1;
		}
		//输入回车或=后，重置isPoint isSymbol, 返回true给其他方法计算
		else if (input == 13 || input == '=') {
			isPoint = false;
			isSymbol = false;
			isSpace = false;
			foobar = 1;
			return true;
		}
		//printf("isPoint=%d\tisSymbol=%d\n", isPoint, isSymbol);
		//printf("\n num1 %lf+%lfi", num1.a, num1.b);
		//printf("\n num2 %lf+%lfi\n", num2.a, num2.b);
	}
	return false;
}

//更新数据
void update() {
	bool isCalculate = hit();
	if (isCalculate) {
		switch (symbol)
		{
		case '+':
			add(&num1, &num2, &result);
			break;
		case '-':
			sub(&num1, &num2, &result);
			break;
		case '*':
			mul(&num1, &num2, &result);
			break;
		case '/':
			if (!div(&num1, &num2, &result)) {
				result.a = 0;
				result.b = 0;
			}
			break;
		default:
			break;
		}
		stop = true;
	}
}

int main() {
	startup();
	readme();
	printf("任意键继续");
	getchar();
	system("cls");
	while (!stop)
	{
		update();
		show();
	}
	return 0;
}