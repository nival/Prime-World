#include "../libs.h"
#include "Part.h"

class FastWriter
{
  int capacity;
  char* memory;
  int size;
public:
  FastWriter( int capacity = 60*1024*1024 ) : capacity(capacity), size( 0 )
  {
    memory = new char[capacity];
  }

  ~FastWriter()
  {
    delete [] memory;
  }

  void Write( const void* data, size_t sizeToWrite )
  {
    if ( size+(int)sizeToWrite > capacity )
    {
      MPxCommand::displayError( "Write buffer overrun." );
      return;
    }
    memcpy(memory+size, data, sizeToWrite);
    size += sizeToWrite;
  }

  char* GetBuffer() 
  { 
    return memory;
  }

  int GetSize()
  {
    return size;
  }
};

// For assigning indexes to joints to establish skin-skeleton matching
struct DAGjoint
{
  unsigned level;          // Hierarchy level. 0 = ROOT
  std::string name;        // DAG name
  std::string fullName; // Full DAG path
  MDagPath dp;                    // Maya DAG Path
  unsigned mayaID;            // Index in array got via skin.getInfluences
  unsigned exportID;      // ID for export, used in skin definition
  unsigned parentID;      // exportID of parent joint

  MMatrix m;                      // Joint transform. World space for root, local for others
  MMatrix mBind;              // Joint bind-time-stored transform. World space

  bool operator == ( const std::string &_j ) const 
  {
    return fullName == _j;
  };
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class h6export: public MPxCommand 
{
public:
    h6export();
    virtual MStatus doIt ( const MArgList& );
    virtual MStatus undoIt ();
    virtual MStatus redoIt ();
    virtual bool isUndoable() const 
    {
        return true;
    }
    
    static void *creator() 
    {
        return new h6export; 
    }

    static MSyntax newSyntax();

private:
    MDGModifier dgMod;
    MString msFileName;
    MSelectionList slList;
    MString msType;
    MObject moMesh;
    MString msSelection;

    // Output parameters
    FILE* pFile;
    FastWriter* writer;

    // File type signatures
    unsigned SIGN;
    static const unsigned statSIGN = 0x54415458;
    static const unsigned skinSIGN = 0x4e494b58;
    static const unsigned skelSIGN = 0x4c454b53;
    static const unsigned animSIGN = 0x4d494e41;
    static const unsigned partSIGN = 0x54524150;
    static const unsigned lghtSIGN = 0x5448474c;

    unsigned nUVsets;
    unsigned nMaterials;

    // Joints per vertex limit
    unsigned nInfluences;

    // Flags for animation export
    unsigned animType;
    static const unsigned TRS = 1;
    static const unsigned ROT = 2;
    static const unsigned SCL = 4;

    // Animation compression tolerance %
    float fTolerance;

    // Coordinate system for export
    MMatrix mSys;

    // Export vertex format
    struct jointWeight
    {
        float value;
        unsigned jointID;
    };

    struct sort_weights_desc
    {
        bool operator () ( const jointWeight _jW1, const jointWeight _jW2 ) const
        {
            return _jW1.value > _jW2.value;
        }
    };

    struct exportVertex
    {
    private:
        unsigned nUVsets;
        exportVertex() {}
    public:
        exportVertex( const unsigned &_nUVsets ) : nUVsets( _nUVsets ) {}
        unsigned mayaID;
        unsigned normalID;
        std::vector<unsigned> uvIDs; // Of size determined by nUVsets
        unsigned ID;

        float x;
        float y;
        float z;

        float r;
        float g;
        float b;
        float a;

        float nx;
        float ny;
        float nz;

        float tx;
        float ty;
        float tz;

        float bx;
        float by;
        float bz;

        std::vector<float> u;   // Of size determined by nUVsets
        std::vector<float> v;   // Of size determined by nUVsets

        std::vector<jointWeight> w;      // Joints' weights. Of size determined by nInfluences

        bool operator < ( const exportVertex &_v ) const 
        {
            if ( mayaID < _v.mayaID )
            {
                return true;
            }

            if ( mayaID > _v.mayaID )
            {
                return false;
            }

            if ( normalID < _v.normalID )
            {
                return true;
            }

            if ( normalID > _v.normalID )
            {
                return false;
            }

            for ( unsigned nI = 0; nI < nUVsets; ++nI )
            {
                if ( uvIDs[nI] < _v.uvIDs[nI] )
                {
                    return true;
                }

                if ( uvIDs[nI] > _v.uvIDs[nI] )
                {
                    return false;
                }
            }
        
            return ID < _v.ID;
        };

        bool operator != ( const exportVertex &_v ) const 
        {
            if ( mayaID != _v.mayaID )
            {
                return true;
            }

            if ( normalID != _v.normalID )
            {
                return true;
            }

            for ( unsigned nI = 0; nI < nUVsets; ++nI )
            {
                if ( uvIDs[nI] != _v.uvIDs[nI] )
                {
                    return true;
                }
            }

            return false;
        };
    };

    // Vertex buffers
    std::vector<exportVertex> vertices;

    // Face index - sequential triads of vertex ids
    MIntArray faces;

    // Material-face index. Vector of "material" arrays containing face indexes
    std::vector<MIntArray> faceMaterials;
    
    std::vector<DAGjoint> skeleton;
    std::vector<DAGjoint>::iterator itSkeleton;


    struct sort_hierarchy_by_name
    {
        bool operator () ( const DAGjoint _j1, const DAGjoint _j2 )
        {
            if ( _j1.level < _j2.level )
            {
                return true;
            }

            if ( _j1.level > _j2.level)
            {
                return false;
            }
            
            unsigned nMin = unsigned( _j1.name.size() < _j2.name.size() ? _j1.name.size() : _j2.name.size() );
            for( unsigned nI = 0; nI < nMin; nI++ )
            {
                if ( _j1.name[nI] < _j2.name[nI] )
                {
                    return true;
                }

                if ( _j1.name[nI] > _j2.name[nI] )
                {
                    return false;
                }
            }

            return _j1.name.size() < _j2.name.size();
        }
    };

    struct sort_by_mayaID
    {
        bool operator () ( const DAGjoint _j1, const DAGjoint _j2 )
        {
            return _j1.mayaID < _j2.mayaID;
        }
    };

    // Animation types
    std::vector<animTrack> animData; // Size of number of joints

    // Particle FX
    //SPartObj partObj;
    partObj partObj;
    hmPartData partData;

    // Light FX
    struct lghtTrack
    {
        TVTrack<3> pos;
        TVTrack<1> radius;
        TVTrack<3> col;
    };

    std::vector<lghtTrack> lghtData;

    // Type-specific export methods
    MStatus stat();
    MStatus sortMaterials( const MObjectArray& _moA, MIntArray& _IDs );

    MStatus skin();
    MStatus pruneWeights( std::vector<jointWeight>& );
    MStatus toBindPose();

    MStatus skel();
    bool isEndJoint( const MDagPath& ) const;
    MStatus indexDAG( const MDagPathArray& );
    MMatrix getMatrix( const unsigned& );
    
    MStatus anim();
    MStatus getJointFrame( const unsigned&, const unsigned& );
    MStatus flipQuaternion( animTrack& );

    MStatus part();

    void FillDagPaths( MFnSkinCluster& mfSkin, MDagPathArray& dpA, MDagPathArray& realJoints );

    MStatus lght();

    MStatus write();
    MStatus writeMesh() const;
    MStatus writeVertices() const;
    MStatus writeFaces() const;
    MStatus writeSkel() const;
    MStatus writeAnim() const;
    MStatus writePart() const;
    MStatus writeLght() const;

    MStatus debugTracks() const;
    MStatus debugMatrix( const MMatrix&, const char* ) const;
  MStatus debugOutputInfo( const char* filename ) const;
  MStatus debugOutputInfoVertices( const char* filename ) const;

    void writeError( const char* format, ... ) const;
};

