#include "DialogueSystem.h"
#include "DialogueDriver.h"
#include "DialogueManager.h"
#include "KeyController.h"



DialogueSystem::DialogueSystem()
{
}


DialogueSystem::~DialogueSystem()
{
}

void DialogueSystem::init()
{
	DialogueManager::getInstance()->init();
	DialogueDriver::getInstance()->init();
}

void DialogueSystem::runDialogue(const std::string& dialogueName)
{
	KeyController::getInstance()->switchCtrlToDialog();

	Dialogue* dialogue = DialogueManager::getInstance()->getDialogue(dialogueName);
	DialogueDriver::getInstance()->startDialogue(dialogue);
}

void DialogueSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	DialogueDriver::getInstance()->handleKeyPressed(keyCode);
}
