// LengthCalc.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>   

using namespace std;

struct LengthTranslator
{
	LengthTranslator();

	void Run();
	void ParseUnit(const string& equal);
	void CalcFormula(const string& equal);

	fstream mFin;
	fstream mFout;
	map<string, float> mUnitLength;
	map<string, string> mDictionary;
};

LengthTranslator::LengthTranslator(): mFin("input.txt", std::ios_base::in), mFout("output.txt", std::ios_base::out)
{
	mUnitLength["meter"] = 1;
	mUnitLength["meters"] = 1;

	mDictionary["inch"] = "inches";
	mDictionary["foot"] = "feet";
}

void LengthTranslator::Run()
{
	mFout<<"hejian1639@sina.com.cn\n\n";
	string line;
	int state = 0;
	while(getline(mFin, line))
	{
		if(line == "")
		{
			++state;
		}
		else
		{
			switch(state)
			{
			case 0:
				ParseUnit(line);
				break;
			case 1:
				CalcFormula(line);
				break;
			}
		}
		cout<<line<<"\n";
	}
}

void LengthTranslator::ParseUnit(const string& equal)
{
	stringstream ss(equal);
	stringstream nameBuf;
	char c;
	c = ss.get();
    if (!ss.good())
	{
		return;
	}
	while(c != '1')
	{
		c = ss.get();
		if (!ss.good())
		{
			return;
		}
	}
	c = ss.get();
    if (!ss.good())
	{
		return;
	}
	while((c == ' ') || (c == '\t'))
	{
		c = ss.get();
		if (!ss.good())
		{
			return;
		}
	}

	while((c != ' ') && (c != '\t') && (c != '='))
	{
		nameBuf<<c;
		c = ss.get();
		if (!ss.good())
		{
			return;
		}
	}
	cout<<nameBuf.str()<<" ";

	c = ss.peek();
	while((c == ' ') || (c == '\t') || (c == '='))
	{
		c = ss.get();
		if (!ss.good())
		{
			return;
		}
		c = ss.peek();
	}
	float length = 0.0f;
	ss>>length;
	mUnitLength[nameBuf.str()] = length;
	map<string, string>::iterator iter = mDictionary.find(nameBuf.str());
	if(iter == mDictionary.end())
	{
		mUnitLength[nameBuf.str()+'s'] = length;
	}
	else
	{
		mUnitLength[iter->second] = length;
	}

	cout<<length<<"\n";
}

void LengthTranslator::CalcFormula(const string& equal)
{
	stringstream ss(equal);
	char c;
	float length = 0.0f;
	bool sign = true;
	while(!ss.eof())
	{
		c = ss.peek();
		while((c < '0') || (c > '9'))
		{
			c = ss.get();
			if (!ss.good())
			{
				return;
			}
			c = ss.peek();
		}
		float l = 0.0f;
		ss>>l;

		c = ss.get();
		while((c < 'a') || (c > 'z'))
		{
			c = ss.get();
			if (!ss.good())
			{
				return;
			}
		}

		stringstream nameBuf;
		while((c >= 'a') && (c <= 'z'))
		{
			nameBuf<<c;
			c = ss.get();
			if (!ss.good())
			{
				break;
			}
		}
		cout<<nameBuf.str()<<"\n";
		map<string, float>::iterator iter = mUnitLength.find(nameBuf.str());
		if(iter == mUnitLength.end())
		{
			break;
		}
		l *= iter->second;


		if(sign)
		{
			length += l;
		}
		else
		{
			length -= l;
		}

		while((c != '+') && (c != '-'))
		{
			c = ss.get();
			if (!ss.good())
			{
				break;
			}
		}
		if(c == '+')
		{
			sign = true;
		}
		else if(c == '-')
		{
			sign = false;
		}

	}

	mFout<<fixed<<setprecision(2)<<length<<" m\n";   

	cout<<length<<" m\n";
}



int main()
{

	LengthTranslator translator;
	translator.Run();

	system("pause");
	return 0;
}

