#include "SMI.h"
#include "..\Core\Bundle.h"
#include "..\Core\FileSystem.h"

using namespace SMI;
using namespace Core;

SMI::Interpreter::Interpreter()
{
}

SMI::Interpreter::~Interpreter()
{
}

void SMI::Interpreter::RunOneStep()
{
	if (now_pos < buffer.size()) {
		name = "";
		cmd = "";
		text = "";
		analysisOneLine(buffer[now_pos++]);
	}
}

bool SMI::Interpreter::LoadSMO(const string& filename)
{
	//file_name = string(filename);
	//file.open(file_name, ios::in);
	Core::ResFile r(filename);	//使用ResFile以读取文件包内容


	keywords.insert('[');
	keywords.insert('<');
	keywords.insert('-');

	string str;

	bool eof = false;

	//read file
	while (!eof) {
		getline(file, str);
		eof = file.eof();

		//jump the comment
		str = str.substr(0, str.find('#'));

		//remove blanks
		str = trim(str);

		buffer.push_back(str);
	}

	//file.close();
	now_state = TEXT;

	//build label list;
	scanFile();
	return true;
}

bool SMI::Interpreter::analysisOneLine(string & line)
{
	bool result = false;
	is_text = false;
	string command = "";

	for (auto iter = line.begin(); iter != line.end(); ++iter) {
		if (!updateState(*iter)) {			//updata state, do something acourding weather changed the state
			switch (now_state)
			{
			case SMI::Interpreter::TEXT:
				text += *iter;
				is_text = true;
				break;
			case SMI::Interpreter::NAME:
				name += *iter;
				break;
			case SMI::Interpreter::CMD_SINGLE:
				command += *iter;
				break;
			case SMI::Interpreter::CMD_MULTI:
				command += *iter;
				break;
			default:
				break;
			}
		} else {
			switch (now_state)
			{
			case SMI::Interpreter::TEXT_END:
				result = true;
				break;
			case SMI::Interpreter::CMD_MULTI:
				//jump the '>' in "<!>"
				++iter;
				break;
			case SMI::Interpreter::CMD_END:
				//exit from the CMD_MULTI
				if (stk_state.top() == CMD_MULTI) {
					stk_state.pop();
					now_state = CMD_SINGLE;
					break;
				}

				//exit the CMD state, do as the command said
				if (command != "") {
					cmdAnalysis(command);
					command = "";
				}
				//resume the state
				now_state = stk_state.top();
				stk_state.pop();
				break;
			default:
				break;
			}
		}
	}
	if (command != "") {
		cmdAnalysis(command);
	}
}

bool SMI::Interpreter::updateState(char word)
{
	bool result = true;

	//deal the situation when state is CMD_START
	if (now_state == CMD_START) {
		switch (word)
		{
		case '!':
			now_state = CMD_MULTI;
			result = true;
			return result;
			break;
		case '/':
			if (stk_state.size() &&  stk_state.top() == CMD_MULTI) {
				now_state = CMD_END;
				result = true;
				return result;
			} else {
				now_state = CMD_SINGLE;
			}
			break;
		default:
			now_state = CMD_SINGLE;
			break;
		}
	}

	if (now_state == TEXT && word == '/') {
		now_state = TEXT_END;
		result = true;
		return result;
	}

	//save state
	stk_state.push(now_state);
	//change the state
	switch (word)
	{
	case '<':
		now_state = CMD_START;
		return result;
		break;
	case '[':
		now_state = NAME;
		return result;
		break;
	case '-':
		if (now_state == CMD_MULTI || now_state == CMD_SINGLE) {
			result = false;
			break;
		}
		if (now_state != LABEL_IN) {
			now_state = LABEL_IN;
			return result;
		} else {
			//resume state
			if (!stk_state.size()) {
				return false;
			}
			stk_state.pop();
			now_state = stk_state.top();
		}
		break;
	case '>':
		//change to CMD_END
		if (!stk_state.size() || stk_state.top() != CMD_SINGLE) {
			return false;
		}
		now_state = CMD_END;
		result = true;
		break;
	case ']':
		//resume state
		if (!stk_state.size()) {
			return false;
		}
		stk_state.pop();
		now_state = stk_state.top();
		break;
	default:
		result = false;
		break;
	}
	stk_state.pop();

	return result;
}

void SMI::Interpreter::cmdAnalysis(string & command)
{
	if (now_state != CMD_MULTI && now_state != CMD_END) {
		return;
	}

	int cut_pos = command.find(':');
	int cut_pos2 = string::npos;
	cmd = command.substr(0, cut_pos);
	string raw_args = command.substr(cut_pos + 1);
	vector<string> arg_array;

	//remove blank
	raw_args = trim(raw_args);

	splitArgs(raw_args, arg_array);

	//init arg_val
	num_args.clear();
	str_args.clear();

	//start
	if (cmd == "flag") {
		str_args.push_back(arg_array[0]);
		if (arg_array.size() == 1) {	// <flag: name>
			flags[raw_args] = 0;
		} else {						// <flag: name, val>
			num_args.push_back(atoi(arg_array[1].c_str()));
			flags[str_args[0]] = num_args[0];
		}
	} else if (cmd == "flag_add") {		// <flag_add: name, val>
		num_args.push_back(atoi(arg_array[1].c_str()));
		str_args.push_back(arg_array[0]);
		if (flags.find(str_args[0]) != flags.end()) {
			flags[str_args[0]] += num_args[0];
		}
	} else if (cmd == "if") {
		str_args.push_back(arg_array[0]);
		switch (arg_array.size())
		{
		case 2:		// <if: name, val>
			num_args.push_back(atoi(arg_array[1].c_str()));
			break;
		case 3:		// <if: name, val1, val2>
			num_args.push_back(atoi(arg_array[1].c_str()));
			num_args.push_back(atoi(arg_array[2].c_str()));
			break;
		default:	// <if: name>
			break;
		} 
	} else if (cmd == "select") {		// <select: opt1, opt2, ...>
		for each (auto var in arg_array) {
			str_args.push_back(var);
		}
	} else {
		str_args.push_back(raw_args);
	}
}

void SMI::Interpreter::cmdOperate()
{
	if (cmd == "") {
		return;
	}

	if (cmd == "if") {

	}
}

void SMI::Interpreter::addLabel()
{
	string label;
	string str;
	size_t pos;

	int result = now_pos + 1;

	do {
		str = buffer[now_pos];
		if (now_state == LABEL_IN) {			//test the state
			label = str.substr(1);
			now_state = LABEL_READING;
			buffer[now_pos].insert(buffer[now_pos].begin(), '#');	//commit the line

			if (str.at(str.length() - 1) == '-') {
				label = label.substr(0, label.length() - 1);
				labels[label] = now_pos;
				now_state = LABEL_EXITING;
			} else {
				++now_pos;
			}
		} else if (now_state == LABEL_READING) {
			pos = str.find('-');		//find the end mark
			if (pos == string::npos) {
				label += str;
				++now_pos;
			} else {				//found
				label += str.substr(0, pos + 1);
				labels[label] = now_pos;
				now_state = LABEL_EXITING;
			}
		}
	} while (now_state != LABEL_EXITING);

	now_state = TEXT;
}

void SMI::Interpreter::scanFile()
{
	now_pos = 0;
	string str;

	//build labels list
	for (now_pos = 0; now_pos < buffer.size(); ++now_pos) {
		str = buffer[now_pos];
		if (str.length() && str.at(0) == '-') {
			now_state = LABEL_IN;
			addLabel();
		}
	}
	now_pos = 0;
}

bool SMI::Interpreter::isKeyword(char word)
{
	return keywords.find(word) != keywords.end();
}

void SMI::Interpreter::splitArgs(string & str, vector<string>& arg_array)
{
	size_t cut_pos = -1;
	size_t cut_pos2 = str.find(',');

	while (cut_pos2 != string::npos) {
		arg_array.push_back(trim(str.substr(cut_pos + 1, cut_pos2 - cut_pos - 1)));
		cut_pos = cut_pos2;
		cut_pos2 = str.find(',', cut_pos + 1);
	}

	arg_array.push_back(trim(str.substr(cut_pos + 1, cut_pos2 - cut_pos - 1)));
}

string& SMI::Interpreter::trim(string & str)
{
	if (str.empty())
	{
		return str;
	}

	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
	return str;
}

void SMI::Interpreter::debug()
{
	for each (auto iter in labels){
		cout << iter.second << endl;
	}
}
