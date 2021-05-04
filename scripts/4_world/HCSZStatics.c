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
        Print("[HCSZ] Item Spawned: '" + item_name + "'" + " With Random Health: '" + rand_health + "'");
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
                    Print("[HCSZ] Attachment Spawning WITH BATTERY: " + attachments.Get(attachment_index));
                item.GetInventory().CreateAttachment(attachments.Get(attachment_index)).GetInventory().CreateAttachment("Battery9V");
                if (!disable_logging)
                    Print("[HCSZ] Successfully attached battery+attachment to : " + item);
                break;
            }
        }
        item.GetInventory().CreateAttachment(attachments.Get(attachment_index));
        if (!disable_logging)
            Print("[HCSZ] Attachment Spawned: " + attachments.Get(attachment_index) + " on Item: " + item);
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
    return {"M4_T3NRDSOptic", "PersonalRadio", "UniversalFlashlight"};
}