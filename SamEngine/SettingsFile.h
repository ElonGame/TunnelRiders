#pragma once
#include <fstream>
#include <map>
#include <string>

class SettingsFile
{
public:
	static SettingsFile& Instance()
	{
		static SettingsFile instance;
		return instance;
	}
	void parseFile(const std::string& filePath);
	void SetValue(const std::string& key, const std::string& value);
	std::string GetValue(const std::string& key);

private:
	SettingsFile() {};
	SettingsFile(const SettingsFile&);
	SettingsFile& operator=(const SettingsFile&);
	std::map<std::string, std::string> storedConfig;
};