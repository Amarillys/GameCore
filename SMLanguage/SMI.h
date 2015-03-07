#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <algorithm>
#define SAVE_SIZE 65536

namespace Core{
	class ResFile;
	class Bundle;
}

using namespace std;

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
		GUIAction actor;

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

		vector<string> buffer;
		size_t now_pos;

	public:
		Interpreter();
		~Interpreter();

		void RunOneStep();

		bool LoadSMO(const string& filename);	//����SMO�ļ�
		void Save(Bundle<SAVE_SIZE>&);	//���������״̬�Դ浵
		bool Load(Bundle<SAVE_SIZE>&);	//��ȡ������״̬

										//�ж��ຯ��
		bool NextIsText();	//��һ��λ���Ƿ�Ϊ�Ի�
		bool CmdOver();	//ָ���Ƿ��ȡ���

						//��ȡ�ຯ��
		string PopCmd();	//��ȡָ������ϵ�ͳ�ջָ��
		string PopArg();	//��ȡ���ֲ����������˫�������Զ�ȥ��
		_int32 PopIntArg();	//��ȡ���ֲ���

		string PopText();	//��ȡ���֣���ָ�ʼǰ�����ߵ����ֽ�����֮ǰ����������ѽ������򷵻����ֽ�����
		string PopName();	//��ȡ��ǰ�Ի�������

							//�����ຯ��
		bool Goto(string&);	//��ת��ĳ����ǩ
		bool OutStack();	//����ջ�����Զ��Թ���ջ��

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
