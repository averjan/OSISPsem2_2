#pragma once

#include <string>
#include <vector>

using namespace std;

class FileTable
{
private:
	vector<vector<string>> readFile(string fileName);
	int countColumns();
public:
	int row_count;
	int column_count;
	vector<vector<string>> tableData;
	FileTable(string fileName);
};
