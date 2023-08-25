#include "commonheader.h"

// 构造函数
Lecture::Lecture()
{
	credit = 0;
	studentNo.clear();
	studentName.clear();
	studentScore.clear();
	studentGPA.clear();
	studentNum = 0;
	totalScore = 0;
	totalGPA = 0;
	averageScore = 0;
	averageGPA = 0;
}

// 析构函数
Lecture::~Lecture() {}

// 获取学分
int Lecture::getCredit()
{
	return credit;
}

// 获取学号
std::vector<int> Lecture::getStudentNo()
{
	return studentNo;
}

// 获取姓名
std::vector<std::string> Lecture::getStudentName()
{
	return studentName;
}

// 获取成绩
std::vector<int> Lecture::getStudentScore()
{
	return studentScore;
}

// 获取绩点
std::vector<double> Lecture::getStudentGPA()
{
	return studentGPA;
}

// 获取学生人数
int Lecture::getStudentNum()
{
	return studentNum;
}

// 获取总分
int Lecture::getTotalScore()
{
	return totalScore;
}

// 获取总绩点
double Lecture::getTotalGPA()
{
	return totalGPA;
}

// 获取平均分
int Lecture::getAverageScore()
{
	return averageScore;
}

// 获取平均绩点
double Lecture::getAverageGPA()
{
	return averageGPA;
}

// 更新课程信息
void Lecture::updateInfo(Database &database)
{
	bool validName = false, validCredit = false;
	std::string inputName;
	int inputCredit;
	std::string oldName = name;

	do
	{
		std::cout << "请输入名称：";
		std::cin >> inputName;
		if (database.queryLecture(inputName, false) && inputName != oldName)
		{
			std::cout << "该名称已存在，请重新输入！" << std::endl;
		}
		else
		{
			name = inputName;
			validName = true;
		}
	} while (!validName);

	do
	{
		std::cout << "请输入学分：";
		std::cin >> inputCredit;
		if (inputCredit < 0)
		{
			std::cout << "学分不能为负数，请重新输入！" << std::endl;
		}
		else
		{
			credit = inputCredit;
			validCredit = true;
		}
	} while (!validCredit);

	// TODO: update database
}

// 设置名称
void Lecture::setName(std::string inputName)
{
	name = inputName;
}

// 设置学分
void Lecture::setCredit(int inputCredit)
{
	credit = inputCredit;
}

// 设置学号
void Lecture::setStudentNo(std::vector<int> inputStudentNo)
{
	studentNo = inputStudentNo;
}

// 设置姓名
void Lecture::setStudentName(std::vector<std::string> inputStudentName)
{
	studentName = inputStudentName;
}

// 设置成绩
void Lecture::setStudentScore(std::vector<int> inputStudentScore)
{
	studentScore = inputStudentScore;
}

// 设置绩点
void Lecture::setStudentGPA(std::vector<double> inputStudentGPA)
{
	studentGPA = inputStudentGPA;
}

// 设置学生人数
void Lecture::setStudentNum(int inputStudentNum)
{
	studentNum = inputStudentNum;
}

// 设置总分
void Lecture::setTotalScore(int inputTotalScore)
{
	totalScore = inputTotalScore;
}

// 设置总绩点
void Lecture::setTotalGPA(double inputTotalGPA)
{
	totalGPA = inputTotalGPA;
}

// 设置平均分
void Lecture::setAverageScore(int inputAverageScore)
{
	averageScore = inputAverageScore;
}

// 设置平均绩点
void Lecture::setAverageGPA(double inputAverageGPA)
{
	averageGPA = inputAverageGPA;
}

// 添加学生
void Lecture::addStudent(int inputStudentNo, std::string inputStudentName, int inputStudentScore, double inputStudentGPA)
{
	studentNo.push_back(inputStudentNo);
	studentName.push_back(inputStudentName);
	studentScore.push_back(inputStudentScore);
	studentGPA.push_back(inputStudentGPA);
	studentNum++;
	totalScore += inputStudentScore;
	totalGPA += inputStudentGPA;
	averageScore = totalScore / studentNum;
	averageGPA = totalGPA / studentNum;
}

// 简略打印课程信息
void Lecture::printInfo(int widthName)
{
	std::cout << std::setw(widthName) << name
			  << std::setw(5) << "通用"
			  << std::setw(5) << credit
			  << std::setw(5) << studentNum
			  << std::setw(5) << std::setprecision(3) << averageScore
			  << std::setw(5) << std::setprecision(3) << averageGPA << std::endl;
}

// 详细打印课程信息
void Lecture::printLectureInfo()
{
	std::cout << std::endl;
	if (isDebugMode())
		std::cout << "     UID：" << uid << std::endl;
	std::cout << "课程名称：" << name << std::endl;
	std::cout << "课程学分：" << credit << std::endl;
	std::cout << "学生人数：" << studentNum << std::endl;
	std::cout << "平均分数：" << averageScore << std::endl;
	std::cout << "平均绩点：" << averageGPA << std::endl;
	int widthStudentNo = 5, widthStudentName = 5, widthStudentScore = 5, widthStudentGPA = 5;
	for (int i = 0; i < studentNum; i++)
	{
		if (std::to_string(studentNo[i]).length() >= widthStudentNo)
		{
			widthStudentNo = std::to_string(studentNo[i]).length() + 1;
		}
		if (studentName[i].length() >= widthStudentName)
		{
			widthStudentName = studentName[i].length() + 1;
		}
	}
	std::cout << std::setw(widthStudentNo) << "学号"
			  << std::setw(widthStudentName) << "姓名"
			  << std::setw(5) << "成绩"
			  << std::setw(5) << "绩点" << std::endl;
	for (int i = 0; i < studentNum; i++)
	{
		std::cout << std::setw(widthStudentNo) << studentNo[i]
				  << std::setw(widthStudentName) << studentName[i]
				  << std::setw(5) << studentScore[i]
				  << std::setw(5) << studentGPA[i] << std::endl;
	}
}

// 流输入操作符重载函数
std::istream &operator>>(std::istream &is, Lecture &lecture)
{
	is >> lecture.name >> lecture.credit >> lecture.studentNum >> lecture.totalScore >> lecture.totalGPA >> lecture.averageScore >> lecture.averageGPA;
	lecture.studentNo.resize(lecture.studentNum);
	lecture.studentName.resize(lecture.studentNum);
	lecture.studentScore.resize(lecture.studentNum);
	lecture.studentGPA.resize(lecture.studentNum);
	for (int i = 0; i < lecture.studentNum; i++)
	{
		is >> lecture.studentNo[i] >> lecture.studentName[i] >> lecture.studentScore[i] >> lecture.studentGPA[i];
	}
	return is;
}

// 流输出操作符重载函数
std::ostream &operator<<(std::ostream &os, Lecture &lecture)
{
	os << lecture.name << "\t"
	   << lecture.credit << "\t"
	   << lecture.studentNum << "\t"
	   << lecture.totalScore << "\t"
	   << lecture.totalGPA << "\t"
	   << lecture.averageScore << "\t"
	   << lecture.averageGPA << std::endl;
	for (int i = 0; i < lecture.studentNum; i++)
	{
		os << lecture.studentNo[i] << "\t"
		   << lecture.studentName[i] << "\t"
		   << lecture.studentScore[i] << "\t"
		   << lecture.studentGPA[i] << std::endl;
	}
	return os;
}
