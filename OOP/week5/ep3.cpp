/*
 *  QUESTION: Usually we access database in ODBC or JDBC. In the process 
 *  		  the PrepareStatement(It's a class.) will be used to void SQL injection.
 *      	  So it's used to construct SQL statement like these: 
 *  
 *  void main(){
 *  	ParseSQL sql = "select ?, ? from student where gender = ? and height >= ? order by ?";
 *
 *		sql.SetAttribute("1", "SID");
 *	 	sql.SetAttribute("2", "Name");
 *	  	sql.SetAttribute("3", "female");
 *	   	sql.SetAttribute("4", "165");
 *     	sql.SetAttribute("5", "gender");
 *     	
 *     	sql.ExecuteSQL();
 *  }
 *  
 *  Here is the outputs:
 *  	select SID, Name from student where gender = female and height >= 165 order by gender
 *  
 *  OR if sql has error, you should give the error information.
 *
 *  Note:
 *  	1. 1, 2, 3, 4, 5   It's not nessary that the numbers is always continuous.
 *  	2. What do you do if the question, ? , does not correspond to the number?
 *  	
 *  THINKING: 
 *  	1. Split raw sql cmd into pieces;
 *  	2. SetAttribute() stroage the postion and content;
 *   	3. join piece to an entire sql command
 *   	4. filter the sensitive character such as "||" 
 *  
 *  AUTHOR: TaQini 1320151097
 *
 *  DATE: 2017-03-29
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class ParseSQL{
    private:
        vector<string> list;
        vector<string> content;
    public:
        ParseSQL(string raw);
        void SetAttribute(string pos, string content);
        void ExecuteSQL();
};

// split function: split(astring,'c');
template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}
// end of spilt function

ParseSQL::ParseSQL(string raw){
    list = split(raw,'?'); // split sql cmd into pieces
    if (raw[raw.size()-1] == '?') 
	    // add a piece in case of '?' in the end of sql cmd to prevent overflow
    	list.push_back(""); 
    for(int i = 0; i < list.size()-1; ++i)
    	content.push_back("?"); // set the default value -> '?'
}

void ParseSQL::SetAttribute(string pos, string cont){
	if (pos[0]-'0'-1 > list.size()-1){ // out of range
		cout << "Error! postion:" << pos << " not found!" << endl;
		exit(0);
	}
	else if (strstr(cont.c_str(),"||") && strstr(cont.c_str(),"-")){
		// protect from SQLi 
		cout << "Sensitive char found!" << endl;
		exit(0);
	}
	else
		// replace "?" with user's input
		content[pos[0]-'0'-1] = cont;
}

void ParseSQL::ExecuteSQL(){
	string exec; // sql cmd to exec
	// make up pieces to an entire sql cmd
	for (int i = 0; i < list.size()-1; ++i)
		exec += list[i] + content[i];
	exec += list[list.size()-1];
	
	cout << exec << endl;
}

int main(){
    string cmd = "select ?, ? from student where gender = ? and height >= ? order by ?";
    ParseSQL sql = cmd;

    sql.SetAttribute("3", "female");
    sql.SetAttribute("1", "SID");
	sql.SetAttribute("2", "Name");
	sql.SetAttribute("4", "165");
	sql.SetAttribute("5", "gender");
	sql.ExecuteSQL();

	sql.SetAttribute("2", "ReSetAttribute"); 
	sql.ExecuteSQL();

	sql.SetAttribute("3", "female || gender = true - "); // SQLi here
	sql.SetAttribute("8", "Name"); //Out of Range
}
