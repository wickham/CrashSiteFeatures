class CrashSiteLoot
{
    string item_type;
    ref TStringArray attachments_type;

    void CrashSiteLoot(string name, ref TStringArray attachments)
    {
        item_type = name;
        attachments_type = attachments;
    }

}

class CrashSiteExclude
{
    float x;
    float y;
    float z;
    string name;

    void CrashSiteExclude(float x_pos, float y_pos, float z_pos, string site_name)
    {
        x = x_pos;
        y = y_pos;
        z = z_pos;
        name = site_name;
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

    int g_HCSZMinNumberOfItems;
    int g_HCSZMaxNumberOfItems;
    int g_HCSZItemsMinDistFromHeli;
    int g_HCSZItemsMaxDistFromHeli;
    int g_HCSZItemsRandomHealth;
    ref array<ref CrashSiteLoot> g_HCSZSpawnableItemsList;

    ref array<ref CrashSiteExclude> g_HCSZExcludedCrashSites;
}

class HCSZConfigManager
{
private static const string configPath = "$profile:\\CrashSiteFeatures\\CrashSiteConfig.json";
private static const string configRoot = "$profile:\\CrashSiteFeatures\\";

    static void LoadConfig(out HCSZConfig hcszConfig)
    {
        if (!FileExist(configPath))
        {
            Print("[HCSZ] 'CrashSiteZombieConfig.json' does not exist, creating default config..");
            CreateDefaultConfig(hcszConfig);
            SaveConfig(hcszConfig);
            return;
        }

        Print("[HCSZ] 'CrashSiteZombieConfig.json' found, loading...");
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

        config.g_HCSZMinNumberOfItems = 15;
        config.g_HCSZMaxNumberOfItems = 15;
        config.g_HCSZItemsMinDistFromHeli = 5;
        config.g_HCSZItemsMaxDistFromHeli = 45;
        config.g_HCSZItemsRandomHealth = 0;

        config.g_HCSZSpawnableItemsList.Insert(new ref CrashSiteLoot("name", {"attachment1",
                                                                              "attachment2"}));
        config.g_HCSZExcludedCrashSites.Insert(new ref CrashSiteExclude(0,0, 0,"Trader with Permanent Heli Spawn"));

        if (!FileExist(configRoot))
        {
            Print("[HCSZ] '" + configRoot + "' does not exist, creating...");
            MakeDirectory(configRoot);
        }
        JsonFileLoader<HCSZConfig>.JsonSaveFile(configPath, config);
    }
}