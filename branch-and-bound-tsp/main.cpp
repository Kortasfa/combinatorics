#include "../BranchAndBound4/BranchAndBound.h"
using namespace std;
const int INITIAL_BORDER_VALUE = 0;

int main()
{
	vector<vector<int>> matrix = {
		{ INT_MAX, 1, 2 },
		{ 4, INT_MAX, 3 },
		{ 5, 6, INT_MAX }
	};

	int minBorder = INT_MAX;
	vector<pair<int, int>> minPath;
	vector<pair<int, int>> path;
	BranchAndBound(matrix, path, minPath, INITIAL_BORDER_VALUE, minBorder);

	for (auto edge : minPath)
	{
		cout << edge.first << " -> " << edge.second << endl;
	}
	int length = findMinPath(matrix, minPath);
	cout << "Min length: " << length << endl;

	return 1;
}