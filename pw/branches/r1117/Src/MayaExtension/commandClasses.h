#include "libs.h"
#include "blindDataShader/blindDataMesh.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class setVertexNormals : public MPxCommand 
{
public:
	virtual MStatus	doIt ( const MArgList& );
	virtual MStatus	undoIt ();
	virtual MStatus	redoIt ();
	virtual bool isUndoable() const {return true;}
	
	static void *creator() { return new setVertexNormals; }
	static MSyntax newSyntax();

private:
	MDGModifier dgMod;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class bindFile : public MPxCommand 
{
public:
	virtual MStatus	doIt ( const MArgList& );
	virtual MStatus	undoIt ();
	virtual MStatus	redoIt ();
	virtual bool isUndoable() const {return true;}
	
	static void *creator() { return new bindFile; }
	static MSyntax newSyntax();

private:
	MDGModifier dgMod;

	double tolerance;

	MStatus	writer(	
		MString filename,
		MDagPathArray jointPaths,	
		MPointArray vertices,	
		std::vector<MFloatArray> weightsVector);

	MStatus	reader(
		MString filename,
		MFnSkinCluster	skinCluster,
		MDagPath	meshPath,
		MObject meshComponent,
		double	tolerance);

	MStatus	writerIDX(
		MString filename,
		MDagPathArray jointPaths,	
		MIntArray vertexIDs, 
		std::vector<MFloatArray> weightsVector);

	MStatus	readerIDX(
		MString	filename,
		MFnSkinCluster skinCluster,
		MDagPath meshPath,
		MObject	meshComponent);

	MStatus	writerBlind(
		MObject mesh,
		MDagPathArray jointPaths,	
		MIntArray vertexIDs, 
		std::vector<MFloatArray> weightsVector);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class polyTrace : public MPxCommand 
{
public:
	virtual MStatus	doIt ( const MArgList& );
	virtual bool isUndoable() const {return false;}
	
	static void *creator() { return new polyTrace; }
	static MSyntax newSyntax();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cvColorShader : public MPxNode
{
	public:
										cvColorShader();
		virtual				 ~cvColorShader();

		virtual MStatus compute( const MPlug&, MDataBlock& );
	virtual void		postConstructor();

		static	void *	creator();
		static	MStatus initialize();

	//	Id tag for use with binary file format
		static	MTypeId id;

	private:

	static inline float dotProd(const MFloatVector &, const MFloatVector &); 


	// Input attributes

	static MObject aReverseAlpha;

	static MObject aPointObj;				// Implicit attribute
	static MObject aPrimitiveId;			// Implicit attribute

	static MObject	aInTransparency;
	static MObject	aInTransR;
	static MObject	aInTransG;
	static MObject	aInTransB;


	// Output attributes
	static MObject aOutColor;
	static MObject aOutAlpha;

	static MObject	aOutTransparency;
	static MObject	aOutTransR;
	static MObject	aOutTransG;
	static MObject	aOutTransB;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class mapFaces : public MPxCommand 
{
public:
	virtual MStatus	doIt ( const MArgList& );
	virtual MStatus	undoIt ();
	virtual MStatus	redoIt ();
	virtual bool isUndoable() const {return true;}
	
	static void *creator() { return new mapFaces; }
	static MSyntax newSyntax();

private:
	MDGModifier dgMod;
};

