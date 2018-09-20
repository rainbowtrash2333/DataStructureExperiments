#include "pch.h"
#include<stdio.h>

//结构 y=a+bi;
//a为实属，b为虚数
typedef struct complex_num
{
	double a;
	double b;
}complex_num;

//加法
void add(complex_num *num1, complex_num *num2, complex_num *num) {

	num->a = num1->a + num2->a;
	num->b = num1->b + num2->b;

}
//减法
void sub(complex_num *num1, complex_num *num2, complex_num *num) {

	num->a = num1->a - num2->a;
	num->b = num1->b - num2->b;
}

//乘法
void mul(complex_num *num1, complex_num *num2, complex_num *num) {

	num->a = num1->a * num2->a - num1->b * num2->b;
	num->b = num1->a * num2->b + num1->b * num2->a;

}
//除法
bool div(complex_num *num1, complex_num *num2, complex_num *num) {

	if (num2->a == 0 && num2->b == 0) return false;

	double foo = num2->a * num2->a + num2->b*num2->b;
	num->a = (num1->a * num2->a + num1->b * num2->b) / foo;
	num->b = (num1->a * num2->b - num1->b * num2->a) / foo;
	return true;
}
