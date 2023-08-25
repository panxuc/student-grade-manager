#include "commonheader.h"

// 构造函数
Database::Database()
{
	studentList.makeEmpty();
	requiredList.makeEmpty();
	limitedList.makeEmpty();
	optionalList.makeEmpty();
	userList.makeEmpty();
	adminList.makeEmpty();
}

// 析构函数
Database::~Database()
{
	studentList.makeEmpty();
	requiredList.makeEmpty();
	limitedList.makeEmpty();
	optionalList.makeEmpty();
	userList.makeEmpty();
	adminList.makeEmpty();
}

// 从文件中读取
void Database::load()
{
	studentList.makeEmpty();
	requiredList.makeEmpty();
	limitedList.makeEmpty();
	optionalList.makeEmpty();
	try
	{
		loadStudent("savedata_student.dat");
		loadRequired("savedata_required.dat");
		loadLimited("savedata_limited.dat");
		loadOptional("savedata_optional.dat");
	}
	catch (FileException e)
	{
		throw e;
	}
}

// 向文件中保存
void Database::save()
{
	try
	{
		saveStudent("savedata_student.dat");
		saveRequired("savedata_required.dat");
		saveLimited("savedata_limited.dat");
		saveOptional("savedata_optional.dat");
	}
	catch (FileException e)
	{
		throw e;
	}
}

// 获取学生列表长度
int Database::getStudentListSize()
{
	return studentList.size();
}

// 获取必选课列表长度
int Database::getRequiredListSize()
{
	return requiredList.size();
}

// 获取限选课列表长度
int Database::getLimitedListSize()
{
	return limitedList.size();
}

// 获取任选课列表长度
int Database::getOptionalListSize()
{
	return optionalList.size();
}

// 从文件中读取学生信息
void Database::loadStudent(const std::string &filename)
{
	encrypt(filename);
	std::ifstream in(filename.c_str(), std::ios::in);
	Node<Student> *stu;
	// 打开文件成功
	if (in)
	{
		in.seekg(0, std::ios::end);
		int fileSize = in.tellg();
		in.seekg(std::ios::beg);
		while (fileSize - in.tellg() > 2)
		{
			stu = new Node<Student>;
			if (in >> stu->data)
			{
				studentList.insert_end(stu);
			}
			else
			{
				FileException e(filename, "operate", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(filename, "open", "read");
		throw e;
	}
	in.close();
	encrypt(filename);
}

// 从文件中读取必选课信息
void Database::loadRequired(const std::string &filename)
{
	encrypt(filename);
	std::ifstream in(filename.c_str(), std::ios::in);
	Node<LectureRequired> *req;
	// 打开文件成功
	if (in)
	{
		in.seekg(0, std::ios::end);
		int fileSize = in.tellg();
		in.seekg(std::ios::beg);
		while (fileSize - in.tellg() > 2)
		{
			req = new Node<LectureRequired>;
			if (in >> req->data)
			{
				requiredList.insert_end(req);
			}
			else
			{
				FileException e(filename, "operate", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(filename, "open", "read");
		throw e;
	}
	in.close();
	encrypt(filename);
}

// 从文件中读取限选课信息
void Database::loadLimited(const std::string &filename)
{
	encrypt(filename);
	std::ifstream in(filename.c_str(), std::ios::in);
	Node<LectureLimited> *lim;
	// 打开文件成功
	if (in)
	{
		in.seekg(0, std::ios::end);
		int fileSize = in.tellg();
		in.seekg(std::ios::beg);
		while (fileSize - in.tellg() > 2)
		{
			lim = new Node<LectureLimited>;
			if (in >> lim->data)
			{
				limitedList.insert_end(lim);
			}
			else
			{
				FileException e(filename, "operate", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(filename, "open", "read");
		throw e;
	}
	in.close();
	encrypt(filename);
}

// 从文件中读取任选课信息
void Database::loadOptional(const std::string &filename)
{
	encrypt(filename);
	std::ifstream in(filename.c_str(), std::ios::in);
	Node<LectureOptional> *opt;
	// 打开文件成功
	if (in)
	{
		in.seekg(0, std::ios::end);
		int fileSize = in.tellg();
		in.seekg(std::ios::beg);
		while (fileSize - in.tellg() > 2)
		{
			opt = new Node<LectureOptional>;
			if (in >> opt->data)
			{
				optionalList.insert_end(opt);
			}
			else
			{
				FileException e(filename, "operate", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(filename, "open", "read");
		throw e;
	}
	in.close();
	encrypt(filename);
}

// 向文件中保存学生信息
void Database::saveStudent(const std::string &filename)
{
	encrypt(filename);
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
	Node<Student> *stu;
	// 打开文件成功
	if (out)
	{
		stu = studentList.getFirst();
		while (stu != nullptr)
		{
			if (!(out << stu->data))
			{
				FileException e(filename, "operate", "write");
				throw e;
			}
			stu = stu->next;
		}
	}
	else
	{
		FileException e(filename, "open", "write");
		throw e;
	}
	out.close();
	encrypt(filename);
}

// 向文件中保存必选课信息
void Database::saveRequired(const std::string &filename)
{
	encrypt(filename);
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
	Node<LectureRequired> *req;
	// 打开文件成功
	if (out)
	{
		req = requiredList.getFirst();
		while (req != nullptr)
		{
			if (!(out << req->data))
			{
				FileException e(filename, "operate", "write");
				throw e;
			}
			req = req->next;
		}
	}
	else
	{
		FileException e(filename, "open", "write");
		throw e;
	}
	out.close();
	encrypt(filename);
}

// 向文件中保存限选课信息
void Database::saveLimited(const std::string &filename)
{
	encrypt(filename);
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
	Node<LectureLimited> *lim;
	// 打开文件成功
	if (out)
	{
		lim = limitedList.getFirst();
		while (lim != nullptr)
		{
			if (!(out << lim->data))
			{
				FileException e(filename, "operate", "write");
				throw e;
			}
			lim = lim->next;
		}
	}
	else
	{
		FileException e(filename, "open", "write");
		throw e;
	}
	out.close();
	encrypt(filename);
}

// 向文件中保存任选课信息
void Database::saveOptional(const std::string &filename)
{
	encrypt(filename);
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
	Node<LectureOptional> *opt;
	// 打开文件成功
	if (out)
	{
		opt = optionalList.getFirst();
		while (opt != nullptr)
		{
			if (!(out << opt->data))
			{
				FileException e(filename, "operate", "write");
				throw e;
			}
			opt = opt->next;
		}
	}
	else
	{
		FileException e(filename, "open", "write");
		throw e;
	}
	out.close();
	encrypt(filename);
}

// 加密文件
void Database::encrypt(const std::string &filename)
{
	std::vector<std::string> codestr;
	std::ifstream in(filename.c_str(), std::ios::in);
	std::string tmp;
	while (std::getline(in, tmp))
	{
		codestr.push_back(tmp);
	}
	in.close();
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
	for (int i = 0; i < codestr.size(); i++)
	{
		for (int j = 0; j < codestr[i].size(); j++)
		{
			if ((char)~codestr[i][j] != 0x1a)
			{
				out << (char)~codestr[i][j];
			}
			else
			{
				out << (char)codestr[i][j];
			}
		}
		out << std::endl;
	}
	out.close();
}

// 更安全的加密文件
void Database::encrypt_key(const std::string &filename, const std::string &keyFilename)
{
	std::string key;
	std::ifstream key_in(keyFilename.c_str(), std::ios::in);
	std::getline(key_in, key);
	key_in.close();
	std::vector<std::string> codestr;
	std::ifstream in(filename.c_str(), std::ios::in);
	std::string tmp;
	while (std::getline(in, tmp))
	{
		codestr.push_back(tmp);
	}
	in.close();
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
	for (int i = 0; i < codestr.size(); i++)
	{
		for (int j = 0; j < codestr[i].size(); j++)
		{
			out << (codestr[i][j] ^ key[(i + j) % key.length()]);
		}
		out << std::endl;
	}
	out.close();
}

// 生成密钥
void Database::key_gen(const std::string &filename)
{
	std::string key = std::to_string(time(0));
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
	out << key;
	out.close();
}

// 时间戳转换
std::string Database::timeStampToString(const time_t &timeStamp)
{
	struct tm *timeinfo;
	char buffer[80];
	timeinfo = localtime(&timeStamp);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
	return std::string(buffer);
}

// 以姓名为准删除学生
bool Database::deleteStudent(const std::string &name)
{
	Node<Student> *stu = studentList.getFirst();
	bool flag = false;
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getName() == name)
			{
				stu->data.printStudentInfo();
				std::cout << "是否确认删除？[Y/N]" << std::endl;
				char input;
				std::cin >> input;
				if (input == 'Y' || input == 'y')
				{
					studentList.remove(stu);
					flag = true;
					std::cout << "删除成功！" << std::endl;
				}
				else
				{
					std::cout << "取消删除！" << std::endl;
				}
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return flag;
}

// 以学号为准删除学生
bool Database::deleteStudent(int studentNo)
{
	Node<Student> *stu = studentList.getFirst();
	bool flag = false;
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getStudentNo() == studentNo)
			{
				stu->data.printStudentInfo();
				std::cout << "是否确认删除？[Y/N]" << std::endl;
				char input;
				input = _getch();
				if (input == 'Y' || input == 'y')
				{
					studentList.remove(stu);
					flag = true;
					std::cout << "删除成功！" << std::endl;
				}
				else
				{
					std::cout << "取消删除！" << std::endl;
				}
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return flag;
}

// 以课程名称为准删除必选课
bool Database::deleteRequired(const std::string &name)
{
	Node<LectureRequired> *req = requiredList.getFirst();
	bool flag = false;
	if (req != nullptr)
	{
		do
		{
			if (req->data.getName() == name)
			{
				req->data.printLectureInfo();
				std::cout << "是否确认删除？[Y/N]" << std::endl;
				char input;
				std::cin >> input;
				if (input == 'Y' || input == 'y')
				{
					requiredList.remove(req);
					flag = true;
					std::cout << "删除成功！" << std::endl;
				}
				else
				{
					std::cout << "取消删除！" << std::endl;
				}
			}
			req = requiredList.getNext();
		} while (req != nullptr);
	}
	return flag;
}

// 以课程名称为准删除限选课
bool Database::deleteLimited(const std::string &name)
{
	Node<LectureLimited> *lim = limitedList.getFirst();
	bool flag = false;
	if (lim != nullptr)
	{
		do
		{
			if (lim->data.getName() == name)
			{
				lim->data.printLectureInfo();
				std::cout << "是否确认删除？[Y/N]" << std::endl;
				char input;
				std::cin >> input;
				if (input == 'Y' || input == 'y')
				{
					limitedList.remove(lim);
					flag = true;
					std::cout << "删除成功！" << std::endl;
				}
				else
				{
					std::cout << "取消删除！" << std::endl;
				}
			}
			lim = limitedList.getNext();
		} while (lim != nullptr);
	}
	return flag;
}

// 以课程名称为准删除任选课
bool Database::deleteOptional(const std::string &name)
{
	Node<LectureOptional> *opt = optionalList.getFirst();
	bool flag = false;
	if (opt != nullptr)
	{
		do
		{
			if (opt->data.getName() == name)
			{
				opt->data.printLectureInfo();
				std::cout << "是否确认删除？[Y/N]" << std::endl;
				char input;
				std::cin >> input;
				if (input == 'Y' || input == 'y')
				{
					optionalList.remove(opt);
					flag = true;
					std::cout << "删除成功！" << std::endl;
				}
				else
				{
					std::cout << "取消删除！" << std::endl;
				}
			}
			opt = optionalList.getNext();
		} while (opt != nullptr);
	}
	return flag;
}

// 新增学生
void Database::addStudent()
{
	Node<Student> *stu = new Node<Student>;
	stu->data.updateInfo(*this);
	studentList.insert_end(stu);
}

// 新增必选课
void Database::addRequired(const std::string &name, int credit)
{
	Node<LectureRequired> *req = new Node<LectureRequired>;
	req->data.setName(name);
	req->data.setCredit(credit);
	requiredList.insert_end(req);
}

// 新增限选课
void Database::addLimited(const std::string &name, int credit)
{
	Node<LectureLimited> *lim = new Node<LectureLimited>;
	lim->data.setName(name);
	lim->data.setCredit(credit);
	limitedList.insert_end(lim);
}

// 新增任选课
void Database::addOptional(const std::string &name, int credit)
{
	Node<LectureOptional> *opt = new Node<LectureOptional>;
	opt->data.setName(name);
	opt->data.setCredit(credit);
	optionalList.insert_end(opt);
}

// 将学生信息添加到课程
void Database::addStudentToLecture(const std::string &name, LectureType type, Student &stu)
{
	int dest = 0;
	for (int i = 0; i < stu.getLectureName().size(); i++)
	{
		if (stu.getLectureName()[i] == name)
		{
			dest = i;
			break;
		}
	}
	switch (type)
	{
	case REQUIRED:
	{
		Node<LectureRequired> *req = requiredList.getFirst();
		if (req != nullptr)
		{
			do
			{
				if (req->data.getName() == name)
				{
					req->data.addStudent(stu.getStudentNo(), stu.getName(), stu.getLectureScore()[dest], stu.getLectureGPA()[dest]);
				}
				req = requiredList.getNext();
			} while (req != nullptr);
		}
		break;
	}
	case LIMITED:
	{
		Node<LectureLimited> *lim = limitedList.getFirst();
		if (lim != nullptr)
		{
			do
			{
				if (lim->data.getName() == name)
				{
					lim->data.addStudent(stu.getStudentNo(), stu.getName(), stu.getLectureScore()[dest], stu.getLectureGPA()[dest]);
				}
				lim = limitedList.getNext();
			} while (lim != nullptr);
		}
		break;
	}
	case OPTIONAL:
	{
		Node<LectureOptional> *opt = optionalList.getFirst();
		if (opt != nullptr)
		{
			do
			{
				if (opt->data.getName() == name)
				{
					opt->data.addStudent(stu.getStudentNo(), stu.getName(), stu.getLectureScore()[dest], stu.getLectureGPA()[dest], stu.getLecturePF()[dest]);
				}
				opt = optionalList.getNext();
			} while (opt != nullptr);
		}
		break;
	}
	default:
		break;
	}
}

////输出学生信息
// void Database::displayStudent(const std::string& name)
//{
//	Node<Student>* stu = studentList.getFirst();
//	if (stu != nullptr)
//	{
//		do
//		{
//			if (stu->data.getName() == name)
//			{
//				stu->data.printStudentInfo();
//			}
//			stu = studentList.getNext();
//		} while (stu != nullptr);
//	}
// }
//
////输出学生信息
// void Database::displayStudent(int studentNo)
//{
//	Node<Student>* stu = studentList.getFirst();
//	if (stu != nullptr)
//	{
//		do
//		{
//			if (stu->data.getStudentNo() == studentNo)
//			{
//				stu->data.printStudentInfo();
//			}
//			stu = studentList.getNext();
//		} while (stu != nullptr);
//	}
// }
//
////输出课程信息
// void Database::displayLecture(const std::string& name)
//{
//	displayRequired(name);
//	displayLimited(name);
//	displayOptional(name);
// }
//
////输出必选课信息
// void Database::displayRequired(const std::string& name)
//{
//	Node<LectureRequired>* req = requiredList.getFirst();
//	if (req != nullptr)
//	{
//		do
//		{
//			if (req->data.getName() == name)
//			{
//				req->data.printLectureInfo();
//			}
//			req = requiredList.getNext();
//		} while (req != nullptr);
//	}
// }
//
////输出限选课信息
// void Database::displayLimited(const std::string& name)
//{
//	Node<LectureLimited>* lim = limitedList.getFirst();
//	if (lim != nullptr)
//	{
//		do
//		{
//			if (lim->data.getName() == name)
//			{
//				lim->data.printLectureInfo();
//			}
//			lim = limitedList.getNext();
//		} while (lim != nullptr);
//	}
// }
//
////输出任选课信息
// void Database::displayOptional(const std::string& name)
//{
//	Node<LectureOptional>* opt = optionalList.getFirst();
//	if (opt != nullptr)
//	{
//		do
//		{
//			if (opt->data.getName() == name)
//			{
//				opt->data.printLectureInfo();
//			}
//			opt = optionalList.getNext();
//		} while (opt != nullptr);
//	}
// }
//
////输出所有学生
// int Database::displayAllStudent()
//{
//	Node<Student>* stu = studentList.getFirst();
//	int count = 0;
//	if (stu != nullptr)
//	{
//		do
//		{
//			stu->data.printStudentInfo();
//			count++;
//			stu = studentList.getNext();
//		} while (stu != nullptr);
//	}
//	return count;
// }
//
////输出所有课程
// int Database::displayAllLecture(LectureType type)
//{
//	Node<LectureRequired>* req = requiredList.getFirst();
//	Node<LectureLimited>* lim = limitedList.getFirst();
//	Node<LectureOptional>* opt = optionalList.getFirst();
//	int count = 0;
//	switch (type)
//	{
//	case DEFAULT:
//		if (req != nullptr)
//		{
//			do
//			{
//				req->data.printLectureInfo();
//				count++;
//				req = requiredList.getNext();
//			} while (req != nullptr);
//		}
//		if (lim != nullptr)
//		{
//			do
//			{
//				lim->data.printLectureInfo();
//				count++;
//				lim = limitedList.getNext();
//			} while (lim != nullptr);
//		}
//		if (opt != nullptr)
//		{
//			do
//			{
//				opt->data.printLectureInfo();
//				count++;
//				opt = optionalList.getNext();
//			} while (opt != nullptr);
//		}
//		break;
//	case REQUIRED:
//		if (req != nullptr)
//		{
//			do
//			{
//				req->data.printLectureInfo();
//				count++;
//				req = requiredList.getNext();
//			} while (req != nullptr);
//		}
//		break;
//	case LIMITED:
//		if (lim != nullptr)
//		{
//			do
//			{
//				lim->data.printLectureInfo();
//				count++;
//				lim = limitedList.getNext();
//			} while (lim != nullptr);
//		}
//		break;
//	case OPTIONAL:
//		if (opt != nullptr)
//		{
//			do
//			{
//				opt->data.printLectureInfo();
//				count++;
//				opt = optionalList.getNext();
//			} while (opt != nullptr);
//		}
//		break;
//	default:
//		break;
//	}
//	return count;
// }

// 按名称修改学生信息
bool Database::modifyStudent(const std::string &name)
{
	Node<Student> *stu = studentList.getFirst();
	bool flag = false;
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getName() == name)
			{
				flag = true;
				stu->data.printStudentInfo();
				std::cout << "是否确认修改？[Y/N]" << std::endl;
				char input;
				std::cin >> input;
				if (input == 'Y' || input == 'y')
				{
					stu->data.updateInfo(*this);
					std::cout << "修改成功！" << std::endl;
				}
				else
				{
					std::cout << "取消修改！" << std::endl;
				}
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return flag;
}

// 按学号修改学生信息
bool Database::modifyStudent(int studentNo)
{
	Node<Student> *stu = studentList.getFirst();
	bool flag = false;
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getStudentNo() == studentNo)
			{
				flag = true;
				stu->data.printStudentInfo();
				std::cout << "是否确认修改？[Y/N]" << std::endl;
				char input;
				std::cin >> input;
				if (input == 'Y' || input == 'y')
				{
					stu->data.updateInfo(*this);
					std::cout << "修改成功！" << std::endl;
				}
				else
				{
					std::cout << "取消修改！" << std::endl;
				}
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return flag;
}

// 按名称修改课程信息
bool Database::modifyLecture(const std::string &name)
{
	bool flag = false;
	flag = modifyRequired(name) + modifyLimited(name) + modifyOptional(name);
	return flag;
}

// 按名称修改必选课信息
bool Database::modifyRequired(const std::string &name)
{
	Node<LectureRequired> *req = requiredList.getFirst();
	bool flag = false;
	if (req != nullptr)
	{
		do
		{
			if (req->data.getName() == name)
			{
				flag = true;
				req->data.printLectureInfo();
				std::cout << "是否确认修改？[Y/N]" << std::endl;
				char input;
				input = _getch();
				if (input == 'Y' || input == 'y')
				{
					req->data.updateInfo(*this);
					std::cout << "修改成功！" << std::endl;
				}
				else
				{
					std::cout << "取消修改！" << std::endl;
				}
			}
			req = requiredList.getNext();
		} while (req != nullptr);
	}
	return flag;
}

// 按名称修改限选课信息
bool Database::modifyLimited(const std::string &name)
{
	Node<LectureLimited> *lim = limitedList.getFirst();
	bool flag = false;
	if (lim != nullptr)
	{
		do
		{
			if (lim->data.getName() == name)
			{
				flag = true;
				lim->data.printLectureInfo();
				std::cout << "是否确认修改？[Y/N]" << std::endl;
				char input;
				input = _getch();
				if (input == 'Y' || input == 'y')
				{
					lim->data.updateInfo(*this);
					std::cout << "修改成功！" << std::endl;
				}
				else
				{
					std::cout << "取消修改！" << std::endl;
				}
			}
			lim = limitedList.getNext();
		} while (lim != nullptr);
	}
	return flag;
}

// 按名称修改任选课信息
bool Database::modifyOptional(const std::string &name)
{
	Node<LectureOptional> *opt = optionalList.getFirst();
	bool flag = false;
	if (opt != nullptr)
	{
		do
		{
			if (opt->data.getName() == name)
			{
				flag = true;
				opt->data.printLectureInfo();
				std::cout << "是否确认修改？[Y/N]" << std::endl;
				char input;
				input = _getch();
				if (input == 'Y' || input == 'y')
				{
					opt->data.updateInfo(*this);
					std::cout << "修改成功！" << std::endl;
				}
				else
				{
					std::cout << "取消修改！" << std::endl;
				}
			}
			opt = optionalList.getNext();
		} while (opt != nullptr);
	}
	return flag;
}

// 按名称查询学生信息
int Database::queryStudent(const std::string &name, bool display)
{
	Node<Student> *stu = studentList.getFirst();
	int count = 0;
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getName() == name)
			{
				if (display)
					stu->data.printStudentInfo();
				count++;
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return count;
}

// 按学号查询学生信息
int Database::queryStudent(int studentNo, bool display)
{
	Node<Student> *stu = studentList.getFirst();
	int count = 0;
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getStudentNo() == studentNo)
			{
				if (display)
					stu->data.printStudentInfo();
				count++;
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return count;
}

// 按名称查询课程信息
int Database::queryLecture(const std::string &name, bool display)
{
	int count = 0;
	count = queryRequired(name, display) + queryLimited(name, display) + queryOptional(name, display);
	return count;
}

// 按名称查询必选课信息
int Database::queryRequired(const std::string &name, bool display)
{
	Node<LectureRequired> *req = requiredList.getFirst();
	int count = 0;
	if (req != nullptr)
	{
		do
		{
			if (req->data.getName() == name)
			{
				if (display)
					req->data.printLectureInfo();
				count++;
			}
			req = requiredList.getNext();
		} while (req != nullptr);
	}
	return count;
}

// 按名称查询限选课信息
int Database::queryLimited(const std::string &name, bool display)
{
	Node<LectureLimited> *lim = limitedList.getFirst();
	int count = 0;
	if (lim != nullptr)
	{
		do
		{
			if (lim->data.getName() == name)
			{
				if (display)
					lim->data.printLectureInfo();
				count++;
			}
			lim = limitedList.getNext();
		} while (lim != nullptr);
	}
	return count;
}

// 按名称查询任选课信息
int Database::queryOptional(const std::string &name, bool display)
{
	Node<LectureOptional> *opt = optionalList.getFirst();
	int count = 0;
	if (opt != nullptr)
	{
		do
		{
			if (opt->data.getName() == name)
			{
				if (display)
					opt->data.printLectureInfo();
				count++;
			}
			opt = optionalList.getNext();
		} while (opt != nullptr);
	}
	return count;
}

// 按名称找到学生信息
Student *Database::findStudent(const std::string &name)
{
	Node<Student> *stu = studentList.getFirst();
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getName() == name)
			{
				return &stu->data;
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return nullptr;
}

// 按学号找到学生信息
Student *Database::findStudent(int studentNo)
{
	Node<Student> *stu = studentList.getFirst();
	if (stu != nullptr)
	{
		do
		{
			if (stu->data.getStudentNo() == studentNo)
			{
				return &stu->data;
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
	return nullptr;
}

// 按名称找到课程信息
Lecture *Database::findLecture(const std::string &name)
{
	Lecture *lec = findRequired(name);
	if (lec != nullptr)
		return lec;
	lec = findLimited(name);
	if (lec != nullptr)
		return lec;
	lec = findOptional(name);
	if (lec != nullptr)
		return lec;
	return nullptr;
}

// 按名称找到必选课信息
LectureRequired *Database::findRequired(const std::string &name)
{
	Node<LectureRequired> *req = requiredList.getFirst();
	if (req != nullptr)
	{
		do
		{
			if (req->data.getName() == name)
			{
				return &req->data;
			}
			req = requiredList.getNext();
		} while (req != nullptr);
	}
	return nullptr;
}

// 按名称找到限选课信息
LectureLimited *Database::findLimited(const std::string &name)
{
	Node<LectureLimited> *lim = limitedList.getFirst();
	if (lim != nullptr)
	{
		do
		{
			if (lim->data.getName() == name)
			{
				return &lim->data;
			}
			lim = limitedList.getNext();
		} while (lim != nullptr);
	}
	return nullptr;
}

// 按名称找到任选课信息
LectureOptional *Database::findOptional(const std::string &name)
{
	Node<LectureOptional> *opt = optionalList.getFirst();
	if (opt != nullptr)
	{
		do
		{
			if (opt->data.getName() == name)
			{
				return &opt->data;
			}
			opt = optionalList.getNext();
		} while (opt != nullptr);
	}
	return nullptr;
}

// 按关键列排序学生，direction为1表示升序，为-1表示降序，keycol为关键列
// 关键列：0-studentNo，1-name，2-totalScore，3-totalCredit，4-totalGPA，5-averageScore，6-averageGPA
void Database::sortStudent(int direction, int keycol)
{
	Student **head;
	int length = studentList.size();
	if (length > 0)
	{
		head = new Student *[length];
		Node<Student> *tmp = studentList.getFirst();
		int cnt = 0;
		do
		{
			head[cnt] = &tmp->data;
			tmp = studentList.getNext();
			cnt++;
		} while (tmp != nullptr);
		sortStudentCustom(head, length, direction, keycol);
		int widthStudentNo = 5, widthName = 5;
		for (cnt = 0; cnt < length; cnt++)
		{
			if (std::to_string(head[cnt]->getStudentNo()).length() > widthStudentNo)
				widthStudentNo = std::to_string(head[cnt]->getStudentNo()).length() + 1;
			if (head[cnt]->getName().length() > widthName)
				widthName = head[cnt]->getName().length() + 1;
		}
		std::cout.width(widthStudentNo);
		std::cout << "学号";
		std::cout.width(widthName);
		std::cout << "姓名";
		std::cout.width(5);
		std::cout << "课数";
		std::cout.width(5);
		std::cout << "学分";
		std::cout.width(5);
		std::cout << "均分";
		std::cout.width(5);
		std::cout << "均绩" << std::endl;
		for (cnt = 0; cnt < length; cnt++)
			head[cnt]->printInfo(widthStudentNo, widthName);
		delete[] head;
	}
	else
	{
		std::cout << "学生信息为空！" << std::endl;
	}
}

// 按关键列排序课程，direction为1表示升序，为-1表示降序，keycol为关键列
// 关键列：0-name，1-credit，2-studentNum，3-averageScore，4-averageGPA
void Database::sortLecture(LectureType type, int direction, int keycol)
{
	Lecture **head;
	int length = 0;
	switch (type)
	{
	case DEFAULT:
		length = requiredList.size() + limitedList.size() + optionalList.size();
		if (length > 0)
		{
			head = new Lecture *[length];
			int cnt = 0;
			Node<LectureRequired> *req = requiredList.getFirst();
			if (req != nullptr)
			{
				do
				{
					head[cnt] = &req->data;
					req = requiredList.getNext();
					cnt++;
				} while (req != nullptr);
			}
			Node<LectureLimited> *lim = limitedList.getFirst();
			if (lim != nullptr)
			{
				do
				{
					head[cnt] = &lim->data;
					lim = limitedList.getNext();
					cnt++;
				} while (lim != nullptr);
			}
			Node<LectureOptional> *opt = optionalList.getFirst();
			if (opt != nullptr)
			{
				do
				{
					head[cnt] = &opt->data;
					opt = optionalList.getNext();
					cnt++;
				} while (opt != nullptr);
			}
			sortLectureCustom(head, length, direction, keycol);
			int widthName = 5;
			for (cnt = 0; cnt < length; cnt++)
			{
				if (head[cnt]->getName().length() > widthName)
					widthName = head[cnt]->getName().length() + 1;
			}
			std::cout.width(widthName);
			std::cout << "名称";
			std::cout.width(5);
			std::cout << "类型";
			std::cout.width(5);
			std::cout << "学分";
			std::cout.width(5);
			std::cout << "人数";
			std::cout.width(5);
			std::cout << "均分";
			std::cout.width(5);
			std::cout << "均绩" << std::endl;
			for (cnt = 0; cnt < length; cnt++)
				head[cnt]->printInfo(widthName);
			delete[] head;
		}
		else
		{
			std::cout << "课程信息为空！" << std::endl;
		}
		break;
	case REQUIRED:
		length = requiredList.size();
		if (length > 0)
		{
			head = new Lecture *[length];
			int cnt = 0;
			Node<LectureRequired> *req = requiredList.getFirst();
			if (req != nullptr)
			{
				do
				{
					head[cnt] = &req->data;
					req = requiredList.getNext();
					cnt++;
				} while (req != nullptr);
			}
			sortLectureCustom(head, length, direction, keycol);
			int widthName = 5;
			for (cnt = 0; cnt < length; cnt++)
			{
				if (head[cnt]->getName().length() > widthName)
					widthName = head[cnt]->getName().length() + 1;
			}
			std::cout.width(widthName);
			std::cout << "名称";
			std::cout.width(5);
			std::cout << "类型";
			std::cout.width(5);
			std::cout << "学分";
			std::cout.width(5);
			std::cout << "人数";
			std::cout.width(5);
			std::cout << "均分";
			std::cout.width(5);
			std::cout << "均绩" << std::endl;
			for (cnt = 0; cnt < length; cnt++)
				head[cnt]->printInfo(widthName);
			delete[] head;
		}
		else
		{
			std::cout << "必选课信息为空！" << std::endl;
		}
		break;
	case LIMITED:
		length = limitedList.size();
		if (length > 0)
		{
			head = new Lecture *[length];
			int cnt = 0;
			Node<LectureLimited> *lim = limitedList.getFirst();
			if (lim != nullptr)
			{
				do
				{
					head[cnt] = &lim->data;
					lim = limitedList.getNext();
					cnt++;
				} while (lim != nullptr);
			}
			sortLectureCustom(head, length, direction, keycol);
			int widthName = 5;
			for (cnt = 0; cnt < length; cnt++)
			{
				if (head[cnt]->getName().length() > widthName)
					widthName = head[cnt]->getName().length() + 1;
			}
			std::cout.width(widthName);
			std::cout << "名称";
			std::cout.width(5);
			std::cout << "类型";
			std::cout.width(5);
			std::cout << "学分";
			std::cout.width(5);
			std::cout << "人数";
			std::cout.width(5);
			std::cout << "均分";
			std::cout.width(5);
			std::cout << "均绩" << std::endl;
			for (cnt = 0; cnt < length; cnt++)
				head[cnt]->printInfo(widthName);
			delete[] head;
		}
		else
		{
			std::cout << "限选课信息为空！" << std::endl;
		}
		break;
	case OPTIONAL:
		length = optionalList.size();
		if (length > 0)
		{
			head = new Lecture *[length];
			int cnt = 0;
			Node<LectureOptional> *opt = optionalList.getFirst();
			if (opt != nullptr)
			{
				do
				{
					head[cnt] = &opt->data;
					opt = optionalList.getNext();
					cnt++;
				} while (opt != nullptr);
			}
			sortLectureCustom(head, length, direction, keycol);
			int widthName = 5;
			for (cnt = 0; cnt < length; cnt++)
			{
				if (head[cnt]->getName().length() > widthName)
					widthName = head[cnt]->getName().length() + 1;
			}
			std::cout.width(widthName);
			std::cout << "名称";
			std::cout.width(5);
			std::cout << "类型";
			std::cout.width(5);
			std::cout << "学分";
			std::cout.width(5);
			std::cout << "人数";
			std::cout.width(5);
			std::cout << "均分";
			std::cout.width(5);
			std::cout << "均绩" << std::endl;
			for (cnt = 0; cnt < length; cnt++)
				head[cnt]->printInfo(widthName);
			delete[] head;
		}
		else
		{
			std::cout << "任选课信息为空！" << std::endl;
		}
		break;
	default:
		std::cout << "课程类型错误！" << std::endl;
		break;
	}
}

// 学生排序函数，direction为1表示升序，为-1表示降序，keycol为关键列
// 关键列：0-studentNo，1-name，2-totalScore，3-totalCredit，4-totalGPA，5-averageScore，6-averageGPA
void Database::sortStudentCustom(Student **head, int length, int direction, int keycol)
{
	Student *tmp;
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < length - 1; i++)
		{
			if (compareStudent(head[i], head[i + 1], direction, keycol) < 0)
			{
				tmp = head[i];
				head[i] = head[i + 1];
				head[i + 1] = tmp;
				flag = true;
			}
		}
	} while (flag);
}

// 课程排序函数，direction为1表示升序，为-1表示降序，keycol为关键列
// 关键列：0-name，1-credit，2-studentNum，3-averageScore，4-averageGPA
void Database::sortLectureCustom(Lecture **head, int length, int direction, int keycol)
{
	Lecture *tmp;
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < length - 1; i++)
		{
			if (compareLecture(head[i], head[i + 1], direction, keycol) < 0)
			{
				tmp = head[i];
				head[i] = head[i + 1];
				head[i + 1] = tmp;
				flag = true;
			}
		}
	} while (flag);
}

// 学生比较函数，direction为1表示升序，为-1表示降序，keycol为关键列
// 关键列：0-studentNo，1-name，2-totalScore，3-totalCredit，4-totalGPA，5-averageScore，6-averageGPA
double Database::compareStudent(Student *a, Student *b, int direction, int keycol)
{
	double compare = 0;
	switch (keycol)
	{
	case 0:
		compare = a->getStudentNo() - b->getStudentNo();
		break;
	case 1:
		compare = (a->getName() > b->getName());
		break;
	case 2:
		compare = a->getTotalScore() - b->getTotalScore();
		break;
	case 3:
		compare = a->getTotalCredit() - b->getTotalCredit();
		break;
	case 4:
		compare = a->getTotalGPA() - b->getTotalGPA();
		break;
	case 5:
		compare = a->getAverageScore() - b->getAverageScore();
		break;
	case 6:
		compare = a->getAverageGPA() - b->getAverageGPA();
		break;
	default:
		compare = 0;
		break;
	}
	return compare * direction;
}

// 课程比较函数，direction为1表示升序，为-1表示降序，keycol为关键列
// 关键列：0-name，1-credit，2-studentNum，3-averageScore，4-averageGPA
double Database::compareLecture(Lecture *a, Lecture *b, int direction, int keycol)
{
	double compare = 0;
	switch (keycol)
	{
	case 0:
		compare = (a->getName() > b->getName());
		break;
	case 1:
		compare = a->getCredit() - b->getCredit();
		break;
	case 2:
		compare = a->getStudentNum() - b->getStudentNum();
		break;
	case 3:
		compare = a->getAverageScore() - b->getAverageScore();
		break;
	case 4:
		compare = a->getAverageGPA() - b->getAverageGPA();
		break;
	default:
		compare = 0;
		break;
	}
	return compare * direction;
}

// 打印全部学生信息
void Database::printStudent()
{
	std::ofstream out("output_student_all.md", std::ios::out | std::ios::trunc);
	if (!out.is_open())
	{
		std::cerr << "Error: cannot open file \""
				  << "output_student_all.md"
				  << "\"." << std::endl;
		return;
	}
	out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
		<< std::endl
		<< "<h2><center>全部学生成绩</center></h2>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>学号</th><th>姓名</th><th>总学分</th><th>平均成绩</th><th>平均绩点</th></tr>" << std::endl;
	Student **head;
	int length = studentList.size();
	if (length > 0)
	{
		head = new Student *[length];
		Node<Student> *tmp = studentList.getFirst();
		int cnt = 0;
		do
		{
			head[cnt] = &tmp->data;
			tmp = studentList.getNext();
			cnt++;
		} while (tmp != nullptr);
		sortStudentCustom(head, length, -1, 0);
		for (cnt = 0; cnt < length; cnt++)
		{
			out << "<tr><td>" << head[cnt]->getStudentNo()
				<< "</td><td>" << head[cnt]->getName()
				<< "</td><td>" << head[cnt]->getTotalCredit()
				<< "</td><td>" << head[cnt]->getAverageScore()
				<< "</td><td>" << head[cnt]->getAverageGPA() << "</td></tr>" << std::endl;
		}
		delete[] head;
	}
	else
	{
		out << "<tr><td colspan=\"5\">无学生信息</td></tr>" << std::endl;
	}
	out << "</table>" << std::endl
		<< std::endl
		<< "打印时间：" << timeStampToString(time(0)) << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩单说明</center></h1>" << std::endl
		<< std::endl
		<< "1. 本成绩单按照学号升序排列" << std::endl
		<< "2. 本成绩单仅包含全部学生的总成绩信息" << std::endl
		<< "3. 本成绩单仅供参考，不作为最终成绩" << std::endl
		<< "4. 本成绩单由学生成绩管理系统自动生成" << std::endl
		<< "5. 本成绩单最终解释权归××大学所有" << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩记载说明</center></h1>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>等级制成绩</th><th>绩点</th><th>对应百分制成绩范围</th></tr>" << std::endl
		<< "<tr><td>A+</td><td rowspan=\"3\">4.0</td><td rowspan=\"2\">95~100</td></tr>" << std::endl
		<< "<tr><td>A</td></tr>" << std::endl
		<< "<tr><td>A-</td><td>90~94</td></tr>" << std::endl
		<< "<tr><td>B+</td><td>3.6</td><td>85~89</td></tr>" << std::endl
		<< "<tr><td>B</td><td>3.3</td><td>80~84</td></tr>" << std::endl
		<< "<tr><td>B-</td><td>3.0</td><td>77~79</td></tr>" << std::endl
		<< "<tr><td>C+</td><td>2.6</td><td>73~76</td></tr>" << std::endl
		<< "<tr><td>C</td><td>2.3</td><td>70~72</td></tr>" << std::endl
		<< "<tr><td>C-</td><td>2.0</td><td>67~69</td></tr>" << std::endl
		<< "<tr><td>D+</td><td>1.6</td><td>63~66</td></tr>" << std::endl
		<< "<tr><td>D</td><td>1.3</td><td>60~62</td></tr>" << std::endl
		<< "<tr><td>F</td><td>0</td><td>0~59</td></tr>" << std::endl
		<< "</table>" << std::endl
		<< std::endl
		<< "平均学分绩（GPA）的计算方法为：$GPA=\\frac{\\Sigma 课程学分 * 绩点}{\\Sigma 课程学分}$" << std::endl
		<< std::endl;
	out.close();
	std::cout << "打印成功！" << std::endl;
}

// 按学号打印学生信息
void Database::printStudent(int studentNo)
{
	Student *stu = findStudent(studentNo);
	if (stu == nullptr)
	{
		std::cout << "未找到该学生！" << std::endl;
		return;
	}
	std::string filename = "output_student_" + std::to_string(studentNo) + "_" + stu->getName() + ".md";
	std::ofstream out(filename, std::ios::out | std::ios::trunc);
	if (!out.is_open())
	{
		std::cerr << "Error: cannot open file \"" << filename << "\"." << std::endl;
		return;
	}
	out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
		<< std::endl
		<< "学号：" << studentNo << std::endl
		<< std::endl
		<< "姓名：" << stu->getName() << std::endl
		<< std::endl
		<< "总学分：" << stu->getTotalCredit() << std::endl
		<< std::endl
		<< "平均成绩：" << stu->getAverageScore() << std::endl
		<< std::endl
		<< "平均绩点：" << stu->getAverageGPA() << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>课程名称</th><th>课程类型</th><th>学分</th><th>成绩</th><th>绩点</th></tr>" << std::endl;
	if (stu->getLectureNum() > 0)
	{
		for (int i = 0; i < stu->getLectureNum(); i++)
		{
			if (!stu->getLecturePF()[i])
			{
				out << "<tr><td>" << stu->getLectureName()[i]
					<< "</td><td>" << ((stu->getLectureType()[i] == REQUIRED) ? "必选课" : ((stu->getLectureType()[i] == LIMITED) ? "限选课" : "任选课"))
					<< "</td><td>" << stu->getLectureCredit()[i]
					<< "</td><td>" << stu->getLectureScore()[i]
					<< "</td><td>" << stu->getLectureGPA()[i] << "</td></tr>" << std::endl;
			}
			else
			{
				out << "<tr><td>" << stu->getLectureName()[i]
					<< "</td><td>" << ((stu->getLectureType()[i] == REQUIRED) ? "必选课" : ((stu->getLectureType()[i] == LIMITED) ? "限选课" : "任选课"))
					<< "</td><td>" << stu->getLectureCredit()[i]
					<< "</td><td>"
					<< "N/A"
					<< "</td><td>" << (stu->getLectureGPA()[i] ? "P" : "F") << "</td></tr>" << std::endl;
			}
		}
	}
	else
	{
		out << "<tr><td colspan=\"5\">无</td></tr>" << std::endl;
	}
	out << "</table>" << std::endl
		<< std::endl
		<< "打印时间：" << timeStampToString(time(0)) << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩单说明</center></h1>" << std::endl
		<< std::endl
		<< "1. 本成绩单仅包含该学生的各课程成绩信息" << std::endl
		<< "2. 本成绩单仅供参考，不作为最终成绩" << std::endl
		<< "3. 本成绩单由学生成绩管理系统自动生成" << std::endl
		<< "4. 本成绩单最终解释权归××大学所有" << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩记载说明</center></h1>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>等级制成绩</th><th>绩点</th><th>对应百分制成绩范围</th></tr>" << std::endl
		<< "<tr><td>A+</td><td rowspan=\"3\">4.0</td><td rowspan=\"2\">95~100</td></tr>" << std::endl
		<< "<tr><td>A</td></tr>" << std::endl
		<< "<tr><td>A-</td><td>90~94</td></tr>" << std::endl
		<< "<tr><td>B+</td><td>3.6</td><td>85~89</td></tr>" << std::endl
		<< "<tr><td>B</td><td>3.3</td><td>80~84</td></tr>" << std::endl
		<< "<tr><td>B-</td><td>3.0</td><td>77~79</td></tr>" << std::endl
		<< "<tr><td>C+</td><td>2.6</td><td>73~76</td></tr>" << std::endl
		<< "<tr><td>C</td><td>2.3</td><td>70~72</td></tr>" << std::endl
		<< "<tr><td>C-</td><td>2.0</td><td>67~69</td></tr>" << std::endl
		<< "<tr><td>D+</td><td>1.6</td><td>63~66</td></tr>" << std::endl
		<< "<tr><td>D</td><td>1.3</td><td>60~62</td></tr>" << std::endl
		<< "<tr><td>F</td><td>0</td><td>0~59</td></tr>" << std::endl
		<< "</table>" << std::endl
		<< std::endl
		<< "平均学分绩（GPA）的计算方法为：$GPA=\\frac{\\Sigma 课程学分 * 绩点}{\\Sigma 课程学分}$" << std::endl
		<< std::endl;
	out.close();
	std::cout << "打印成功！" << std::endl;
}

// 按姓名打印学生信息
void Database::printStudent(const std::string &name)
{
	Student *stu = findStudent(name);
	if (stu == nullptr)
	{
		std::cout << "未找到该学生！" << std::endl;
		return;
	}
	std::string filename = "output_student_" + std::to_string(stu->getStudentNo()) + "_" + name + ".md";
	std::ofstream out(filename, std::ios::out | std::ios::trunc);
	if (!out.is_open())
	{
		std::cerr << "Error: cannot open file \"" << filename << "\"." << std::endl;
		return;
	}
	out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
		<< std::endl
		<< "学号：" << stu->getStudentNo() << std::endl
		<< std::endl
		<< "姓名：" << name << std::endl
		<< std::endl
		<< "总学分：" << stu->getTotalCredit() << std::endl
		<< std::endl
		<< "平均成绩：" << stu->getAverageScore() << std::endl
		<< std::endl
		<< "平均绩点：" << stu->getAverageGPA() << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>课程名称</th><th>课程类型</th><th>学分</th><th>成绩</th><th>绩点</th></tr>" << std::endl;
	if (stu->getLectureNum() > 0)
	{
		for (int i = 0; i < stu->getLectureNum(); i++)
		{
			if (!stu->getLecturePF()[i])
			{
				out << "<tr><td>" << stu->getLectureName()[i]
					<< "</td><td>" << ((stu->getLectureType()[i] == REQUIRED) ? "必选课" : ((stu->getLectureType()[i] == LIMITED) ? "限选课" : "任选课"))
					<< "</td><td>" << stu->getLectureCredit()[i]
					<< "</td><td>" << stu->getLectureScore()[i]
					<< "</td><td>" << stu->getLectureGPA()[i] << "</td></tr>" << std::endl;
			}
			else
			{
				out << "<tr><td>" << stu->getLectureName()[i]
					<< "</td><td>" << ((stu->getLectureType()[i] == REQUIRED) ? "必选课" : ((stu->getLectureType()[i] == LIMITED) ? "限选课" : "任选课"))
					<< "</td><td>" << stu->getLectureCredit()[i]
					<< "</td><td>"
					<< "N/A"
					<< "</td><td>" << (stu->getLectureGPA()[i] ? "P" : "F") << "</td></tr>" << std::endl;
			}
		}
	}
	else
	{
		out << "<tr><td colspan=\"5\">无</td></tr>" << std::endl;
	}
	out << "</table>" << std::endl
		<< std::endl
		<< "打印时间：" << timeStampToString(time(0)) << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩单说明</center></h1>" << std::endl
		<< std::endl
		<< "1. 本成绩单仅包含该学生的各课程成绩信息" << std::endl
		<< "2. 本成绩单仅供参考，不作为最终成绩" << std::endl
		<< "3. 本成绩单由学生成绩管理系统自动生成" << std::endl
		<< "4. 本成绩单最终解释权归××大学所有" << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩记载说明</center></h1>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>等级制成绩</th><th>绩点</th><th>对应百分制成绩范围</th></tr>" << std::endl
		<< "<tr><td>A+</td><td rowspan=\"3\">4.0</td><td rowspan=\"2\">95~100</td></tr>" << std::endl
		<< "<tr><td>A</td></tr>" << std::endl
		<< "<tr><td>A-</td><td>90~94</td></tr>" << std::endl
		<< "<tr><td>B+</td><td>3.6</td><td>85~89</td></tr>" << std::endl
		<< "<tr><td>B</td><td>3.3</td><td>80~84</td></tr>" << std::endl
		<< "<tr><td>B-</td><td>3.0</td><td>77~79</td></tr>" << std::endl
		<< "<tr><td>C+</td><td>2.6</td><td>73~76</td></tr>" << std::endl
		<< "<tr><td>C</td><td>2.3</td><td>70~72</td></tr>" << std::endl
		<< "<tr><td>C-</td><td>2.0</td><td>67~69</td></tr>" << std::endl
		<< "<tr><td>D+</td><td>1.6</td><td>63~66</td></tr>" << std::endl
		<< "<tr><td>D</td><td>1.3</td><td>60~62</td></tr>" << std::endl
		<< "<tr><td>F</td><td>0</td><td>0~59</td></tr>" << std::endl
		<< "</table>" << std::endl
		<< std::endl
		<< "平均学分绩（GPA）的计算方法为：$GPA=\\frac{\\Sigma 课程学分 * 绩点}{\\Sigma 课程学分}$" << std::endl
		<< std::endl;
	out.close();
	std::cout << "打印成功！" << std::endl;
}

// 打印全部课程信息
void Database::printLecture()
{
	std::ofstream out("output_lecture_all.md", std::ios::out | std::ios::trunc);
	if (!out.is_open())
	{
		std::cerr << "Error: cannot open file \""
				  << "output_lecture_all.md"
				  << "\"." << std::endl;
		return;
	}

	out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
		<< std::endl
		<< "<h2><center>全部课程信息</center></h2>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>名称</th><th>类型</th><th>学分</th><th>学生数</th><th>平均成绩</th><th>平均绩点</th></tr>" << std::endl;
	Lecture **head;
	int reqLength = requiredList.size(), limLength = limitedList.size(), optLength = optionalList.size();
	if (reqLength + limLength + optLength > 0)
	{
		head = new Lecture *[reqLength + limLength + optLength];
		int cnt = 0;
		if (reqLength > 0)
		{
			Node<LectureRequired> *tmp = requiredList.getFirst();
			do
			{
				head[cnt] = &tmp->data;
				tmp = requiredList.getNext();
				cnt++;
			} while (tmp != nullptr);
		}
		if (limLength > 0)
		{
			Node<LectureLimited> *tmp = limitedList.getFirst();
			do
			{
				head[cnt] = &tmp->data;
				tmp = limitedList.getNext();
				cnt++;
			} while (tmp != nullptr);
		}
		if (optLength > 0)
		{
			Node<LectureOptional> *tmp = optionalList.getFirst();
			do
			{
				head[cnt] = &tmp->data;
				tmp = optionalList.getNext();
				cnt++;
			} while (tmp != nullptr);
		}
		sortLectureCustom(head, reqLength + limLength + optLength, -1, 0);
		for (cnt = 0; cnt < reqLength + limLength + optLength; cnt++)
		{
			out << "<tr><td>" << head[cnt]->getName()
				<< "</td><td>" << ((head[cnt]->getLectureType() == REQUIRED) ? "必选课" : (head[cnt]->getLectureType() == LIMITED ? "限选课" : "任选课"))
				<< "</td><td>" << head[cnt]->getCredit()
				<< "</td><td>" << head[cnt]->getStudentNum()
				<< "</td><td>" << head[cnt]->getAverageScore()
				<< "</td><td>" << head[cnt]->getAverageGPA() << "</td></tr>" << std::endl;
		}
		delete[] head;
	}
	else
	{
		out << "<tr><td colspan=\"6\">无课程信息</td></tr>" << std::endl;
	}
	out << "</table>" << std::endl
		<< std::endl
		<< "打印时间：" << timeStampToString(time(0)) << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩单说明</center></h1>" << std::endl
		<< std::endl
		<< "1. 本成绩单按照课程名称升序排列" << std::endl
		<< "2. 本成绩单仅包含全部课程的总成绩信息" << std::endl
		<< "3. 本成绩单仅供参考，不作为最终成绩" << std::endl
		<< "4. 本成绩单由学生成绩管理系统自动生成" << std::endl
		<< "5. 本成绩单最终解释权归××大学所有" << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩记载说明</center></h1>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>等级制成绩</th><th>绩点</th><th>对应百分制成绩范围</th></tr>" << std::endl
		<< "<tr><td>A+</td><td rowspan=\"3\">4.0</td><td rowspan=\"2\">95~100</td></tr>" << std::endl
		<< "<tr><td>A</td></tr>" << std::endl
		<< "<tr><td>A-</td><td>90~94</td></tr>" << std::endl
		<< "<tr><td>B+</td><td>3.6</td><td>85~89</td></tr>" << std::endl
		<< "<tr><td>B</td><td>3.3</td><td>80~84</td></tr>" << std::endl
		<< "<tr><td>B-</td><td>3.0</td><td>77~79</td></tr>" << std::endl
		<< "<tr><td>C+</td><td>2.6</td><td>73~76</td></tr>" << std::endl
		<< "<tr><td>C</td><td>2.3</td><td>70~72</td></tr>" << std::endl
		<< "<tr><td>C-</td><td>2.0</td><td>67~69</td></tr>" << std::endl
		<< "<tr><td>D+</td><td>1.6</td><td>63~66</td></tr>" << std::endl
		<< "<tr><td>D</td><td>1.3</td><td>60~62</td></tr>" << std::endl
		<< "<tr><td>F</td><td>0</td><td>0~59</td></tr>" << std::endl
		<< "</table>" << std::endl
		<< std::endl
		<< "平均学分绩（GPA）的计算方法为：$GPA=\\frac{\\Sigma 课程学分 * 绩点}{\\Sigma 课程学分}$" << std::endl
		<< std::endl;
	out.close();
	std::cout << "打印成功！" << std::endl;
}

// 按类型打印课程信息
void Database::printLecture(LectureType type)
{
	std::string filename = "output_lecture_" + std::string((type == REQUIRED) ? "required" : (type == LIMITED ? "limited" : "optional")) + ".md";
	std::ofstream out(filename, std::ios::out | std::ios::trunc);
	if (!out.is_open())
	{
		std::cerr << "Error: cannot open file \"" << filename << "\"." << std::endl;
		return;
	}
	Lecture **head = nullptr;
	int length = 0;
	int cnt = 0;
	switch (type)
	{
	case REQUIRED:
		out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
			<< std::endl
			<< "<h2><center>必选课程信息</center></h2>" << std::endl
			<< std::endl
			<< "<table border=\"1\" align=\"center\">" << std::endl
			<< "<tr><th>名称</th><th>类型</th><th>学分</th><th>学生数</th><th>平均成绩</th><th>平均绩点</th></tr>" << std::endl;
		length = requiredList.size();
		head = new Lecture *[length];
		if (length > 0)
		{
			Node<LectureRequired> *tmp = requiredList.getFirst();
			do
			{
				head[cnt] = &tmp->data;
				tmp = requiredList.getNext();
				cnt++;
			} while (tmp != nullptr);
		}
		break;
	case LIMITED:
		out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
			<< std::endl
			<< "<h2><center>限选课程信息</center></h2>" << std::endl
			<< std::endl
			<< "<table border=\"1\" align=\"center\">" << std::endl
			<< "<tr><th>名称</th><th>类型</th><th>学分</th><th>学生数</th><th>平均成绩</th><th>平均绩点</th></tr>" << std::endl;
		length = limitedList.size();
		head = new Lecture *[length];
		if (length > 0)
		{
			Node<LectureLimited> *tmp = limitedList.getFirst();
			do
			{
				head[cnt] = &tmp->data;
				tmp = limitedList.getNext();
				cnt++;
			} while (tmp != nullptr);
		}
		break;
	case OPTIONAL:
		out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
			<< std::endl
			<< "<h2><center>任选课程信息</center></h2>" << std::endl
			<< std::endl
			<< "<table border=\"1\" align=\"center\">" << std::endl
			<< "<tr><th>名称</th><th>类型</th><th>学分</th><th>学生数</th><th>平均成绩</th><th>平均绩点</th></tr>" << std::endl;
		length = optionalList.size();
		head = new Lecture *[length];
		if (length > 0)
		{
			Node<LectureOptional> *tmp = optionalList.getFirst();
			do
			{
				head[cnt] = &tmp->data;
				tmp = optionalList.getNext();
				cnt++;
			} while (tmp != nullptr);
		}
		break;
	default:
		return;
		break;
	}
	if (length > 0)
	{
		sortLectureCustom(head, length, -1, 0);
		for (cnt = 0; cnt < length; cnt++)
		{
			out << "<tr><td>" << head[cnt]->getName()
				<< "</td><td>" << ((head[cnt]->getLectureType() == REQUIRED) ? "必选课" : (head[cnt]->getLectureType() == LIMITED ? "限选课" : "任选课"))
				<< "</td><td>" << head[cnt]->getCredit()
				<< "</td><td>" << head[cnt]->getStudentNum()
				<< "</td><td>" << head[cnt]->getAverageScore()
				<< "</td><td>" << head[cnt]->getAverageGPA() << "</td></tr>" << std::endl;
		}
		delete[] head;
	}
	else
	{
		out << "<tr><td colspan=\"6\">无课程信息</td></tr>" << std::endl;
	}
	out << "</table>" << std::endl
		<< std::endl
		<< "打印时间：" << timeStampToString(time(0)) << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩单说明</center></h1>" << std::endl
		<< std::endl
		<< "1. 本成绩单按照课程名称升序排列" << std::endl
		<< "2. 本成绩单仅包含全部课程的总成绩信息" << std::endl
		<< "3. 本成绩单仅供参考，不作为最终成绩" << std::endl
		<< "4. 本成绩单由学生成绩管理系统自动生成" << std::endl
		<< "5. 本成绩单最终解释权归××大学所有" << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩记载说明</center></h1>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>等级制成绩</th><th>绩点</th><th>对应百分制成绩范围</th></tr>" << std::endl
		<< "<tr><td>A+</td><td rowspan=\"3\">4.0</td><td rowspan=\"2\">95~100</td></tr>" << std::endl
		<< "<tr><td>A</td></tr>" << std::endl
		<< "<tr><td>A-</td><td>90~94</td></tr>" << std::endl
		<< "<tr><td>B+</td><td>3.6</td><td>85~89</td></tr>" << std::endl
		<< "<tr><td>B</td><td>3.3</td><td>80~84</td></tr>" << std::endl
		<< "<tr><td>B-</td><td>3.0</td><td>77~79</td></tr>" << std::endl
		<< "<tr><td>C+</td><td>2.6</td><td>73~76</td></tr>" << std::endl
		<< "<tr><td>C</td><td>2.3</td><td>70~72</td></tr>" << std::endl
		<< "<tr><td>C-</td><td>2.0</td><td>67~69</td></tr>" << std::endl
		<< "<tr><td>D+</td><td>1.6</td><td>63~66</td></tr>" << std::endl
		<< "<tr><td>D</td><td>1.3</td><td>60~62</td></tr>" << std::endl
		<< "<tr><td>F</td><td>0</td><td>0~59</td></tr>" << std::endl
		<< "</table>" << std::endl
		<< std::endl
		<< "平均学分绩（GPA）的计算方法为：$GPA=\\frac{\\Sigma 课程学分 * 绩点}{\\Sigma 课程学分}$" << std::endl
		<< std::endl;
	out.close();
	std::cout << "打印成功！" << std::endl;
}

// 按课程名打印课程信息
void Database::printLecture(const std::string &name)
{
	Lecture *lec = findLecture(name);
	if (lec == nullptr)
	{
		std::cout << "未找到该课程！" << std::endl;
		return;
	}
	std::string filename = "output_lecture_" + name + ".md";
	std::ofstream out(filename, std::ios::out | std::ios::trunc);
	if (!out.is_open())
	{
		std::cerr << "Error: cannot open file \"" << filename << "\"." << std::endl;
		return;
	}
	out << "<h1><center>××大学学生成绩单</center></h1>" << std::endl
		<< std::endl
		<< "名称：" << name << std::endl
		<< std::endl
		<< "学分：" << lec->getCredit() << std::endl
		<< std::endl
		<< "平均成绩：" << lec->getAverageScore() << std::endl
		<< std::endl
		<< "平均绩点：" << lec->getAverageGPA() << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>学号</th><th>姓名</th><th>成绩</th><th>绩点</th></tr>" << std::endl;
	if (lec->getStudentNum() > 0)
	{
		for (int i = 0; i < lec->getStudentNum(); i++)
		{
			if (!queryOptional(name, false))
			{
				out << "<tr><td>" << lec->getStudentNo()[i]
					<< "</td><td>" << lec->getStudentName()[i]
					<< "</td><td>" << lec->getStudentScore()[i]
					<< "</td><td>" << lec->getStudentGPA()[i] << "</td></tr>" << std::endl;
			}
			else if (!findOptional(name)->getStudentPF()[i])
			{
				out << "<tr><td>" << lec->getStudentNo()[i]
					<< "</td><td>" << lec->getStudentName()[i]
					<< "</td><td>" << lec->getStudentScore()[i]
					<< "</td><td>" << lec->getStudentGPA()[i] << "</td></tr>" << std::endl;
			}
			else
			{
				out << "<tr><td>" << lec->getStudentNo()[i]
					<< "</td><td>" << lec->getStudentName()[i]
					<< "</td><td>"
					<< "N/A"
					<< "</td><td>" << (lec->getStudentGPA()[i] ? "P" : "F") << "</td></tr>" << std::endl;
			}
		}
	}
	else
	{
		out << "<tr><td colspan=\"4\">无学生选修该课程</td></tr>" << std::endl;
	}
	out << "</table>" << std::endl
		<< std::endl
		<< "打印时间：" << timeStampToString(time(0)) << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩单说明</center></h1>" << std::endl
		<< std::endl
		<< "1. 本成绩单仅包含该课程的各学生成绩信息" << std::endl
		<< "2. 本成绩单仅供参考，不作为最终成绩" << std::endl
		<< "3. 本成绩单由学生成绩管理系统自动生成" << std::endl
		<< "4. 本成绩单最终解释权归××大学所有" << std::endl
		<< std::endl
		<< "***" << std::endl
		<< std::endl
		<< "<h1><center>成绩记载说明</center></h1>" << std::endl
		<< std::endl
		<< "<table border=\"1\" align=\"center\">" << std::endl
		<< "<tr><th>等级制成绩</th><th>绩点</th><th>对应百分制成绩范围</th></tr>" << std::endl
		<< "<tr><td>A+</td><td rowspan=\"3\">4.0</td><td rowspan=\"2\">95~100</td></tr>" << std::endl
		<< "<tr><td>A</td></tr>" << std::endl
		<< "<tr><td>A-</td><td>90~94</td></tr>" << std::endl
		<< "<tr><td>B+</td><td>3.6</td><td>85~89</td></tr>" << std::endl
		<< "<tr><td>B</td><td>3.3</td><td>80~84</td></tr>" << std::endl
		<< "<tr><td>B-</td><td>3.0</td><td>77~79</td></tr>" << std::endl
		<< "<tr><td>C+</td><td>2.6</td><td>73~76</td></tr>" << std::endl
		<< "<tr><td>C</td><td>2.3</td><td>70~72</td></tr>" << std::endl
		<< "<tr><td>C-</td><td>2.0</td><td>67~69</td></tr>" << std::endl
		<< "<tr><td>D+</td><td>1.6</td><td>63~66</td></tr>" << std::endl
		<< "<tr><td>D</td><td>1.3</td><td>60~62</td></tr>" << std::endl
		<< "<tr><td>F</td><td>0</td><td>0~59</td></tr>" << std::endl
		<< "</table>" << std::endl
		<< std::endl
		<< "平均学分绩（GPA）的计算方法为：$GPA=\\frac{\\Sigma 课程学分 * 绩点}{\\Sigma 课程学分}$" << std::endl
		<< std::endl;
	out.close();
	std::cout << "打印成功！" << std::endl;
}

// 百分制成绩转化为绩点
double Database::calculateGPA(int score)
{
	double ret = 0;
	if (score >= 90)
		ret = 4.0;
	else if (score >= 85)
		ret = 3.6;
	else if (score >= 80)
		ret = 3.3;
	else if (score >= 77)
		ret = 3.0;
	else if (score >= 73)
		ret = 2.6;
	else if (score >= 70)
		ret = 2.3;
	else if (score >= 67)
		ret = 2.0;
	else if (score >= 63)
		ret = 1.6;
	else if (score >= 60)
		ret = 1.3;
	else
		ret = 0;
	return ret;
}

// 从课程更新学生信息
void Database::updateStudent()
{
	studentList.makeEmpty();
	Node<LectureRequired> *req = requiredList.getFirst();
	Node<LectureLimited> *lim = limitedList.getFirst();
	Node<LectureOptional> *opt = optionalList.getFirst();
	if (req != nullptr)
	{
		do
		{
			for (int i = 0; i < req->data.getStudentNum(); i++)
			{
				if (!queryStudent(req->data.getStudentNo()[i], false))
				{
					Node<Student> *stu = new Node<Student>;
					stu->data.setStudentNo(req->data.getStudentNo()[i]);
					stu->data.setName(req->data.getStudentName()[i]);
					stu->data.setLectureNum(stu->data.getLectureNum() + 1);
					stu->data.getLectureName().push_back(req->data.getName());
					stu->data.getLectureType().push_back(REQUIRED);
					stu->data.getLectureCredit().push_back(req->data.getCredit());
					stu->data.getLectureScore().push_back(req->data.getStudentScore()[i]);
					stu->data.getLectureGPA().push_back(req->data.getStudentGPA()[i]);
					stu->data.getLecturePF().push_back(false);
					stu->data.setTotalScore(stu->data.getTotalScore() + req->data.getStudentScore()[i] * req->data.getCredit());
					stu->data.setTotalCredit(stu->data.getTotalCredit() + req->data.getCredit());
					stu->data.setTotalGPA(stu->data.getTotalGPA() + calculateGPA(req->data.getStudentScore()[i]) * req->data.getCredit());
					if (stu->data.getTotalCredit() - stu->data.getTotalPFCredit())
						stu->data.setAverageScore(stu->data.getTotalScore() / (stu->data.getTotalCredit() - stu->data.getTotalPFCredit()));
					if (stu->data.getTotalCredit() - stu->data.getTotalPFCredit())
						stu->data.setAverageGPA(stu->data.getTotalGPA() / (stu->data.getTotalCredit() - stu->data.getTotalPFCredit()));
					studentList.insert_end(stu);
				}
				else
				{
					Student *stu = findStudent(req->data.getStudentNo()[i]);
					stu->setLectureNum(stu->getLectureNum() + 1);
					stu->getLectureName().push_back(req->data.getName());
					stu->getLectureType().push_back(REQUIRED);
					stu->getLectureCredit().push_back(req->data.getCredit());
					stu->getLectureScore().push_back(req->data.getStudentScore()[i]);
					stu->getLectureGPA().push_back(req->data.getStudentGPA()[i]);
					stu->getLecturePF().push_back(false);
					stu->setTotalScore(stu->getTotalScore() + req->data.getStudentScore()[i] * req->data.getCredit());
					stu->setTotalCredit(stu->getTotalCredit() + req->data.getCredit());
					stu->setTotalGPA(stu->getTotalGPA() + calculateGPA(req->data.getStudentScore()[i]) * req->data.getCredit());
					if (stu->getTotalCredit() - stu->getTotalPFCredit())
						stu->setAverageScore(stu->getTotalScore() / (stu->getTotalCredit() - stu->getTotalPFCredit()));
					if (stu->getTotalCredit() - stu->getTotalPFCredit())
						stu->setAverageGPA(stu->getTotalGPA() / (stu->getTotalCredit() - stu->getTotalPFCredit()));
				}
			}
			req = requiredList.getNext();
		} while (req != nullptr);
	}
	if (lim != nullptr)
	{
		do
		{
			for (int i = 0; i < lim->data.getStudentNum(); i++)
			{
				if (!queryStudent(lim->data.getStudentNo()[i], false))
				{
					Node<Student> *stu = new Node<Student>;
					stu->data.setStudentNo(lim->data.getStudentNo()[i]);
					stu->data.setName(lim->data.getStudentName()[i]);
					stu->data.setLectureNum(stu->data.getLectureNum() + 1);
					stu->data.getLectureName().push_back(lim->data.getName());
					stu->data.getLectureType().push_back(LIMITED);
					stu->data.getLectureCredit().push_back(lim->data.getCredit());
					stu->data.getLectureScore().push_back(lim->data.getStudentScore()[i]);
					stu->data.getLectureGPA().push_back(lim->data.getStudentGPA()[i]);
					stu->data.getLecturePF().push_back(false);
					stu->data.setTotalScore(stu->data.getTotalScore() + lim->data.getStudentScore()[i] * lim->data.getCredit());
					stu->data.setTotalCredit(stu->data.getTotalCredit() + lim->data.getCredit());
					stu->data.setTotalGPA(stu->data.getTotalGPA() + calculateGPA(lim->data.getStudentScore()[i]) * lim->data.getCredit());
					if (stu->data.getTotalCredit() - stu->data.getTotalPFCredit())
						stu->data.setAverageScore(stu->data.getTotalScore() / (stu->data.getTotalCredit() - stu->data.getTotalPFCredit()));
					if (stu->data.getTotalCredit() - stu->data.getTotalPFCredit())
						stu->data.setAverageGPA(stu->data.getTotalGPA() / (stu->data.getTotalCredit() - stu->data.getTotalPFCredit()));
					studentList.insert_end(stu);
				}
				else
				{
					Student *stu = findStudent(lim->data.getStudentNo()[i]);
					stu->setLectureNum(stu->getLectureNum() + 1);
					stu->getLectureName().push_back(lim->data.getName());
					stu->getLectureType().push_back(LIMITED);
					stu->getLectureCredit().push_back(lim->data.getCredit());
					stu->getLectureScore().push_back(lim->data.getStudentScore()[i]);
					stu->getLectureGPA().push_back(lim->data.getStudentGPA()[i]);
					stu->getLecturePF().push_back(false);
					stu->setTotalScore(stu->getTotalScore() + lim->data.getStudentScore()[i] * lim->data.getCredit());
					stu->setTotalCredit(stu->getTotalCredit() + lim->data.getCredit());
					stu->setTotalGPA(stu->getTotalGPA() + calculateGPA(lim->data.getStudentScore()[i]) * lim->data.getCredit());
					if (stu->getTotalCredit() - stu->getTotalPFCredit())
						stu->setAverageScore(stu->getTotalScore() / (stu->getTotalCredit() - stu->getTotalPFCredit()));
					if (stu->getTotalCredit() - stu->getTotalPFCredit())
						stu->setAverageGPA(stu->getTotalGPA() / (stu->getTotalCredit() - stu->getTotalPFCredit()));
				}
			}
			lim = limitedList.getNext();
		} while (lim != nullptr);
	}
	if (opt != nullptr)
	{
		do
		{
			for (int i = 0; i < opt->data.getStudentNum(); i++)
			{
				if (!queryStudent(opt->data.getStudentNo()[i], false))
				{
					Node<Student> *stu = new Node<Student>;
					stu->data.setStudentNo(opt->data.getStudentNo()[i]);
					stu->data.setName(opt->data.getStudentName()[i]);
					stu->data.setLectureNum(stu->data.getLectureNum() + 1);
					stu->data.getLectureName().push_back(opt->data.getName());
					stu->data.getLectureType().push_back(OPTIONAL);
					stu->data.getLectureCredit().push_back(opt->data.getCredit());
					stu->data.getLectureScore().push_back(opt->data.getStudentScore()[i]);
					stu->data.getLectureGPA().push_back(opt->data.getStudentGPA()[i]);
					stu->data.getLecturePF().push_back(opt->data.getStudentPF()[i]);
					stu->data.setLecturePFNum(stu->data.getLecturePFNum() + (opt->data.getStudentPF()[i] ? 1 : 0));
					stu->data.setTotalScore(stu->data.getTotalScore() + opt->data.getStudentScore()[i] * (!opt->data.getStudentPF()[i] ? opt->data.getCredit() : 0));
					stu->data.setTotalCredit(stu->data.getTotalCredit() + opt->data.getCredit());
					stu->data.setTotalPFCredit(stu->data.getTotalPFCredit() + (opt->data.getStudentPF()[i] ? opt->data.getCredit() : 0));
					stu->data.setTotalGPA(stu->data.getTotalGPA() + calculateGPA(opt->data.getStudentScore()[i]) * opt->data.getCredit());
					if (stu->data.getTotalCredit() - stu->data.getTotalPFCredit())
						stu->data.setAverageScore(stu->data.getTotalScore() / (stu->data.getTotalCredit() - stu->data.getTotalPFCredit()));
					if (stu->data.getTotalCredit() - stu->data.getTotalPFCredit())
						stu->data.setAverageGPA(stu->data.getTotalGPA() / (stu->data.getTotalCredit() - stu->data.getTotalPFCredit()));
					studentList.insert_end(stu);
				}
				else
				{
					Student *stu = findStudent(opt->data.getStudentNo()[i]);
					stu->setLectureNum(stu->getLectureNum() + 1);
					stu->getLectureName().push_back(opt->data.getName());
					stu->getLectureType().push_back(OPTIONAL);
					stu->getLectureCredit().push_back(opt->data.getCredit());
					stu->getLectureScore().push_back(opt->data.getStudentScore()[i]);
					stu->getLectureGPA().push_back(opt->data.getStudentGPA()[i]);
					stu->getLecturePF().push_back(opt->data.getStudentPF()[i]);
					stu->setLecturePFNum(stu->getLecturePFNum() + (opt->data.getStudentPF()[i] ? 1 : 0));
					stu->setTotalScore(stu->getTotalScore() + opt->data.getStudentScore()[i] * (!opt->data.getStudentPF()[i] ? opt->data.getCredit() : 0));
					stu->setTotalCredit(stu->getTotalCredit() + opt->data.getCredit());
					stu->setTotalPFCredit(stu->getTotalPFCredit() + (opt->data.getStudentPF()[i] ? opt->data.getCredit() : 0));
					stu->setTotalGPA(stu->getTotalGPA() + calculateGPA(opt->data.getStudentScore()[i]) * opt->data.getCredit());
					if (stu->getTotalCredit() - stu->getTotalPFCredit())
						stu->setAverageScore(stu->getTotalScore() / (stu->getTotalCredit() - stu->getTotalPFCredit()));
					if (stu->getTotalCredit() - stu->getTotalPFCredit())
						stu->setAverageGPA(stu->getTotalGPA() / (stu->getTotalCredit() - stu->getTotalPFCredit()));
				}
			}
			opt = optionalList.getNext();
		} while (opt != nullptr);
	}
}

// 从学生更新课程信息
void Database::updateLecture()
{
	requiredList.makeEmpty();
	limitedList.makeEmpty();
	optionalList.makeEmpty();
	Node<Student> *stu = studentList.getFirst();
	if (stu != nullptr)
	{
		do
		{
			for (int i = 0; i < stu->data.getLectureNum(); i++)
			{
				if (stu->data.getLectureType()[i] == REQUIRED)
				{
					if (!queryRequired(stu->data.getLectureName()[i], false))
					{
						Node<LectureRequired> *req = new Node<LectureRequired>;
						req->data.setName(stu->data.getLectureName()[i]);
						req->data.setCredit(stu->data.getLectureCredit()[i]);
						req->data.setStudentNum(req->data.getStudentNum() + 1);
						std::vector<int> studentNo = req->data.getStudentNo();
						std::vector<std::string> studentName = req->data.getStudentName();
						std::vector<int> studentScore = req->data.getStudentScore();
						std::vector<double> studentGPA = req->data.getStudentGPA();
						studentNo.push_back(stu->data.getStudentNo());
						studentName.push_back(stu->data.getName());
						studentScore.push_back(stu->data.getLectureScore()[i]);
						studentGPA.push_back(stu->data.getLectureGPA()[i]);
						req->data.setStudentNo(studentNo);
						req->data.setStudentName(studentName);
						req->data.setStudentScore(studentScore);
						req->data.setStudentGPA(studentGPA);
						req->data.setTotalScore(req->data.getTotalScore() + stu->data.getLectureScore()[i]);
						req->data.setTotalGPA(req->data.getTotalGPA() + stu->data.getLectureGPA()[i]);
						req->data.setAverageScore(req->data.getTotalScore() / req->data.getStudentNum());
						req->data.setAverageGPA(req->data.getTotalGPA() / req->data.getStudentNum());
						requiredList.insert_end(req);
					}
					else
					{
						LectureRequired *req = findRequired(stu->data.getLectureName()[i]);
						req->setStudentNum(req->getStudentNum() + 1);
						std::vector<int> studentNo = req->getStudentNo();
						std::vector<std::string> studentName = req->getStudentName();
						std::vector<int> studentScore = req->getStudentScore();
						std::vector<double> studentGPA = req->getStudentGPA();
						studentNo.push_back(stu->data.getStudentNo());
						studentName.push_back(stu->data.getName());
						studentScore.push_back(stu->data.getLectureScore()[i]);
						studentGPA.push_back(stu->data.getLectureGPA()[i]);
						req->setStudentNo(studentNo);
						req->setStudentName(studentName);
						req->setStudentScore(studentScore);
						req->setStudentGPA(studentGPA);
						req->setTotalScore(req->getTotalScore() + stu->data.getLectureScore()[i]);
						req->setTotalGPA(req->getTotalGPA() + stu->data.getLectureGPA()[i]);
						req->setAverageScore(req->getTotalScore() / req->getStudentNum());
						req->setAverageGPA(req->getTotalGPA() / req->getStudentNum());
					}
				}
				else if (stu->data.getLectureType()[i] == LIMITED)
				{
					if (!queryLimited(stu->data.getLectureName()[i], false))
					{
						Node<LectureLimited> *lim = new Node<LectureLimited>;
						lim->data.setName(stu->data.getLectureName()[i]);
						lim->data.setCredit(stu->data.getLectureCredit()[i]);
						lim->data.setStudentNum(lim->data.getStudentNum() + 1);
						std::vector<int> studentNo = lim->data.getStudentNo();
						std::vector<std::string> studentName = lim->data.getStudentName();
						std::vector<int> studentScore = lim->data.getStudentScore();
						std::vector<double> studentGPA = lim->data.getStudentGPA();
						studentNo.push_back(stu->data.getStudentNo());
						studentName.push_back(stu->data.getName());
						studentScore.push_back(stu->data.getLectureScore()[i]);
						studentGPA.push_back(stu->data.getLectureGPA()[i]);
						lim->data.setStudentNo(studentNo);
						lim->data.setStudentName(studentName);
						lim->data.setStudentScore(studentScore);
						lim->data.setStudentGPA(studentGPA);
						lim->data.setTotalScore(lim->data.getTotalScore() + stu->data.getLectureScore()[i]);
						lim->data.setTotalGPA(lim->data.getTotalGPA() + stu->data.getLectureGPA()[i]);
						lim->data.setAverageScore(lim->data.getTotalScore() / lim->data.getStudentNum());
						lim->data.setAverageGPA(lim->data.getTotalGPA() / lim->data.getStudentNum());
						limitedList.insert_end(lim);
					}
					else
					{
						LectureLimited *lim = findLimited(stu->data.getLectureName()[i]);
						lim->setStudentNum(lim->getStudentNum() + 1);
						std::vector<int> studentNo = lim->getStudentNo();
						std::vector<std::string> studentName = lim->getStudentName();
						std::vector<int> studentScore = lim->getStudentScore();
						std::vector<double> studentGPA = lim->getStudentGPA();
						studentNo.push_back(stu->data.getStudentNo());
						studentName.push_back(stu->data.getName());
						studentScore.push_back(stu->data.getLectureScore()[i]);
						studentGPA.push_back(stu->data.getLectureGPA()[i]);
						lim->setStudentNo(studentNo);
						lim->setStudentName(studentName);
						lim->setStudentScore(studentScore);
						lim->setStudentGPA(studentGPA);
						lim->setTotalScore(lim->getTotalScore() + stu->data.getLectureScore()[i]);
						lim->setTotalGPA(lim->getTotalGPA() + stu->data.getLectureGPA()[i]);
						lim->setAverageScore(lim->getTotalScore() / lim->getStudentNum());
					}
				}
				else if (stu->data.getLectureType()[i] == OPTIONAL)
				{
					if (!queryOptional(stu->data.getLectureName()[i], false))
					{
						Node<LectureOptional> *opt = new Node<LectureOptional>;
						opt->data.setName(stu->data.getLectureName()[i]);
						opt->data.setCredit(stu->data.getLectureCredit()[i]);
						opt->data.setStudentNum(opt->data.getStudentNum() + 1);
						std::vector<int> studentNo = opt->data.getStudentNo();
						std::vector<std::string> studentName = opt->data.getStudentName();
						std::vector<int> studentScore = opt->data.getStudentScore();
						std::vector<double> studentGPA = opt->data.getStudentGPA();
						std::vector<int> studentPF = opt->data.getStudentPF();
						studentNo.push_back(stu->data.getStudentNo());
						studentName.push_back(stu->data.getName());
						studentScore.push_back(stu->data.getLectureScore()[i]);
						studentGPA.push_back(stu->data.getLectureGPA()[i]);
						studentPF.push_back(stu->data.getLecturePF()[i]);
						opt->data.setStudentNo(studentNo);
						opt->data.setStudentName(studentName);
						opt->data.setStudentScore(studentScore);
						opt->data.setStudentGPA(studentGPA);
						opt->data.setStudentPF(studentPF);
						opt->data.setStudentPFNum(opt->data.getStudentPFNum() + stu->data.getLecturePF()[i]);
						opt->data.setTotalScore(opt->data.getTotalScore() + (!stu->data.getLecturePF()[i] ? stu->data.getLectureScore()[i] : 0));
						opt->data.setTotalGPA(opt->data.getTotalGPA() + (!stu->data.getLecturePF()[i] ? stu->data.getLectureGPA()[i] : 0));
						if (opt->data.getStudentNum() - opt->data.getStudentPFNum())
							opt->data.setAverageScore(opt->data.getTotalScore() / (opt->data.getStudentNum() - opt->data.getStudentPFNum()));
						if (opt->data.getStudentNum() - opt->data.getStudentPFNum())
							opt->data.setAverageGPA(opt->data.getTotalGPA() / (opt->data.getStudentNum() - opt->data.getStudentPFNum()));
						optionalList.insert_end(opt);
					}
					else
					{
						LectureOptional *opt = findOptional(stu->data.getLectureName()[i]);
						opt->setStudentNum(opt->getStudentNum() + 1);
						std::vector<int> studentNo = opt->getStudentNo();
						std::vector<std::string> studentName = opt->getStudentName();
						std::vector<int> studentScore = opt->getStudentScore();
						std::vector<double> studentGPA = opt->getStudentGPA();
						std::vector<int> studentPF = opt->getStudentPF();
						studentNo.push_back(stu->data.getStudentNo());
						studentName.push_back(stu->data.getName());
						studentScore.push_back(stu->data.getLectureScore()[i]);
						studentGPA.push_back(stu->data.getLectureGPA()[i]);
						studentPF.push_back(stu->data.getLecturePF()[i]);
						opt->setStudentNo(studentNo);
						opt->setStudentName(studentName);
						opt->setStudentScore(studentScore);
						opt->setStudentGPA(studentGPA);
						opt->setStudentPF(studentPF);
						opt->setStudentPFNum(opt->getStudentPFNum() + stu->data.getLecturePF()[i]);
						opt->setTotalScore(opt->getTotalScore() + (!stu->data.getLecturePF()[i] ? stu->data.getLectureScore()[i] : 0));
						opt->setTotalGPA(opt->getTotalGPA() + (!stu->data.getLecturePF()[i] ? stu->data.getLectureGPA()[i] : 0));
						if (opt->getStudentNum() - opt->getStudentPFNum())
							opt->setAverageScore(opt->getTotalScore() / (opt->getStudentNum() - opt->getStudentPFNum()));
						if (opt->getStudentNum() - opt->getStudentPFNum())
							opt->setAverageGPA(opt->getTotalGPA() / (opt->getStudentNum() - opt->getStudentPFNum()));
					}
				}
			}
			stu = studentList.getNext();
		} while (stu != nullptr);
	}
}

// 登录
Account *Database::login(std::string username, std::string password)
{
	Node<User> *user = userList.getFirst();
	while (user != nullptr)
	{
		if (user->data.getName() == username && user->data.getPassword() == password)
			return &user->data;
		user = userList.getNext();
	}
	Node<Admin> *admin = adminList.getFirst();
	while (admin != nullptr)
	{
		if (admin->data.getName() == username && admin->data.getPassword() == password)
			return &admin->data;
		admin = adminList.getNext();
	}
	return nullptr;
}

// 注册
Account *Database::registerUser(std::string username, std::string password, int permission)
{
	if (permission == 1)
	{
		Node<User> *acc = new Node<User>;
		acc->data.setName(username);
		acc->data.setPassword(password);
		userList.insert_end(acc);
		return &acc->data;
	}
	else if (permission == 2)
	{
		Node<Admin> *acc = new Node<Admin>;
		acc->data.setName(username);
		acc->data.setPassword(password);
		adminList.insert_end(acc);
		return &acc->data;
	}
	else
	{
		return nullptr;
	}
}

// 加载账号
void Database::loadAccount(const std::string &userFilename, const std::string &adminFilename)
{
	userList.makeEmpty();
	adminList.makeEmpty();
	encrypt(userFilename);
	encrypt(adminFilename);
	std::ifstream in;
	in.open(userFilename.c_str(), std::ios::in);
	Node<User> *user;
	int tmpPermission = 0;
	// 打开文件成功
	if (in)
	{
		in.seekg(0, std::ios::end);
		int fileSize = in.tellg();
		in.seekg(std::ios::beg);
		while (fileSize - in.tellg() > 2)
		{
			user = new Node<User>;
			if (in >> user->data)
			{
				userList.insert_end(user);
			}
			else
			{
				FileException e(userFilename, "operate", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(userFilename, "open", "read");
		throw e;
	}
	in.close();
	in.open(adminFilename.c_str(), std::ios::in);
	Node<Admin> *admin;
	// 打开文件成功
	if (in)
	{
		in.seekg(0, std::ios::end);
		int fileSize = in.tellg();
		in.seekg(std::ios::beg);
		while (fileSize - in.tellg() > 2)
		{
			admin = new Node<Admin>;
			if (in >> admin->data)
			{
				adminList.insert_end(admin);
			}
			else
			{
				FileException e(adminFilename, "operate", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(adminFilename, "open", "read");
		throw e;
	}
	encrypt(userFilename);
	encrypt(adminFilename);
}

// 保存账号
void Database::saveAccount(const std::string &userFilename, const std::string &adminFilename)
{
	encrypt(userFilename);
	encrypt(adminFilename);
	std::ofstream out;
	out.open(userFilename.c_str(), std::ios::out);
	Node<User> *user = userList.getFirst();
	// 打开文件成功
	if (out)
	{
		while (user != nullptr)
		{
			if (!(out << user->data))
			{
				FileException e(userFilename, "operate", "write");
				throw e;
			}
			user = userList.getNext();
		}
	}
	else
	{
		FileException e(userFilename, "open", "write");
		throw e;
	}
	out.close();
	out.open(adminFilename.c_str(), std::ios::out);
	Node<Admin> *admin = adminList.getFirst();
	// 打开文件成功
	if (out)
	{
		while (admin != nullptr)
		{
			if (!(out << admin->data))
			{
				FileException e(adminFilename, "operate", "write");
				throw e;
			}
			admin = adminList.getNext();
		}
	}
	else
	{
		FileException e(adminFilename, "open", "write");
		throw e;
	}
	encrypt(userFilename);
	encrypt(adminFilename);
}

// 查询账号
int Database::queryAccount(const std::string& username)
{
	int count = 0;
	Node<User>*user = userList.getFirst();
	while (user != nullptr)
	{
		if (user->data.getName() == username)
			count++;
		user = userList.getNext();
	}
	Node<Admin>*admin = adminList.getFirst();
	while (admin != nullptr)
	{
		if (admin->data.getName() == username)
			count++;
		admin = adminList.getNext();
	}
	return count;
}