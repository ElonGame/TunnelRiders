#include "HighScores.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

std::vector<std::pair<std::string, int>> HighScores::ReadHighScores(const std::string & filePath)
{
	std::vector<std::pair<std::string, int>> highScores;

	// Open File
	std::ifstream file;
	file.open(filePath);

	// Parse File
	std::string line;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			// Ignore comments
			if (line.substr(0, 2) == "//" || line.substr(0, 1) == "#") continue;

			std::string name;
			int score;

			// Get Data
			std::istringstream ss(line);
			ss >> name >> score;
			highScores.push_back(std::pair<std::string, int>(name, score));
		}
		file.close();
	}

	highScores = Sort(highScores);

	return highScores;
}

bool HighScores::WriteHighScores(std::vector<std::pair<std::string, int>> scores, const std::string & filePath)
{
	std::ofstream file;
	file.open(filePath);

	if (file.is_open())
	{
		for (auto pair : scores)
		{
			file << pair.first << " " << pair.second << std::endl;
		}
		file.close();
		return true;
	}
	return false;
}

std::vector<std::pair<std::string, int>> HighScores::Sort(std::vector<std::pair<std::string, int>>& highScores)
{
	std::sort(highScores.begin(), highScores.end(), [](auto &left, auto &right) {
		return left.second > right.second;
	});
	return highScores;
}
