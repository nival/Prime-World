
namespace DBCodeGen.SocialClientGeneration
{
  class NameMapItemInsterter
  {
    public const string NameMapInterfaceImplementation = @"
    private NameMapReflector _namemap_generated_variable = null;

    public virtual object GetValue( string name, params INameMap[] context )
    {
      if ( _namemap_generated_variable == null )
        _namemap_generated_variable = new NameMapReflector( this );

      return _namemap_generated_variable.GetValue( name, context );
    }";
  }
}
