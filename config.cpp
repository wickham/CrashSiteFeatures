class CfgPatches
{
	class HeliCrashSite
	{
		requiredAddons[] =
			{
				"DZ_Data"};
		requiredVersion = 0.1;
		units[] = {};
		weapons[] = {};
	};
};
class CfgMods
{
	class HeliCrashSite_Scripts
	{
		dir = "HeliCrashSite";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Heli Crash Sites";
		credits = "oppahansi";
		author = "";
		authorID = "";
		version = "1.0";
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
						"HeliCrashSite/scripts/3_game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] =
					{
						"HeliCrashSite/scripts/4_world"};
			};
			class missionScriptModule
			{
				value = "";
				files[] =
					{
						"HeliCrashSite/scripts/5_mission"};
			};
		};
	};
};
