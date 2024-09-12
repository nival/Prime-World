using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Globalization;
using System.Web.Security;

namespace ControlCenter.Areas.Admin.Models
{
  #region Models
  [PropertiesMustMatch("NewPassword", "ConfirmPassword", ErrorMessage = "The new password and confirmation password do not match.")]
  public class ChangePasswordModel
  {
    [Required]
    [DataType(DataType.Password)]
    [DisplayName("Current password")]
    public string OldPassword { get; set; }

    [Required]
    [DataType(DataType.Password)]
    [DisplayName("New password")]
    public string NewPassword { get; set; }

    [Required]
    [DataType(DataType.Password)]
    [DisplayName("Confirm new password")]
    public string ConfirmPassword { get; set; }
  }

  public class LogOnModel
  {
    [Required]
    [DisplayName("User name")]
    public string UserName { get; set; }

    [Required]
    [DataType(DataType.Password)]
    [DisplayName("Password")]
    public string Password { get; set; }

    [DisplayName("Remember me?")]
    public bool RememberMe { get; set; }
  }

  public class ProfileModel
  {
    [DisplayName("User name")]
    public string UserName { get; set; }

  }
  #endregion

  public struct CustomUserData
  {
    public bool superuser;
    public string[] roles;
    public string[] permissions;
    public string[] locales;
    public string[] muids;

    /// <summary>
    /// Tiny serialization to store result in cookie.
    /// </summary>
    /// <returns></returns>
    public string Serialize()
    {
      return String.Format("{0}&{1}&{2}&{3}&{4}", superuser, String.Join("|", roles), String.Join("|", permissions), String.Join("|", locales), String.Join("|", muids));
    }

    /// <summary>
    /// Deserialization of cookie value.
    /// </summary>
    public static CustomUserData Deserialize(string text)
    {
      try
      {
        string[] userdata = text.Split('&');
        return new CustomUserData
                 {
                   superuser = Boolean.Parse(userdata[0]),
                   roles = userdata[1].Split('|'),
                   permissions = userdata[2].Split('|'),
                   locales = String.IsNullOrEmpty(userdata[3]) ? new string[0] : userdata[3].Split('|'),
                   muids = String.IsNullOrEmpty(userdata[4]) ? new string[0] : userdata[4].Split('|')
                 };
      }
      catch (Exception)
      {
        return new CustomUserData
                 {
                   superuser = false,
                   roles = new string[0],
                   permissions = new string[0],
                   locales = new string[0],
                   muids = new string[0]
                 };
      }
    }
  }

  #region Validation

  [AttributeUsage(AttributeTargets.Class, AllowMultiple = true, Inherited = true)]
  public sealed class PropertiesMustMatchAttribute : ValidationAttribute
  {
    private const string _defaultErrorMessage = "'{0}' and '{1}' do not match.";
    private readonly object _typeId = new object();

    public PropertiesMustMatchAttribute(string originalProperty, string confirmProperty)
      : base(_defaultErrorMessage)
    {
      OriginalProperty = originalProperty;
      ConfirmProperty = confirmProperty;
    }

    public string ConfirmProperty { get; private set; }
    public string OriginalProperty { get; private set; }

    public override object TypeId
    {
      get
      {
        return _typeId;
      }
    }

    public override string FormatErrorMessage(string name)
    {
      return String.Format(CultureInfo.CurrentUICulture, ErrorMessageString,
          OriginalProperty, ConfirmProperty);
    }

    public override bool IsValid(object value)
    {
      PropertyDescriptorCollection properties = TypeDescriptor.GetProperties(value);
      object originalValue = properties.Find(OriginalProperty, true /* ignoreCase */).GetValue(value);
      object confirmValue = properties.Find(ConfirmProperty, true /* ignoreCase */).GetValue(value);
      return Object.Equals(originalValue, confirmValue);
    }
  }

  [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property, AllowMultiple = false, Inherited = true)]
  public sealed class ValidatePasswordLengthAttribute : ValidationAttribute
  {
    private const string _defaultErrorMessage = "'{0}' must be at least {1} characters long.";
    private readonly int _minCharacters = Membership.Provider.MinRequiredPasswordLength;

    public ValidatePasswordLengthAttribute()
      : base(_defaultErrorMessage)
    {
    }

    public override string FormatErrorMessage(string name)
    {
      return String.Format(CultureInfo.CurrentUICulture, ErrorMessageString,
          name, _minCharacters);
    }

    public override bool IsValid(object value)
    {
      string valueAsString = value as string;
      return (valueAsString != null && valueAsString.Length >= _minCharacters);
    }
  }
  #endregion

}
