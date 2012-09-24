//
// TaskList - MainWindow.h
// Copyright (c) George Burton 2012
//
// This file is released under the terms of the MIT License - you 
//   can read more at opensource.org/licenses/mit-license.php
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <InterfaceKit.h>

class MainWindow : public BWindow
{
public:
			MainWindow(void);
	void	FrameResized(float width, float height);
	void	MessageReceived(BMessage *message);
	bool	QuitRequested(void);
	void	LoadItems(void);
	void	SerializeItems(void);
	
private:
	BListView 	 *itemListView;
	BTextControl *itemEntryBox;
	BButton		 *addButton;
	BButton		 *removeButton;
};

#endif // MAINWINDOW_H
