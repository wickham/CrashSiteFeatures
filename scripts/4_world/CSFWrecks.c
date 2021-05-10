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

            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            bool rand_health = false;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int total_items_spawned = 0; total_items_spawned < lootAmount; total_items_spawned++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(item_index);
                // Check if we have anything to spawn
                if (!g_CSFSpawnableLootList)
                {
                    Print("[CSF] WARNING : failed to find valid item before reaching end of 'lootAmount'");
                    total_items_spawned = lootAmount;
                    break;
                }
                // TODO: Check if item is valid
                // HERE
                // Spawn Item count based on min-max
                else
                {
                    item_to_spawn = g_CSFSpawnableLootList.ItemName;
                    item_count = Math.RandomInt(g_CSFSpawnableLootList.MinCount, g_CSFSpawnableLootList.MaxCount);
                    Print("[CSF] {DEBUG} Item Count: '" + item_count + "'");

                    // Check if No items needed to spawn, then exit statement
                    if (item_count == 0)
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Skipping Items to spawn for");
                        break;
                    }
                    else if (item_count > (lootAmount - total_items_spawned))
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Too many item count requested, requesting diff instead: '" + (lootAmount - total_items_spawned) + "'");
                        item_count = (lootAmount - total_items_spawned);
                    }
                    else
                    {
                        Print("[CSF] {DEBUG} ITEM '" + item_to_spawn + "' COUNT IS '" + item_count + "'");
                        for (int item_dupe = 0; item_dupe < item_count; item_dupe++)
                        {
                            // Checking if random health requested
                            if (csfLoot.g_CSFLootRandomHealth)
                            {
                                rand_health = csfLoot.g_CSFLootRandomHealth;
                                if (!csfConfig.g_CSFDisableLogMessages)
                                    Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                            }
                            // Begin spawning items+attachments
                            if (!csfConfig.g_CSFDisableLogMessages)
                                Print("[CSF] {DEBUG} Spawn---Wreck_UH1Y---" + item_to_spawn + "-----------------");
                            ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_UH1Y, csfLoot.g_CSFLootMaxDistFrom_UH1Y), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Attachments)
                                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Sight)
                                SpawnSight(itemEnt, g_CSFSpawnableLootList.Sight, false, csfConfig.g_CSFDisableLogMessages);
                            debug_items++;
                            total_items_spawned++;
                        }
                    }
                    item_index++;
                }
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + lootAmount + "' Wreck_UH1Y loot spawned.");
                Print("[CSF] Adjusted Result: '" + debug_items + "'");
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
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(item_index);
                // Check if we have anything to spawn
                if (!g_CSFSpawnableLootList)
                {
                    Print("[CSF] WARNING : failed to find valid item before reaching end of 'lootAmount'");
                    k = lootAmount;
                    break;
                }
                // TODO: Check if item is valid
                // HERE
                // Spawn Item count based on min-max
                else
                {
                    item_to_spawn = g_CSFSpawnableLootList.ItemName;
                    item_count = Math.RandomInt(g_CSFSpawnableLootList.MinCount, g_CSFSpawnableLootList.MaxCount);

                    // Check if No items needed to spawn, then exit statement
                    if (item_count == 0)
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} 0 Items to spawn for" + item_to_spawn);
                        break;
                    }
                    else if (item_count > (lootAmount - k))
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Too many item count requested, requesting diff instead: '" + (lootAmount - k) + "'");
                        item_count = (lootAmount - k);
                    }
                    else
                    {
                        Print("[CSF] {DEBUG} ITEM '" + item_to_spawn + "' COUNT IS '" + item_count + "'");
                        for (int item_dupe = 0; item_dupe < item_count; item_dupe++)
                        {
                            // Checking if random health requested
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
                            // Begin spawning items+attachments
                            if (!csfConfig.g_CSFDisableLogMessages)
                                Print("[CSF] {DEBUG} -----------------" + item_to_spawn + "-----------------");
                            ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_Mi8, csfLoot.g_CSFLootMaxDistFrom_Mi8), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Attachments)
                                SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Sight)
                                SpawnSight(itemEnt, g_CSFSpawnableLootList.Sight, false, csfConfig.g_CSFDisableLogMessages);
                            debug_items++;
                        }
                    }
                    item_index++;
                }
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + lootAmount + "' Wreck_Mi8 loot spawned.");
                Print("[CSF] Adjusted Result: '" + debug_items + "'");
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
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(item_index);
                // Check if we have anything to spawn
                if (!g_CSFSpawnableLootList)
                {
                    Print("[CSF] WARNING : failed to find valid item before reaching end of 'lootAmount'");
                    k = lootAmount;
                    break;
                }
                // TODO: Check if item is valid
                // HERE
                // Spawn Item count based on min-max
                else
                {
                    item_to_spawn = g_CSFSpawnableLootList.ItemName;
                    item_count = Math.RandomInt(g_CSFSpawnableLootList.MinCount, g_CSFSpawnableLootList.MaxCount);

                    // Check if No items needed to spawn, then exit statement
                    if (item_count == 0)
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} 0 Items to spawn for" + item_to_spawn);
                        break;
                    }
                    else if (item_count > (lootAmount - k))
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Too many item count requested, requesting diff instead: '" + (lootAmount - k) + "'");
                        item_count = (lootAmount - k);
                    }
                    else
                    {
                        Print("[CSF] {DEBUG} ITEM '" + item_to_spawn + "' COUNT IS '" + item_count + "'");
                        for (int item_dupe = 0; item_dupe < item_count; item_dupe++)
                        {
                            // Checking if random health requested
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
                            // Begin spawning items+attachments
                            if (!csfConfig.g_CSFDisableLogMessages)
                                Print("[CSF] {DEBUG} -----------------" + item_to_spawn + "-----------------");
                            ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_C130, csfLoot.g_CSFLootMaxDistFrom_C130), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                            SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Sight)
                                SpawnSight(itemEnt, g_CSFSpawnableLootList.Sight, false, csfConfig.g_CSFDisableLogMessages);
                            debug_items++;
                        }
                    }
                    item_index++;
                }
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + lootAmount + "' crashed_Wreck_UH1Y loot spawned.");
                Print("[CSF] Adjusted Result: '" + debug_items + "'");
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
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(item_index);
                // Check if we have anything to spawn
                if (!g_CSFSpawnableLootList)
                {
                    Print("[CSF] WARNING : failed to find valid item before reaching end of 'lootAmount'");
                    k = lootAmount;
                    break;
                }
                // TODO: Check if item is valid
                // HERE
                // Spawn Item count based on min-max
                else
                {
                    item_to_spawn = g_CSFSpawnableLootList.ItemName;
                    item_count = Math.RandomInt(g_CSFSpawnableLootList.MinCount, g_CSFSpawnableLootList.MaxCount);

                    // Check if No items needed to spawn, then exit statement
                    if (item_count == 0)
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} 0 Items to spawn for" + item_to_spawn);
                        break;
                    }
                    else if (item_count > (lootAmount - k))
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Too many item count requested, requesting diff instead: '" + (lootAmount - k) + "'");
                        item_count = (lootAmount - k);
                    }
                    else
                    {
                        Print("[CSF] {DEBUG} ITEM '" + item_to_spawn + "' COUNT IS '" + item_count + "'");
                        for (int item_dupe = 0; item_dupe < item_count; item_dupe++)
                        {
                            // Checking if random health requested
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
                            // Begin spawning items+attachments
                            if (!csfConfig.g_CSFDisableLogMessages)
                                Print("[CSF] {DEBUG} -----------------" + item_to_spawn + "-----------------");
                            ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_C130, csfLoot.g_CSFLootMaxDistFrom_C130), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                            SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Sight)
                                SpawnSight(itemEnt, g_CSFSpawnableLootList.Sight, false, csfConfig.g_CSFDisableLogMessages);
                            debug_items++;
                        }
                    }
                    item_index++;
                }
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + lootAmount + "' crashed_Wreck_UH1Y loot spawned.");
                Print("[CSF] Adjusted Result: '" + debug_items + "'");
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
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(item_index);
                // Check if we have anything to spawn
                if (!g_CSFSpawnableLootList)
                {
                    Print("[CSF] WARNING : failed to find valid item before reaching end of 'lootAmount'");
                    k = lootAmount;
                    break;
                }
                // TODO: Check if item is valid
                // HERE
                // Spawn Item count based on min-max
                else
                {
                    item_to_spawn = g_CSFSpawnableLootList.ItemName;
                    item_count = Math.RandomInt(g_CSFSpawnableLootList.MinCount, g_CSFSpawnableLootList.MaxCount);

                    // Check if No items needed to spawn, then exit statement
                    if (item_count == 0)
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} 0 Items to spawn for" + item_to_spawn);
                        break;
                    }
                    else if (item_count > (lootAmount - k))
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Too many item count requested, requesting diff instead: '" + (lootAmount - k) + "'");
                        item_count = (lootAmount - k);
                    }
                    else
                    {
                        Print("[CSF] {DEBUG} ITEM '" + item_to_spawn + "' COUNT IS '" + item_count + "'");
                        for (int item_dupe = 0; item_dupe < item_count; item_dupe++)
                        {
                            // Checking if random health requested
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
                            // Begin spawning items+attachments
                            if (!csfConfig.g_CSFDisableLogMessages)
                                Print("[CSF] {DEBUG} -----------------" + item_to_spawn + "-----------------");
                            ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_Mi8, csfLoot.g_CSFLootMaxDistFrom_Mi8), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                            SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Sight)
                                SpawnSight(itemEnt, g_CSFSpawnableLootList.Sight, false, csfConfig.g_CSFDisableLogMessages);
                            debug_items++;
                        }
                    }
                    item_index++;
                }
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + lootAmount + "' crashed_Wreck_UH1Y loot spawned.");
                Print("[CSF] Adjusted Result: '" + debug_items + "'");
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
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            string item_to_spawn;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int k = 0; k < lootAmount; k++)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(item_index);
                // Check if we have anything to spawn
                if (!g_CSFSpawnableLootList)
                {
                    Print("[CSF] WARNING : failed to find valid item before reaching end of 'lootAmount'");
                    k = lootAmount;
                    break;
                }
                // TODO: Check if item is valid
                // HERE
                // Spawn Item count based on min-max
                else
                {
                    item_to_spawn = g_CSFSpawnableLootList.ItemName;
                    item_count = Math.RandomInt(g_CSFSpawnableLootList.MinCount, g_CSFSpawnableLootList.MaxCount);

                    // Check if No items needed to spawn, then exit statement
                    if (item_count == 0)
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} 0 Items to spawn for" + item_to_spawn);
                        break;
                    }
                    else if (item_count > (lootAmount - k))
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Too many item count requested, requesting diff instead: '" + (lootAmount - k) + "'");
                        item_count = (lootAmount - k);
                    }
                    else
                    {
                        Print("[CSF] {DEBUG} ITEM '" + item_to_spawn + "' COUNT IS '" + item_count + "'");
                        for (int item_dupe = 0; item_dupe < item_count; item_dupe++)
                        {
                            // Checking if random health requested
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
                            // Begin spawning items+attachments
                            if (!csfConfig.g_CSFDisableLogMessages)
                                Print("[CSF] {DEBUG} -----------------" + item_to_spawn + "-----------------");
                            ItemBase itemEnt = SpawnItem(item_to_spawn, GetRandomSpawnPosition(spawnPosition, csfLoot.g_CSFLootMinDistFrom_Mi8, csfLoot.g_CSFLootMaxDistFrom_Mi8), csfLoot.g_CSFLootLifetime, rand_health, csfConfig.g_CSFDisableLogMessages);
                            SpawnAttachments(itemEnt, g_CSFSpawnableLootList.Attachments, false, csfConfig.g_CSFDisableLogMessages);
                            if (g_CSFSpawnableLootList.Sight)
                                SpawnSight(itemEnt, g_CSFSpawnableLootList.Sight, false, csfConfig.g_CSFDisableLogMessages);
                            debug_items++;
                        }
                    }
                    item_index++;
                }
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + lootAmount + "' crashed_Wreck_UH1Y loot spawned.");
                Print("[CSF] Adjusted Result: '" + debug_items + "'");
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

        // LOOT
        // Begin Spawners
        if (!csfLoot.g_CSFDisable_Wreck_UH1Y_Loot && !exclude_loot)
        {

            // TODO: Find how to grab max health of item to spawn
            bool rand_health = csfLoot.g_CSFLootRandomHealth;
            int random_selected_index = 0;
            int item_min;
            int item_max;
            int item_count;
            int item_index = 0;
            int debug_items = 0;
            string item_to_spawn;
            bool include_loot = true;
            // Spawn system iterator
            int lootAmount = Math.RandomInt(csfLoot.g_CSFLootMin, csfLoot.g_CSFLootMax);
            for (int total_items_spawned = 0; total_items_spawned < lootAmount;)
            {
                ref CrashSiteLoot g_CSFSpawnableLootList = csfLoot.g_CSFSpawnableLootList.Get(item_index);
                // Check if we have anything to spawn
                if (!g_CSFSpawnableLootList)
                {
                    Print("[CSF] WARNING : failed to find valid item before reaching end of 'lootAmount'!");
                    total_items_spawned = lootAmount;
                    break;
                }
                if (!g_CSFSpawnableLootList.IncludedWrecks)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] {DEBUG} No Wrecks found, defaulting to all");
                }
                else
                {
                    // Is loot included?
                    if (!IncludeLoot(g_CSFSpawnableLootList.IncludedWrecks, "UH1Y"))
                        include_loot = false;
                    else
                        include_loot = true;
                }

                // TODO: Check if item is valid
                // HERE
                // Spawn Item count based on min-max

                item_to_spawn = g_CSFSpawnableLootList.ItemName;
                // Check if No items needed to spawn, then exit statement
                if (!include_loot)
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                        Print("[CSF] {DEBUG} Skipping Items to spawned for" + item_to_spawn);
                    item_index++;
                    Print("[CSF] Next item check at index: " + item_index);
                }
                else
                {
                    if (!csfConfig.g_CSFDisableLogMessages)
                    {
                        Print("[CSF] -----------------ALLOW ITEMS TO SPAWN!!-----------------");
                    }
                    item_count = Math.RandomInt(g_CSFSpawnableLootList.MinCount, g_CSFSpawnableLootList.MaxCount);
                    if (item_count > (lootAmount - total_items_spawned))
                    {
                        if (!csfConfig.g_CSFDisableLogMessages)
                            Print("[CSF] {DEBUG} Too many item count requested, requesting diff instead: '" + (lootAmount - total_items_spawned) + "'");
                        item_count = (lootAmount - total_items_spawned);
                    }
                    Print("[CSF] {DEBUG} ITEM '" + item_to_spawn + "' COUNT IS '" + item_count + "'");
                    for (int item_dupe = 0; item_dupe < item_count; item_dupe++)
                    {
                        // Checking if random health requested
                        if (csfLoot.g_CSFLootRandomHealth)
                        {
                            rand_health = csfLoot.g_CSFLootRandomHealth;
                            if (!csfConfig.g_CSFDisableLogMessages)
                                Print("[CSF] RANDOM HEALTH! : '" + rand_health + "'");
                        }
                        else
                        {
                            rand_health = false;
                        }
                        //SpawnItem in List
                        SpawnItemsInList(g_CSFSpawnableLootList, spawnPosition, csfLoot.g_CSFLootMinDistFrom_UH1Y, csfLoot.g_CSFLootMaxDistFrom_UH1Y, csfLoot.g_CSFLootLifetime, csfLoot.g_CSFLootRandomHealth, !csfConfig.g_CSFDisableLogMessages);
                        debug_items++;
                        total_items_spawned++;
                    }
                    item_index++;
                    Print("[CSF] Next item check at index: " + item_index);
                }
            }
            if (!csfConfig.g_CSFDisableLogMessages)
            {
                Print("[CSF] Requested '" + lootAmount + "' crashed_Wreck_UH1Y loot spawned.");
                Print("[CSF] Actual Spawn Count: '" + debug_items + "'");
            }
        }
    }
}