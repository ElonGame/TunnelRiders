#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "SettingsFile.h"

void SettingsFile::parseFile(const std::string& filePath)
{
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

			std::string key;
			std::string value;

			// Get Data
			std::istringstream ss(line);
			ss >> key >> value;
			storedConfig[key] = value;
		}
		file.close();
	}
}

std::string SettingsFile::GetValue(const std::string& key)
{
	// Found
	std::map<std::string, std::string>::iterator i = storedConfig.find(key);
	if (i != storedConfig.end())
	{
		return i->second;
	}
	// Not found
	return "";
}

void SettingsFile::SetValue(const std::string & key, const std::string & value)
{
	storedConfig[key] = value;
}
