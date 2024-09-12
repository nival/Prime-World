#pragma once

class HttpRequest
{
public:
	typedef StringsMap RequestParams;
	typedef WStringsMap RequestHeaders;
	enum ReqType
	{
		REQ_GET,
		REQ_POST,
	};
	HttpRequest();

	HRESULT SendRequest(const std::wstring& url, const RequestParams& params, const RequestHeaders& headers, ReqType type = REQ_GET);
	HRESULT SendRequest(const std::wstring& url, const RequestParams& params, ReqType type = REQ_GET);
	HRESULT SendRequest(const std::wstring& url, ReqType type = REQ_GET);

	const std::wstring& GetResult() const { return m_result; }
	const std::string& GetResultUTF8() const { return m_resultUTF8; }
	const std::wstring& GetLastError() const { return m_lastError; }
private:
	std::wstring m_result;
	std::string m_resultUTF8;

	std::wstring m_lastError;
};
