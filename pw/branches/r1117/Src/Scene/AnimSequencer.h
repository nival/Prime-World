#pragma once
#include "SceneTypes.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
    class SkeletalMesh;
    class RenderComponent;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AnimPos
{
    CVec3 pos;
    float yaw;
    float pitch;
    float roll;
    AnimPos() : pos(VNULL3), yaw(0), pitch(0), roll(0) {} 
    AnimPos( const CVec3 &_pos ) : pos(_pos), yaw(0), pitch(0), roll(0) {} 
    AnimPos( const CVec3 &_pos, float _yaw, float _pitch, float _roll ) : pos(_pos), yaw(_yaw), pitch(_pitch), roll(_roll) {} 
    AnimPos( const CVec3 &_pos, const CQuat &_rot );
    AnimPos( const SHMatrix &m );
    AnimPos( const Matrix43 &m );
    void FillMatrix( SHMatrix *pRes ) const;
    void GetDir( CVec3 *pRes ) const;
    void GetRotation( CQuat *pRes ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EAnimAction
{
    AA_INVALID,           // mark default animation info as invalid  
    AA_INVISIBLE,                   // special action of invisibility
    AA_IDLE,                            // cyclic, endless action at place,
                                                // useful for idles, "before times" and "after times" animations
    AA_ONESHOT_STILL,           // one-shot action which freezes forever at it's last frame
    AA_ONESHOT,                     // one-shot action 
    AA_NON_ESSENTIAL,           // one-shot optional action at place, which would be taken place
                                                // only if 1) object doesn't perform any actions at the moment
                                                // (with exclusion for IDLE), 2) doesn't have pending actions
                                                // all ONESHOT, MOVE, NON_ESSENTIAL automatically followed by an IDLE
    AA_COUNT__
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SMoveAnimationOptions
{
    bool useYaw;
    bool usePitch;
    bool useRoll;
    bool useStartPos;
    bool useEndPos;
    Time startBlend;
    Time endBlend;
    SMoveAnimationOptions() : useYaw(false),usePitch(false),useRoll(false),useStartPos(true), useEndPos(true), startBlend(0), endBlend(0) {}
};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
