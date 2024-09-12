#ifndef _SINGLETON_4DLL_H_
#define _SINGLETON_4DLL_H_

template <class BASE> class Singleton4DLL
{
private:
  static BASE* instance;

	static void Set(BASE *instance_);

protected:
  Singleton4DLL() {}
  ~Singleton4DLL() {}

public:
	static BASE* Get();

	static void Init()
  {
    Set(new BASE());
  }

  template <class PARAM0> static void Init(PARAM0& p0)
  {
    Set(new BASE(p0));
  }

  template <class PARAM0, class PARAM1> static void Init(PARAM0& p0, PARAM1& p1)
  {
    Set(new BASE(p0, p1));
  }

  static void Term()
  {
    delete Get();
    Set(0);
  }
};

#define SINGLETON4DLL_DEF(BASE) \
	BASE * Singleton4DLL< BASE >::Get() { return instance; } \
	void Singleton4DLL< BASE >::Set(BASE *instance_) { instance = instance_; } \
	BASE * Singleton4DLL< BASE >::instance = 0;


#endif

