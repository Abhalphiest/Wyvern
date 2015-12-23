#ifndef _TIMEMASTER_H
#define _TIMEMASTER_H
#include"definitions.h"

class TimeMaster{

	DWORD timerStart = 0;
	DWORD startingTime = 0;
	DWORD lastCalled = 0;

	uint fps = 60; //frames per second
	int frames = 0; //keep track of frames

	std::vector<DWORD> clock; //clock list

public:
	uint GetFPS(void);
	void UpdateTime(void); //update the current time
	void StartClock(uint clock); //starts a time count for the clock at given index
	float TimeDiff(uint clock); //time difference since the last time this method was called for the given clock
	bool Countdown(uint clock, float time, bool repeat); //counts down on the given clock, returns true when count is up

private:
	TimeMaster(void); //constructor
	TimeMaster(TimeMaster const& other); //copy constructor
	TimeMaster & operator=(TimeMaster const& other); //copy assignment operator
	~TimeMaster(void); //destructor

	void Release(void); //give up our memory
	void Init(void); //initialize
};
#endif