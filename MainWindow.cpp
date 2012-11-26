//
// TaskPad - MainWindow.cpp
// Copyright (c) George Burton 2012
//
// This file is released under the terms of the MIT License - you 
//   can read more at opensource.org/licenses/mit-license.php
//

#include "MainWindow.h"

#include <AppKit.h>
#include <StorageKit.h>

#include <stdio.h>

#include "TaskList.h"

enum
{
	M_ADD_ITEM = 'aitm',
	M_REMOVE_ITEM = 'ritm',
	M_SHOW_ABOUT = 'sabt'
};

MainWindow::MainWindow(void)
	:	BWindow(BRect(0, 0, 100, 100), "TaskPad", B_DOCUMENT_WINDOW,
								B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE)
{	
	BRect b(Bounds());
	BView *windowBack = new BView(b, "topview", B_FOLLOW_ALL, B_WILL_DRAW);
	windowBack->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(windowBack);
 
	addButton = new BButton(BRect(10, 10, 11, 11), "addbutton", "Add",
								 new BMessage(M_ADD_ITEM),
								 B_FOLLOW_TOP | B_FOLLOW_RIGHT);
	addButton->ResizeToPreferred();
	addButton->MoveTo(Bounds().right - addButton->Bounds().Width() - 
					 (B_V_SCROLL_BAR_WIDTH / 4),
					  Bounds().top + 3.0);
	
	removeButton = new BButton(BRect(10, 10, 11, 11), "removebutton", "Remove",
								 new BMessage(M_REMOVE_ITEM),
								 B_FOLLOW_TOP | B_FOLLOW_LEFT);
	removeButton->ResizeToPreferred();
	removeButton->MoveTo(Bounds().left + 3,
					  Bounds().top + 3.0);
					  
	aboutButton = new BButton(BRect(10, 10, 11, 11), "aboutbutton", "About"B_UTF8_ELLIPSIS,
								new BMessage(M_SHOW_ABOUT), B_FOLLOW_TOP | B_FOLLOW_LEFT);
	
	itemEntryBox = new BTextControl(BRect(10, 10, 11, 11), "itementry", NULL, 
									"", new BMessage(M_ADD_ITEM), B_FOLLOW_TOP | B_FOLLOW_LEFT, B_WILL_DRAW);
	itemEntryBox->MoveTo(Bounds().left + removeButton->Bounds().Width() + (B_V_SCROLL_BAR_WIDTH / 4), 
						 Bounds().top + 3.0);

	BRect r(Bounds());
	r.right -= B_V_SCROLL_BAR_WIDTH;
	r.left += 1;
	r.top += addButton->Bounds().Height() + 8.0;
	r.bottom -= B_H_SCROLL_BAR_HEIGHT;
	
	itemListView = new BListView(r, "listview", B_SINGLE_SELECTION_LIST,
								B_FOLLOW_ALL);
	
	BScrollView *scrollView = new BScrollView("scrollview", itemListView,
												B_FOLLOW_ALL, 0, true, true);
												
	windowBack->AddChild(scrollView);
	windowBack->AddChild(addButton);
	windowBack->AddChild(removeButton);
	windowBack->AddChild(itemEntryBox);
	
	SetSizeLimits(300, 30000, 150, 30000);
	//ResizeTo(400,300);
	MoveTo((BScreen().Frame().Width() - Bounds().Width()) / 2.0,
			BScreen().Frame().Height() / 4.0);
	
	LoadItems();
}

void
MainWindow::FrameResized(float width, float height)
{
	itemEntryBox->ResizeTo(width - addButton->Bounds().Width() - 
		removeButton->Bounds().Width() - (B_V_SCROLL_BAR_WIDTH / 2), 
		addButton->Frame().Height());
}

bool
MainWindow::QuitRequested(void)
{
	SerializeItems();
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

void
MainWindow::LoadItems(void)
{
	BPath listPath;
	find_directory(B_USER_SETTINGS_DIRECTORY, &listPath);	
	listPath.Append("TaskPad/ToDoItems");

	BMessage listItems;
	BFile file(listPath.Path(), B_READ_ONLY);
	if (file.InitCheck() == B_OK) {
		listItems.Unflatten(&file);	
	}

	for (int i=0; 
		 i < listItems.CountNames(B_STRING_TYPE);
		 i++) {
		const char *name = "0"+i;
		BStringItem *item = new BStringItem(listItems.FindString(name));
		itemListView->AddItem(item);
	}
}

void
MainWindow::SerializeItems(void)
{
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
}

void
MainWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		case M_ADD_ITEM:
		{
			BString *itemText = new BString(itemEntryBox->Text());
			itemText->Trim();
			if (itemText->Length() <= 0) {
				itemEntryBox->SetText("");
				break;
			}

			BStringItem *item = new BStringItem(itemText->String()) ;
			itemListView->AddItem(item);
			itemEntryBox->SetText("");

			delete itemText;
			break;
		}

		case M_REMOVE_ITEM:
		{
			itemListView->RemoveItem(
					itemListView->CurrentSelection());
			break;
		}
		
		case M_SHOW_ABOUT:
		{
			BAlert *about = new BAlert("About"B_UTF8_ELLIPSIS, 
				"A simple ToDo List for Haiku", "Close");
		
			about->Go();
			break;
		}

		default:
		{
			BWindow::MessageReceived(message);
			break;
		}
	}
}
