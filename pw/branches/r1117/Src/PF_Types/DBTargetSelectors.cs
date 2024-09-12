//#include "DBUnit.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_GameLogic.DBUnit;

namespace PF_GameLogic.DBAbility
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E676B40)]
  [UseTypeName("TGSL")]
	[FactoryBase( "Create", "NWorld::PFTargetSelector", "NWorld::PFWorld* world" )]
  public class TargetSelector : DBResource
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ETargetSelectorMode
  {
    Normal = 0,
    CaptureTargets,
    SendOnce,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ESortingOrder
  {
    Increasing,
    Decreasing,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Flags]
  public enum ETargetSelectorFlags
  {
    Zero = 0,
    IgnoreOriginalTarget = 1,
    DeadAllowed = 2,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ETargetSelectorPoint
  {
    AbilityOwner,
    CurrentPosition,
    PreviousPosition,
    OwnerDirection,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E6C82C0)]
  [UseTypeName("TGSL")]
  public class MultipleTargetSelector : TargetSelector
  {
    [Description("Selector working mode")]
    public ETargetSelectorMode mode = ETargetSelectorMode.Normal;

    [Description("Target selector flags")]
    public ETargetSelectorFlags flags = ETargetSelectorFlags.Zero;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E7192C0)]
  [UseTypeName("TGSL")]
  public class MultipleTargetSelectorFiltered : MultipleTargetSelector
  {
    [Description("Flags that specify targets of this spell. Specify 0 if you want to apply this spell on sender.")]
    public ESpellTarget targetFilter = ESpellTarget.AllEnemies | ESpellTarget.VisibleTargetsOnly;
  }



  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E6C82C1)]
  [UseTypeName("TGSL")]
  public class SingleTargetSelector : TargetSelector
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Multiple target selectors
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E676B40)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFAreaTargetSelector", "PFTargetSelector.h")]
  public class AreaTargetSelector : MultipleTargetSelectorFiltered
  {
    [Description("Range of selection")]
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");

    [Description("Absolute position of area selection center point; set (0,0) to ignore this parameter")]
    public Vec2 absolutePosition = new Vec2(0.0f, 0.0f);

    [Description("Position from which AreaTargetSelector should search targets")]
    public DBPtr<SingleTargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2B7BB4C0)]
  [DBVersion(1)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFConditionTargetSelector", "PFTargetSelector.h")]
  public class ConditionTargetSelector : MultipleTargetSelector
  {
    public DBPtr<MultipleTargetSelector> targetSelector;

    [Description("Selection condition")]
    public ExecutableBoolString condition = new ExecutableBoolString("true");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E6C8A40)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFSectorTargetSelector", "PFTargetSelector.h")]
  [DBVersion(1)]
  public class SectorTargetSelector : MultipleTargetSelectorFiltered
  {
    [Description("Begin of segment defining direction")]
    public ETargetSelectorPoint segmentBegin = ETargetSelectorPoint.AbilityOwner;

    [Description("End of segment defining direction")]
    public ETargetSelectorPoint segmentEnd = ETargetSelectorPoint.CurrentPosition;

    [Description("Range of selection")]
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");

    [Description("Range of selection")]
    public float angle = 90.0f;

    [Description( "Account segmentEnd as sector's center" )]
    public bool centerIsSegmentEnd = false;

    [Description("Дополнительный поворот выбранного направления сектора, в градусах")]
    public float segmentDirectionOffset = 0.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E6CBAC0)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFCapsuleTargetSelector", "PFTargetSelector.h")]
  [DBVersion(1)]
  public class CapsuleTargetSelector : MultipleTargetSelectorFiltered
  {
    [Description("Begin of segment defining direction")]
    public ETargetSelectorPoint segmentBegin = ETargetSelectorPoint.AbilityOwner;

    [Description("End of segment defining direction")]
    public ETargetSelectorPoint segmentEnd = ETargetSelectorPoint.CurrentPosition;

    [Description("If defined, overrides segmentEnd")]
    public DBPtr<SingleTargetSelector> segmentEndTargetSelector = null;

    [Description("Range of selection")]
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");

    [Description("Range from ability owner. Set to 0 if not required.")]
    public ExecutableFloatString rangeFromOwner = new ExecutableFloatString( "0.0f" );

    [Description("Cutoff beginning of the first segment")]
    public bool cutoffFirstSegment = false;

    [Description("Дополнительный поворот выбранного направления капсулы, в градусах")]
    public float segmentDirectionOffset = 0.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E67EC00)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFNearestInAreaTargetSelector", "PFTargetSelector.h")]
  public class NearestInAreaTargetSelector : MultipleTargetSelectorFiltered
  {
    [Description("Range of selection")]
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Flags]
  public enum SummonTypeFlags
  {
    Primary   = 1 << SummonType.Primary,
    Secondary = 1 << SummonType.Secondary,
    Pet       = 1 << SummonType.Pet,
    Clone     = 1 << SummonType.Clone,
  }

  [TypeId(0x9E677280)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFSummonEnumerator", "PFTargetSelector.h")]
  public class SummonEnumerator : MultipleTargetSelector
  {
    public SummonTypeFlags summonTypes = SummonTypeFlags.Primary;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E677300)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFUnitEnumerator", "PFTargetSelector.h")]
  public class UnitEnumerator : MultipleTargetSelectorFiltered
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E67AB00)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFHeroEnumerator", "PFTargetSelector.h")]
  public class HeroEnumerator : MultipleTargetSelectorFiltered
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Single target selectors
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E6C8340)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFNearestTargetSelector", "PFTargetSelector.h")]
  public class NearestTargetSelector : SingleTargetSelector
  {
    [Description("Target selector to select from")]
    public DBPtr<TargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E71DB80)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFUnitPlaceCorrector", "PFTargetSelector.h")]
  public class UnitPlaceCorrector : SingleTargetSelector
  {
    [Description("Target selector to select from")]
    public DBPtr<SingleTargetSelector> targetSelector;

    [Description("Искать место не дальше radius от requester'а. Задайте false если вам это не интересно.")]
    public bool checkByRangeToRequester = false;

    [Description("Искать место только на родном террейне")]
    public bool nativeTerrainOnly = false;

    [Description("Радиус, в котором искать место. Укажите 0, если он не превышает размеров юнита.")]
    public float radius = 0.0f;

    [Description("Типы проходимости для которых чекать свободно место. 0 - обычный режим.")]
    public ETraceMode passabilityCheckMode = 0;

    [Description("Чекать видимость или нет")]
    public bool checkLineOfSight = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum TargetToLandMode
  {
    First,
    Nearest,
    Center,
    CenterTarget,
  }

  [TypeId(0x9E71EBC1)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFConvertTargetToLand", "PFTargetSelector.h")]
  public class ConvertTargetToLand : SingleTargetSelector
  {
    [Description( "Метод преобразования нескольких целей в позицию на земле" )]
    public TargetToLandMode aggregateMode = TargetToLandMode.First;

    [Description("Target selector to select from")]
    public DBPtr<TargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB720B41)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFMainBuildingTargetSelector", "PFTargetSelector.h")]
  public class MainBuildingTargetSelector : SingleTargetSelector
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB720B42)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFFountainTargetSelector", "PFTargetSelector.h")]
  public class FountainTargetSelector : SingleTargetSelector
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF756BC0)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFShopTargetSelector", "PFTargetSelector.h")]
  public class ShopTargetSelector : SingleTargetSelector
  {
      public bool secret = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EUnitRelation
  {
    Master,
    Target,
    AlphaSummon,
    Mount,
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E6C8400)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFRelativeUnitTargetSelector", "PFTargetSelector.h")]
  public class RelativeUnitTargetSelector : SingleTargetSelector
  {
    public EUnitRelation relation = EUnitRelation.Master;
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[TypeId(0x1E728BC0)]
	[UseTypeName("TGSL")]
	[FactoryImpl("Create", "NWorld::PFUnitShiftTarget", "PFTargetSelector.h")]
	public class UnitShiftTarget : SingleTargetSelector
	{
		[FieldCategory("Maximal shift distance")]
    public ExecutableFloatString distance = new ExecutableFloatString("10.0f");
	}

  public enum EPointTargetSelectorMode
  {
    ToOwner,
    ToTarget,
    RangeFromOwner,
    RangeFromTarget,
    Interpolation,
    OffsetFromOwner,
    RangeFromTargetToRequester,
    OffsetFromTarget,
    RandomPoint,
    RandomDirection,
    RangeFromTargetToAbility,
  }

  [Flags]
  public enum ETraceMode
  {
    Dynamic = 1,
    Static = 2,
    Building = 4,
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(1)]
  [TypeId(0x1E728BC0)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFPointTargetSelector", "PFTargetSelector.h")]
  public class PointTargetSelector : SingleTargetSelector
  {
    public DBPtr<SingleTargetSelector> targetSelector;
    public EPointTargetSelectorMode mode = EPointTargetSelectorMode.ToOwner;
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");
    [Description("Смещение относительно хозяина. ВАЖНО! Нормируется и умножается на range!")]
    public Vec2 offset = new Vec2(0.0f, 1.0f);

    [Description("Works only for mode = RangeFromOwner, OffsetFromOwner, OffsetFromTarget")]
    public ETraceMode traceMode = 0;

    [Description("Check range with half sizes of owner and target")]
    public bool checkMinRange = true;

    [Description("Calculate new target as parallel to vector from owner to target which selected target from received unit position (only for RangeFromOwner)")]
    public bool paralleledTarget = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF738B00)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFFirstTargetSelector", "PFTargetSelector.h")]
  public class FirstTargetSelector : SingleTargetSelector
  {
    public DBPtr<MultipleTargetSelector> targetSelector;
    public bool nearestTarget = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0x2282AB00 )]
  [UseTypeName( "TGSL" )]
  [FactoryImpl( "Create", "NWorld::PFWeightTargetSelector", "PFTargetSelector.h" )]
  public class WeightTargetSelector : SingleTargetSelector
  {
    public DBPtr<MultipleTargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF738B01)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFListOfTargetSelectors", "PFTargetSelector.h")]
  public class ListOfTargetSelectors : MultipleTargetSelector
  {
    public List<DBPtr<TargetSelector>> targetSelectors = new List<DBPtr<TargetSelector>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF738B02)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFFilterTargetSelector", "PFTargetSelector.h")]
  public class FilterTargetSelector : MultipleTargetSelector
  {
    public DBPtr<MultipleTargetSelector> targetSelector;
    public List<DBPtr<Unit>> suitableUnits = new List<DBPtr<Unit>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE776A5C0)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFCountingTargetSelector", "PFTargetSelector.h")]
  public class CountingTargetSelector : MultipleTargetSelector
  {
    public DBPtr<MultipleTargetSelector> targetSelector;

    [Description("Число целей")]
    public ExecutableIntString targetsNumber = new ExecutableIntString("1");
    [Description("Выдавать героев в первую очередь")]
    public bool heroesFirst = false;
    [Description("Сортировать результаты по значению")]
    public bool enableSorting = false;
    [Description("Контрольное значение сортировки")]
    public ExecutableFloatString sortingValue = new ExecutableFloatString("1");
    [Description("Порядок сортировки")]
    public ESortingOrder order = ESortingOrder.Decreasing;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE776B440)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFComparingTargetSelector", "PFTargetSelector.h")]
  public class ComparingTargetSelector : SingleTargetSelector
  {
      public DBPtr<MultipleTargetSelector> targetSelector;

      [Description("Опорное значение")]
      public ExecutableFloatString referenceValue = new ExecutableFloatString("0.0f");
      [Description("Значение, которое будет сравниваться с опорным")]
      public ExecutableFloatString valueToCompare = new ExecutableFloatString("0.0f");
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB76C240)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFHighlanderA1TargetSelector", "PFHighlander.h")]
  public class HighlanderA1TargetSelector : MultipleTargetSelectorFiltered
  {
    [Description("Радиус для поиска целей")]
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");

    [Description("Количество целей, которых должен атаковать горец. Может зависеть от ранга абилки.")]
    public ExecutableFloatString targetCount = new ExecutableFloatString("1.0f");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE77B1C80)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFSelectApplicatorTarget", "PFTargetSelector.h")]
  public class SelectApplicatorTarget : SingleTargetSelector
  {
      [Description("Выбрать цель аппликатора (аналогично полю applyTarget аппликатора)")]
      public EApplicatorApplyTarget selectTarget = EApplicatorApplyTarget.ApplicatorTarget;

      [Description("Если не пусто: найти аппликатор у цели, заданной selectTarget и выбрать его цель namedApplicatorTarget")]
      public string applicatorName = "";

      [Description("Выбрать n-й по счету аппликатор с именем applicatorName (если applicatorName не пусто)")]
      public int applicatorIndex = 0;

      [Description("Выбрать цель именованного аппликатора (если applicatorName не пусто)")]
      public EApplicatorApplyTarget namedApplicatorTarget = EApplicatorApplyTarget.ApplicatorTarget;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE7832C00)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFApplicatorRecipientsTargetSelector", "PFTargetSelector.h")]
  public class ApplicatorRecipientsTargetSelector : MultipleTargetSelector
  {
      [Description("Аппликатор, получателей которого надо собрать")]
      public DBPtr<BaseApplicator> applicator;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xEF9752C0)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFFixToCenterTargetSelector", "PFTargetSelector.h")]
  public class FixToCenterTargetSelector : SingleTargetSelector
  {
    [Description("Target selector to select from")]
    public DBPtr<SingleTargetSelector> targetSelector;

    [Description("Name of script area that is used for definition parameters")]
    public string nameScriptArea = "";
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9A9C5C40)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFMaximizingTargetSelector", "PFAITargetSelectors.h")]
  public class MaximizingTargetSelector : SingleTargetSelector
  {
    [Description("Селектор, у которого максимизируем количество целей (по CurrentPosition)")]
    public DBPtr<MultipleTargetSelector> targetSelector;

    [Description( "Радиус, на котором ищем цель" )]
    public ExecutableFloatString range = new ExecutableFloatString( "0.0f" );

    [Description( "Поиск целей включится, только если в этом радиусе есть хотя бы одна цель c флагами из searchFilter" )]
    public ExecutableFloatString searchRange = new ExecutableFloatString( "0.0f" );

    [Description( "Flags that specify targets of this spell. Specify 0 if you want to apply this spell on sender." )]
    public ESpellTarget searchFilter = ESpellTarget.AllEnemies | ESpellTarget.VisibleTargetsOnly;


    [Description( "Если число целей меньше - не выбирать ни одной" )]
    public ExecutableIntString minTargetsNumber = new ExecutableIntString( "0" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0xE79C9480 )]
  [UseTypeName( "TGSL" )]
  [FactoryImpl( "Create", "NWorld::PFWallTargetSelector", "PFTargetSelector.h" )]
  public class WallTargetSelector : MultipleTargetSelectorFiltered
  {
    [Description( "Точка в которой находится центр стены" )]
    public DBPtr<SingleTargetSelector> origin;

    [Description( "Точка в которую смотрит стена (точнее перпендикуляр)" )]
    public DBPtr<SingleTargetSelector> direction;

    [Description( "Длина стены" )]
    public ExecutableFloatString length = new ExecutableFloatString( "4.0f" );

    [Description( "Ширина стены" )]
    public ExecutableFloatString width = new ExecutableFloatString( "2.0f" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0x9A9C5C41 )]
  [UseTypeName( "TGSL" )]
  [FactoryImpl( "Create", "NWorld::PFDelayTargetSelector", "PFAITargetSelectors.h" )]
  public class DelayTargetSelector : MultipleTargetSelector
  {
    [Description( "Селектор, чьи цели выдаем после задержки" )]
    public DBPtr<TargetSelector> targetSelector;

    [Description( "Время, в течении которого цель должна быть во вложенном селекторе, чтобы быть отданным этим селектором" )]
    public ExecutableFloatString delay = new ExecutableFloatString( "0.0f" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0x9A9C5C42 )]
  [UseTypeName( "TGSL" )]
  [FactoryImpl( "Create", "NWorld::PFCheckConditionTargetSelector", "PFAITargetSelectors.h" )]
  public class CheckConditionTargetSelector : MultipleTargetSelector
  {
    [Description( "Селектор, чьи цели выдаем, если условие выполнено" )]
    public DBPtr<TargetSelector> targetSelector;

    [Description( "Какие цели отбирать для проверки" )]
    public ExecutableBoolString condition = new ExecutableBoolString( "true" );

    [Description( "Если отобрано меньше целей - не выбирать ни одной" )]
    public ExecutableIntString minTargetsNumber = new ExecutableIntString( "0" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0x9A9C6C40 )]
  [UseTypeName( "TGSL" )]
  [FactoryImpl( "Create", "NWorld::PFNotTargetOfSameAbilitySelector", "PFAITargetSelectors.h" )]
  public class NotTargetOfSameAbilitySelector : MultipleTargetSelector
  {
    [Description( "Селектор, чьи цели проверяем и выдаем" )]
    public DBPtr<TargetSelector> targetSelector;

    [Description( "Селектор, который ищет применяющих ту же абилку" )]
    public DBPtr<TargetSelector> abilityCastersSelector;

    [Description( "Если цель абилки - точка, задает разрешенное расстояние между целями" )]
    public ExecutableFloatString minDistBetweenTargets = new ExecutableFloatString( "0.f" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EBetweenUnitsMode
  {
    AllPairs,
    Chain,
  }

  [TypeId( 0x9A9CE3C0 )]
  [UseTypeName( "TGSL" )]
  [FactoryImpl( "Create", "NWorld::PFBetweenUnitsTargetSelector", "PFTargetSelector.h" )]
  public class BetweenUnitsTargetSelector : MultipleTargetSelector
  {
    [Description( "Селектор, между целями которых будут возвращаемые точки" )]
    public DBPtr<MultipleTargetSelector> targetSelector;

    [Description( "Максимальное число возвращаемых позиций (0=неограничено)" )]
    public ExecutableIntString maxTargets = new ExecutableIntString( "0" );

    [Description( "Брать N*(N-1) пересечений (AllPairs) или N-1 (Chain) ?" )]
    public EBetweenUnitsMode pairMode = EBetweenUnitsMode.AllPairs;

    [Description( "Если пара целей ближе - не возвращать точку между ними" )]
    public ExecutableFloatString minDistBetweenTargets = new ExecutableFloatString( "0.f" );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EAttackersType
  {
      Targeters,
      DamageDealers,
  }

  [TypeId(0x9A9D43C0)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFAttackersTargetSelector", "PFTargetSelector.h")]
  public class AttackersTargetSelector : MultipleTargetSelectorFiltered
  {
      [Description("Which criteria to use, 'who targeted me' or 'who damaged me in x seconds'")]
      public EAttackersType type = EAttackersType.Targeters;

      [Description("Time span to cvount dealed damage (when type = DamageDealers)")]
      public ExecutableFloatString damageDealTime = new ExecutableFloatString("0.0f");

      [Description("Unit to get attackers from (using aplicator target if not specified)")]
      public DBPtr<SingleTargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9A9C5CD0)]
  [UseTypeName("TGSL")]
  [FactoryImpl("Create", "NWorld::PFDamagingLinksTargetSelector", "PFAITargetSelectors.h")]
  public class DamagingLinksTargetSelector : SingleTargetSelector
  {
      [Description("Селектор объектов, связанных с нами линками")]
      public DBPtr<MultipleTargetSelector> linkEndsSelector;

      [Description("Селектор, по которому линки бьют врагов")]
      public DBPtr<MultipleTargetSelector> linkTargetsSelector;

      [Description("Радиус от нас, на котором ищем цель")]
      public ExecutableFloatString moveRange = new ExecutableFloatString("0.0f");

      [Description("Не приближаемся к концам линков ближе заданного")]
      public ExecutableFloatString minRangeFromLinkEnds = new ExecutableFloatString("0.0f");

      [Description("Не отдаляемся от концов линков дальше заданного")]
      public ExecutableFloatString maxRangeFromLinkEnds = new ExecutableFloatString("0.0f");
  }

}
