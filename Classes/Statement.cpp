#include "Statement.h"
#include "DialogueDriver.h"



Statement::Statement()
{
}

Statement::~Statement()
{
}

void Statement::run()
{
	DialogueDriver::getInstance()->run(this);
}
