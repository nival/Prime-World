#include "StdAfx.h"
#include "ObjectFactory.h"
namespace NObjectFactory
{
void CheckTypes()
{
    for( vector<TypeToCheck>::const_iterator it = typesToCheck.begin(); it != typesToCheck.end(); ++it )
    {
        switch( it->typeId )
        {
        case 0x9A547BC0: //ClientSpellScriptMachine
        case 0x6254CB40: //ClientTownSceneObjectsManager
        case 0x6254CAC1: //ClientHeroSceneObjectsManager
            continue;
        }

        const int currentNew = GetMallocsTotal();
        CObj<CObjectBase> pObject = it->pfnNewFunc();
        const int newStep1 = GetMallocsTotal() - currentNew;
        pObject = 0;
        const int newStep2 = GetMallocsTotal() - currentNew;

        if ( newStep1 != 1 )
            OutputDebugStringA( NStr::StrFmt( "%s(%d): Type %s (0x%08X) has %d news in default constructor\n", it->file, it->line, it->type, it->typeId, newStep1 ) );

        if ( newStep2 != 0 )
            OutputDebugStringA( NStr::StrFmt( "%s(%d): Type %s (0x%08X) has %d unreleased news after create/destroy\n", it->file, it->line, it->type, it->typeId, newStep2 ) );
    }

    typesToCheck.clear();
}
}
