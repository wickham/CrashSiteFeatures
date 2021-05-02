modded class DayZGame
{
    protected ref HCSZConfig m_HCSZConfig;

    void SetHCSZConfig(HCSZConfig config)
    {
		m_HCSZConfig = config;
    }

    HCSZConfig GetHCSZConfig()
    {
        return m_HCSZConfig;
    }
}