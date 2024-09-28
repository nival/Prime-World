#include "StdAfx.h"
#include "OcclusionQueries.h"

namespace Render
{

static OcclusionQueriesBank::CameraID currentCamera = OcclusionQueriesBank::CID_MAIN;

OcclusionQueriesBank::OcclusionQueriesBank(void)
{
  LPDIRECT3DQUERY9 query = NULL;
  IDirect3DDevice9* const pDev = GetDevice();
  HRESULT hr;
  for(UINT n = 0; n < queries.capacity(); n++)
  {
    hr = pDev->CreateQuery(D3DQUERYTYPE_OCCLUSION, &query);
    NI_ASSERT(hr == S_OK, "Can't create query");

    queries[n].query = query;
    queries[n].state = OcclusionQuery::UNUSED;
  }

  currentFrame = UINT_MAX;
  // init our head pointer to the first element.  head is always the oldest query in use
  head = 0;
}

OcclusionQueriesBank::~OcclusionQueriesBank(void)
{
}

//////////////////////////////////////////////////////////////////////////
// Returns the most recent results of outstanding queries.  Once results have
// been encountered the query becomes unsued again.  If multiple queries
// finished since the last call, then only the most recent results will be returned.
int OcclusionQueriesBank::GetLatestResults()
{
  if(UINT_MAX == lastFinishedQuery)
  {
    DWORD tempCount = 0;
    lastResult = 0;
    HRESULT hr = E_FAIL;
    UINT n = head;

    do {
      OcclusionQuery& sQuery = queries[n];
      if(sQuery.state == OcclusionQuery::ISSUEDEND)
      {
        hr = sQuery.query->GetData(&tempCount, sizeof(DWORD), 0);
        if(hr == S_OK)
        { // if we have a result, then record it and keep testing
          lastResult = tempCount;
          lastFinishedQuery = n;
          sQuery.state = OcclusionQuery::UNUSED;
        }
        continue;
      }

      if(sQuery.state == OcclusionQuery::UNUSED)
        break;

      NI_ALWAYS_ASSERT("mismatched Query begin/end encountered"); // sQuery.state == OcclusionQuery::ISSUEDBEGIN
    } while(++n % queries.capacity() == head);

    if(UINT_MAX == lastFinishedQuery)
      return UINT(-1);

    for(n = head; n % queries.capacity() != lastFinishedQuery; ++n)
    {
      OcclusionQuery& sQuery = queries[n];
      if(sQuery.state == OcclusionQuery::ISSUEDEND)
      {
        hr = sQuery.query->GetData(&tempCount, sizeof(DWORD), D3DGETDATA_FLUSH);
        if(hr == S_OK)
        { // if we have a result, then record it and keep testing
          lastResult = tempCount;
          sQuery.state = OcclusionQuery::UNUSED;
        }
        else
          NI_ALWAYS_ASSERT("couldn't flash Query"); // sQuery.state == OcclusionQuery::ISSUEDBEGIN
      }
    }
  }

  return lastResult;
}

//////////////////////////////////////////////////////////////////////////
// Issue a new begin occlusion query into the pushbuffer.
HRESULT OcclusionQueriesBank::BeginNextQuery()
{
  if(s_currentFrame != currentFrame)
  {
    lastFinishedQuery = UINT_MAX;
    UINT n = head;
    do {
      // first unused query gets begin'd
      if(queries[n].state == OcclusionQuery::UNUSED)
      {
        HRESULT hr = queries[n].query->Issue(D3DISSUE_BEGIN);
        if( SUCCEEDED(hr) )
          queries[n].state = OcclusionQuery::ISSUEDBEGIN;

        return hr;
      }
    } while(++n % queries.capacity() == head);
  }

  return E_FAIL;
}

//////////////////////////////////////////////////////////////////////////
// Issue a new end occlusion query into the pushbuffer
HRESULT OcclusionQueriesBank::EndNextQuery()
{
  if(s_currentFrame != currentFrame)
  {
    UINT n = head;
    {
      // first begin'd query gets end'd
      if(queries[n].state == OcclusionQuery::ISSUEDBEGIN)
      {
        HRESULT hr = queries[n].query->Issue(D3DISSUE_END);
        if( SUCCEEDED(hr) )
        {
          queries[n].state = OcclusionQuery::ISSUEDEND;
          currentFrame = s_currentFrame;
        }
        return hr;
      }
    } while(++n % queries.capacity() == head);
  }

  return S_FALSE;
}


OcclusionQueriesBank& OcclusionQueries::Get()
{
  VQueries::iterator it = banks.begin();
  VQueries::iterator const end = banks.end();
  while(it != end && it->cameraID != currentCamera)
    ++it;

  if(it != end)
    return *it;

  OcclusionQueriesBank& result = banks.push_back();
  result.cameraID = currentCamera;
  return result;
}

UINT OcclusionQueriesBank::s_currentFrame = 0;

static OcclusionQueries::UseMode      s_useMode = OcclusionQueries::QUM_NONE;

void OcclusionQueries::SetUseMode(UseMode _useMode) { s_useMode = _useMode; }
OcclusionQueries::UseMode OcclusionQueries::GetUseMode() { return s_useMode; }

void OcclusionQueries::SetCurrentCameraID(OcclusionQueriesBank::CameraID _id) { currentCamera = _id; }
};