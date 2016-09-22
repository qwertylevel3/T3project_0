#include "BaseManager.h"
#include "ToolFunction.h"
#include "base/ccMacros.h"



BaseManager::BaseManager()
{
}


BaseManager::~BaseManager()
{
}

std::string BaseManager::getChildElementStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return childElement->GetText();
}

std::wstring BaseManager::getChildElementWStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	std::string temp=childElement->GetText();
	return ToolFunction::string2wstring(childElement->GetText());
}

int BaseManager::getChildElementIntAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return ToolFunction::string2int(childElement->GetText());
}

tinyxml2::XMLElement* BaseManager::getChildElement(tinyxml2::XMLElement* parent, std::string name)
{
	tinyxml2::XMLElement* element = parent->FirstChildElement(name.c_str());
	CCAssert(element, (std::string("unknow element type ") + name).c_str());
	return element;
}
