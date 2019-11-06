#include "handle.h"



Data newData;

Data callBack(Data data)
{
	newData.age = data.age;
	newData.name = data.name;
	return newData;
}

int main()
{
	cout << "pre newData.age = " << newData.age << endl
		<< "pre newData.name = " << newData.name << endl;
	handler newHandle(callBack);
	//newHandle.setCallBack(callBack);
	cout << "newData.age = " << newData.age << endl
		<< "newData.name = " << newData.name << endl;
}