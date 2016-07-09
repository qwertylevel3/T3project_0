#include "Storey.h"
#include"FieldEnum.h"
#include"cocos2d.h"
#include<tinyxml2\tinyxml2.h>

using namespace Field;
USING_NS_CC;

Storey::Storey(int w,int h)
{

	for (int i = 0; i < w*h; i++)
	{
		tiles.push_back(Unused);
	}
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
		exit(-1);
	}
	return tiles[x + y * width];
}

void Storey::setTile(int x, int y,int tile)
{
	tiles[x + y * width] = tile;
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
	std::string picturePath = FileUtils::getInstance()->fullPathForFilename("tile.png");

	tinyxml2::XMLDocument *pDoc=new tinyxml2::XMLDocument();
	//xml ������������ѡ��
	tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDel);


	//����map�ڵ�
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

	//����tileset�ڵ�
	tinyxml2::XMLElement *tilesetElement = pDoc->NewElement("tileset");
	tilesetElement->SetAttribute("firstgid", "1");
	tilesetElement->SetAttribute("name", "tiled");
	tilesetElement->SetAttribute("tilewidth", "32");
	tilesetElement->SetAttribute("tileheight", "32");
	tilesetElement->SetAttribute("tilecount", "128");
	tilesetElement->SetAttribute("clumns", 64);
	mapElement->LinkEndChild(tilesetElement);

	//��tileset�ڵ�������image�ڵ�
	tinyxml2::XMLElement *imageElement = pDoc->NewElement("image");
	imageElement->SetAttribute("source", picturePath.c_str());
	imageElement->SetAttribute("width", "256");
	imageElement->SetAttribute("height", "512");
	tilesetElement->LinkEndChild(imageElement);

	//����layer�ڵ�
	tinyxml2::XMLElement *layerElement = pDoc->NewElement("layer");
	layerElement->SetAttribute("name", "bk");
	layerElement->SetAttribute("width" , this->getWidth());
	layerElement->SetAttribute("height", this->getHeight());
	mapElement->LinkEndChild(layerElement);

	//����layer�е�bk data�ڵ�
	tinyxml2::XMLElement *bkdataElement = pDoc->NewElement("data");
	layerElement->LinkEndChild(bkdataElement);

	//bk data ����
	for (int i = 0; i < this->getWidth(); i++)
	{
		for (int j = 0; j < this->getHeight(); j++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", "1");
			bkdataElement->LinkEndChild(tempElement);
		}
	}


	//����terrain layer�ڵ�
	tinyxml2::XMLElement *terrainlayerElement = pDoc->NewElement("layer");
	terrainlayerElement->SetAttribute("name", "terrain");
	terrainlayerElement->SetAttribute("width", this->getWidth());
	terrainlayerElement->SetAttribute("height", this->getHeight());
	mapElement->LinkEndChild(terrainlayerElement);

	//����terrain layer��data
	tinyxml2::XMLElement *terraindataElement = pDoc->NewElement("data");
	terrainlayerElement->LinkEndChild(terraindataElement);

	//����data����
	for (int i = 0; i < this->getWidth(); i++)
	{
		for (int j = 0; j < this->getHeight(); j++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", this->getTile(i,j));
			terraindataElement->LinkEndChild(tempElement);
		}
	}

	pDoc->SaveFile(filePath.c_str());
	pDoc->Print();
	delete pDoc;
}

