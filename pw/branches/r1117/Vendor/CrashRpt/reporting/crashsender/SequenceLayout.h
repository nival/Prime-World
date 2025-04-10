/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: SequenceLayout.h
// Description: A layout class for positioning dialog controls one below another.
// Authors: zexspectrum
// Date: 2010

#pragma once
#include "stdafx.h"

// class CSequenceLayout
// Implements vertical layout to position controls 
// on the dialog one below another. Some layout items 
// can be hidden/shown, and controls are automatically repositioned by the class.
// The layout class can also resize the container window to accomodate all the layout itmes.
class CSequenceLayout
{
	// Internal structure
    struct ItemInfo
    {
        BOOL m_bSecondary; // Is this item secondary?
        HWND m_hWnd;       // Handle to control's window.
        RECT m_rcInitial;  // Initial rectangle of the item within the parent dialog.
    };

public:

	// Constructor
    CSequenceLayout()
    {
        m_hWndContainer = NULL;
    }

	// Sets the container window for this layout
    void SetContainerWnd(HWND hWnd)
    {
        m_hWndContainer = hWnd;
        GetClientRect(m_hWndContainer, &m_rcContainer);
    }

	// Adds an item to layout
    void Insert(HWND hWnd, BOOL bSecondary=FALSE)
    {
        RECT rc;
        GetWindowRect(hWnd, &rc);
        MapWindowPoints(0, GetParent(hWnd), (LPPOINT)&rc, 2);
        ItemInfo ii;
        ii.m_hWnd = hWnd;
        ii.m_bSecondary = bSecondary;
        ii.m_rcInitial = rc;
        m_aItems.push_back(ii);
    }

	// Updates item positions
    void Update()
    { 
        int nDeltaY = 0;

		// Walk through items
        int i;
        for(i=0; i<(int)m_aItems.size(); i++)
        {      
			// Get i-th item
            ItemInfo ii = m_aItems[i];
            if(GetWindowLong(ii.m_hWnd, GWL_STYLE)&WS_VISIBLE) // Skip invisible items
            {        
				// Position the item appropriately
                CWindow wnd = ii.m_hWnd;
                CRect rc = ii.m_rcInitial;
                rc.OffsetRect(0, nDeltaY);
                wnd.MoveWindow(&rc);
            }
            else 
            {
				// Skip secondary items
                if(ii.m_bSecondary)
                    continue;

				// Get the next primary item
                int nNext = GetNextPrimaryItem(i+1);
                if(nNext==-1)
                    continue;

				// Update vertical offset
                ItemInfo nextItem = m_aItems[nNext];
                nDeltaY -= nextItem.m_rcInitial.top - ii.m_rcInitial.top;
            }    
        }

		// Resize the container to accomodate all the layout items
        if(m_hWndContainer!=NULL)
        {
            CWindow wnd = m_hWndContainer;
            wnd.ResizeClient(m_rcContainer.Width(), m_rcContainer.Height()+nDeltaY);
        }
    }

private:

	// Returns the index of the next primary item
    int GetNextPrimaryItem(int nStart)
    {
		// Walk through layout items
        int i;
        for(i=nStart; i<(int)m_aItems.size(); i++)
        {
			// If this item is primary, return its index
            if(m_aItems[i].m_bSecondary==FALSE)
                return i;
        }

		// Return -1 to indicate the item not found
        return -1;
    }

	// Variables used internally
    HWND m_hWndContainer;           // Handle to the continer window.
    CRect m_rcContainer;            // Countainer window's rectangle.
    std::vector<ItemInfo> m_aItems; // The list of layout items.
};