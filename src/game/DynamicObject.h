#ifndef WOWSERVER_DYNAMICOBJECT_H
#define WOWSERVER_DYNAMICOBJECT_H

struct SpellEntry;

typedef set<Unit*>  DynamicObjectList;
typedef set<Unit*>  FactionRangeList;

class SERVER_DECL DynamicObject : public Object
{
public:
	DynamicObject( uint32 high, uint32 low );
	~DynamicObject( );

	void Create(Unit * caster, Spell * pSpell, float x, float y, float z, uint32 duration, float radius);
	void UpdateTargets();

	void AddInRangeObject(Object* pObj);
	void RemoveInRangeObject(Object* pObj);
	void Remove();

protected:
	
	SpellEntry * m_spellProto;
	Unit * u_caster;
	Player * p_caster;
	Spell* m_parentSpell;
	DynamicObjectList targets;
	FactionRangeList  m_inRangeOppFactions;
	
	uint32 m_aliveDuration;
	uint32 _fields[DYNAMICOBJECT_END];
};

#endif

