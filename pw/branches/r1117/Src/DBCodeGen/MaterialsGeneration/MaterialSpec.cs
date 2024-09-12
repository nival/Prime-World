using System;
using System.Collections.Generic;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;

namespace DBCodeGen.MaterialsGeneration
{
  public sealed class MaterialGroup
  {
    public string GroupName = String.Empty;
    public string BaseGroupName = String.Empty;
    public List<string> GroupFunctions = new List<string>();

    public override bool Equals(object obj)
    {
      if (obj is MaterialGroup)
      {
        return GroupName == (obj as MaterialGroup).GroupName;
      }
      return false;
    }

    public override int GetHashCode()
    {
      return base.GetHashCode();
    }
  }

	public sealed class MaterialSpec
	{
		private readonly string projectName = string.Empty;
		private readonly string baseMaterialDbName = string.Empty;

		private string baseMaterialParents = string.Empty;
		private string runtimePinsParents = string.Empty;

		private readonly List<string> runtimePins = new List<string>();
		private readonly List<string> includeMaterialDbHeaders = new List<string>();
		private readonly List<string> runtimePinsDefaults = new List<string>();
		private readonly List<string> materialDeclarations = new List<string>();
		private readonly List<string> projectsWithSpecs = new List<string>();
		private readonly List<string> materialRegistrations = new List<string>();
		private readonly List<string> shaders = new List<string>();
		private readonly List<string> shadersRegistrations = new List<string>();
    private readonly List<string> materialsGroup = new List<string>();
    private readonly List<string> materialOffsetsRegistrations = new List<string>();
    private readonly List<string> materialOffsetsDeclarations = new List<string>();

    private readonly List<MaterialGroup> alreadyAddedMaterialGroups = new List<MaterialGroup>();

		public MaterialSpec( string projectName, string baseMaterialDbName, IEnumerable<KeyValuePair<Type, string>> runtimePins, IEnumerable<CodeFile> dependencies )
		{
			this.projectName = projectName;
			this.baseMaterialDbName = baseMaterialDbName;

			foreach ( KeyValuePair<Type, string> runtimePin in runtimePins )
				this.runtimePins.Add( string.Format( "{0} {1};", DBCodeGen.GetFullTypeName( runtimePin.Key ), runtimePin.Value ) );

			foreach ( CodeFile dependency in dependencies )
				includeMaterialDbHeaders.Add( string.Format( "#include \"../{0}/{1}.h\"", dependency.Project, dependency.Name ) );
		}

    public void AddGroupDeclaration( string groupName, string baseGroupName, FunctionsCollection functions )
    {
      MaterialGroup materialGroup = new MaterialGroup();
      materialGroup.GroupName = groupName;
      if (string.IsNullOrEmpty(baseGroupName))
      {
        materialGroup.BaseGroupName = "Render::Material";
      }
      else
      {
        materialGroup.BaseGroupName = baseGroupName;
      }
      if (functions != null)
      {
        foreach (var function in functions.SortedFunctions)
        {
          string functionString = FunctionsCollection.Format(function, FunctionFormat.EmptyBody);

          if (!string.IsNullOrEmpty(functionString))
            materialGroup.GroupFunctions.Add(functionString);
        }
      }

      if (alreadyAddedMaterialGroups.Contains(materialGroup)) return;
      alreadyAddedMaterialGroups.Add(materialGroup);
      materialsGroup.AddRange( PatternFormatter.Format( Patterns.Patterns.MaterialGroup, materialGroup ) );
    }

		public void InitializeFinal( IEnumerable<string> _projectsWithSpecs, IEnumerable<KeyValuePair<Type, string>> runtimePins )
		{
			foreach ( string project in _projectsWithSpecs )
			{
				if ( project != projectName )
					projectsWithSpecs.Add( project );
			}
			projectsWithSpecs.Sort( String.Compare );

			baseMaterialParents = string.Format( " : public {0}, public {1}", MaterialCompiler.RENDER_MATERIAL_CLASS_NAME, MaterialCompiler.BASE_MATERIAL_INTERFACE_NAME );
			foreach ( string project in projectsWithSpecs )
			{
				baseMaterialParents += string.Format( ", public {0}::{1}", project, MaterialCompiler.BASE_MATERIAL_INTERFACE_NAME );
				runtimePinsParents += string.Format( "{2}public {0}::{1}", project, MaterialCompiler.RUNTIME_PINS_CLASS_NAME, string.IsNullOrEmpty( runtimePinsParents ) ? " : " : ", " );
			}

			foreach ( KeyValuePair<Type, string> runtimePin in runtimePins )
				runtimePinsDefaults.Add( string.Format( "{0} = ({1})0;", runtimePin.Value, DBCodeGen.GetFullTypeName( runtimePin.Key ) ) );
		}

    public void AddMaterialDeclaration(Type materialType, IEnumerable<MaterialPinDefenition> materialPins, string groupName, FunctionsCollection functions, Project finalProject, Project materialProject)
		{
			shaders.Add( DBCodeGen.GetTypeName( materialType ) );
			shadersRegistrations.Add( string.Format( "Render::RegisterShader( \"{0}\", {1} );", DBCodeGen.GetTypeName( materialType ), shaders.Count - 1 ) );

      MaterialCode code = new MaterialCode(BaseMaterialDbName, materialType, materialPins, groupName, functions, shaders.Count - 1, finalProject, materialProject);
      materialDeclarations.AddRange( PatternFormatter.Format( Patterns.Patterns.MaterialCode, code ) );

			materialRegistrations.Add( string.Format( "Render::RegisterMaterialType( {0}::typeId, {0}::CreateMaterial, \"{0}\" );", DBCodeGen.GetTypeName( materialType ) ) );


      if( code.SamplersCount > 0)
      {
        materialOffsetsDeclarations.Add( string.Format( "int {0}::samplersOffsets[{1}];",
          DBCodeGen.GetTypeName( materialType ), code.SamplersCount ) );

        materialOffsetsRegistrations.Add( string.Format( "{0}::InitSamplersOffsets();",
          DBCodeGen.GetTypeName( materialType ) ) ); 
      }
		}

		public string ProjectName { get { return projectName; } }
		public string BaseMaterialInterfaceName { get { return MaterialCompiler.BASE_MATERIAL_INTERFACE_NAME; } }
		public string RuntimePinsClassName { get { return MaterialCompiler.RUNTIME_PINS_CLASS_NAME; } }
		public string MaterialSpecFileName { get { return MaterialCompiler.MATERIAL_SPEC_FILE_NAME; } }
		public string RuntimePinsParents { get { return runtimePinsParents; } }
		public string BaseMaterialDbName { get { return baseMaterialDbName; } }
		public string ShadersCount { get { return shaders.Count.ToString(); } }

		public string[] RuntimePins { get { return runtimePins.ToArray(); } }
		public string[] IncludeMaterialDbHeaders { get { return includeMaterialDbHeaders.ToArray(); } }
		public string[] RuntimePinsDefaults { get { return runtimePinsDefaults.ToArray(); } }
		public string[] MaterialDeclarations { get { return materialDeclarations.ToArray(); } }
		public string[] ProjectsWithSpecs { get { return projectsWithSpecs.ToArray(); } }
		public string[] MaterialRegistrations { get { return materialRegistrations.ToArray(); } }
		public string[] ShadersRegistrations { get { return shadersRegistrations.ToArray(); } }
    public string[] MaterialsGroup { get { return materialsGroup.ToArray(); } }

    public string[] MaterialOffsetsDeclarations { get { return materialOffsetsDeclarations.ToArray(); } }
    public string[] MaterialOffsetsRegistrations { get { return materialOffsetsRegistrations.ToArray(); } }
  }
}
