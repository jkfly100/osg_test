#pragma once
#ifndef __HANDLE_H__
#define __HEADLE_H__

#include <iostream>
#include <functional>
#include <string>

using namespace std;
struct Data
{
	string name;
	int age;
};

class handler
{
public:
	using callback = function<Data(Data)>;
	handler(callback call);
	~handler();

	void setCallBack(callback call);

private:
	callback _call;
	Data _data;
};

#endif // !__HANDLE_H__

