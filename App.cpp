//
// TaskList - App.cpp
// Copyright (c) George Burton 2012
//
// This file is released under the terms of the MIT License - you 
//   can read more at opensource.org/licenses/mit-license.php
//

#include "App.h"
#include "MainWindow.h"

App::App(void)
	:	BApplication("application/x-vnd.gab-TaskPad")
{
	MainWindow *mainWin = new MainWindow();
	mainWin->Show();
}

int
main(int argc, char **argv)
{
	App *app = new App();
	app->Run();
	delete app;
	return 0;
}
