using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using libdb.DB;

namespace DBCodeGen.SocialClientCodeGeneration
{
  internal static class AdaptiveItemsInserter
  {

    private static string _stringNullCheck =
      @"bool firstIsEmpty = string.IsNullOrEmpty( _{0} );
        bool secondIsEmpty = string.IsNullOrEmpty( _{1} );";

    private static string _objectNullCheck =
      @"bool firstIsEmpty = (_{0} == null);
        bool secondIsEmpty = (_{1} == null);";

    private static string _listNullCheck =
      @"bool firstIsEmpty = (_{0}.Count == 0);
        bool secondIsEmpty = (_{1}.Count == 0);";

    private static string _fieldsSubstitutionCheck = @"
        if( !firstIsEmpty && secondIsEmpty )
          return _{0};

        if ( firstIsEmpty && !secondIsEmpty )
          return _{1};";


    private static string _genderAdaptivePattern = @"public {0} {1} 
{{ 
  get
    {{ 
{2}
      if(_currentGender == PlayerGender.Male) 
        return _{1}" + GenderPostfixA + @"; 
      if(_currentGender == PlayerGender.Female) 
        return _{1}" + GenderPostfixB + @";
      return _{1}" + GenderPostfixA + @";
    }}
}}";

    private static string _fractionAdaptivePattern = @"public {0} {1} 
{{ 
  get
    {{ 
{2}
     if(_currentFraction == PlayerFraction.A) 
      return _{1}" + RacePostfixA + @";
     if(_currentFraction == PlayerFraction.B) 
      return _{1}" + RacePostfixB + @"; 
     return _{1}" + RacePostfixA + @";
    }} 
}}";

    private const string GenderPostfixA = "Male";
    private const string GenderPostfixB = "Female";

    private const string RacePostfixA = "A";
    private const string RacePostfixB = "B";

    public const string AdaptMethodText = @"private PlayerGender _currentGender; 
private PlayerFraction _currentFraction; 
public void Adapt(PlayerFraction fraction, PlayerGender gender)
{ 
  _currentGender = gender; 
  _currentFraction = fraction;
}";
    //public static string TestGeneration()
    //{
    //  string result = String.Empty;
    //  result += String.Format(_genderAdaptivePattern, "string", "TestGender");
    //  result += String.Format(_raceAdaptivePattern, "string", "TestRace");
    //  return result;
    //}

    private static string GenerateEmptyDataSubstitutionCode( Type fieldType, string firstName, string secondName )
    {
      string nullCheck = string.Empty;
      if ( typeof( string ).IsAssignableFrom( fieldType ) || typeof( TextRef ).IsAssignableFrom( fieldType )
        //DBPtr to Texture object after code generation converts to string
        //So adaptaion must be proceed for a string type
        || (typeof( DBPtrBase ).IsAssignableFrom( fieldType )
          && TypesReplacement.TryToReplace( DBCodeGen.GetCSSimpleTypeName(fieldType) ) == "string" ) )

        nullCheck = string.Format( _stringNullCheck, firstName, secondName );
      else
        if ( typeof( DBPtrBase ).IsAssignableFrom( fieldType ) )
          nullCheck = string.Format( _objectNullCheck, firstName, secondName );
        else
          if ( typeof( IList ).IsAssignableFrom( fieldType ) )
            nullCheck = string.Format( _listNullCheck, firstName, secondName );

      if ( !string.IsNullOrEmpty( nullCheck ) )
      {
        return string.Format( @"{0} 
{1}", nullCheck, string.Format( _fieldsSubstitutionCheck, firstName, secondName ) );
      }
      return string.Empty;
    }
    public static bool CollectAdaptiveAccessors( List<FieldInfo> fields, ref string result )
    {
      result = string.Empty;
      List<string> fieldsNames = new List<string>();
      foreach ( FieldInfo field in fields )
      {
        fieldsNames.Add( field.Name );
      }
      foreach ( FieldInfo field in fields )
      {
        if ( field.Name.EndsWith( GenderPostfixA ) && field.Name.Length != GenderPostfixA.Length )
        {
          string shortName = field.Name.Substring( 0, field.Name.Length - GenderPostfixA.Length );
          if ( fieldsNames.Contains( shortName + GenderPostfixB ) )
            result += string.Format( _genderAdaptivePattern,
                                     TypesReplacement.TryToReplace( DBCodeGen.GetCSSimpleTypeName( field.FieldType ) ),
                                     shortName, GenerateEmptyDataSubstitutionCode( field.FieldType, shortName + GenderPostfixA, shortName + GenderPostfixB ) );
          continue;

        }
        if ( field.Name.EndsWith( RacePostfixA ) && field.Name.Length != RacePostfixA.Length )
        {
          string shortName = field.Name.Substring( 0, field.Name.Length - RacePostfixA.Length );
          if ( fieldsNames.Contains( shortName + RacePostfixB ) )
            result += string.Format( _fractionAdaptivePattern,
              TypesReplacement.TryToReplace( DBCodeGen.GetCSSimpleTypeName( field.FieldType ) ),
              shortName, GenerateEmptyDataSubstitutionCode( field.FieldType, shortName + RacePostfixA, shortName + RacePostfixB ) );
          continue;
        }
      }
      if ( !String.IsNullOrEmpty( result ) )
        return true;
      return false;
    }
  }
}
