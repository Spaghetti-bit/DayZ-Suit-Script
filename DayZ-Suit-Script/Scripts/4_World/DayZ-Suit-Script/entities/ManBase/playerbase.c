modded class PlayerBase extends ManBase
{
    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
		
        if (GetGame().IsServer())
        {
			CheckSlotsForItemsAndUnlock();
            string cfg_Path = "cfgVehicles " + item.GetType();
            if (GetGame().ConfigIsExisting(cfg_Path) && IsPlayerLoaded())
            {
                ref array<string> suitArr = new array<string>;
                ref array<string> suitSlotArr = new array<string>;

                GetGame().ConfigGetTextArray(cfg_Path + " suit", suitArr);
                GetGame().ConfigGetTextArray(cfg_Path + " suitSlots", suitSlotArr);
                for (int i = 0; i < suitArr.Count(); i++)
                {
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedSuitCheck, 200, false, suitSlotArr.Get(i), suitArr.Get(i), item);
                }
            }
        }
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        if (GetGame().IsServer() && IsPlayerLoaded())
        {
			CheckSlotsForItemsAndUnlock();
            string cfg_Path = "cfgVehicles " + item.GetType();
            if (GetGame().ConfigIsExisting(cfg_Path))
            {
				ref array<string> suitArr = new array<string>;
                ref array<string> suitSlotArr = new array<string>;
                GetGame().ConfigGetTextArray(cfg_Path + " suit", suitArr);
                GetGame().ConfigGetTextArray(cfg_Path + " suitSlots", suitSlotArr);
                for (int i = 0; i < suitSlotArr.Count(); i++)
                {
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedSuitCheckDetach, 200, false, suitSlotArr.Get(i), suitArr.Get(i));
                }
            }
        }
    }

    override void OnPlayerLoaded()
    {
        super.OnPlayerLoaded();
		CheckSlotsForItemsAndUnlock();
        foreach(string slot_name: SUIT_SLOT_NAMES)
        {
            ItemBase item = ItemBase.Cast(FindAttachmentBySlotName(slot_name));
            if (item) 
            { 
                string cfg_Path = "cfgVehicles " + item.GetType();
                if (GetGame().ConfigIsExisting(cfg_Path))
                {
                    ref array<string> suitArr = new array<string>;
                    ref array<string> suitSlotArr = new array<string>;

                    GetGame().ConfigGetTextArray(cfg_Path + " suit", suitArr);
                    GetGame().ConfigGetTextArray(cfg_Path + " suitSlots", suitSlotArr);
                    for (int i = 0; i < suitArr.Count(); i++)
                    {
                        //Hood implement check to avoid removing the _Down version of a top.
                        /*
                            @Example:
                                Sunrise_Top_Down
                        */
                        if (suitSlotArr.Get(i) == "Body")
                        {
                            ItemBase top = ItemBase.Cast(FindAttachmentBySlotName(suitSlotArr.Get(i)));
                            if (top && top.GetType().Contains("_Down"))
                            {
                                GetInventory().SetSlotLock( InventorySlots.GetSlotIdFromString(suitSlotArr.Get(i)), true );
                            }
                            else 
                            {
                                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedSuitCheck, 200, false, suitSlotArr.Get(i), suitArr.Get(i), item);
                            }
                        }
                        else
                        {
                            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedSuitCheck, 200, false, suitSlotArr.Get(i), suitArr.Get(i), item);
                        }
                    }
                }
            }
            
        }
    }

    void DelayedSuitCheck(string slot, string suitItem, ItemBase parent)
    {
        ItemBase itemOnSlot = ItemBase.Cast(FindAttachmentBySlotName(slot));
        if (itemOnSlot)
        {
			if (!itemOnSlot.IsKindOf(suitItem))
            {
				DropItemOnSlot(slot);
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CreateItemOnSlot, 200, false, slot, suitItem, parent);
            }
            else
            {
				SetLockOnSlot(itemOnSlot, true);
            }
        }
        else
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CreateItemOnSlot, 200, false, slot, suitItem, parent);
        }
    }
    void DelayedSuitCheckDetach(string slot, string suitItem)
    {
        ItemBase itemOnSlot = ItemBase.Cast(FindAttachmentBySlotName(slot));
        if (itemOnSlot)
        {
            if (itemOnSlot.IsKindOf(suitItem))
			{
				DeleteItemOnSlot(suitItem, slot);
			}
        }
    }

    void CreateItemOnSlot(string slot_name, string item_name, ItemBase parent)
    {
        ItemBase suit_item = ItemBase.Cast(GetInventory().CreateAttachmentEx(item_name, InventorySlots.GetSlotIdFromString(slot_name)));

        if (suit_item)
        {
            float max = suit_item.GetMaxHealth("", "");
            int hp = parent.GetHealthLevel("");
            switch ( hp )
            {
                case GameConstants.STATE_PRISTINE:
                    suit_item.SetHealth("", "", max * GameConstants.DAMAGE_PRISTINE_VALUE);
                    break;
                case GameConstants.STATE_BADLY_DAMAGED:
                    suit_item.SetHealth("", "", max * GameConstants.DAMAGE_BADLY_DAMAGED_VALUE);
                break;

                case GameConstants.STATE_DAMAGED:
                    suit_item.SetHealth("", "", max * GameConstants.DAMAGE_DAMAGED_VALUE);
                    break;

                case GameConstants.STATE_WORN:
                    suit_item.SetHealth("", "", max * GameConstants.DAMAGE_WORN_VALUE);
                    break;
                
                case GameConstants.STATE_RUINED:
                    suit_item.SetHealth("", "", max * GameConstants.DAMAGE_RUINED_VALUE);
                    break;
                    
                default:
                    break;
            }
			SetLockOnSlot(suit_item, true);	
        }
    }
	void DeleteItemOnSlot(string item_name, string slot)
	{
		vector extents = ".25 0 .25";
        ItemBase itemOnSlot = ItemBase.Cast(FindAttachmentBySlotName(slot));
        if (itemOnSlot)
        {
			// Only delete and unlock if the slot's item is equal to a suit item.
			//if (itemOnSlot.GetType() == item_name)
            if (itemOnSlot.IsKindOf(item_name))
			{
				MiscGameplayFunctions.DropAllItemsInInventoryInBounds(itemOnSlot, extents);
				SetLockOnSlot(itemOnSlot, false);
                itemOnSlot.DeleteSafe();
			}
        }
	}
	void DropItemOnSlot(string slot)
	{
		ItemBase itemOnSlot = ItemBase.Cast(FindAttachmentBySlotName(slot));
		if (itemOnSlot)
		{
			ServerDropEntity(itemOnSlot);
		}	
	}
	
	void SetLockOnSlot(ItemBase item, bool locked)
	{
		if (item)
        {
            //Store slot location.
            InventoryLocation inventory_location = new InventoryLocation;

            // Stores the InventoryLocation in inventory_location
            item.GetInventory().GetCurrentInventoryLocation( inventory_location );

            // Unlocks/Locks the slot at the location of inventory_location.
            GetInventory().SetSlotLock( inventory_location.GetSlot(), locked );
        }
	}
	
	void CheckSlotsForItemsAndUnlock()
	{
		foreach(string slot: SUIT_SLOT_NAMES)
		{
			if (!FindAttachmentBySlotName(slot))
			{
				GetInventory().SetSlotLock( InventorySlots.GetSlotIdFromString(slot), false );
			}
		}
	}

    // Not implemented, but this would allow for suits to be ruined on death. For now it just calls the original EEKilled function.
    override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
    }


    // Not implemented, allows for specific slots to be displayed if you wanted to hide stuff like.... hidden items.
    override bool CanDisplayAttachmentSlot(int slot_id)
	{
		// string slotName = InventorySlots.GetSlotName(slot_id);

		return super.CanDisplayAttachmentSlot(slot_id);
	}
	
};
