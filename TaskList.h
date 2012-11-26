//
// TaskPad - TaskList.h
// Copyright (c) George Burton 2012
//
// This file is released under the terms of the MIT License - you 
//   can read more at opensource.org/licenses/mit-license.php
//

#ifndef TASKLIST_H
#define TASKLIST_H

#include <SupportKit.h>

class TaskList {
public:
// Constructors
			TaskList(void);

// Accessors
	BList*	GetTasks();

// Other Methods
	void	AddTask(BString *task);
	void	Serialize();
	void	LoadTasks();
	
private:
	BList *tasks;
	
};

#endif // TASKLIST_H
