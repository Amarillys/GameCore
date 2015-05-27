#include "../../include/SMLanguage/SMI.h"

using namespace SMI;

SMI::Interpreter::Interpreter()
{
}

SMI::Interpreter::~Interpreter()
{
}

bool SMI::Interpreter::RunOneStep()
{
	bool result = false;
	if (now_pos < all_text.size()) {
		name = "";
		cmd = "";
		text = "";
		while (now_pos < all_text.size() && all_text[now_pos].length() && all_text[now_pos].at(0) == '#') {
			++now_pos;
		}
		if (now_pos < all_text.size()) {
			result = analysisOneLine(all_text[now_pos++]);
			//To do...
		}
	}
	return result;
}

bool SMI::Interpreter::LoadSMO(const char * filename)
{
	file_name = string(filename);
	file.open(file_name, ios::in);
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

		all_text.push_back(str);
	}

	file.close();
	now_state = TEXT;

	//build label list;
	scanFile();
	return true;
}

void SMI::Interpreter::Save(Bundle<SAVE_SIZE> &bundle)
{
	BYTE buffer[SAVE_SIZE];
	size_t size = Serialize(buffer);
	for (int i = 0; i < size; ++i) {
		Write<BYTE>(buffer[i]);
	}
}

void SMI::Interpreter::Load(Bundle<SAVE_SIZE> &bundle)
{
	BYTE buffer[SAVE_SIZE];
	for (int i = 0; i < SAVE_SIZE; ++i) {
		Read<BYTE>(buffer[i]);
	}
	Unserialize(buffer);
}

bool SMI::Interpreter::NextIsText()
{
	return is_text;
}

bool SMI::Interpreter::CmdOver()
{
	return is_end;
}

string SMI::Interpreter::PopCmd()
{
	return cmd;
}

void SMI::Interpreter::PopArg(vector<string> &arr)
{
	arr = str_args;
}

void SMI::Interpreter::PopIntArg(vector<int> &arr)
{
	arr = num_args;
}

void SMI::Interpreter::PopFlags(unordered_map<string, int>& &arr)
{
	arr = flags;
}

string SMI::Interpreter::PopText()
{
	return text;
}

string SMI::Interpreter::PopName()
{
	return name;
}

bool SMI::Interpreter::Goto(string& label)
{
	auto iter = labels.find(label);
	bool result = iter != labels.end();
	if (result) {
		now_pos = iter->second;
		if (now_state != CMD_END) {
			now_state = TEXT;
			while (stk_state.size()) {
				stk_state.pop();
			}
		}
	}
	return result;
}

bool SMI::Interpreter::OutStack()
{
	bool result = now_state == CMD_MULTI;
	int floor = 0;

	if (result) {
		int pos = now_pos;
		while (pos < all_text.size()) {
			if (all_text[pos] == "<!>" || all_text[pos].find("if") != string::npos) {
				++floor;
			}

			if (all_text[pos] == "<\\>" || all_text[pos] == "\\") {
				if (floor) {
					--floor;
				} else {
					now_state = stk_state.top();
					num_args.clear();
					str_args.clear();
					stk_state.pop();
					break;
				}
			}
			++pos;
		}
		result = pos != now_pos;
		now_pos = pos + 1;
	}

	return result;
}

size_t SMI::Interpreter::Serialize(BYTE *buffer)
{
	BYTE *p = buffer;

	*(int*)p = file_name.length();
	p += sizeof(int);
	file_name.copy((char*)p, file_name.length());
	p += sizeof(char) * file_name.length();

	*(state*)p = now_state;
	p += sizeof(state);

	*(int*)p = stk_state.size();
	p += sizeof(int);
	stack<state> stk_temp;
	while (stk_state.size()) {
		stk_temp.push(stk_state.top());
		stk_state.pop();
	}
	while (stk_temp.size()) {
		*(state*)p = stk_temp.top();
		stk_state.push(stk_temp.top());
		p += sizeof(state);
		stk_temp.pop();
	}

	*(int*)p = keywords.size();
	p += sizeof(int);
	for each (auto var in keywords) {
		*p++ = var;
	}

	*(int*)p = labels.size();
	p += sizeof(int);
	for each (auto var in labels) {
		*(int*)p = var.first.length();
		p += sizeof(int);
		var.first.copy((char*)p, var.first.length());
		p += sizeof(char) * var.first.length();

		*(int*)p = var.second;
		p += sizeof(int);
	}

	*(int*)p = flags.size();
	p += sizeof(int);
	for each (auto var in flags) {
		*(int*)p = var.first.length();
		p += sizeof(int);
		var.first.copy((char*)p, var.first.length());
		p += sizeof(char) * var.first.length();

		*(int*)p = var.second;
		p += sizeof(int);
	}

	*p++ = is_text;
	*p++ = is_end;

	*(int*)p = cmd.length();
	p += sizeof(int);
	cmd.copy((char*)p, cmd.length());
	p += sizeof(char) * cmd.length();

	*(int*)p = str_args.size();
	p += sizeof(int);
	for each (auto var in str_args){
		*(int*)p = var.length();
		p += sizeof(int);
		var.copy((char*)p, var.length());
		p += sizeof(char) * var.length();
	}

	*(int*)p = num_args.size();
	p += sizeof(int);
	for each (auto var in num_args) {
		*(int*)p = var;
		p += sizeof(int);
	}

	*(int*)p = text.length();
	p += sizeof(int);
	text.copy((char*)p, text.length());
	p += sizeof(char) * text.length();

	*(int*)p = name.length();
	p += sizeof(int);
	name.copy((char*)p, name.length());
	p += sizeof(char) * name.length();

	*(int*)p = all_text.size();
	p += sizeof(int);
	for each (auto var in all_text) {
		*(int*)p = var.length();
		p += sizeof(int);
		var.copy((char*)p, var.length());
		p += sizeof(char) * var.length();
	}

	*(int*)p++ = now_pos;

	return p - buffer;
}

void SMI::Interpreter::Unserialize(BYTE *buffer)
{
	BYTE *p = buffer;
	int len = 0;
	int arr_len = 0;
	string str_temp = "";
	int num_temp = 0;

	len = *(int*)p;
	p += sizeof(int);
	file_name = "";
	for (int i = 0; i < len; ++i) {
		file_name += (char)*p++;
	}
	file = ifstream(file_name);

	now_state = *(state*)p;
	p += sizeof(state);

	len = *(int*)p;
	p += sizeof(int);
	for (int i = 0; i < len; ++i) {
		stk_state.push(*(state*)p);
		p += sizeof(state);
	}

	len = *(int*)p;
	p += sizeof(int);
	for (int i = 0; i < len; ++i) {
		keywords.insert(*p++);
	}

	arr_len = *(int*)p;
	p += sizeof(int);
	for (int i = 0; i < arr_len; ++i) {
		len = *(int*)p;
		p += sizeof(int);
		str_temp = "";
		for (int i = 0; i < len; ++i) {
			str_temp += (char)*p++;
		}
		num_temp = *(int*)p;
		p += sizeof(int);

		labels[str_temp] = num_temp;
	}

	arr_len = *(int*)p;
	p += sizeof(int);
	for (int i = 0; i < arr_len; ++i) {
		len = *(int*)p;
		p += sizeof(int);
		str_temp = "";
		for (int i = 0; i < len; ++i) {
			str_temp += (char)*p++;
		}
		num_temp = *(int*)p;
		p += sizeof(int);

		flags[str_temp] = num_temp;
	}

	is_text = *p++;
	is_end = *p++;

	len = *(int*)p;
	p += sizeof(int);
	cmd = "";
	for (int i = 0; i < len; ++i) {
		cmd += (char)*p++;
	}

	arr_len = *(int*)p;
	p += sizeof(int);
	for (int i = 0; i < arr_len; ++i) {
		len = *(int*)p;
		p += sizeof(int);
		str_temp = "";
		for (int i = 0; i < len; ++i) {
			str_temp += (char)*p++;
		}

		str_args.push_back(str_temp);
	}

	arr_len = *(int*)p;
	p += sizeof(int);
	for (int i = 0; i < arr_len; ++i) {
		num_temp = *(int*)p;
		p += sizeof(int);

		num_args.push_back(num_temp);
	}

	len = *(int*)p;
	p += sizeof(int);
	text = "";
	for (int i = 0; i < len; ++i) {
		text += (char)*p++;
	}

	len = *(int*)p;
	p += sizeof(int);
	name = "";
	for (int i = 0; i < len; ++i) {
		name += (char)*p++;
	}

	arr_len = *(int*)p;
	p += sizeof(int);
	for (int i = 0; i < arr_len; ++i) {
		len = *(int*)p;
		p += sizeof(int);
		str_temp = "";
		for (int i = 0; i < len; ++i) {
			str_temp += (char)*p++;
		}

		all_text.push_back(str_temp);
	}

	now_pos = *(int*)p;
}

bool SMI::Interpreter::analysisOneLine(string & line)
{
	bool result = false;
	is_text = false;
	static string command = "";

	for (auto iter = line.begin(); iter != line.end(); ++iter) {
		if (*iter == '#') {
			break;
		}
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
		command = "";
	}

	return true;
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
		case '\\':
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

	if (word == '\\') {
		if (now_state == TEXT) {
			now_state = TEXT_END;
			result = true;
			return result;
		} else if (now_state == CMD_MULTI && stk_state.top() == CMD_MULTI) {
			now_state = CMD_END;
			result = true;
		}
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
			num_args.push_back(0);
		}
		else {						// <flag: name, val>
			num_args.push_back(atoi(arg_array[1].c_str()));
		}
	} else if (cmd == "flag_add") {		// <flag_add: name, val>
		num_args.push_back(atoi(arg_array[1].c_str()));
		str_args.push_back(arg_array[0]);

	} else if (cmd == "flag_del") {		// <flag_del: name>
		str_args.push_back(arg_array[0]);
	} else if (cmd == "goto") {		// <goto: name>
		str_args.push_back(arg_array[0]);
	} else if (cmd == "if") {
		str_args.push_back(arg_array[0]);
		for (auto iter = arg_array.begin() + 1; iter != arg_array.end(); ++iter) {
			num_args.push_back(atoi((*iter).c_str()));
		}
	} else if (cmd == "select") {		// <select: opt1, opt2, ...>
		for each (auto var in arg_array) {
			str_args.push_back(var);
		}
	} else {
		str_args.push_back(raw_args);
	}
	cmdOperate();
}

void SMI::Interpreter::cmdOperate()
{
	if (cmd == "flag") {
		flags[str_args[0]] = num_args[0];
	} else if (cmd == "end") {
		is_end = true;
	} else if (cmd == "flag_add") {		// <flag_add: name, val>
		if (flags.find(str_args[0]) != flags.end()) {
			flags[str_args[0]] += num_args[0];
		}
	} else if (cmd == "flag_del") {		// <flag_del: name>
		flags.erase(str_args[0]);
	} else if (cmd == "goto") {		// <goto: name>
		Goto(str_args[0]);
	} else if (cmd == "if") {
		bool test_result = false;
		switch (num_args.size()) {
		case 0:
			test_result = flags.find(str_args[0]) != flags.end();
			break;
		case 1:
			if (flags.find(str_args[0]) != flags.end()) {
				test_result = flags[str_args[0]] == num_args[0];
			}
			break;
		case 2:
			if (flags.find(str_args[0]) != flags.end()) {
				test_result = (flags[str_args[0]] >= num_args[0] && flags[str_args[0]] < num_args[1]);
			}
			break;
		default:
			break;
		}
		//Todo
		stk_state.push(CMD_MULTI);
		
		if (!test_result) {
			OutStack();
		}
	}
}

void SMI::Interpreter::addLabel()
{
	string label;
	string str;
	size_t pos;

	int result = now_pos + 1;

	do {
		str = all_text[now_pos];
		if (now_state == LABEL_IN) {			//test the state
			label = str.substr(1);
			now_state = LABEL_READING;
			all_text[now_pos].insert(all_text[now_pos].begin(), '#');	//commit the line

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
	for (now_pos = 0; now_pos < all_text.size(); ++now_pos) {
		str = all_text[now_pos];
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
	str.erase(0, str.find_first_not_of('\t'));
	str.erase(str.find_last_not_of('\t') + 1);
	return str;
}

void SMI::Interpreter::debug()
{
	for each (auto iter in labels){
		cout << iter.second << endl;
	}
}
