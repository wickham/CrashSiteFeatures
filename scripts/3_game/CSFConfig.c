class CrashSiteLoot
{
    string ItemName;

    ref TStringArray Attachments;
    string Magazine;
    string Sight;
    int MinCount;
    int MaxCount;
    ref TStringArray IncludedWrecks;

    void CrashSiteLoot(string name, ref TStringArray attachments, string magazine, string sight, int min_count, int max_count, ref TStringArray wrecks)
    {
        ItemName = name;
        Attachments = attachments;
        Magazine = magazine;
        Sight = sight;
        MinCount = min_count;
        MaxCount = max_count;
        IncludedWrecks = wrecks;
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
    bool g_CSFDisable_Wreck_UH1Y_USMC_1_Animals;

    bool g_CSFDisable_Mi8_Animals;
    bool g_CSFDisable_Wreck_Mi8_CDF_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_CDF_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_1_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_1_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_2_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_2_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_3_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_3_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_4_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_RU_4_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_Winter_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_Winter_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_Civ_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_Civ_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_UN_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_UN_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_Desert_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_Desert_2_Animals;
    bool g_CSFDisable_Wreck_Mi8_Tropic_1_Animals;
    bool g_CSFDisable_Wreck_Mi8_Tropic_2_Animals;

    bool g_CSFDisable_Wreck_C130_USMC_1_Animals;
    bool g_CSFDisable_Wreck_C130_USMC_2_Animals;
    bool g_CSFDisable_Wreck_C130_USAF_1_Animals;
    bool g_CSFDisable_Wreck_C130_USAF_2_Animals;
    bool g_CSFDisable_Wreck_C130_Camo_1_Animals;
    bool g_CSFDisable_Wreck_C130_Camo_2_Animals;
    bool g_CSFDisable_Wreck_C130_Camo_3_Animals;
    bool g_CSFDisable_Wreck_C130_AAF_1_Animals;
    bool g_CSFDisable_Wreck_C130_AAF_2_Animals;
    bool g_CSFDisable_Wreck_C130_CIV_1_Animals;
    bool g_CSFDisable_Wreck_C130_CIV_2_Animals;




    bool g_CSFDisable_Mi8_Zombies;
    bool g_CSFDisable_Wreck_Mi8_CDF_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_CDF_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_1_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_1_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_2_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_2_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_3_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_3_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_4_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_RU_4_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Winter_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Winter_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Civ_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Civ_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_UN_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_UN_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Desert_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Desert_2_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Tropic_1_Zombies;
    bool g_CSFDisable_Wreck_Mi8_Tropic_2_Zombies;

    bool g_CSFDisable_UH1Y_Zombies;
    bool g_CSFDisable_Wreck_UH1Y_USMC_1_Zombies;

    bool g_CSFDisable_Wreck_C130_USMC_1_Zombies;
    bool g_CSFDisable_Wreck_C130_USMC_2_Zombies;
    bool g_CSFDisable_Wreck_C130_USAF_1_Zombies;
    bool g_CSFDisable_Wreck_C130_USAF_2_Zombies;
    bool g_CSFDisable_Wreck_C130_Camo_1_Zombies;
    bool g_CSFDisable_Wreck_C130_Camo_2_Zombies;
    bool g_CSFDisable_Wreck_C130_Camo_3_Zombies;
    bool g_CSFDisable_Wreck_C130_AAF_1_Zombies;
    bool g_CSFDisable_Wreck_C130_AAF_2_Zombies;
    bool g_CSFDisable_Wreck_C130_CIV_1_Zombies;
    bool g_CSFDisable_Wreck_C130_CIV_2_Zombies;

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


    bool g_CSFDisable_Mi8_Loot;
    bool g_CSFDisable_Wreck_Mi8_CDF_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_CDF_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_1_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_1_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_2_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_2_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_3_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_3_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_4_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_RU_4_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_Winter_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_Winter_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_Civ_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_Civ_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_UN_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_UN_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_Desert_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_Desert_2_Loot;
    bool g_CSFDisable_Wreck_Mi8_Tropic_1_Loot;
    bool g_CSFDisable_Wreck_Mi8_Tropic_2_Loot;

    bool g_CSFDisable_UH1Y_Loot;
    bool g_CSFDisable_Wreck_UH1Y_USMC_1_Loot;

    bool g_CSFDisable_Wreck_C130_USMC_1_Loot;
    bool g_CSFDisable_Wreck_C130_USMC_2_Loot;
    bool g_CSFDisable_Wreck_C130_USAF_1_Loot;
    bool g_CSFDisable_Wreck_C130_USAF_2_Loot;
    bool g_CSFDisable_Wreck_C130_Camo_1_Loot;
    bool g_CSFDisable_Wreck_C130_Camo_2_Loot;
    bool g_CSFDisable_Wreck_C130_Camo_3_Loot;
    bool g_CSFDisable_Wreck_C130_AAF_1_Loot;
    bool g_CSFDisable_Wreck_C130_AAF_2_Loot;
    bool g_CSFDisable_Wreck_C130_CIV_1_Loot;
    bool g_CSFDisable_Wreck_C130_CIV_2_Loot;

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

        config.g_CSFDisableLogMessages = true;
        config.g_CSFZombieAndAnimalLifetime = 2700;

        config.g_CSFAnimalsMin = 0;
        config.g_CSFAnimalsMax = 0;
        config.g_CSFAnimalsMinDistFromHeli = 45;
        config.g_CSFAnimalsMaxDistFromHeli = 90;

        config.g_CSFZombiesMin = 5;
        config.g_CSFZombiesMax = 12;
        config.g_CSFZombieMinDistFromHeli = 5;
        config.g_CSFZombieMaxDistFromHeli = 45;




        config.g_CSFDisable_Mi8_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_CDF_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_CDF_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_1_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_1_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_2_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_2_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_3_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_3_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_4_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_RU_4_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Winter_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Winter_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Civ_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Civ_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_UN_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_UN_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Desert_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Desert_2_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Tropic_1_Animals = true;
        config.g_CSFDisable_Wreck_Mi8_Tropic_2_Animals = true;

        config.g_CSFDisable_UH1Y_Animals = true;
        config.g_CSFDisable_Wreck_UH1Y_USMC_1_Animals = true;

        config.g_CSFDisable_Wreck_C130_USMC_1_Animals = true;
        config.g_CSFDisable_Wreck_C130_USMC_2_Animals = true;
        config.g_CSFDisable_Wreck_C130_USAF_1_Animals = true;
        config.g_CSFDisable_Wreck_C130_USAF_2_Animals = true;
        config.g_CSFDisable_Wreck_C130_Camo_1_Animals = true;
        config.g_CSFDisable_Wreck_C130_Camo_2_Animals = true;
        config.g_CSFDisable_Wreck_C130_Camo_3_Animals = true;
        config.g_CSFDisable_Wreck_C130_AAF_1_Animals = true;
        config.g_CSFDisable_Wreck_C130_AAF_2_Animals = true;
        config.g_CSFDisable_Wreck_C130_CIV_1_Animals = true;
        config.g_CSFDisable_Wreck_C130_CIV_2_Animals = true;


        config.g_CSFDisable_Mi8_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_CDF_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_CDF_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_1_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_1_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_2_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_2_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_3_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_3_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_4_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_RU_4_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Winter_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Winter_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Civ_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Civ_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_UN_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_UN_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Desert_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Desert_2_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Tropic_1_Zombies = false;
        config.g_CSFDisable_Wreck_Mi8_Tropic_2_Zombies = false;

        config.g_CSFDisable_UH1Y_Zombies = false;
        config.g_CSFDisable_Wreck_UH1Y_USMC_1_Zombies = false;

        config.g_CSFDisable_Wreck_C130_USMC_1_Zombies = false;
        config.g_CSFDisable_Wreck_C130_USMC_2_Zombies = false;
        config.g_CSFDisable_Wreck_C130_USAF_1_Zombies = false;
        config.g_CSFDisable_Wreck_C130_USAF_2_Zombies = false;
        config.g_CSFDisable_Wreck_C130_Camo_1_Zombies = false;
        config.g_CSFDisable_Wreck_C130_Camo_2_Zombies = false;
        config.g_CSFDisable_Wreck_C130_Camo_3_Zombies = false;
        config.g_CSFDisable_Wreck_C130_AAF_1_Zombies = false;
        config.g_CSFDisable_Wreck_C130_AAF_2_Zombies = false;
        config.g_CSFDisable_Wreck_C130_CIV_1_Zombies = false;
        config.g_CSFDisable_Wreck_C130_CIV_2_Zombies = false;

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




        loot.g_CSFDisable_Mi8_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_CDF_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_CDF_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_1_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_1_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_2_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_2_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_3_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_3_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_4_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_RU_4_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Winter_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Winter_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Civ_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Civ_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_UN_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_UN_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Desert_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Desert_2_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Tropic_1_Loot = true;
        loot.g_CSFDisable_Wreck_Mi8_Tropic_2_Loot = true;


        loot.g_CSFDisable_UH1Y_Loot = true;
        loot.g_CSFDisable_Wreck_UH1Y_USMC_1_Loot = true;


        loot.g_CSFDisable_Wreck_C130_USMC_1_Loot = true;
        loot.g_CSFDisable_Wreck_C130_USMC_2_Loot = true;
        loot.g_CSFDisable_Wreck_C130_USAF_1_Loot = true;
        loot.g_CSFDisable_Wreck_C130_USAF_2_Loot = true;
        loot.g_CSFDisable_Wreck_C130_Camo_1_Loot = true;
        loot.g_CSFDisable_Wreck_C130_Camo_2_Loot = true;
        loot.g_CSFDisable_Wreck_C130_Camo_3_Loot = true;
        loot.g_CSFDisable_Wreck_C130_AAF_1_Loot = true;
        loot.g_CSFDisable_Wreck_C130_AAF_2_Loot = true;
        loot.g_CSFDisable_Wreck_C130_CIV_1_Loot = true;
        loot.g_CSFDisable_Wreck_C130_CIV_2_Loot = true;




        loot.g_CSFSpawnableLootList.Insert(new ref CrashSiteLoot(
            "item_type",
            {
                "attachment_type1",
                "attachment_type2_battery_req",
                "attachemnt_type2_battery_name"
            },
            "magazine_type",
            "sight_type",
            0,
            5,
            {
                "Mi8",
                "UH1Y",
                "C130"
             }));
        loot.g_CSFSpawnableLootList.Insert(new ref CrashSiteLoot(
            "M4A1",
            {
                "M4_Suppressor",
                "M4_RISHndgrd",
                "UniversalFlashlight",
                "Battery9V"
            },
            "Mag_STANAG_60Rnd",
            "M68Optic",
            0,
            5,
            {
                "none"
            }));

        if (!FileExist(configRoot))
        {
            Print("[CSF] - '" + configRoot + "' does not exist, creating...");
            MakeDirectory(configRoot);
        }
        JsonFileLoader<CSFLoot>.JsonSaveFile(loot_path, loot);
    }
}