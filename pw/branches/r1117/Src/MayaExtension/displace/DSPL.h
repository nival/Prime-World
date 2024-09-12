#include "../libs.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class displace : public MPxDeformerNode 
{ 
private:
	MImage miHM; // Height map storage
	float* pPx;  // Pointer to pixels from miHM
	int nSX;// Image X size
	int nSY;// Image X size

	float getHeight( const double& _fU, const double& _fV ) const;     // Returns height at fU fV from miHM
	MColor getPixel( const int& _nX, const int& _nY ) const; // Returns pixel at _nX _nY from pPx

public: 
	displace(); 
	virtual ~displace(); 
	static void* creator(); 
	static MStatus initialize(); 

	virtual MStatus compute( const MPlug& _pl, MDataBlock& _db );
	
	// deformation function 
	virtual MStatus deform(
		MDataBlock& block, 
		MItGeometry& iter, 
		const MMatrix& mat, 
		unsigned multiIndex ); 

public:
	static MObject heightMap;   // Attribute for height map
	static MObject BBox1;   // Attribute for height map
	static MObject BBox2;   // Attribute for height map

	static MObject hmUpdate;// Attribute indicating height map update
	static MTypeId id;
}; 