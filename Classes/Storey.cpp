#include "Storey.h"
#include"FieldEnum.h"
#include"Character.h"


using namespace Field;
USING_NS_CC;

Storey::Storey(int w,int h)
{

	for (int i = 0; i < w*h; i++)
	{
		tiles.push_back(Unused);
	}
	for (int i = 0; i < w*h; i++)
	{
		characterMap.push_back(nullptr);
	}
	picturePath = FileUtils::getInstance()->fullPathForFilename("tile.png");
	width = w;
	height = h;
}


Storey::~Storey()
{
}

int Storey::getTile(int x,int y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		return Unused;
		CCAssert(false, "tile position out of range");
	}
	return tiles[x + y * width];
}

int Field::Storey::getTile(cocos2d::Point position)
{
	return getTile(position.x, position.y);
}

void Storey::setTile(int x, int y,int tile)
{
	tiles[x + y * width] = tile;
}

Character * Field::Storey::getCharacter(int x, int y)
{
	return characterMap[x + y*width];
}

Character * Field::Storey::getCharacter(cocos2d::Point position)
{
	return getCharacter(position.x ,position.y);
}

void Field::Storey::setCharacter(int x, int y, Character * character)
{
	characterMap[x + y*width] = character;
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
	filePath=filePath+floor+".tmx";

	tinyxml2::XMLDocument* pDoc=getPDoc();

	pDoc->SaveFile(filePath.c_str());
	//pDoc->Print();
	delete pDoc;
}

std::string Field::Storey::getFileContent()
{
	tinyxml2::XMLDocument* pDoc=getPDoc();
	tinyxml2::XMLPrinter printer;
	pDoc->Print(&printer);

	return printer.CStr();
}

tinyxml2::XMLDocument * Field::Storey::getPDoc()
{
	tinyxml2::XMLDocument *pDoc=new tinyxml2::XMLDocument();
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
	layerElement->SetAttribute("width" , this->getWidth());
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
			tempElement->SetAttribute("gid", this->getTile(i,j));
			terraindataElement->LinkEndChild(tempElement);
		}
	}

	return pDoc;
}


