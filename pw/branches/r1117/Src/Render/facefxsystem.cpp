#include "stdafx.h"
#include "facefxsystem.h"

#include "../Vendor/FaceFX/include/FxSDK.h"
#include "../Vendor/FaceFX/include/FxActor.h"
#include "../Vendor/FaceFX/include/FxActorInstance.h"

using namespace OC3Ent::Face;

namespace Render
{
namespace FaceFXSystem
{
///
void Init()
{
	// Start up the FaceFX SDK with its default allocation policy.
	FxMemoryAllocationPolicy allocationPolicy;
	allocationPolicy.allocationType = MAT_Heap;
	allocationPolicy.bUseMemoryPools = FxFalse;
	allocationPolicy.userAllocate = 0;
	allocationPolicy.userAllocateDebug = 0;
	allocationPolicy.userFree = 0;
	
	// Loads an actor from the file using the fast method (reading the entire
	// file into memory and serializing once the entire actor is in memory.)

	FxSDKStartup( allocationPolicy );


	//boneList.GetRefBone(0).ge
//	pActor->GetAnimPtr()->Get

	//delete pActor;
}
///
void Release()
{
	// Shut down the FaceFX SDK.
	FxSDKShutdown();
}
}; // namespace FaceFX
}; // namespace Render