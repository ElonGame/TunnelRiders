#pragma once
#include <map>
#include <string>
#include <vector>

class Message;
class Observer;

typedef std::map<std::string, std::vector<Observer*> > MessageListenerMap;
typedef std::map<std::string, std::vector<Observer*> >::iterator MessageListenerMapIterator;
typedef std::vector<Observer*>::iterator ObserverListIterator;

class ObserverSubject
{
public:
	ObserverSubject() {}
	virtual ~ObserverSubject() {}

	// Register an observer for a particular type of message
	void RegisterListener(std::string msg, Observer* o);

	// De-register an observer
	void UnregisterListener(std::string msg, Observer* o);

	// Broadcast a message to any listeners
	void BroadcastMessage(Message* m);

protected:
	// Listener registration
	MessageListenerMap	_messageListeners;
};

