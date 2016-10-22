#pragma once

#include <map>
#include<string>

#include "Singleton.h"
#include "Dialogue.h"
#include "base\CCEventKeyboard.h"
#include "XMLConfigure.h"

class Question;
class Statement;

class DialogueFactory:public XMLConfigure,public Singleton<DialogueFactory>
{
public:
	DialogueFactory();
	~DialogueFactory();
	void init();
	Dialogue* getDialogue(const std::string& dialogueName);
protected:
	std::map<std::string, Dialogue*> dialogueBox;

	Statement* initStatement(tinyxml2::XMLElement *sentenceElement);
	Question* initQuestion(tinyxml2::XMLElement *sentenceElement);
};

