#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

std::map<std::string, std::vector<std::string> > things;
std::fstream baseFile;
std::fstream makeFile;

bool FileExists(std::string f)
{
	struct stat sts;
	if(stat(f.c_str(), &sts) == -1 && errno == ENOENT) return false;
	return true;
}

std::vector<std::string> StringToStrings(std::string s)
{
	std::vector<std::string> v;
	while(s.size() > 0 || s != " ")
	{
		std::string e = s.substr(0, s.find(' '));
		v.push_back(e);
		if(e.size() + 1 < s.size()) s = s.substr(e.size() + 1);
		else break;
	}
	return v;
}

void GetObjects(std::vector<std::string> &objects, std::string t)
{
	std::vector<std::string> subThings = things[t];
	for(int i = 0; i < subThings.size(); i++)
	{
		if(things.find(subThings[i]) == things.end())
		{
			std::string cpp = subThings[i];
			cpp += ".cpp";
			std::string obj = subThings[i];
			obj += ".o";
			if(FileExists(cpp)) objects.push_back(subThings[i]);
		}
		else GetObjects(objects, subThings[i]);
	}
}

int main(int argc, char **argv)
{
	if(argc < 2) baseFile.open("MakefileBase", std::fstream::in);
	else baseFile.open(argv[1], std::fstream::in);
	if(!baseFile.is_open()) return 0;
	while(!baseFile.eof())
	{
		std::string line;
		getline(baseFile, line);
		if(line == "") continue;
		std::vector<std::string> subThings = StringToStrings(line);
		std::string firstSubThing = subThings[0];
		subThings.erase(subThings.begin());
		things[firstSubThing] = subThings;
	}
	baseFile.close();
	if(argc < 3) makeFile.open("Makefile", std::fstream::out);
	else makeFile.open(argv[2], std::fstream::out);
	std::string cc, flags, libs, exec, objDir;
	cc = "g++";
	flags = "-g -Wreturn-type -Werror";
	libs = "-lalleg";
	exec = "TROG";
	objDir = "obj/";
	makeFile << "norulespecified: all\n\n";
	for(std::map<std::string, std::vector<std::string> >::iterator i = things.begin(); i != things.end(); i++)
	{
		makeFile << i->first << ':';
		for(int j = 0; j < i->second.size(); j++)
		{
			if(things.find(i->second[j]) != things.end())
			{
				makeFile << ' ' << i->second[j];
			}
			else
			{
				std::string cpp = i->second[j];
				std::string obj = cpp;
				cpp += ".cpp";
				obj += ".o";
				if(FileExists(cpp)) makeFile << ' ' << objDir << obj;
			}
		}
		makeFile << '\n';
		if(i->first == "TROG")
		{
			makeFile << '\t' << cc << ' ' << flags;
			std::vector<std::string> objs;
			GetObjects(objs, "TROG");
			for(int j = 0; j < objs.size(); j++) makeFile << ' ' << objDir << objs[j] << ".o";
			makeFile << " -o " << exec << ' ' << libs << '\n';
		}
		makeFile << '\n';
	}
	std::vector<std::string> objs;
	GetObjects(objs, "TROG");
	for(int j = 0; j < objs.size(); j++)
	{
		std::string cpp = objs[j];
		std::string obj = objs[j];
		std::string header = objs[j];
		cpp += ".cpp";
		obj += ".o";
		header += ".h";
		makeFile << objDir << obj << ':';
		if(FileExists(cpp)) makeFile << ' ' << cpp;
		if(FileExists(header)) makeFile << ' ' << header;
		makeFile << "\n\t" << cc << ' ' << flags << " -c " << cpp << " -o " << objDir << obj << ' ' << libs << "\n\n";
	}
	makeFile.close();
	return 0;
}