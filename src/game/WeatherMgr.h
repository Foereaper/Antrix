/****************************************************************************
 *
 * Weather System
 *
 */

#ifndef __WEATHERMGR_H
#define __WEATHERMGR_H

#define WEATHER_DENSITY_UPDATE 0.01f

class WeatherInfo;
class WeatherMgr;

class WeatherMgr :  public Singleton < WeatherMgr >
{
public:
	WeatherMgr();
	~WeatherMgr();

	void LoadFromDB();
	uint32 GetSound(uint32 effect, float density);
	void SendWeather(Player *plr);

private:
	std::map<uint32, WeatherInfo*> m_zoneWeathers;
};

class WeatherInfo : public EventableObject
{
	friend class WeatherMgr;
public:
	WeatherInfo();
	~WeatherInfo();

	void Update();	
	void SendUpdate();
	void SendUpdate(Player *plr);

protected:
	void _GenerateWeather();

	uint32 m_zoneId;

	uint32 m_totalTime;
	uint32 m_currentTime;

	float m_maxDensity;
	float m_currentDensity;

	uint32 m_currentEffect;
	bool m_increase;
	std::map<uint32, uint32> m_effectValues;
};

#define sWeatherMgr WeatherMgr::getSingleton()

#endif
