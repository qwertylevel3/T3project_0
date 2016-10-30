#include "XMLConfigure.h"
#include "ToolFunction.h"
#include "base/ccMacros.h"



XMLConfigure::XMLConfigure()
{
}


XMLConfigure::~XMLConfigure()
{
}

std::string XMLConfigure::getChildElementStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return childElement->GetText();
}

std::wstring XMLConfigure::getChildElementWStrAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	std::string temp=childElement->GetText();
	return ToolFunction::string2wstring(childElement->GetText());
}

int XMLConfigure::getChildElementIntAttr(tinyxml2::XMLElement* element, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(element, attrName);
	return ToolFunction::string2int(childElement->GetText());
}

tinyxml2::XMLElement* XMLConfigure::getChildElement(tinyxml2::XMLElement* parent, std::string name)
{
	tinyxml2::XMLElement* element = parent->FirstChildElement(name.c_str());
	return element;
}
