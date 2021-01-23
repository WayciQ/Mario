#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#define SCENE_SECTION_UNKNOWN -1
#define MAX_SCENE_LINE 1024
#define SCENE_SECTION_OBJECTS	1
#define SCENE_FILE_SECTION_SETTINGS	2	
#define SIZE_CELL  11
#define COLS_MAP 161
#define ROWS_MAP 12
int SizeCell = 0;
//int cols = (int(COLS_MAP / SIZE_CELL));
//int rows = (int(ROWS_MAP / SIZE_CELL)) + 1;
int cols = 0;
int rows = 0;
void GetCell(int x, int y, int& l, int& t, int& r, int& b, int w = 1, int h = 1) {
	int ri = int((x + w - 1) / SIZE_CELL);
	int bo = int((y + h - 1) / SIZE_CELL);
	t = int(max(0, y / SIZE_CELL));
	l = int(max(0, x / SIZE_CELL));
	r = int(min(cols - 1,ri ));
	b = int(min(rows - 1, bo));
}
vector<string> split(string line, string delimeter = "\t")
{
	vector<string> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != string::npos)
	{
		tokens.push_back(line.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(line.substr(last));

	return tokens;
}
void _ParseSection_OBJECTS(string line, ofstream& ofs) {
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	int object_TAG = atoi(tokens[0].c_str());
	int tag = static_cast<int>(object_TAG);
	int object_TYPE = atof(tokens[3].c_str());
	int type = static_cast<int>(object_TYPE);
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int left, top, right, bot;

	switch (tag)
	{
	case 4:
		switch (type)
		{
		case 11:
			GetCell(x, y, left, top, right, bot, (int)atof(tokens[4].c_str()), (int)atof(tokens[5].c_str()));
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << (float)atof(tokens[4].c_str()) << "\t" << (float)atof(tokens[5].c_str()) << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		case 5:
			GetCell(x, y, left, top, right, bot);
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << (float)atof(tokens[4].c_str()) << "\t" << (float)atof(tokens[5].c_str()) << "\t" << (float)atof(tokens[6].c_str()) << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		case 7:
			GetCell(x, y, left, top, right, bot);
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		case 9:
			GetCell(x, y, left, top, right, bot, (int)atof(tokens[4].c_str()), (int)atof(tokens[5].c_str()));
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << (float)atof(tokens[4].c_str()) << "\t" << (float)atof(tokens[5].c_str()) << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		}
		break;
	case 1:
		if (type == 17 || type == 18) {
			GetCell(x, y, left, top, right, bot);
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << (float)atof(tokens[4].c_str()) << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		}
		else {
			GetCell(x, y, left, top, right, bot);
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		}
		
	case 3:
		GetCell(x, y, left, top, right, bot);
		ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
		break;
	case 5:
		switch (type)
		{
		case 33:
		{
			GetCell(x, y, left, top, right, bot);
			ofs << tag << "\t";
			ofs << x << "\t"; 
			ofs << y << "\t"; 
			ofs << type << "\t";
			ofs << (float)atof(tokens[4].c_str()) << "\t";
			ofs << (int)atof(tokens[5].c_str()) << "\t";
			ofs << (int)atof(tokens[6].c_str()) << "\t";
			ofs << (int)atof(tokens[7].c_str()) << "\t";
			ofs << (int)atof(tokens[8].c_str()) << "\t";
			ofs << (int)atof(tokens[9].c_str()) << "\t";
			ofs << (int)atof(tokens[10].c_str()) << "\t";
			ofs << (int)atof(tokens[11].c_str()) << "\t";
			ofs << (int)atof(tokens[12].c_str()) << "\t";
			ofs << (int)atof(tokens[13].c_str()) << "\t";
			ofs << (int)atof(tokens[14].c_str()) << "\t";
			ofs << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		}
		case 34:
		{
			GetCell(x, y, left, top, right, bot);
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << (float)atof(tokens[4].c_str()) << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		}
		case 35:
		{
			GetCell(x, y, left, top, right, bot);
			ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
			break;
		}
		}
		break;
	case 6:
		GetCell(x, y, left, top, right, bot);
		ofs << tag << "\t" << x << "\t" << y << "\t" << type << "\t" << left << "\t" << top << "\t" << right << "\t" << bot;
		break;
	default:
		return;
	}
	
	ofs << "\n";
}

void _ParseSection_SETTINGS(string line, ofstream& ofs) {
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return;

	SizeCell = int(atoi(tokens[0].c_str()));
	cols = (int(atoi(tokens[1].c_str())) / SizeCell);
	rows = (int(atoi(tokens[2].c_str())) / SizeCell) + 1;
	
	ofs << "\nSize: " << SIZE_CELL << "\nCols: " << cols << "\nRows: " << rows << "\n";
}

int main()
{
	ifstream fs;
	ofstream ofs;
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	ofs.open("output.txt", ios::out);
	fs.open("input.txt");
	int id = 0;
	if (fs.fail())
	{
		cout << "Load file scene fail";
	}
	else
	{
		cout << "Load File Thanh cong";
		char str[MAX_SCENE_LINE];
		
		while (fs.getline(str, MAX_SCENE_LINE))
		{
			string line(str);

			if (line[0] == '#') continue;	// skip comment lines	
			if (line == "[SETTINGS]") {
				ofs << "[GRID]" << "\n";
				section = SCENE_FILE_SECTION_SETTINGS; continue;
			}
			if (line == "[OBJECTS]") {
				ofs << "[OBJECTS]" << "\n";
				section = SCENE_SECTION_OBJECTS; continue;
			}

			if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }
			//
			// data section
			//
			switch (section)
			{
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line, ofs); break;
			case SCENE_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line, ofs); break;
			}
		}
		
	}
	fs.close();
	ofs.close();
	return 0;
}

