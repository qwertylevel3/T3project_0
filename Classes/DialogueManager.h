#pragma once

#include <map>
#include<string>

#include "Singleton.h"
#include "Dialogue.h"
#include "base\CCEventKeyboard.h"
#include "BaseManager.h"

class Question;
class Statement;

class DialogueManager:public BaseManager,public Singleton<DialogueManager>
{
public:
	DialogueManager();
	~DialogueManager();
	void init();
	Dialogue* getDialogue(const std::string& dialogueName);
protected:
	std::map<std::string, Dialogue*> dialogueBox;

	Statement* initStatement(tinyxml2::XMLElement *sentenceElement);
	Question* initQuestion(tinyxml2::XMLElement *sentenceElement);
};

