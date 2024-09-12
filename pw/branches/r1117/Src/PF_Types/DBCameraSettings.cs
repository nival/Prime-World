using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;

namespace PF_GameLogic.DBStats
{

public class DampSmoothing
{
  [Description("Время лага пружины в режиме наблюдения за героем. " +
               "Характеризует максимальное расстояние от текущей позиции до целевой: " +
               "<Максимальное расстояние> = <Текущая скорость> * <Время лага>")]
  public float dampTimeObserv = 0.4f;

  [Description("Время лага пружины в режиме свободного перемещения")]
  public float dampTimeMove = 0.2f;

  [Description("Длина вектора на который смещается точка привязки камеры в режиме " +
               "наблюдения за героем. " +
               "Вектор направлен в сторону взгляда героя и служит для того чтобы с одной " + 
               "стороны камера не слишком отставала при движении, а с другой стоны," +
               "для того чтобы можно было увидеть больше в направлении взгляда героя, " +
               "где обычно происходит самое интересное")]
  public float anchorShiftObserv = 2.5f;

  [Description("Длина вектора при максимальном зуме на который смещается точка привязки " + 
               "камеры в режиме наблюдения за героем. Вектор направлен в ту же сторону, " + 
               "что и камера и служит для того чтобы в центре экрана находилось тело героя, " +
               "а не его ботинки")]
  public float projCorretionShiftObservMaxZoom = 2.2f;

  [Description("Длина вектора при минимальном зуме на который смещается точка привязки " +
               "камеры в режиме наблюдения за героем. Вектор направлен в ту же сторону, " +
               "что и камера и служит для того чтобы в центре экрана находилось тело героя, " +
               "а не его ботинки")]
  public float projCorretionShiftObservMinZoom = 0.0f;

  [Description("Время первого прыжка камеры в режиме свободного перемещения. " +
               "Такой прыжок нужен для того, чтобы повысить отзывчивость камеры, " +
               "которая без такого смещения ощутимо сопротивляется движению")]
  public float firstJumpTime = 0.2f;

  [Description("Коэффициент зависимости смещения камеры от текущего зума в режиме " +
               "свободного перемещения. " +
               "Без такой зависимости при приближении к земле камеру невозможно подвинуть " +
               "к конкретному предмету. При значении 1 зависимость отсутствует, далее " +
               "при уменьшении коэффициента зависимость увеличивается. Поведение камеры " +
               "при зуме по-умолчанию не зависит " +
               "от данного коэффициента")]
  public float zoomFactorMove = 0.1f;

  [Description("Коэффициент зависимости смещения камеры от текущего зума в режиме " +
               "наблюдения за героем. " +
               "Данная зависимость  управляет dampTimeObserv и anchorShiftObserv")]
  public float zoomFactorObserv = 0.7f;

  [Description("Максимальная скорость камеры")]
  public float maxSpeed = 60.0f;

  [Description("Время за которое достигается максимальная скорость движения камеры " +
               "в режиме свободного перемещения при непрерывном нажатии кнопки")]
  public float timeToMaxSpeed = 3.0f;
}

[UseTypeName("CAMS")]
public class AdventureCameraSettings : DBResource
{
  [Description("Camera id to be used in console commands")]
  public string name;

  [Description("Camera movement speed")]
  public float movementSpeed = 3;
  [Description("Angle (0..90) from land plane in bottom-position")]
  public float vertAngleBottom = 0;
  [Description("Length of rod in bottom-position")]
  public float vertLengthBottom = 0;
  [Description("Angle (0..90) from land plane in top-position")]
  public float vertAngleTop = 0;
  [Description("Length of rod in top-position")]
  public float vertLengthTop = 0;
  [Description("Time of vertical deviation from top to bottom")]
  public float vertTime = 0;

  [Description("Default horizontal angle (yaw)")]
  public float horCenterAngle = 0;
  [Description("Max horizontal deviation (0..90)")]
  public float horAngle = 0;
  [Description("Time of max horizontal deviation")]
  public float horTime = 0;

  [Description("Limit ellipse horizontal radius")]
  public float limitRadiusHor  = 200.0f;
  [Description("Limit ellipse vertical radius")]
  public float limitRadiusVert = 200.0f;

  [Description("Static camera fov")]
  public float fov = 70.0f;
  [Description("FOV correction angle for non-standard aspects")]
  public float fovCorrectionAngle = 66.0f;

  [Description("Radius of height filtration (on meters)")]
  public float smoothRadius = 3.0f;
  [Description("Smooth area discretization (0 - use only center point)")]
  public int smoothDiscrete = 3;
  [Description("Influence of neighboring points (sigma). Bigger than 0")]
  public float smoothDensity = 2.0f;

  [Description("Radius of landscape collision check (on meters)")]
  public float pitchRMax = 3.0f;
  [Description("Radius of const values of landscape collision check ( <= pitchRMax)")]
  public float pitchRConst = 1.0f;
  [Description("Landscape collision area discretization (0 - use only center point)")]
  public int pitchDiscrete = 3;
  [Description("Minimal height of camera in bottom (on meters)")]
  public float minCameraHeight = 1.0f;
  [Description( "Center offset of camera" )]
  public Vec2 centerOffset;

  [Description( "Camera zoom speed scale" )]
  public float zoomSpeed = 1.0f;

  [Description("Maximum zoom factor value; Use values greater than 1.0 to extend over normal camera settings")]
  public float maxZoomFactor = 1.0f;

	[FieldCategory("Map lock overrides")]
	[Description( "Multiplier for locking outside tiles by camera's limitRadiusHor" )]
	public float lockMultRadiusHor = 1.0f;

	[FieldCategory("Map lock overrides")]
	[Description( "Multiplier for locking outside tiles by camera's limitRadiusVert" )]
	public float lockMultRadiusVert = 1.0f;

	[FieldCategory("Map lock overrides")]
	[Description( "Locking outside tiles center offset from camera's centerOffset" )]
	public Vec2 lockCenterOffset = new Vec2( 0.0f, 0.0f );

  [Description("New camera movement algorithm based on damping oscillation")]
  public DampSmoothing dampSmoothing;
}

[UseTypeName("CAMS")]
public class WebTowerCameraSettings : DBResource
{
  [Description("Linear speed")]
  public float linearSpeed = 4.0f;
  [Description("Initial pitch")]
  public float initialPitch = -0.4f;
  [Description("Yaw speed")]
  public float yawSpeed = 1.0f;
  [Description("Height offset")]
  public float heightOffset = 0.0f;
  [Description("Min rod")]
  public float minRod = 1.0f;
  [Description("Max rod")]
  public float maxRod = 15.0f;
}

}
