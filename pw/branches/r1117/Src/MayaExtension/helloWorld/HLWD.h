#include "../libs.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class helloWorld : public MPxCommand 
{
public:
	virtual MStatus	doIt ( const MArgList& );
	virtual MStatus	undoIt ();
	virtual MStatus	redoIt ();
	virtual bool isUndoable() const {return true;}

	static void *creator() { return new helloWorld; }

private:
	MDGModifier dgMod;

};

