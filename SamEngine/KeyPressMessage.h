#pragma once
#include "Message.h"
#include <string>

class KeyPressMessage
	: public Message
{
public:
	KeyPressMessage(int key, bool down);
	virtual ~KeyPressMessage();

	int GetKey() const { return _key; }
	bool GetDown() const { return _down; }

protected:
	int _key;
	bool _down;
};

