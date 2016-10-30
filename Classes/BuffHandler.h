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

		void addBuff(std::string buffID);
		void removeBuff(std::string buffID);
		std::vector<BuffBase*>& getBuffBoxRef();
		void update();

		void onAttack();
		void onInjured();
		void onRoundStart();
		void onRoundEnd();

		void clearInactiveBuff();
		void calculateAttr();

		bool exist(std::string buffID);
	protected:
		void addBuff(BuffBase* buff);

		std::vector<BuffBase*> buffBox;
		Character* characterPrt;
	};
}
