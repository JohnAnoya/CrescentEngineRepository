#include "FileWatcher.h"
#include <iostream>
#include <stdio.h>
/// Processes a file action
class UpdateListener : public FW::FileWatchListener
{
public:
	UpdateListener() {}
	void handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename,
		FW::Action action)
	{
		std::wcout << "DIR (" << dir << ") FILE (" << filename << ") has event " << action << std::endl;
	}
};