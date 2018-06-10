#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cstdint>
#include <cmath>

struct BITMAP;
struct DATAFILE;

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

struct Int64Tuple
{
	std::int64_t a;
	std::int64_t b;
};

std::vector<std::string> StringToStrings(std::string s);
void UnderlinesToSpaces(std::string &s);
std::string Itoa(int value);
void ToGrayscale(BITMAP *bmp);
float LineAngle(float x1, float y1, float x2, float y2);
void RadiansToAllegro(float rad, void *theFix);
int MCM(int a, int b);
void SmoothScale(BITMAP *source, BITMAP *dest);
void DrawParallax(BITMAP *bmp, BITMAP *bg, int sx, int sy);
void CustomHash(std::uint8_t *data, std::size_t n, Int64Tuple *st);
std::string Base64Encode(unsigned char const* bytes_to_encode, unsigned int in_len);
std::string Base64Decode(std::string const& encodedString);
std::string RemoveWhitespace(std::string in);
std::string DatafileToString(DATAFILE *d);
long ReadWholeFile(const char *filename, char **ptxt, bool binary);
std::string ReadWholeTextFile(const char *filename);
std::vector<char> ReadWholeBinFile(const char *filename);

#endif