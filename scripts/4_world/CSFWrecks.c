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
                    Print("[CSF] -----------------Name of Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
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
                        Print("[CSF] - Crash Site Exclusion MATCH!");

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
                        Print("[CSF] - Wreck_UH1Y - Name of Excluded Site Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
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

        // Loot
        if (!csfLoot.g_CSFDisable_UH1Y_Loot && !exclude_loot)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(Math.RandomInt(0, csfLoot.g_CSFSpawnableLootList.Count()));
                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // TODO: Check if item is valid
                // HERE
                if (csfLoot.g_CSFLootRandomHealth)
                {
                    rand_health = true;
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                }
                else
                {
                    rand_health = false;
                }
                if (!csfConfig.g_CSFDisableLogMessages)
                    Print("[CSF] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_UH1Y, csfLoot.g_CSFLootMaxDistFrom_UH1Y), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
            }
            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + lootAmount + " Wreck_UH1Y loot spawned.");
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
                    Print("[CSF] -----------------Name of Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
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
                        Print("[CSF] - Crash Site Exclusion MATCH!");

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
                        Print("[CSF] - Wreck_Mi8 - Name of Excluded Site Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
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

        // Loot
        if (!csfLoot.g_CSFDisable_Mi8_Loot && !exclude_loot)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(Math.RandomInt(0, csfLoot.g_CSFSpawnableLootList.Count()));
                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // TODO: Check if item is valid
                // HERE
                if (csfLoot.g_CSFLootRandomHealth)
                {
                    rand_health = true;
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                }
                else
                {
                    rand_health = false;
                }
                if (!csfConfig.g_CSFDisableLogMessages)
                    Print("[CSF] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_Mi8, csfLoot.g_CSFLootMaxDistFrom_Mi8), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
            }
            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + lootAmount + " Wreck_Mi8 loot spawned.");
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
                    Print("[CSF] -----------------Name of Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
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
                        Print("[CSF] - Crash Site Exclusion MATCH!");

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
                        Print("[CSF] - crashed_Wreck_C130J - Name of Excluded Site Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
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
        // Loot
        if (!csfLoot.g_CSFDisable_Wreck_C130J_Loot && !exclude_loot)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(Math.RandomInt(0, csfLoot.g_CSFSpawnableLootList.Count()));
                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // TODO: Check if item is valid
                // HERE
                if (csfLoot.g_CSFLootRandomHealth)
                {
                    rand_health = true;
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                }
                else
                {
                    rand_health = false;
                }
                if (!csfConfig.g_CSFDisableLogMessages)
                    Print("[CSF] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_C130, csfLoot.g_CSFLootMaxDistFrom_C130), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
            }
            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + lootAmount + " crashed_Wreck_C130J loot spawned.");
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
                    Print("[CSF] -----------------Name of Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
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
                        Print("[CSF] - Crash Site Exclusion MATCH!");

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
                        Print("[CSF] - crashed_Wreck_C130_Camo - Name of Excluded Site Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
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
        // Loot
        if (!csfLoot.g_CSFDisable_Wreck_C130_Camo_Loot && !exclude_loot)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(Math.RandomInt(0, csfLoot.g_CSFSpawnableLootList.Count()));
                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // TODO: Check if item is valid
                // HERE
                if (csfLoot.g_CSFLootRandomHealth)
                {
                    rand_health = true;
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                }
                else
                {
                    rand_health = false;
                }
                if (!csfConfig.g_CSFDisableLogMessages)
                    Print("[CSF] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_C130, csfLoot.g_CSFLootMaxDistFrom_C130), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
            }
            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + lootAmount + " crashed_Wreck_C130_Camo loot spawned.");
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
                    Print("[CSF] -----------------Name of Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
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
                        Print("[CSF] - Crash Site Exclusion MATCH!");

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
                        Print("[CSF] - crashed_Wreck_Mi8_CDF - Name of Excluded Site Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
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
        // Loot
        if (!csfLoot.g_CSFDisable_Wreck_Mi8_CDF_Loot && !exclude_loot)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(Math.RandomInt(0, csfLoot.g_CSFSpawnableLootList.Count()));
                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // TODO: Check if item is valid
                // HERE
                if (csfLoot.g_CSFLootRandomHealth)
                {
                    rand_health = true;
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                }
                else
                {
                    rand_health = false;
                }
                if (!csfConfig.g_CSFDisableLogMessages)
                    Print("[CSF] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_Mi8, csfLoot.g_CSFLootMaxDistFrom_Mi8), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
            }
            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + lootAmount + " crashed_Wreck_Mi8_CDF loot spawned.");
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
                    Print("[CSF] -----------------Name of Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
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
                        Print("[CSF] - Crash Site Exclusion MATCH!");

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
                        Print("[CSF] - crashed_Wreck_Mi8_RU - Name of Excluded Site Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
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
        // Loot
        if (!csfLoot.g_CSFDisable_Wreck_Mi8_RU_Loot && !exclude_loot)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(Math.RandomInt(0, csfLoot.g_CSFSpawnableLootList.Count()));
                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // TODO: Check if item is valid
                // HERE
                if (csfLoot.g_CSFLootRandomHealth)
                {
                    rand_health = true;
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                }
                else
                {
                    rand_health = false;
                }
                if (!csfConfig.g_CSFDisableLogMessages)
                    Print("[CSF] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_Mi8, csfLoot.g_CSFLootMaxDistFrom_Mi8), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
            }
            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + lootAmount + " crashed_Wreck_Mi8_RU loot spawned.");
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
                    Print("[CSF] -----------------Name of Excluded Site to Check: '" + g_CSFExcludedCrashSites.Label + "'-----------------");
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
                        Print("[CSF] - Crash Site Exclusion MATCH!");

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
                        Print("[CSF] - crashed_Wreck_UH1Y - Name of Excluded Site Setup: '" + g_CSFExcludedCrashSites.Label + " - Exclude ~ Animals: " + exclude_animals + ", Loot: " + exclude_loot + ", Zombies: " + exclude_zombies);
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
        // Loot
        if (!csfLoot.g_CSFDisable_Wreck_UH1Y_Loot && !exclude_loot)
        {
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
            }
            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(Math.RandomInt(0, csfLoot.g_CSFSpawnableLootList.Count()));

                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // TODO: Check if item is valid
                // HERE
                if (csfLoot.g_CSFLootRandomHealth)
                {
                    rand_health = true;
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                }
                else
                {
                    rand_health = false;
                }
                if (!csfConfig.g_CSFDisableLogMessages)
                    Print("[CSF] -----------------" + item_to_spawn + "-----------------");
                ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_UH1Y, csfLoot.g_CSFLootMaxDistFrom_UH1Y), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
            }
            if (!csfConfig.g_CSFDisableLogMessages)
                Print("[CSF] " + lootAmount + " crashed_Wreck_UH1Y loot spawned.");
        }
    }
}
