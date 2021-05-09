modded class DayZGame
{
    protected ref CSFConfig m_CSFConfig;
    protected ref CSFLoot m_CSFLoot;

    void SetCSFConfig(CSFConfig config)
    {
        m_CSFConfig = config;
    }

    void SetCSFLoot(CSFLoot loot)
    {
        m_CSFLoot = loot;
    }

    CSFConfig GetCSFConfig()
    {
        return m_CSFConfig;
    }

    CSFLoot GetCSFLoot()
    {
        return m_CSFLoot;
    }
}