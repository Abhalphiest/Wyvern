#ifndef _TIMEMASTER_H
#define _TIMEMASTER_H
#include"definitions.h"

class TimeMaster{

	struct Clock
	{

	};
	DWORD timerStart = 0;
	DWORD startingTime = 0;
	DWORD lastCalled = 0;

	uint fps = 60; //frames per second
	int frames = 0; //keep track of frames

public:
	static TimeMaster* GetInstance(void);
	static void ReleaseInstance(void);
	uint CreateClock(void);
	uint GetFPS(void);
	void UpdateTime(void); //update the current time
	void StartClock(uint p_clockIndex); //starts a time count for the clock at given index
	float TimeDiff(uint p_clockIndex); //time difference since the last time this method was called for the given clock
	bool Countdown(uint p_clockIndex, float p_time); //counts down on the given clock, returns true when count is up

private:
	TimeMaster(void); //constructor
	TimeMaster(TimeMaster const& other); //copy constructor
	TimeMaster & operator=(TimeMaster const& other); //copy assignment operator
	~TimeMaster(void); //destructor
	static TimeMaster* m_instance;
	std::vector<Clock> m_clocks; //clock list
};
#endif