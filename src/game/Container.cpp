#include "StdAfx.h"

Container::Container(uint32 high,uint32 low) : Item()
{
    m_objectTypeId = TYPEID_CONTAINER;
    m_valuesCount = CONTAINER_END;
    m_uint32Values = __fields;
    memset(m_uint32Values, 0,(CONTAINER_END)*sizeof(uint32));
    m_updateMask.SetCount(CONTAINER_END);
    SetUInt32Value( OBJECT_FIELD_TYPE,TYPE_CONTAINER|TYPE_ITEM|TYPE_OBJECT);
    SetUInt32Value( OBJECT_FIELD_GUID,low);
    SetUInt32Value( OBJECT_FIELD_GUID+1,high);
    m_wowGuid.Init(GetGUID());

    SetFloatValue( OBJECT_FIELD_SCALE_X, 1 );//always 1


    m_Slot = NULL;
}

Container::~Container( )
{
   for(uint32 i = 0; i < m_itemProto->ContainerSlots; i++)
    {
        if(m_Slot[i])
        {
            if(m_Slot[i]->IsContainer())
                delete ((Container*)m_Slot[i]);
            else
                delete m_Slot[i];
        }
    }

    delete [] m_Slot;
}
void Container::LoadFromDB( Field*fields )
{

    uint32 itemid=fields[2].GetUInt32();
    m_itemProto = ItemPrototypeStorage.LookupEntry( itemid );

    ASSERT(m_itemProto);
    SetUInt32Value( OBJECT_FIELD_ENTRY, itemid );
    

    SetUInt32Value( ITEM_FIELD_CREATOR, fields[3].GetUInt32() );
    SetUInt32Value( ITEM_FIELD_STACK_COUNT, 1);
    
    SetUInt32Value( ITEM_FIELD_FLAGS, fields[6].GetUInt32());
    SetUInt32Value( ITEM_FIELD_RANDOM_PROPERTIES_ID, fields[7].GetUInt32());

    SetUInt32Value( ITEM_FIELD_MAXDURABILITY, m_itemProto->MaxDurability);
    SetUInt32Value( ITEM_FIELD_DURABILITY, fields[9].GetUInt32());
  

    SetUInt32Value( CONTAINER_FIELD_NUM_SLOTS, m_itemProto->ContainerSlots);

    m_Slot = new Item*[m_itemProto->ContainerSlots];
    memset(m_Slot, 0, sizeof(Item*)*(m_itemProto->ContainerSlots));

}

void Container::Create( uint32 itemid, Player *owner )
{

    m_itemProto = ItemPrototypeStorage.LookupEntry( itemid );
    ASSERT(m_itemProto);

    SetUInt32Value( OBJECT_FIELD_ENTRY, itemid );
    SetUInt64Value( ITEM_FIELD_OWNER, owner->GetGUID() );
    SetUInt64Value( ITEM_FIELD_CONTAINED, owner->GetGUID() );
    SetUInt32Value( ITEM_FIELD_STACK_COUNT, 1 );
    SetUInt32Value( CONTAINER_FIELD_NUM_SLOTS, m_itemProto->ContainerSlots);

    m_Slot = new Item*[m_itemProto->ContainerSlots];
    memset(m_Slot, 0, sizeof(Item*)*(m_itemProto->ContainerSlots));

    m_owner = owner;
}


int8 Container::FindFreeSlot()
{
    int8 TotalSlots = GetUInt32Value( CONTAINER_FIELD_NUM_SLOTS );
    for (int8 i=0; i < TotalSlots; i++)
    {
        if(!m_Slot[i]) 
        { 
            return i; 
        }
    }
    return ITEM_NO_SLOT_AVAILABLE;
}

bool Container::HasItems()
{
    int8 TotalSlots = GetUInt32Value( CONTAINER_FIELD_NUM_SLOTS );
    for (int8 i=0; i < TotalSlots; i++)
    {
        if(m_Slot[i]) 
        { 
            return true; 
        }
    }
    return false;
}

bool Container::AddItem(int8 slot, Item *item)
{
    if((uint32)slot > m_itemProto->ContainerSlots)
        return false;

    //ASSERT(m_Slot[slot] == NULL);
    if(m_Slot[slot] != NULL)
    {
        //sLog.outString("Bad container item %u slot %d", item->GetGUID(), slot);
        return false;
    }

    if (!m_owner)
        return false;

    m_Slot[slot] = item;
    item->m_isDirty = true;

    item->SetUInt64Value(ITEM_FIELD_CONTAINED, GetGUID());
    item->SetOwner(m_owner);

    if (item->GetProto()->Bonding == ITEM_BIND_ON_PICKUP) 
        item->SoulBind();

    SetUInt64Value(CONTAINER_FIELD_SLOT_1  + (slot*2), item->GetGUID());

    //new version to fix bag issues
    if(m_owner->IsInWorld() && !item->IsInWorld())
    {
        //item->AddToWorld();
        item->PushToWorld(m_owner->GetMapMgr());

        ByteBuffer buf(2500);
        uint32 count = item->BuildCreateUpdateBlockForPlayer(&buf, m_owner);
        m_owner->PushUpdateData(&buf, count);
    }
    return true;
}

void Container::SwapItems(int8 SrcSlot, int8 DstSlot)
{
    Item *temp;
    if(m_Slot[DstSlot] &&  m_Slot[SrcSlot]&&m_Slot[DstSlot]->GetEntry()==m_Slot[SrcSlot]->GetEntry() && m_Slot[DstSlot]->GetProto()->MaxCount>1)
    {
        uint32 total=m_Slot[SrcSlot]->GetUInt32Value(ITEM_FIELD_STACK_COUNT)+m_Slot[DstSlot]->GetUInt32Value(ITEM_FIELD_STACK_COUNT);
        m_Slot[DstSlot]->m_isDirty = m_Slot[SrcSlot]->m_isDirty = true;
        if(total<=m_Slot[DstSlot]->GetProto()->MaxCount)
        {
            m_Slot[DstSlot]->ModUInt32Value(ITEM_FIELD_STACK_COUNT,m_Slot[SrcSlot]->GetUInt32Value(ITEM_FIELD_STACK_COUNT));
            SafeFullRemoveItemFromSlot(SrcSlot);
            return;
        }
        else
        {
            if(m_Slot[DstSlot]->GetUInt32Value(ITEM_FIELD_STACK_COUNT) == m_Slot[DstSlot]->GetProto()->MaxCount)
            {

            }
            else
            {
                int32 delta=m_Slot[DstSlot]->GetProto()->MaxCount-m_Slot[DstSlot]->GetUInt32Value(ITEM_FIELD_STACK_COUNT);
                m_Slot[DstSlot]->SetUInt32Value(ITEM_FIELD_STACK_COUNT,m_Slot[DstSlot]->GetProto()->MaxCount);
                m_Slot[SrcSlot]->ModUInt32Value(ITEM_FIELD_STACK_COUNT,-delta);
                return;
            }
        }
    }
   
    temp = m_Slot[SrcSlot];
    m_Slot[SrcSlot] = m_Slot[DstSlot];
    m_Slot[DstSlot] = temp;

    if( m_Slot[DstSlot])
    {
        SetUInt64Value(CONTAINER_FIELD_SLOT_1  + (DstSlot*2),  m_Slot[DstSlot]->GetGUID()  );
        m_Slot[DstSlot]->m_isDirty = true;
    }
    else
    {
        SetUInt64Value(CONTAINER_FIELD_SLOT_1  + (DstSlot*2), 0 );
    }

    if( m_Slot[SrcSlot])
    {
        SetUInt64Value(CONTAINER_FIELD_SLOT_1  + (SrcSlot*2), m_Slot[SrcSlot]->GetGUID() );
        m_Slot[SrcSlot]->m_isDirty = true;
    }
    else
    {
        SetUInt64Value(CONTAINER_FIELD_SLOT_1  + (SrcSlot*2), 0 );
    }
}

Item *Container::SafeRemoveAndRetreiveItemFromSlot(int8 slot, bool destroy)
{
    ASSERT((uint32)slot < GetProto()->ContainerSlots);

    Item *pItem = m_Slot[slot];

    if (pItem == NULL) return NULL;
    m_Slot[slot] = NULL;

    SetUInt64Value(CONTAINER_FIELD_SLOT_1  + slot*2, 0 );
    pItem->SetUInt64Value(ITEM_FIELD_CONTAINED, 0);

    if(destroy)
    {
        if(pItem->IsInWorld())
        {
            pItem->RemoveFromWorld();
        }
        pItem->DeleteFromDB();
    }

    return pItem;
}

bool Container::SafeFullRemoveItemFromSlot(int8 slot)
{
    ASSERT((uint32)slot < GetProto()->ContainerSlots);

    Item *pItem = m_Slot[slot];

    if (pItem == NULL) return false;
    m_Slot[slot] = NULL;

    SetUInt64Value(CONTAINER_FIELD_SLOT_1  + slot*2, 0 );
    pItem->SetUInt64Value(ITEM_FIELD_CONTAINED, 0);

    if(pItem->IsInWorld())
    {
        pItem->RemoveFromWorld();
    }
    pItem->DeleteFromDB();
    delete pItem;

    return true;
}

bool Container::AddItemToFreeSlot(Item *pItem)
{
    uint32 slot;
    for(slot = 0; slot < GetProto()->ContainerSlots; slot++)
    {
        if(!m_Slot[slot])
        {
            m_Slot[slot] = pItem;
            pItem->m_isDirty = true;

            pItem->SetUInt64Value(ITEM_FIELD_CONTAINED, GetGUID());
            pItem->SetOwner(m_owner);

            SetUInt64Value(CONTAINER_FIELD_SLOT_1  + (slot*2), pItem->GetGUID());

            if(m_owner->IsInWorld() && !pItem->IsInWorld())
            {
                //pItem->AddToWorld();
                pItem->PushToWorld(m_owner->GetMapMgr());
                ByteBuffer buf(2500);
                uint32 count = pItem->BuildCreateUpdateBlockForPlayer( &buf, m_owner );
                m_owner->PushUpdateData(&buf, count);
            }
            return true;
        }
    }
    return false;
}


void Container::SaveBagToDB(int8 slot, bool first)
{
    ((Item*)this)->SaveToDB(INVENTORY_SLOT_NOT_SET, slot);

    for(uint32 i = 0; i < m_itemProto->ContainerSlots; i++)
    {
        if (m_Slot[i])
        {
            m_Slot[i]->SaveToDB(slot, i, first);
        }
    }
}


