using System;
using System.ComponentModel;
using libdb.DB;

namespace PF_GameLogic.DBDayNight
{
  public enum EDayNightState
  {
    Day,
    Night,
  }

  public class DayNightSettings
  {
    [Description("Начальное состояние после загрузки карты")]
    public EDayNightState initialState = EDayNightState.Day;

    [Description("Относительное смещение начального состояния. Пример: 0.3 - 30% дня (ночи) уже прошло на момент старта.")]
    [FloatMinMax(0.0f, 1.0f)]
    public float initialStateFraction = 0.0f;

    [Description("Длительность визуального эффекта перехода из дня в ночь и наоборот, в секундах")]
    [FloatMin(0.0f)]
    public float transitionDuration = 0.5f;
    [Description("Относительная граница, при переходе через которую меняется визуальное состояние MSO")]
    [FloatMinMax(0.0f, 1.0f)]
    public float transitionThreshold = 0.75f;

    [Description("Длительность дня, в секундах")]
    [FloatMin(5.0f)]
    public float dayDuration = 10.0f * 60.0f;
    [Description("Длительность ночи, в секундах")]
    [FloatMin(5.0f)]
    public float nightDuration = 10.0f * 60.0f;

    [FloatMin(0.0f), Browsable(false), HideInOutliner]
    public float twilightDuration = 1.0f * 60.0f;
    [FloatMinMax(0.0f, 1.0f), Browsable(false), HideInOutliner]
    public float twilightFraction = 0.5f;

    [Description("Коэффициент уменьшения specular-компоненты динамического освещения ночью")]
    [FloatMinMax(0.0f, 1.0f)]
    public float nightSpecularReduction = 0.4f;

    [Description("Прячет виджет времени суток")]
    public bool hideDayNightWidget = false;
  }
}
