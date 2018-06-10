#include <allegro.h>

#include "FileWatch.h"

void FileWatchManager::Update()
{
	for(std::map<std::string, FileWatch *>::iterator it = watches.begin() ; it != watches.end(); ++it)
	{
		std::string fn = it->first;
		FileWatch *w = it->second;
		time_t newTime = file_time(fn.c_str());
		if(difftime(newTime, w->lastModified) > 0.0)
		{
			w->OnModify();
			w->lastModified = newTime;
		}
	}
	
}

void FileWatchManager::Add(std::string filename, FileWatch *w)
{
	w->lastModified = file_time(filename.c_str());
	watches[filename] = w;
}

void FileWatchManager::AddRun(std::string filename, FileWatch *w)
{
	w->OnModify();
	Add(filename, w);
}

void FileWatchManager::Remove(std::string filename)
{
	watches.erase(filename);
}