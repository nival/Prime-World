using System;
using System.CodeDom.Compiler;
using System.Threading;
using NUnit.Framework;
using River.Master;

namespace River.Tests.Master
{
  [TestFixture]
  public class BotNetTests
  {
    #region BotNet tests

		[Test, Description( "Test that 1 bot in Botnet allows to create a RunningSuite" )]
		public void TestSingleBotRSCreation()
		{
			BotNet bn = new BotNet();
			MockBot ibot = new MockBot();
			MasterBot mbot = new MasterBot( ibot );
			bn.RegisterBot( mbot );

			RunningSuite rs = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty );
			Assert.IsNotNull( rs );
			Assert.AreEqual( MasterBot.BotStatus.Loading, mbot.Status );
			ibot.StopLoading();
			ThreadUtils.WaitFor( () => { return !ibot.Loading; } );
			Assert.AreEqual( "SimpleScenario", ibot.LoadedType );
		}

    [Test, Description( "Test that disconnected single bot in BotNet gets an exception when trying to get a RunningSuite" )]
		[ExpectedException( typeof( InvalidOperationException ), MatchType = MessageMatch.Contains, ExpectedMessage = "1" )]
    public void TestSingleBotDisconnectRSCreation()
    {
      BotNet bn = new BotNet();
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );

      bn.RegisterBot( mbot );
      mbot.Disconnect();
      RunningSuite rs = null;
      rs = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
    }

    [Test, Description( "Test that we can not create a RunningSuite if all bots are taken" )]
		[ExpectedException( typeof( InvalidOperationException ), MatchType = MessageMatch.Contains, ExpectedMessage = "1" )]
		public void TestSingleBotTwoRSCreation()
    {
      BotNet bn = new BotNet();
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );
      bn.RegisterBot( mbot );

      RunningSuite rs1 = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
      RunningSuite rs2 = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
		}

		[Test, Description( "Test that a bot becomes available after a RunningSuite finishes with it" )]
    public void TestSingleBotRecycling()
    {
      BotNet bn = new BotNet();
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );
      bn.RegisterBot( mbot );
      RunningSuite rs1 = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
			ibot.StopLoading( new CompilerError() );
			ThreadUtils.WaitFor( () => { return mbot.Status == MasterBot.BotStatus.Idle; } );

      RunningSuite rs2 = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
      Assert.IsNotNull( rs2 );
      Assert.AreEqual( MasterBot.BotStatus.Loading, mbot.Status );
    }

    [Test, Description( "Test that two bots get distributed between two RunningSuites" )]
    public void TestMultipleBotDistribution()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs1 = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
      Assert.IsTrue( mbot1.Status == MasterBot.BotStatus.Idle || mbot2.Status == MasterBot.BotStatus.Idle );
      Assert.IsTrue( mbot1.Status == MasterBot.BotStatus.Loading || mbot2.Status == MasterBot.BotStatus.Loading );
      RunningSuite rs2 = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
      Assert.IsNotNull( rs2 );
      Assert.IsTrue( mbot1.Status == MasterBot.BotStatus.Loading && mbot2.Status == MasterBot.BotStatus.Loading );
    }

    [Test, Description( "Test that RunningSuite can be created for 2 bots (out of 3)" )]
    public void Test2BotRSCreation()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );
      MockBot ibot3 = new MockBot();
      MasterBot mbot3 = new MasterBot( ibot3 );
      bn.RegisterBot( mbot3 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      int usedCount = 0;
      if ( mbot1.Status == MasterBot.BotStatus.Loading )
        ++usedCount;
      if ( mbot2.Status == MasterBot.BotStatus.Loading )
        ++usedCount;
      if ( mbot3.Status == MasterBot.BotStatus.Loading )
        ++usedCount;
      Assert.AreEqual( 2, usedCount );
      Assert.IsTrue( mbot1.Status == MasterBot.BotStatus.Idle 
        || mbot2.Status == MasterBot.BotStatus.Idle 
        || mbot3.Status == MasterBot.BotStatus.Idle );
    }

    [Test, Description( "Test that RunningSuite can be created for 3 bots" )]
    public void Test3BotRSCreation()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );
      MockBot ibot3 = new MockBot();
      MasterBot mbot3 = new MasterBot( ibot3 );
      bn.RegisterBot( mbot3 );

      RunningSuite rs = bn.CreateRunningSuite("ThreeBotsSuite", null, Scenarios.Scenarios.ThreeBotsSuite, Guid.Empty);
      Assert.IsTrue( mbot1.Status == MasterBot.BotStatus.Loading
        && mbot2.Status == MasterBot.BotStatus.Loading 
        && mbot3.Status == MasterBot.BotStatus.Loading );
    }

    #endregion
  }
}
