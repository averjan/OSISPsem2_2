#include <fstream>
#include <regex>

#include "file_reader.h"

using namespace std;

fileTable::fileTable(string fileName)
{
	this->tableData = readFile(fileName);
	this->row_count = this->tableData.size();
	this->column_count = countColumns();
}

int fileTable::countColumns()
{
	int max = -1;
	for (vector<string> v : this->tableData)
	{
		if ((long)v.size() > max) {
			max = v.size();
		}
	}

	return max;
}

vector<vector<string>> fileTable::readFile(string fileName)
{	
	ifstream src(fileName);
	string line;
	vector<vector<string>> table;
	while (getline(src, line))
	{
		regex reg{ R"([\s]+)" };
		sregex_token_iterator it{ line.begin(), line.end(), reg, -1 };
		table.emplace_back(vector<string>{it, {}});
	}

	return table;
}
