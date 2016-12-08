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
		if (character->getPlayType() == Character::Enemy)
		{
			delete character;
		}
	}
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
	return characterMap[x + y*width];
}

std::list<Character* >& Field::Storey::getAllCharacter()
{
	return characterList;
}

void Field::Storey::characterMoveUp(Character* character)
{
	character->setOrientationUp();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y--;
	if (!isMoveAble(targetCoord))
	{
		return;
	}
	//和队友交换位置
	if (isPartner(targetCoord))
	{
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
	else
	{
		cocos2d::Point position = character->getPosition();
		ActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x, position.y + 32));
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
}

void Field::Storey::characterMoveDown(Character* character)
{
	character->setOrientationDown();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.y++;
	if (!isMoveAble(targetCoord))
	{
		return;
	}

	if (isPartner(targetCoord))
	{
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
	else
	{
		cocos2d::Point position = character->getPosition();
		ActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x, position.y - 32));
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
}

void Field::Storey::characterMoveLeft(Character* character)
{
	character->setOrientationLeft();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x--;
	if (!isMoveAble(targetCoord))
	{
		return;
	}

	if (isPartner(targetCoord))
	{
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
	else
	{
		cocos2d::Point position = character->getPosition();
		ActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x - 32, position.y));
		character->showMoveLeftAnimation();
		character->getSprite()->runAction(moveAction);

		removeCharacter(character);
		character->setMapCoord(targetCoord);

		characterMap[targetCoord.x + targetCoord.y*width] = character;

		//to refactor： 重放入时保持原有在list中的位置
		characterList.push_back(character);
	}
}

void Field::Storey::characterMoveRight(Character* character)
{
	character->setOrientationRight();

	cocos2d::Point targetCoord = character->getMapCoord();
	targetCoord.x++;
	if (!isMoveAble(targetCoord))
	{
		return;
	}

	if (isPartner(targetCoord))
	{
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
	else
	{
		cocos2d::Point position = character->getPosition();
		ActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x + 32, position.y));
		character->showMoveRightAnimation();
		character->getSprite()->runAction(moveAction);

		removeCharacter(character);
		character->setMapCoord(targetCoord);

		characterMap[targetCoord.x + targetCoord.y*width] = character;

		//to refactor： 重放入时保持原有在list中的位置
		characterList.push_back(character);
	}
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
	if (getCharacter(mapCoord) && !getCharacter(mapCoord)->isDead()
		&& getCharacter(mapCoord)->getPlayType() != Character::Hero)
	{
		return false;
	}
	if (isPartner(mapCoord))
	{
		return true;
	}
	return isMoveAble(getTile(mapCoord));
}

bool Field::Storey::isPartner(cocos2d::Point mapCoord)
{
	if (getCharacter(mapCoord)
		&& !getCharacter(mapCoord)->isDead()
		&& getCharacter(mapCoord)->getPlayType() == Character::Hero)
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
	case Field::Tile::Floor:
	case Field::Tile::UpStair:
	case Field::Tile::DownStair:
		flag = true;
		break;
	default:
		flag = false;
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