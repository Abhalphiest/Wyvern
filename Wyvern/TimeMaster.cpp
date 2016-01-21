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

}
void TimeMaster::UpdateTime(void)
{

}
void TimeMaster::StartClock(uint p_clockIndex)
{

}
float TimeMaster::TimeDiff(uint p_clockIndex)
{

}
bool TimeMaster::Countdown(uint p_clockIndex, float p_time)
{

}
TimeMaster::TimeMaster(void)
{

}
TimeMaster::TimeMaster(TimeMaster const& other)
{

}
TimeMaster& TimeMaster::operator=(TimeMaster const& other)
{
	return *this;
}
TimeMaster::~TimeMaster(void)
{

}