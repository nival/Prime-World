using System;

namespace BusinessLogic.Queuing
{
  public interface ITask
  {

    int ErrorCount { get; set; }
    string LastErrorMessage { get; set; }
    DateTime? LastExecutionTime { get; set; }

    string Dump();

    bool Execute();

  }
}