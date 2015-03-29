#include<vector>
#include<string>
#include<iostream>
using namespace std;
#pragma once
class BigInt
{ 
private:
	
	string digits;
	bool sign;
	
public:
	BigInt();
	BigInt(int a);
	BigInt(string a);
	BigInt operator + ( BigInt second);
	BigInt operator - (BigInt second);
	BigInt operator / (BigInt second);
	BigInt operator % (BigInt second);
	bool operator < (BigInt second);
	void operator =(BigInt second);
	BigInt operator *(BigInt second);
	BigInt operator ^(int);
	string powerofmod(string a,string N,string mod);
	string Chck();
	friend ostream& operator << (ostream& os, const BigInt& x);
	friend istream& operator >> (istream& inp, BigInt& bigInt);
	
	~BigInt();
};

