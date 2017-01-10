#include "NoteTextFactory.h"

NoteText::NoteText()
{
	size = 0;
}

NoteText::~NoteText()
{

}

void NoteText::addPage(std::string page)
{
	text.push_back(page);
	size = text.size();
}

std::string NoteText::getPage(int index)
{
	return text[index];
}

int NoteText::getSize()
{
	return size;
}

//////////////////////////////////////////////////////////////////////////


NoteTextFactory::NoteTextFactory()
{
}


NoteTextFactory::~NoteTextFactory()
{
}

void NoteTextFactory::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("noteText.xml");

	tinyxml2::XMLElement* allNoteElement = doc.RootElement();
	tinyxml2::XMLElement* noteElement = allNoteElement->FirstChildElement();

	while (noteElement)
	{
		NoteText noteText;
		std::string noteID = getChildElementStrAttr(noteElement, "noteID");

		tinyxml2::XMLElement* pageNode = noteElement->FirstChildElement("page");

		while (pageNode)
		{
			noteText.addPage(pageNode->GetText());
			pageNode = pageNode->NextSiblingElement();

		}
		noteTextBox[noteID] = noteText;

		noteElement = noteElement->NextSiblingElement();
	}
}

NoteText NoteTextFactory::getNoteText(std::string noteID)
{
	return noteTextBox[noteID];
}

