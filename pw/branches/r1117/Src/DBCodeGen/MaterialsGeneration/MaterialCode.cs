using System;
using System.Collections.Generic;
using System.Reflection;
using DBCodeGen.VisualStudioSupport;
using libdb.Animated;
using libdb.DB;

namespace DBCodeGen.MaterialsGeneration
{
  public class MaterialCode
  {
    private readonly List<string> materialFields = new List<string>();
    private readonly List<string> fillMaterialParameters = new List<string>();
    private readonly List<string> baseMaterialFunctions = new List<string>();
    private readonly List<string> materialInclude = new List<string>();
    private readonly List<string> bindStates = new List<string>();
    private readonly List<string> bindSamplers = new List<string>();

    private readonly List<string> animatedFields = new List<string>();
    private readonly List<string> isAnimatedFunc = new List<string>();
    private readonly List<string> updateFunc = new List<string>();
    private readonly List<string> setStartTimeFunc = new List<string>();
    private readonly List<string> getAnimLengthFunc = new List<string>();

    private readonly List<string> groupName = new List<string>();
    private readonly List<string> checkTypesSizes = new List<string>();

    private readonly List<KeyValuePair<string, string>>[] prioritizedMaterialFields = new List<KeyValuePair<string, string>>[3];

    private readonly List<string> initSamplersOffsets = new List<string>();

    private static string GetFullTypeName( Type type )
    {
      string result = DBCodeGen.GetFullTypeName( type );
      if ( TypeUtils.IsSubclassOf( type, typeof( IAnimated ) ) )
        result = "NDb::" + result;

      return result;
    }

    private void AddMaterialField( int priority, string type, string field )
    {
      prioritizedMaterialFields[priority].Add( new KeyValuePair<string, string>( type, field ) );
    }

    public MaterialCode( string baseMaterialDbName, Type materialType, IEnumerable<MaterialPinDefenition> pins, string groupName, FunctionsCollection functions, int shaderIndex, Project finalProject, Project materialProject )
    {
      BaseMaterialDbName = baseMaterialDbName;
      MaterialName = DBCodeGen.GetTypeName( materialType );
      ShaderIndex = shaderIndex.ToString();

      for ( int i = 0; i < prioritizedMaterialFields.Length; ++i )
        prioritizedMaterialFields[i] = new List<KeyValuePair<string, string>>();

      FieldInfo[] fields = DBCodeGen.GetFields( materialType, false, string.Empty, null );
      foreach ( FieldInfo field in fields )
      {
        if ( TypeUtils.HasAttribute<NoCodeAttribute>( field, false ) )
          continue;

        bool nonSignificant = TypeUtils.HasAttribute<NonSignificantFieldAttribute>( field, false );
        SamplerAttribute sampler = TypeUtils.GetAttribute<SamplerAttribute>( field, false );
        if ( sampler != null )
        {
          // render sampler
          AddMaterialField( nonSignificant ? 2 : 0, MaterialCompiler.SAMPLER_CLASS_NAME, field.Name );
          fillMaterialParameters.Add(string.Format("FillSampler( pDbMaterial->{0}, &{0}, {1}, texturePoolId );", field.Name, sampler.CanBeVisualDegrade.ToString().ToLower()));
          bindSamplers.Add( string.Format( "Render::BindSampler( {0}, {1} );", sampler.SamplerIndex, field.Name ) );
          
          initSamplersOffsets.Add( string.Format( "samplersOffsets[{0}] = offsetof( {1}, {2} );",
            initSamplersOffsets.Count, MaterialName, field.Name ) );
        }
        else
        {
          fillMaterialParameters.Add( string.Format( "{0} = pDbMaterial->{0};", field.Name ) );

          if ( TypeUtils.IsSubclassOf( field.FieldType, typeof( IAnimated ) ) )
          {
            IAnimated animated = TypeUtils.CreateInstance( field.FieldType ) as IAnimated;
            if ( animated == null )
              // animated constant with non-trivial type
              AddMaterialField( nonSignificant ? 2 : 1, string.Format( "NDb::{0}::TAnimatedType", DBCodeGen.GetFullTypeName( field.FieldType ) ), field.Name );
            else
              // animated constant with trivial type
              AddMaterialField( nonSignificant ? 2 : 1, DBCodeGen.GetFullTypeName( animated.ValueType ), field.Name );

            // animated wrapper
            AddMaterialField( 2, string.Format( "NDb::AnimatedWrapper<NDb::{0} >", DBCodeGen.GetFullTypeName( field.FieldType ) ), string.Format( "{0}Wrapper;", field.Name ) );
            fillMaterialParameters.Add( string.Format( "{0}Wrapper.Init( &{0}, pDbMaterial->{0}, 0.0f );", field.Name ) );

            animatedFields.Add( field.Name );
          }
          else if ( TypeUtils.HasAttribute<StateTypeAttribute>( field.FieldType, true ) )
          {
            // Replace state name
            string stateName = DBCodeGen.GetFullTypeName( field.FieldType );
            if ( stateName == MaterialCompiler.RENDERSTATE_NDB_CLASS_NAME )
              stateName = MaterialCompiler.RENDERSTATE_CLASS_NAME;

            // render state
            AddMaterialField( nonSignificant ? 2 : 0, stateName, field.Name );
            bindStates.Add( string.Format( "Render::SetRenderState( {0} );", field.Name ) );
          }
          else if ( TypeUtils.HasAttribute<Pin2Attribute>( field.FieldType, true ) || TypeUtils.HasAttribute<Pin2Attribute>( field, true ) || TypeUtils.IsSubclassOf( field.FieldType, typeof( DBPtrBase ) ) )
            AddMaterialField( 2, DBCodeGen.GetFullTypeName( field.FieldType ), field.Name );
          else
            AddMaterialField( nonSignificant ? 2 : 1, DBCodeGen.GetFullTypeName( field.FieldType ), field.Name );
        }
      }

      foreach ( var priorityFields in prioritizedMaterialFields )
      {
        foreach ( var field in priorityFields )
        {
          materialFields.Add( field.Key + " " + field.Value + ";" );
        }
      }

      List<string> significantFields = new List<string>();
      foreach ( var field in prioritizedMaterialFields[0] )
      {
        significantFields.Add( field.Value );
      }
      foreach ( var field in prioritizedMaterialFields[1] )
      {
        significantFields.Add( field.Value );
      }
      for ( int i = 0; i < significantFields.Count - 1; ++i )
      {
        checkTypesSizes.Add(string.Format("NI_STATIC_ASSERT( offsetof( {0}, {1} ) + sizeof( {1} ) == offsetof( {0}, {2} ), Found_gap_after_significant_field_{1} );", MaterialName, significantFields[i], significantFields[i + 1]));
      }


      if ( prioritizedMaterialFields[0].Count > 0 || prioritizedMaterialFields[1].Count > 0 )
      {
        string firstSignificantField = prioritizedMaterialFields[0].Count > 0 ? prioritizedMaterialFields[0][0].Value : prioritizedMaterialFields[1][0].Value;
        string lastSignificantField = prioritizedMaterialFields[1].Count > 0 ? prioritizedMaterialFields[1][prioritizedMaterialFields[1].Count - 1].Value : prioritizedMaterialFields[0][prioritizedMaterialFields[0].Count - 1].Value;
        SignificantPartLength = string.Format( "offsetof( {0}, {2} ) - offsetof( {0}, {1} ) + sizeof( {2} )", MaterialName, firstSignificantField, lastSignificantField );
      }

      FunctionsCollection thisFunctions = new FunctionsCollection();
      thisFunctions.FillFromMaterialType( materialType );

      if ( functions != null )
      {
        this.groupName.Add( groupName );
        foreach ( var function in functions.SortedFunctions )
        {
          if ( thisFunctions.HasFunction( function.Key ) )
          {
            string functionString = FunctionsCollection.Format( thisFunctions.GetFunction( function.Key ), FunctionFormat.Default );
            if ( !string.IsNullOrEmpty( functionString ) )
              baseMaterialFunctions.Add( functionString );
          }

        }
      }
      else
      {
        this.groupName.Add( "Render::Material" );
      }

      foreach ( MaterialFuncAttribute materialFunc in TypeUtils.GetAttributes<MaterialFuncAttribute>( materialType, false ) )
      {
        if ( !materialInclude.Exists( item => string.Compare( item, materialFunc.IncludeFileName, true ) == 0 ) )
        {
          if ( finalProject == materialProject || materialProject == null )
            materialInclude.Add( string.Format( "#include \"{0}\"", materialFunc.IncludeFileName ) );
          else
            materialInclude.Add( string.Format( "#include \"../{1}/{0}\"", materialFunc.IncludeFileName, materialProject.ProjectFileName ) );
        }
      }
			materialInclude.Sort();

      DynamicShaderIndexCalculation = "0";
      StaticShaderIndexCalculation = "0";

      foreach ( MaterialPinDefenition pin in pins )
      {
        if ( pin.PinRuntime )
        {
          if ( DynamicShaderIndexCalculation == "0" )
            DynamicShaderIndexCalculation = string.Format( "{0} * GetRuntimePins().{1}", pin.PinMultiplier, pin.PinName );
          else
            DynamicShaderIndexCalculation += string.Format( " + {0} * GetRuntimePins().{1}", pin.PinMultiplier, pin.PinName );
        }
        else
        {
          if ( StaticShaderIndexCalculation == "0" )
            StaticShaderIndexCalculation = string.Format( "{0} * {1}", pin.PinMultiplier, pin.PinName );
          else
            StaticShaderIndexCalculation += string.Format( " + {0} * {1}", pin.PinMultiplier, pin.PinName );
        }
      }

      if ( animatedFields.Count > 0 )
      {
        isAnimatedFunc.Add( "virtual bool IsAnimated() const" );
        isAnimatedFunc.Add( "{" );
        updateFunc.Add( "virtual void Update( float dt )" );
        updateFunc.Add( "{" );
        updateFunc.Add( string.Format( "\tif( !{0}::IsAnimated() )", MaterialName ) );
        updateFunc.Add("\t\treturn;");
        updateFunc.Add("\tMarkMaterialUpdated();");
        setStartTimeFunc.Add( "virtual void SetStartTime( float startTime )" );
        setStartTimeFunc.Add( "{" );

        getAnimLengthFunc.Add( "virtual float GetAnimLength() const" );
        getAnimLengthFunc.Add( "{" );
        getAnimLengthFunc.Add( "\tfloat length = 0.0f;" );

        for ( int i = 0; i < animatedFields.Count; ++i )
        {
          string line = animatedFields[i] + "Wrapper.IsAnimated()";
          if ( i == 0 )
            line = "\treturn " + line;
          else
            line = "\t\t|| " + line;
          if ( i == animatedFields.Count - 1 )
            line += ";";
          isAnimatedFunc.Add( line );

          getAnimLengthFunc.Add( "\tif ( " + animatedFields[i] + "Wrapper.IsAnimated() && " + animatedFields[i] + "Wrapper.GetLength() > length )" );
          getAnimLengthFunc.Add( "\t\tlength = " + animatedFields[i] + "Wrapper.GetLength();" );

          updateFunc.Add( string.Format( "\t{0}Wrapper.Step( dt );", animatedFields[i] ) );
          setStartTimeFunc.Add( string.Format( "\t{0}Wrapper.SetStartTime( startTime );", animatedFields[i] ) );
        }

        getAnimLengthFunc.Add( "\treturn length;" );
        getAnimLengthFunc.Add( "}" );
        getAnimLengthFunc.Add( string.Empty );
        isAnimatedFunc.Add( "}" );
        isAnimatedFunc.Add( string.Empty );
        updateFunc.Add( "}" );
        updateFunc.Add( string.Empty );
        setStartTimeFunc.Add( "}" );
        setStartTimeFunc.Add( string.Empty );

        //@Ivn@TODO: find max( animatedFields.Length );
      }
    }

    public readonly string BaseMaterialDbName = string.Empty;

    public readonly string MaterialName = string.Empty;
    public string BaseMaterialName { get { return MaterialCompiler.BASE_MATERIAL_INTERFACE_NAME; } }
    public string RenderMaterialName { get { return MaterialCompiler.RENDER_MATERIAL_CLASS_NAME; } }

    public readonly string DynamicShaderIndexCalculation = "0"; // { get { return dynamicShaderIndexCalculation; } }
    public readonly string StaticShaderIndexCalculation = "0"; // { get { return staticShaderIndexCalculation; } }

    public readonly string SignificantPartLength = "0";

    public string[] MaterialFields { get { return materialFields.ToArray(); } }
    public string[] FillMaterialParameters { get { return fillMaterialParameters.ToArray(); } }

    public string[] BaseMaterialFunctions { get { return baseMaterialFunctions.ToArray(); } }
    public string[] MaterialInclude { get { return materialInclude.ToArray(); } }

    public readonly string ShaderIndex = string.Empty;
    public string[] BindStates { get { return bindStates.ToArray(); } }
    public string[] BindSamplers { get { return bindSamplers.ToArray(); } }

    public string[] GetAnimLengthFunc { get { return getAnimLengthFunc.ToArray(); } }
    public string[] IsAnimatedFunc { get { return isAnimatedFunc.ToArray(); } }
    public string[] UpdateFunc { get { return updateFunc.ToArray(); } }
    public string[] SetStartTimeFunc { get { return setStartTimeFunc.ToArray(); } }
    public string[] GroupName { get { return groupName.ToArray(); } }

    public string[] CheckTypesSizes { get { return checkTypesSizes.ToArray(); } }

    public int SamplersCount { get { return initSamplersOffsets.Count; } }

    public string SetSamplersFunc 
    { 
      get
      {
        if( SamplersCount > 0 )
          return string.Format( "SetSamplers( samplersOffsets, {0} );", SamplersCount );

        return string.Empty;
      }
    }

    public string SamplersCountArray
    {
      get
      {
        if( SamplersCount > 0 )
          return string.Format( "static int samplersOffsets[{0}];", SamplersCount );

        return string.Empty;
      }
    }

    public string[] InitSamplersOffsets { get { return initSamplersOffsets.ToArray(); } }
  }
}
