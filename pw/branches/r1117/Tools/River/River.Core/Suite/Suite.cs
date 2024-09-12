using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Reflection;

namespace River.Core.Suite
{
	[Serializable]
	public sealed class ScenarioDistributeInfo
	{
		private readonly string typeName;
		private readonly DistributeAttribute distribute;
		private readonly int count;

		public ScenarioDistributeInfo( string typeName, DistributeAttribute distribute, int count )
		{
			this.typeName = typeName;
			this.distribute = distribute;
			this.count = count;
		}

		public string TypeName { get { return typeName; } }
		public int Count { get { return count; } }
		public DistributeAttribute Distribute { get { return distribute; } }
	}

	public sealed partial class Suite : IDisposable
	{
		private readonly string source;
		private readonly string language;

		private AppDomain domain;
		private SuiteCompiler compiler;

    string suiteName;
    string suiteDirectory;

		//TODO: Bot decide about running path, not suite, moreover due use restrictions folder AppDomain.CurrentDomain.BaseDirectory may be unaviable for writing
    public string SuitePath { get { return suiteDirectory; } }

		public Suite( string source, string language )
		{
			this.source = source;
			this.language = language;

      suiteName = Guid.NewGuid().ToString( "D" );
      suiteDirectory = AppDomain.CurrentDomain.BaseDirectory + "\\" + suiteName;
    }

		private CompilerErrorCollection CompileSuite()
		{
			if ( compiler != null )
				return new CompilerErrorCollection();

			domain = AppDomain.CreateDomain( suiteName, AppDomain.CurrentDomain.Evidence );
			compiler = domain.CreateInstanceAndUnwrap( Assembly.GetCallingAssembly().FullName, typeof( SuiteCompiler ).FullName ) as SuiteCompiler;
			return compiler.Compile( Source, Language );
		}

		public Scenario CreateScenario( string typeName, out CompilerErrorCollection errors )
		{
			errors = CompileSuite();
			if ( errors.HasErrors )
				return null;

			return compiler.CreateScenario( typeName );
		}

		public void CleanUp()
		{
			compiler = null;

			if ( domain != null )
			{
				AppDomain.Unload( domain );
				domain = null;
			}
		}

		public string Source { get { return source; } }
		public string Language { get { return language; } }

		#region IDisposable Members

		public void Dispose()
		{
			CleanUp();
		}

		#endregion

		/// <summary>
		/// Retrive aviable scenarios from suite's code
		/// </summary>
		/// <param name="source">Source of suite's code</param>
		/// <param name="language">Language of source</param>
		/// <param name="errors">Errors and warnings occured duiring compile</param>
		/// <returns>List of aviable scenarios</returns>
		public static ScenarioDistributeInfo[] GetScenarios( string source, string language, out CompilerErrorCollection errors )
		{
			List<ScenarioDistributeInfo> result = new List<ScenarioDistributeInfo>();
			using ( Suite s = new Suite( source, language ) )
			{
				errors = s.CompileSuite();
				if ( !errors.HasErrors )
					result.AddRange( s.compiler.GetScenarios() );
				s.CleanUp();
			}
			return result.ToArray();
		}
	}
}
