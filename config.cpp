class CfgPatches
{
    class CrashSiteFeatures
    {
        requiredAddons[] =
            {
                "DZ_Data",
                "CJ187_CrashSites"};
        requiredVersion = 0.1;
        units[] = {};
        weapons[] = {};
    };
};
class CfgMods
{
    class CrashSiteFeatures_Scripts
    {
        dir = "CrashSiteFeatures";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "Crash Site Features";
        credits = "oppahansi";
        author = "ChronoRift";
        authorID = "";
        version = "2.0";
        extra = 0;
        type = "mod";
        dependencies[] =
            {
                "Game",
                "World",
                "Mission"};
        class defs
        {
            class gameScriptModule
            {
                files[] =
                    {
                        "CrashSiteFeatures/scripts/3_game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] =
                    {
                        "CrashSiteFeatures/scripts/4_world"};
            };
            class missionScriptModule
            {
                value = "";
                files[] =
                    {
                        "CrashSiteFeatures/scripts/5_mission"};
            };
        };
    };
};
