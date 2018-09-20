/*           复数四则运算计算器         */
/*             开发平台：win10          */
/*              开发语言：C语言         */
/*                作者：Twikura         */
/*github: https://github.com/rainbowtrash2333  */

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

//int main() {
//
//	complex_num num1, num2, num;
//
//	printf("input first complex number (for example: 15 12 )");
//	scanf_s("%lf%lf", &num1.a, &num1.b);
//	printf("\n%lf+%lfi", num1.a, num1.b);
//	printf("\ninput second complex number (for example: 15 12 )");
//	scanf_s("%lf%lf", &num2.a, &num2.b);
//	printf("\n%lf+%lfi", num2.a, num2.b);
//	num = div(num1, num2);
//	printf("\n%lf+%lfi", num.a, num.b);
//}

