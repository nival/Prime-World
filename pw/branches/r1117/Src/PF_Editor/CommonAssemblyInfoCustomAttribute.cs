using System;

namespace PF_Editor
{


[AttributeUsage(AttributeTargets.Assembly, Inherited = false)]
public sealed class AssemblyFileVersionCustomAttribute : Attribute
{
    private string major;
    private string minor;
    private string buildNumber;
    private string revision;

    public string Major { get { return major; } }
    public string Minor { get { return minor; } }
    public string BuildNumber { get { return buildNumber; } }
    public string Revision { get { return revision; } }

    public AssemblyFileVersionCustomAttribute() : this(string.Empty) { }
    public AssemblyFileVersionCustomAttribute(string versionString)
    {
        major = "0";
        minor = "0";
        buildNumber = "0";
        revision = "0";

        string[] versionAttributes = versionString.Split('.');
        if (versionAttributes.Length < 4)
        {
            throw new ArgumentException("Required 4 group of digits which split by dots", versionString);
        }
        major = versionAttributes[0];
        minor = versionAttributes[1];
        buildNumber = versionAttributes[2];
        revision = versionAttributes[3];
    }

    public string Version
    {
        get
        {
        return String.Format("{0}.{1}.{2}.{3}", major, minor, buildNumber, revision);
        }
    }
}

}