/****************************************************************************
**
**  This file is part of GAP, a system for computational discrete algebra.
**
**  Copyright of GAP belongs to its developers, whose names are too numerous
**  to list here. Please refer to the COPYRIGHT file for details.
**
**  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "error.h"
#include "gasman.h"
#include "objects.h"    // HACK: for FIRST_IMM_MUT_TNUM; remove this later

/****************************************************************************
**
*V  InfoBags[<type>]  . . . . . . . . . . . . . . . . .  information for bags
*/
#ifdef COUNT_BAGS
TNumInfoBags InfoBags[NUM_TYPES];
#endif


UInt8 SizeAllBags;


// TODO: perhaps this should become RetypeObj ?
void RetypeBagSM(Bag bag, UInt new_type)
{
   if (FIRST_IMM_MUT_TNUM <= new_type && new_type <= LAST_IMM_MUT_TNUM) {
        Int oldImm = !IS_MUTABLE_OBJ(bag);
        Int newImm = new_type & IMMUTABLE;
        if (newImm)
            ErrorMayQuit("RetypeBagSM: target tnum should not indicate immutability", 0, 0);
        if (oldImm)
            new_type |= IMMUTABLE;
    }
    RetypeBag(bag, new_type);
}

#ifdef HPCGAP
void RetypeBagSMIfWritable(Bag bag, UInt new_type)
{
   if (FIRST_IMM_MUT_TNUM <= new_type && new_type <= LAST_IMM_MUT_TNUM) {
        Int oldImm = !IS_MUTABLE_OBJ(bag);
        Int newImm = new_type & IMMUTABLE;
        if (newImm)
            ErrorMayQuit("RetypeBagSM: target tnum should not indicate immutability", 0, 0);
        if (oldImm)
            new_type |= IMMUTABLE;
    }
    RetypeBagIfWritable(bag, new_type);
}
#endif


inline void MarkArrayOfBags(const Bag array[], UInt count)
{
    for (UInt i = 0; i < count; i++) {
        MarkBag(array[i]);
    }
}

void MarkNoSubBags(Bag bag)
{
}

void MarkOneSubBags(Bag bag)
{
    MarkArrayOfBags(CONST_PTR_BAG(bag), 1);
}

void MarkTwoSubBags(Bag bag)
{
    MarkArrayOfBags(CONST_PTR_BAG(bag), 2);
}

void MarkThreeSubBags(Bag bag)
{
    MarkArrayOfBags(CONST_PTR_BAG(bag), 3);
}

void MarkFourSubBags(Bag bag)
{
    MarkArrayOfBags(CONST_PTR_BAG(bag), 4);
}

void MarkAllSubBags(Bag bag)
{
    MarkArrayOfBags(CONST_PTR_BAG(bag), SIZE_BAG(bag) / sizeof(Bag));
}

void MarkAllButFirstSubBags(Bag bag)
{
    MarkArrayOfBags(CONST_PTR_BAG(bag) + 1, SIZE_BAG(bag) / sizeof(Bag) - 1);
}

void MarkAllSubBagsDefault(Bag bag)
{
    MarkArrayOfBags(CONST_PTR_BAG(bag), SIZE_BAG(bag) / sizeof(Bag));
}
