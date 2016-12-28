#include "DialogueFactory.h"
#include "Statement.h"
#include "Question.h"
#include "ToolFunction.h"
#include "DialogueDriver.h"
#include "HudMenuSystem.h"
#include "HudPlayerStateMenu.h"
#include "KeyController.h"

USING_NS_CC;

DialogueFactory::DialogueFactory()
{
}

DialogueFactory::~DialogueFactory()
{
}

void DialogueFactory::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("dialogue.xml");

	tinyxml2::XMLElement *dialogueBoxElement = doc.RootElement();
	tinyxml2::XMLElement *dialogueElement = dialogueBoxElement->FirstChildElement("dialogue");

	while (dialogueElement)
	{
		Dialogue* dialogue = new Dialogue();
		dialogue->setName(getChildElementStrAttr(dialogueElement, "name"));

		Statement* sentence = new Statement();

		sentence->setActorSpriteName("null");
		sentence->setWord("error");
		sentence->setNextIndex(-1);

		dialogue->addSentence(sentence);

		tinyxml2::XMLElement *sentenceElement = getChildElement(dialogueElement, "sentence");
		while (sentenceElement)
		{
			Sentence* sentence;
			std::string type = getChildElementStrAttr(sentenceElement, "type");
			if (type == "statement")
			{
				sentence = initStatement(sentenceElement);
			}
			else if (type == "question")
			{
				sentence = initQuestion(sentenceElement);
			}
			dialogue->addSentence(sentence);

			sentenceElement = sentenceElement->NextSiblingElement();
		}
		dialogueBox[dialogue->getName()] = dialogue;

		dialogueElement = dialogueElement->NextSiblingElement();
	}
}

Dialogue* DialogueFactory::getDialogue(const std::string& dialogueName)
{
	return dialogueBox[dialogueName];
}

Statement* DialogueFactory::initStatement(tinyxml2::XMLElement *sentenceElement)
{
	Statement* sentence = new Statement();

	sentence->setActorSpriteName(getChildElementStrAttr(sentenceElement, "actorName"));
	sentence->setWord(getChildElementStrAttr(sentenceElement, "word"));
	sentence->setNextIndex(getChildElementIntAttr(sentenceElement, "next"));

	return sentence;
}

Question* DialogueFactory::initQuestion(tinyxml2::XMLElement *sentenceElement)
{
	Question* sentence = new Question();

	sentence->setActorSpriteName(getChildElementStrAttr(sentenceElement, "actorName"));
	sentence->setWord(getChildElementStrAttr(sentenceElement, "word"));

	tinyxml2::XMLElement* optionListElement = getChildElement(sentenceElement, "optionList");

	tinyxml2::XMLElement* option = getChildElement(optionListElement, "option");
	int count = 0;
	while (option)
	{
		sentence->addOption(getChildElementStrAttr(option, "label"));
		sentence->addOptionMap(count, getChildElementIntAttr(option, "next"));

		option = option->NextSiblingElement();
		count++;
	}
	return sentence;
}