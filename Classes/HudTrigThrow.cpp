#include "HudTrigThrow.h"
#include "HudMenuItem.h"
#include "Player.h"
#include "InventoryFactory.h"
#include "HudInventoryMenu.h"
#include "InventoryHandler.h"
#include "Dungeon.h"
#include "Inventory.h"
#include "StoreyInventoryHandler.h"
#include "MainLayer.h"
#include "2d/CCAnimation.h"



HudTrigThrow::HudTrigThrow()
{

}


HudTrigThrow::~HudTrigThrow()
{
}

void HudTrigThrow::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	std::string inventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	characterPtr->removeInventory(inventoryName);

	cocos2d::Point targetCoord = getTarget();
	Character* targetCharacter = Field::Dungeon::getInstance()->getCharacter(targetCoord);

	//todo : refactor
	//////////////////////////////////////////////////////////////////////////
	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryName);

	showEffect(inventory,targetCoord);
	//////////////////////////////////////////////////////////////////////////

	characterPtr->processAction(0.1);
	menuItem->getParentMenu()->closeMenu();
}

cocos2d::Point HudTrigThrow::getTarget()
{
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	cocos2d::Point offset(0, 0);
	switch (characterPrt->getOrientation())
	{
	case Character::Orientation::UP:
		offset.y--;
		break;
	case Character::Orientation::DOWN:
		offset.y++;
		break;
	case Character::Orientation::LEFT:
		offset.x--;
		break;
	case Character::Orientation::RIGHT:
		offset.x++;
		break;
	}

	cocos2d::Point targetCoord = characterPrt->getMapCoord();
	int lenCount = 0;
	const int maxLength = 5;
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	while (lenCount != maxLength)
	{
		targetCoord += offset;
		Character* target = storey->getCharacter(targetCoord);
		if (target)
		{
			return targetCoord;
		}
		if (!storey->isMoveAble(targetCoord))
		{
			return targetCoord - offset;
		}
		lenCount++;
	}
	return targetCoord;
}

void HudTrigThrow::showEffect(Inventory* inventory,cocos2d::Point targetCoord)
{
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriPosition = characterPrt->getPosition();
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);

	cocos2d::Sprite* inventorySprite = cocos2d::Sprite::create("sys/inventory.png");
	inventorySprite->setPosition(oriPosition);
	MainLayer::getInstance()->addChild(inventorySprite, 15);
	cocos2d::ActionInterval* moveAction = cocos2d::CCMoveTo::create(0.1, cocos2d::Vec2(targetPosition));
//	inventorySprite->runAction(moveAction);
//	inventorySprite->removeFromParent();
	inventorySprite->runAction(cocos2d::Sequence::create(moveAction, 
		cocos2d::CallFunc::create(CC_CALLBACK_0(HudTrigThrow::throwResult,this,inventory,targetCoord)),
		cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, inventorySprite)), NULL));
}


void HudTrigThrow::throwResult(Inventory* inventory,cocos2d::Point targetCoord)
{
	Character* targetCharacter = Field::Dungeon::getInstance()->getCharacter(targetCoord);

	//hit！
	if (targetCharacter)
	{
		//投掷消减对象chant点数
		int damage = 10 * inventory->getLevel();
		targetCharacter->sufferHPEffect(-damage);
		targetCharacter->clearChant();
		delete inventory;
	}
	else
	{
		Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
		storey->getInventoryHandler()->addInventory(inventory, targetCoord.x, targetCoord.y);
	}
}
