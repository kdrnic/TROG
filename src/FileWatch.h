#ifndef FILEWATCH_H
#define FILEWATCH_H

#include <time.h>
#include <map>
#include <string>

class FileWatch
{
	public:
		time_t lastModified;
		
		virtual void OnModify(){};
		virtual ~FileWatch(){};
};

class FileWatchManager
{
	public:
		void Update();
		void Add(std::string filename, FileWatch *w);
		void AddRun(std::string filename, FileWatch *w);
		void Remove(std::string filename);
	private:
		std::map<std::string, FileWatch *> watches;
};

#endif