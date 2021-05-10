static void SpawnInfected(vector pos, int lifetime)
{
    EntityAI zed = ZombieBase.Cast(GetGame().CreateObject(ZombieTypes().GetRandomElement(), pos, false, true));
    if (zed)
        zed.SetLifetime(lifetime);
}

static void SpawnAnimal(vector pos, int lifetime)
{
    EntityAI anim = AnimalBase.Cast(GetGame().CreateObject(AnimalTypes().GetRandomElement(), pos, false, true));
    if (anim)
        anim.SetLifetime(lifetime);
}

static ItemBase SpawnItem(string item_name, vector pos, int lifetime, bool rand_health, bool disable_logging)
{
    // TODO: Add function to grab item list and attachments
    // TODO: Check if (Main Item && Attachments) -- NEW FUNCTION START
    // TODO: (TRUE) Get Attachments
    // TODO: (BREAK) Get Main Item
    // TODO: Check if Item exists
    // TODO: Loop iter Attachments exists -- NEW FUNCTION END
    // TODO: Attach all attachments and trigger Item spawn
    ItemBase main_item = ItemBase.Cast(GetGame().CreateObject(item_name, pos, false, true));
    if (!disable_logging)
        Print("[CSF] Item Spawned: '" + item_name + "'" + " With Random Health: '" + rand_health + "'");
    return main_item;
}

static void SpawnAttachments(ItemBase item, ref TStringArray attachments, bool rand_health, bool disable_logging)
{
    bool battery_required = false;
    for (int attachment_index = 0; attachment_index < attachments.Count(); attachment_index++)
    {
        // TODO: Check static list of items that require 9V/other attachments and logic
        for (int batteries_req = 0; batteries_req < BatteryNeededTypes().Count(); batteries_req++)
        {
            if (attachments.Get(attachment_index) == BatteryNeededTypes().Get(batteries_req))
            {
                battery_required = true;
                if (!disable_logging)
                    Print("[CSF] Attachment Spawning WITH BATTERY: " + attachments.Get(attachment_index));
                item.GetInventory().CreateAttachment(attachments.Get(attachment_index)).GetInventory().CreateAttachment("Battery9V");
                if (!disable_logging)
                    Print("[CSF] Successfully attached battery+attachment to : " + item);
                break;
            }
        }
        item.GetInventory().CreateAttachment(attachments.Get(attachment_index));
        if (!disable_logging)
            Print("[CSF] Attachment Spawned: " + attachments.Get(attachment_index) + " on Item: " + item);
    }
}

static void SpawnMag(ItemBase item, string mag, bool rand_health, bool disable_logging)
{
    item.GetInventory().CreateAttachment(mag);
    if (!disable_logging)
        Print("[CSF] Magazine Spawned: " + mag + " on Item: " + item);
}

static void SpawnSight(ItemBase item, string sight, bool rand_health, bool disable_logging)
{
    switch (sight)
    {
        // case "random":
        //     string sight_to_spawn = SightTypes().GetRandomElement();
        //     EntityAI sightEnt = item.GetInventory().CreateAttachment(sight_to_spawn);
        //     Print("[CSF] {SpawnSight} " + sight_to_spawn);

        //     // TODO: Check static list of items that require 9V/other attachments and logic
        //     for (int batteries_req = 0; batteries_req < BatteryNeededTypes().Count(); batteries_req++)
        //     {
        //         if (sight_to_spawn == BatteryNeededTypes().Get(batteries_req))
        //         {
        //             if (!disable_logging)
        //                 Print("[CSF] Attachment Spawning WITH BATTERY: " + sight_to_spawn);
        //             sightEnt.GetInventory().CreateAttachment("Battery9V");
        //             break;
        //         }
        //     }

        //     if (!disable_logging)
        //         Print("[CSF] Random Sight: " + sight + " on Item: " + item);
        //     break;

    case "none":
        if (!disable_logging)
            Print("[CSF] no SIGHT requested... NOT YET IMPLEMENTED");
        return;

    default:
        item.GetInventory().CreateAttachment(sight).GetInventory().CreateAttachment("Battery9V");
        if (!disable_logging)
            Print("[CSF] Attachment Sight: " + sight + " on Item: " + item);
        break;
    }
}

static vector GetRandomSpawnPosition(vector centerpoint, int minDistFromHeli, int maxDistFromHeli)
{
    float height = Math.RandomFloat(0.0, 2.0) * Math.PI;
    float distance = Math.RandomFloat(minDistFromHeli, maxDistFromHeli);
    vector randomSpawnPosition = centerpoint + Vector(Math.Cos(height) * distance, 0.0, Math.Sin(height) * distance);

    randomSpawnPosition[1] = GetGame().SurfaceY(randomSpawnPosition[0], randomSpawnPosition[2]) + 0.5;

    return randomSpawnPosition;
}

static void SpawnItemsInList(
    ref CrashSiteLoot loot_list,
    vector spawn_position,
    int min_dist,
    int max_dist,
    int lifetime,
    bool rand_health,
    bool is_logging_disabled)
{
    // Begin spawning items+attachments
    if (is_logging_disabled)
        Print("[CSF] {DEBUG} ---{SpawnListOfItems}---" + loot_list.ItemName + "-----------------");
    ItemBase itemEnt = SpawnItem(loot_list.ItemName, GetRandomSpawnPosition(spawn_position, min_dist, max_dist), lifetime, rand_health, is_logging_disabled);
    if (loot_list.Attachments)
    {
        Print("[CSF] {DEBUG} Requested Attachments --- " + loot_list.Attachments.Count());
        SpawnAttachments(itemEnt, loot_list.Attachments, rand_health, is_logging_disabled);
    }

    if (loot_list.Sight)
    {
        Print("[CSF] {DEBUG} Requested SpawnSight --- " + loot_list.Sight);
        SpawnSight(itemEnt, loot_list.Sight, rand_health, is_logging_disabled);
    }
    if (loot_list.Magazine)
    {
        Print("[CSF] {DEBUG} Requested Magazine --- " + loot_list.Magazine);
        SpawnMag(itemEnt, loot_list.Magazine, rand_health, is_logging_disabled);
    }
}

static bool IncludeLoot(ref TStringArray included_wrecks, string crash_type)
{
    // "Mi8","UH1Y","C130","all", "none"
    if (!included_wrecks)
    {
        Print("[CSF] {DEBUG} Defaulting to INCLUDED ALL'");
        return true;
    }
    for (int item_wreck_index = 0; item_wreck_index < included_wrecks.Count(); item_wreck_index++)
    {
        if (included_wrecks[item_wreck_index].Contains(crash_type) || included_wrecks[item_wreck_index].Contains("all") || !included_wrecks[item_wreck_index].Contains("none"))
        {
            Print("[CSF] {DEBUG} Loot INCLUDED for: '" + crash_type + "'");
            return true;
        }
    }
    Print("[CSF] {DEBUG} Loot NOT INCLUDED for: '" + crash_type + "'");
    return false;
}

static TStringArray ZombieTypes()
{
    return {
        // Military
        "ZmbM_PatrolNormal_Autumn", "ZmbM_PatrolNormal_Flat", "ZmbM_PatrolNormal_PautRev", "ZmbM_PatrolNormal_Summer",
        "ZmbM_SoldierNormal", "ZmbM_usSoldier_normal_Desert", "ZmbM_usSoldier_normal_Woodland",
        // Firefighter
        "ZmbM_FirefighterNormal",
        // Medic
        "ZmbF_DoctorSkinny", "ZmbF_NurseFat", "ZmbF_ParamedicNormal_Blue", "ZmbF_ParamedicNormal_Green", "ZmbF_ParamedicNormal_Red",
        "ZmbF_PatientOld", "ZmbM_DoctorFat", "ZmbM_ParamedicNormal_Black", "ZmbM_ParamedicNormal_Blue", "ZmbM_ParamedicNormal_Green",
        "ZmbM_ParamedicNormal_Red", "ZmbM_PatientSkinny",
        // Police
        "ZmbF_PoliceWomanNormal", "ZmbM_PolicemanFat", "ZmbM_PolicemanSpecForce",
        "ZmbM_PrisonerSkinny"};
}

static TStringArray AnimalTypes()
{
    return {"Animal_CanisLupus_Grey", "Animal_CanisLupus_White"};
}

static TStringArray BatteryNeededTypes()
{
    return {
        "PersonalRadio",
        "UniversalLight",
        "M68Optic",
        "FNP45_MRDSOptic",
        "KobraOptic",
        "M4_T3NRDSOptic",
        "PSO11Optic",
        "PSO1Optic",
        "PistolOptic",
        "ReflexOptic",
        // Advanced Scopes
        "AD_ACOG_RMR",
        "AD_ACOG_RMR_MosinMount",
        "AD_ACOG_RMR_B13",
        "AD_NFATACR",
        "AD_NFATACR_MosinMount",
        "AD_NFATACR_B13",
        "AD_NFATACR_1_8",
        "AD_NFATACR_1_8_MosinMount",
        "AD_NFATACR_1_8_B13",
        "AD_RMR",
        "AD_RMR_LM",
        "AD_RMR_LM_MosinMount",
        "AD_RMR_LM_B13",
        "AD_RMR_TM",
        "AD_RMR_TM_MosinMount",
        "AD_RMR_TM_B13",
        // ASC LVOA Scopes
        "ASC_LVOAC_HurricaneOptic",
        "ASC_LVOAC_HurricaneOptic_Camo",
        "ASC_LVOAC_HurricaneOptic_DigiTan",
        "ASC_LVOAC_HurricaneOptic_Tan",
        "ASC_LVOAC_HurricaneOptic_UCP",
        // Morty Sights
        "TTC_Holo",
        "TTC_HAMR",
        // MSFC NVG
        "MSFC_NVG",
        "MSFC_NVG_One",
        "MSFC_NVG_GPNVG18",
        ""};
}

static TStringArray SightTypes()
{
    return {
        "ACOGOptic",
        "M68Optic",
        "BUISOptic",
        "FNP45_MRDSOptic",
        "HuntingOptic",
        "KashtanOptic",
        "KazuarOptic",
        "KobraOptic",
        "M4_T3NRDSOptic",
        "PSO11Optic",
        "PSO1Optic",
        "PUScopeOptic",
        "PistolOptic",
        "ReflexOptic",
        // Advanced Scopes
        "AD_B13Mount",
        "AD_MosinMount",
        "AD_ACOG",
        "AD_ACOG_MosinMount",
        "AD_ACOG_B13",
        "AD_ACOG_RMR",
        "AD_ACOG_RMR_MosinMount",
        "AD_ACOG_RMR_B13",
        "AD_DHF5",
        "AD_DHF5_MosinMount",
        "AD_DHF5_B13",
        "AD_MRS",
        "AD_MRS_MosinMount",
        "AD_MRS_B13",
        "AD_NFATACR",
        "AD_NFATACR_MosinMount",
        "AD_NFATACR_B13",
        "AD_NFATACR_1_8",
        "AD_NFATACR_1_8_MosinMount",
        "AD_NFATACR_1_8_B13",
        "AD_OKP7",
        "AD_OKP7_MosinMount",
        "AD_OKP7_B13",
        "AD_Pilad",
        "AD_Pilad_MosinMount",
        "AD_Pilad_B13",
        "AD_PVS4",
        "AD_PVS4_MosinMount",
        "AD_PVS4_B13",
        "AD_RMR",
        "AD_RMR_LM",
        "AD_RMR_LM_MosinMount",
        "AD_RMR_LM_B13",
        "AD_RMR_TM",
        "AD_RMR_TM_MosinMount",
        "AD_RMR_TM_B13",
        "AD_SpecterDR",
        "AD_SpecterDR_MosinMount",
        "AD_SpecterDR_B13",
        // ACS Lvoa Scopes
        "ASC_LVOAC_MilStdScope",
        "ASC_LVOAC_MilStdScope_OliveGreen",
        "ASC_LVOAC_MilStdScope_Tan",
        "ASC_LVOAC_HurricaneOptic",
        "ASC_LVOAC_HurricaneOptic_Camo",
        "ASC_LVOAC_HurricaneOptic_DigiTan",
        "ASC_LVOAC_HurricaneOptic_Tan",
        "ASC_LVOAC_HurricaneOptic_UCP",
        // Morty Sights
        "TTC_G3_Optic",
        "TTC_Holo",
        "TTC_HAMR",
        // MFSC Optics
        "MSFC_Optic_EOtech_XPS20",
        "MSFC_Optic_HartmanMH1",
        "none"};
}
