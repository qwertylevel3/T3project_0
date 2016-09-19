#include "Question.h"
#include "DialogueDriver.h"



Question::Question()
{
	optionIndex = 0;
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
	optionIndex = index;
	nextIndex = optionMap[optionIndex];
}

void Question::run()
{
	DialogueDriver::getInstance()->run(this);
}
