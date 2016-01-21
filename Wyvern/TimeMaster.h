#ifndef _TIMEMASTER_H
#define _TIMEMASTER_H
#include"definitions.h"

class TimeMaster{

	struct Time
	{
		long long m_days = 0;
		uint m_hours = 0;
		uint m_minutes = 0;
		uint m_seconds = 0;
		uint m_milliseconds = 0;

		long long getMilliseconds(void){ return (long long)(8.64 * glm::pow(10, 7) * m_days + 3.6 * glm::pow(10, 6) * m_hours + 60000 * m_minutes + 1000 * m_seconds + m_milliseconds); }
		long long getSeconds(void){ return 86400 * m_days + 3600 * m_hours + 60 * m_minutes + m_seconds; }
		long long getMinutes(void){ return 1440 * m_days + 60 * m_hours + m_minutes; }
		long long getHours(void){ return 24*m_days+m_hours; }
		long long getDays(void){ return m_days; }
		void SetMilliseconds(long long p_milliseconds);
		void SetSeconds(long long p_seconds);
		void SetMinutes(long long p_minutes);
		void SetHours(long long p_hours);
		void SetDays(long long p_days);
		void AddMilliseconds(long long p_milliseconds);
		void AddSeconds(long long p_seconds);
		void AddMinutes(long long p_minutes);
		void AddHours(long long p_hours);
		void AddDays(long long p_days);
	};
	struct Clock
	{
		bool m_running = false;
		bool m_countdown = false;
		Time m_currentTime;
		Time m_lastChecked;
		Time m_countdownStart;
		Time m_startTime;
	};
	
	Time m_programTime;
	uint m_fps; //frames per second
	float m_msPerFrame; //milliseconds per frame, objectively a better number to look at in terms of comparison
	int m_frames = 0; //keep track of frames

public:
	static TimeMaster* GetInstance(void);
	static void ReleaseInstance(void);
	uint CreateClock(void);
	uint GetFPS(void);
	float getMsPerFrame(void);
	void UpdateTime(void); //update the current time
	void StartClock(uint p_clockIndex); //starts a time count for the clock at given index
	void SuspendClock(uint p_clockIndex); //pauses the clock at given index
	float ClockLap(uint p_clockIndex); //time difference since the last time this method was called for the given clock
	bool Countdown(uint p_clockIndex, long long p_milliseconds); //counts down on the given clock, returns true when count is up
	void SetClock(uint p_clockIndex, long long p_milliseconds);

	const long MINUTES_TO_MILLISECONDS = 60000;
	const long SECONDS_TO_MILLISECONDS = 1000;
	const long HOURS_TO_MILLISECONDS = 36 * 100000;
	const long DAYS_TO_MILLISECONDS = 864 * 100000;
	const uint MILLISECONDS_IN_SECOND = 1000;
	const uint SECONDS_IN_MINUTE = 60;
	const uint MINUTES_IN_HOUR = 60;
	const uint HOURS_IN_DAY = 24;
private:
	TimeMaster(void); //constructor
	TimeMaster(TimeMaster const& other); //copy constructor
	TimeMaster & operator=(TimeMaster const& other); //copy assignment operator
	~TimeMaster(void); //destructor
	static TimeMaster* m_instance;
	std::vector<Clock> m_clocks; //clock list
	long long TimeDiff(long long p_startTime);
};
#endif