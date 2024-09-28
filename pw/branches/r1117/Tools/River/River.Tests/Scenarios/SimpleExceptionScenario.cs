using System;
using River.Core;

public class SimpleExceptionScenario : Scenario
{
  public SimpleExceptionScenario()
  {
    throw new Exception( "Qwerty" );
  }
}
