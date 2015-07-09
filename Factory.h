#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>

template <class C>
class Factory
{
	public:
		typedef C (* CreateCFunction)();
		
		void RegisterF(std::string name, CreateCFunction function)
		{
			registeredCs[name] = function;
		}
		
		template <class D>
		void Register(std::string name)
		{
			registeredCs[name] = &CreateInstance<D>;
		}

		C Create(std::string name)
		{
			return registeredCs[name]();
		}
	private:
		std::map<std::string, CreateCFunction> registeredCs;
		
		template <class D>
		static C CreateInstance()
		{
			return new D;
		}
};

#endif