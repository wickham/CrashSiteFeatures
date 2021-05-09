class CrashSiteLoot
{
    string ItemName;

    ref TStringArray Attachments;
    string Magazine;
    string Sight;
    float SpawnPercent;

    void CrashSiteLoot(string name, ref TStringArray attachments, string sight, float chance)
    {
        ItemName = name;
        Attachments = attachments;
        Magazine = attachments;
        Sight = sight;
        SpawnPercent = chance;
    }

}

class CrashSiteExclude
{
    string Label;
    float X;
    float Y;
    float Z;
    ref TStringArray ExcludedSpawns;

    void CrashSiteExclude(string site_name, float x_pos, float y_pos, float z_pos, ref TStringArray spawns)
    {
        Label = site_name;
        X = x_pos;
        Y = y_pos;
        Z = z_pos;
        ExcludedSpawns = spawns;
    }
}

class CSFConfig
{
    bool g_CSFDisableLogMessages;
    int g_CSFZombieAndAnimalLifetime;

    int g_CSFAnimalsMin;
    int g_CSFAnimalsMax;
    int g_CSFAnimalsMinDistFromHeli;
    int g_CSFAnimalsMaxDistFromHeli;

    int g_CSFZombiesMin;
    int g_CSFZombiesMax;
    int g_CSFZombieMinDistFromHeli;
    int g_CSFZombieMaxDistFromHeli;

    bool g_CSFDisable_UH1Y_Animals;
    bool g_CSFDisable_Mi8_Animals;
    bool g_CSFDisable_Wreck_Mi8_CDF_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_Animals;
    bool g_CSFDisable_Wreck_UH1Y_Animals;
    bool g_CSFDisable_Wreck_C130J_Animals;
    bool g_CSFDisable_Wreck_C130_Camo_Animals;

    bool g_CSFDisable_UH1Y_Zombies;
    bool g_CSFDisable_Mi8_Zombies;
    bool g_CSFDisable_Wreck_Mi8_CDF_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_Zombies;
    bool g_CSFDisable_Wreck_UH1Y_Zombies;
    bool g_CSFDisable_Wreck_C130J_Zombies;
    bool g_CSFDisable_Wreck_C130_Camo_Zombies;

    ref array<ref CrashSiteExclude> g_CSFExcludedCrashSites;
}
class CSFLoot
{
    int g_CSFLootMin;
    int g_CSFLootMax;

    bool g_CSFLootRandomHealth;
    int g_CSFLootLifetime;

    int g_CSFLootMinDistFrom_UH1Y;
    int g_CSFLootMaxDistFrom_UH1Y;
    int g_CSFLootMinDistFrom_Mi8;
    int g_CSFLootMaxDistFrom_Mi8;
    int g_CSFLootMinDistFrom_C130;
    int g_CSFLootMaxDistFrom_C130;

    bool g_CSFDisable_UH1Y_Loot;
    bool g_CSFDisable_Mi8_Loot;
    bool g_CSFDisable_Wreck_Mi8_CDF_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_Loot;
    bool g_CSFDisable_Wreck_UH1Y_Loot;
    bool g_CSFDisable_Wreck_C130J_Loot;
    bool g_CSFDisable_Wreck_C130_Camo_Loot;

    ref array<ref CrashSiteLoot> g_CSFSpawnableLootList;
}

class CSFConfigManager
{
    private static const string config_path = "$profile:\\CrashSiteFeatures\\CrashSiteFeaturesConfig.json";
    private static const string loot_path = "$profile:\\CrashSiteFeatures\\CrashSiteFeaturesLoot.json";
    private static const string configRoot = "$profile:\\CrashSiteFeatures\\";

    // Check for CONFIG
    static void LoadConfig(out CSFConfig csfConfig)
    {
        if (!FileExist(config_path))
        {
            Print("[CSF] - 'CrashSiteFeaturesConfig.json' does not exist, creating default config..");
            CreateDefaultConfig(csfConfig);
            SaveConfig(csfConfig);
            return;
        }
        Print("[CSF] - 'CrashSiteFeaturesConfig.json' found, loading...");
        JsonFileLoader<CSFConfig>.JsonLoadFile(config_path, csfConfig);
    }
    // Check for LOOT
    static void LoadLoot(out CSFLoot csfLoot)
    {
        if (!FileExist(loot_path))
        {
            Print("[CSF] - 'CrashSiteFeaturesLoot.json' does not exist, creating default loot..");
            CreateDefaultLoot(csfLoot);
            SaveLoot(csfLoot);
            return;
        }
        Print("[CSF] - 'CrashSiteFeaturesLoot.json' found, loading...");
        JsonFileLoader<CSFLoot>.JsonLoadFile(loot_path, csfLoot);
    }

    // Save Config
    protected static void SaveConfig(CSFConfig csfConfig)
        {
            if (!FileExist(configRoot))
            {
                Print("[CSF] - '" + configRoot + "' does not exist, creating...");
                MakeDirectory(configRoot);
            }

            JsonFileLoader<CSFConfig>.JsonSaveFile(config_path, csfConfig);
        }

    // Save Loot
    protected static void SaveLoot(CSFLoot csfLoot)
        {
            if (!FileExist(configRoot))
            {
                Print("[CSF] - '" + configRoot + "' does not exist, creating...");
                MakeDirectory(configRoot);
            }

            JsonFileLoader<CSFLoot>.JsonSaveFile(loot_path, csfLoot);
        }

    protected static void CreateDefaultConfig(out CSFConfig config)
    {
            config = new CSFConfig();
            config.g_CSFExcludedCrashSites = new ref array<ref CrashSiteExclude>;

            config.g_CSFDisableLogMessages = false;
            config.g_CSFZombieAndAnimalLifetime = 2700;

            config.g_CSFAnimalsMin = 0;
            config.g_CSFAnimalsMax = 0;
            config.g_CSFAnimalsMinDistFromHeli = 45;
            config.g_CSFAnimalsMaxDistFromHeli = 90;

            config.g_CSFZombiesMin = 5;
            config.g_CSFZombiesMax = 12;
            config.g_CSFZombieMinDistFromHeli = 5;
            config.g_CSFZombieMaxDistFromHeli = 45;

            config.g_CSFDisable_UH1Y_Animals = true;
            config.g_CSFDisable_Mi8_Animals = true;
            config.g_CSFDisable_Wreck_Mi8_CDF_Animals = true;
            config.g_CSFDisable_Wreck_Mi8_RU_Animals = true;
            config.g_CSFDisable_Wreck_UH1Y_Animals = true;
            config.g_CSFDisable_Wreck_C130J_Animals = true;
            config.g_CSFDisable_Wreck_C130_Camo_Animals = true;
        
            config.g_CSFDisable_UH1Y_Zombies = false;
            config.g_CSFDisable_Mi8_Zombies = false;
            config.g_CSFDisable_Wreck_Mi8_CDF_Zombies = false;
            config.g_CSFDisable_Wreck_Mi8_RU_Zombies = false;
            config.g_CSFDisable_Wreck_UH1Y_Zombies = false;
            config.g_CSFDisable_Wreck_C130J_Zombies = false;
            config.g_CSFDisable_Wreck_C130_Camo_Zombies = false;

            config.g_CSFExcludedCrashSites.Insert(new ref CrashSiteExclude("New Hope Trader1", 541.244629, 423.528442, 11138.811523, {"all"}));
            config.g_CSFExcludedCrashSites.Insert(new ref CrashSiteExclude("<Customizable Exclusion Loot Types>", 1, 0, 1, {"loot", "zombies", "animals"}));

            if (!FileExist(configRoot))
            {
                Print("[CSF] - '" + configRoot + "' does not exist, creating...");
                MakeDirectory(configRoot);
            }
            JsonFileLoader<CSFConfig>.JsonSaveFile(config_path, config);
    }

    protected static void CreateDefaultLoot(out CSFLoot loot)
    {
            loot = new CSFLoot();

            loot.g_CSFSpawnableLootList = new ref array<ref CrashSiteLoot>;

            loot.g_CSFDisable_UH1Y_Loot = true;
            loot.g_CSFDisable_Mi8_Loot = true;
            loot.g_CSFDisable_Wreck_Mi8_CDF_Loot = true;
            loot.g_CSFDisable_Wreck_Mi8_RU_Loot = true;
            loot.g_CSFDisable_Wreck_UH1Y_Loot = true;
            loot.g_CSFDisable_Wreck_C130J_Loot = true;
            loot.g_CSFDisable_Wreck_C130_Camo_Loot = true;

            loot.g_CSFLootMin = 0;
            loot.g_CSFLootMax = 15;
            loot.g_CSFLootLifetime = 2700;
            loot.g_CSFLootRandomHealth = false;

            loot.g_CSFLootMinDistFrom_UH1Y = 2;
            loot.g_CSFLootMaxDistFrom_UH1Y = 25;
            loot.g_CSFLootMinDistFrom_Mi8 = 2;
            loot.g_CSFLootMaxDistFrom_Mi8 = 25;
            loot.g_CSFLootMinDistFrom_C130 = 9;
            loot.g_CSFLootMaxDistFrom_C130 = 35;

            loot.g_CSFSpawnableLootList.Insert(new ref CrashSiteLoot(
                "item_type",
                {
                    "attachment_type1",
                    "attachment_type2_battery_req",
                    "attachemnt_type2_battery_name"
                },
                "magazine_type",
                "sight_type",
                "float_chance_0.0-100.0"));

            if (!FileExist(configRoot))
            {
                Print("[CSF] - '" + configRoot + "' does not exist, creating...");
                MakeDirectory(configRoot);
            }
            JsonFileLoader<CSFLoot>.JsonSaveFile(loot_path, loot);
    }
}