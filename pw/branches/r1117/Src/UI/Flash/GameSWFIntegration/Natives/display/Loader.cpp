#include "TamarinPCH.h"

#include "System/FileSystem/FilePath.h"

#include "../../FlashMovie.h"
#include "../../FlashClassesCache.h"

#include "../net/URLRequest.h"

#include "Bitmap.h"
#include "Loader.h"
#include "LoaderInfo.h"

namespace avmplus
{

LoaderObject::LoaderObject( LoaderClass * classType ) :
  DisplayObjectContainerObject( (DisplayObjectContainerClass*)classType )
{
  CONSTRUCT_CACHE_OBJECT( contentLoaderInfo, FlashCore(), LoaderInfoClass, LoaderInfoObject );
}

LoaderObject::LoaderObject( VTable* ivtable, ScriptObject* prototype ) :
  DisplayObjectContainerObject(ivtable, prototype)
{
  CONSTRUCT_CACHE_OBJECT( contentLoaderInfo, FlashCore(), LoaderInfoClass, LoaderInfoObject );
}

LoaderObject::~LoaderObject()
{

}

LoaderInfoObject* LoaderObject::get_contentLoaderInfo()
{
  return contentLoaderInfo;
}

void LoaderObject::_load(URLRequestObject* request, bool checkPolicyFile, ApplicationDomainObject* applicationDomain, SecurityDomainObject* securityDomain, double deblockingFilter)
{
  NI_VERIFY( request, "Request is null", return );

  AvmString url = request->get_url();
  StUTF8String urlTemp( url );
  nstl::string urlString = urlTemp.c_str();

  nstl::string basePath = FlashCore()->GetMovie()->GetFileName();

  NFile::NormalizePath( &urlString );
  NFile::NormalizePath( &basePath );

  if ( urlString[0] != ':' )
    NFile::MakeFullPath( &urlString, urlString, basePath );
  else
    urlString = &urlString[1];

  nstl::string ext = NFile::GetFileExt( urlString );

  if ( ext == ".png" || ext == ".dds" )
  {
    avmplus::BitmapClass* bitmapClass = FlashCore()->GetClassCache().GetClass<avmplus::BitmapClass>( EFlashClassID::BitmapClass );
    avmplus::BitmapObject* bitmapObject = dynamic_cast<avmplus::BitmapObject*>( bitmapClass->newInstance() );
    
    bitmapObject->LoadImage( urlString );
    
    content = bitmapObject;

    addChild( content );

    contentLoaderInfo->SetContent( content );
    contentLoaderInfo->Fire_INIT();
    contentLoaderInfo->Fire_COMPLETE();
  }
}

double LoaderObject::_getJPEGLoaderContextdeblockingfilter(AvmBox context)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (double)0;
}

void LoaderObject::_loadBytes(ByteArrayObject* bytes, bool checkPolicyFile, ApplicationDomainObject* applicationDomain, SecurityDomainObject* securityDomain, double deblockingFilter)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void LoaderObject::close()
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void LoaderObject::_unload(bool halt, bool gc)
{
  if ( content )
    removeChild( content );

  content = 0;
}

}