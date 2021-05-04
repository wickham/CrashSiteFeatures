modded class Wreck_UH1Y
{
    // TODO: WRONG MAX HEALTH
    void SetRandomItemHealth(EntityAI itemEnt, int minHealth = 1, int maxHealth = 100)
    {
        if (itemEnt)
        {
            itemEnt.SetHealth("", "", (float)Math.RandomInt(minHealth, maxHealth));
        }
    }

    override void EEInit()
    {
        super.EEInit();

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();
        if (!hcszConfig.g_HCSZDisableLogMessages)
        {
            Print("[HCSZ] Wreck_UH1Y - heli crash spawned at " + spawnPosition);
        }

        // EXCLUSION CHECK
        bool exclude_items = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        Print("[HCSZ] Excluded: " + hcszConfig.g_HCSZExcludedCrashSites);
        if (hcszConfig.g_HCSZExcludedCrashSites)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                if (!hcszConfig.g_HCSZDisableLogMessages)
                {
                    Print("[HCSZ] -----------------Name of Excluded Site to Check: '" + g_HCSZExcludedCrashSites.name + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_HCSZExcludedCrashSites.x;
                exclusion_pos[1] = g_HCSZExcludedCrashSites.y;
                exclusion_pos[2] = g_HCSZExcludedCrashSites.z;
                exclude_spawn_types = g_HCSZExcludedCrashSites.exclude_spawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] - Crash Site Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [HCSZ] - Exclude ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [HCSZ] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "items":
                            // [HCSZ] - Exclude ITEMS
                            exclude_items = true;
                            break;

                        case "zombies":
                            // [HCSZ] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [HCSZ] - Include ALL
                            exclude_items = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [HCSZ] - Default: EXCLUDE ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                    {
                        Print("[HCSZ] - Wreck_UH1Y - Name of Excluded Site Setup: '" + g_HCSZExcludedCrashSites.name + " - Exclude ~ Animals: " + exclude_animals + ", Items: " + exclude_items + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!hcszConfig.g_HCSZDisable_UH1Y_Zombies && !exclude_zombies)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + zombiesAmount + " Wreck_UH1Y zombies spawned.");
        }

        // Animals
        if (!hcszConfig.g_HCSZDisable_UH1Y_Animals && !exclude_animals)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + animalsAmount + " Wreck_UH1Y animals spawned.");
        }

        // Items
        if (!hcszConfig.g_HCSZDisable_UH1Y_Items && !exclude_items)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            float max_health = 500.0;
            float item_health;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int itemsAmount = Math.RandomInt(hcszConfig.g_HCSZItemsMin, hcszConfig.g_HCSZItemsMax);
            for (int k = 0; k < itemsAmount; k++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(Math.RandomInt(0, hcszConfig.g_HCSZSpawnableItemsList.Count()));
                item_to_spawn = g_HCSZSpawnableItemsList.item_type;
                // TODO: Check if item is valid
                // HERE
                if (hcszConfig.g_HCSZItemsRandomHealth)
                {
                    item_health = (float)Math.RandomInt(1, max_health);
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] RANDOM HEALTH! : '" + item_health + "'");
                }
                else
                {
                    item_health = max_health;
                }
                if (!hcszConfig.g_HCSZDisableLogMessages)
                    Print("[HCSZ] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFrom_UH1Y, hcszConfig.g_HCSZItemsMaxDistFrom_UH1Y), hcszConfig.g_HCSZZombieAndAnimalLifetime, item_health);
                SpawnAttachments(itemEnt, g_HCSZSpawnableItemsList.attachments_list, false);
            }
            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + itemsAmount + " Wreck_UH1Y items spawned.");
        }
    }
}

class Wreck_Mi8 extends House
{
};

modded class Wreck_Mi8
{
    void SetRandomItemHealth(EntityAI itemEnt, int minHealth = 1, int maxHealth = 100)
    {
        if (itemEnt)
        {
            itemEnt.SetHealth("", "", (float)Math.RandomInt(minHealth, maxHealth));
        }
    }

    override void EEInit()
    {
        super.EEInit();

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!hcszConfig.g_HCSZDisableLogMessages)
            Print("[HCSZ] Wreck_Mi8 - heli crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_items = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        Print("[HCSZ] Excluded: " + hcszConfig.g_HCSZExcludedCrashSites);
        if (hcszConfig.g_HCSZExcludedCrashSites)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                if (!hcszConfig.g_HCSZDisableLogMessages)
                {
                    Print("[HCSZ] -----------------Name of Excluded Site to Check: '" + g_HCSZExcludedCrashSites.name + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_HCSZExcludedCrashSites.x;
                exclusion_pos[1] = g_HCSZExcludedCrashSites.y;
                exclusion_pos[2] = g_HCSZExcludedCrashSites.z;
                exclude_spawn_types = g_HCSZExcludedCrashSites.exclude_spawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] - Crash Site Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [HCSZ] - Exclude ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [HCSZ] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "items":
                            // [HCSZ] - Exclude ITEMS
                            exclude_items = true;
                            break;

                        case "zombies":
                            // [HCSZ] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [HCSZ] - Include ALL
                            exclude_items = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [HCSZ] - Default: EXCLUDE ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                    {
                        Print("[HCSZ] - Wreck_Mi8 - Name of Excluded Site Setup: '" + g_HCSZExcludedCrashSites.name + " - Exclude ~ Animals: " + exclude_animals + ", Items: " + exclude_items + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!hcszConfig.g_HCSZDisable_Mi8_Zombies)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + zombiesAmount + " Wreck_Mi8 zombies spawned.");
        }

        // Animals
        if (!hcszConfig.g_HCSZDisable_Mi8_Animals)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + animalsAmount + " Wreck_Mi8 animals spawned.");
        }

        // Items
        if (!hcszConfig.g_HCSZDisable_Mi8_Items && !exclude_items)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            float max_health = 500.0;
            float item_health;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int itemsAmount = Math.RandomInt(hcszConfig.g_HCSZItemsMin, hcszConfig.g_HCSZItemsMax);
            for (int k = 0; k < itemsAmount; k++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(Math.RandomInt(0, hcszConfig.g_HCSZSpawnableItemsList.Count()));
                item_to_spawn = g_HCSZSpawnableItemsList.item_type;
                // TODO: Check if item is valid
                // HERE
                if (hcszConfig.g_HCSZItemsRandomHealth)
                {
                    item_health = (float)Math.RandomInt(1, max_health);
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] RANDOM HEALTH! : '" + item_health + "'");
                }
                else
                {
                    item_health = max_health;
                }
                if (!hcszConfig.g_HCSZDisableLogMessages)
                    Print("[HCSZ] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFrom_UH1Y, hcszConfig.g_HCSZItemsMaxDistFrom_UH1Y), hcszConfig.g_HCSZZombieAndAnimalLifetime, item_health);
                SpawnAttachments(itemEnt, g_HCSZSpawnableItemsList.attachments_list, false);
            }
            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + itemsAmount + " Wreck_Mi8 items spawned.");
        }
    }
}

modded class crashed_Wreck_C130J
{
    void SetRandomItemHealth(EntityAI itemEnt, int minHealth = 1, int maxHealth = 100)
    {
        if (itemEnt)
        {
            itemEnt.SetHealth("", "", (float)Math.RandomInt(minHealth, maxHealth));
        }
    }

    override void EEInit()
    {
        super.EEInit();

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!hcszConfig.g_HCSZDisableLogMessages)
            Print("[HCSZ] New_crashed_Wreck_C130J - Plane Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_items = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        Print("[HCSZ] Excluded: " + hcszConfig.g_HCSZExcludedCrashSites);
        if (hcszConfig.g_HCSZExcludedCrashSites)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                if (!hcszConfig.g_HCSZDisableLogMessages)
                {
                    Print("[HCSZ] -----------------Name of Excluded Site to Check: '" + g_HCSZExcludedCrashSites.name + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_HCSZExcludedCrashSites.x;
                exclusion_pos[1] = g_HCSZExcludedCrashSites.y;
                exclusion_pos[2] = g_HCSZExcludedCrashSites.z;
                exclude_spawn_types = g_HCSZExcludedCrashSites.exclude_spawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] - Crash Site Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [HCSZ] - Exclude ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [HCSZ] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "items":
                            // [HCSZ] - Exclude ITEMS
                            exclude_items = true;
                            break;

                        case "zombies":
                            // [HCSZ] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [HCSZ] - Include ALL
                            exclude_items = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [HCSZ] - Default: EXCLUDE ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                    {
                        Print("[HCSZ] - New_crashed_Wreck_C130J - Name of Excluded Site Setup: '" + g_HCSZExcludedCrashSites.name + " - Exclude ~ Animals: " + exclude_animals + ", Items: " + exclude_items + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!hcszConfig.g_HCSZDisable_Wreck_C130J_Zombies)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + zombiesAmount + " New_crashed_Wreck_C130J zombies spawned.");
        }

        // Animals
        if (!hcszConfig.g_HCSZDisable_Wreck_C130J_Animals)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + animalsAmount + " New_crashed_Wreck_C130J animals spawned.");
        }
        // Items
        if (!hcszConfig.g_HCSZDisable_Wreck_C130J_Items && !exclude_items)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            float max_health = 500.0;
            float item_health;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int itemsAmount = Math.RandomInt(hcszConfig.g_HCSZItemsMin, hcszConfig.g_HCSZItemsMax);
            for (int k = 0; k < itemsAmount; k++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(Math.RandomInt(0, hcszConfig.g_HCSZSpawnableItemsList.Count()));
                item_to_spawn = g_HCSZSpawnableItemsList.item_type;
                // TODO: Check if item is valid
                // HERE
                if (hcszConfig.g_HCSZItemsRandomHealth)
                {
                    item_health = (float)Math.RandomInt(1, max_health);
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] RANDOM HEALTH! : '" + item_health + "'");
                }
                else
                {
                    item_health = max_health;
                }
                if (!hcszConfig.g_HCSZDisableLogMessages)
                    Print("[HCSZ] -----------------" + item_to_spawn + "-----------------");
                // TODO: Change min distance
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFrom_C130, hcszConfig.g_HCSZItemsMaxDistFrom_C130), hcszConfig.g_HCSZZombieAndAnimalLifetime, item_health);
                SpawnAttachments(itemEnt, g_HCSZSpawnableItemsList.attachments_list, false);
            }
            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + itemsAmount + " New_crashed_Wreck_C130J items spawned.");
        }
    }
}

class crashed_Wreck_C130_Camo extends House
{
};
modded class crashed_Wreck_C130_Camo
{
    void SetRandomItemHealth(EntityAI itemEnt, int minHealth = 1, int maxHealth = 100)
    {
        if (itemEnt)
        {
            itemEnt.SetHealth("", "", (float)Math.RandomInt(minHealth, maxHealth));
        }
    }

    override void EEInit()
    {
        super.EEInit();

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!hcszConfig.g_HCSZDisableLogMessages)
            Print("[HCSZ] New_crashed_Wreck_C130_Camo - Plane Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_items = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        Print("[HCSZ] Excluded: " + hcszConfig.g_HCSZExcludedCrashSites);
        if (hcszConfig.g_HCSZExcludedCrashSites)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                if (!hcszConfig.g_HCSZDisableLogMessages)
                {
                    Print("[HCSZ] -----------------Name of Excluded Site to Check: '" + g_HCSZExcludedCrashSites.name + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_HCSZExcludedCrashSites.x;
                exclusion_pos[1] = g_HCSZExcludedCrashSites.y;
                exclusion_pos[2] = g_HCSZExcludedCrashSites.z;
                exclude_spawn_types = g_HCSZExcludedCrashSites.exclude_spawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] - Crash Site Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [HCSZ] - Exclude ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [HCSZ] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "items":
                            // [HCSZ] - Exclude ITEMS
                            exclude_items = true;
                            break;

                        case "zombies":
                            // [HCSZ] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [HCSZ] - Include ALL
                            exclude_items = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [HCSZ] - Default: EXCLUDE ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                    {
                        Print("[HCSZ] - crashed_Wreck_C130_Camo - Name of Excluded Site Setup: '" + g_HCSZExcludedCrashSites.name + " - Exclude ~ Animals: " + exclude_animals + ", Items: " + exclude_items + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!hcszConfig.g_HCSZDisable_Wreck_C130_Camo_Zombies)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + zombiesAmount + " New_crashed_Wreck_C130_Camo zombies spawned.");
        }

        // Animals
        if (!hcszConfig.g_HCSZDisable_Wreck_C130_Camo_Animals)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + animalsAmount + " New_crashed_Wreck_C130_Camo animals spawned.");
        }
        // Items
        if (!hcszConfig.g_HCSZDisable_Wreck_C130_Camo_Items && !exclude_items)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            float max_health = 500.0;
            float item_health;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int itemsAmount = Math.RandomInt(hcszConfig.g_HCSZItemsMin, hcszConfig.g_HCSZItemsMax);
            for (int k = 0; k < itemsAmount; k++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(Math.RandomInt(0, hcszConfig.g_HCSZSpawnableItemsList.Count()));
                item_to_spawn = g_HCSZSpawnableItemsList.item_type;
                // TODO: Check if item is valid
                // HERE
                if (hcszConfig.g_HCSZItemsRandomHealth)
                {
                    item_health = (float)Math.RandomInt(1, max_health);
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] RANDOM HEALTH! : '" + item_health + "'");
                }
                else
                {
                    item_health = max_health;
                }
                if (!hcszConfig.g_HCSZDisableLogMessages)
                    Print("[HCSZ] -----------------" + item_to_spawn + "-----------------");
                // TODO: Change min distance
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFrom_C130, hcszConfig.g_HCSZItemsMaxDistFrom_C130), hcszConfig.g_HCSZZombieAndAnimalLifetime, item_health);
                SpawnAttachments(itemEnt, g_HCSZSpawnableItemsList.attachments_list, false);
            }
            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + itemsAmount + " crashed_Wreck_C130_Camo items spawned.");
        }
    }
}

modded class crashed_Wreck_Mi8_CDF
{
    void SetRandomItemHealth(EntityAI itemEnt, int minHealth = 1, int maxHealth = 100)
    {
        if (itemEnt)
        {
            itemEnt.SetHealth("", "", (float)Math.RandomInt(minHealth, maxHealth));
        }
    }

    override void EEInit()
    {
        super.EEInit();

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!hcszConfig.g_HCSZDisableLogMessages)
            Print("[HCSZ] New_crashed_Wreck_Mi8_CDF - Heli Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_items = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        Print("[HCSZ] Excluded: " + hcszConfig.g_HCSZExcludedCrashSites);
        if (hcszConfig.g_HCSZExcludedCrashSites)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                if (!hcszConfig.g_HCSZDisableLogMessages)
                {
                    Print("[HCSZ] -----------------Name of Excluded Site to Check: '" + g_HCSZExcludedCrashSites.name + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_HCSZExcludedCrashSites.x;
                exclusion_pos[1] = g_HCSZExcludedCrashSites.y;
                exclusion_pos[2] = g_HCSZExcludedCrashSites.z;
                exclude_spawn_types = g_HCSZExcludedCrashSites.exclude_spawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] - Crash Site Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [HCSZ] - Exclude ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [HCSZ] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "items":
                            // [HCSZ] - Exclude ITEMS
                            exclude_items = true;
                            break;

                        case "zombies":
                            // [HCSZ] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [HCSZ] - Include ALL
                            exclude_items = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [HCSZ] - Default: EXCLUDE ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                    {
                        Print("[HCSZ] - crashed_Wreck_Mi8_CDF - Name of Excluded Site Setup: '" + g_HCSZExcludedCrashSites.name + " - Exclude ~ Animals: " + exclude_animals + ", Items: " + exclude_items + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!hcszConfig.g_HCSZDisable_Wreck_Mi8_CDF_Zombies)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + zombiesAmount + " New_crashed_Wreck_Mi8_CDF zombies spawned.");
        }

        // Animals
        if (!hcszConfig.g_HCSZDisable_Wreck_Mi8_CDF_Animals)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + animalsAmount + " New_crashed_Wreck_Mi8_CDF animals spawned.");
        }
        // Items
        if (!hcszConfig.g_HCSZDisable_Wreck_Mi8_CDF_Items && !exclude_items)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            float max_health = 500.0;
            float item_health;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int itemsAmount = Math.RandomInt(hcszConfig.g_HCSZItemsMin, hcszConfig.g_HCSZItemsMax);
            for (int k = 0; k < itemsAmount; k++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(Math.RandomInt(0, hcszConfig.g_HCSZSpawnableItemsList.Count()));
                item_to_spawn = g_HCSZSpawnableItemsList.item_type;
                // TODO: Check if item is valid
                // HERE
                if (hcszConfig.g_HCSZItemsRandomHealth)
                {
                    item_health = (float)Math.RandomInt(1, max_health);
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] RANDOM HEALTH! : '" + item_health + "'");
                }
                else
                {
                    item_health = max_health;
                }
                if (!hcszConfig.g_HCSZDisableLogMessages)
                    Print("[HCSZ] -----------------" + item_to_spawn + "-----------------");
                // TODO: Change min distance
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFrom_C130, hcszConfig.g_HCSZItemsMaxDistFrom_C130), hcszConfig.g_HCSZZombieAndAnimalLifetime, item_health);
                SpawnAttachments(itemEnt, g_HCSZSpawnableItemsList.attachments_list, false);
            }
            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + itemsAmount + " crashed_Wreck_Mi8_CDF items spawned.");
        }
    }
}

modded class crashed_Wreck_Mi8_RU
{
    void SetRandomItemHealth(EntityAI itemEnt, int minHealth = 1, int maxHealth = 100)
    {
        if (itemEnt)
        {
            itemEnt.SetHealth("", "", (float)Math.RandomInt(minHealth, maxHealth));
        }
    }

    override void EEInit()
    {
        super.EEInit();

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!hcszConfig.g_HCSZDisableLogMessages)
            Print("[HCSZ] New_crashed_Wreck_Mi8_RU - Heli Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_items = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        Print("[HCSZ] Excluded: " + hcszConfig.g_HCSZExcludedCrashSites);
        if (hcszConfig.g_HCSZExcludedCrashSites)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                if (!hcszConfig.g_HCSZDisableLogMessages)
                {
                    Print("[HCSZ] -----------------Name of Excluded Site to Check: '" + g_HCSZExcludedCrashSites.name + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_HCSZExcludedCrashSites.x;
                exclusion_pos[1] = g_HCSZExcludedCrashSites.y;
                exclusion_pos[2] = g_HCSZExcludedCrashSites.z;
                exclude_spawn_types = g_HCSZExcludedCrashSites.exclude_spawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] - Crash Site Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [HCSZ] - Exclude ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [HCSZ] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "items":
                            // [HCSZ] - Exclude ITEMS
                            exclude_items = true;
                            break;

                        case "zombies":
                            // [HCSZ] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [HCSZ] - Include ALL
                            exclude_items = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [HCSZ] - Default: EXCLUDE ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                    {
                        Print("[HCSZ] - crashed_Wreck_Mi8_RU - Name of Excluded Site Setup: '" + g_HCSZExcludedCrashSites.name + " - Exclude ~ Animals: " + exclude_animals + ", Items: " + exclude_items + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!hcszConfig.g_HCSZDisable_Wreck_Mi8_RU_Zombies)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + zombiesAmount + " New_crashed_Wreck_Mi8_RU zombies spawned.");
        }

        // Animals
        if (!hcszConfig.g_HCSZDisable_Wreck_Mi8_RU_Animals)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + animalsAmount + " New_crashed_Wreck_Mi8_RU animals spawned.");
        }
        // Items
        if (!hcszConfig.g_HCSZDisable_Wreck_Mi8_RU_Items && !exclude_items)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            float max_health = 500.0;
            float item_health;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int itemsAmount = Math.RandomInt(hcszConfig.g_HCSZItemsMin, hcszConfig.g_HCSZItemsMax);
            for (int k = 0; k < itemsAmount; k++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(Math.RandomInt(0, hcszConfig.g_HCSZSpawnableItemsList.Count()));
                item_to_spawn = g_HCSZSpawnableItemsList.item_type;
                // TODO: Check if item is valid
                // HERE
                if (hcszConfig.g_HCSZItemsRandomHealth)
                {
                    item_health = (float)Math.RandomInt(1, max_health);
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] RANDOM HEALTH! : '" + item_health + "'");
                }
                else
                {
                    item_health = max_health;
                }
                if (!hcszConfig.g_HCSZDisableLogMessages)
                    Print("[HCSZ] -----------------" + item_to_spawn + "-----------------");
                // TODO: Change min distance
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFrom_C130, hcszConfig.g_HCSZItemsMaxDistFrom_C130), hcszConfig.g_HCSZZombieAndAnimalLifetime, item_health);
                SpawnAttachments(itemEnt, g_HCSZSpawnableItemsList.attachments_list, false);
            }
            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + itemsAmount + " crashed_Wreck_Mi8_RU items spawned.");
        }
    }
}

modded class crashed_Wreck_UH1Y
{
    void SetRandomItemHealth(EntityAI itemEnt, int minHealth = 1, int maxHealth = 100)
    {
        if (itemEnt)
        {
            itemEnt.SetHealth("", "", (float)Math.RandomInt(minHealth, maxHealth));
        }
    }

    override void EEInit()
    {
        super.EEInit();

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!hcszConfig.g_HCSZDisableLogMessages)
            Print("[HCSZ] New_crashed_Wreck_UH1Y - Heli Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_items = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        Print("[HCSZ] Excluded: " + hcszConfig.g_HCSZExcludedCrashSites);
        if (hcszConfig.g_HCSZExcludedCrashSites)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                if (!hcszConfig.g_HCSZDisableLogMessages)
                {
                    Print("[HCSZ] -----------------Name of Excluded Site to Check: '" + g_HCSZExcludedCrashSites.name + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_HCSZExcludedCrashSites.x;
                exclusion_pos[1] = g_HCSZExcludedCrashSites.y;
                exclusion_pos[2] = g_HCSZExcludedCrashSites.z;
                exclude_spawn_types = g_HCSZExcludedCrashSites.exclude_spawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] - Crash Site Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [HCSZ] - Exclude ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [HCSZ] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "items":
                            // [HCSZ] - Exclude ITEMS
                            exclude_items = true;
                            break;

                        case "zombies":
                            // [HCSZ] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [HCSZ] - Include ALL
                            exclude_items = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [HCSZ] - Default: EXCLUDE ALL
                            exclude_items = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                    {
                        Print("[HCSZ] - crashed_Wreck_UH1Y - Name of Excluded Site Setup: '" + g_HCSZExcludedCrashSites.name + " - Exclude ~ Animals: " + exclude_animals + ", Items: " + exclude_items + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!hcszConfig.g_HCSZDisable_Wreck_UH1Y_Zombies)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + zombiesAmount + " New_crashed_Wreck_UH1Y zombies spawned.");
        }

        // Animals
        if (!hcszConfig.g_HCSZDisable_Wreck_UH1Y_Animals)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + animalsAmount + " New_crashed_Wreck_UH1Y animals spawned.");
        }
        // Items
        if (!hcszConfig.g_HCSZDisable_Wreck_UH1Y_Items && !exclude_items)
        {
            if (!hcszConfig.g_HCSZDisableLogMessages)
            {
                Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            float max_health = 500.0;
            float item_health;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int itemsAmount = Math.RandomInt(hcszConfig.g_HCSZItemsMin, hcszConfig.g_HCSZItemsMax);
            for (int k = 0; k < itemsAmount; k++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(Math.RandomInt(0, hcszConfig.g_HCSZSpawnableItemsList.Count()));
                item_to_spawn = g_HCSZSpawnableItemsList.item_type;
                // TODO: Check if item is valid
                // HERE
                if (hcszConfig.g_HCSZItemsRandomHealth)
                {
                    item_health = (float)Math.RandomInt(1, max_health);
                    if (!hcszConfig.g_HCSZDisableLogMessages)
                        Print("[HCSZ] RANDOM HEALTH! : '" + item_health + "'");
                }
                else
                {
                    item_health = max_health;
                }
                if (!hcszConfig.g_HCSZDisableLogMessages)
                    Print("[HCSZ] -----------------" + item_to_spawn + "-----------------");
                // TODO: Change min distance
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFrom_C130, hcszConfig.g_HCSZItemsMaxDistFrom_C130), hcszConfig.g_HCSZZombieAndAnimalLifetime, item_health);
                SpawnAttachments(itemEnt, g_HCSZSpawnableItemsList.attachments_list, false);
            }
            if (!hcszConfig.g_HCSZDisableLogMessages)
                Print("[HCSZ] " + itemsAmount + " crashed_Wreck_UH1Y items spawned.");
        }
    }
}
