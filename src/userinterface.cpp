#include "commonheader.h"

// 构造函数
UserInterface::UserInterface()
{
	database = nullptr;
}

// 析构函数
UserInterface::~UserInterface()
{
	if (database != nullptr)
	{
		delete database;
	}
}

// 主要的交互界面
bool UserInterface::run()
{
	system("cls");
	std::cin.clear();
	std::cin.sync();

	if (database == nullptr)
	{
		database = new Database();
	}
	while(currentUser == nullptr)
	{
		currentUser = login();
	}
	if (currentUser == (Account*)this)
	{
		std::cout<<"已退出系统！"<<std::endl;
		pause();
		return false;
	}
	welcome();
	char input;
	input = _getch();
	std::cout << input << std::endl;
	if (currentUser->getPermission() == 1)
	{
		switch (input)
		{
		case '1':
			while (searchInfo())
				;
			break;
		case '2':
			while (sortInfo())
				;
			break;
		case '3':
			while (load())
				;
			break;
		case '4':
			while (print())
				;
			break;
		case '5':
			while (about())
				;
			break;
		case '0':
			quit();
			currentUser = nullptr;
			break;
		}
	}
	else if (currentUser->getPermission() == 2)
	{
		switch (input)
		{
		case '1':
			while (searchInfo())
				;
			break;
		case '2':
			while (sortInfo())
				;
			break;
		case '3':
			while (addInfo())
				;
			break;
		case '4':
			while (deleteInfo())
				;
			break;
		case '5':
			while (modifyInfo())
				;
			break;
		case '6':
			while (load())
				;
			break;
		case '7':
			while (save())
				;
			break;
		case '8':
			while (print())
				;
			break;
		case '9':
			while (about())
				;
			break;
		case '0':
			quit();
			currentUser = nullptr;
			break;
		case '`':
		case '~':
			while (debug())
				;
			break;
		default:
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
		}
	}

	return true;
}

// 暂停函数
void UserInterface::pause()
{
	std::cin.clear();
	std::cin.sync();
	std::cout << "按任意键继续...";
	_getch();
}

// 登录界面
Account *UserInterface::login()
{
	database->loadAccount("savedata_user.dat", "savedata_admin.dat");
	system("cls");
	std::cin.clear();
	std::cin.sync();
	std::cout << "学生成绩管理系统" << std::endl
			  << "────────────────" << std::endl
			  << std::endl
			  << "  1 登录" << std::endl
			  << "  2 注册" << std::endl
			  << "  3 退出" << std::endl
			  << std::endl
			  << "  > ";
	char input;
	input = _getch();
	std::cout << input << std::endl;
	char tmpPermission;
	std::string tmpUsername;
	std::string tmpPassword;
	Account *acc = nullptr;
	switch (input)
	{
	case '1':
		std::cout<<"* 用户登录"<<std::endl;
		std::cout << "  用户名：";
		std::cin >> tmpUsername;
		std::cout << "    密码：";
		std::cin >> tmpPassword;
		acc = database->login(tmpUsername, tmpPassword);
		if (acc != nullptr)
		{
			std::cout << "登录成功！" << std::endl;
			database->saveAccount("savedata_user.dat", "savedata_admin.dat");
			pause();
			std::cout << std::endl;
			return acc;
		}
		else
		{
			std::cout << "登录失败！" << std::endl;
			pause();
			return nullptr;
		}
		break;
	case '2':
		std::cout<<"* 用户注册"<<std::endl;
		std::cout << "* 用户类型选择" << std::endl
				  << "  1 学生" << std::endl
				  << "  2 教师" << std::endl
				  << "  > ";
		tmpPermission = _getch();
		std::cout << tmpPermission << std::endl;
		if (tmpPermission != '1' && tmpPermission != '2')
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return nullptr;
		}
		tmpPermission -= 48;
		if (tmpPermission == 2)
			std::cout << "  用户名：";
		else
			std::cout << "    学号：";
		std::cin >> tmpUsername;
		if (database->queryAccount(tmpUsername))
		{
			std::cout<<"该用户已存在！"<<std::endl;
			pause();
			return nullptr;
		}
		std::cout << "    密码：";
		std::cin >> tmpPassword;
		acc = database->registerUser(tmpUsername, tmpPassword, tmpPermission);
		if (acc != nullptr)
		{
			std::cout << "注册成功！" << std::endl;
			database->saveAccount("savedata_user.dat", "savedata_admin.dat");
			pause();
			std::cout << std::endl;
			return acc;
		}
		else
		{
			std::cout << "注册失败！" << std::endl;
			pause();
			return nullptr;
		}
		break;
	case '3':
		return (Account*)this;
		break;
	}
}

// 欢迎界面
void UserInterface::welcome()
{
	system("cls");
	std::cout << "学生成绩管理系统" << std::endl
			  << "────────────────" << std::endl
			  << "您好，" << currentUser->getName() << (currentUser->getPermission() % 2 ? "同学" : "老师") << std::endl
			  << std::endl;
	if (currentUser->getPermission() == 1)
	{
		if (Info::isDebugMode())
			std::cout << "  ~ 调试模式" << std::endl;
		std::cout << "  1 查询信息" << std::endl
				  << "  2 全部信息" << std::endl
				  << "  3 读取信息" << std::endl
				  << "  4 打印信息" << std::endl
				  << "  5 关于程序" << std::endl
				  << "  0 退出程序" << std::endl
				  << std::endl
				  << "  > ";
	}
	else if (currentUser->getPermission() == 2)
	{
		if (Info::isDebugMode())
			std::cout << "  ~ 调试模式" << std::endl;
		std::cout << "  1 查询信息" << std::endl
				  << "  2 全部信息" << std::endl
				  << "  3 添加信息" << std::endl
				  << "  4 删除信息" << std::endl
				  << "  5 修改信息" << std::endl
				  << "  6 读取信息" << std::endl
				  << "  7 保存信息" << std::endl
				  << "  8 打印信息" << std::endl
				  << "  9 关于程序" << std::endl
				  << "  0 退出程序" << std::endl
				  << std::endl
				  << "  > ";
	}
	else
	{
		std::cout << "未知用户类型！" << std::endl;
	}
}

// 1.查询信息
bool UserInterface::searchInfo()
{
	system("cls");
	if (currentUser->getPermission() == 1)
	{
		std::cout << "    查询信息    " << std::endl
			<< "────────────────" << std::endl
			<< std::endl;
		std::cout << "  1 查询学生信息" << std::endl
			<< "  2 返回上一级" << std::endl
			<< std::endl
			<< "  > ";

		char input;
		input = _getch();
		std::cout << input << std::endl;

		switch (input)
		{
		case '1':
			while (searchStudent())
				;
			break;
		case '2':
			std::cout << "返回上一级。" << std::endl;
			return false;
		default:
			std::cout << "输入错误，请重新输入！" << std::endl;
			break;
		}
		pause();
		return true;
	}
	else
	{
		std::cout << "    查询信息    " << std::endl
			<< "────────────────" << std::endl
			<< std::endl;
		std::cout << "  1 查询学生信息" << std::endl
			<< "  2 查询课程信息" << std::endl
			<< "  3 返回上一级" << std::endl
			<< std::endl
			<< "  > ";

		char input;
		input = _getch();
		std::cout << input << std::endl;

		switch (input)
		{
		case '1':
			while (searchStudent())
				;
			break;
		case '2':
			while (searchLecture())
				;
			break;
		case '3':
			std::cout << "返回上一级。" << std::endl;
			return false;
		default:
			std::cout << "输入错误，请重新输入！" << std::endl;
			break;
		}
		pause();
		return true;
	}
}

// 查询学生信息
bool UserInterface::searchStudent()
{
	system("cls");

	if (currentUser->getPermission() == 1)
	{
		std::cout << "  查询学生信息  " << std::endl
				  << "────────────────" << std::endl
				  << std::endl;
		int num = database->queryStudent(atoi(currentUser->getName().c_str()));
		if (num == 0)
		{
			std::cout << "未找到该学生！" << std::endl;
		}
		else
		{
			std::cout << "共找到" << num << "个学生。" << std::endl;
		}
		return false;
	}
	else
	{
		std::cout << "  查询学生信息  " << std::endl
				  << "────────────────" << std::endl
				  << std::endl;
		std::cout << "  1 按学号查询" << std::endl
				  << "  2 按姓名查询" << std::endl
				  << "  3 返回上一级" << std::endl
				  << std::endl
				  << "  > ";

		char input;
		int num;
		int stuNo;
		std::string stuName;
		input = _getch();
		std::cout << input << std::endl;

		switch (input)
		{
		case '1':
			std::cout << "  学号：";
			std::cin >> stuNo;
			if (!std::cin)
			{
				std::cout << "输入错误，请重新输入！" << std::endl;
				pause();
				return true;
			}
			num = database->queryStudent(stuNo);
			std::cout << std::endl;
			if (num == 0)
			{
				std::cout << "未找到该学生！" << std::endl;
			}
			else
			{
				std::cout << "共找到" << num << "个学生。" << std::endl;
			}
			break;
		case '2':
			std::cout << "  姓名：";
			std::cin >> stuName;
			if (!std::cin)
			{
				std::cout << "输入错误，请重新输入！" << std::endl;
				pause();
				return true;
			}
			num = database->queryStudent(stuName);
			std::cout << std::endl;
			if (num == 0)
			{
				std::cout << "未找到该学生！" << std::endl;
			}
			else
			{
				std::cout << "共找到" << num << "个学生。" << std::endl;
			}
			break;
		case '3':
			std::cout << "返回上一级。" << std::endl;
			return false;
		default:
			std::cout << "输入错误，请重新输入！" << std::endl;
			break;
		}
		pause();
		return true;
	}
}

// 查询课程信息
bool UserInterface::searchLecture()
{
	system("cls");

	std::cout << "  查询课程信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 按课程名查询" << std::endl
			  << "  2 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input = 0;
	int num = 0;
	std::string lecName;
	input = _getch();
	std::cout << input << std::endl;

	if (!std::cin)
	{
		std::cout << "输入错误，请重新输入！" << std::endl;
		pause();
		return true;
	}

	switch (input)
	{
	case '1':
		std::cout << "  课程名：";
		std::cin >> lecName;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		num = database->queryLecture(lecName);
		if (num == 0)
		{
			std::cout << "未找到该课程！" << std::endl;
		}
		else
		{
			std::cout << "共找到" << num << "个课程。" << std::endl;
		}
		break;
	case '2':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		pause();
		return true;
	}
	pause();
	return true;
}

// 全部信息
bool UserInterface::sortInfo()
{
	system("cls");

	if (currentUser->getPermission() == 1)
	{
		while (sortLecture())
			;
		return false;
	}
	else
	{
		std::cout << "    全部信息    " << std::endl
				  << std::endl;
		std::cout << "  1 显示学生信息" << std::endl
				  << "  2 显示课程信息" << std::endl
				  << "  3 返回上一级" << std::endl
				  << std::endl
				  << "  > ";

		char input;
		input = _getch();
		std::cout << input << std::endl;

		switch (input)
		{
		case '1':
			while (sortStudent())
				;
			break;
		case '2':
			while (sortLecture())
				;
			break;
		case '3':
			std::cout << "返回上一级。" << std::endl;
			return false;
		default:
			std::cout << "输入错误，请重新输入！" << std::endl;
			break;
		}
	}
	pause();
	return true;
}

// 排序学生信息
bool UserInterface::sortStudent()
{
	system("cls");

	char input = 0;
	char direction = 0;

	std::cout << "  全部学生信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 默认排序" << std::endl
			  << "  2 按学号排序" << std::endl
			  << "  3 按姓名排序" << std::endl
			  << "  4 按总成绩排序" << std::endl
			  << "  5 按总学分排序" << std::endl
			  << "  6 按总绩点排序" << std::endl
			  << "  7 按平均成绩排序" << std::endl
			  << "  8 按平均绩点排序" << std::endl
			  << "  9 返回上一级" << std::endl
			  << std::endl
			  << "  > ";
	input = _getch();
	std::cout << input << std::endl;
	switch (input)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
		break;
	case '9':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		pause();
		return true;
	}

	if (input != '1')
	{
		std::cout << std::endl
				  << "* 排序方向选择" << std::endl
				  << "  1 升序" << std::endl
				  << "  2 降序" << std::endl
				  << "  > ";
		direction = _getch();
		std::cout << direction << std::endl;
		if (direction != '1' && direction != '2')
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
	}

	database->sortStudent((direction == '1') ? -1 : 1, input - 50);

	pause();
	return true;
}

// 排序课程信息
bool UserInterface::sortLecture()
{
	system("cls");

	char input = 0;
	char direction = 0;
	char lecType = 0;

	std::cout << "  全部课程信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 默认排序" << std::endl
			  << "  2 按课程名排序" << std::endl
			  << "  3 按学分排序" << std::endl
			  << "  4 按学生数排序" << std::endl
			  << "  5 按平均分排序" << std::endl
			  << "  6 按平均绩点排序" << std::endl
			  << "  7 返回上一级" << std::endl
			  << std::endl
			  << "  > ";
	input = _getch();
	std::cout << input << std::endl;
	switch (input)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
		break;
	case '7':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		pause();
		return true;
	}

	std::cout << std::endl
			  << "* 课程类型选择" << std::endl
			  << "  1 全部课" << std::endl
			  << "  2 必选课" << std::endl
			  << "  3 限选课" << std::endl
			  << "  4 任选课" << std::endl
			  << "  > ";
	lecType = _getch();
	std::cout << lecType << std::endl;
	if (lecType != '1' && lecType != '2' && lecType != '3' && lecType != '4')
	{
		std::cout << "输入错误，请重新输入！" << std::endl;
		pause();
		return true;
	}

	if (input != '1')
	{
		std::cout << "* 排序方向选择" << std::endl
				  << "  1 升序" << std::endl
				  << "  2 降序" << std::endl
				  << "  > ";
		direction = _getch();
		std::cout << direction << std::endl;
		if (direction != '1' && direction != '2')
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
	}

	database->sortLecture((LectureType)(lecType - 49), (direction == '1') ? -1 : 1, input - 50);

	pause();
	return true;
}

// 添加信息
bool UserInterface::addInfo()
{
	system("cls");

	std::cout << "    添加信息    " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 添加学生信息" << std::endl
			  << "  2 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input;
	input = _getch();
	std::cout << input << std::endl;

	switch (input)
	{
	case '1':
		while (addStudent())
			;
		break;
	case '2':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}
	pause();
	return true;
}

// 添加学生信息
bool UserInterface::addStudent()
{
	system("cls");

	std::cout << "  添加学生信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	database->addStudent();
	database->updateLecture();

	std::cout << "是否继续添加？[y/N]";
	char input;
	input = _getch();
	if (input == 'Y' || input == 'y')
	{
		std::cout << input << std::endl;
		return true;
	}
	else
	{
		if (input != '\n')
		{
			std::cout << input << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
		return false;
	}
}

// 添加课程信息
bool UserInterface::addLecture()
{
	return true;
}

// 删除信息
bool UserInterface::deleteInfo()
{
	system("cls");

	std::cout << "  删除学生信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 删除学生信息" << std::endl
			  << "  2 删除课程信息" << std::endl
			  << "  3 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input;
	input = _getch();
	std::cout << input << std::endl;

	switch (input)
	{
	case '1':
		while (deleteStudent())
			;
		break;
	case '2':
		while (deleteLecture())
			;
		break;
	case '3':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}
	pause();
	return true;
}

// 删除学生信息
bool UserInterface::deleteStudent()
{
	system("cls");

	std::cout << "  删除学生信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 按学号删除" << std::endl
			  << "  2 按姓名删除" << std::endl
			  << "  3 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input;
	int num;
	int stuNo;
	std::string stuName;

	input = _getch();
	std::cout << input << std::endl;

	switch (input)
	{
	case '1':
		std::cout << "请输入学号：";
		std::cin >> stuNo;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		num = database->queryStudent(stuNo, false);
		if (num == 0)
		{
			std::cout << "未找到该学生！" << std::endl;
		}
		else
		{
			database->deleteStudent(stuNo);
			std::cout << "已删除" << num << "个学生。" << std::endl;
			database->updateLecture();
		}
		break;
	case '2':
		std::cout << "请输入姓名：";
		std::cin >> stuName;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		num = database->queryStudent(stuName, false);
		if (num == 0)
		{
			std::cout << "未找到该学生！" << std::endl;
		}
		else
		{
			database->deleteStudent(stuName);
			std::cout << "已删除" << num << "个学生。" << std::endl;
			database->updateLecture();
		}
		break;
	case '3':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}

	std::cout << "是否继续删除？[y/N]";
	char ctn;
	ctn = _getch();
	if (ctn == 'Y' || ctn == 'y')
	{
		std::cout << ctn << std::endl;
		return true;
	}
	else
	{
		if (ctn != '\n')
		{
			std::cout << ctn << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
		return false;
	}
}

// 删除课程信息
bool UserInterface::deleteLecture()
{
	system("cls");

	std::cout << "  删除课程信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 按名称删除" << std::endl
			  << "  2 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input;
	int num;
	std::string lecName;

	input = _getch();
	std::cout << input << std::endl;
	switch (input)
	{
	case '1':
		std::cout << "请输入课程名：";
		std::cin >> lecName;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		num = database->queryLecture(lecName, false);
		if (num == 0)
		{
			std::cout << "未找到该课程！" << std::endl;
		}
		else
		{
			if (database->queryRequired(lecName, false))
			{
				database->deleteRequired(lecName);
				std::cout << "已删除" << num << "个必选课。" << std::endl;
				database->updateStudent();
			}
			else if (database->queryLimited(lecName, false))
			{
				database->deleteLimited(lecName);
				std::cout << "已删除" << num << "个限选课。" << std::endl;
				database->updateStudent();
			}
			else
			{
				database->deleteOptional(lecName);
				std::cout << "已删除" << num << "个任选课。" << std::endl;
				database->updateStudent();
			}
		}
		break;
	case '2':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}

	std::cout << "是否继续删除？[y/N]";
	char ctn;
	ctn = _getch();
	if (ctn == 'Y' || ctn == 'y')
	{
		std::cout << ctn << std::endl;
		return true;
	}
	else
	{
		if (ctn != '\n')
		{
			std::cout << ctn << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
		return false;
	}
}

// 修改信息
bool UserInterface::modifyInfo()
{
	system("cls");

	std::cout << "    修改信息    " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 修改学生信息" << std::endl
			  << "  2 修改课程信息" << std::endl
			  << "  3 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	int input;
	input = _getch();
	std::cout << input << std::endl;
	switch (input)
	{
	case '1':
		while (modifyStudent())
			;
		break;
	case '2':
		while (modifyLecture())
			;
		break;
	case '3':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}

	std::cout << "是否继续修改？[y/N]";
	char ctn;
	ctn = _getch();
	if (ctn == 'Y' || ctn == 'y')
	{
		std::cout << ctn << std::endl;
		return true;
	}
	else
	{
		if (ctn != '\n')
		{
			std::cout << ctn << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
		return false;
	}
}

// 修改学生信息
bool UserInterface::modifyStudent()
{
	system("cls");

	std::cout << "  修改学生信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 按学号修改" << std::endl
			  << "  2 按姓名修改" << std::endl
			  << "  3 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input;
	int num;
	int stuNo;
	std::string stuName;

	input = _getch();
	std::cout << input << std::endl;
	switch (input)
	{
	case '1':
		std::cout << "请输入学号：";
		std::cin >> stuNo;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		num = database->queryStudent(stuNo, false);
		if (num == 0)
		{
			std::cout << "未找到该学生！" << std::endl;
		}
		else
		{
			database->modifyStudent(stuNo);
			std::cout << "已修改" << num << "个学生。" << std::endl;
			database->updateLecture();
		}
		break;
	case '2':
		std::cout << "请输入姓名：";
		std::cin >> stuName;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		num = database->queryStudent(stuName, false);
		if (num == 0)
		{
			std::cout << "未找到该学生！" << std::endl;
		}
		else
		{
			database->modifyStudent(stuName);
			std::cout << "已修改" << num << "个学生。" << std::endl;
			database->updateLecture();
		}
		break;
	case '3':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}

	std::cout << "是否继续修改？[y/N]";
	char ctn;
	ctn = _getch();
	if (ctn == 'Y' || ctn == 'y')
	{
		std::cout << ctn << std::endl;
		return true;
	}
	else
	{
		if (ctn != '\n')
		{
			std::cout << ctn << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
		return false;
	}
}

// 修改课程信息
bool UserInterface::modifyLecture()
{
	system("cls");

	std::cout << "  修改课程信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 按名称修改" << std::endl
			  << "  2 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input;
	std::string lecName;

	input = _getch();
	std::cout << input << std::endl;
	switch (input)
	{
	case '1':
		std::cout << "请输入课程名称：";
		std::cin >> lecName;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		database->modifyLecture(lecName);
		database->updateStudent();
		break;
	case '2':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}

	std::cout << "是否继续修改？[y/N]";
	char ctn;
	ctn = _getch();
	if (ctn == 'Y' || ctn == 'y')
	{
		std::cout << ctn << std::endl;
		return true;
	}
	else
	{
		if (ctn != '\n')
		{
			std::cout << ctn << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
		return false;
	}
}

// 读取信息
bool UserInterface::load()
{
	system("cls");

	std::cout << "  读取保存信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "该操作将会覆盖当前数据，是否继续？[y/N]" << std::endl;
	char input;
	input = _getch();
	std::cout << input << std::endl;
	if (input == 'Y' || input == 'y')
	{
		try
		{
			database->load();
		}
		catch (FileException e)
		{
			if (e.mode == "open")
			{
				std::cout << "以" << e.type << "方式打开文件" << e.filename << "失败！" << std::endl;
			}
			else
			{
				if (e.type == "read")
				{
					std::cout << "读取文件" << e.filename << "失败！" << std::endl;
				}
				else
				{
					std::cout << "写入文件" << e.filename << "失败！" << std::endl;
				}
			}
		}
		std::cout << "数据已读取。" << std::endl;
	}
	pause();
	return false;
}

// 保存信息
bool UserInterface::save()
{
	system("cls");

	std::cout << "    保存信息    " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;

	try
	{
		database->save();
	}
	catch (FileException e)
	{
		if (e.mode == "open")
		{
			std::cout << "以" << e.type << "方式打开文件" << e.filename << "失败！" << std::endl;
		}
		else
		{
			if (e.type == "read")
			{
				std::cout << "读取文件" << e.filename << "失败！" << std::endl;
			}
			else
			{
				std::cout << "写入文件" << e.filename << "失败！" << std::endl;
			}
		}
	}
	std::cout << "数据已保存。" << std::endl;
	pause();
	return false;
}

// 打印信息
bool UserInterface::print()
{
	system("cls");

	if (currentUser->getPermission() == 1)
	{
		while (printStudent())
			;
		return false;
	}
	else
	{
		std::cout << "    打印信息    " << std::endl
				  << "────────────────" << std::endl
				  << std::endl;
		std::cout << "  1 打印学生信息" << std::endl
				  << "  2 打印课程信息" << std::endl
				  << "  3 返回上一级" << std::endl
				  << std::endl
				  << "  > ";

		char input;
		input = _getch();
		std::cout << input << std::endl;
		switch (input)
		{
		case '1':
			while (printStudent())
				;
			break;
		case '2':
			while (printLecture())
				;
			break;
		case '3':
			std::cout << "返回上一级。" << std::endl;
			return false;
		default:
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			break;
		}
	}
	pause();
	return true;
}

// 打印学生信息
bool UserInterface::printStudent()
{
	system("cls");

	if (currentUser->getPermission() == 1)
	{
		std::cout << "  打印学生信息  " << std::endl
				  << "────────────────" << std::endl
				  << std::endl;
		database->printStudent(atoi(currentUser->getName().c_str()));
		pause();
		return false;
	}
	else
	{
		std::cout << "  打印学生信息  " << std::endl
				  << std::endl;
		std::cout << "  1 打印全部学生信息" << std::endl
				  << "  2 按学号打印学生信息" << std::endl
				  << "  3 按姓名打印学生信息" << std::endl
				  << "  4 返回上一级" << std::endl
				  << std::endl
				  << "  > ";

		char input;
		int stuId;
		std::string stuName;

		input = _getch();
		std::cout << input << std::endl;
		switch (input)
		{
		case '1':
			database->printStudent();
			pause();
			break;
		case '2':
			std::cout << "请输入学号：";
			std::cin >> stuId;
			if (!std::cin)
			{
				std::cout << "输入错误，请重新输入！" << std::endl;
				pause();
				return true;
			}
			database->printStudent(stuId);
			pause();
			break;
		case '3':
			std::cout << "请输入姓名：";
			std::cin >> stuName;
			if (!std::cin)
			{
				std::cout << "输入错误，请重新输入！" << std::endl;
				pause();
				return true;
			}
			database->printStudent(stuName);
			pause();
			break;
		case '4':
			std::cout << "返回上一级。" << std::endl;
			return false;
		default:
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			break;
		}
	}
	return true;
}

// 打印课程信息
bool UserInterface::printLecture()
{
	system("cls");

	std::cout << "  打印课程信息  " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "  1 打印全部课程信息" << std::endl
			  << "  2 按类型打印课程信息" << std::endl
			  << "  3 按名称打印课程信息" << std::endl
			  << "  4 返回上一级" << std::endl
			  << std::endl
			  << "  > ";

	char input;
	char lecType;
	std::string lecName;

	input = _getch();
	std::cout << input << std::endl;
	switch (input)
	{
	case '1':
		database->printLecture();
		pause();
		break;
	case '2':
		std::cout << "* 课程类型选择" << std::endl
				  << "  1 必选课" << std::endl
				  << "  2 限选课" << std::endl
				  << "  3 任选课" << std::endl;
		lecType = _getch();
		std::cout << lecType << std::endl;
		if (lecType < '1' || lecType > '3')
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		database->printLecture((LectureType)(lecType - 48));
		pause();
		break;
	case '3':
		std::cout << "请输入课程名：";
		std::cin >> lecName;
		if (!std::cin)
		{
			std::cout << "输入错误，请重新输入！" << std::endl;
			pause();
			return true;
		}
		database->printLecture(lecName);
		pause();
		break;
	case '4':
		std::cout << "返回上一级。" << std::endl;
		return false;
	default:
		std::cout << "输入错误，请重新输入！" << std::endl;
		break;
	}
	return true;
}

// 关于程序
bool UserInterface::about()
{
	system("cls");

	std::cout << "    关于程序    " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	std::cout << "学生成绩管理系统" << std::endl
			  << "Copyright (c) Xuc Pan 2023" << std::endl
			  << "GitHub: https://github.com/Panxuc" << std::endl
			  << std::endl;
	std::cout << "* 统计信息：" << std::endl
			  << "    学生" << database->getStudentListSize() << "人。" << std::endl
			  << "  必选课" << database->getRequiredListSize() << "门。" << std::endl
			  << "  限选课" << database->getLimitedListSize() << "门。" << std::endl
			  << "  任选课" << database->getOptionalListSize() << "门。" << std::endl;
	pause();
	return false;
}

// 退出程序
void UserInterface::quit()
{
	if (currentUser->getPermission() == 2)
	{
		std::cout << "是否保存数据？[y/N]"<<std::endl;
		char input;
		input = _getch();
		if (input == 'Y' || input == 'y')
		{
			try
			{
				database->save();
			}
			catch (FileException e)
			{
				if (e.mode == "open")
				{
					std::cout << "以" << e.type << "方式打开文件" << e.filename << "失败！" << std::endl;
				}
				else
				{
					if (e.type == "read")
					{
						std::cout << "读取文件" << e.filename << "失败！" << std::endl;
					}
					else
					{
						std::cout << "写入文件" << e.filename << "失败！" << std::endl;
					}
				}
			}
			std::cout << "数据已保存。" << std::endl;
		}
		else
		{
			std::cout << "数据未保存。" << std::endl;
		}
	}
	std::cout << "感谢使用本学生成绩管理系统。" << std::endl;
}

//~.调试模式
bool UserInterface::debug()
{
	system("cls");

	std::cout << "    调试模式    " << std::endl
			  << "────────────────" << std::endl
			  << std::endl;
	if (!Info::isDebugMode())
	{
		std::cout << "调试模式会输出更多信息，也可以自由修改所有数值，是否继续？[y/N]" << std::endl;
		char input;
		input = _getch();
		if (input == 'Y' || input == 'y')
		{
			std::cout << "请输入密码：" << std::endl;
			std::string password;
			std::cin >> password;
			if (password == "114514")
			{
				std::cout << "调试模式已开启。" << std::endl;
				Info::setDebug(true);
				pause();
				return false;
			}
			else
			{
				std::cout << "密码错误，调试模式未开启。" << std::endl;
				pause();
				return false;
			}
		}
		else
		{
			std::cout << "回到主菜单。" << std::endl;
			pause();
			return false;
		}
	}
	else
	{
		std::cout << "调试模式已开启，是否关闭？[y/N]" << std::endl;
		int input;
		input = _getch();
		if (input == 'Y' || input == 'y')
		{
			std::cout << "请输入密码：" << std::endl;
			std::string password;
			std::cin >> password;
			if (password == "114514")
			{
				std::cout << "调试模式已关闭。" << std::endl;
				Info::setDebug(false);
				pause();
				return false;
			}
			else
			{
				std::cout << "密码错误，调试模式未关闭。" << std::endl;
				pause();
				return false;
			}
		}
		else
		{
			std::cout << "回到主菜单。" << std::endl;
			pause();
			return false;
		}
	}
}
