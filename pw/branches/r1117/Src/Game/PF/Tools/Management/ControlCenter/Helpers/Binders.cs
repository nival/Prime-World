using System;
using System.Globalization;
using System.Web.Mvc;

namespace ControlCenter.Helpers
{
  public class CustomDateTimeBinder : IModelBinder
  {
    public object BindModel(ControllerContext controllerContext, ModelBindingContext bindingContext)
    {
      ValueProviderResult vpr = bindingContext.ValueProvider.GetValue(bindingContext.ModelName);
      if (vpr == null || String.IsNullOrEmpty(vpr.AttemptedValue))
        return null;
      try
      {
        return vpr.ConvertTo(typeof (DateTime), CultureInfo.GetCultureInfo("ru-RU"));
      }
      catch (Exception ex)
      {
        bindingContext.ModelState.AddModelError(bindingContext.ModelName, ex);
        bindingContext.ModelState.SetModelValue(bindingContext.ModelName, vpr);
        return null;
      }
    }
  }
}