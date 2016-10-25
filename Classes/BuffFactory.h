#pragma once

#include <string>
#include "Singleton.h"
#include <map>
#include <vector>

namespace Buff
{
	class BuffBase;

	class BuffFactory :public Singleton<BuffFactory>
	{
	public:
		BuffFactory();
		~BuffFactory();
		BuffBase* getBuff(std::string b);
	protected:
		BuffBase* getBuffPrototype(const std::string& buffName);
		std::map<std::string, BuffBase*> buffPrototypeBox;
		void split(std::string s, char splitchar, std::vector<std::string>& vec);
	};
}
