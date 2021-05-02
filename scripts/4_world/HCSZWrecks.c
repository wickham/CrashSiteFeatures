modded class Wreck_UH1Y
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

        if (hcszConfig.g_HCSZDisableLogMessages != 1)
            Print("[HCSZ] Wreck_UH1Y - heli crash spawned at " + spawnPosition);
        // Zombies
        if (hcszConfig.g_HCSZDisableUH1YZombies != 1)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (hcszConfig.g_HCSZDisableLogMessages != 1)
                Print("[HCSZ] " + zombiesAmount + " Wreck_UH1Y zombies spawned.");
        }

        // Animals
        if (hcszConfig.g_HCSZDisableUH1YAnimals != 1)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (hcszConfig.g_HCSZDisableLogMessages != 1)
                Print("[HCSZ] " + animalsAmount + " Wreck_UH1Y animals spawned.");
        }

        // Items
        if (hcszConfig.g_HCSZSpawnableItemsList)
        {
            Print("[HCSZ] -----------------FOUND ITEMS TO SPAWN!!-----------------");
            Print("[HCSZ] -----------------" + hcszConfig.g_HCSZSpawnableItemsList + "-----------------");

            bool exclude_items = false;
            // EXCLUSION LIST

            Print("[HCSZ] -----------------" + hcszConfig.g_HCSZExcludedCrashSites + "-----------------");
            // Print("[HCSZ] -----------------" + hcszConfig.g_HCSZExcludedCrashSites.Get(0) + "-----------------");
            for (int exclude_me_index = 0; exclude_me_index < hcszConfig.g_HCSZExcludedCrashSites.Count(); exclude_me_index++)
            {
                ref CrashSiteExclude g_HCSZExcludedCrashSites = hcszConfig.g_HCSZExcludedCrashSites.Get(exclude_me_index);
                Print("[HCSZ] -----------------NAME OF EXCLUDED SITE: '" + g_HCSZExcludedCrashSites.name + "'");
                vector exclusion_spawn;
                exclusion_spawn[0] = g_HCSZExcludedCrashSites.x;
                exclusion_spawn[1] = g_HCSZExcludedCrashSites.y;
                exclusion_spawn[2] = g_HCSZExcludedCrashSites.z;

                if (exclusion_spawn == spawnPosition)
                {
                    Print("[HCSZ] -----------------DONT SPAWN THAT SHIT!");
                    exclude_items = true;
                }
            }

            // Spawn system iterator
            for (int ab = 0; ab < hcszConfig.g_HCSZSpawnableItemsList.Count(); ab++)
            {
                ref CrashSiteLoot g_HCSZSpawnableItemsList = hcszConfig.g_HCSZSpawnableItemsList.Get(ab);
                Print("[HCSZ] -----------------" + g_HCSZSpawnableItemsList.item_type + "-----------------");
                Print("[HCSZ] -----------------" + hcszConfig.g_HCSZMaxNumberOfItems + "-----------------");
                // TODO: Check if item is valid
                // HERE
                Print("[HCSZ] -----------------MADE IT-----------------");
                for (int k = 0; k < hcszConfig.g_HCSZMaxNumberOfItems; k++)
                {
                    // Spawns Item
                    // if (hcszConfig.g_HCSZDisableLogMessages != 1)
                    // GetGame().CreateObject(g_HCSZSpawnableItemsList.item_type, spawnPosition);
                    Print("[HCSZ] Item EXCLUDED! : '" + g_HCSZSpawnableItemsList.item_type + "'");
                    if (!exclude_items)
                    {
                        SpawnItem(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZItemsMinDistFromHeli, hcszConfig.g_HCSZItemsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime, 500.0);
                    }
                }
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

        HCSZConfig hcszConfig = GetDayZGame().GetHCSZConfig();
        if (hcszConfig == NULL)
            return;

        vector spawnPosition = this.GetPosition();

        if (hcszConfig.g_HCSZDisableLogMessages != 1)
            Print("[HCSZ] New_Wreck_Mi8 - heli crash spawned at " + spawnPosition);
        // Zombies
        if (hcszConfig.g_HCSZDisableMi8Zombies != 1)
        {
            int zombiesAmount = Math.RandomInt(hcszConfig.g_HCSZZombiesMin, hcszConfig.g_HCSZZombiesMax);

            for (int i = 0; i <= zombiesAmount; i++)
                SpawnInfected(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZZombieMinDistFromHeli, hcszConfig.g_HCSZZombieMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (hcszConfig.g_HCSZDisableLogMessages != 1)
                Print("[HCSZ] " + zombiesAmount + " New_Wreck_Mi8 zombies spawned.");
        }

        // Animals
        if (hcszConfig.g_HCSZDisableMi8Animals != 1)
        {
            int animalsAmount = Math.RandomInt(hcszConfig.g_HCSZAnimalsMin, hcszConfig.g_HCSZAnimalsMax);

            for (int j = 0; j <= animalsAmount; j++)
                SpawnAnimal(GetRandomSpawnPosition(spawnPosition, hcszConfig.g_HCSZAnimalsMinDistFromHeli, hcszConfig.g_HCSZAnimalsMaxDistFromHeli), hcszConfig.g_HCSZZombieAndAnimalLifetime);

            if (hcszConfig.g_HCSZDisableLogMessages != 1)
                Print("[HCSZ] " + animalsAmount + " New_Wreck_Mi8 animals spawned.");
        }
    }
}