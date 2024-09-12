using System.CodeDom.Compiler;
using NUnit.Framework;
using River.Core;
using River.Core.Suite;

namespace River.Tests.Core
{
	[TestFixture]
	public class SuiteTests
	{
		[Test, Description( "Test that compiler just ... compile" )]
		public void TestEmptyScenario()
		{
			string code =
				@"using System;";

			CompilerErrorCollection e = null;
			ScenarioDistributeInfo[] scenarios = Suite.GetScenarios( code, "CSharp", out e );
			Assert.IsFalse( e.HasErrors );
			Assert.AreEqual( scenarios.Length, 0 );
		}

		[Test, Description( "Test compilation of scenarion with single test and w/o DistributeAttribute specified" )]
		public void TestSingleTestScenarioWithDefaultDistribute()
		{
			string code =
				@"using System;
				using River.Core;
				public class SimpleTest : Scenario
				{
				}";

			CompilerErrorCollection e = null;
			ScenarioDistributeInfo[] scenarios = Suite.GetScenarios( code, "CSharp", out e );
			Assert.IsFalse( e.HasErrors );
			Assert.AreEqual( scenarios.Length, 1 );
			Assert.AreEqual( scenarios[0].TypeName, "SimpleTest" );
			Assert.AreEqual( scenarios[0].Count, 1 );
		}

		[Test, Description( "Test DistibuteAttribute" )]
		public void TestSingleTestScenarioWithCustomDistribute()
		{
			string code =
				@"using System;
				using River.Core;
				[Distribute( 5 )]
				[Distribute( 13 )]
				public class SimpleTest : Scenario
				{
				}";

			CompilerErrorCollection e = null;
			ScenarioDistributeInfo[] scenarios = Suite.GetScenarios( code, "CSharp", out e );
			Assert.IsFalse( e.HasErrors );
			Assert.AreEqual( scenarios.Length, 1 );
			Assert.AreEqual( scenarios[0].TypeName, "SimpleTest" );
			Assert.AreEqual( scenarios[0].Count, 18 );
		}

		[Test, Description( "Test that suite can create nessceary scenario" )]
		public void TestCreateScenario()
		{
			string code =
				@"using System;
				using River.Core;
				public class NonTrivialScenario_Name : Scenario
				{
				}";

			using ( Suite s = new Suite( code, "CSharp" ) )
			{
				CompilerErrorCollection e = null;
				Scenario scenario = s.CreateScenario( "NonTrivialScenario_Name", out e );
				Assert.IsFalse( e.HasErrors );
				Assert.IsNotNull( scenario );
				s.CleanUp();
			}
		}
	}
}
