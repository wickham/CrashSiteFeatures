class CrashSiteLoot
{
    string item_type;
    ref TStringArray attachments_list;

    void CrashSiteLoot(string name, ref TStringArray attachments)
    {
        item_type = name;
        attachments_list = attachments;
    }

}

class CrashSiteExclude
{
    string name;
    float x;
    float y;
    float z;
    ref TStringArray exclude_spawns;

    void CrashSiteExclude(string site_name, float x_pos, float y_pos, float z_pos, ref TStringArray spawns)
    {
        name = site_name;
        x = x_pos;
        y = y_pos;
        z = z_pos;
        exclude_spawns = spawns;
    }
}

class HCSZConfig
{
    int g_HCSZDisableLogMessages;

    int g_HCSZZombiesMin;
    int g_HCSZZombiesMax;
    int g_HCSZDisableUH1YZombies;
    int g_HCSZDisableMi8Zombies;
    int g_HCSZZombieMinDistFromHeli;
    int g_HCSZZombieMaxDistFromHeli;

    int g_HCSZAnimalsMin;
    int g_HCSZAnimalsMax;
    int g_HCSZDisableUH1YAnimals;
    int g_HCSZDisableMi8Animals;
    int g_HCSZAnimalsMinDistFromHeli;
    int g_HCSZAnimalsMaxDistFromHeli;

    int g_HCSZZombieAndAnimalLifetime;

    int g_HCSZItemsMin;
    int g_HCSZItemsMax;
    int g_HCSZItemsMinDistFromHeli;
    int g_HCSZItemsMaxDistFromHeli;
    bool g_HCSZItemsRandomHealth;
    ref array<ref CrashSiteLoot> g_HCSZSpawnableItemsList;
    ref array<ref CrashSiteExclude> g_HCSZExcludedCrashSites;
}

class HCSZConfigManager
{
    private static const string configPath = "$profile:\\CrashSiteFeatures\\CrashSiteFeaturesConfig.json";
    private static const string configRoot = "$profile:\\CrashSiteFeatures\\";

    static void LoadConfig(out HCSZConfig hcszConfig)
    {
        if (!FileExist(configPath))
        {
            Print("[HCSZ] 'CrashSiteFeaturesConfig.json' does not exist, creating default config..");
            CreateDefaultConfig(hcszConfig);
            SaveConfig(hcszConfig);
            return;
        }

        Print("[HCSZ] 'CrashSiteFeaturesConfig.json' found, loading...");
        JsonFileLoader<HCSZConfig>.JsonLoadFile(configPath, hcszConfig);
    }

    protected static void SaveConfig(HCSZConfig hcszConfig)
    {
        if (!FileExist(configRoot))
        {
            Print("[HCSZ] '" + configRoot + "' does not exist, creating...");
            MakeDirectory(configRoot);
        }

        JsonFileLoader<HCSZConfig>.JsonSaveFile(configPath, hcszConfig);
    }

protected static void CreateDefaultConfig(out HCSZConfig config)
    {
        config = new HCSZConfig();

        config.g_HCSZSpawnableItemsList = new ref array<ref CrashSiteLoot>;
        config.g_HCSZExcludedCrashSites = new ref array<ref CrashSiteExclude>;

        config.g_HCSZDisableLogMessages = 0;

        config.g_HCSZZombiesMin = 5;
        config.g_HCSZZombiesMax = 12;
        config.g_HCSZDisableUH1YZombies = 0;
        config.g_HCSZDisableMi8Zombies = 0;
        config.g_HCSZZombieMinDistFromHeli = 5;
        config.g_HCSZZombieMaxDistFromHeli = 45;

        config.g_HCSZAnimalsMin = 0;
        config.g_HCSZAnimalsMax = 0;
        config.g_HCSZDisableUH1YAnimals = 1;
        config.g_HCSZDisableMi8Animals = 1;
        config.g_HCSZAnimalsMinDistFromHeli = 45;
        config.g_HCSZAnimalsMaxDistFromHeli = 90;

        config.g_HCSZZombieAndAnimalLifetime = 2700;

        config.g_HCSZItemsMin = 0;
        config.g_HCSZItemsMax = 15;
        config.g_HCSZItemsMinDistFromHeli = 2;
        config.g_HCSZItemsMaxDistFromHeli = 15;
        config.g_HCSZItemsRandomHealth = false;

        config.g_HCSZSpawnableItemsList.Insert(new ref CrashSiteLoot("types_name", {"attachment1_types_name",
                                                                                    "attachment2_types_name"}));
        config.g_HCSZExcludedCrashSites.Insert(new ref CrashSiteExclude("<Trader with Permanent Heli Spawn>", 0, 0, 0, {"all"}));
        config.g_HCSZExcludedCrashSites.Insert(new ref CrashSiteExclude("<Customizable Exclusion Item Types>", 1, 0, 1, {"items", "zombies", "animals"}));

        if (!FileExist(configRoot))
        {
            Print("[HCSZ] '" + configRoot + "' does not exist, creating...");
            MakeDirectory(configRoot);
        }
        JsonFileLoader<HCSZConfig>.JsonSaveFile(configPath, config);
    }
}