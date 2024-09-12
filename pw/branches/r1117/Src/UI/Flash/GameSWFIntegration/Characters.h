#pragma once

#include "DisplayTags.h"
#include "ShapeData.h"
#include "ImageData.h"
#include "System/Pointers/Pointers.h"


namespace avmplus
{
  class DisplayObjectObject;
  class SpriteObject;
}

namespace flash
{

class Movie;
class SoundData;
class FlashMovieAvmCore;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ICharacter : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( ICharacter, IBaseInterfaceST )

  virtual void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID ) = 0;

  virtual void AddDisplayTag( IDisplayTag* _displayTag ) = 0;

  // some of characters aren't based on DisplaObject
  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject ) = 0;

  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore ) = 0;

  virtual void InitObject( avmplus::ScriptObject* _scriptObject ) = 0;

  virtual void AddFrameLabel( int frameId, const nstl::string& fameLabel ) = 0;

  virtual void SetScale9Grid( const SWF_RECT& _scale9Grid ) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CharacterBase : public ICharacter
{
  NI_DECLARE_CLASS_1( CharacterBase, ICharacter )
public:

  CharacterBase() : useScale9Grid( false ) {}

  virtual void SetScale9Grid( const SWF_RECT& _scale9Grid )
  {
    scale9Grid = _scale9Grid;
    useScale9Grid = true;
  }

protected:

  SWF_RECT scale9Grid;
  bool useScale9Grid;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ShapeCharacter : public CharacterBase, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ShapeCharacter, CharacterBase, BaseObjectST );

public:
  ShapeCharacter() {}

  virtual void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID );

  virtual void AddDisplayTag( IDisplayTag* _displayTag ) {}
  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject ) {}

  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore ); 
  virtual void InitObject( avmplus::ScriptObject* _scriptObject );

  virtual void AddFrameLabel( int frameId, const nstl::string& fameLabel ) {}

private:

  ShapeDefinition shapeDesc;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SpriteCharacter : public CharacterBase, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( SpriteCharacter, CharacterBase, BaseObjectST );

public:
  
  typedef nstl::hash_map<nstl::string, int> FrameLabelMap;

  SpriteCharacter(): frameToFill(1) {}

  virtual void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID ) {}

  virtual void AddDisplayTag( IDisplayTag* _displayTag );
  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject ) {}

  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore ); 
  virtual void InitObject( avmplus::ScriptObject* _scriptObject );

  DisplayTags * GetTags(int frame);
  int GetFramesCount() {return frameToFill-1;}

  virtual void AddFrameLabel( int frameId, const nstl::string& fameLabel );
  int GetFrameByLabel( const nstl::string& fameLabel );

private:
  int frameToFill;
  DisplayTagsByFrame displayTagsMap;
  FrameLabelMap frameLabelMap; 
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MovieCharacter : public SpriteCharacter
{
  NI_DECLARE_REFCOUNT_CLASS_1( MovieCharacter, SpriteCharacter );

public:
  MovieCharacter() {}

  virtual void InitObject( avmplus::ScriptObject* _scriptObject );
  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore ); 
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BitmapCharacter : public CharacterBase, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( BitmapCharacter, CharacterBase, BaseObjectST );

public:
  BitmapCharacter() : movie(0) {}

  void SetMovie( Movie * _movie ) { movie = _movie; }

  virtual void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID );

  virtual void AddDisplayTag( IDisplayTag* _displayTag ) {}
  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject );

  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore ); 
  virtual void InitObject( avmplus::ScriptObject* _scriptObject );

  const ImageData& GetImageData() const { return imageData; }

  virtual void AddFrameLabel( int frameId, const nstl::string& fameLabel ) {}

private:
  ImageData imageData;
  Movie * movie;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SoundCharacter : public CharacterBase, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( SoundCharacter, CharacterBase, BaseObjectST );

public:
  SoundCharacter() {}
  
  virtual void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID );;

  virtual void AddDisplayTag( IDisplayTag* _displayTag ) {}
  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject ) {};

  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore ) {return 0;} 
  virtual void InitObject( avmplus::ScriptObject* _scriptObject );

  virtual void AddFrameLabel( int frameId, const nstl::string& fameLabel ) {}

private:
  Strong<SoundData> soundData;

};

}