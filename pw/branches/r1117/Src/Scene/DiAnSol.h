#ifndef DI_ANSOL_H
#define DI_ANSOL_H

/**
@file
@brief    Solid memory block. @ref anim_AB file memory image processing routines
@date     Created on 25/08/2000
@project  skeleton
@author   Miron
*/

/****************************************************************************
Includes
*/
//#include "DiClump.h"

///eugbelNSCENE///namespace NScene {

/****************************************************************************
Defines & Types
*/
// animation file header signature
#define diANIMIO_SIGNATURE        (0x4E414944L)  ///< reads 'DIAN'

// animation file format version
#define diANIMIO_VERSION          400 ///< current version of @ref anim_AB file

#define DIAN_FTE_SIGN  0x20455446  ///< reads 'FTE '

/**
@brief @ref anim_AB file header on disk
*/
typedef struct tagDiAnimFileLeadingBlock
{
  DiInt32   nSign;      ///< diANIMIO_SIGNATURE expected
  DiInt32   nVersion;   ///< diANIMIO_VERSION expected
  DiInt32   nSeqsCount; ///< number of sequences in @ref anim_AB file
  DiUInt32  uAllocSize; ///< number of bytes required for memory image  
  DiUInt32  uFileBodySize;  ///< entire size of data stored in file (size to pass for read command)
} DiAnimFileLeadingBlock;

/** 
@brief pointer to array, each element has length diFRAMEID_NAMELENGTH 
*/
typedef DiTChar    (*DiAnimNamesArray)[diFRAMEID_NAMELENGTH];

/*==============================================================
 memory structures, their layout:
  DiEntireAnimBlock
  DiaSeqTable
  [] SeqTops
  [] NodesCountBySeq
  DiaFrameTable
  [] DiaFrameTableEntry
  [] Paths
  SeqTop1
  Node_src1_1
  ...
  Node_src1_N
  Pos1_1
  Quat1_1
  ...
  Pos1_N
  Quat1_N
  SeqTop2
  ...
  SeqTopK
  ...
 */

#pragma warning( disable : 4200 )

/**
@brief Animation sequence table in @ref anim_AB file memory image
*/
typedef struct tagDiaSeqTable
{
  DiInt32       nSeqsCount;         ///< number of sequences in file
  DiInt32       *npNodesCountBySeq; ///< pinter to "number of nodes in sequence" array
  DiUInt32      naAlignFields[2];
  DiInt32*      *astpaSeqTops[0];   ///< always keep at tail. Fake "no-pointer" array
} DiaSeqTable;

#define diANIM_NAMELENGTH        28 

/**
@brief Per frame structure that defines all animation sequences in data block for given frame
*/
typedef struct tagDiaFrameTableEntry
{
  DiInt32       nSign;     ///< always equal to DIAN_FTE_SIGN     
  DiTChar       caFrameName[diANIM_NAMELENGTH]; ///< Frame name mentioned animation tracks belongs to
  DiInt32       *anpaPaths[0]; ///< always keep at tail. Fake "no-pointer" array. All animation tracks for given frame
} DiaFrameTableEntry;

#pragma warning( default : 4200 )

/**
@brief One global table header for all animation data (decomposed LTMs)
*/
typedef struct tagDiaFrameTable
{
  DiInt32       nEntriesCount; ///< number of entries
  DiInt32       nFilledCount;  ///< number of valid entries 
  DiInt32       nEntrySize;  /// size of each entry in bytes
  DiByte       *bpFirstEntry; ///Pointer to first entry
} DiaFrameTable;

/**
Layout of @ref anim_AB file in memory: <br>
DiEntireAnimBlock                      <br>
DiaSeqTable                            <br>
[] SeqTops                             <br>
[] NodesCountBySeq                     <br>
DiaFrameTable                          <br>
[] DiaFrameTableEntry                  <br>
[] Paths                               <br>
SeqTop1                                <br>
Node_src1_1                            <br>
...                                    <br>
Node_src1_N                            <br>
Pos1_1                                 <br>
Quat1_1                                <br>
...                                    <br>
Pos1_N                                 <br>
Quat1_N                                <br>
SeqTop2                                <br>
...                                    <br>
SeqTopK                                <br>
...                                    

@brief In-memory header of AB file image
*/
typedef struct tagDiEntireAnimBlock
{
  DiInt32       nReferenceCount;        ///< number of times this image has been referenced. Reference counter in short.
  DiaSeqTable   *stpSeqTable;           ///< pointer to sequence table
  DiaFrameTable *ftpFrameTable;         ///< pointers to frames, we have animation for, table
  DiUInt32      naAlignFields[1];
} DiEntireAnimBlock;

/*==============================================================
 .
 */

/****************************************************************************
Data access
*/


/****************************************************************************
Function prototypes
*/
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
See @ref DiAniSLoadFramedAnimationExt for details

@brief "normal" API user usage macro
*/
#define DiAniSLoadFramedAnimation(cpABFileName)            \
  DiAniSLoadFramedAnimationExt(cpABFileName, NULL, NULL)
                                             
/**
  This function creates a single referencing block from animation file.

 @brief    Create a single referencing block from animation file
 @return   in memory image of @ref anim_AB file. NULL returned in case of failure. 
 @param[in]   cpABFileName pointer to the AB file name
 @param[out]  cppSeqsNamesArray place where loading procedure will store textual names of sequences
 @param[in, out]  npNumSequencesUserAssumes number of elements in cppSeqsNamesArray. In case this number is too small cppSeqsNamesArray will not be filled. If npNumSequencesUserAssumes large then actual number of sequences in file, it will contain actual number of  sequence names filled
 @author  Miron
*/
extern DiEntireAnimBlock *DiAniSLoadFramedAnimationExt(DiTChar const *cpABFileName, 
                                                       DiAnimNamesArray cppSeqsNamesArray,
                                                       DiInt32 *npNumSequencesUserAssumes);

/**
 AnimScaleTimedModeSpeed - changes one sequence in loaded animation so that
     in timed mode it will be played faster or slower than recorded. 
     Use rScale>1 to speed up, rScale<1 to slow down.

 @param[in]   eapBlock loaded data to change
 @param[in]   nSeqIdx  seq to change
 @param[in]   rScale   the scale
 @author  Miron
*/
extern DiVoid DiAnimScaleTimedModeSpeed(DiEntireAnimBlock *eapBlock, DiInt32 nSeqIdx, DiFloat rScale);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

///eugbelNSCENE///} // end of namespace NScene

#endif /* DI_ANSOL_H */

