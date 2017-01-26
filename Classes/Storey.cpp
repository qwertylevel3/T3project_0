#include "Storey.h"
#include"FieldEnum.h"
#include"Character.h"
#include "Player.h"
#include "RoundSystem.h"
#include "StoreyInventoryHandler.h"
#include "MainLayer.h"
#include "MaskLayer.h"
#include "ZOrderManager.h"
#include "RoundSystem.h"

using namespace Field;
USING_NS_CC;

Storey::Storey(int w, int h)
{
	for (int i = 0; i < w*h; i++)
	{
		tiles.push_back(Unused);
	}
	for (int i = 0; i < w*h; i++)
	{
		characterMap.push_back(nullptr);
	}
	inventoryHandler = new StoreyInventoryHandler(w, h);
	picturePath = FileUtils::getInstance()->fullPathForFilename("tile/tile.png");
	width = w;
	height = h;
	tileMap = nullptr;
}

Storey::~Storey()
{
	tileMap->release();
	for each (Character* character in characterList)
	{
		//仅仅析构enemy和object，Hero,Friend和player另外处理
		if (character->getPlayType() == Character::Enemy
			|| character->getPlayType() == Character::Object)
		{
			delete character;
		}
	}
	characterList.clear();
	delete inventoryHandler;
}

int Storey::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		return Unused;
		CCAssert(false, "tile position out of range");
	}
	return tiles[x + y * width];
}

cocos2d::Point Field::Storey::getTilePosition(cocos2d::Point coord)
{
	return cocos2d::Point(coord.x * 32 + 16, (height - coord.y) * 32 - 16);
}

void Field::Storey::setPositionByCoord(Character* character, cocos2d::Point coord)
{
	character->setPosition(getTilePosition(coord));
}

int Field::Storey::getTile(cocos2d::Point coord)
{
	return getTile(coord.x, coord.y);
}

void Storey::setTile(int x, int y, int tile)
{
	tiles[x + y * width] = tile;
}

Character * Field::Storey::getCharacter(int x, int y)
{
	if (isValid(cocos2d::Point(x, y)))
	{
		if (characterMap[x + y*width]
			&& !characterMap[x + y*width]->isDead())
		{
			return characterMap[x + y*width];
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

std::list<Character* >& Field::Storey::getAllCharacter()
{
	return characterList;
}

void Field::Storey::moveUp(Character* character)
{
	character->setOrientationUp();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y--;

	if (isMoveAble(targetCoord))
	{
		characterMoveUp(character);
	}
	else if (isPartner(targetCoord))
	{
		if (isPlayer(character))
		{
			exchangeCoordUp(character);
		}
	}

	cocos2d::Point tempCoord = character->getMapCoord();
	tempCoord.y--;

	//如果脚下为冰块
	if (isIce(character->getMapCoord())
		&& isMoveAble(tempCoord))
	{
		characterMoveUp(character);
	}
}

void Field::Storey::moveDown(Character* character)
{
	character->setOrientationDown();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y++;

	if (isMoveAble(targetCoord))
	{
		characterMoveDown(character);
	}
	else if (isPartner(targetCoord))
	{
		if (isPlayer(character))
		{
			exchangeCoordDown(character);
		}
	}

	cocos2d::Point tempCoord = character->getMapCoord();
	tempCoord.y++;

	//如果脚下为冰块
	if (isIce(character->getMapCoord())
		&& isMoveAble(tempCoord))
	{
		characterMoveDown(character);
	}
}

void Field::Storey::moveLeft(Character* character)
{
	character->setOrientationLeft();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x--;

	if (isMoveAble(targetCoord))
	{
		characterMoveLeft(character);
	}
	else if (isPartner(targetCoord))
	{
		if (isPlayer(character))
		{
			exchangeCoordLeft(character);
		}
	}

	cocos2d::Point tempCoord = character->getMapCoord();
	tempCoord.x--;

	//如果脚下为冰块
	if (isIce(character->getMapCoord())
		&& isMoveAble(tempCoord))
	{
		characterMoveLeft(character);
	}
}

void Field::Storey::moveRight(Character* character)
{
	character->setOrientationRight();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x++;

	if (isMoveAble(targetCoord))
	{
		characterMoveRight(character);
	}
	else if (isPartner(targetCoord))
	{
		if (isPlayer(character))
		{
			exchangeCoordRight(character);
		}
	}

	cocos2d::Point tempCoord = character->getMapCoord();
	tempCoord.x++;

	//如果脚下为冰块
	if (isIce(character->getMapCoord())
		&& isMoveAble(tempCoord))
	{
		characterMoveRight(character);
	}
}

void Field::Storey::characterMoveUp(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y--;
	cocos2d::Point position = character->getPosition();
	cocos2d::Point targetPosition = getTilePosition(targetCoord);
	ActionInterval* moveAction = CCMoveTo::create(0.2, targetPosition);
	character->showMoveUpAnimation();
	character->getSprite()->runAction(moveAction);

	removeCharacter(character);
	character->setMapCoord(targetCoord);
	//上下移动的时候注意修改Zorder，使得前后遮挡生效
	character->getSprite()->setZOrder(targetCoord.y);

	characterMap[targetCoord.x + targetCoord.y*width] = character;

	//to refactor： 重放入时保持原有在list中的位置
	characterList.push_back(character);
}

void Field::Storey::characterMoveDown(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y++;

	cocos2d::Point position = character->getPosition();
	cocos2d::Point targetPosition = getTilePosition(targetCoord);
	ActionInterval* moveAction = CCMoveTo::create(0.2, targetPosition);
	character->showMoveDownAnimation();
	character->getSprite()->runAction(moveAction);

	removeCharacter(character);
	character->setMapCoord(targetCoord);
	//上下移动的时候注意修改Zorder，使得前后遮挡生效
	character->getSprite()->setZOrder(targetCoord.y);

	characterMap[targetCoord.x + targetCoord.y*width] = character;

	//to refactor： 重放入时保持原有在list中的位置
	characterList.push_back(character);
}

void Field::Storey::characterMoveLeft(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x--;

	cocos2d::Point position = character->getPosition();
	cocos2d::Point targetPosition = getTilePosition(targetCoord);
	ActionInterval* moveAction = CCMoveTo::create(0.2, targetPosition);
	character->showMoveLeftAnimation();
	character->getSprite()->runAction(moveAction);

	removeCharacter(character);
	character->setMapCoord(targetCoord);

	characterMap[targetCoord.x + targetCoord.y*width] = character;

	//to refactor： 重放入时保持原有在list中的位置
	characterList.push_back(character);
}

void Field::Storey::characterMoveRight(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x++;

	cocos2d::Point position = character->getPosition();
	cocos2d::Point targetPosition = getTilePosition(targetCoord);
	ActionInterval* moveAction = CCMoveTo::create(0.2, targetPosition);
	character->showMoveRightAnimation();
	character->getSprite()->runAction(moveAction);

	removeCharacter(character);
	character->setMapCoord(targetCoord);

	characterMap[targetCoord.x + targetCoord.y*width] = character;

	//to refactor： 重放入时保持原有在list中的位置
	characterList.push_back(character);
}

void Field::Storey::exchangeCoordUp(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y--;

	Character* partner = getCharacter(targetCoord);

	removeCharacter(partner);
	removeCharacter(character);

	cocos2d::Point tempCoord = character->getMapCoord();
	character->setMapCoord(targetCoord);
	//上下移动的时候注意修改Zorder，使得前后遮挡生效
	character->getSprite()->setZOrder(targetCoord.y);

	partner->setMapCoord(tempCoord);

	characterMap[targetCoord.x + targetCoord.y*width] = character;
	characterMap[tempCoord.x + tempCoord.y*width] = partner;

	characterList.push_back(character);
	characterList.push_back(partner);

	cocos2d::Point characterPosition = getTilePosition(character->getMapCoord());
	cocos2d::Point partnerPosition = getTilePosition(partner->getMapCoord());

	partner->setOrientationDown();
	partner->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, partnerPosition)
	);
	partner->showMoveDownAnimation();

	RoundHandler* roundHandler = partner->getRoundHandler();
	roundHandler->setSkipNextRound(true);

	character->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, characterPosition)
	);
	character->showMoveUpAnimation();
}

void Field::Storey::exchangeCoordDown(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y++;

	Character* partner = getCharacter(targetCoord);

	removeCharacter(partner);
	removeCharacter(character);

	cocos2d::Point tempCoord = character->getMapCoord();
	character->setMapCoord(targetCoord);
	//上下移动的时候注意修改Zorder，使得前后遮挡生效
	character->getSprite()->setZOrder(targetCoord.y);

	partner->setMapCoord(tempCoord);

	characterMap[targetCoord.x + targetCoord.y*width] = character;
	characterMap[tempCoord.x + tempCoord.y*width] = partner;

	characterList.push_back(character);
	characterList.push_back(partner);

	cocos2d::Point characterPosition = getTilePosition(character->getMapCoord());
	cocos2d::Point partnerPosition = getTilePosition(partner->getMapCoord());

	partner->setOrientationUp();
	partner->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, partnerPosition)
	);
	partner->showMoveUpAnimation();
	RoundHandler* roundHandler = partner->getRoundHandler();
	roundHandler->setSkipNextRound(true);

	character->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, characterPosition)
	);
	character->showMoveDownAnimation();
}

void Field::Storey::exchangeCoordLeft(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x--;

	Character* partner = getCharacter(targetCoord);

	removeCharacter(partner);
	removeCharacter(character);

	cocos2d::Point tempCoord = character->getMapCoord();
	character->setMapCoord(targetCoord);
	partner->setMapCoord(tempCoord);

	characterMap[targetCoord.x + targetCoord.y*width] = character;
	characterMap[tempCoord.x + tempCoord.y*width] = partner;

	characterList.push_back(character);
	characterList.push_back(partner);

	cocos2d::Point characterPosition = getTilePosition(character->getMapCoord());
	cocos2d::Point partnerPosition = getTilePosition(partner->getMapCoord());

	partner->setOrientationRight();
	partner->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, partnerPosition)
	);
	partner->showMoveRightAnimation();
	RoundHandler* roundHandler = partner->getRoundHandler();
	roundHandler->setSkipNextRound(true);

	character->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, characterPosition)
	);
	character->showMoveLeftAnimation();
}

void Field::Storey::exchangeCoordRight(Character* character)
{
	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x++;

	Character* partner = getCharacter(targetCoord);

	removeCharacter(partner);
	removeCharacter(character);

	cocos2d::Point tempCoord = character->getMapCoord();
	character->setMapCoord(targetCoord);
	partner->setMapCoord(tempCoord);

	characterMap[targetCoord.x + targetCoord.y*width] = character;
	characterMap[tempCoord.x + tempCoord.y*width] = partner;

	characterList.push_back(character);
	characterList.push_back(partner);

	cocos2d::Point characterPosition = getTilePosition(character->getMapCoord());
	cocos2d::Point partnerPosition = getTilePosition(partner->getMapCoord());

	partner->setOrientationLeft();
	partner->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, partnerPosition)
	);
	partner->showMoveLeftAnimation();
	RoundHandler* roundHandler = partner->getRoundHandler();
	roundHandler->setSkipNextRound(true);

	character->getSprite()->runAction(
		cocos2d::MoveTo::create(0.2, characterPosition)
	);
	character->showMoveRightAnimation();
}

Character * Field::Storey::getCharacter(cocos2d::Point mapCoord)
{
	return getCharacter(mapCoord.x, mapCoord.y);
}

void Field::Storey::addCharacter(int x, int y, Character * character)
{
	MainLayer::getInstance()->addChild(character->getSprite(),
		y);

	character->setMapCoord(cocos2d::Point(x, y));

	character->setPosition((x) * 32 + 16, (height - y) * 32 - 16);

	characterMap[x + y*width] = character;
	characterList.push_back(character);

	RoundSystem::getInstance()->addCharacter(character);

	MaskLayer::getInstance()->addLightForCharacter(character);
}

void Field::Storey::addCharacter(cocos2d::Point coord, Character* character)
{
	addCharacter(coord.x, coord.y, character);
}

void Field::Storey::removeCharacter(int x, int y)
{
	Character* character = characterMap[x + y*width];
	for (std::list<Character*>::iterator iter = characterList.begin();
		iter != characterList.end(); iter++)
	{
		if ((*iter) == character)
		{
			characterList.erase(iter);
			break;
		}
	}
	characterMap[x + y*width] = nullptr;
}

void Field::Storey::changeCharacterCoord(Character* character, cocos2d::Point targetCoord)
{
	std::list<Character* >::iterator iter = characterList.begin();
	while (iter != characterList.end())
	{
		if (*iter == character)
		{
			cocos2d::Point targetPosition = getTilePosition(targetCoord);
			character->getSprite()->stopAllActions();

			character->setPosition(targetPosition);

			removeCharacter(character);
			character->setMapCoord(targetCoord);

			characterMap[targetCoord.x + targetCoord.y*width] = character;

			characterList.push_back(character);
			return;
		}

		iter++;
	}
}

void Field::Storey::removeCharacter(Character* character)
{
	cocos2d::Point coord = character->getMapCoord();
	CCAssert(characterMap[coord.x + coord.y*width] == character, "null character remove");

	for (std::list<Character*>::iterator iter = characterList.begin();
		iter != characterList.end(); iter++)
	{
		if ((*iter) == character)
		{
			characterList.erase(iter);
			break;
		}
	}
	characterMap[coord.x + coord.y*width] = nullptr;
}

StoreyInventoryHandler* Field::Storey::getInventoryHandler()
{
	return inventoryHandler;
}

bool Field::Storey::isMoveAble(cocos2d::Point mapCoord)
{
	if (getCharacter(mapCoord) && !getCharacter(mapCoord)->isDead())
	{
		return false;
	}
	//	if (getCharacter(mapCoord) && !getCharacter(mapCoord)->isDead()
	//		&& getCharacter(mapCoord)->getPlayType() != Character::Hero)
	//	{
	//		return false;
	//	}
	//	if (isPartner(mapCoord))
	//	{
	//		return true;
	//	}
	return isMoveAble(getTile(mapCoord));
}

bool Field::Storey::isMoveAble_v2(cocos2d::Point mapCoord)
{
	if (getCharacter(mapCoord) && !getCharacter(mapCoord)->isDead()
		&& (getCharacter(mapCoord)->getPlayType() == Character::Object
			|| getCharacter(mapCoord)->getPlayType()==Character::Enemy))
	{
		return false;
	}
	//	if (getCharacter(mapCoord) && !getCharacter(mapCoord)->isDead()
	//		&& getCharacter(mapCoord)->getPlayType() != Character::Hero)
	//	{
	//		return false;
	//	}
	//	if (isPartner(mapCoord))
	//	{
	//		return true;
	//	}
	return isMoveAble(getTile(mapCoord));
}

bool Field::Storey::isMoveAble_v3(cocos2d::Point mapCoord)
{
	if (getCharacter(mapCoord) && !getCharacter(mapCoord)->isDead()
		&& getCharacter(mapCoord)->getPlayType()==Character::Object)
	{
		return false;
	}
	return isMoveAble(getTile(mapCoord));
}


bool Field::Storey::isPartner(cocos2d::Point mapCoord)
{
	if (getCharacter(mapCoord)
		&& !getCharacter(mapCoord)->isDead()
		&& (getCharacter(mapCoord)->getPlayType() == Character::Hero
			|| getCharacter(mapCoord)->getPlayType() == Character::Friend))
	{
		return true;
	}
	return false;
}

bool Field::Storey::isMoveAble(int tile)
{
	bool flag = false;
	switch (tile)
	{
	case Field::Tile::Wall:
	case Field::Tile::Unused:
		flag = false;
		break;
	default:
		flag = true;
		break;
	}
	return flag;
}

bool Field::Storey::isWall(cocos2d::Point mapCoord)
{
	if (getTile(mapCoord) == Field::Wall)
	{
		return true;
	}
	return false;
}

bool Field::Storey::isFloor(cocos2d::Point mapCoord)
{
	if (getTile(mapCoord) == Field::Floor
		|| getTile(mapCoord) == Field::UpStair
		|| getTile(mapCoord) == Field::DownStair)
	{
		return true;
	}
	return false;
}

bool Field::Storey::isValid(cocos2d::Point mapCoord)
{
	return mapCoord.x >= 0 && mapCoord.y >= 0 && mapCoord.x < width && mapCoord.y < height;
}

bool Field::Storey::isIce(cocos2d::Point mapCoord)
{
	if (getTile(mapCoord) == Field::Ice)
	{
		return true;
	}
	return false;
}

bool Field::Storey::isTrap(cocos2d::Point mapCoord)
{
	if (getTile(mapCoord) == Field::Trap)
	{
		return true;
	}
	return false;
}

bool Field::Storey::isPlayer(Character* character)
{
	return character == Player::getInstance()->getcharacterPtr();
}

int Storey::getHeight()
{
	return height;
}

int Storey::getWidth()
{
	return width;
}

void Storey::writeToFile(std::string floor)
{
	std::string filePath = FileUtils::getInstance()->getWritablePath();
	filePath = filePath + floor + ".tmx";

	tinyxml2::XMLDocument* pDoc = getPDoc();

	pDoc->SaveFile(filePath.c_str());
	//pDoc->Print();
	delete pDoc;
}

std::string Field::Storey::getFileContent()
{
	tinyxml2::XMLDocument* pDoc = getPDoc();
	tinyxml2::XMLPrinter printer;
	pDoc->Print(&printer);

	return printer.CStr();
}

tinyxml2::XMLDocument * Field::Storey::getPDoc()
{
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	//xml 声明（参数可选）
	tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDel);

	//添加map节点
	tinyxml2::XMLElement *mapElement = pDoc->NewElement("map");
	mapElement->SetAttribute("version", "1.0");
	mapElement->SetAttribute("orientation", "orthogonal");
	mapElement->SetAttribute("renderorder", "right-down");
	mapElement->SetAttribute("width", this->getWidth());
	mapElement->SetAttribute("height", this->getHeight());
	mapElement->SetAttribute("tilewidth", 32);
	mapElement->SetAttribute("tileheight", 32);
	mapElement->SetAttribute("nextobjectid", "1");
	pDoc->LinkEndChild(mapElement);

	//添加tileset节点
	tinyxml2::XMLElement *tilesetElement = pDoc->NewElement("tileset");
	tilesetElement->SetAttribute("firstgid", "1");
	tilesetElement->SetAttribute("name", "tiled");
	tilesetElement->SetAttribute("tilewidth", "32");
	tilesetElement->SetAttribute("tileheight", "32");
	tilesetElement->SetAttribute("tilecount", "128");
	tilesetElement->SetAttribute("clumns", 64);
	mapElement->LinkEndChild(tilesetElement);

	//在tileset节点中添加image节点
	tinyxml2::XMLElement *imageElement = pDoc->NewElement("image");
	imageElement->SetAttribute("source", picturePath.c_str());
	imageElement->SetAttribute("width", "256");
	imageElement->SetAttribute("height", "512");
	tilesetElement->LinkEndChild(imageElement);

	//添加layer节点
	tinyxml2::XMLElement *layerElement = pDoc->NewElement("layer");
	layerElement->SetAttribute("name", "bk");
	layerElement->SetAttribute("width", this->getWidth());
	layerElement->SetAttribute("height", this->getHeight());
	mapElement->LinkEndChild(layerElement);

	//添加layer中的bk data节点
	tinyxml2::XMLElement *bkdataElement = pDoc->NewElement("data");
	layerElement->LinkEndChild(bkdataElement);

	//bk data 数据
	for (int i = 0; i < this->getWidth(); i++)
	{
		for (int j = 0; j < this->getHeight(); j++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", "1");
			bkdataElement->LinkEndChild(tempElement);
		}
	}

	//添加terrain layer节点
	tinyxml2::XMLElement *terrainlayerElement = pDoc->NewElement("layer");
	terrainlayerElement->SetAttribute("name", "terrain");
	terrainlayerElement->SetAttribute("width", this->getWidth());
	terrainlayerElement->SetAttribute("height", this->getHeight());
	mapElement->LinkEndChild(terrainlayerElement);

	//添加terrain layer中data
	tinyxml2::XMLElement *terraindataElement = pDoc->NewElement("data");
	terrainlayerElement->LinkEndChild(terraindataElement);

	//添加data数据
	for (int j = 0; j < this->getHeight(); j++)
	{
		for (int i = 0; i < this->getWidth(); i++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", this->getTile(i, j));
			terraindataElement->LinkEndChild(tempElement);
		}
	}

	return pDoc;
}

cocos2d::TMXTiledMap * Field::Storey::getTileMap()
{
	if (!tileMap)
	{
		tileMap = TMXTiledMap::createWithXML(getFileContent(), "");
		tileMap->retain();
	}
	return tileMap;
}

std::vector<Character*>& Field::Storey::getCharacterMap()
{
	return characterMap;
}