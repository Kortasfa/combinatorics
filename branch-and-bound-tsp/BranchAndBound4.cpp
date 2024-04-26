#include "../BranchAndBound4/BranchAndBound.h"
using namespace std;

pair<vector<int>, vector<int>> CalculatePenalties(vector<vector<int>>& matrix, int& lowerBound)
{
	int n = matrix.size();
	vector<int> rowPenalty(n);
	vector<int> columnPenalty(n);

	for (int i = 0; i < n; ++i)
	{
		int min_val = INT_MAX;
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] < min_val)
			{
				min_val = matrix[i][j];
			}
		}
		if (min_val != INT_MAX && min_val >= 0)
		{
			rowPenalty[i] = min_val;
			lowerBound += min_val;
			for (int j = 0; j < n; ++j)
			{
				if (matrix[i][j] != INT_MAX)
				{
					matrix[i][j] -= min_val;
				}
			}
		}
	}

	for (int j = 0; j < n; ++j)
	{
		int min_val = INT_MAX;
		for (int i = 0; i < n; ++i)
		{
			if (matrix[i][j] < min_val)
			{
				min_val = matrix[i][j];
			}
		}
		if (min_val != INT_MAX && min_val >= 0)
		{
			columnPenalty[j] = min_val;
			lowerBound += min_val;
			for (int i = 0; i < n; ++i)
			{
				if (matrix[i][j] != INT_MAX)
				{
					matrix[i][j] -= min_val;
				}
			}
		}
	}

	return { rowPenalty, columnPenalty };
}

pair<int, int> FindMaxPenaltyPoint(const vector<vector<int>>& matrix, const vector<int>& rowPenalty, const vector<int>& columnPenalty)
{
	int n = matrix.size();
	int maxPenalty = INT_MIN;
	pair<int, int> maxPenaltyPoint;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] == 0)
			{
				if (rowPenalty[i] + columnPenalty[j] > maxPenalty)
				{
					maxPenaltyPoint = { i, j };
					maxPenalty = rowPenalty[i] + columnPenalty[j];
				}
			}
		}
	}

	return maxPenaltyPoint;
}

pair<int, int> ReduceMatrix(vector<vector<int>>& matrix, int& lowerBound)
{
	vector<int> rowPenalty;
	vector<int> columnPenalty;

	tie(rowPenalty, columnPenalty) = CalculatePenalties(matrix, lowerBound);

	return FindMaxPenaltyPoint(matrix, rowPenalty, columnPenalty);
}

void RemoveEdge(vector<vector<int>>& matrix, pair<int, int> indexes)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		matrix[indexes.first][i] = INT_MAX;
		matrix[i][indexes.second] = INT_MAX;
	}
}

void BranchAndBound(
	vector<vector<int>>& matrix,
	vector<pair<int, int>>& edges,
	vector<pair<int, int>>& minEdges,
	int border,
	int& minBorder)
{
	if (edges.size() == matrix.size() && border < minBorder)
	{
		minBorder = border;
		minEdges = edges;
		return;
	}

	int newBorder = border;
	vector<vector<int>> newMatrix = matrix;

	pair<int, int> edgeIndex = ReduceMatrix(newMatrix, newBorder);

	if (matrix[edgeIndex.first][edgeIndex.second] == INT_MAX)
	{
		return;
	}

	int borderToPass = newBorder + matrix[edgeIndex.first][edgeIndex.second];
	vector<pair<int, int>> newEdges = edges; // Choose
	vector<pair<int, int>> oldEdges = edges; // Not choose
	vector<vector<int>> matrixWithEdge = newMatrix; // Choose
	vector<vector<int>> matrixWithoutEdge = newMatrix; // Not choose
	newEdges.push_back(edgeIndex);

	RemoveEdge(matrixWithEdge, edgeIndex); // Choose
	BranchAndBound(matrixWithEdge, newEdges, minEdges, borderToPass, minBorder);

	matrixWithoutEdge[edgeIndex.first][edgeIndex.second] = INT_MAX; // Not Choose
	BranchAndBound(matrixWithoutEdge, oldEdges, minEdges, borderToPass, minBorder);
}