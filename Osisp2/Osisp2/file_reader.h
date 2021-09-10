#pragma once

#include <string>
#include <vector>

using namespace std;

class fileTable
{
private:
	vector<vector<string>> readFile(string fileName);
	int countColumns();
public:
	int row_count;
	int column_count;
	vector<vector<string>> tableData;
	fileTable(string fileName);
};
