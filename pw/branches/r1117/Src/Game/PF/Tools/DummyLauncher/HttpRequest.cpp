#include "stdafx.h"
#include "HttpRequest.h"
#include "Convert.h"
#include "Application.h"
#include "ConsoleWindow.h"
#include "Log.h"

#define CHECK_RESULT(x) { HRESULT hr = x; if (hr != S_OK ) throw _com_error(hr); }

HttpRequest::HttpRequest()
{
}

HRESULT HttpRequest::SendRequest(const std::wstring& url, HttpRequest::ReqType type)
{
	return SendRequest(url, RequestParams(), RequestHeaders(), type);
}

HRESULT HttpRequest::SendRequest(const std::wstring& url, const RequestParams& params, HttpRequest::ReqType type)
{
	return SendRequest(url, params, RequestHeaders(), type);
}

HRESULT HttpRequest::SendRequest(const std::wstring& url, const RequestParams& params, const RequestHeaders& headers, ReqType type)
{
	try
	{
		std::wstring reqString;
		for( RequestParams::const_iterator iter = params.begin(); iter != params.end(); ++iter )
      reqString += Convert::FromUTF8("&" + iter->first + "=" + iter->second);
		if(!reqString.empty())
		{
			wchar_t endChar = url[url.length() - 1];
			if(type == REQ_POST || endChar == L'&' || endChar == L'?')
				reqString = reqString.substr(1);
      else
        reqString[0] = L'?';
		}

		WinHttp::IWinHttpRequestPtr req;
		req.CreateInstance(__uuidof(WinHttp::WinHttpRequest));

		_bstr_t method;
		_bstr_t urlPrm(url.c_str());
    std::wstring consoleStr;
		switch(type)
		{
		case REQ_GET:
			method = L"GET";
			urlPrm += reqString.c_str();
      consoleStr = L"GET request:\r\n";
      consoleStr += (LPWSTR)urlPrm;
			break;
		case REQ_POST:
			method = L"POST";
      consoleStr = L"POST request:\r\n";
      consoleStr += (LPWSTR)urlPrm;
      consoleStr += L"\r\n";
      consoleStr += reqString;
			break;
		}
		_variant_t vtFalse = false;
		_variant_t vtNull;
		vtNull.vt = VT_NULL;
		LOG( "Req: %s: %s", (LPCSTR)method, (LPCSTR)urlPrm );

    g_App->GetConsole().AddText(STYLE_FROM_CLIENT, consoleStr);

    req->put_Option(WinHttp::WinHttpRequestOption_SslErrorIgnoreFlags,
      _variant_t((long)WinHttp::SslErrorFlag_Ignore_All));
    
    CHECK_RESULT( req->Open(method, urlPrm, vtFalse) );
		CHECK_RESULT( req->SetRequestHeader(L"If-Modified-Since", L"Mon, 1 Jan 1990 00:00:00 GMT") );

		for(RequestHeaders::const_iterator iter = headers.begin(); iter != headers.end(); ++iter)
			CHECK_RESULT( req->SetRequestHeader((BSTR)iter->first.c_str(), (BSTR)iter->second.c_str()) );
		
		_variant_t sendPrms = (type==REQ_POST) ? _bstr_t(reqString.c_str()) : vtNull;
		LOG( "Req: Send %s", Convert::VarToString(sendPrms).c_str() );
		CHECK_RESULT( req->Send(sendPrms) );

//		long state = 0;
		_bstr_t result;

    CHECK_RESULT( req->get_ResponseText( &result.GetBSTR() ) );

    LOG( "Req: response: %s", (LPCSTR)result );
		if((LPCSTR)result == NULL)
			m_resultUTF8.clear();
		else
			m_resultUTF8 = (LPCSTR)result;
		m_result = Convert::FromUTF8(result);
		m_lastError.clear();
	}
	catch(_com_error& err)
	{
		LOG( "Req: error 0x%08x (%s)", err.Error(), (LPCSTR)_bstr_t(err.ErrorMessage()) );
		m_lastError = Convert::FormatString(L"Error (0x%08x) ", err.Error()) + err.ErrorMessage();

    g_App->GetConsole().AddText(STYLE_FROM_SERVER_ERROR, L"Got error: " + m_lastError);

		m_result.clear();
		m_resultUTF8.clear();
		return err.Error();
	}

	return S_OK;
}
