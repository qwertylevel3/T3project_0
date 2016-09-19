#pragma once
#include "Sentence.h"
#include <vector>
#include <map>
#include <string>

class Question :
	public Sentence
{
public:
	Question();
	~Question();
	void addOptionMap(int optionIndex,int sentenceIndex);
	void addOption(std::string option);
	void changeOption(int index);
	void run();
protected:
	int optionIndex;
	//选项index到下一句index的映射
	std::map<int, int> optionMap;
	std::vector<std::string> options;
};

