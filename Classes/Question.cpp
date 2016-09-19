#include "Question.h"
#include "DialogueDriver.h"



Question::Question()
{
	curIndex = 0;
}


Question::~Question()
{
}

void Question::addOptionMap(int optionIndex, int sentenceIndex)
{
	optionMap[optionIndex] = sentenceIndex;
}

void Question::addOption(std::string option)
{
	options.push_back(option);
}

void Question::changeOption(int index)
{
	curIndex = index;
	nextIndex = optionMap[curIndex];
}

void Question::run()
{
	DialogueDriver::getInstance()->run(this);
}

std::vector<std::string>& Question::getAllOption()
{
	return options;
}

int Question::getSize()
{
	return options.size();
}
