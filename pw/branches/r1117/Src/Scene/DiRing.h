/************************************************************
 * HEADER NAME  DiRing.h
 * PURPOSE      List type "Ring"
 *
 * SPEC         26 sept 97, Miron
 *
 * SWITCHES     None
 * NOTES        None
 ************************************************************/

#ifndef __DIRING__
#define __DIRING__

/****************************************************************************
Includes
*/

//engine includes
#include "DiTypes.h"

/****************************************************************************
Defines & Types
*/

#define diOFFSETOF(s,m)   (DiInt32)&(((s *)0)->m)

/**
 * This structure contains ring part
 * @memo     Ring part
 * @member   rpNext pointer to the next ring element
 * @member   rpPrev pointer to the previous ring element
 * @header   DiRing.h
 * @see      DiRingPartPtr
 */
typedef struct DiRingPartTag
{
    struct DiRingPartTag *rpNext;
    struct DiRingPartTag *rpPrev;
}
DiRingPart;

/**
 * This type is pointer to the DiRingPart structure
 * @memo     Pointer to the DiRingPart structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
typedef DiRingPart *DiRingPartPtr;

/**
 * This structure contains ring lock
 * @memo     Ring lock
 * @member   rLink ring part
 * @header   DiRing.h
 * @see      DiRingLockPtr
 */
typedef struct DiRingLockTag
{
    DiRingPart rLink;
}
DiRingLock;

/**
 * This type is pointer to the DiRingLock structure
 * @memo     Pointer to the DiRingLock structure
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
typedef DiRingLock *DiRingLockPtr;


/****************************************************************************
Data access
*/

/**
 * This macro initializes DiRingLock structure
 * @memo     Initialize DiRingLock structure
 * @param    l   pointer to the DiRingLock structure
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define DiRingInitialize(l) \
    (l)->rLink.rpNext=((DiRingPart *)(l)); \
    (l)->rLink.rpPrev=((DiRingPart *)(l));

/**
 * This macro checks if ring empty
 * @memo     Check if ring empty
 * @param    l   pointer to the DiRingLock structure to check
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define DiRingIsEmpty(l) \
    (((l)->rLink.rpNext)==(&(l)->rLink))

/**
 * This macro adds part to a ring
 * @memo     Add part to a ring
 * @param    ring   pointer to the DiRingLock structure, represents a ring
 * @param    part   pointer to the DiRingPart  to add
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define DiRingPartAdd(ring,part) \
    (part)->rpNext = (ring)->rLink.rpNext; \
    (part)->rpPrev = (&(ring)->rLink); \
    \
    ((ring)->rLink.rpNext)->rpPrev = (part); \
    (ring)->rLink.rpNext = (part)

/**
 * This macro adds part at the end of ring
 * @memo     Add part at the end of ring
 * @param    ring   pointer to the DiRingLock structure, represents a ring
 * @param    part   pointer to the DiRingPart  to add
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define DiRingPartAddToEnd(ring, part)       \
    (part)->rpPrev = (ring)->rLink.rpPrev;   \
    (part)->rpNext = (&(ring)->rLink);       \
                                             \
    ((ring)->rLink.rpPrev)->rpNext = (part); \
    (ring)->rLink.rpPrev = (part)

/**
 * This macro inserts part1 before part2
 * @memo     Insert part1 before part2
 * @param    part1   pointer to the DiRingPart
 * @param    part2   pointer to the DiRingPart
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define DiRingPartInsert(part1, part2)      \
    DIASSERT((part1) != (part2));           \
    DIASSERT((part2)->rpPrev != (part1));   \
                                            \
    (part1)->rpNext = (part2);              \
    (part1)->rpPrev = (part2)->rpPrev;      \
                                            \
    ((part2)->rpPrev)->rpNext = (part1);    \
    (part2)->rpPrev = (part1)

/**
 * This macro removes part from ring
 * @memo     Remove part1 from ring
 * @param    part   pointer to the DiRingPart
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define DiRingPartRemove(part) \
	((part)->rpPrev)->rpNext = (part)->rpNext; \
	((part)->rpNext)->rpPrev = (part)->rpPrev; \
        (part)->rpNext = (DiRingPart*)NULL;  \
        (part)->rpPrev = (DiRingPart*)NULL

/**
 * This macro checks if part exist in ring
 * @memo     Check if part exist in ring
 * @param    part   pointer to the DiRingPart
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define  DiRingPartIsInRing(part)   \
         (((part)->rpNext != NULL) && ((part)->rpPrev != NULL))

/**
 * This macro checks if part exist in ring
 * @memo     Check if part exist in ring
 * @param    part   DiRingPart structure
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define  DiRingPPartIsInRing(part)   \
         (((part).rpNext != NULL) && ((part).rpPrev != NULL))

/**
 * This macro gets ring part data
 * @memo     Get ring part data
 * @return   pointr to the data
 * @param    part   pointer to the DiRingPart structure
 * @param    type   data type
 * @param    entry  -
 * @header   DiRing.h
 * @see      DiRingLock structure
 */
#define DiRingPartGetData(part,type,entry) \
	((type *)(((char *)(part))-diOFFSETOF(type,entry)))

/**
 * This macro initializes DiRingPart structure
 * @memo     Initialize DiRingPart structure
 * @param    part   pointer to the DiRingPart structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
#define DiRingPartInitialize(part) \
	(part)->rpPrev = (DiRingPart*)NULL; \
	(part)->rpNext = (DiRingPart*)NULL;

/**
 * This macro obtains next element for part
 * @memo     Obtain next element for part
 * @return   pointer to the next element
 * @param    part   pointer to the DiRingPart structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
#define DiRingPartGetNext(part) \
	((part)->rpNext)

/**
 * This macro obtains previous element for part
 * @memo     Obtain previous element for part
 * @return   pointer to the previous element
 * @param    part   pointer to the DiRingPart structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
#define DiRingPartGetPrev(part) \
	((part)->rpPrev)

/**
 * This macro obtains first element for ring lock
 * @memo     Obtain first element for ring lock
 * @return   pointer to the first element
 * @param    ring   pointer to the DiRingLock structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
#define DiRingPartGetFirst(ring) \
	((ring)->rLink.rpNext)

/**
 * This macro obtains last element for ring lock
 * @memo     Obtain last element for ring lock
 * @return   pointer to the last element
 * @param    ring   pointer to the DiRingLock structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
#define DiRingPartGetLast(ring) \
    ((ring)->rLink.rpPrev)

/**
 * This macro obtains terminator for ring lock
 * @memo     Obtain terminator for ring lock
 * @return   pointer to the terminator
 * @param    ring   pointer to the DiRingLock structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
#define DiRingGetTerminator(ring) \
	(&((ring)->rLink))

/**
 * This macro changes terminator for ring lock
 * @memo     Change terminator for ring lock
 * @param    LnkSrc   pointer to the DiRingLock structure
 * @param    LnkDst   pointer to the DiRingLock structure
 * @header   DiRing.h
 * @see      DiRingPart structure
 */
#define DiRingChangeTerminator(LnkSrc,LnkDst) \
        if (DiRingIsEmpty(LnkSrc)) \
        {/* make new empty */ \
          DiRingInitialize(LnkDst); \
        } \
        else \
        {/* bind to new */ \
    	    (LnkSrc)->rLink.rpPrev->rpNext = &(LnkDst)->rLink; \
    	    (LnkSrc)->rLink.rpNext->rpPrev = &(LnkDst)->rLink; \
          *(LnkDst) = *(LnkSrc);\
        }

#ifdef DIDEBUG
  extern  DiVoid DiRingTestIntegrity(DiRingLock *rlpMain);
#else
  #define DiRingTestIntegrity(rlp)
#endif //DIDEBUG
/****************************************************************************
Function prototypes
*/



#endif __DIRING__


