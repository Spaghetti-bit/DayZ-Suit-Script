class CfgPatches
{
	class MT_Scripts
	{
		requiredAddons[] = { "DZ_Scripts" };
	};
};

class CfgAddons
{
    class PreloadAddons
    {
        class DayZ-Suit-Script
        {
            list[]={};
        };
    };
};

class CfgMods
{
    class DayZ-Suit-Script
    {
        name="";
        dir="DayZ-Suit-Script";
        picture="";
        action="";
        author="";
        overview = "";
		inputs = "";
        defines[] = {};

        class defs
		{
			class imageSets
			{
				files[]= {};
			};
			class widgetStyles
			{
				files[]= {};
			};

			class engineScriptModule 
			{ 
				files[] = { "DayZ-Suit-Script/Scripts/1_Core"};
			};

			class gameScriptModule
			{
				files[] = { "DayZ-Suit-Script/Scripts/3_Game" };
			};
			class worldScriptModule
			{
				files[] = { "DayZ-Suit-Script/Scripts/4_World" };
			};

			class missionScriptModule 
			{
				files[] = { "DayZ-Suit-Script/Scripts/5_Mission" };
			};
		};
    };
};
