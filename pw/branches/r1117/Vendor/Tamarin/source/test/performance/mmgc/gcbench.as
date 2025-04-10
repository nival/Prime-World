/* -*- mode: java; tab-width: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 *
 *    This benchmark was adapted for ActionScript by Edwin Smith of Adobe Systems, Inc.
 *    This is adapted from a benchmark written by John Ellis and Pete Kovac of Post Communications.
 *    It was modified by Hans Boehm of Silicon Graphics.
 *   
 * Copyright (c) 1988, 1989 Hans-J. Boehm, Alan J. Demers
 * Copyright (c) 1991-1996 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 1999-2004 Hewlett-Packard Development Company, L.P.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose,  provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 * ***** END LICENSE BLOCK ***** */

import avmplus.*;

class Node 
{
    var left:Node, right:Node;
    var i:int, j:int;
    function Node(l:Node = null, r:Node = null) { left = l; right = r; }
}

class GCBench
{
    var rootNode:Node;
		
    var tempTree:Node;
    var tStart:Number, tFinish:Number;
    var tElapsed:Number;

    static const kStretchTreeDepth:int    = 18;	 // about 16Mb (for Java / C++)
    static const kLongLivedTreeDepth:int  = 16;  // about 4Mb (for Java / C++)
    static const kArraySize:int  = 500000;       // about 4Mb (for Java / C++)
    static const kMinTreeDepth:int = 4;
    static const kMaxTreeDepth:int = 16;

    static const bTrace:Boolean = true;

    function msg(s) 
    {
	if (bTrace)
	    trace(s);
    }

    function now() 
    {
	return (new Date()).getTime();
    }

    function GCBench()
    {
	// msgBox = new TextField();
	// msgBox.width = stage.width
	// msgBox.height = stage.height

	msg("Garbage Collector Test");
	msg(" Stretching memory with a binary tree of depth " + kStretchTreeDepth);

	tStart = now();

	// Stretch the memory space quickly
	tempTree = MakeTree(kStretchTreeDepth);
	tempTree = null;

	// Create a long lived object
	msg(" Creating a long-lived binary tree of depth " + kLongLivedTreeDepth);
	var longLivedTree:Node = new Node();
	Populate(kLongLivedTreeDepth, longLivedTree);

	// Create long-lived array, filling half of it
	msg(" Creating a long-lived array of " + kArraySize + " doubles");
	var bcArray:Vector.<Number> = new Vector.<Number>(kArraySize);
	for (var bci:int = 0; bci < kArraySize/2; ++bci) {
	    bcArray[bci] = 1.0/bci;
	}

	for (var d:int = kMinTreeDepth; d <= kMaxTreeDepth; d += 2) {
	    TimeConstruction(d);
	}

	if (longLivedTree == null || bcArray[1000] != .001)
	    trace("Failed");

	// fake reference to LongLivedTree
	// and array
	// to keep them from being optimized away

	tFinish = now();
	tElapsed = tFinish-tStart;
	trace("metric time "+tElapsed);

    }

    //function trace(str)
    //{
    //    msgBox.text += ( str + "\n");
    //}

    // Nodes used by a tree of a given size
    function TreeSize(ts:int):int
    {
	return ((1 << (ts + 1)) - 1);
    }

    // Number of iterations to use for a given tree depth
    function NumIters(ni:int):int
    {
	return Math.round(2 * TreeSize(kStretchTreeDepth) / TreeSize(ni));
    }

    // Build tree top down, assigning to older objects. 
    function Populate(iDepth:int, thisNode:Node):void
    {
	if (iDepth<=0) {
	    return;
	} else {
	    iDepth--;
	    thisNode.left  = new Node();
	    thisNode.right = new Node();
	    Populate (iDepth, thisNode.left);
	    Populate (iDepth, thisNode.right);
	}
    }

    // Build tree bottom-up
    function MakeTree(iDepth:int):Node
    {
	if (iDepth<=0) {
	    return new Node();
	} else {
	    return new Node(MakeTree(iDepth-1),
			    MakeTree(iDepth-1));
	}
    }

    function TimeConstruction(depth:int):void 
    {
	var rootNode:Node;
	var tStart:Number, tFinish:Number;
	var iNumIters:int = NumIters(depth);
	var tempTree:Node;

	msg("Creating " + iNumIters + " trees of depth " + depth);
	tStart = now();
	for (var i:int = 0; i < iNumIters; ++i) {
	    tempTree = new Node();
	    Populate(depth, tempTree);
	    tempTree = null;
	}
	tFinish = now();
	msg("\tTop down construction took " + (tFinish - tStart) + "msecs");
	tStart = now();
	for (var itr:int = 0; itr < iNumIters; ++itr) {
	    tempTree = MakeTree(depth);
	    tempTree = null;
	}
	tFinish = now();
	msg("\tBottom up construction took " + (tFinish - tStart) + "msecs");
		
    }
}

(new GCBench());
