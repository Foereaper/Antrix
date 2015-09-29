/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef _OBJECT_H
#define _OBJECT_H

class Unit;

enum HIGHGUID {
    HIGHGUID_PLAYER        = 0x00000000,
    HIGHGUID_UNIT          = 0x00000001,
    HIGHGUID_GAMEOBJECT    = 0x00000002,
    HIGHGUID_CORPSE        = 0x00000003,
    HIGHGUID_DYNAMICOBJECT = 0x00000004,
    HIGHGUID_ITEM          = 0x00000005,
    HIGHGUID_CONTAINER     = 0x00000006,
    HIGHGUID_WAYPOINT      = 0x00000007,
    HIGHGUID_TRANSPORTER   = 0x00000008,
    HIGHGUID_PET           = 0x00000009,
};

// TODO: fix that type mess

enum TYPE {
    TYPE_OBJECT         = 1,
    TYPE_ITEM           = 2,
    TYPE_CONTAINER      = 4,
    TYPE_UNIT           = 8,
    TYPE_PLAYER         = 16,
    TYPE_GAMEOBJECT     = 32,
    TYPE_DYNAMICOBJECT  = 64,
    TYPE_CORPSE         = 128,
    TYPE_AIGROUP        = 256,
    TYPE_AREATRIGGER    = 512,
};

enum TYPEID {
    TYPEID_OBJECT        = 0,
    TYPEID_ITEM          = 1,
    TYPEID_CONTAINER     = 2,
    TYPEID_UNIT          = 3,
    TYPEID_PLAYER        = 4,
    TYPEID_GAMEOBJECT    = 5,
    TYPEID_DYNAMICOBJECT = 6,
    TYPEID_CORPSE        = 7,
    TYPEID_AIGROUP       = 8,
    TYPEID_AREATRIGGER   = 9,
    TYPEID_UNUSED            = 10,//used to signal invalid reference (object dealocated but someone is still using it)
};

enum OBJECT_UPDATE_TYPE {
    UPDATETYPE_VALUES = 0,
    //  8 bytes - GUID
    //  Goto Update Block
    UPDATETYPE_MOVEMENT = 1,
    //  8 bytes - GUID
    //  Goto Position Update
    UPDATETYPE_CREATE_OBJECT = 2,
    //  8 bytes - GUID
    //  1 byte - Object Type (*)
    //  Goto Position Update
    //  Goto Update Block
    UPDATETYPE_CREATE_YOURSELF = 3, // looks like 3 & 4 do the same thing
    //  4 bytes - Count
    //  Loop Count Times:
    //  8 bytes - GUID
    UPDATETYPE_OUT_OF_RANGE_OBJECTS = 4 // <- this is correct, not sure about 3
    //  4 bytes - Count
    //  Loop Count Times:
    //  8 bytes - GUID

};

class WorldPacket;
class ByteBuffer;
class WorldSession;
class Player;
class MapCell;
class MapMgr;

//====================================================================
//  Object
//  Base object for every item, unit, player, corpse, container, etc
//====================================================================
class SERVER_DECL Object : public EventableObject
{
public:
    typedef std::set<Object*> InRangeSet;

    virtual ~Object ( );

    virtual void Update ( uint32 time ) { }
  //! True if object exists in world
 
    
    inline bool IsInWorld() { return m_mapMgr != NULL; }
    virtual void AddToWorld();
    void PushToWorld(MapMgr*);
    virtual void OnPushToWorld() { }
    virtual void RemoveFromWorld();

    // guid always comes first
    inline const uint64& GetGUID() const { return *((uint64*)m_uint32Values); }
    inline const WoWGuid& GetNewGUID() const { return m_wowGuid; }
    inline uint32 GetEntry(){return m_uint32Values[3];}
    
    inline const uint32& GetGUIDLow() const { return m_uint32Values[0]; }
    inline const uint32& GetGUIDHigh() const { return m_uint32Values[1]; }

    // type
    inline const uint8& GetTypeId() const { return m_objectTypeId; }
    inline bool IsPlayer() { return m_objectTypeId == TYPEID_PLAYER; }

    //! This includes any nested objects we have, inventory for example.
    virtual uint32 __fastcall BuildCreateUpdateBlockForPlayer( ByteBuffer *data, Player *target );
    uint32 __fastcall BuildValuesUpdateBlockForPlayer( ByteBuffer *buf, Player *target );
    uint32 __fastcall BuildOutOfRangeUpdateBlock( ByteBuffer *buf );

    WorldPacket* BuildFieldUpdatePacket(uint32 index,uint32 value);
    void BuildFieldUpdatePacket(Player* Target, uint32 Index, uint32 Value);
    void BuildFieldUpdatePacket(ByteBuffer * buf, uint32 Index, uint32 Value);

    void DealDamage(Unit *pVictim, uint32 damage, uint32 targetEvent, uint32 unitEvent, uint32 spellId, bool no_remove_auras = false);
    

    virtual void DestroyForPlayer( Player *target ) const;

    void BuildHeartBeatMsg( WorldPacket *data ) const;
    WorldPacket * BuildTeleportAckMsg( const LocationVector & v);
    bool IsBeingTeleported() { return mSemaphoreTeleport; }
    void SetSemaphoreTeleport(bool semphsetting) { mSemaphoreTeleport = semphsetting; }

    bool SetPosition( float newX, float newY, float newZ, float newOrientation, bool allowPorting = false );
    bool SetPosition( const LocationVector & v, bool allowPorting = false);
    void SetRotation( uint64 guid );

    inline const float& GetPositionX( ) const { return m_position.x; }
    inline const float& GetPositionY( ) const { return m_position.y; }
    inline const float& GetPositionZ( ) const { return m_position.z; }
    inline const float& GetOrientation( ) const { return m_position.o; }
    inline void SetOrientation( float &o ) { m_position.o = o; }

    inline const float& GetSpawnX( ) const { return m_spawnLocation.x; }
    inline const float& GetSpawnY( ) const { return m_spawnLocation.y; }
    inline const float& GetSpawnZ( ) const { return m_spawnLocation.z; }
    inline const float& GetSpawnO( ) const { return m_spawnLocation.o; }

    inline const LocationVector & GetPosition() { return m_position; }

    //Distance Calculation
    float CalcDistance(Object* Ob);
    float CalcDistance(float ObX, float ObY, float ObZ);
    float CalcDistance(Object *Oa, Object *Ob);
    float CalcDistance(Object *Oa, float ObX, float ObY, float ObZ);
    float CalcDistance(float OaX, float OaY, float OaZ, float ObX, float ObY, float ObZ);

    //! Only for MapMgr use
    inline MapCell* GetMapCell() const { return m_mapCell; }
    //! Only for MapMgr use
    inline void SetMapCell(MapCell* cell) { m_mapCell = cell; }
    //! Only for MapMgr use
    inline MapMgr* GetMapMgr() const { return m_mapMgr; }

    inline void SetMapId(uint32 newMap) { m_mapId = newMap; }
    void SetZoneId(uint32 newZone);

    inline const uint32 GetMapId( ) const { return m_mapId; }
    inline const uint32& GetZoneId( ) const { return m_zoneId; }

    //! Get uint32 property
    inline const uint32& GetUInt32Value( uint32 index ) const
    {
        ASSERT( index < m_valuesCount );
        return m_uint32Values[ index ];
    }

    //! Get uint64 property
    inline const uint64& GetUInt64Value( uint32 index ) const
    {
        ASSERT( index + uint32(1) < m_valuesCount );
        return *((uint64*)&(m_uint32Values[ index ]));
    }

    //! Get float property
    inline const float& GetFloatValue( uint32 index ) const
    {
        ASSERT( index < m_valuesCount );
        return m_floatValues[ index ];
    }

    void __fastcall ModFloatValue(const uint32 index, const float value );
    void ModPFloatValue(const uint32 index, const float value, bool apply);
    void ModUInt32Value(uint32 index, int32 value);
//    void ModPUInt32Value(const uint32 index, const int32 value, bool apply);
    uint32 GetModPUInt32Value(const uint32 index, const int32 value);

    //! Set uint32 property
    void SetByte(uint32 index, uint32 index1,uint8 value);

    inline uint8 GetByte(uint32 i,uint32 i1)
    {
        ASSERT( i < m_valuesCount);
        ASSERT(i1 < 4);
        return ((uint8*)m_uint32Values)[i*4+i1];
    }
    
    void __fastcall SetUInt32Value( const uint32 index, const uint32 value );

    //! Set uint64 property
    void __fastcall SetUInt64Value( const uint32 index, const uint64 value );

    //! Set float property
    void __fastcall SetFloatValue( const uint32 index, const float value );

    void __fastcall SetFlag( const uint32 index, uint32 newFlag );

    void __fastcall RemoveFlag( const uint32 index, uint32 oldFlag );

    inline bool HasFlag( const uint32 index, uint32 flag ) const
    {
        ASSERT( index < m_valuesCount );
        return (m_uint32Values[ index ] & flag) != 0;
    }
    
    ////////////////////////////////////////
    void ClearUpdateMask( )
    {
        m_updateMask.Clear();
        m_objectUpdated = false;
    }

    bool HasUpdateField(uint32 index)
    {
        ASSERT( index < m_valuesCount);
        return m_updateMask.GetBit(index);
    }

    //use it to check if a object is in range of another
    bool isInRange(Object* target, float range);

    // Use it to Check if a object is in front of another one
    bool isInFront(Object* target);
    bool isInBack(Object* target);
    /* Calculates the angle between two Positions */
    float calcAngle( float Position1X, float Position1Y, float Position2X, float Position2Y );
    float calcRadAngle( float Position1X, float Position1Y, float Position2X, float Position2Y );

    /* converts to 360 > x > 0 */
    float getEasyAngle( float angle );

    inline const float GetDistanceSq(Object* obj)
    {
        if(obj->GetMapId() != m_mapId) return 40000.0f; //enough for out of range
        return m_position.DistanceSq(obj->GetPosition());
    }

    inline float GetDistanceSq(LocationVector & comp)
    {
        return comp.DistanceSq(m_position);
    }

    inline float CalcDistance(LocationVector & comp)
    {
        return comp.Distance(m_position);
    }

    inline const float GetDistanceSq(float x, float y, float z)
    {
        return m_position.DistanceSq(x, y, z);
    }

    inline const float GetDistance2dSq(Object* obj)
    {
        if(obj->GetMapId() != m_mapId) return 40000.0f; //enough for out of range
        return m_position.Distance2DSq(obj->m_position);
    }

    // In-range object management, not sure if we need it
    inline bool IsInRangeSet(Object* pObj) { return !(m_objectsInRange.find(pObj) == m_objectsInRange.end()); }
    
    inline virtual void AddInRangeObject(Object* pObj)
    {
#ifdef _DEBUG
        if(!pObj)
        {
            sLog.outError("ERROR : trying to add a null object from inrange set");
            return;//wellt his should not happen, but theory is far from practice
        }
#endif
        m_objectsInRange.insert(pObj);
        if(pObj->GetTypeId() == TYPEID_PLAYER)
            m_inRangePlayers.insert( ((Player*)pObj) );
    }
    inline virtual void RemoveInRangeObject(Object* pObj)
    {
#ifdef _DEBUG
        if(!pObj)
        {
            sLog.outError("ERROR : trying to remove a null object from inrange set");
            return;//wellt his should not happen, but theory is far from practice
        }
#endif
        m_objectsInRange.erase(pObj);
        if(pObj->GetTypeId() == TYPEID_PLAYER)
            ASSERT(m_inRangePlayers.erase( ((Player*)pObj) ) == 1);
    }

    virtual void ClearInRangeSet()
    {
        m_objectsInRange.clear();
        m_inRangePlayers.clear();
        m_oppFactsInRange.clear();
    }

    inline uint32 GetInRangeCount() { return m_objectsInRange.size(); }
    inline InRangeSet::iterator GetInRangeSetBegin() { return m_objectsInRange.begin(); }
    inline InRangeSet::iterator GetInRangeSetEnd() { return m_objectsInRange.end(); }

    bool IsInRangeOppFactSet(Object* pObj) { return (m_oppFactsInRange.count(pObj) > 0); }
    void UpdateOppFactionSet();
    inline std::set<Object*>::iterator GetInRangeOppFactsSetBegin() { return m_oppFactsInRange.begin(); }
    inline std::set<Object*>::iterator GetInRangeOppFactsSetEnd() { return m_oppFactsInRange.end(); }
    inline std::set<Player*>::iterator GetInRangePlayerSetBegin() { return m_inRangePlayers.begin(); }
    inline std::set<Player*>::iterator GetInRangePlayerSetEnd() { return m_inRangePlayers.end(); }
    inline std::set<Player*> * GetInRangePlayerSet() { return &m_inRangePlayers; };

    void __fastcall SendMessageToSet(WorldPacket *data, bool self,bool myteam_only=false);
    inline void SendMessageToSet(StackBufferBase * data, bool self) { OutPacketToSet(data->GetOpcode(), data->GetSize(), data->GetBufferPointer(), self); }
    void OutPacketToSet(uint16 Opcode, uint16 Len, const void * Data, bool self);

    //! Fill values with data from a space seperated string of uint32s.
    void LoadValues(const char* data);

    inline uint16 GetValuesCount() const { return m_valuesCount; }

    //! Blizzard seem to send those for all object types. weird.
    float m_walkSpeed;
    float m_runSpeed;
    float m_backWalkSpeed;
    float m_swimSpeed;
    float m_backSwimSpeed;
    float m_turnRate;
    float m_flySpeed;
    float m_backFlySpeed;
    
    inline bool IsUnit()//creature or player
    {
        return ( m_objectTypeId == TYPEID_UNIT || m_objectTypeId == TYPEID_PLAYER); 
    }
    void EventSpellDamage(uint64 Victim, uint32 SpellID, uint32 Damage);
    void SpellNonMeleeDamageLog(Unit *pVictim, uint32 spellID, uint32 damage, bool allowProc, bool no_remove_auras = false);
    
    //*****************************************************************************************
    //* SpellLog packets just to keep the code cleaner and better to read
    //*****************************************************************************************
    void SendSpellLog(Object *Caster, Object *Target,uint32 Ability, uint8 SpellLogType);
    void SendSpellNonMeleeDamageLog(Object * Caster, Object * Target,uint32 SpellID,uint32 Damage, uint8 Damage_Type,uint32 AbsorbedDamage, uint32 ResistedDamage,bool PhysicalDamage, uint32 BlockedDamage, bool CriticalHit, bool bToSet);
    
    bool IsPet();
    
    //object faction
    void _setFaction();
    uint32 _getFaction(){return m_faction->Faction;}
    
    FactionTemplateDBC *m_faction;
    FactionDBC *m_factionDBC;

    inline void SetInstanceID(int32 instance) { m_instanceId = instance; }
    inline int32 GetInstanceID() { return m_instanceId; }

    int32 event_GetInstanceID();

    bool Active;
    bool CanActivate();
    void Activate(MapMgr * mgr);
    void Deactivate(MapMgr * mgr);
    bool m_inQueue;
    inline void SetMapMgr(MapMgr * mgr) { m_mapMgr = mgr; }

    void Delete()
    {
        if(IsInWorld())
            RemoveFromWorld();
        delete this;
    }

    void GMScriptEvent(void * function, uint32 argc, uint32 * argv, uint32 * argt);

protected:
    Object (  );

    //void _Create (uint32 guidlow, uint32 guidhigh);
    void _Create( uint32 mapid, float x, float y, float z, float ang);

    //! Mark values that need updating for specified player.
    virtual void _SetUpdateBits(UpdateMask *updateMask, Player *target) const;
    //! Mark values that player should get when he/she/it sees object for first time.
    virtual void _SetCreateBits(UpdateMask *updateMask, Player *target) const;

    void _BuildMovementUpdate( ByteBuffer *data, uint8 flags, uint32 flags2, Player* target );
    void _BuildValuesUpdate( ByteBuffer *data, UpdateMask *updateMask, Player* target );

    /* Main Function called by isInFront(); */
    bool inArc(float Position1X, float Position1Y, float FOV, float Orientation, float Position2X, float Position2Y );

    //! WoWGuid class
    WoWGuid m_wowGuid;

     //! Type id.
    uint8 m_objectTypeId;

    //! Zone id.
    uint32 m_zoneId;
    //! Continent/map id.
    uint32 m_mapId;
    //! Map manager
    MapMgr *m_mapMgr;
    //! Current map cell
    MapCell *m_mapCell;

    LocationVector m_position;
    LocationVector m_spawnLocation;

    // Semaphores - needed to forbid two operations on the same object at the same very time (may cause crashing\lack of data)
    bool mSemaphoreTeleport;

    //! Object properties.
    union {
        uint32 *m_uint32Values;
        float *m_floatValues;
    };

    //! Number of properties
    uint32 m_valuesCount;

    //! List of object properties that need updating.
    UpdateMask m_updateMask;

    //! True if object was updated
    bool m_objectUpdated;

    //! Set of Objects in range.
    //! TODO: that functionality should be moved into WorldServer.
    std::set<Object*> m_objectsInRange;
    std::set<Player*> m_inRangePlayers;
    std::set<Object*> m_oppFactsInRange;
   
  
    //! Remove object from map
    void _RemoveFromMap();

    int32 m_instanceId;
};

#endif


