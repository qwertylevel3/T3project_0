#include "DialogueSystem.h"
#include "HudMessageBox.h"
#include "DialogueDriver.h"
#include "DialogueFactory.h"
#include "KeyController.h"



DialogueSystem::DialogueSystem()
{
}


DialogueSystem::~DialogueSystem()
{
}

void DialogueSystem::init()
{
	DialogueFactory::getInstance()->init();
	DialogueDriver::getInstance()->init();
}

void DialogueSystem::runDialogue(const std::string& dialogueName,Character* actor)
{
	KeyController::getInstance()->switchCtrlToDialog();
	HudMessageBox::getInstance()->hide();
	if (actor)
	{
		setCurActor(actor);
	}
	else
	{
		setCurActor(nullptr);
	}
	Dialogue* dialogue = DialogueFactory::getInstance()->getDialogue(dialogueName);
	DialogueDriver::getInstance()->startDialogue(dialogue);
}

void DialogueSystem::setCurActor(Character* actor)
{
	DialogueDriver::getInstance()->setCurActor(actor);
}

void DialogueSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	DialogueDriver::getInstance()->handleKeyPressed(keyCode);
}
