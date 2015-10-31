#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#include <allegro.h>

std::vector<std::string> StringToStrings(std::string s);
void UnderlinesToSpaces(std::string &s);
std::string Itoa(int value);
void ToGrayscale(BITMAP *bmp);
float LineAngle(float x1, float y1, float x2, float y2);
fixed RadiansToAllegro(float rad);
int MCM(int a, int b);
void SmoothScale(BITMAP *source, BITMAP *dest);
void DrawParallax(BITMAP *bmp, BITMAP *bg, int sx, int sy);

#endif