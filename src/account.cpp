#include "commonheader.h"

// 构造函数
Account::Account()
{
	name = "DefaultName";
	uid = currentUid++;
}

// 构造函数
Account::Account(std::string inputName, std::string inputPassword)
{
	name = inputName;
	password = inputPassword;
	uid = currentUid++;
}

// 析构函数
Account::~Account() {}

// 获取密码
std::string Account::getPassword()
{
	return password;
}

// 设置用户名
void Account::setName(std::string inputName)
{
	name = inputName;
}

// 设置密码
void Account::setPassword(std::string inputPassword)
{
	password = inputPassword;
}

// 重载">>"运算符
std::istream &operator>>(std::istream &is, Account &account)
{
	is >> account.name >> account.password;
	return is;
}

// 重载"<<"运算符
std::ostream &operator<<(std::ostream &os, Account &account)
{
	os << account.name << "\t"
	   << account.password << std::endl;
	return os;
}
