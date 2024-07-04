////////////////////////////////////////////////////////////////////
//DeRap: Configs\Suits\config.bin
//Produced from mikero's Dos Tools Dll version 9.10
//https://mikero.bytex.digital/Downloads
//'now' is Tue Jun 25 10:16:18 2024 : 'file' last modified on Wed May 29 13:45:19 2024
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class SpaghettiSuits_Testing
	{
		units[] = {"TShirt_Beige_suitTest"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters_Headgear","DZ_Characters","DZ_Data","DZ_Scripts"};
	};
};
class CfgVehicles
{
	class BaseballCap_ColorBase;
	class M65Jacket_ColorBase;
	class TShirt_Beige;
	class TShirt_Beige_suitTest: TShirt_Beige
	{
		displayName = "Suit Testing {TShirt_Beige}";
		suit[] = {"HeadDummy_Base","AirborneMask","LeatherStorageVest_Natural","WorkingGloves_Black","Jeans_Green"};
		suitSlots[] = {"Headgear","Mask","Vest","Gloves","Legs"};
		descriptionShort = "Testing Shirt";
	};
	class DummyBase: BaseballCap_ColorBase
	{
		scope = 0;
		visibilityModifier = 1;
		displayName = "";
		descriptionShort = "";
		weight = 0;
		quickBarBonus = 0;
		varWetMax = 0;
		heatIsolation = 1;
		repairableWithKits[] = {5,2};
		repairCosts[] = {30,25};
		soundAttType = "NylonJacket";
		inventorySlot[] = {"Headgear"};
		itemInfo[] = {"Clothing"};
		hiddenSelectionsTextures[] = {"zybtek"};
		BlockedSlots[] = {};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 325;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 1;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;
					};
				};
				class Melee
				{
					class Health
					{
						damage = 1;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;
					};
				};
				class Infected
				{
					class Health
					{
						damage = 1;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage = 1;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 1;
					};
				};
			};
		};
	};
	class HeadDummy_Base: DummyBase
	{
		scope = 2;
		displayName = "Suit Hood";
		descriptionShort = "A hood to go with your suit.";
		inventorySlot[] = {"Headgear"};
	};
	class HeadDummy_SEVA: HeadDummy_Base
	{
		scope = 2;
		displayName = "Suit Hood";
		descriptionShort = "A composite hood that protects the user from mutant and ballistic threats.";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 325;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 0.75;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0.8;
					};
				};
				class Melee
				{
					class Health
					{
						damage = 0.6;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0.7;
					};
				};
				class Infected
				{
					class Health
					{
						damage = 0.6;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0.7;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage = 0.75;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0.75;
					};
				};
			};
		};
	};
	class BackpackDummy: DummyBase
	{
		scope = 2;
		inventorySlot[] = {"Back"};
	};
	class TopDummy: DummyBase
	{
		scope = 2;
		inventorySlot[] = {"Body"};
	};
	class PantsDummy: DummyBase
	{
		scope = 2;
		inventorySlot[] = {"Legs"};
	};
	class BeltDummy: DummyBase
	{
		scope = 2;
		inventorySlot[] = {"Hips"};
	};
	class MaskDummy: DummyBase
	{
		scope = 2;
		inventorySlot[] = {"Mask"};
	};
	class VestDummy: DummyBase
	{
		scope = 2;
		inventorySlot[] = {"Vest"};
	};
};