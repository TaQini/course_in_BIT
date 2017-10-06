/*
 *  QUESTION: 人员、student、teacher类，人员类保存姓名，性别，出生年月，ID（学生以入学年份开头，教师以t开头）。
 *    要求：1) 学生能知道某一门课是哪位老师讲课;
 *         2) 学生根据课程名称查询成绩；
 *         3) 教师通过ID能知道学生的基本信息（姓名、性别和年龄）；
 *         4) 教师能给出课程成绩；
 *         5) 根据给出的示例性数据，根据需要补充其他类，综合分析类间的组合、继承关系，完成上述功能。
 *
 *		示例性的数据：
 *
 *		学生姓名    性别     出生年月       ID
 *  	李逵        男       1963.8       20120801       
 *   	花千羽      女       1999.10      20131011
 *    	TF-BOY      男       2003.9       20140901
 *     	冷冰冰      女       2010.12      20151217
 *
 *		教师姓名    性别     出生年月        ID
 *  	孙悟空      男       1950.8       t20011211
 *   	张三丰      男       1979.10      t20160708
 *
 *		课程编号    课程名称    讲课教师
 *  	COM002    知识图谱     孙悟空
 *   	COM016    大数据       张三丰
 *
 * 		学生ID       课程编号      成绩
 *   	20120801       COM002        86
 *    	20131011       COM002        77
 *	    20140901       COM002        90
 *	    20151217       COM002        59
 *	 
 *  THINKING: 
 *  	combination. (see the code)
 *  	
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-04-12
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

class member{
	private:
		int m_key; // use for select a member
		int m_size;
		vector<string> m_name; // base info
		vector<string> m_sex;
		vector<string> m_birthday;
		vector<string> m_ID;
		vector<string> m_pwd; // use for login 
	public:
		member() : m_size(0){}; // sz = 0
		void insert(string name, string sex, string birthday, string ID, string pwd); // insert information into Table Member
		int login(); // login system
		int check_ID(string ID); // check ID vaild? if vaild, return the position of member in Table 
		string get_name(int key){ return m_name[key]; }
		string get_sex(int key){ return m_sex[key]; }
		string get_birthday(int key) { return m_birthday[key]; }
		string get_id(int key) { return m_ID[key]; }
		int get_key() { return m_key;}
		int get_size() { return m_size;}
};

int member::check_ID(string ID){
	int key = -1;
	for (int i=0; i<m_size; i++){
		if (ID == m_ID[i]) { // ID is in table
			key = i; break;
		}
	}
	if (key < 0){ // ID NOT Found 
		cout << "ID NOT Found!" << endl;
		exit(0);
	} 
	return key;
}

int member::login(){
	string ID;
	string pwd;

	cout << "Login: pls input ur ID: ";
	cin >> ID; // get ID

	int key = check_ID(ID); // check ID
	
	cout << "Pls input ur password: ";
	cin >> pwd; // get pwd

	if (pwd == m_pwd[key]) {
		cout << "Login OK!" << endl;
		m_key = key;
	} // check pwd
	else{
		cout << "password error!" << endl;
		exit(0);
	}
}

void member::insert(string name, string sex, string birthday, string ID, string pwd){
	m_name.push_back(name);
	m_sex.push_back(sex);
	m_birthday.push_back(birthday);
	m_ID.push_back(ID);
	m_pwd.push_back(pwd);
	m_size ++;
}

class course{
	private:
		int c_size;
		vector<string> c_cno;
		vector<string> c_cname;
		vector<string> c_teacher;
	public:
		course(): c_size(0){};
		void insert(string cno, string cname, string teacher); // insert into Table Course
		int c_Query(string cname); // query by course name; return the position in table course
		string get_cno(int key){ return c_cno[key]; }
		string get_teacher(int key){ return c_teacher[key]; };
};

int course::c_Query(string cname){
	int key = -1;
	for (int i=0; i<c_size; i++){
		if (cname == c_cname[i]){
			key = i; break;
		}
	}
	if (key < 0){ // check course exist?
		cout << "Course NOT Found!" << endl;
		exit(0);
	}
	return key;
}

void course::insert(string cno, string cname, string teacher){
	c_cno.push_back(cno);
	c_cname.push_back(cname);
	c_teacher.push_back(teacher);
	c_size ++;
}

class score{
	private:
		int s_size;
		vector<string> s_ID;
		vector<string> s_cno;
		vector<int> s_sc;
	public:
		score() : s_size(0){};
		void insert(string ID, string cno, int sc);
		int s_Query(string ID, string cno); // query by ID and course number;
		int get_sc(int key){ return s_sc[key]; }
		void set_sc(int key, int sc){ s_sc[key] = sc;}
};

int score::s_Query(string ID, string cno){
	int key = -1; //similar with c_query
	for (int i=0; i<s_size; i++){
		if (ID == s_ID[i] && cno == s_cno[i]){
			key = i; break;
		}
	}
	if (key < 0){
		cout << "ID or Cno NOT Found!" << endl;
		exit(0);
	}
	return key;
}

void score::insert(string ID, string cno, int sc){
	s_ID.push_back(ID);
	s_cno.push_back(cno);
	s_sc.push_back(sc);
	s_size ++;
}

class student : public member, public course, public score{
	public:
		student(member &m, course &c, score &s) : member(m), course(c), score(s){}; //combination
		void who_teach(string cname); // function 1 Cname -> Teacher
		void score_of(string cname);  // function 2 Cname -> Score
		string give_info(string ID);  // show base information
		friend void show_info(student &a, string ID); // teacher can call it
		void menu(); // not important
};

void student::who_teach(string cname){
	cout << get_teacher(c_Query(cname)) << endl;
}

void student::score_of(string cname){
	string cno;
	string ID;
	int key;
	cno = get_cno(c_Query(cname));
	ID = get_id(get_key());
	key = s_Query(ID,cno);
	cout << get_sc(key) << endl;
}

string student::give_info(string ID){
	int key = check_ID(ID);
	string buf; //temp buffer
	buf += "Name: " + get_name(key) + "\n";
	buf += "Sex: " + get_sex(key) + "\n";
	buf += "ID: " + get_id(key) + "\n";
	buf += "Birthday: " + get_birthday(key);
	return buf;
}

void show_info(student &a, string ID){
	cout << a.give_info(ID) << endl;
}

class teacher : public member, public course, public score{
	public:
		teacher(member &m, course &c, score &s) : member(m), course(c), score(s){}; //combination
		void check_info(student &a, string ID); // show students' information
		void give_score(string ID, string cname, int sc, student &a, score &s); // update score 
		void menu(); // not important
};

void teacher::check_info(student &a, string ID){
	show_info(a, ID);
}

void teacher::give_score(string ID, string cname, int sc, student &a, score &s){
	string cno;
	int key;
	cno = get_cno(c_Query(cname));
	key = s_Query(ID, cno); 
	set_sc(key, sc);  // update score in Table Teacher
	a.set_sc(key, sc);// update score in Table Student
	s.set_sc(key, sc);// update score in Table Score
}

void menu(){ // not important
	cout << "Welcome to TaQini's DBMS!" << endl;
	cout << "1. I am teacher" << endl;
	cout << "2. I am student" << endl;
	cout << "0. Quit system" << endl;
}

void teacher::menu(){ // not important
	cout << "\nHello, Teacher " + get_name(get_key()) + "!" << endl;
	cout << "1. Show student's infomation" << endl;
	cout << "2. Give student's score" << endl;
	cout << "3. Back to menu" << endl;
	cout << "0. Quit system" << endl;
}

void student::menu(){ // not important
	cout << "\nHello, " + get_name(get_key()) + "!" << endl;
	cout << "1. Show score" << endl;
	cout << "2. Show who teach me course" << endl;
	cout << "3. Back to menu" << endl;
	cout << "0. Quit system" << endl;
}

void err_opt(){ // not important
	cout << "Wrong option!" << endl; 
	exit(0);
}

void quit(){ // not important
	cout << "Thanks for using!" << endl;
	exit(0);
}

int main(){
	// insert data into database
	member M;
	
	course C;
	C.insert("COM002","知识图谱","孙悟空");
	C.insert("COM016","大数据","张三丰");
	
	score S;
	S.insert("20120801","COM002",86);
	S.insert("20131011","COM002",77);
	S.insert("20140901","COM002",90);
	S.insert("20151217","COM002",59);

	student A(M,C,S);
	A.member::insert("李逵","男","1963.8","20120801","123456");
	A.member::insert("花千羽","女","1999.10","20131011","123456");
	A.member::insert("TF-BOY","男","2003.9","20140901","123456");
	A.member::insert("冷冰冰","女","2010.12","20151217","123456");

	teacher B(M,C,S);
	B.member::insert("孙悟空","男","1950.8","t20011211","888888");
	B.member::insert("张三丰","男","1979.10","t20160708","888888");


	// start DBMS
	while (1){
		menu();
		int opt;
		cin >> opt;
		if (opt == 1){ // teacher
			B.login();
			while (1){
				B.menu();
				int o;
				cin >> o;
				if (o == 1){ // show student info
					cout << "Input Student ID: ";
					string ID;
					cin >> ID;
					show_info(A, ID);
				}
				else if (o == 2){ // give score
					cout << "Input Course Name: ";
					string cname;
					cin >> cname;
					
					cout << "Input Student ID: ";
					string ID;
					cin >> ID;
					
					cout << "Give a score: ";
					int sc;
					cin >> sc;

					B.give_score(ID, cname, sc, A, S);
				}
				else if (o == 3){ // back
					break;
				}
				else if (o == 0){ // quit
					quit();
				}
				else{ // other
					err_opt();
				}	
			}
		}
		else if (opt == 2){
			A.login();
			while (1){ // student
				A.menu();
				int o;
				cin >> o;
				if (o == 1){ // show score
					cout << "Input Course Name: ";
					string cname;
					cin >> cname;

					A.score_of(cname);
				}
				else if (o == 2){ // show teacher
					cout << "Input Course Name: ";
					string cname;
					cin >> cname;

					A.who_teach(cname);
				}
				else if (o == 3){ // back
					break;
				}
				else if (o == 0){ // quit
					quit();
				}
				else{ // other
					err_opt();
				}
			}
		}
		else if (opt == 0){ // menu quit
			quit();
		}
		else{ //..
			err_opt();
		}
	}
}

/*output information
$ ./ep3 
Welcome to TaQini's DBMS!
1. I am teacher
2. I am student
0. Quit system
1
Login: pls input ur ID: t20011211
Pls input ur password: 888888
Login OK!

Hello, Teacher 孙悟空!
1. Show student's infomation
2. Give student's score
3. Back to menu
0. Quit system
1
Input Student ID: 20151217
Name: 冷冰冰
Sex: 女
ID: 20151217
Birthday: 2010.12

Hello, Teacher 孙悟空!
1. Show student's infomation
2. Give student's score
3. Back to menu
0. Quit system
2
Input Course Name: 知识图谱
Input Student ID: 20151217
Give a score: 99

Hello, Teacher 孙悟空!
1. Show student's infomation
2. Give student's score
3. Back to menu
0. Quit system
3
Welcome to TaQini's DBMS!
1. I am teacher
2. I am student
0. Quit system
2
Login: pls input ur ID: 20151217
Pls input ur password: 123456
Login OK!

Hello, 冷冰冰!
1. Show score
2. Show who teach me course
3. Back to menu
0. Quit system
2
Input Course Name: 知识图谱
孙悟空

Hello, 冷冰冰!
1. Show score
2. Show who teach me course
3. Back to menu
0. Quit system
1
Input Course Name: 知识图谱
99

Hello, 冷冰冰!
1. Show score
2. Show who teach me course
3. Back to menu
0. Quit system
0
Thanks for using!
*/ /*
Mr.Hu, 
	Thanks for theaching us OOP!
	OOP is cool!
						~ TaQini
*/ //..