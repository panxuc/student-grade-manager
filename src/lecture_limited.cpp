#include "commonheader.h"

// 构造函数
LectureLimited::LectureLimited()
{
}

// 析构函数
LectureLimited::~LectureLimited()
{
}

// 更新课程信息
void LectureLimited::updateInfo(Database &database)
{
	Lecture::updateInfo(database);
}

// 简略打印课程信息
void LectureLimited::printInfo(int widthName)
{
	std::cout << std::setw(widthName) << name
			  << std::setw(5) << "限选"
			  << std::setw(5) << credit
			  << std::setw(5) << studentNum
			  << std::setw(5) << std::setprecision(3) << averageScore
			  << std::setw(5) << std::setprecision(3) << averageGPA << std::endl;
}

// 详细打印课程信息
void LectureLimited::printLectureInfo()
{
	std::cout << std::endl;
	if (isDebugMode())
		std::cout << "     UID：" << uid << std::endl;
	std::cout << "课程名称：" << name << std::endl
			  << "课程类型：限选课" << std::endl
			  << "课程学分：" << credit << std::endl
			  << "学生人数：" << studentNum << std::endl
			  << "平均分数：" << averageScore << std::endl
			  << "平均绩点：" << averageGPA << std::endl;
	int widthStudentNo = 5, widthStudentName = 5;
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
std::istream &operator>>(std::istream &is, LectureLimited &lecture)
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
std::ostream &operator<<(std::ostream &os, LectureLimited &lecture)
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
