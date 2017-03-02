#pragma once
#include <vector>

class HighScores
{
public:
	static std::vector<std::pair<std::string, int>> ReadHighScores(const std::string &filePath);
	static bool WriteHighScores(std::vector<std::pair<std::string, int>> scores, const std::string &filePath);

	static std::vector<std::pair<std::string, int>> Sort(std::vector<std::pair<std::string, int>>&);


private:
	HighScores() {}
};

