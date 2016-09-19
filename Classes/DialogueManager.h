#pragma once

#include <map>
#include<string>

#include "Singleton.h"
#include"tinyxml2\tinyxml2.h"
#include "Dialogue.h"
#include "base\CCEventKeyboard.h"

class Question;
class Statement;

class DialogueManager:public Singleton<DialogueManager>
{
public:
	DialogueManager();
	~DialogueManager();
	void init();
	void run(const std::string& dialogueName);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	std::map<std::string, Dialogue*> dialogueBox;

	Statement* initStatement(tinyxml2::XMLElement *sentenceElement);
	Question* initQuestion(tinyxml2::XMLElement *sentenceElement);

	std::string getChildElementStrAttr(tinyxml2::XMLElement* element, std::string attrName);
	std::wstring getChildElementWStrAttr(tinyxml2::XMLElement* element, std::string attrName);
	int getChildElementIntAttr(tinyxml2::XMLElement* element, std::string attrName);

	tinyxml2::XMLElement* getChildElement(tinyxml2::XMLElement* parent, std::string name);
};

