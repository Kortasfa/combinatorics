#pragma once
#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

void BranchAndBound(
	std::vector<std::vector<int>>& matrix,
	std::vector<std::pair<int, int>>& edges,
	std::vector<std::pair<int, int>>& minEdges,
	int border,
	int& minBorder);

inline int findMinPath(std::vector<std::vector<int>>& matrix, std::vector<std::pair<int, int>>& edges)
{
	int path = 0;
	for (auto edge : edges)
	{
		path += matrix[edge.first][edge.second];
	}
	return path;
}