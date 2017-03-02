#pragma once
#include <string>

class Message
{
public:
	Message(std::string type);
	virtual ~Message();

	std::string GetMessageType() const { return _type; }

protected:
	std::string _type;

};