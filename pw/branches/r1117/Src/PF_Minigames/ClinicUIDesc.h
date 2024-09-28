#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

namespace EClinicLevelStatus
{
  enum Enum
  {
    //Внимание, в коде используются также и целочисленные значения констант!
    Incomplete,
    Complete,
    SilverMedal,
    GoldMedal
  };
};


namespace EClinicCreepAward
{
  enum Enum
  {
    None,
    SilverMedal,
    GoldMedal
  };
};


struct ClinicCreepUIDesc
{
	wstring creepName;
  NDb::Ptr<NDb::BaseUIMaterial> imageMaterial;
	float barValue;
  float goldMade;
  EClinicCreepAward::Enum award;
	bool isFled;

  ClinicCreepUIDesc() : barValue(0.f), goldMade(0), award(EClinicCreepAward::None), isFled(false) {}
};


struct ClinicLevelUIDesc
{
	nstl::wstring name;
	nstl::wstring desc;
	bool available;
  EClinicLevelStatus::Enum lastStatus, bestStatus;
  float goldMade;

  ClinicLevelUIDesc() : available(false), lastStatus(EClinicLevelStatus::Incomplete), bestStatus(EClinicLevelStatus::Incomplete), goldMade(0) {}
};

typedef nstl::vector<PF_Minigames::ClinicCreepUIDesc> ClinicCreepsUIDesc;

} // namespace PF_Minigames
