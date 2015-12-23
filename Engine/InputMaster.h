#include"WindowMaster.h" //we need to be able to get an instance of this

class InputMaster
{
	public:
		static InputMaster* GetInstance(void); //accessor
		static void ReleaseInstance(void); //release

};