#pragma once


#include <vector>
#include <map>
#include "XMLConfigure.h"
#include "Singleton.h"

class NoteText
{
public:
	NoteText();
	~NoteText();

	void addPage(std::string page);
	std::string getPage(int index);
	int getSize();
protected:
	std::vector<std::string> text;
	int size;
};


class NoteTextFactory:public XMLConfigure,public Singleton<NoteTextFactory>
{
public:
	NoteTextFactory();
	~NoteTextFactory();
	void init();

	NoteText getNoteText(std::string noteID);
protected:
	std::map<std::string, NoteText> noteTextBox;
};

