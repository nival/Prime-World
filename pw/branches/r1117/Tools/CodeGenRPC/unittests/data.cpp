  REMOTE struct SimpleReplicated
  {
    RPC_ID(0xCCCCF007);
    SimpleReplicated()
    {
      i = 0;
      d = 0;
      s = 0;
      f = 0;
      b = 0;
      BoolVar = false;
    }

    REMOTE int i;
    REMOTE double d;
    REMOTE short s;
    REMOTE float f;
    REMOTE byte b;
    REMOTE bool BoolVar;
    REMOTE nstl::vector<int> vi;
    REMOTE nstl::vector<double> vd;
    REMOTE nstl::string name;

    REMOTE CObj<MyClass> mkl;
    REMOTE nstl::vector<CObj<YourClass>> ykl;
  };
