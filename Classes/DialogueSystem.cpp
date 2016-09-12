#include "DialogueSystem.h"
#include "Statement.h"
#include "ToolFunction.h"
#include "DialogueDriver.h"
#include "HudMenuSystem.h"
#include "HudStateSystem.h"
#include "KeyController.h"

USING_NS_CC;


DialogueSystem::DialogueSystem()
{
}


DialogueSystem::~DialogueSystem()
{
}

void DialogueSystem::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("dialogue.xml");
	
	tinyxml2::XMLElement *dialogueBoxElement = doc.RootElement();
	tinyxml2::XMLElement *dialogueElement = dialogueBoxElement->FirstChildElement("dialogue");

	while (dialogueElement)
	{
		Dialogue* dialogue = new Dialogue();
		dialogue->setName(getChildElementStrAttr(dialogueElement, "name"));
		
		tinyxml2::XMLElement *sentenceElement = getChildElement(dialogueElement, "sentence");
		while (sentenceElement)
		{
			Statement* sentence = new Statement();

			sentence->setActorSpriteName(getChildElementStrAttr(sentenceElement, "actorName"));
			sentence->setWord(getChildElementStrAttr(sentenceElement, "word"));
			sentence->setNextIndex(getChildElementIntAttr(sentenceElement, "next"));

			dialogue->addSentence(sentence);

			sentenceElement = sentenceElement->NextSiblingElement();
		}
		dialogueBox[dialogue->getName()] = dialogue;

		dialogueElement = dialogueBoxElement->NextSiblingElement();
	}

	DialogueDriver::getInstance()->init();
}

void DialogueSystem::run(const std::string& dialogueName)
{
	KeyController::getInstance()->switchCtrlToDialog();

	DialogueDriver::getInstance()->startDialogue(dialogueBox[dialogueName]);
}

void DialogueSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	DialogueDriver::getInstance()->handleKeyPressed(keyCode);
}

std::string DialogueSystem::getChildElementStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return childElement->GetText();
}

std::wstring DialogueSystem::getChildElementWStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	std::string temp=childElement->GetText();
	return ToolFunction::string2wstring(childElement->GetText());
}

int DialogueSystem::getChildElementIntAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return ToolFunction::string2int(childElement->GetText());
}

tinyxml2::XMLElement* DialogueSystem::getChildElement(tinyxml2::XMLElement* parent, std::string name)
{
	tinyxml2::XMLElement* element = parent->FirstChildElement(name.c_str());
	CCAssert(element, (std::string("unknow element type ") + name).c_str());
	return element;
}

