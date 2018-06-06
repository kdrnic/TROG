#ifndef TELLER_H
#include "Entity.h"

#include <vector>
#include <string>

class Teller : public Entity
{
	public:
		void Update();
		void SetParameter(std::string p, std::string v);

		Teller();
	private:
		std::vector<std::string> text;
};

#endif
