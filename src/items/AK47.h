#ifndef AK47_H
#define AK47_H

#include "Item.h"

class AK47 : public Item
{
	public:
		bool hasMag;
		
		void OnUse();
		
		AK47();
	private:
		unsigned int shotsCounter;
		int voiceId;
};

#endif