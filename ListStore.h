//
// TaskList - ListStore.h
// Copyright (c) George Burton 2012
//
// This file is released under the terms of the MIT License - you 
//   can read more at opensource.org/licenses/mit-license.php
//

#ifndef LISTSTORE_H
#define LISTSTORE_H

#include <SupportKit.h>

class ListStore : public BList
{
public:
	ListStore(void);
	~ListStore();
	void	AddItem(BString *item);
	void	RemoveItem(int index);
	void	SerializeItems();
	void	LoadItems();
	
private:

};

#endif // LISTSTORE_H
