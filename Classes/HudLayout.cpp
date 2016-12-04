#include "HudLayout.h"



HudLayout::HudLayout()
{
}


HudLayout::~HudLayout()
{
}

void HudLayout::init()

{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("layout.xml");
	tinyxml2::XMLElement* layoutElement = doc.RootElement();

	tinyxml2::XMLElement* mainMenuSizeElement = getChildElement(layoutElement, "mainMenuSize");
	mainMenuSize.setSize(getChildElementIntAttr(mainMenuSizeElement, "x"),
		getChildElementIntAttr(mainMenuSizeElement, "y"));

	tinyxml2::XMLElement* mainMenuPositionElement = getChildElement(layoutElement, "mainMenuPosition");
	mainMenuPosition.x = getChildElementIntAttr(mainMenuPositionElement, "x");
	mainMenuPosition.y = getChildElementIntAttr(mainMenuPositionElement, "y");
	
	tinyxml2::XMLElement* mediumMenuSizeElement = getChildElement(layoutElement, "mediumMenuSize");
	mediumMenuSize.setSize(getChildElementIntAttr(mediumMenuSizeElement, "x"),
		getChildElementIntAttr(mediumMenuSizeElement, "y"));

	tinyxml2::XMLElement* mediumMenuPositionElement = getChildElement(layoutElement, "mediumMenuPosition");
	mediumMenuPosition.x = getChildElementIntAttr(mediumMenuPositionElement, "x");
	mediumMenuPosition.y = getChildElementIntAttr(mediumMenuPositionElement, "y");

	tinyxml2::XMLElement* leafMenuSizeElement = getChildElement(layoutElement, "leafMenuSize");
	leafMenuSize.setSize(getChildElementIntAttr(leafMenuSizeElement, "x"),
		getChildElementIntAttr(leafMenuSizeElement,"y"));

	tinyxml2::XMLElement* leafMenuPositionElement = getChildElement(layoutElement, "leafMenuPosition");
	leafMenuPosition.x = getChildElementIntAttr(leafMenuPositionElement, "x");
	leafMenuPosition.y = getChildElementIntAttr(leafMenuPositionElement, "y");

	tinyxml2::XMLElement* barSizeElement = getChildElement(layoutElement, "barSize");
	barSize.setSize(getChildElementIntAttr(barSizeElement, "x"),
		getChildElementIntAttr(barSizeElement,"y"));

	tinyxml2::XMLElement* hpBarPositionElement = getChildElement(layoutElement, "hpBarPosition");
	hpBarPosition.x = getChildElementIntAttr(hpBarPositionElement, "x");
	hpBarPosition.y = getChildElementIntAttr(hpBarPositionElement, "y");

	tinyxml2::XMLElement* mpBarPositionElement = getChildElement(layoutElement, "mpBarPosition");
	mpBarPosition.x = getChildElementIntAttr(mpBarPositionElement, "x");
	mpBarPosition.y = getChildElementIntAttr(mpBarPositionElement, "y");

	tinyxml2::XMLElement* descriptionSizeElement = getChildElement(layoutElement, "descriptionSize");
	descriptionSize.setSize(
		getChildElementIntAttr(descriptionSizeElement, "x"),
		getChildElementIntAttr(descriptionSizeElement, "y")
	);

	tinyxml2::XMLElement* descriptionPositionElement = getChildElement(layoutElement, "descriptionPosition");
	descriptionPosition.x = getChildElementIntAttr(descriptionPositionElement, "x");
	descriptionPosition.y = getChildElementIntAttr(descriptionPositionElement, "y");

	tinyxml2::XMLElement* playerStateSizeElement = getChildElement(layoutElement, "playerStateSize");
	playerStateSize.setSize(
		getChildElementIntAttr(playerStateSizeElement, "x"),
		getChildElementIntAttr(playerStateSizeElement, "y")
	);

	tinyxml2::XMLElement* playerStatePositionElement = getChildElement(layoutElement, "playerStatePosition");
	playerStatePosition.x = getChildElementIntAttr(playerStatePositionElement, "x");
	playerStatePosition.y = getChildElementIntAttr(playerStatePositionElement, "y");

}
