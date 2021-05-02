modded class MissionServer
{
    void MissionServer()
    {
        HCSZConfig hcszConfig;
        HCSZConfigManager.LoadConfig(hcszConfig);
        GetDayZGame().SetHCSZConfig(hcszConfig);
    }
}