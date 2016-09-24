#pragma once

#include "tinyxml2/tinyxml2.h"
#include <string>

class XMLConfigure
{
public:
	XMLConfigure();
	~XMLConfigure();
	virtual void init()=0;
protected:
	std::string getChildElementStrAttr(tinyxml2::XMLElement* element, std::string attrName);
	std::wstring getChildElementWStrAttr(tinyxml2::XMLElement* element, std::string attrName);
	int getChildElementIntAttr(tinyxml2::XMLElement* element, std::string attrName);

	tinyxml2::XMLElement* getChildElement(tinyxml2::XMLElement* parent, std::string name);
};

