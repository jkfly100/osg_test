#include "handle.h"

handler::handler(callback call)
	:_call(call)
{
	setCallBack(_call);
}

handler::~handler()
{}

void handler::setCallBack(callback call)
{
	Data data;
	data.age = 13;
	data.name = "zs";
	_call = call;
	_call(data);
}