#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

std::map<std::string, int> soundVolumes;

void LoadSoundVolumes(std::istream &is)
{
	char soundName[1024];
	int vol;
	std::string sndLine;
	
	while(!is.eof())
	{
		getline(is, sndLine);
		if(sscanf(sndLine.c_str(), "%s %d", soundName, &vol))
		{
			soundVolumes[std::string(soundName)] = vol;
		}
	}
}

int GetSoundVolume(std::string name)
{
	if(soundVolumes.find(name) != soundVolumes.end()) return soundVolumes[name];
	return 255;
}