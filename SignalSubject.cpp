#include "SignalSubject.h"
#include "SignalObserver.h"


namespace jothly
{
	template<typename ...Args>
	void SignalSubject<Args...>::Emit(Args ...args)
	{
		observers[0].Test(args);

		//for (int i = 0; i < _observers.size(); i++)
		//{
		//	//_observers[i].Test(args);
		//}
	}
}