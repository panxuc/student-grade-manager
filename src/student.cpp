#include "commonheader.h"

// 构造函数
Student::Student()
{
	studentNo = 0;
	lectureName.clear();
	lectureScore.clear();
	lectureCredit.clear();
	lectureGPA.clear();
	lectureNum = 0;
	lecturePFNum = 0;
	totalScore = 0;
	totalCredit = 0;
	totalPFCredit = 0;
	totalGPA = 0;
	averageScore = 0;
	averageGPA = 0;
}

// 析构函数
Student::~Student() {}

// 获取学号
int Student::getStudentNo()
{
	return studentNo;
}

// 获取姓名
std::string Student::getName()
{
	return name;
}

// 获取各科名称
std::vector<std::string> Student::getLectureName()
{
	return lectureName;
}

// 获取各科类型
std::vector<LectureType> Student::getLectureType()
{
	return lectureType;
}

// 获取各科成绩
std::vector<int> Student::getLectureScore()
{
	return lectureScore;
}

// 获取各科学分
std::vector<int> Student::getLectureCredit()
{
	return lectureCredit;
}

// 获取各科学分绩点
std::vector<double> Student::getLectureGPA()
{
	return lectureGPA;
}

// 获取各科是否计PF
std::vector<int> Student::getLecturePF()
{
	return lecturePF;
}

// 获取课程数
int Student::getLectureNum()
{
	return lectureNum;
}

// 获取PF课程数
int Student::getLecturePFNum()
{
	return lecturePFNum;
}

// 获取总成绩
int Student::getTotalScore()
{
	return totalScore;
}

// 获取总学分
int Student::getTotalCredit()
{
	return totalCredit;
}

// 获取PF学分
int Student::getTotalPFCredit()
{
	return totalPFCredit;
}

// 获取总学分绩点
double Student::getTotalGPA()
{
	return totalGPA;
}

// 获取平均成绩
double Student::getAverageScore()
{
	return averageScore;
}

// 获取平均学分绩点
double Student::getAverageGPA()
{
	return averageGPA;
}

// 修改学生信息
void Student::updateInfo(Database &database)
{
	int oldStudentNo = studentNo;
	std::string oldName = name;
	bool validStudentNo = false, validName = false, validLecture = false, newLecture = false, moreLecture = false;
	int existLecture = 0;
	int inputStudentNo;
	std::string inputName;
	std::string tmpLectureName;
	int tmpLectureType;
	int tmpLectureScore;
	int tmpLectureCredit;
	double tmpLectureGPA;
	bool tmpLecturePF = false;
	LectureType destLectureType;

	do
	{
		std::cout << "请输入学号：";
		std::cin >> inputStudentNo;
		if (database.queryStudent(inputStudentNo, false) && oldStudentNo != inputStudentNo)
		{
			std::cout << "该学号已存在，请重新输入！" << std::endl;
		}
		else
		{
			studentNo = inputStudentNo;
			validStudentNo = true;
		}
	} while (!validStudentNo);

	do
	{
		std::cout << "请输入姓名：";
		std::cin >> inputName;
		if (database.queryStudent(inputName, false) && oldName != inputName)
		{
			std::cout << "该姓名已存在，请重新输入！" << std::endl;
		}
		else
		{
			name = inputName;
			validName = true;
		}
	} while (!validName);

	do
	{
		validLecture = newLecture = moreLecture = tmpLecturePF = false;
		existLecture = 0;
		std::cout << "请输入课程名称：";
		std::cin >> tmpLectureName;
		if (!lectureName.empty())
		{
			for (int i = 0; i < lectureName.size(); i++)
			{
				if (lectureName[i] == tmpLectureName)
				{
					existLecture = i + 1;
					break;
				}
			}
		}
		if (existLecture)
		{
			std::cout << "该学生已有该课程的成绩记录。是否覆盖？[Y/N]" << std::endl;
			int cover;
			cover = _getch();
			if (cover == 'Y' || cover == 'y')
			{
				destLectureType = (database.queryRequired(tmpLectureName, false) ? REQUIRED : (database.queryLimited(tmpLectureName, false) ? LIMITED : OPTIONAL));
				std::cout << "请输入课程成绩（0~100）：";
				std::cin >> tmpLectureScore;
				if (!std::cin)
				{
					std::cout << "输入错误！" << std::endl;
					std::cin.clear();
					std::cin.ignore();
					continue;
				}
				if (tmpLectureScore < 0 || tmpLectureScore > 100)
				{
					std::cout << "输入错误！" << std::endl;
					continue;
				}
				if (destLectureType == OPTIONAL)
				{
					std::cout << "该课程为任选课，得分是否计PF？[Y/N]" << std::endl;
					int inputLecturePF = _getch();
					if (inputLecturePF == 'Y' || inputLecturePF == 'y')
					{
						tmpLecturePF = true;
					}
				}
				lectureScore[existLecture - 1] = tmpLectureScore;
				lecturePF[existLecture - 1] = tmpLectureScore;
			}
		}
		else
		{
			if (database.queryLecture(tmpLectureName, false))
			{
				std::cout << "该课程已存在于数据库中。它的类型是";
				if (database.queryRequired(tmpLectureName, false))
				{
					std::cout << "必选课。" << std::endl;
					destLectureType = REQUIRED;
					tmpLectureCredit = database.findRequired(tmpLectureName)->getCredit();
				}
				else if (database.queryLimited(tmpLectureName, false))
				{
					std::cout << "限选课。" << std::endl;
					destLectureType = LIMITED;
					tmpLectureCredit = database.findLimited(tmpLectureName)->getCredit();
				}
				else
				{
					std::cout << "任选课。" << std::endl;
					destLectureType = OPTIONAL;
					tmpLectureCredit = database.findOptional(tmpLectureName)->getCredit();
				}
			}
			else
			{
				std::cout << "该课程不存在于数据库中。它的类型是什么？" << std::endl;
				std::cout << "1.必选课" << std::endl
						  << "2.限选课" << std::endl
						  << "3.任选课" << std::endl;
				tmpLectureType = _getch();
				if (tmpLectureType != '1' && tmpLectureType != '2' && tmpLectureType != '3')
				{
					std::cout << "输入错误！" << std::endl;
					continue;
				}
				switch (tmpLectureType)
				{
				case '1':
					destLectureType = REQUIRED;
					break;
				case '2':
					destLectureType = LIMITED;
					break;
				case '3':
					destLectureType = OPTIONAL;
					break;
				default:
					break;
				}
				std::cout << "请输入课程学分：";
				std::cin >> tmpLectureCredit;
				if (!std::cin)
				{
					std::cout << "输入错误！" << std::endl;
					std::cin.clear();
					std::cin.ignore();
					continue;
				}
				if (tmpLectureCredit < 0)
				{
					std::cout << "输入错误！" << std::endl;
					continue;
				}
				newLecture = true;
			}
			std::cout << "请输入课程成绩（0~100）：";
			std::cin >> tmpLectureScore;
			if (!std::cin)
			{
				std::cout << "输入错误！" << std::endl;
				std::cin.clear();
				std::cin.ignore();
				continue;
			}
			if (tmpLectureScore < 0 || tmpLectureScore > 100)
			{
				std::cout << "输入错误！" << std::endl;
				continue;
			}
			if (destLectureType == OPTIONAL)
			{
				std::cout << "该课程为任选课，得分是否计PF？[Y/N]" << std::endl;
				int inputLecturePF = _getch();
				if (inputLecturePF == 'Y' || inputLecturePF == 'y')
				{
					tmpLecturePF = true;
				}
			}
			lectureScore.push_back(tmpLectureScore);
			lectureName.push_back(tmpLectureName);
			lectureType.push_back(destLectureType);
			lectureCredit.push_back(tmpLectureCredit);
			lecturePF.push_back(tmpLecturePF);
			lectureNum++;
			if (tmpLecturePF)
				lecturePFNum++;
			validLecture = true;
			tmpLectureGPA = database.calculateGPA(tmpLectureScore);
			lectureGPA.push_back(tmpLectureGPA);
			if (!tmpLecturePF)
				totalScore += tmpLectureScore * tmpLectureCredit;
			totalCredit += tmpLectureCredit;
			if (tmpLecturePF)
				totalPFCredit += tmpLectureCredit;
			if (!tmpLecturePF)
				totalGPA += tmpLectureGPA * tmpLectureCredit;
			if (totalCredit - totalPFCredit > 0)
				averageScore = totalScore / (totalCredit - totalPFCredit);
			if (totalCredit - totalPFCredit > 0)
				averageGPA = totalGPA / (totalCredit - totalPFCredit);
			if (newLecture)
			{
				switch (tmpLectureType)
				{
				case '1':
					database.addRequired(tmpLectureName, tmpLectureCredit);
					destLectureType = REQUIRED;
					break;
				case '2':
					database.addLimited(tmpLectureName, tmpLectureCredit);
					destLectureType = LIMITED;
					break;
				case '3':
					database.addOptional(tmpLectureName, tmpLectureCredit);
					destLectureType = OPTIONAL;
					break;
				default:
					break;
				}
			}
			// database.addStudentToLecture(tmpLectureName, destLectureType, *this);
		}

		std::cout << "是否继续输入课程？[Y/N]" << std::endl;
		char tmp;
		tmp = _getch();
		if (tmp == 'Y' || tmp == 'y')
		{
			moreLecture = true;
		}
		else
		{
			moreLecture = false;
		}
	} while (!validLecture || moreLecture);
}

// 设置学号
void Student::setStudentNo(int inputStudentNo)
{
	studentNo = inputStudentNo;
}

// 设置姓名
void Student::setName(std::string inputName)
{
	name = inputName;
}

// 设置课程名称
void Student::setLectureName(std::vector<std::string> inputLectureName)
{
	lectureName = inputLectureName;
}

// 设置课程类型
void Student::setLectureType(std::vector<LectureType> inputLectureType)
{
	lectureType = inputLectureType;
}

// 设置课程学分
void Student::setLectureCredit(std::vector<int> inputLectureCredit)
{
	lectureCredit = inputLectureCredit;
}

// 设置课程成绩
void Student::setLectureScore(std::vector<int> inputLectureScore)
{
	lectureScore = inputLectureScore;
}

// 设置课程绩点
void Student::setLectureGPA(std::vector<double> inputLectureGPA)
{
	lectureGPA = inputLectureGPA;
}

// 设置课程PF
void Student::setLecturePF(std::vector<int> inputLecturePF)
{
	lecturePF = inputLecturePF;
}

// 设置课程数
void Student::setLectureNum(int inputLectureNum)
{
	lectureNum = inputLectureNum;
}

// 设置PF课程数
void Student::setLecturePFNum(int inputLecturePFNum)
{
	lecturePFNum = inputLecturePFNum;
}

// 设置总学分
void Student::setTotalCredit(int inputTotalCredit)
{
	totalCredit = inputTotalCredit;
}

// 设置PF学分
void Student::setTotalPFCredit(int inputTotalPFCredit)
{
	totalPFCredit = inputTotalPFCredit;
}

// 设置总成绩
void Student::setTotalScore(int inputTotalScore)
{
	totalScore = inputTotalScore;
}

// 设置总绩点
void Student::setTotalGPA(double inputTotalGPA)
{
	totalGPA = inputTotalGPA;
}

// 设置平均成绩
void Student::setAverageScore(double inputAverageScore)
{
	averageScore = inputAverageScore;
}

// 设置平均绩点
void Student::setAverageGPA(double inputAverageGPA)
{
	averageGPA = inputAverageGPA;
}

// 简略打印学生信息
void Student::printInfo(int widthStudentNo, int widthName)
{
	std::cout << std::setw(widthStudentNo) << studentNo
			  << std::setw(widthName) << name
			  << std::setw(5) << lectureNum
			  << std::setw(5) << totalCredit
			  << std::setw(5) << std::setprecision(3) << averageScore
			  << std::setw(5) << std::setprecision(3) << averageGPA << std::endl;
}

// 详细打印学生信息
void Student::printStudentInfo()
{
	std::cout<<std::endl;
	if (isDebugMode())
		std::cout << "     UID：" << uid << std::endl;
	std::cout << "    学号：" << studentNo << std::endl
			  << "    姓名：" << name << std::endl
			  << "  课程数：" << lectureNum << std::endl
			  << "  总学分：" << totalCredit << std::endl
			  << "平均成绩：" << averageScore << std::endl
			  << "平均绩点：" << averageGPA << std::endl;
	int widthLectureName = 9, widthLectureType = 5;
	for (int i = 0; i < lectureNum; i++)
	{
		if (lectureName[i].length() >= widthLectureName)
		{
			widthLectureName = lectureName[i].length() + 1;
		}
	}
	std::cout << std::setw(widthLectureName) << "课程名称"
			  << std::setw(widthLectureType) << "类型"
			  << std::setw(5) << "学分"
			  << std::setw(5) << "成绩"
			  << std::setw(5) << "绩点" << std::endl;
	for (int i = 0; i < lectureNum; i++)
	{
		if (!lecturePF[i])
		{
			std::cout << std::setw(widthLectureName) << lectureName[i]
					  << std::setw(widthLectureType) << ((lectureType[i] == REQUIRED) ? "必选" : ((lectureType[i] == LIMITED) ? "限选" : "任选"))
					  << std::setw(5) << lectureCredit[i]
					  << std::setw(5) << std::setprecision(3) << lectureScore[i]
					  << std::setw(5) << std::setprecision(3) << lectureGPA[i] << std::endl;
		}
		else
		{
			std::cout << std::setw(widthLectureName) << lectureName[i]
					  << std::setw(widthLectureType) << ((lectureType[i] == REQUIRED) ? "必选" : ((lectureType[i] == LIMITED) ? "限选" : "任选"))
					  << std::setw(5) << lectureCredit[i]
					  << std::setw(5) << "N/A"
					  << std::setw(5) << (lectureGPA[i] ? "P" : "F") << std::endl;
		}
	}
}

// 流输入操作符重载函数
std::istream &operator>>(std::istream &is, Student &student)
{
	is >> student.studentNo >> student.name >> student.totalCredit >> student.totalScore >> student.totalGPA >> student.averageScore >> student.averageGPA >> student.lectureNum >> student.lecturePFNum;
	student.lectureName.resize(student.lectureNum);
	student.lectureType.resize(student.lectureNum);
	student.lectureCredit.resize(student.lectureNum);
	student.lectureScore.resize(student.lectureNum);
	student.lectureGPA.resize(student.lectureNum);
	student.lecturePF.resize(student.lectureNum);
	int tmpLectureType;
	for (int i = 0; i < student.lectureNum; i++)
	{
		is >> student.lectureName[i] >> tmpLectureType >> student.lectureCredit[i] >> student.lectureScore[i] >> student.lectureGPA[i] >> student.lecturePF[i];
		student.lectureType[i] = (LectureType)tmpLectureType;
	}
	return is;
}

// 流输出操作符重载函数
std::ostream &operator<<(std::ostream &os, Student &student)
{
	os << student.studentNo << "\t"
	   << student.name << "\t"
	   << student.totalCredit << "\t"
	   << student.totalScore << "\t"
	   << student.totalGPA << "\t"
	   << student.averageScore << "\t"
	   << student.averageGPA << "\t"
	   << student.lectureNum << "\t"
	   << student.lecturePFNum << std::endl;
	for (int i = 0; i < student.lectureNum; i++)
	{
		os << student.lectureName[i] << "\t"
		   << student.lectureType[i] << "\t"
		   << student.lectureCredit[i] << "\t"
		   << student.lectureScore[i] << "\t"
		   << student.lectureGPA[i] << "\t"
		   << student.lecturePF[i] << std::endl;
	}
	return os;
}
