#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

std::map<std::string, int> soundVolumes;

void LoadSoundVolumes(const char *filename)
{
	char soundName[1024];
	int vol;
	FILE *inf = fopen(filename, "r");
	
	if(!inf) return;
	
	while(fscanf(inf, "%s,%d", soundName, &vol) == 2) soundVolumes[std::string(soundName)] == vol;
	
	fclose(inf);
}

int GetSoundVolume(std::string name)
{
	if(soundVolumes.find(name) != soundVolumes.end()) return soundVolumes[name];
	return 255;
}