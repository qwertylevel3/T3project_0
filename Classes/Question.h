#pragma once
#include "Sentence.h"

class Question :
	public Sentence
{
public:
	Question();
	~Question();
	int run();
};

