using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Collections;

namespace EaselLevelEditor
{
  /// <summary>
  /// common class, representing spline trajectory
  /// </summary>
  public class EaselSpline
  {
    #region internal structures
    struct FPoint   // floating point coords 
    {
      public float x;
      public float y;
    }
    #endregion

    #region properties area

    public int MaxNumControlPoint
    {
      get { return MAX_NUM_CONTROL_POINTS; }
    }

    public int PointContainerCapacity
    {
      get { return POINT_CONTAINER_CAPACITY; }
    }

    public double SplinePresice
    {
      get { return SPLINE_PRECICE; }
    }

    public int CurveDegree
    {
      get { return curveDegree; }
      set
      {
        if (value > 0)
        {
          curveDegree = value;
          ReinitSpline();
        }
      }
    }

    public int ControlPointsNum
    {
      get { return numControlPoints; }
    }

    public Point[] ControlPoints
    {
      get
      {
        Point[] points = new Point[numControlPoints];
        currControlPoints.CopyTo(points);
        return points;
      }
    }

    public Point[] SplineLinearPoints
    {
      get
      {
        Point[] points = new Point[splinePoints.Count];
        splinePoints.Values.CopyTo(points, 0);
        return points;
      }
    }

    #endregion
    
    #region internal constant data
    
    //private const int CONTROL_POINT_OFFSET     = 10;

    private const int MAX_NUM_CONTROL_POINTS   = 100;
    private const int POINT_CONTAINER_CAPACITY = 100;
    private const double SPLINE_PRECICE        = 0.01;
    private const int CURVE_DEGREE             = 3;

    #endregion

    #region internal spline calculated data

    private Int64                    completeSplineLength;
    private Dictionary<Int64, Point> splinePoints;  // calculated spline linear points    

    private List<Point> currControlPoints;   // current control points number
    private List<int>   nodeVector;          // current nodes vector

    private int curveDegree;       // current curve degree
    private int numControlPoints;  // current control points number
    
    #endregion

    #region constructors
    public EaselSpline()
    {
      completeSplineLength = new Int64();
      completeSplineLength = 0;

      curveDegree = CURVE_DEGREE; // кубический сплайн

      splinePoints      = new Dictionary<Int64, Point>();
      currControlPoints = new List<Point>();
      nodeVector        = new List<int>();
            
      ClearControlPointsStorage();
      ClearNodeVector();
      ClearSplinePoints();
    }
    #endregion

    #region control points management operations

    public void AddControlPointAtEnd(Point controlPoint)
    {
      if(numControlPoints < MAX_NUM_CONTROL_POINTS)
      {
        currControlPoints.Add(controlPoint);
        numControlPoints++;
        ReinitSpline();
      }
    }

    public void AddControlPointAtNumber(Point controlPoint, int cpIndex)
    {
      if (cpIndex > MAX_NUM_CONTROL_POINTS && cpIndex <= 0)
        return;

      if (cpIndex > numControlPoints)
        AddControlPointAtEnd(controlPoint);
      else
      {
        currControlPoints.Insert(cpIndex - 1, controlPoint);
        numControlPoints++;
        ReinitSpline();
      }
    }

    public void ReplaceControlPointAtNumber(Point controlPoint, int cpIndex)
    {
      if (cpIndex > MAX_NUM_CONTROL_POINTS && cpIndex <= 0)
        return;

      currControlPoints.RemoveAt(cpIndex - 1);
      currControlPoints.Insert(cpIndex - 1, controlPoint);
      ReinitSpline();
    }

    public void RemoveControlPointAtNumber(int cpIndex)
    {
      if(cpIndex <= numControlPoints)
      {
        currControlPoints.RemoveAt(cpIndex - 1);
        numControlPoints--;
        ReinitSpline();
      }
    }

    #endregion

    #region spline initialization methods
    public bool InitSpline(List<Point> _points,int _numPoints)
    {
      currControlPoints = _points;
      numControlPoints  = _numPoints;

      return ReinitSpline();
    }

    private void CreateNodesVector()
    {
      int knots = 0;
      for(int i=0; i<(curveDegree+numControlPoints+1); i++)						// n+m+1 = nr of nodes
      {
        if (i > curveDegree)
        {
          if (i <= numControlPoints)
            //nodeVector[i] = ++knots;
            nodeVector.Insert(i, ++knots);
          else
            //nodeVector[i] = knots;	
            nodeVector.Insert(i, knots);
        }
        else
          //nodeVector[i] = knots; 		
          nodeVector.Insert(i, knots);
      }
    }

    private bool ReinitSpline()
    {
      if (numControlPoints == 0)
        return false;

      CreateNodesVector();

      splinePoints.Clear();

      FPoint coordSecond = new FPoint();
      coordSecond.x = 0;
      coordSecond.y = 0;

      FPoint coordFirst = new FPoint();
      coordFirst.x = currControlPoints[0].X;
      coordFirst.y = currControlPoints[0].Y;

      Int64 lenghtComplete = new Int64();    // complete spline lenght
      lenghtComplete = 0;

      for (double i = 0; i < nodeVector[curveDegree + numControlPoints]; i += SPLINE_PRECICE)   // точность прохода 
      {
        for (int j = 0; j < numControlPoints; j++)	// until  every cP is passed
        {
          if (i >= j) { coordSecond = CalculateDeBoor(curveDegree, j, i); }
        }

        // calculating line length
        double deltaX = Math.Abs(coordSecond.x - coordFirst.x);
        double deltaY = Math.Abs(coordSecond.y - coordFirst.y);

        lenghtComplete += (Int64)Math.Sqrt(deltaX*deltaX + deltaY*deltaY);

        Point splinePoint = new Point();
        splinePoint.X     = (int)coordSecond.x;
        splinePoint.Y     = (int)coordSecond.y;

        // adding new point to container    
        Int64 lenght = new Int64();
        lenght = lenghtComplete;

        if(splinePoints.ContainsKey(lenght) == false)
          splinePoints.Add(lenght,splinePoint);
        coordFirst = coordSecond;
      }

      double _deltaX = Math.Abs(coordFirst.x - currControlPoints[currControlPoints.Count - 1].X);
      double _deltaY = Math.Abs(coordFirst.y - currControlPoints[currControlPoints.Count - 1].Y);

      lenghtComplete += (Int64)Math.Sqrt(_deltaX * _deltaX + _deltaY * _deltaY);
      // adding new point to container    
      Int64 _lenght = new Int64();
      _lenght = lenghtComplete;

      Point _splinePoint = new Point();
      _splinePoint.X = (int)currControlPoints[currControlPoints.Count - 1].X;
      _splinePoint.Y = (int)currControlPoints[currControlPoints.Count - 1].Y;

      if (splinePoints.ContainsKey(_lenght) == false)
        splinePoints.Add(_lenght, _splinePoint);

      completeSplineLength = lenghtComplete;

      return true;
    }

    #endregion

    #region Cleanup operations
    // clean up operations
    private void ClearControlPointsStorage()
    {
      currControlPoints.Clear();
    }

    private void ClearNodeVector()
    {
      nodeVector.Clear();
    }

    private void ClearSplinePoints()
    {
      splinePoints.Clear();
      completeSplineLength = 0;
    }
    #endregion

    #region Spline intersection calculations

    private bool CheckIntersectsX(int x1, int x2, int target)
    {
      if ((target > x1 && target > x2) || (target < x1 && target < x2))
        return false;
      else
        return true;
    }

    private bool CheckIntersectsY(int y1, int y2, int target)
    {
      if ((target > y1 && target > y2) || (target < y1 && target < y2))
        return false;
      else
        return true;
    }

    private int FindYIntersectionPoint(Point pt1, Point pt2, int x)
    {
      if (pt1.Y == pt2.Y)
        return pt1.Y;

      int deltaY = Math.Abs((pt1.Y - x) * (pt2.Y - pt1.Y) / (pt2.X - pt1.X));
      if (pt1.Y > pt2.Y)
        return pt2.Y + deltaY;
      else
        return pt1.Y + deltaY;
    }

    private int FindXIntersectionPoint(Point pt1, Point pt2, int y)
    {
      if (pt1.X == pt2.X)
        return pt1.X;

      int deltaX = Math.Abs((pt2.Y - y) * (pt2.X - pt1.X) / (pt2.Y - pt1.Y));
      if (pt1.X > pt2.X)
        return pt2.X + deltaX;
      else
        return pt1.X + deltaX;
    }

    public int GetLengthByCoords(Point _coords,out Int64 _length,int _approximation)
    {
      _length = 0;

      if(splinePoints.Count == 0 )
        return -1;
    
      // internal calculation arrays
      int[] xCoord = new int[3];
      xCoord[0] = _coords.X; xCoord[1] = _coords.X-_approximation; xCoord[2] = _coords.X+_approximation;
      int[] yCoord = new int[3];
      yCoord[0] = _coords.Y; yCoord[1] = _coords.Y-_approximation; yCoord[2] = _coords.Y+_approximation;

      int aproximNum = 1;
      if(_approximation != 0)
        aproximNum = 3;


      IDictionaryEnumerator mapEnum = splinePoints.GetEnumerator();

      Point firstPoint = new Point(splinePoints[0].X, splinePoints[0].Y);
      Point secondPoint = new Point(splinePoints[0].X, splinePoints[0].Y);
      
      while(mapEnum.MoveNext() == true)
      {
        KeyValuePair<Int64, Point> pair = (KeyValuePair<Int64, Point>)mapEnum.Current;
        //DictionaryEntry pair = (DictionaryEntry)mapEnum.Current;
        Point value = (Point)pair.Value;

        secondPoint.X = value.X;
        secondPoint.Y = value.Y;

        // checking probable X intersection
        for (int i = 0; i < aproximNum; i++)
        {
          if ( CheckIntersectsX(firstPoint.X, secondPoint.X, xCoord[i])  )
          {
            int yPoint = FindYIntersectionPoint(firstPoint, secondPoint, xCoord[i]);
            if (yPoint >= (_coords.Y - _approximation) &&
                yPoint <= (_coords.Y + _approximation))   // point is on spline, need to get length
            {
              // calculating total lenght
              double deltaX = Math.Abs(firstPoint.X - xCoord[i]);
              double deltaY = Math.Abs(firstPoint.Y - yPoint);

              _length = (Int64)pair.Key + (Int64)Math.Sqrt(deltaX * deltaX + deltaY * deltaY);

              return 0;
            }
          }
        }

        // need to check possible Y intersection .....
        for (int i = 0; i < aproximNum; i++)
        {
          if ( CheckIntersectsY(firstPoint.Y, secondPoint.Y, yCoord[i])  )
          {
            int xPoint = FindXIntersectionPoint(firstPoint, secondPoint, yCoord[i]);
            if (xPoint >= (_coords.X - _approximation) &&
                xPoint <= (_coords.X + _approximation))
            {
              // calculating total lenght
              double deltaX = Math.Abs(firstPoint.X -xPoint);
              double deltaY = Math.Abs(firstPoint.Y - yCoord[i]);

              _length = (Int64)pair.Key + (Int64)Math.Sqrt(deltaX * deltaX + deltaY * deltaY);

              return 0;
            }
          }
        }

        firstPoint.X = secondPoint.X;
        firstPoint.Y = secondPoint.Y;
      }   
      
      return -1;    // passed coordinate is not on spline
    }

    public int GetXLineIntersect(int _xLine,out List<Point> _result)
    {
      _result = new List<Point>(10);

      if(splinePoints.Count == 0)
        return 0;

      if(splinePoints.Count == 1)
      {
        if(splinePoints[0].X == _xLine)   // first map point length is always 0
        {
          _result.Add(new Point(_xLine,splinePoints[0].Y));
          return 1;
        }
      }
      
      IDictionaryEnumerator mapEnum = splinePoints.GetEnumerator();
      
      Point firstPoint = new Point(0,0);
      Point secondPoint = new Point(0,0);
      
      while(mapEnum.MoveNext() == true)
      {
        DictionaryEntry pair = (DictionaryEntry)mapEnum.Current;
        Point value = (Point)pair.Value;
        secondPoint.X = value.X;
        secondPoint.Y = value.Y;
        
        // checking probable X intersection
        if ( CheckIntersectsX(firstPoint.X,secondPoint.Y,_xLine)  )
        {
            int targetPoint = FindYIntersectionPoint(firstPoint,secondPoint,_xLine);
            _result.Add(new Point(_xLine,targetPoint));
        }

        firstPoint.X = secondPoint.X;
        firstPoint.Y = secondPoint.Y;
      }
      
      //
      // UNDONE !!! позможно следует проверять последнюю границу
      //

      _result.Sort(CompareByXCoord);
      return _result.Count;
    }

    public int GetYLineIntersect(int _yLine,out List<Point> _result)
    {
      _result = new List<Point>(10);

      if(splinePoints.Count == 0)
        return 0;

      if(splinePoints.Count == 1)
      {
        if(splinePoints[0].Y == _yLine)   // first map point length is always 0
        {
          _result.Add(new Point(splinePoints[0].X,splinePoints[0].Y));
          return 1;
        }
      }
            
      IDictionaryEnumerator mapEnum = splinePoints.GetEnumerator();
      
      Point firstPoint = new Point(0,0);
      Point secondPoint = new Point(0,0);
  
      while(mapEnum.MoveNext() == true)
      {
        DictionaryEntry pair = (DictionaryEntry)mapEnum.Current;
        Point value = (Point)pair.Value;
        secondPoint.X = value.X;
        secondPoint.Y = value.Y;
        
        // checking probable X intersection
        if ( CheckIntersectsY(firstPoint.Y,secondPoint.Y,_yLine)  )
        {
          int targetPoint = FindXIntersectionPoint(firstPoint,secondPoint,_yLine);
          _result.Add(new Point(targetPoint,_yLine));
        }

        firstPoint.X = secondPoint.X;
        firstPoint.Y = secondPoint.Y;
      }
              
      //
      // UNDONE !!! позможно следует проверять последнюю границу
      //
       
      _result.Sort(CompareByYCoord);
      return _result.Count;
    }

    private static int CompareByYCoord(Point lhs,Point rhs)
    {
      if (lhs.Y > rhs.Y)
        return 1;
      else if (lhs.Y == rhs.Y)
        return 0;
      else
        return -1;
    }

    private static int CompareByXCoord(Point lhs,Point rhs)
    {
      if (lhs.X > rhs.X)
        return 1;
      else if (lhs.X == rhs.X)
        return 0;
      else
        return -1;
    }


    #endregion

    #region spline calculation methods
    // recursive deBoor algorithm implementation
    // u - step value
    // i - current control point number
    // r - curve degree
    FPoint CalculateDeBoor(int r, int i, double u)
    {
      if (r == 0)   // calculation is done
      {
        FPoint point = new FPoint();
        point.x = currControlPoints[i].X;
        point.y = currControlPoints[i].Y;
        
        return point;

        //return currControlPoints[i].ToCVec2();
      }
      else
      {
        double pre = (u - nodeVector[i + r]) / (nodeVector[i + curveDegree + 1] - nodeVector[i + r]);	// pre calculations

        FPoint point1 = CalculateDeBoor(r - 1, i, u);
        point1.x *= (float)(1-pre);
        point1.y *= (float)(1-pre);

        FPoint point2 = CalculateDeBoor(r - 1, i + 1, u);
        point2.x *= (float)pre;
        point2.y *= (float)pre;

        point1.x += point2.x;
        point1.y += point2.y;

        return point1;

        //return ((CalculateDeBoor(r - 1, i, u) * (1 - pre)) + (CalculateDeBoor(r - 1, i + 1, u) * (pre)));
      }
    }
    #endregion
  }
}
