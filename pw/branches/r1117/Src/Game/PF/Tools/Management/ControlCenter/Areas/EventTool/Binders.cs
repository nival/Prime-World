using System;
using System.Web.Mvc;
using ControlCenter.Areas.EventTool.Models;
using log4net;

namespace ControlCenter.Areas.EventTool
{
  /*

    Как это работает:
    
    В данном биндере мы пытаемся заполнить модель, у которой внутри есть коллекция
      List<TList> NewPrices
    данными из POST формы, которые приходят в виде
      somefield_1 : 123123
      otherfield_1 : "азазаза"
      somefield_2 : 321321312
      otherfield_2 : "ащащаща"
    где somefield и otherfield - это названия полей в типе TList,
    а 1 и 2 - это индексы, означающие что поля с таким суффиксом должны попасть в один объект.
    Индексы могут быть неупорядоченными, главное чтобы они совпадали для всех полей одного объекта.

  */

  public class NewPricesModelBinder<T, TList> : DefaultModelBinder 
    where T : INewPricesListModel<TList>
    where TList : new()
  {
    private static readonly ILog _log = LogManager.GetLogger(typeof(NewPricesModelBinder<T, TList>));

    public override object BindModel(ControllerContext controllerContext, ModelBindingContext bindingContext)
    {
      if (bindingContext.ModelType != typeof(T))
      {
        _log.ErrorFormat("Incorrect using of NewPricesModelBinder: expected type {0}, but got {1}", typeof(T), bindingContext.ModelType);
        return base.BindModel(controllerContext, bindingContext);
      }

      T model = (T) base.BindModel(controllerContext, bindingContext);

      var form = controllerContext.HttpContext.Request.Form;
      string indexes = form["index"];

      // Находим в модели все возможные индексы
      if (!String.IsNullOrEmpty(indexes))
      {
        foreach (var idx in indexes.Split(','))
        {
          // Создаем объект для каждого индекса.
          var listobj = new TList();

          // Ищем в форме все поля которые имеют суффикс "_циферкаиндекса" и заполняем ими свежесозданный объект.
          foreach (string key in form.Keys)
          {
            if (key.EndsWith("_" + idx))
            {
              try
              {
                string propName = key.Replace("_" + idx, "");
                var prop = typeof(TList).GetProperty(propName);
                if (prop == null)
                  continue;

                object value;
                if (prop.PropertyType == typeof(int))
                  value = Int32.Parse(form[key]);
                else if ( prop.PropertyType == typeof( double ) )
                  value = Double.Parse( form[key] );
                else
                  value = form[key];

                prop.SetValue(listobj, value, null);
              }
              catch (Exception ex)
              {
                _log.ErrorFormat("Can't bind key '{0}' to {1}. {2}", key, typeof(TList), ex);
              }
            }
          }

          // Кладем объект в коллекцию NewPrices.
          model.NewPrices.Add(listobj);
        }
      }

      return model;
    }
  }


}