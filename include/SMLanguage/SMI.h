#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <algorithm>
#include "../Core/Bundle.h"
#define SAVE_SIZE 65536

using namespace std;
using namespace Core;

//typedef unsigned char BYTE;

namespace SMI
{
	class GUIAction
	{
		void textOut(string& text);
		void nameOut(string& name);

	};

	class Interpreter
	{
	private:
		enum state
		{
			TEXT,
			TEXT_END,
			NAME,
			LABEL_IN,
			LABEL_READING,
			LABEL_EXITING,
			CMD_START,
			CMD_MULTI,
			CMD_SINGLE,
			CMD_END,

		};

		string file_name;
		ifstream file;

		state now_state;
		stack<state> stk_state;

		unordered_set<char> keywords;

		unordered_map<string, int> labels;
		unordered_map<string, int> flags;
		bool is_text;
		bool is_end;

		string cmd;
		vector<string> str_args;
		vector<int> num_args;

		string text;
		string name;

		vector<string> all_text;
		size_t now_pos;

	public:
		Interpreter();
		~Interpreter();

		bool RunOneStep();

		bool LoadSMO(const char* filename);	//加载SMO文件
		void Save(Bundle<SAVE_SIZE>&);	//保存解释器状态以存档
		bool Load(Bundle<SAVE_SIZE>&);	//读取解释器状态

										//判断类函数
		bool NextIsText();	//下一个位置是否为对话
		bool CmdOver();	//指令是否读取完成

						//读取类函数
		string PopCmd();	//读取指令，包括断点和出栈指令
		void PopArg(vector<string>&);	//读取文字参数，如果有双引号则自动去掉
		void PopIntArg(vector<int>&);	//读取数字参数
		void PopFlags(unordered_map<string, int>&);	//返回所有Flag
		
		string PopText();	//读取文字，到指令开始前，或者到文字结束符之前，如果文字已结束，则返回文字结束符
		string PopName();	//读取当前对话者名称

							//操作类函数
		bool Goto(string&);	//跳转到某个标签
		bool OutStack();	//跳出栈区，自动略过子栈区

		size_t Serialize(BYTE *buffer);
		void Unserialize(BYTE *buffer);

	private:
		bool analysisOneLine(string& line);
		bool updateState(char word);
		void cmdAnalysis(string& command);

		void cmdOperate();

		void addLabel();
		void scanFile();
		bool isKeyword(char word);

		void splitArgs(string& str, vector<string>& arg_array);
		string& trim(string& str);

		void debug();
	};
}
