using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using River.Core.Utils;

namespace River.Core.Suite
{
	public partial class Suite
	{
		private class SuiteCompiler : MarshalByRefObject
		{
			#region Private static constructor for ComplierParameters

			private static string[] systemRefs = new string[] { "mscorlib.dll", "System.dll" };
			private static string[] internalRefs = new string[] { "River.Core.dll" };

			private static CompilerParameters CreateCompilerParameters()
			{
				CompilerParameters compilerParameters = new CompilerParameters();
				compilerParameters.GenerateInMemory = true;
				compilerParameters.ReferencedAssemblies.AddRange( systemRefs );

				string entryAssemblyPath = Path.GetFullPath( Path.GetDirectoryName( Assembly.GetCallingAssembly().Location ) );
				foreach ( var internalRef in internalRefs )
					compilerParameters.ReferencedAssemblies.Add( Path.Combine( entryAssemblyPath, internalRef ) );

				return compilerParameters;
			}

			#endregion

			private Assembly assembly;

			public CompilerErrorCollection Compile( string source, string language )
			{
				assembly = null;

				CompilerResults results = null;
				try
				{
					CodeDomProvider provider = CodeDomProvider.CreateProvider( language );
					results = provider.CompileAssemblyFromSource( CreateCompilerParameters(), new string[] { source } );
				}
				catch ( Exception e )
				{
					CompilerErrorCollection errors = new CompilerErrorCollection();
					errors.Add( new CompilerError( string.Empty, 0, 0, string.Empty, e.Message ) );
					return errors;
				}

				if ( !results.Errors.HasErrors )
					assembly = results.CompiledAssembly;

				return results.Errors;
			}

			public ScenarioDistributeInfo[] GetScenarios()
			{
				if ( assembly == null )
					throw new InvalidOperationException( "Call Compile before GetScenarios" );

				List<ScenarioDistributeInfo> scenarios = new List<ScenarioDistributeInfo>();
				foreach ( Type type in assembly.GetTypes() )
				{
					if ( type.IsSubclassOf( typeof( Scenario ) ) )
					{
						object[] attrs = type.GetCustomAttributes( typeof( DistributeAttribute ), false );
						if ( attrs == null || attrs.Length == 0 )
							scenarios.Add( new ScenarioDistributeInfo( type.Name, new DistributeAttribute(), 1 ) );
						else
						{
							List<Pair<DistributeAttribute, int>> distributes = new List<Pair<DistributeAttribute, int>>();
							foreach ( object attr in attrs )
							{
								DistributeAttribute distribute = attr as DistributeAttribute;
								int index = distributes.FindIndex( ( Pair<DistributeAttribute, int> item ) => { return DistributeAttribute.IsEqual( item.Key, distribute ); } );
								if ( index == -1 )
									distributes.Add( new Pair<DistributeAttribute, int>( distribute, distribute.Count ) );
								else
									distributes[index].Value += distribute.Count;
							}
							foreach ( var distribute in distributes )
								scenarios.Add( new ScenarioDistributeInfo( type.Name, distribute.Key, distribute.Value ) );
						}
					}
				}

				return scenarios.ToArray();
			}

			public Scenario CreateScenario( string typeName )
			{
				if ( assembly == null )
					throw new InvalidOperationException( "Call Compile before GetScenarios" );

				Type type = assembly.GetType( typeName, false, false );
				if ( type == null )
					throw new ArgumentException( string.Format( "Cannot find scenario with type \"{0}\"", typeName ), "typeName" );

				ConstructorInfo cotr = type.GetConstructor( Type.EmptyTypes );
				if ( cotr == null )
					throw new InvalidOperationException( string.Format( "Cannot find default constructor for scenario with type \"{0}\"", typeName ) );

				try
				{
					Scenario result = cotr.Invoke( new object[0] ) as Scenario;
					if ( cotr == null )
						throw new InvalidOperationException( string.Format( "Cannot create valid scenario with type \"{0}\"", typeName ) );

					return result;
				}
				catch ( Exception e )
				{
					throw new InvalidOperationException( string.Format( "Cannot create valid scenario with type \"{0}\"", typeName ), e );
				}
			}
		}
	}
}
