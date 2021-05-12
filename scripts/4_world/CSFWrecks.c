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

        CSFConfig csfConfig = GetDayZGame().GetCSFConfig();
        CSFLoot csfLoot = GetDayZGame().GetCSFLoot();
        if (csfConfig == NULL || csfLoot == NULL)
            return;

        vector spawnPosition = this.GetPosition();
        if (!csfConfig.g_CSFDisableLogMessages)
        {
            Print("[CSF] Wreck_UH1Y - heli crash spawned at " + spawnPosition);
        }

        // SPAWNER EXCLUSION CHECK
        bool exclude_loot = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;

        if (csfConfig.g_CSFExcludedCrashSites)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < csfConfig.g_CSFExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_CSFExcludedCrashSites = csfConfig.g_CSFExcludedCrashSites.Get(exclude_me_index);
                if (!csfConfig.g_CSFDisableLogMessages)
                {
                    Print("[CSF] --- Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_CSFExcludedCrashSites.X;
                exclusion_pos[1] = g_CSFExcludedCrashSites.Y;
                exclusion_pos[2] = g_CSFExcludedCrashSites.Z;
                exclude_spawn_types = g_CSFExcludedCrashSites.ExcludedSpawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] - Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [CSF] - Exclude ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [CSF] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "loot":
                            // [CSF] - Exclude loot
                            exclude_loot = true;
                            break;

                        case "zombies":
                            // [CSF] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [CSF] - Include ALL
                            exclude_loot = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [CSF] - Default: EXCLUDE ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] - Wreck_UH1Y - List of Excluded Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!csfConfig.g_CSFDisable_UH1Y_Zombies && !exclude_zombies)
        {
            int zombiesAmount = Math.RandomInt(csfConfig.g_CSFZombiesMin, csfConfig.g_CSFZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFZombieMinDistFromHeli, csfConfig.g_CSFZombieMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + zombiesAmount + " Wreck_UH1Y zombies spawned.");
        }

        // Animals
        if (!csfConfig.g_CSFDisable_UH1Y_Animals && !exclude_animals)
        {
            int animalsAmount = Math.RandomInt(csfConfig.g_CSFAnimalsMin, csfConfig.g_CSFAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFAnimalsMinDistFromHeli, csfConfig.g_CSFAnimalsMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + animalsAmount + " Wreck_UH1Y animals spawned.");
        }

        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_UH1Y_Loot && !exclude_loot)
        {
            // TODO: Find how to grab max health of item to spawn
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            int adjusted_items_spawned = 0;
            bool include_loot = true;
            // Spawn system iterator
            int total_loot_amount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax + 1);
            for (int total_items_spawned = 0; total_items_spawned < total_loot_amount; item_index++)
            {
                adjusted_items_spawned = ValidateItemsToSpawn(
                    csfLoot.g_CSFSpawnableLootList.Get(item_index),
                    total_loot_amount,
                    csfLoot.g_CSFLootRandomHealth,
                    csfLoot.g_CSFLootLifetime,
                    spawnPosition,
                    csfLoot.g_CSFLootMinDistFrom_UH1Y,
                    csfLoot.g_CSFLootMaxDistFrom_UH1Y,
                    total_items_spawned,
                    "UH1Y",
                    csfConfig.g_CSFDisableLogMessages);
                if (adjusted_items_spawned == -1)
                    break;
                else
                    total_items_spawned = adjusted_items_spawned;
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + total_loot_amount + "' Wreck_UH1Y loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + total_items_spawned + "'");
            }
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

        CSFConfig csfConfig = GetDayZGame().GetCSFConfig();
        CSFLoot csfLoot = GetDayZGame().GetCSFLoot();
        if (csfConfig == NULL || csfLoot == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!csfConfig.g_CSFDisableLogMessages)
            Print("[CSF] Wreck_Mi8 - heli crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_loot = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;

        if (csfConfig.g_CSFExcludedCrashSites)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < csfConfig.g_CSFExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_CSFExcludedCrashSites = csfConfig.g_CSFExcludedCrashSites.Get(exclude_me_index);
                if (!csfConfig.g_CSFDisableLogMessages)
                {
                    Print("[CSF] --- Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_CSFExcludedCrashSites.X;
                exclusion_pos[1] = g_CSFExcludedCrashSites.Y;
                exclusion_pos[2] = g_CSFExcludedCrashSites.Z;
                exclude_spawn_types = g_CSFExcludedCrashSites.ExcludedSpawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] - Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [CSF] - Exclude ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [CSF] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "loot":
                            // [CSF] - Exclude ITEMS
                            exclude_loot = true;
                            break;

                        case "zombies":
                            // [CSF] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [CSF] - Include ALL
                            exclude_loot = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [CSF] - Default: EXCLUDE ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] - Wreck_Mi8 - List of Excluded Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!csfConfig.g_CSFDisable_Mi8_Zombies)
        {
            int zombiesAmount = Math.RandomInt(csfConfig.g_CSFZombiesMin, csfConfig.g_CSFZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFZombieMinDistFromHeli, csfConfig.g_CSFZombieMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + zombiesAmount + " Wreck_Mi8 zombies spawned.");
        }

        // Animals
        if (!csfConfig.g_CSFDisable_Mi8_Animals)
        {
            int animalsAmount = Math.RandomInt(csfConfig.g_CSFAnimalsMin, csfConfig.g_CSFAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFAnimalsMinDistFromHeli, csfConfig.g_CSFAnimalsMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + animalsAmount + " Wreck_Mi8 animals spawned.");
        }

        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_Mi8_Loot && !exclude_loot)
        {
            // TODO: Find how to grab max health of item to spawn
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            int adjusted_items_spawned = 0;
            bool include_loot = true;
            // Spawn system iterator
            int total_loot_amount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax + 1);
            for (int total_items_spawned = 0; total_items_spawned < total_loot_amount; item_index++)
            {
                adjusted_items_spawned = ValidateItemsToSpawn(
                    csfLoot.g_CSFSpawnableLootList.Get(item_index),
                    total_loot_amount,
                    csfLoot.g_CSFLootRandomHealth,
                    csfLoot.g_CSFLootLifetime,
                    spawnPosition,
                    csfLoot.g_CSFLootMinDistFrom_Mi8,
                    csfLoot.g_CSFLootMaxDistFrom_Mi8,
                    total_items_spawned,
                    "Mi8",
                    csfConfig.g_CSFDisableLogMessages);
                if (adjusted_items_spawned == -1)
                    break;
                else
                    total_items_spawned = adjusted_items_spawned;
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + total_loot_amount + "' Wreck_Mi8 loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + total_items_spawned + "'");
            }
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

        CSFConfig csfConfig = GetDayZGame().GetCSFConfig();
        CSFLoot csfLoot = GetDayZGame().GetCSFLoot();
        if (csfConfig == NULL || csfLoot == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!csfConfig.g_CSFDisableLogMessages)
            Print("[CSF] crashed_Wreck_C130J - Plane Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_loot = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;

        if (csfConfig.g_CSFExcludedCrashSites)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < csfConfig.g_CSFExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_CSFExcludedCrashSites = csfConfig.g_CSFExcludedCrashSites.Get(exclude_me_index);
                if (!csfConfig.g_CSFDisableLogMessages)
                {
                    Print("[CSF] --- Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_CSFExcludedCrashSites.X;
                exclusion_pos[1] = g_CSFExcludedCrashSites.Y;
                exclusion_pos[2] = g_CSFExcludedCrashSites.Z;
                exclude_spawn_types = g_CSFExcludedCrashSites.ExcludedSpawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] - Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [CSF] - Exclude ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [CSF] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "loot":
                            // [CSF] - Exclude ITEMS
                            exclude_loot = true;
                            break;

                        case "zombies":
                            // [CSF] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [CSF] - Include ALL
                            exclude_loot = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [CSF] - Default: EXCLUDE ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] - crashed_Wreck_C130J - List of Excluded Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!csfConfig.g_CSFDisable_Wreck_C130J_Zombies)
        {
            int zombiesAmount = Math.RandomInt(csfConfig.g_CSFZombiesMin, csfConfig.g_CSFZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFZombieMinDistFromHeli, csfConfig.g_CSFZombieMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + zombiesAmount + " crashed_Wreck_C130J zombies spawned.");
        }

        // Animals
        if (!csfConfig.g_CSFDisable_Wreck_C130J_Animals)
        {
            int animalsAmount = Math.RandomInt(csfConfig.g_CSFAnimalsMin, csfConfig.g_CSFAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFAnimalsMinDistFromHeli, csfConfig.g_CSFAnimalsMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + animalsAmount + " crashed_Wreck_C130J animals spawned.");
        }

        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_Wreck_C130J_Loot && !exclude_loot)
        {
            // TODO: Find how to grab max health of item to spawn
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            int adjusted_items_spawned = 0;
            bool include_loot = true;
            // Spawn system iterator
            int total_loot_amount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax + 1);
            for (int total_items_spawned = 0; total_items_spawned < total_loot_amount; item_index++)
            {
                adjusted_items_spawned = ValidateItemsToSpawn(
                    csfLoot.g_CSFSpawnableLootList.Get(item_index),
                    total_loot_amount,
                    csfLoot.g_CSFLootRandomHealth,
                    csfLoot.g_CSFLootLifetime,
                    spawnPosition,
                    csfLoot.g_CSFLootMinDistFrom_C130,
                    csfLoot.g_CSFLootMaxDistFrom_C130,
                    total_items_spawned,
                    "C130",
                    csfConfig.g_CSFDisableLogMessages);
                if (adjusted_items_spawned == -1)
                    break;
                else
                    total_items_spawned = adjusted_items_spawned;
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + total_loot_amount + "' crashed_Wreck_C130J loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + total_items_spawned + "'");
            }
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

        CSFConfig csfConfig = GetDayZGame().GetCSFConfig();
        CSFLoot csfLoot = GetDayZGame().GetCSFLoot();
        if (csfConfig == NULL || csfLoot == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!csfConfig.g_CSFDisableLogMessages)
            Print("[CSF] crashed_Wreck_C130_Camo - Plane Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_loot = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;

        if (csfConfig.g_CSFExcludedCrashSites)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < csfConfig.g_CSFExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_CSFExcludedCrashSites = csfConfig.g_CSFExcludedCrashSites.Get(exclude_me_index);
                if (!csfConfig.g_CSFDisableLogMessages)
                {
                    Print("[CSF] --- Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_CSFExcludedCrashSites.X;
                exclusion_pos[1] = g_CSFExcludedCrashSites.Y;
                exclusion_pos[2] = g_CSFExcludedCrashSites.Z;
                exclude_spawn_types = g_CSFExcludedCrashSites.ExcludedSpawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] - Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [CSF] - Exclude ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [CSF] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "loot":
                            // [CSF] - Exclude ITEMS
                            exclude_loot = true;
                            break;

                        case "zombies":
                            // [CSF] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [CSF] - Include ALL
                            exclude_loot = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [CSF] - Default: EXCLUDE ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] - crashed_Wreck_C130_Camo - List of Excluded Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!csfConfig.g_CSFDisable_Wreck_C130_Camo_Zombies)
        {
            int zombiesAmount = Math.RandomInt(csfConfig.g_CSFZombiesMin, csfConfig.g_CSFZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFZombieMinDistFromHeli, csfConfig.g_CSFZombieMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + zombiesAmount + " crashed_Wreck_C130_Camo zombies spawned.");
        }

        // Animals
        if (!csfConfig.g_CSFDisable_Wreck_C130_Camo_Animals)
        {
            int animalsAmount = Math.RandomInt(csfConfig.g_CSFAnimalsMin, csfConfig.g_CSFAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFAnimalsMinDistFromHeli, csfConfig.g_CSFAnimalsMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + animalsAmount + " crashed_Wreck_C130_Camo animals spawned.");
        }

        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_Wreck_C130_Camo_Loot && !exclude_loot)
        {
            // TODO: Find how to grab max health of item to spawn
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            int adjusted_items_spawned = 0;
            bool include_loot = true;
            // Spawn system iterator
            int total_loot_amount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax + 1);
            for (int total_items_spawned = 0; total_items_spawned < total_loot_amount; item_index++)
            {
                adjusted_items_spawned = ValidateItemsToSpawn(
                    csfLoot.g_CSFSpawnableLootList.Get(item_index),
                    total_loot_amount,
                    csfLoot.g_CSFLootRandomHealth,
                    csfLoot.g_CSFLootLifetime,
                    spawnPosition,
                    csfLoot.g_CSFLootMinDistFrom_C130,
                    csfLoot.g_CSFLootMaxDistFrom_C130,
                    total_items_spawned,
                    "C130",
                    csfConfig.g_CSFDisableLogMessages);
                if (adjusted_items_spawned == -1)
                    break;
                else
                    total_items_spawned = adjusted_items_spawned;
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + total_loot_amount + "' crashed_Wreck_C130_Camo loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + total_items_spawned + "'");
            }
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

        CSFConfig csfConfig = GetDayZGame().GetCSFConfig();
        CSFLoot csfLoot = GetDayZGame().GetCSFLoot();
        if (csfConfig == NULL || csfLoot == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!csfConfig.g_CSFDisableLogMessages)
            Print("[CSF] crashed_Wreck_Mi8_CDF - Heli Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_loot = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;

        if (csfConfig.g_CSFExcludedCrashSites)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < csfConfig.g_CSFExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_CSFExcludedCrashSites = csfConfig.g_CSFExcludedCrashSites.Get(exclude_me_index);
                if (!csfConfig.g_CSFDisableLogMessages)
                {
                    Print("[CSF] --- Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_CSFExcludedCrashSites.X;
                exclusion_pos[1] = g_CSFExcludedCrashSites.Y;
                exclusion_pos[2] = g_CSFExcludedCrashSites.Z;
                exclude_spawn_types = g_CSFExcludedCrashSites.ExcludedSpawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] - Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [CSF] - Exclude ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [CSF] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "loot":
                            // [CSF] - Exclude ITEMS
                            exclude_loot = true;
                            break;

                        case "zombies":
                            // [CSF] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [CSF] - Include ALL
                            exclude_loot = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [CSF] - Default: EXCLUDE ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] - crashed_Wreck_Mi8_CDF - List of Excluded Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!csfConfig.g_CSFDisable_Wreck_Mi8_CDF_Zombies)
        {
            int zombiesAmount = Math.RandomInt(csfConfig.g_CSFZombiesMin, csfConfig.g_CSFZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFZombieMinDistFromHeli, csfConfig.g_CSFZombieMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + zombiesAmount + " crashed_Wreck_Mi8_CDF zombies spawned.");
        }

        // Animals
        if (!csfConfig.g_CSFDisable_Wreck_Mi8_CDF_Animals)
        {
            int animalsAmount = Math.RandomInt(csfConfig.g_CSFAnimalsMin, csfConfig.g_CSFAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFAnimalsMinDistFromHeli, csfConfig.g_CSFAnimalsMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + animalsAmount + " crashed_Wreck_Mi8_CDF animals spawned.");
        }
        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_Wreck_Mi8_CDF_Loot && !exclude_loot)
        {
            // TODO: Find how to grab max health of item to spawn
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            int adjusted_items_spawned = 0;
            bool include_loot = true;
            // Spawn system iterator
            int total_loot_amount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax + 1);
            for (int total_items_spawned = 0; total_items_spawned < total_loot_amount; item_index++)
            {
                adjusted_items_spawned = ValidateItemsToSpawn(
                    csfLoot.g_CSFSpawnableLootList.Get(item_index),
                    total_loot_amount,
                    csfLoot.g_CSFLootRandomHealth,
                    csfLoot.g_CSFLootLifetime,
                    spawnPosition,
                    csfLoot.g_CSFLootMinDistFrom_Mi8,
                    csfLoot.g_CSFLootMaxDistFrom_Mi8,
                    total_items_spawned,
                    "C130",
                    csfConfig.g_CSFDisableLogMessages);
                if (adjusted_items_spawned == -1)
                    break;
                else
                    total_items_spawned = adjusted_items_spawned;
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + total_loot_amount + "' crashed_Wreck_Mi8_CDF loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + total_items_spawned + "'");
            }
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

        CSFConfig csfConfig = GetDayZGame().GetCSFConfig();
        CSFLoot csfLoot = GetDayZGame().GetCSFLoot();
        if (csfConfig == NULL || csfLoot == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!csfConfig.g_CSFDisableLogMessages)
            Print("[CSF] crashed_Wreck_Mi8_RU - Heli Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_loot = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;

        if (csfConfig.g_CSFExcludedCrashSites)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < csfConfig.g_CSFExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_CSFExcludedCrashSites = csfConfig.g_CSFExcludedCrashSites.Get(exclude_me_index);
                if (!csfConfig.g_CSFDisableLogMessages)
                {
                    Print("[CSF] --- Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_CSFExcludedCrashSites.X;
                exclusion_pos[1] = g_CSFExcludedCrashSites.Y;
                exclusion_pos[2] = g_CSFExcludedCrashSites.Z;
                exclude_spawn_types = g_CSFExcludedCrashSites.ExcludedSpawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] - Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [CSF] - Exclude ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [CSF] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "loot":
                            // [CSF] - Exclude ITEMS
                            exclude_loot = true;
                            break;

                        case "zombies":
                            // [CSF] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [CSF] - Include ALL
                            exclude_loot = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [CSF] - Default: EXCLUDE ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] - crashed_Wreck_Mi8_RU - List of Excluded Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!csfConfig.g_CSFDisable_Wreck_Mi8_RU_Zombies)
        {
            int zombiesAmount = Math.RandomInt(csfConfig.g_CSFZombiesMin, csfConfig.g_CSFZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFZombieMinDistFromHeli, csfConfig.g_CSFZombieMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + zombiesAmount + " crashed_Wreck_Mi8_RU zombies spawned.");
        }

        // Animals
        if (!csfConfig.g_CSFDisable_Wreck_Mi8_RU_Animals)
        {
            int animalsAmount = Math.RandomInt(csfConfig.g_CSFAnimalsMin, csfConfig.g_CSFAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFAnimalsMinDistFromHeli, csfConfig.g_CSFAnimalsMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + animalsAmount + " crashed_Wreck_Mi8_RU animals spawned.");
        }
        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_Wreck_Mi8_RU_Loot && !exclude_loot)
        {
            // TODO: Find how to grab max health of item to spawn
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            int adjusted_items_spawned = 0;
            bool include_loot = true;
            // Spawn system iterator
            int total_loot_amount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax + 1);
            for (int total_items_spawned = 0; total_items_spawned < total_loot_amount; item_index++)
            {
                adjusted_items_spawned = ValidateItemsToSpawn(
                    csfLoot.g_CSFSpawnableLootList.Get(item_index),
                    total_loot_amount,
                    csfLoot.g_CSFLootRandomHealth,
                    csfLoot.g_CSFLootLifetime,
                    spawnPosition,
                    csfLoot.g_CSFLootMinDistFrom_Mi8,
                    csfLoot.g_CSFLootMaxDistFrom_Mi8,
                    total_items_spawned,
                    "Mi8",
                    csfConfig.g_CSFDisableLogMessages);
                if (adjusted_items_spawned == -1)
                    break;
                else
                    total_items_spawned = adjusted_items_spawned;
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + total_loot_amount + "' crashed_Wreck_Mi8_RU loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + total_items_spawned + "'");
            }
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

        CSFConfig csfConfig = GetDayZGame().GetCSFConfig();
        CSFLoot csfLoot = GetDayZGame().GetCSFLoot();
        if (csfConfig == NULL || csfLoot == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (!csfConfig.g_CSFDisableLogMessages)
            Print("[CSF] crashed_Wreck_UH1Y - Heli Crash spawned at " + spawnPosition);

        // EXCLUSION CHECK
        bool exclude_loot = false;
        bool exclude_zombies = false;
        bool exclude_animals = false;
        if (csfConfig.g_CSFExcludedCrashSites)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Excluded Sites Found!");
            }

            for (int exclude_me_index = 0; exclude_me_index < csfConfig.g_CSFExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_CSFExcludedCrashSites = csfConfig.g_CSFExcludedCrashSites.Get(exclude_me_index);
                if (!csfConfig.g_CSFDisableLogMessages)
                {
                    Print("[CSF] --- Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
                }
                vector exclusion_pos;
                ref TStringArray exclude_spawn_types;
                exclusion_pos[0] = g_CSFExcludedCrashSites.X;
                exclusion_pos[1] = g_CSFExcludedCrashSites.Y;
                exclusion_pos[2] = g_CSFExcludedCrashSites.Z;
                exclude_spawn_types = g_CSFExcludedCrashSites.ExcludedSpawns;
                if (exclusion_pos == spawnPosition)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] - Exclusion MATCH!");

                    for (int excluded_spawns_index = 0; excluded_spawns_index < exclude_spawn_types.Count(); excluded_spawns_index++)
                    {
                        switch (exclude_spawn_types[excluded_spawns_index])
                        {
                        case "all":
                            // [CSF] - Exclude ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;

                        case "animals":
                            // [CSF] - Exclude ANIMALS
                            exclude_animals = true;
                            break;

                        case "loot":
                            // [CSF] - Exclude ITEMS
                            exclude_loot = true;
                            break;

                        case "zombies":
                            // [CSF] - Exclude ZOMBIES
                            exclude_zombies = true;
                            break;

                        case "none":
                            // [CSF] - Include ALL
                            exclude_loot = false;
                            exclude_zombies = false;
                            exclude_animals = false;
                            break;

                        default:
                            // [CSF] - Default: EXCLUDE ALL
                            exclude_loot = true;
                            exclude_zombies = true;
                            exclude_animals = true;
                            break;
                        }
                    }
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] - crashed_Wreck_UH1Y - List of Excluded Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
                    }
                }
            }
        }
        // Zombies
        if (!csfConfig.g_CSFDisable_Wreck_UH1Y_Zombies)
        {
            int zombiesAmount = Math.RandomInt(csfConfig.g_CSFZombiesMin, csfConfig.g_CSFZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFZombieMinDistFromHeli, csfConfig.g_CSFZombieMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + zombiesAmount + " crashed_Wreck_UH1Y zombies spawned.");
        }

        // Animals
        if (!csfConfig.g_CSFDisable_Wreck_UH1Y_Animals)
        {
            int animalsAmount = Math.RandomInt(csfConfig.g_CSFAnimalsMin, csfConfig.g_CSFAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, csfConfig.g_CSFAnimalsMinDistFromHeli, csfConfig.g_CSFAnimalsMaxDistFromHeli), csfConfig.g_CSFZombieAndAnimalLifetime);

            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + animalsAmount + " crashed_Wreck_UH1Y animals spawned.");
        }

        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_Wreck_UH1Y_Loot && !exclude_loot)
        {
            // TODO: Find how to grab max health of item to spawn
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            int adjusted_items_spawned = 0;
            bool include_loot = true;
            // Spawn system iterator
            int total_loot_amount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax + 1);
            for (int total_items_spawned = 0; total_items_spawned < total_loot_amount; item_index++)
            {
                adjusted_items_spawned = ValidateItemsToSpawn(
                    csfLoot.g_CSFSpawnableLootList.Get(item_index),
                    total_loot_amount,
                    csfLoot.g_CSFLootRandomHealth,
                    csfLoot.g_CSFLootLifetime,
                    spawnPosition,
                    csfLoot.g_CSFLootMinDistFrom_UH1Y,
                    csfLoot.g_CSFLootMaxDistFrom_UH1Y,
                    total_items_spawned,
                    "UH1Y",
                    csfConfig.g_CSFDisableLogMessages);
                if (adjusted_items_spawned == -1)
                    break;
                else
                    total_items_spawned = adjusted_items_spawned;
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + total_loot_amount + "' crashed_Wreck_UH1Y loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + total_items_spawned + "'");
            }
        }
    }
}