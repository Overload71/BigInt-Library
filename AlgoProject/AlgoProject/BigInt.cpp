#include "BigInt.h"
#include<algorithm>
#include <iterator>
#include<string>
using namespace std;
#pragma warning (disable : 4996)

string powerofmod(string N, string sum, string mod);
string multiply(string X, string Y);
void div(string a, string b, string &q, string &r);
bool comp(string a, string b);
string Substr(string str1, string str2);
int MakeEqLength(string &A, string &B);
string AddStr(string a, string b);
string rem(string a, string b);
string whole(string a, string b);


string  BigInt::powerofmod(string a,string N,string mod)//encode
{
	string sum;
	if (N == "0")
		return "1";
	sum = rem(powerofmod(a, whole(N, "2"), mod), mod);
	if (N[N.size()-1]%2==0)
		return rem(multiply(sum, sum), mod);
	else
		return rem((multiply(rem(a, mod), multiply(sum, sum))), mod);
}
bool comp(string a, string b)
{
	if (a.size()<b.size())
		return true;
	else if (a.size() > b.size())
		return false;
	else
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] > b[i])
				return false;
			else if (a[i] < b[i])
				return true;
		}
		return false;
	}
}
string AddStr(string a, string b)
{
	string result;
	int i = 0;
	if (comp(a, b))
		swap(a, b);
	result.resize(a.size());
	int subSum(0);
	int subCarry(0);
	int j = a.size() - 1;
	for (i=b.size()-1; i>= 0; i--)
	{
		subSum = (a[j]-48) + (b[i]-48) + int(subCarry);
		subCarry = subSum / 10;
		result[j] = (subSum % 10)+48;
		j--;
	}
	for (; j >=0 ; j--)
	{
		subSum = (a[j]-48) + subCarry;
		subCarry = subSum / 10;
		result[j] = (subSum % 10)+48;
	}
	if (subCarry)
		result.insert(0,"1");
	return result;
}

string Substr(string a1, string a2)
{
	string res;
	int i;
	int temp;
	int tran = 0;
	bool flag = false;
	if (comp(a1, a2))
		swap(a1, a2);
	res.resize(a1.size());
	int j = a1.size() - 1;
	for (i = a2.size() - 1; i >= 0; i--)
	{
		temp = ((a1[j] - '0') - (a2[i] - '0')) - tran;
		if (temp < 0)
		{
			tran = 1;
			res[j] = temp + 10 + 48;
		}
		else
		{
			tran = 0;
			res[j] = temp + 48;
		}
		j--;
	}
	for (; j >= 0; j--)
	{
		temp = (a1[j] - '0') - tran;
		if (temp < 0)
		{
			tran = 1;
			res[j] = temp + 10 + 48;
		}
		else
		{
			tran = 0;
			res[j] = temp + 48;
		}
	}
	while (res[0] == '0' && res.length() != 1) // erase leading zeros
		res.erase(0, 1);
	return res;
}
void div(string a, string b, string &q, string &r)
{
	if ((a < b))
	{
		q = "0";
		r = a;
		return;
	}

	div(a, AddStr(b, b), q, r);
	q = AddStr(q, q);
	if ((r< b))
	{
		return;
	}
	else
	{
		q = AddStr(q, "1");
		r = Substr(r, b);
		return;
	}
}
string rem(string a, string b)
{
	string q, r;
	if (comp(a, b))
	{
		q = "0";
		r = a;
		return r;
	}

	div(a, AddStr(b, b), q, r);
	q = AddStr(q, q);
	if (comp(r, b))
	{
		return r;
	}
	else
	{
		q = AddStr(q, "1");
		r = Substr(r, b);
		return r;
	}
}
string whole(string a, string b)
{
	string q, r;
	if (comp(a, b))
	{
		q = "0";
		r = a;
		return q;
	}

	div(a, AddStr(b, b), q, r);
	q = AddStr(q, q);
	if (comp(r, b))
	{
		return q;
	}
	else
	{
		q = AddStr(q, "1");
		r = Substr(r, b);
		return q;
	}
}
BigInt::BigInt()
{

}

BigInt::BigInt(string a)
{
	digits = a;
}

BigInt::BigInt(int a)
{
	string b = "";
	while (a != 0)
	{
		b += a % 10;
		a /= 10;
	}
	reverse(b.begin(), b.end());
	digits = b;
}
bool BigInt::operator<(BigInt a2)
{
	bool res = comp(this->digits, a2.digits);
	return res;
}
BigInt BigInt::operator/(BigInt a2)
{
	string q, r;
	div(this->digits, a2.digits, q, r);
	q += ".";
	q += r;
	BigInt qq = q;
	return qq;
}
BigInt BigInt::operator%(BigInt a2)
{
	string q, r;
	div(this->digits, a2.digits, q, r);
	return BigInt(r);
}
string BigInt::Chck()
{
	if (digits[digits.size() - 1] % 2 == 0)
		return "Even";
	return "Odd";
}
void BigInt::operator=(BigInt second)
{
	digits = second.digits;
}

BigInt BigInt::operator + (BigInt second)
{
	string res = AddStr(this->digits, second.digits);
	return BigInt(res);
}

BigInt BigInt::operator *(BigInt second)
{
	string res = multiply(this->digits, second.digits);
	return BigInt(res);
}

BigInt BigInt::operator-(BigInt second)
{
	string res = Substr(this->digits, second.digits);
	return BigInt(res);
}
BigInt::~BigInt()
{

}
ostream& operator<<(ostream& os, const BigInt& x) {
	os << x.digits;

	return os;
}

istream& operator >>(istream& inp, BigInt& bigInt){
	inp >> bigInt.digits;
	return inp;
}
string multiply(string X, string Y)
{
	int diff_size = X.size() - Y.size();
	diff_size = abs(diff_size);
	string Zeros;
	Zeros.resize(diff_size, '0');
	if (X.size() > Y.size())
		Y = Zeros + Y;
	else
		X = Zeros + X;
	///////////////////////////////////////////////////////////////////////////
	//BASE CASE
	if (X.size() % 2 == 1 && X.size() != 1)
	{
		X = '0' + X;
		Y = '0' + Y;
	}
	if (X.size() == 1)
	{
		string result;
		int temp = (X[0] - '0')*(Y[0] - '0');
		do
		{
			char ch = (temp % 10) + '0';
			result = ch + result;
			temp /= 10;
		} while (temp != 0);
		return result;
	}
	//////////////////////////////////////////////////////////////////////////
	int fh = X.size() / 2;
	int sh = (X.size() - fh);
	string a = X.substr(0, fh);
	string b = X.substr(fh, sh);
	string c = Y.substr(0, fh);
	string d = Y.substr(fh, sh);
	string AplusB = AddStr(a, b);
	string CplusD = AddStr(c, d);

	string AmulC = multiply(a, c);
	string BmulD = multiply(b, d);
	string  k = multiply(AplusB, CplusD);
	string g = AddStr(AmulC, BmulD);
	string Score = Substr(k, g);
	Zeros.resize(sh, '0');
	Score = Score + Zeros;
	Zeros.resize(sh + fh, '0');
	AmulC = AmulC + Zeros;
	string Final = AddStr(AmulC, AddStr(Score, BmulD));
	while (Final[0] == '0' && Final.size() != 1)
	{
		Final.erase(0, 1);
	}
	return Final;
}