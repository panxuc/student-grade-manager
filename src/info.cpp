#include "commonheader.h"

// 构造函数
Info::Info()
{
	name = "DefaultName";
	uid = currentUid++;
}

// 构造函数
Info::Info(std::string inputName)
{
	name = inputName;
	uid = currentUid++;
}

// 析构函数
Info::~Info() {}

// 获取名称
std::string Info::getName()
{
	return name;
}

// 获取唯一标识符
int Info::getUid()
{
	return uid;
}

// 获取是否处于调试模式
bool Info::isDebugMode()
{
	return DebugMode;
}

// 设置名称
void Info::setName(std::string inputName)
{
	name = inputName;
}
