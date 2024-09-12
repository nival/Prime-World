#ifndef SINGLETON_H__
#define SINGLETON_H__

template <class BASE> class Singleton
{
private:
  static BASE* instance;

protected:
  Singleton() {}
  ~Singleton() {}

public:
  static BASE* Init()
  {
    instance = new BASE();
	return Get();
  }

  template <class PARAM0> static void Init(PARAM0& p0)
  {
    instance = new BASE(p0);
  }

  template <class PARAM0, class PARAM1> static void Init(PARAM0& p0, PARAM1& p1)
  {
    instance = new BASE(p0, p1);
  }

  static void Term()
  {
    delete instance;
    instance = NULL;
  }

  static BASE* Get()
  {
    return instance;
  }
};

template<class BASE> BASE* Singleton<BASE>::instance = NULL;

#endif //SINGLETON_H__

