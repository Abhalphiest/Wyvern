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
	return m_fps;
}
float TimeMaster::getMsPerFrame(void)
{
	return m_msPerFrame;
}
void TimeMaster::UpdateTime(void)
{
	for (int i = 0; i < m_clocks.size(); i++)
	{
		m_programTime = TimeDiff(m_programTime.getMilliseconds());
	}
}
void TimeMaster::StartClock(uint p_clockIndex)
{

}
void SuspendClock(uint p_clockIndex)
{

}
float TimeMaster::ClockLap(uint p_clockIndex)
{
	return 0.0f;
}
bool TimeMaster::Countdown(uint p_clockIndex, long long p_milliseconds)
{
	return false;
}
void TimeMaster::SetClock(uint p_clockIndex, long long p_milliseconds)
{

}
TimeMaster::TimeMaster(void)
{
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

}