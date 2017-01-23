#include "GameSaveManager.h"
#include "ToolFunction.h"
#include "HudMessageBox.h"


using namespace tinyxml2;

GameSaveManager::GameSaveManager()
{
}

GameSaveManager::~GameSaveManager()
{
}

void GameSaveManager::init()
{

}

void GameSaveManager::load()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("gamesave.xml");

	tinyxml2::XMLElement* gamesaveElement = doc.RootElement();

	playCount = this->getChildElementIntAttr(gamesaveElement, "playCount");
	dieCount = this->getChildElementIntAttr(gamesaveElement, "dieCount");
	vergilDieCount = this->getChildElementIntAttr(gamesaveElement, "vergilDieCount");
	persephoneDieCount = this->getChildElementIntAttr(gamesaveElement, "persephoneDieCount");
	clearGameCount = this->getChildElementIntAttr(gamesaveElement, "clearGameCount");
	firstClear = this->getChildElementIntAttr(gamesaveElement, "firstClear");
}

void GameSaveManager::save()
{
	//要储存XML文件的路径
	std::string filePath = "gamesave.xml";//cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "wociao.xml";

	//xml文档
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	if (NULL == pDoc) {
		return;
	}
	//xml声明
	XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	if (NULL == pDel) {
		return;
	}
	pDoc->LinkEndChild(pDel);
	//节点plist
	XMLElement *gamesaveElement = pDoc->NewElement("gamesave");
	gamesaveElement->SetAttribute("version", "1.0");//给节点设置属性
	pDoc->LinkEndChild(gamesaveElement);

	saveValue(pDoc, gamesaveElement, "playCount", playCount);
	saveValue(pDoc, gamesaveElement, "dieCount", dieCount);
	saveValue(pDoc, gamesaveElement, "vergilDieCount", vergilDieCount);
	saveValue(pDoc, gamesaveElement, "persephoneDieCount", persephoneDieCount);
	saveValue(pDoc, gamesaveElement, "clearGameCount", clearGameCount);
	saveValue(pDoc, gamesaveElement, "firstClear", firstClear);



	pDoc->SaveFile(filePath.c_str());//保存文件 参数：路径
//	pDoc->Print();//打印
	delete pDoc;
}

int GameSaveManager::getPlayCount()
{
	return playCount;
}

int GameSaveManager::getDieCount()
{
	return dieCount;
}

int GameSaveManager::getVergilDieCount()
{
	return vergilDieCount;
}

int GameSaveManager::getPersephoneDieCount()
{
	return persephoneDieCount;
}

int GameSaveManager::getClearGameCount()
{
	return clearGameCount;
}

int GameSaveManager::getFirstClear()
{
	return firstClear;
}

void GameSaveManager::increasePlayCount()
{
	playCount++;
}

void GameSaveManager::increaseDieCount()
{
	dieCount++;
}

void GameSaveManager::increaseVergilDieCount()
{
	vergilDieCount++;
}

void GameSaveManager::increasePersephoneDieCount()
{
	persephoneDieCount++;
}

void GameSaveManager::increaseClearGameCount()
{
	clearGameCount++;
}

void GameSaveManager::increaseFirstClear()
{
	firstClear++;
}

void GameSaveManager::saveValue(
	tinyxml2::XMLDocument * pDoc,
	tinyxml2::XMLElement* parent, 
	std::string elementName, 
	int value)
{
	XMLElement * element = pDoc->NewElement(elementName.c_str());
	element->LinkEndChild(pDoc->NewText(
		ToolFunction::int2string(value).c_str()
	));//给节点设置值
	parent->LinkEndChild(element);


}
