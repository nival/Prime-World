using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Text.RegularExpressions;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;

namespace DBCodeGen.MaterialsGeneration
{
	public class FunctionName
	{
		private readonly string name = string.Empty;
		private readonly string parameters = string.Empty;
		private readonly bool constant = false;

		public FunctionName( string name, string parameters, bool constant )
		{
			this.name = name;
			this.parameters = parameters;
			this.constant = constant;
		}

		public override bool Equals( object obj )
		{
			FunctionName func = obj as FunctionName;
			if ( func == null )
				return false;

			return name == func.Name && parameters == func.parameters && constant == func.constant;
		}

		public override int GetHashCode()
		{
			return name.GetHashCode() ^ parameters.GetHashCode() ^ constant.GetHashCode();
		}

		public string Name { get { return name; } }
		public string Parameters { get { return parameters; } }
		public bool Constant { get { return constant; } }
	}

	public class FunctionInfo
	{
		private readonly string returnType = string.Empty;
		private readonly string body = string.Empty;

		private readonly List<string> projects = new List<string>();

		private FunctionInfo( string returnType, string body, string project )
		{
			this.returnType = returnType;
			this.body = body;
			projects.Add( project );
		}

		public static FunctionInfo CreateMaterial( string project )
		{
			return new FunctionInfo( "void", string.Empty, project );
		}

		public static FunctionInfo CreatePinSetter( Type pinType, string fieldName, string project )
		{
			return new FunctionInfo( "void", string.Format( "{0} = value; UpdateStaticShaderIndex()", fieldName ), project );
		}

		public static FunctionInfo CreatePinGetter( Type pinType, string fieldName, string project )
		{
			return new FunctionInfo( string.Format( "const NDb::{0}", DBCodeGen.GetTypeName( pinType ) ), string.Format( "return {0}", fieldName ), project );
		}

		public static FunctionInfo CreateSampler( string fieldName, bool constant, string project )
		{
      return new FunctionInfo( string.Format( "{0}{1}*", constant ? "const " : string.Empty, MaterialCompiler.SAMPLER_CLASS_NAME ), 
                               string.Format( "return &{0}", fieldName ), project);
		}

		public void AddProject( string project )
		{
			if ( !projects.Exists( item => item == project ) )
				projects.Add( project );
		}

		public bool IsEqual( string _returnType, string _parameters, string _body )
		{
			return returnType == _returnType && body == _body;
		}

		public bool IsEqual( FunctionInfo functionInfo )
		{
			return returnType == functionInfo.returnType;// && body == functionInfo.body;
		}

		public string ReturnType { get { return returnType; } }
		public string Body { get { return body; } }

		//public IEnumerable<string> Projects { get { return projects; } }
		public string Project { get { return projects[0]; } }
	}

	public enum FunctionFormat
	{
		PureVirtual,
		EmptyBody,
		Default,
	}

	public class FunctionsCollection
	{
		private readonly Dictionary<FunctionName, FunctionInfo> functions = new Dictionary<FunctionName, FunctionInfo>();
		private List<KeyValuePair<FunctionName, FunctionInfo>> sortedFunctions = new List<KeyValuePair<FunctionName, FunctionInfo>>();

		private int Compare( KeyValuePair<FunctionName, FunctionInfo> f1, KeyValuePair<FunctionName, FunctionInfo> f2 )
		{
			return string.Compare( f1.Key.Name, f2.Key.Name );
		}

		private void SortFunctions()
		{
			if ( sortedFunctions != null )
				return;

			sortedFunctions = new List<KeyValuePair<FunctionName, FunctionInfo>>( functions );
			sortedFunctions.Sort( Compare );
		}

		private bool AddFunction( FunctionName name, FunctionInfo info )
		{
			FunctionInfo function = null;
			if ( !functions.TryGetValue( name, out function ) )
				functions.Add( name, info );
			else if ( function.IsEqual( info ) )
				function.AddProject( info.Project );
			else
			{
				Trace.TraceError( "Function \"{0}\" defined twice with different return type, paramters and/or body", name.Name );
				return false;
			}

			sortedFunctions = null;
			return true;
		}

		public void Clear()
		{
			functions.Clear();
			sortedFunctions.Clear();
		}

		public bool FillFromMaterialType( Type material )
		{
			string project = string.Empty;
			CodeFile.TryGetProject( material, out project );

			MaterialFuncAttribute[] materialFuncs = TypeUtils.GetAttributes<MaterialFuncAttribute>( material, false );
			foreach ( MaterialFuncAttribute materialFunc in materialFuncs )
			{
				if ( materialFunc != null && materialFunc.Functions != null )
				{
					foreach ( string function in materialFunc.Functions )
					{
						Match funcMatch = Regex.Match( function, @"(?<name>[_A-Za-z][_A-Za-z0-9]*)[\s]*\([\s]*((?<params>[_A-Za-z\&\*][_A-Za-z\&\*0-9:<>\s]*[_A-Za-z0-9])([\s]*\,[\s]*(?<params>[_A-Za-z\&\*][_A-Za-z\&\*0-9:<>\s]*[_A-Za-z0-9]))*)?[\s]*\)[\s]*(?<const>const)?[\s]*" );
						if ( !funcMatch.Success || !funcMatch.Groups["name"].Success )
							continue;

						string parameters = string.Empty;
						if ( funcMatch.Groups["params"].Success && funcMatch.Groups["params"].Captures.Count > 0 )
						{
							List<string> paramsList = new List<string>();
							foreach ( Capture capture in funcMatch.Groups["params"].Captures )
								paramsList.Add( capture.ToString() );
							parameters = string.Join( ", ", paramsList.ToArray() );
						}

						FunctionName name = new FunctionName( funcMatch.Groups["name"].Value, parameters, funcMatch.Groups["const"].Success );
						FunctionInfo info = FunctionInfo.CreateMaterial( project );

						if ( !AddFunction( name, info ) )
							return false;
					}
				}
			}

			FieldInfo[] fields = DBCodeGen.GetFields( material, false, string.Empty, null );
			foreach ( FieldInfo field in fields )
			{
				Pin2Attribute pinAttribute = TypeUtils.GetAttribute<Pin2Attribute>( field, true );
				if ( pinAttribute != null && !string.IsNullOrEmpty( pinAttribute.ExposeName ) )
				{
					FunctionName setName = new FunctionName( string.Format( "Set{0}", pinAttribute.ExposeName ), string.Format( "const NDb::{0} value", DBCodeGen.GetTypeName( field.FieldType ) ), false );
					FunctionInfo setInfo = FunctionInfo.CreatePinSetter( field.FieldType, field.Name, project );
					if ( !AddFunction( setName, setInfo ) )
						return false;

					FunctionName getName = new FunctionName( string.Format( "Get{0}", pinAttribute.ExposeName ), string.Empty, true );
					FunctionInfo getInfo = FunctionInfo.CreatePinGetter( field.FieldType, field.Name, project );
					if ( !AddFunction( getName, getInfo ) )
						return false;
				}

				SamplerAttribute samplerAttribute = TypeUtils.GetAttribute<SamplerAttribute>( field, true );
				if ( samplerAttribute != null && !string.IsNullOrEmpty( samplerAttribute.ExposeName ) )
				{
					FunctionName getName = new FunctionName( string.Format( "Get{0}", samplerAttribute.ExposeName ), string.Empty, false );
					FunctionInfo getInfo = FunctionInfo.CreateSampler( field.Name, false, project );
					if ( !AddFunction( getName, getInfo ) )
						return false;

					FunctionName getConstName = new FunctionName( string.Format( "Get{0}", samplerAttribute.ExposeName ), string.Empty, true );
					FunctionInfo getConstInfo = FunctionInfo.CreateSampler( field.Name, true, project );
					if ( !AddFunction( getConstName, getConstInfo ) )
						return false;
				}
			}

			return true;
		}

		public bool HasFunction( FunctionName name ) { return functions.ContainsKey( name ); }
		public KeyValuePair<FunctionName, FunctionInfo> GetFunction( FunctionName name )
		{
			FunctionInfo function = null;
			if ( !functions.TryGetValue( name, out function ) )
				return new KeyValuePair<FunctionName, FunctionInfo>( name, null );

			return new KeyValuePair<FunctionName, FunctionInfo>( name, function );
		}

		public bool IsEmpty { get { return functions.Count == 0; } }
		public IEnumerable<KeyValuePair<FunctionName, FunctionInfo>> SortedFunctions { get { SortFunctions(); return sortedFunctions; } }

		public static string Format( KeyValuePair<FunctionName, FunctionInfo> function, FunctionFormat format )
		{
			string paramters = string.IsNullOrEmpty( function.Key.Parameters ) ? string.Empty : string.Format( " {0} ", function.Key.Parameters );

			switch ( format )
			{
			case FunctionFormat.PureVirtual:
				return string.Format( "virtual {0} {1}({2}){3} = 0;", function.Value.ReturnType, function.Key.Name, paramters, function.Key.Constant ? " const" : string.Empty );
			case FunctionFormat.Default:
				if ( string.IsNullOrEmpty( function.Value.Body ) )
					return string.Empty;
				else
					return string.Format( "virtual {0} {1}({2}){3} {{ {4}; }}", function.Value.ReturnType, function.Key.Name, paramters, function.Key.Constant ? " const" : string.Empty, function.Value.Body );
			case FunctionFormat.EmptyBody:
				if ( function.Value.ReturnType == "void" )
					return string.Format( "virtual {0} {1}({2}){3} {{ }}", function.Value.ReturnType, function.Key.Name, paramters, function.Key.Constant ? " const" : string.Empty );
				else
					return string.Format( "virtual {0} {1}({2}){3} {{ return ({0})0; }}", function.Value.ReturnType, function.Key.Name, paramters, function.Key.Constant ? " const" : string.Empty );
			}

			return string.Empty;
		}
	}
}
