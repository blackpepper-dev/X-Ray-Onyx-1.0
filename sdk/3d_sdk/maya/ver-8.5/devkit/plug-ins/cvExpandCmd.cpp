//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc. and/or its licensors.  All 
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors, which is protected by U.S. and Canadian federal copyright 
// law and by international treaties.
//
// The Data is provided for use exclusively by You. You have the right 
// to use, modify, and incorporate this Data into other products for 
// purposes authorized by the Autodesk software license agreement, 
// without fee.
//
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the 
// following disclaimer, must be included in all copies of the 
// Software, in whole or in part, and all derivative works of 
// the Software, unless such copies or derivative works are solely 
// in the form of machine-executable object code generated by a 
// source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
// PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE, OR 
// TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS LICENSORS 
// BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL, 
// DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK 
// AND/OR ITS LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY 
// OR PROBABILITY OF SUCH DAMAGES.
//
// ==========================================================================
//+

#include <maya/MSimple.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>
#include <maya/MItSelectionList.h>
#include <maya/MItSurfaceCV.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>

#include <maya/MIOStream.h>

DeclareSimpleCommand( cvExpand, PLUGIN_COMPANY, "3.0");

MStatus cvExpand::doIt( const MArgList& args )
{

	MSelectionList list;
	MSelectionList newList;

	// Get the geometry list from what is currently selected in the 
	// model
	//
	MGlobal::getActiveSelectionList( list );

	MDagPath path;
	MObject  component;
 
	// Make expanded Selection List
	//
	for ( MItSelectionList iter( list ); !iter.isDone(); iter.next() ) {
		iter.getDagPath( path, component );
		
		if ( path.hasFn( MFn::kNurbsSurfaceGeom ) && 
			 !component.isNull() ) {
			for ( MItSurfaceCV cvIter( path, component ); 
				  !cvIter.isDone(); cvIter.next() ) {
				newList.add( path, cvIter.cv() );
			}
		} else {
			newList.add( path, component );
		}
	}

	// Return expanded selection list as an array of strings
	//
	MStringArray returnArray;
	newList.getSelectionStrings( returnArray );

	MPxCommand::setResult( returnArray );

	return MS::kSuccess;
}
