#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <string.h>

#include "Utils.h"

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

void UnderlinesToSpaces(std::string &s)
{
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == '_') s[i] = ' ';
	}
}

std::string Itoa(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

void ToGrayscale(BITMAP *bmp)
{
	for(int x = 0; x < bmp->w; x++)
	{
		for(int y = 0; y < bmp->h; y++)
		{
			int c = getpixel(bmp, x, y);
			int r = getr(c);
			int g = getg(c);
			int b = getb(c);
			int m = (r + g + b) / 3;
			putpixel(bmp, x, y, makecol(m, m, m));
		}
	}
}

float LineAngle(float x1, float y1, float x2, float y2)
{
	return std::atan2(y2 - y1, x2 - x1);
}

fixed RadiansToAllegro(float angle)
{
	fixed fAngleRad;
	fAngleRad = ftofix(angle);
	fixed fAngleAlDeg;
	fAngleAlDeg = fixmul(fAngleRad, radtofix_r);
	return fAngleAlDeg;
}

int LCM(int a, int b)
{
	int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};
	int numPrimes = 95;
	int lcm = 1;
	for(int i = 0; i < numPrimes; i++)
	{
		while((a % primes[i] == 0) || (b % primes[i] == 0))
		{
			if(a % primes[i] == 0) a /= primes[i];
			if(b % primes[i] == 0) b /= primes[i];
			lcm *= primes[i];
		}
		if(a + b == 2) break;
	}
	return lcm;
}

void SmoothScale(BITMAP *source, BITMAP *dest)
{
	//BITMAP *temp = create_bitmap(MCM(source->w, dest->w), MCM(source->h, dest->h));
	//stretch_blit(source, temp, 0, 0, source->w, source->h, 0, 0, W, H);
	int W = LCM(source->w, dest->w);
	int H = LCM(source->h, dest->h);
	for(int x = 0; x < dest->w; x++)
	{
		for(int y = 0; y < dest->h; y++)
		{
			float sumR = 0;
			float sumG = 0;
			float sumB = 0;
			float numPixels = 0;
			for(int dx = 0; dx < W / dest->w; dx++)
			{
				int _x = x * (W / dest->w);
				_x += dx;
				for(int dy = 0; dy < H / dest->h; dy++)
				{
					int _y = y * (H / dest->h);
					_y += dy;
					int color = getpixel(source, (_x * source->w) / W, (_y * source->h) / H);
					if(color == 0xFF00FF) continue;
					sumR += getr(color);
					sumG += getg(color);
					sumB += getb(color);
					numPixels++;
				}
			}
			sumR /= numPixels;
			sumG /= numPixels;
			sumB /= numPixels;
			putpixel(dest, x, y, makecol(int(sumR), int(sumG), int(sumB)));
		}
	}
}

void DrawParallax(BITMAP *bmp, BITMAP *bg, int sx, int sy)
{
	int coveredWidth = -sx;
	int coveredHeight = -sy;
	while(coveredWidth > 0) coveredWidth -= bg->w;
	while(coveredWidth < -bg->w) coveredWidth += bg->w;
	while(coveredHeight > 0) coveredHeight -= bg->h;
	while(coveredHeight < -bg->h) coveredHeight += bg->h;
	
	while(coveredWidth < 640)
	{
		int _coveredHeight = coveredHeight;
		while(_coveredHeight < 480)
		{
			draw_sprite(bmp, bg, coveredWidth, _coveredHeight);
			_coveredHeight += bg->h;
		}
		coveredWidth += bg->w;
	}
}

void CustomHash(std::uint8_t *data, std::size_t n, Int64Tuple *st)
{
	for(std::size_t i = 0; i < n; i++)
	{
		for(unsigned int j = 0; j < 25; j++) // 25 is minimum to avoid keeping top bits
		{
			st->a = (st->a * -7 + st->b + 0x31415926) ^ data[i];
			st->b = (st->b /  3 + st->a + 0x53589793) ^ data[i];
		}
	}
}


static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz" "0123456789+/";

static inline bool is_base64(unsigned char c)
{
	return (std::isalnum(c) || (c == '+') || (c == '/'));
}

std::string Base64Encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while(in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if(i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;
			for(i = 0; (i <4) ; i++) ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}
	
	if(i)
	{
		for(j = i; j < 3; j++) char_array_3[j] = '\0';
		
		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;
		
		for(j = 0; (j < i + 1); j++) ret += base64_chars[char_array_4[j]];
		
		while((i++ < 3)) ret += '=';
	}
	
	return ret;
}

std::string Base64Decode(std::string const& encodedString)
{
	int i = 0, j = 0;
	int in_ = 0;
	int inputLength = encodedString.size();
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;
	
	while(inputLength-- && ( encodedString[in_] != '=') && is_base64(encodedString[in_]))
	{
		char_array_4[i++] = encodedString[in_]; in_++;
		if(i ==4)
		{
			for(i = 0; i <4; i++) char_array_4[i] = base64_chars.find(char_array_4[i]);
		
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
		
			for(i = 0; (i < 3); i++) ret += char_array_3[i];
			i = 0;
		}
	}
	
	if(i)
	{
		for(j = i; j <4; j++) char_array_4[j] = 0;
		
		for(j = 0; j <4; j++) char_array_4[j] = base64_chars.find(char_array_4[j]);
		
		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
		
		for(j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}
	
	return ret;
}

std::string RemoveWhitespace(std::string in)
{
	std::string s;
	for(int i = 0; i < in.size(); i++)
	{
		if(!isspace(in[i])) s += in[i];
	}
	return s;
}

std::string DatafileToString(DATAFILE *d)
{
	char *cstr = new char[d->size + 1];
	memcpy(cstr, d->dat, d->size);
	cstr[d->size] = 0;
	std::string cppStr(cstr);
	delete cstr;
	return cppStr;
}