#ifndef _TIMEMASTER_H
#define _TIMEMASTER_H
#include"definitions.h"

class TimeMaster{

	///<summary> </summary>
	struct Time
	{
		unsigned long long m_days = 0;
		uint m_hours = 0;
		uint m_minutes = 0;
		uint m_seconds = 0;
		uint m_milliseconds = 0;

		///<summary> </summary>
		///<returns> </returns>
		unsigned long long GetMilliseconds(void){ return (long long)(8.64 * glm::pow(10, 7) * m_days + 3.6 * glm::pow(10, 6) * m_hours + 60000 * m_minutes + 1000 * m_seconds + m_milliseconds); }
		///<summary> </summary>
		///<returns> </returns>
		unsigned long long GetSeconds(void){ return 86400 * m_days + 3600 * m_hours + 60 * m_minutes + m_seconds; }
		///<summary> </summary>
		///<returns> </returns>
		unsigned long long GetMinutes(void){ return 1440 * m_days + 60 * m_hours + m_minutes; }
		///<summary> </summary>
		///<returns> </returns>
		unsigned long long GetHours(void){ return 24 * m_days + m_hours; }
		///<summary> </summary>
		///<returns> </returns>
		unsigned long long GetDays(void){ return m_days; }
		///<summary> </summary>
		///<param name="p_milliseconds"> </param>
		void SetMilliseconds(unsigned long long p_milliseconds);
		///<summary> </summary>
		///<param name="p_seconds"> </param>
		void SetSeconds(unsigned long long p_seconds);
		///<summary> </summary>
		///<param name="p_minutes"> </param>
		void SetMinutes(unsigned long long p_minutes);
		///<summary> </summary>
		///<param name="p_hours"> </param>
		void SetHours(unsigned long long p_hours);
		///<summary> </summary>
		///<param name="p_days"> </param>
		void SetDays(unsigned long long p_days);
		///<summary> </summary>
		///<param name="p_milliseconds"> </param>
		void AddMilliseconds(unsigned long long p_milliseconds);
		///<summary> </summary>
		///<param name="p_seconds"> </param>
		void AddSeconds(unsigned long long p_seconds);
		///<summary> </summary>
		///<param name="p_minutes"> </param>
		void AddMinutes(unsigned long long p_minutes);
		///<summary> </summary>
		///<param name="p_hours"> </param>
		void AddHours(unsigned long long p_hours);
		///<summary> </summary>
		///<param name="p_days"> </param>
		void AddDays(unsigned long long p_days);
		
	};
	///<summary> </summary>
	struct Clock
	{
		bool m_running = false;
		bool m_countdown = false;
		Time m_currentTime;
		Time m_lastChecked;
		Time m_countdownRemaining;
		Time m_startTime;
		///<summary> </summary>
		///<param name="p_milliseconds"> </param>
		void UpdateCountdown(uint p_milliseconds) //if we're using more than a uint of milliseconds per frame, we have bigger problems
		{
			m_countdownRemaining.SetMilliseconds(m_countdownRemaining.GetMilliseconds() - p_milliseconds);
			if (m_countdownRemaining.GetMilliseconds() <= 0)
			{
				m_countdown = false;
				m_countdownRemaining.SetMilliseconds(0);
			}
		}
	};
	
	Time m_programTime;
	uint m_msPerFrame; //milliseconds per frame, objectively a better number to look at in terms of comparison
	int m_frames = 0; //keep track of frames

public:
	static TimeMaster* GetInstance(void);
	static void ReleaseInstance(void);
	uint CreateClock(void);
	uint GetFPS(void);
	uint getMsPerFrame(void);
	void UpdateTime(void); //update the current time
	void StartClock(uint p_clockIndex); //starts a time count for the clock at given index
	void SuspendClock(uint p_clockIndex); //pauses the clock at given index
	unsigned long long ClockLap(uint p_clockIndex); //time difference since the last time this method was called for the given clock
	void StartCountdown(uint p_clockIndex, unsigned long long p_milliseconds);
	bool CountdownCheck(uint p_clockIndex); //counts down on the given clock, returns true when count is up
	void SetClock(uint p_clockIndex, unsigned long long p_milliseconds); //destroys last checked

	static const long MINUTES_TO_MILLISECONDS = 60000;
	static const long SECONDS_TO_MILLISECONDS = 1000;
	static const long HOURS_TO_MILLISECONDS = 36 * 100000;
	static const long DAYS_TO_MILLISECONDS = 864 * 100000;
	static const uint MILLISECONDS_IN_SECOND = 1000;
	static const uint SECONDS_IN_MINUTE = 60;
	static const uint MINUTES_IN_HOUR = 60;
	static const uint HOURS_IN_DAY = 24;
private:
	TimeMaster(void); //constructor
	TimeMaster(TimeMaster const& other); //copy constructor
	TimeMaster & operator=(TimeMaster const& other); //copy assignment operator
	~TimeMaster(void); //destructor
	static TimeMaster* m_instance;
	std::vector<Clock> m_clocks; //clock list
	unsigned long long TimeDiff(unsigned long long p_startTime);
};
#endif