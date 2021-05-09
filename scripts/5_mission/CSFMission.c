modded class MissionServer
{
    void MissionServer()
    {
        CSFConfig csfConfig;
        CSFLoot csfLoot;
        CSFConfigManager.LoadConfig(csfConfig);
        CSFConfigManager.LoadLoot(csfLoot);
        GetDayZGame().SetCSFConfig(csfConfig);
        GetDayZGame().SetCSFLoot(csfLoot);
    }
}