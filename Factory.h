#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>

template <class C>
class Factory
{
	public:
		typedef C (* CreateCFunction)();
		
		void Register(std::string name, CreateCFunction function)
		{
			registeredCs[name] = function;
		}

		C Create(std::string name)
		{
			return registeredCs[name]();
		}
	private:
		std::map<std::string, CreateCFunction> registeredCs;
};

#endif