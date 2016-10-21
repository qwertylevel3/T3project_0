#pragma once


#include <vector>

class Character;
namespace Buff
{
	class BuffBase;
}


namespace Buff
{
	class BuffHandler
	{
	public:
		BuffHandler(Character* c);
		~BuffHandler();
		void addBuff(BuffBase* buff);
		std::vector<BuffBase*>& getBuffBoxRef();
		void update();

		void onBuffLoad();
		void onBuffUnload();
		void onAttack();
		void onInjured();
		void onRoundStart();
		void onRoundOver();
	protected:
		std::vector<BuffBase*> buffBox;
		Character* characterPrt;
	};
}
