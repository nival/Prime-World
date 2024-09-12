#pragma once

///
template <typename VecT, typename SclrT>
inline VecT Lerp( const VecT &left, const VecT &right, SclrT k )
{
	//NI_ASSERT(k >= 0.0f && k <= 1.0f, "Invalid lerp coeficient!");
	return right * k + left * (1 - k);
}


template <typename T>
inline T SerpStepFactor( T k )
{
  //Smoothstep
  //http://sol.gfxile.net/interpolation/index.html#c4
  return k * k * (3 - 2 * k);
}

template <typename T>
inline T SmoothDampStepFactor( T k )
{
  //Данная функция быстро набирает скорость и плавно останавливается - 
  //её график похож на Serp но смещён вправо.
  //Интерполяция с её помощью смотрится приятнее для глаза, чем Serp и SerpX2.
  //Получена при помощи следующего кода на Maple:
  /*
    restart;
    F := x -> C0 * x^4 + C1 * x^3 + C2 * x^2 + C3 * x^1;
    F1 := unapply( diff(F(x), x ), x );
    F2 := unapply( diff(F(x), x, x ), x );
    Sys := { F1(0) = 0, F1(1) = 0, F2(1/3) = 0, F(1) = 1 }:
    Rez := solve(Sys);
    SmoothStep := x -> ((x) * (x) * (3 - 2 * (x))):
    ResultFormula := factor(eval(F(x),Rez));
    plot( [eval(F(x),Rez), eval(F1(x),Rez), eval(F2(x),Rez), SmoothStep(x), SmoothStep(SmoothStep(x))], x = 0..1, y=-0.5..1.5 );
  */
  
  const T k2 = k * k;
  return  k2 * ( 3 * k2 - 8 * k + 6 ); 
}


//Cheap approximation of sinus(x) interpolation
template <typename VecT, typename SclrT>
inline VecT Serp( const VecT &left, const VecT &right, SclrT k )
{
  return Lerp( left, right, SerpStepFactor(k) );
}

//Cheap approximation of sinus(sinus(x)) interpolation
template <typename VecT, typename SclrT>
inline VecT SerpX2( const VecT &left, const VecT &right, SclrT k )
{
  return Lerp( left, right, SerpStepFactor(SerpStepFactor(k)) );
}  

//Asymmetric S-curve interpolation. Fast in - Slow out.
//Fast racing at the beginning and a long stopping.
template <typename VecT, typename SclrT>
inline VecT SmoothDamp( const VecT &left, const VecT &right, SclrT k )
{
  return Lerp( left, right, SmoothDampStepFactor(k) );
}

// SmoothCritDamp for ease-in / ease-out smoothing
// Позволяет плавно изменять величину от текущего значения curPos до целевого toPos,
// таким образом, что на плавности изменения не отражается перемещение 
// конечного значения toPos во время движения. Поведение моделирует резинку или 
// пружину на которой подвешен один объект, с координатными curPos, к другому с координатами
// toPos
// Текущая скорость хранится во внешней переменной velocity, а изменение времени с последнего
// вызова передаётся в timeDelta
// Жёсткость пружины определяется, через параметр smoothTime, который характеризует максимальное 
// расстояние от текущей позиции до целевой (время лага):
//    <Максимальное расстояние> = <Текущая скорость> * smoothTime; 
template <typename VecT, typename SclrT>
inline VecT SmoothCritDamp(const VecT &curPos, const VecT &toPos, VecT &velocity, SclrT timeDelta, SclrT smoothTime )
{
  //Based on Game Programming Gems 4 Chapter 1.10
  const SclrT omega = 2.f / smoothTime;
  const SclrT x = omega * timeDelta;
  const SclrT exp = 1.f / ( 1.f + x + 0.48f * x * x + 0.235f * x * x * x );
  const VecT change = curPos - toPos;
  const VecT temp = ( velocity + omega * change ) * timeDelta;
  velocity = ( velocity - omega * temp ) * exp;  
  return toPos + ( change + temp ) * exp;
}


template<typename T> 
__forceinline T BiLerp(const T& P00,const T& P10,const T& P01,const T& P11, float FracX, float FracY)
{
	return Lerp(
		Lerp(P00,P10,FracX),
		Lerp(P01,P11,FracX),
		FracY
		);
}

