#include "Note.h"



Note::Note()
{
}


Note::~Note()
{
}

Note* Note::clone()
{
	Note* newNote = new Note();

	this->copyData(newNote);
	newNote->setInventoryType(Inventory::Note);
	newNote->setTextID(textID);

	return newNote;
}
