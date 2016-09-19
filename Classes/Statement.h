#pragma once
#include "Sentence.h"
#include "platform/CCPlatformMacros.h"

class Statement :
	public Sentence
{
public:
	Statement();
	~Statement();
	void run();
};

