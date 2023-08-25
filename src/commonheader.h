#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <string.h>
#include <conio.h>
#include <time.h>

class Database;

enum LectureType
{
	DEFAULT,
	REQUIRED,
	LIMITED,
	OPTIONAL
};

class Info
{
protected:
	// 名称（name）、唯一标识符（uid）、调试模式（DebugMode）
	std::string name;
	int uid;
	static int currentUid;
	static bool DebugMode;

public:
	Info();
	Info(std::string inputName);
	virtual ~Info() = 0;

	virtual std::string getName();
	int getUid();
	static bool isDebugMode();

	// virtual void updateInfo(Database& database) = 0;
	virtual void setName(std::string inputName) = 0;
	static void setDebug(bool inputDebugMode)
	{
		DebugMode = inputDebugMode;
	}

	virtual void printInfo(int) = 0;
	virtual void printInfo(int, int) = 0;
};

class Account : virtual public Info
{
protected:
	std::string password;

public:
	Account();
	Account(std::string inputName, std::string inputPassword);
	~Account();
	virtual std::string getPassword();
	virtual void setName(std::string inputName);
	virtual void setPassword(std::string inputPassword);
	virtual int getPermission() { return 0; }
	virtual void printInfo(int) {}
	virtual void printInfo(int, int) {}
	friend std::istream& operator>>(std::istream&, Account&);
	friend std::ostream& operator<<(std::ostream&, Account&);
};

class User : virtual public Account
{
public:
	int getPermission() { return 1; }
};

class Admin : virtual public Account
{
public:
	int getPermission() { return 2; }
};

// Student类，对学生信息进行封装
class Student : virtual public Info, User
{
protected:
	// 学号（studentNo）、姓名（name）、各科名称（lectureName）、各科类型（lectureType）、各科成绩（lectureScore）、各科学分（lectureCredit）、学分绩点（lectureGPA）、平均学分绩点（averageGPA）
	int studentNo;
	std::vector<std::string> lectureName;
	std::vector<LectureType> lectureType;
	std::vector<int> lectureScore;
	std::vector<int> lectureCredit;
	std::vector<double> lectureGPA;
	std::vector<int> lecturePF;
	int lectureNum;
	int lecturePFNum;
	int totalScore;
	int totalCredit;
	int totalPFCredit;
	double totalGPA;
	double averageScore;
	double averageGPA;

public:
	// 构造函数
	Student();

	// 析构函数
	~Student();

	// 访问数据成员的接口函数
	int getStudentNo();
	std::string getName();
	std::vector<std::string> getLectureName();
	std::vector<LectureType> getLectureType();
	std::vector<int> getLectureScore();
	std::vector<int> getLectureCredit();
	std::vector<double> getLectureGPA();
	std::vector<int> getLecturePF();
	int getLectureNum();
	int getLecturePFNum();
	int getTotalScore();
	int getTotalCredit();
	int getTotalPFCredit();
	double getTotalGPA();
	double getAverageScore();
	double getAverageGPA();

	// 修改数据成员的接口函数
	void updateInfo(Database &database);
	void setStudentNo(int inputStudentNo);
	void setName(std::string inputName);
	void setLectureName(std::vector<std::string> inputLectureName);
	void setLectureType(std::vector<LectureType> inputLectureType);
	void setLectureScore(std::vector<int> inputLectureScore);
	void setLectureCredit(std::vector<int> inputLectureCredit);
	void setLectureGPA(std::vector<double> inputLectureGPA);
	void setLecturePF(std::vector<int> inputLecturePF);
	void setLectureNum(int inputLectureNum);
	void setLecturePFNum(int inputLecturePFNum);
	void setTotalScore(int inputTotalScore);
	void setTotalCredit(int inputTotalCredit);
	void setTotalPFCredit(int inputTotalPFCredit);
	void setTotalGPA(double inputTotalGPA);
	void setAverageScore(double inputAverageScore);
	void setAverageGPA(double inputAverageGPA);

	// 打印学生信息
	void printInfo(int) {}
	void printInfo(int widthStudentNo, int widthName);
	void printStudentInfo();

	// 运算符重载
	friend std::istream &operator>>(std::istream &, Student &);
	friend std::ostream &operator<<(std::ostream &, Student &);
};

class Lecture : virtual public Info
{
protected:
	// 课程名称（name）、课程学分（credit）
	int credit;
	std::vector<int> studentNo;
	std::vector<std::string> studentName;
	std::vector<int> studentScore;
	std::vector<double> studentGPA;
	int studentNum;
	int totalScore;
	double totalGPA;
	int averageScore;
	double averageGPA;

public:
	// 构造函数
	Lecture();

	// 析构函数
	virtual ~Lecture();

	// 访问数据成员的接口函数
	virtual LectureType getLectureType() { return DEFAULT; }
	virtual int getCredit();
	virtual std::vector<int> getStudentNo();
	virtual std::vector<std::string> getStudentName();
	virtual std::vector<int> getStudentScore();
	virtual std::vector<double> getStudentGPA();
	virtual int getStudentNum();
	virtual int getTotalScore();
	virtual double getTotalGPA();
	virtual int getAverageScore();
	virtual double getAverageGPA();

	// 设置数据成员的接口函数
	virtual void updateInfo(Database &database);
	virtual void setName(std::string inputName);
	virtual void setCredit(int inputCredit);
	virtual void setStudentNo(std::vector<int> inputStudentNo);
	virtual void setStudentName(std::vector<std::string> inputStudentName);
	virtual void setStudentScore(std::vector<int> inputStudentScore);
	virtual void setStudentGPA(std::vector<double> inputStudentGPA);
	virtual void setStudentNum(int inputStudentNum);
	virtual void setTotalScore(int inputTotalScore);
	virtual void setTotalGPA(double inputTotalGPA);
	virtual void setAverageScore(int inputAverageScore);
	virtual void setAverageGPA(double inputAverageGPA);
	virtual void addStudent(int inputStudentNo, std::string inputStudentName, int inputStudentScore, double inputStudentGPA);

	// 打印课程信息
	virtual void printInfo(int widthName);
	virtual void printInfo(int, int) {}
	virtual void printLectureInfo();

	// 运算符重载
	friend std::istream &operator>>(std::istream &, Lecture &);
	friend std::ostream &operator<<(std::ostream &, Lecture &);
};

class LectureRequired : virtual public Lecture
{
protected:
public:
	// 构造函数
	LectureRequired();

	// 析构函数
	~LectureRequired();

	// 访问数据成员的接口函数
	virtual LectureType getLectureType() { return REQUIRED; }

	// 设置数据成员的接口函数
	void updateInfo(Database &database);

	// 打印课程信息
	void printInfo(int widthName);
	void printInfo(int, int) {}
	void printLectureInfo();

	// 运算符重载
	friend std::istream &operator>>(std::istream &, LectureRequired &);
	friend std::ostream &operator<<(std::ostream &, LectureRequired &);
};

class LectureLimited : virtual public Lecture
{
protected:
public:
	// 构造函数
	LectureLimited();

	// 析构函数
	~LectureLimited();

	// 访问数据成员的接口函数
	virtual LectureType getLectureType() { return LIMITED; }

	// 设置数据成员的接口函数
	void updateInfo(Database &database);

	// 打印课程信息
	void printInfo(int widthName);
	void printInfo(int, int) {}
	void printLectureInfo();

	// 运算符重载
	friend std::istream &operator>>(std::istream &, LectureLimited &);
	friend std::ostream &operator<<(std::ostream &, LectureLimited &);
};

class LectureOptional : virtual public Lecture
{
protected:
	std::vector<int> studentPF;
	int studentPFNum;

public:
	// 构造函数
	LectureOptional();

	// 析构函数
	~LectureOptional();

	// 访问数据成员的接口函数
	virtual LectureType getLectureType() { return OPTIONAL; }
	std::vector<int> getStudentPF();
	int getStudentPFNum();

	// 设置数据成员的接口函数
	void setStudentPF(std::vector<int> inputStudentPF);
	void setStudentPFNum(int inputStudentPFNum);
	void updateInfo(Database &database);
	virtual void addStudent(int inputStudentNo, std::string inputStudentName, int inputStudentScore, double inputStudentGPA, bool inputStudentPF);

	// 打印课程信息
	void printInfo(int widthName);
	void printInfo(int, int) {}
	void printLectureInfo();

	// 运算符重载
	friend std::istream &operator>>(std::istream &, LectureOptional &);
	friend std::ostream &operator<<(std::ostream &, LectureOptional &);
};

// 基于模板的链表结点定义
template <class T>
struct Node
{
	T data;
	Node<T> *next;
};

// 基于模板的链表类声明
template <class T>
class LinkedList
{
private:
	Node<T> *head;										 // 头结点
	Node<T> *current;									 // 当前结点
	inline void deepCopy(const LinkedList<T> &original); // 内联函数，用于深拷贝
public:
	// 构造函数、复制构造函数、析构函数
	LinkedList();
	LinkedList(const LinkedList<T> &aplist);
	~LinkedList();

	void insert(Node<T> *newNode);	   // 在头部之前插入元素
	void insert_end(Node<T> *newNode); // 在尾部插入
	Node<T> *getFirst();			   // 获得链表头的数据
	inline Node<T> *getNext();		   // 获得当前结点的下一个数据
	bool find(const T &element);	   // 查找一个数据
	bool retrieve(T &element);		   // 检索一个数据
	bool replace(const T &newElement); // 替换一个数据
	bool remove(Node<T> *node);		   // 移除一个数据
	bool isEmpty() const;			   // 判断链表是否为空
	void makeEmpty();				   // 清空链表
	int size();						   // 获得链表的大小

	// 重载"="运算符
	LinkedList<T> &operator=(const LinkedList<T> &rlist);
};

// 无参构造函数
template <class T>
LinkedList<T>::LinkedList()
{
	head = current = nullptr;
}

// 复制构造函数
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &aplist)
{
	deepCopy(aplist);
}

// 析构函数
template <class T>
LinkedList<T>::~LinkedList()
{
	makeEmpty();
}

// 在头部之前插入函数
template <class T>
void LinkedList<T>::insert(Node<T> *newNode)
{
	current = nullptr;
	newNode->next = head;
	head = newNode;
}

// 在尾部之后插入函数
template <class T>
void LinkedList<T>::insert_end(Node<T> *newNode)
{
	current = nullptr;
	Node<T> *tail = head;
	newNode->next = nullptr;
	if (tail == nullptr)
	{
		head = newNode;
	}
	else
	{
		while (tail->next != nullptr)
		{
			tail = tail->next;
		}
		tail->next = newNode;
	}
}

// 获得链表头的函数
template <class T>
Node<T> *LinkedList<T>::getFirst()
{
	if (head == nullptr)
	{
		return nullptr;
	}
	current = head;
	return head;
}

// 获得下一个数据
template <class T>
Node<T> *LinkedList<T>::getNext()
{
	if (current == nullptr)
	{
		return nullptr;
	}
	if (current->next == nullptr)
	{
		current = nullptr;
		return nullptr;
	}
	current = current->next;
	return current;
}

// 查找一个数据
template <class T>
bool LinkedList<T>::find(const T &element)
{
	Node<T> *n;
	n = getFirst();
	if (n == nullptr)
	{
		return false;
	}
	do
	{
		if (n->data == element)
		{
			return true;
		}
		n = getNext();
	} while (n != nullptr);
	return false;
}

// 检索一个数据
template <class T>
bool LinkedList<T>::retrieve(T &element)
{
	if (!find(element))
	{
		return false;
	}
	element = current->data;
	return true;
}

// 替换一个数据
template <class T>
bool LinkedList<T>::replace(const T &newElement)
{
	if (current == nullptr)
	{
		return false;
	}
	current->data = newElement;
	return true;
}

// 移除一个数据
template <class T>
bool LinkedList<T>::remove(Node<T> *n)
{
	current = nullptr;
	if (head == nullptr)
	{
		return false;
	}
	Node<T> *tmp = head;
	if (tmp == n)
	{
		head = tmp->next;
		delete tmp;
		return true;
	}
	while (tmp->next != nullptr)
	{
		if (tmp->next == n)
		{
			Node<T> *ptr = tmp->next;
			tmp->next = ptr->next;
			delete ptr;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

// 判断是否为空
template <class T>
bool LinkedList<T>::isEmpty() const
{
	return head == nullptr;
}

// 将链表清空
template <class T>
void LinkedList<T>::makeEmpty()
{
	while (head != nullptr)
	{
		current = head;
		head = head->next;
		delete current;
	}
	current = nullptr;
}

// 获得链表大小
template <class T>
int LinkedList<T>::size()
{
	int size = 0;
	Node<T> *tmp = head;
	while (tmp != nullptr)
	{
		size++;
		tmp = tmp->next;
	}
	return size;
}

//"="运算符重载
template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rlist)
{
	if (this == &rlist)
	{
		return *this;
	}
	makeEmpty();
	deepCopy(rlist);
	return *this;
}

// 深拷贝函数
template <class T>
void LinkedList<T>::deepCopy(const LinkedList<T> &original)
{
	head = current = nullptr;
	if (original.head == nullptr)
	{
		return;
	}
	Node<T> *copy = head = new Node<T>;
	Node<T> *origin = original.head;
	copy->data = origin->data;
	if (origin == original.current)
	{
		current = copy;
	}
	while (origin->next != nullptr)
	{
		copy->next = new Node<T>;
		origin = origin->next;
		copy = copy->next;
		copy->data = origin->data;
		if (origin == original.current)
		{
			current = copy;
		}
	}
	copy->next = nullptr;
}

class FileException
{
public:
	std::string filename;
	std::string mode;
	std::string type;

	FileException(std::string inputFilename, std::string inputMode, std::string inputType)
	{
		filename = inputFilename;
		mode = inputMode;
		type = inputType;
	};

	~FileException(){};
};

// 数据库类，对程序使用的数据结构进行封装
class Database
{
private:
	LinkedList<Student> studentList;
	LinkedList<LectureRequired> requiredList;
	LinkedList<LectureLimited> limitedList;
	LinkedList<LectureOptional> optionalList;
	LinkedList<User> userList;
	LinkedList<Admin> adminList;

public:
	// 构造函数与析构函数
	Database();
	~Database();

	// 列表相关函数
	int getStudentListSize();
	int getRequiredListSize();
	int getLimitedListSize();
	int getOptionalListSize();

	// 文件读写函数
	void load();
	void save();

	void loadStudent(const std::string &filename);
	void loadRequired(const std::string &filename);
	void loadLimited(const std::string &filename);
	void loadOptional(const std::string &filename);

	void saveStudent(const std::string &filename);
	void saveRequired(const std::string &filename);
	void saveLimited(const std::string &filename);
	void saveOptional(const std::string &filename);

	void encrypt(const std::string &filename);
	void encrypt_key(const std::string &filename, const std::string &keyFilename);
	void key_gen(const std::string &filename);
	std::string timeStampToString(const time_t &timeStamp);

	// 删除学生与课程函数
	bool deleteStudent(const std::string &name);
	bool deleteStudent(int studentNo);
	bool deleteRequired(const std::string &name);
	bool deleteLimited(const std::string &name);
	bool deleteOptional(const std::string &name);

	// 添加学生与课程函数
	void addStudent();
	void addRequired(const std::string &name, int credit);
	void addLimited(const std::string &name, int credit);
	void addOptional(const std::string &name, int credit);
	void addStudentToLecture(const std::string &name, LectureType type, Student &stu);

	//// 显示学生与课程函数
	// void displayStudent(const std::string& name);
	// void displayStudent(int studentNo);
	// void displayLecture(const std::string& name);
	// void displayRequired(const std::string& name);
	// void displayLimited(const std::string& name);
	// void displayOptional(const std::string& name);
	// int displayAllStudent();
	// int displayAllLecture(LectureType type);

	// 修改学生与课程函数
	bool modifyStudent(const std::string &name);
	bool modifyStudent(int studentNo);
	bool modifyLecture(const std::string &name);
	bool modifyRequired(const std::string &name);
	bool modifyLimited(const std::string &name);
	bool modifyOptional(const std::string &name);

	// 查询学生与课程函数
	int queryStudent(const std::string &name, bool display = true);
	int queryStudent(int studentNo, bool display = true);
	int queryLecture(const std::string &name, bool display = true);
	int queryRequired(const std::string &name, bool display = true);
	int queryLimited(const std::string &name, bool display = true);
	int queryOptional(const std::string &name, bool display = true);
	Student *findStudent(const std::string &name);
	Student *findStudent(int studentNo);
	Lecture *findLecture(const std::string &name);
	LectureRequired *findRequired(const std::string &name);
	LectureLimited *findLimited(const std::string &name);
	LectureOptional *findOptional(const std::string &name);

	// 排序函数
	void sortStudent(int direction, int keycol);
	void sortLecture(LectureType type, int direction, int keycol);
	void sortStudentCustom(Student **head, int length, int direction, int keycol);
	void sortLectureCustom(Lecture **head, int length, int direction, int keycol);
	double compareStudent(Student *a, Student *b, int direction, int keycol);
	double compareLecture(Lecture *a, Lecture *b, int direction, int keycol);

	// 打印函数
	void printStudent();
	void printStudent(int studentNo);
	void printStudent(const std::string &name);
	void printLecture();
	void printLecture(LectureType type);
	void printLecture(const std::string &name);

	// 百分制成绩转化为绩点
	double calculateGPA(int score);

	// 在修改后更新学生与课程
	void updateStudent();
	void updateLecture();

	// 登录与注册函数
	Account *login(std::string username, std::string password);
	Account *registerUser(std::string username, std::string password, int permission);
	void loadAccount(const std::string &userFilename, const std::string &adminFilename);
	void saveAccount(const std::string &userFilename, const std::string &adminFilename);
	int queryAccount(const std::string &username);
};

// 用户界面类
class UserInterface
{
private:
	Database *database;			 // 数据库指针
	static Account *currentUser; // 当前用户指针

public:
	// 构造函数
	UserInterface();

	// 析构函数
	~UserInterface();

	// 运行与交互主函数
	bool run();

	// 功能函数
	Account *login(); // 登录界面
	void welcome();	  // 欢迎界面
	bool searchInfo();
	bool searchStudent(); // 查询学生信息
	bool searchLecture(); // 查询课程信息
	bool sortInfo();
	bool sortStudent(); // 排序学生信息
	bool sortLecture(); // 排序课程信息
	bool addInfo();
	bool addStudent(); // 添加学生信息
	bool addLecture(); // 添加课程信息
	bool deleteInfo();
	bool deleteStudent(); // 删除学生信息
	bool deleteLecture(); // 删除课程信息
	bool modifyInfo();
	bool modifyStudent(); // 修改学生信息
	bool modifyLecture(); // 修改课程信息
	bool load();		  // 读取文件信息
	bool save();		  // 保存文件信息
	bool print();		  // 打印信息
	bool printStudent();  // 打印学生信息
	bool printLecture();  // 打印课程信息
	bool debug();		  // 调试模式
	bool about();		  // 关于程序
	void quit();		  // 退出程序
	void pause();		  // 暂停程序
};
