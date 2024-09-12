#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../Scripts/TypeWrapper.h"

struct IXmlSaver;

namespace NDb
{
struct LightEnvironment;
struct UICursor;

struct UICursorDesc
{
	string name;
	Ptr<UICursor> cursor;
	Ptr<UICursor> cursorOverlay;
	CTPoint<int> cursorOverlayOffset;

	UICursorDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DWORD CalcCheckSum() const { return 0; }
};

struct UISceneEnvironment
{
	string ID;
	Ptr<LightEnvironment> lightEnvironment;

	UISceneEnvironment();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DWORD CalcCheckSum() const { return 0; }
};

struct UISoundDesc
{
	string name;
	string soundFileName;

	UISoundDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DWORD CalcCheckSum() const { return 0; }
};

struct H6UIRoot : public DbResource
{
	DBRESOURCE_METHODS( H6UIRoot );
public:
	vector<UICursorDesc> cursors;
	vector<UISoundDesc> sounds;
	vector<UISceneEnvironment> sceneEnviroments;

	H6UIRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DWORD CalcCheckSum() const { return 0; }

	virtual bool GetVariantValue( NScript::VariantValue & value, const char *key ) const;
};

}; // namespace NDb
