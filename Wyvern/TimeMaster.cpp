#include"TimeMaster.h"
TimeMaster* TimeMaster::m_instance = nullptr;

TimeMaster* TimeMaster::GetInstance(void)
{
	if (m_instance == nullptr)
	{
		m_instance = new TimeMaster();
	}
	return m_instance;
}
void TimeMaster::ReleaseInstance(void)
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}
uint TimeMaster::GetFPS(void)
{
	return (uint)(MILLISECONDS_IN_SECOND*m_msPerFrame); //two multiplicative inverses cancel to just give multiplication
}
uint TimeMaster::getMsPerFrame(void)
{
	return m_msPerFrame;
}
void TimeMaster::UpdateTime(void)
{
	m_frames++;
	m_msPerFrame = (uint)TimeDiff(m_programTime.GetMilliseconds());
	uint adjustedTime; //if we're using more than a uint per frame, we have bigger problems
	m_programTime.AddMilliseconds(TimeDiff(m_programTime.GetMilliseconds()));
	fprintf(stdout,"%d \n",m_msPerFrame);
	for (uint i = 0; i < m_clocks.size(); i++)
	{
		if (m_clocks[i].m_running)
		{
			
			adjustedTime = (uint)(m_programTime.GetMilliseconds() - m_clocks[i].m_startTime.GetMilliseconds() - m_clocks[i].m_currentTime.GetMilliseconds());
			m_clocks[i].m_currentTime.AddMilliseconds(adjustedTime);
			if (m_clocks[i].m_countdown)
			{
				m_clocks[i].UpdateCountdown(adjustedTime);
			}
		}
	}
}
uint TimeMaster::CreateClock(void)
{
	m_clocks.push_back(Clock());
	return m_clocks.size() - 1;
}
void TimeMaster::StartClock(uint p_clockIndex)
{
	if (p_clockIndex < 0 || p_clockIndex >= m_clocks.size())
		return;
	m_clocks[p_clockIndex].m_running = true;
	m_clocks[p_clockIndex].m_startTime = m_programTime;
}
void TimeMaster::SuspendClock(uint p_clockIndex)
{
	if (p_clockIndex < 0 || p_clockIndex >= m_clocks.size())
		return;
	m_clocks[p_clockIndex].m_running = false;
}
unsigned long long TimeMaster::ClockLap(uint p_clockIndex)
{
	if (p_clockIndex < 0 || p_clockIndex >= m_clocks.size())
		return 0;

	unsigned long long elapsed = m_clocks[p_clockIndex].m_currentTime.GetMilliseconds() - m_clocks[p_clockIndex].m_lastChecked.GetMilliseconds();
	m_clocks[p_clockIndex].m_lastChecked = m_clocks[p_clockIndex].m_currentTime;
	return elapsed;
}
bool TimeMaster::CountdownCheck(uint p_clockIndex)
{
	if (p_clockIndex < 0 || p_clockIndex >= m_clocks.size())
		return false;

	if (m_clocks[p_clockIndex].m_countdown)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void TimeMaster::StartCountdown(uint p_clockIndex, unsigned long long p_milliseconds)
{
	if (p_clockIndex < 0 || p_clockIndex >= m_clocks.size())
		return;
	m_clocks[p_clockIndex].m_countdownRemaining.SetMilliseconds(p_milliseconds);
	m_clocks[p_clockIndex].m_countdown = true;
}
void TimeMaster::SetClock(uint p_clockIndex, unsigned long long p_milliseconds)
{
	if (p_clockIndex < 0 || p_clockIndex >= m_clocks.size())
		return;
	//can't think of a clean way to handle the last checked without possibly going in to negative time values
	//so it will just be innaccurate the next time they call for a lap
	m_clocks[p_clockIndex].m_currentTime.SetMilliseconds(p_milliseconds);
}
TimeMaster::TimeMaster(void)
{
	m_programTime.SetMilliseconds((unsigned long long)(glfwGetTime()*SECONDS_TO_MILLISECONDS));
	m_clocks = std::vector<Clock>();
}
TimeMaster::TimeMaster(TimeMaster const& other)
{
	m_clocks = other.m_clocks;
}
TimeMaster& TimeMaster::operator=(TimeMaster const& other)
{
	m_clocks = other.m_clocks;
	return *this;
}
TimeMaster::~TimeMaster(void)
{
	//only exists to be private, we didn't do anything on the heap
}

unsigned long long TimeMaster::TimeDiff(unsigned long long p_startTime)
{
	return (unsigned long long)(glfwGetTime()*SECONDS_TO_MILLISECONDS) - p_startTime;
}
void TimeMaster::Time::SetMilliseconds(unsigned long long p_milliseconds)
{
	m_days = 0;
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
	m_milliseconds = 0;
	AddMilliseconds(p_milliseconds);
}
void TimeMaster::Time::SetSeconds(unsigned long long p_seconds)
{
	m_days = 0;
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
	m_milliseconds = 0;
	AddSeconds(p_seconds);
}
void TimeMaster::Time::SetMinutes(unsigned long long p_minutes)
{
	m_days = 0;
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
	m_milliseconds = 0;
	AddMinutes(p_minutes);
}
void TimeMaster::Time::SetHours(unsigned long long p_hours)
{
	m_days = 0;
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
	m_milliseconds = 0;
	AddHours(p_hours);
}
void TimeMaster::Time::SetDays(unsigned long long p_days)
{
	m_days = 0;
	m_hours = 0;
	m_minutes = 0;
	m_seconds = 0;
	m_milliseconds = 0;
	AddDays(p_days);
}
void TimeMaster::Time::AddMilliseconds(unsigned long long p_milliseconds)
{
	while (p_milliseconds >= DAYS_TO_MILLISECONDS)
	{
		m_days++;
		p_milliseconds -= DAYS_TO_MILLISECONDS;
	}
	while (p_milliseconds >= HOURS_TO_MILLISECONDS)
	{
		m_hours++;
		p_milliseconds -= HOURS_TO_MILLISECONDS;
	}
	while (p_milliseconds >= MINUTES_TO_MILLISECONDS)
	{
		m_minutes++;
		p_milliseconds -= MINUTES_TO_MILLISECONDS;
	}
	while (p_milliseconds >= SECONDS_TO_MILLISECONDS)
	{
		m_seconds++;
		p_milliseconds -= SECONDS_TO_MILLISECONDS;
	}
	m_milliseconds = (uint)p_milliseconds;
}
void TimeMaster::Time::AddSeconds(unsigned long long p_seconds)
{
	AddMilliseconds(SECONDS_TO_MILLISECONDS*p_seconds);
}
void TimeMaster::Time::AddMinutes(unsigned long long p_minutes)
{
	AddMilliseconds(MINUTES_TO_MILLISECONDS*p_minutes);
}
void TimeMaster::Time::AddHours(unsigned long long p_hours)
{
	AddMilliseconds(HOURS_TO_MILLISECONDS*p_hours);
}
void TimeMaster::Time::AddDays(unsigned long long p_days)
{
	AddMilliseconds(DAYS_TO_MILLISECONDS*p_days);
}
