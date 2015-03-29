#include"BigInt.h"
#include<string>
#include<ctime>
#include<iostream>
#pragma warning (disable : 4996)
using namespace std;
int main()
{
	//freopen("Text.txt", "r", stdin);
	BigInt a, b;
	cin >> a >> b;
	cout << a / b << endl;
}