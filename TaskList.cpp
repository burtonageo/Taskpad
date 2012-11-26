//
// TaskPad - TaskList.cpp
// Copyright (c) George Burton 2012
//
// This file is released under the terms of the MIT License - you 
//   can read more at opensource.org/licenses/mit-license.php
//

#include "TaskList.h"

TaskList::TaskList(void)
{
	tasks = new BList();
}

BList *
TaskList::GetTasks()
{
	return tasks;
}

void
TaskList::AddTask(BString *task)
{
	//tasks.AddItem(task);
}

void
TaskList::Serialize()
{
	/*
	BPath listPath;
	find_directory(B_USER_SETTINGS_DIRECTORY, &listPath);	
	listPath.Append("TaskPad/ToDoItems");

	BMessage listItems;
	for (int i = 0; i < itemListView->CountItems(); i++) {
		BStringItem *item = dynamic_cast<BStringItem*>(
											itemListView->ItemAt(i));
		const char *name = "0"+i;
		listItems.AddString(name,item->Text());
		delete item;
	}

	BFile file(listPath.Path(), B_CREATE_FILE | B_ERASE_FILE | B_WRITE_ONLY);
	if (file.InitCheck() == B_OK) {
		listItems.Flatten(&file);
	}
	*/
}

void
TaskList::LoadTasks()
{
	
}
