using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using System.Web.Routing;
using System.Web.UI.MobileControls;
using ControlCenter.Areas.EventTool.Models;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Areas.GWEvents.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Controllers
{

  [Authorize]
  public class EventsController : Controller
  {
    protected EventsService Service { get; set; }
    protected IHistoryUIService HistorySvc { get; set; }

    protected override void Initialize(RequestContext requestContext)
    {
      if (Service == null)
        Service = new EventsService();

      if (HistorySvc == null)
          HistorySvc = new HistoryUIService();

      base.Initialize(requestContext);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult Index()
    {
      var model = Service.GetEvents();
      if (model == null)
        return View("Error", new HandleErrorInfo(new Exception("Can't get list of events from server"), "Events", "Index"));

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult Start(int id)
    {
      string error = Service.StartEvent(id);
      if (!String.IsNullOrEmpty(error))
        return View("Error", new HandleErrorInfo(new Exception("Error in starting event with id=" + id), "Events", "Start"));
      return RedirectToAction("Index");
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult Stop(int id)
    {
      string error = Service.StopEvent(id);
      if (!String.IsNullOrEmpty(error))
        return View("Error", new HandleErrorInfo(new Exception("Error in stopping event with id=" + id), "Events", "Stop"));
      return RedirectToAction("Index");
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult Delete(int id)
    {
      string error = Service.DeleteEvent(id);
      if (!String.IsNullOrEmpty(error))
        return View("Error", new HandleErrorInfo(new Exception("Error in deleting event with id=" + id), "Events", "Delete"));
      return RedirectToAction("Index");
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult HeroPrice(int? id)
    {
      HeroPriceModel model;
      if (id == null)
      {
        model = new HeroPriceModel
                {
                  DefaultPrices = Service.GetDefaultHeroPrices(),
                  StartTime = DateTime.Today.AddDays(1),
                  EndTime = DateTime.Today.AddDays(2)
                };
      }
      else
      {
        model = Service.GetHeroPriceById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "HeroPrice"));
      }
      
      ViewData["Heroes"] = HeroesCatalog.HeroesWithStaticData.OrderBy(h => h.HeroName)
        .Select(d => new { Id = d.HeroName, Name = d.HeroName });

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult HeroPrice(HeroPriceModel model)
    {
      if (model.NewPrices.Count == 0)
        ModelState.AddModelError("", "You should specify at least one hero price");

      if (!ModelState.IsValid)
      {
        ViewData["Heroes"] = HeroesCatalog.HeroesWithStaticData.OrderBy(h => h.HeroName)
          .Select(d => new { Id = d.HeroName, Name = d.HeroName });

        model.DefaultPrices = Service.GetDefaultHeroPrices();

        return View(model);
      }

      return Process(Service.EditHeroPriceEvent, model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult SkinPrice(int? id)
    {
      SkinPriceModel model;
      if (id == null)
      {
        model = new SkinPriceModel
                {
                  DefaultPrices = Service.GetDefaultSkinPrices(),
                  StartTime = DateTime.Today.AddDays(1),
                  EndTime = DateTime.Today.AddDays(2)
                };
      }
      else
      {
        model = Service.GetSkinPriceById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "SkinPrice"));
      }

      ViewData["Heroes"] = HeroesCatalog.HeroesWithStaticData.OrderBy(h => h.HeroName)
        .Select(d => new { Id = d.HeroClassId, Name = d.HeroName });

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult SkinPrice(SkinPriceModel model)
    {
      if (model.NewPrices.Count == 0)
        ModelState.AddModelError("", "You should specify at least one skin price");

      if (!ModelState.IsValid)
      {
        ViewData["Heroes"] = HeroesCatalog.HeroesWithStaticData.OrderBy(h => h.HeroName)
          .Select(d => new { Id = d.HeroClassId, Name = d.HeroName });

        model.DefaultPrices = Service.GetDefaultSkinPrices();

        return View(model);
      }

      return Process(Service.EditSkinPriceEvent, model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult Custom(int? id)
    {
      CustomEventModel model;
      if (id == null)
      {
        model = new CustomEventModel
                {
                  StartTime = DateTime.Today.AddDays(1),
                  EndTime = DateTime.Today.AddDays(2)
                };
      }
      else
      {
        model = Service.GetCustomEventById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "Custom"));
      }

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult Custom(CustomEventModel model)
    {
      if (!ModelState.IsValid)
        return View(model);

      return Process(Service.EditCustomEvent, model);
    }


    public ActionResult Techs(int? id)
    {
      TechsModel model;
      if (id == null)
      {
        model = new TechsModel
                {
                  StartTime = DateTime.Today.AddDays(1),
                  EndTime = DateTime.Today.AddDays(2)
                };
      }
      else
      {
        model = Service.GetTechsById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "Techs"));
      }

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult Techs(TechsModel model)
    {
      if (!ModelState.IsValid)
        return View(model);

      return Process(Service.EditTechsEvent, model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult CustomMap(int? id)
    {
      CustomMapModel model;
      if (id == null)
      {
        model = new CustomMapModel
        {
          StartTime = DateTime.Today.AddDays(1),
          EndTime = DateTime.Today.AddDays(2)
        };
      }
      else
      {
        model = Service.GetCustomMapById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "CustomMap"));
      }

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult CustomMap(CustomMapModel model)
    {
      if (!ModelState.IsValid)
        return View(model);

      return Process(Service.EditCustomMapEvent, model);
    }


    public ActionResult TalentDrop(int? id)
    {
      TalentDropRarityModel model;

      if (id == null)
      {
        var defaults = Service.GetDefaultTalentDropRarities();
        if (defaults == null)
          return View("Error", new HandleErrorInfo(new Exception("Can't get default rarities from server"), "Events", "TalentDrop"));

        model = new TalentDropRarityModel
                {
                  StartTime = DateTime.Today.AddDays(1),
                  EndTime = DateTime.Today.AddDays(2),
                  OrdinaryDefault = defaults[false],
                  PremiumDefault = defaults[true]
                };
      }
      else
      {
        model = Service.GetTalentDropRarityById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "TalentDrop"));
      }

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult TalentDrop(TalentDropRarityModel model)
    {
      if (!ModelState.IsValid)
        return View(model);

      return Process(Service.EditTalentDropRarityEvent, model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult NewsBanner(int? id)
    {
      NewsBannerModel model;
      if (id == null)
      {
        model = new NewsBannerModel
        {
          StartTime = DateTime.Today.AddDays(1),
          EndTime = DateTime.Today.AddDays(2)
        };
      }
      else
      {
        model = Service.GetNewsBannerById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "NewsBanner"));
        //model.Deserialize("{\"data\":[{\"Key\":\"InteractionText\",\"Value\":\"test InteractionText\"},{\"Key\":\"InteractionUI\",\"Value\":\"W_HeroTalentsPanel\"},{\"Key\":\"InteractionUIParam\",\"Value\":\"freeze\"}],\"type\":\"Interface\"}");
      }

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult NewsBanner(NewsBannerModel model)
    {
      if (!ModelState.IsValid)
        return View(model);

      model.UpdateExtensionJSON();
      return Process(Service.EditNewsBanner, model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult Transmutation(int? id)
    {
      TransmutationEventModel model;

      if (id == null)
      {
        int? talents = Service.GetDefaultTransmutation();
        if (talents == null)
          return View("Error", new HandleErrorInfo(new Exception("Can't get default talents for perl from server"), "Events", "Transmutation"));

        model = new TransmutationEventModel
                {
                  StartTime = DateTime.Today.AddDays(1),
                  EndTime = DateTime.Today.AddDays(2),
                  Talents = talents.Value,
                  TalentsDefault = talents.Value
                };
      }
      else
      {
        model = Service.GetTransmutationEventById(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "Transmutation"));
      }

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult Transmutation(TransmutationEventModel model)
    {
      if (!ModelState.IsValid)
        return View(model);

      return Process(Service.EditTransmutationEvent, model);
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollSlots( int? id )
    {
      RerollShopSlotsModel model;

      if ( id == null )
      {
        RerollSlotsModel defaultSlots = Service.GetDefaultRerollSlots();
        if ( defaultSlots == null )
          return View( "Error", new HandleErrorInfo( new Exception( "Can't get default reroll slots info from server" ), "Events", "RerollSlots" ) );

          
        model = new RerollShopSlotsModel
        {
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 ),
          RerollSlots = defaultSlots,
          DefaultRerollSlots = defaultSlots
        };
      }
      else
      {
        model = Service.GetRerollShopSlotsById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollSlots" ) );
      }

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollSlots( RerollShopSlotsModel model )
    {
      if ( !ModelState.IsValid )
        return View( model );

      if (model.RerollSlots.UsualSlots + model.RerollSlots.PremiumSlots != 10)
        return View( "Error", new HandleErrorInfo( new Exception( "Sum of usual and premium slots must be 10!"), "Events", "RerollSlots" ) );

      return Process( Service.EditRerollShopSlotsEvent, model );
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    public ActionResult ReforgeTalents(int? id)
    {
        ReforgeTalentsEventModel model;

        if (id == null)
        {
            ReforgeTalentsEventModel defaultPrice = Service.GetDefaultReforgeTalents();
            if (defaultPrice == null)
                return View("Error", new HandleErrorInfo(new Exception("Can't get default reforge talents info from server"), "Events", "ReforgeTalents"));

            model = new ReforgeTalentsEventModel
            {
                StartTime = DateTime.Today.AddDays(1),
                EndTime = DateTime.Today.AddDays(2),
                DefaultListReforgeTalentPrices = defaultPrice.DefaultListReforgeTalentPrices
            };
        }
        else
        {
            model = Service.GetDefaultReforgeTalentsById(id.Value);
            if (model == null)
                return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "ReforgeTalents"));
        }

        return View(model);
    }


    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost]
    public ActionResult ReforgeTalents(ReforgeTalentsEventModel model)
    {
        if (!ModelState.IsValid)
            return View(model);
        
        model.ReInitRarity();
        return Process(Service.EditReforgeTalentsEvent, model);
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollPrice( int? id )
    {
      RerollShopPriceModel model;

      if ( id == null )
      {
        ResourcesTableSmallModel defaultPrice = Service.GetDefaultRerollPrice();
        if ( defaultPrice == null )
          return View( "Error", new HandleErrorInfo( new Exception( "Can't get default reroll slots info from server" ), "Events", "RerollPrice" ) );

        model = new RerollShopPriceModel
        {
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 ),
          Price = defaultPrice,
          DefaultPrice = defaultPrice
        };
      }
      else
      {
        model = Service.GetRerollShopPriceById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollPrice" ) );
      }

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollPrice( RerollShopPriceModel model )
    {
      if ( !ModelState.IsValid )
        return View( model );

      return Process( Service.EditRerollShopPriceEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollGroupPrice( int? id )
    {
      RerollShopGroupPriceModel model;
      if ( id == null )
      {
        model = new RerollShopGroupPriceModel
        {
          DefaultPrices = Service.GetDefaultRerollShopGroupPrices(),
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 )
        };
      }
      else
      {
        model = Service.GetRerollShopGroupPriceById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollGroupPrice" ) );
      }

      ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollGroupPrice( RerollShopGroupPriceModel model )
    {
      if ( model.NewPrices.Count == 0 )
        ModelState.AddModelError( "", "You should specify at least one group price" );
      

      if ( !ModelState.IsValid )
      {
        model.DefaultPrices = Service.GetDefaultRerollShopGroupPrices();
        ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

        return View( model );
      }

      return Process( Service.EditRerollShopGroupPriceEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollGroupProbabilities( int? id )
    {
      RerollShopGroupProbabilityModel model;
      if ( id == null )
      {
        model = new RerollShopGroupProbabilityModel
        {
          DefaultPrices = Service.GetDefaultRerollShopGroupProbabilities(),
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 )
        };
      }
      else
      {
        model = Service.GetRerollShopGroupProbabilityById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollGroupProbabilities" ) );
      }

      ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollGroupProbabilities( RerollShopGroupProbabilityModel model )
    {
      if ( model.NewPrices.Count == 0 )
        ModelState.AddModelError( "", "You should specify at least one group probability" );


      if ( !ModelState.IsValid )
      {
        model.DefaultPrices = Service.GetDefaultRerollShopGroupProbabilities();
        ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

        return View( model );
      }

      return Process( Service.EditRerollShopGroupProbabilityEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollGroupCurrencies( int? id )
    {
      RerollShopGroupCurrenciesModel model;
      if ( id == null )
      {
        model = new RerollShopGroupCurrenciesModel
        {
          DefaultPrices = Service.GetDefaultRerollShopGroupCurrencies(),
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 )
        };
      }
      else
      {
        model = Service.GetRerollShopGroupCurrenciesById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollGroupCurrencies" ) );
      }

      ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollGroupCurrencies( RerollShopGroupCurrenciesModel model )
    {
      if ( model.NewPrices.Count == 0 )
        ModelState.AddModelError( "", "You should specify at least one group currency" );


      if ( !ModelState.IsValid )
      {
        model.DefaultPrices = Service.GetDefaultRerollShopGroupCurrencies();
        ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

        return View( model );
      }

      return Process( Service.EditRerollShopGroupCurrenciesEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollSlotPrice( int? id )
    {
      RerollShopSlotPriceModel model;
      if ( id == null )
      {
        model = new RerollShopSlotPriceModel
        {
          DefaultPrices = Service.GetDefaultRerollSlotPrices(),
          StartTime = DateTime.Today.AddDays( 1 ).ToLocalTime(),
          EndTime = DateTime.Today.AddDays(2).ToLocalTime()
        };
      }
      else
      {
        model = Service.GetRerollSlotPriceById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollSlotPrice" ) );
      }

      ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } ).Distinct();
      
      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollSlotPrice( RerollShopSlotPriceModel model )
    {
      if ( model.NewPrices.Count == 0 )
        ModelState.AddModelError( "", "You should specify at least one group price" );


      if ( !ModelState.IsValid )
      {
        model.DefaultPrices = Service.GetDefaultRerollSlotPrices();
        ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

        return View( model );
      }

      return Process( Service.EditRerollSlotPriceEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollSlotAmount( int? id )
    {
      RerollShopSlotAmountModel model;
      if ( id == null )
      {
        model = new RerollShopSlotAmountModel
        {
          DefaultPrices = Service.GetDefaultRerollSlotAmounts(),
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 )
        };
      }
      else
      {
        model = Service.GetRerollSlotAmountById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollSlotAmount" ) );
      }

      ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } ).Distinct();

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollSlotAmount( RerollShopSlotAmountModel model )
    {
      if ( model.NewPrices.Count == 0 )
        ModelState.AddModelError( "", "You should specify at least one group amount" );


      if ( !ModelState.IsValid )
      {
        model.DefaultPrices = Service.GetDefaultRerollSlotAmounts();
        ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

        return View( model );
      }

      return Process( Service.EditRerollSlotAmountEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult FirstBuyPrice( int? id )
    {
      FirstBuyPriceModel model;
      if ( id == null )
      {
        model = new FirstBuyPriceModel
        {
          DefaultPrices = Service.GetDefaultFirstBuyPrices(),
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 )
        };
      }
      else
      {
        model = Service.GetFirstBuyPriceById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "FirstBuyPrice" ) );
      }

      ViewData["Constructions"] = model.DefaultPrices.Select(d => new {Id = d.Construction, Name = d.Construction});

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult FirstBuyPrice( FirstBuyPriceModel model )
    {
      if ( model.NewPrices.Count == 0 )
        ModelState.AddModelError( "", "You should specify at least one construction price" );

      if ( !ModelState.IsValid )
      {        
        model.DefaultPrices = Service.GetDefaultFirstBuyPrices();
        ViewData["Constructions"] = model.DefaultPrices.Select( d => new { Id = d.Construction, Name = d.Construction } );

        return View( model );
      }

      return Process( Service.EditFirstBuyPriceEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollShopPremiumNotInactive( int? id )
    {
      RerollShopPremiumNotInactiveEventModel model;

      if ( id == null )
      {
        bool? isInactive = Service.GetDefaultRerollShopPremiumNotInactive();
        if ( isInactive == null )
          return View( "Error", new HandleErrorInfo( new Exception( "Can't get default premium slots is inactive from server" ), "Events", "RerollShopPremiumNotInactive" ) );

        model = new RerollShopPremiumNotInactiveEventModel
        {
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 ),
          IsInactive = isInactive.Value,
          IsInactiveDefault = isInactive.Value
        };
      }
      else
      {
        model = Service.GetRerollShopPremiumNotInactiveEventById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollShopPremiumNotInactive" ) );
      }

      return View( model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollGroupSlots( int? id )
    {
      RerollShopGroupSlotsModel model;
      if ( id == null )
      {
        model = new RerollShopGroupSlotsModel
        {
          DefaultPrices = Service.GetDefaultRerollShopGroupSlots(),
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 )
        };
      }
      else
      {
        model = Service.GetRerollShopGroupSlotsById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollGroupSlots" ) );
      }

      ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );
      var slots = new List<SelectListItem>();
      foreach (var group in model.DefaultPrices)
      {
        foreach (var slot in group.Slots.Split(','))
        {
          var listItem = new SelectListItem() {Text = slot, Value = slot};
          if(!slots.Contains(listItem)) slots.Add(listItem);
        }
      }
      model.Slots = new SelectList(slots);

      return View( model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollGroupSlots( RerollShopGroupSlotsModel model )
    {
      if ( model.NewPrices.Count == 0 )
        ModelState.AddModelError( "", "You should specify at least one group slot" );


      if ( !ModelState.IsValid )
      {
        model.DefaultPrices = Service.GetDefaultRerollShopGroupSlots();
        ViewData["Groups"] = model.DefaultPrices.Select( d => new { Id = d.Group, Name = d.Group } );

        return View( model );
      }

      return Process( Service.EditRerollShopGroupSlotsEvent, model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollShopPremiumNotInactive( RerollShopPremiumNotInactiveEventModel model )
    {
      if ( !ModelState.IsValid )
        return View( model );

      return Process( Service.EditRerollShopPremiumNotInactiveEvent, model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollShopBanner( int? id )
    {
      RerollShopBannerModel model;
      if ( id == null )
      {
        model = new RerollShopBannerModel
        {
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 ),
          SvcLocales = new SelectList( Service.GetBroadcastLocales() )
        };
      }
      else
      {
        model = Service.GetRerollShopBannerById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollShopBanner" ) );
      }

      return View( model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]
    [HttpPost]
    public ActionResult RerollShopBanner( RerollShopBannerModel model )
    {
      if ( !ModelState.IsValid )
        return View( model );

      return Process( Service.EditRerollShopBanner, model );
    }


    [AuthorizeWithPermission( Permission = "EventTool" )]
    public ActionResult RerollShopTooltip( int? id )
    {
      RerollShopTooltipModel model;
      if ( id == null )
      {
        model = new RerollShopTooltipModel
        {
          StartTime = DateTime.Today.AddDays( 1 ),
          EndTime = DateTime.Today.AddDays( 2 ),
          SvcLocales = new SelectList( Service.GetBroadcastLocales())
        };
      }
      else
      {
        model = Service.GetRerollShopTooltipById( id.Value );
        if ( model == null )
          return View( "Error", new HandleErrorInfo( new Exception( "No event with id = " + id ), "Events", "RerollShopTooltip" ) );
      }

      return View( model );
    }

    [AuthorizeWithPermission( Permission = "EventTool" )]    
    [HttpPost, ValidateInput( false )]
    public ActionResult RerollShopTooltip( RerollShopTooltipModel model )
    {
      if ( !ModelState.IsValid )
        return View( model );

      return Process( Service.EditRerollShopTooltip, model );
    }

    #region Roll Events

    private void RollEventModelFillSupportData(ref RollEventModel model)
    {
      model.AvailableLocales = new SelectList(Service.GetBroadcastLocales().ToArray());
      model.New = model.EventId == 0;
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpGet]
    public ActionResult RollEvent(int? id)
    {
      RollEventModel model;

      if (id == null)
      {
        model = new RollEventModel();
      }
      else
      {
        model = Service.GetRollEventModel(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "RollEvent"));
      }

      RollEventModelFillSupportData(ref model);

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost, ValidateInput(false)]
    public ActionResult RollEvent(RollEventModel model, string command)
    {
      RollEventModelFillSupportData(ref model);

      if (!string.IsNullOrEmpty(command))
      {
        ModelState.Clear();

        if (command.Equals("AddRoll"))
        {
          model.Rolls.Add(new RollEventRuleModel());
          return View(model);
        }
        if (command.Equals("Clone"))
        {
          model.EventId = 0;
          model.New = true;
          return View(model);
        }

        string[] commandArgs = command.Split('_');
        int rollIndex = commandArgs.Length > 1 ? Convert.ToInt32(commandArgs[1]) : 0;
        int itemIndex = commandArgs.Length > 2 ? Convert.ToInt32(commandArgs[2]) : 0;

        if (command.Contains("RemoveRoll_"))
        {
          model.Rolls.RemoveAt(rollIndex);
        }
        else if (command.Contains("AddReward_"))
        {
          model.Rolls[rollIndex].Rewards.Add(new RollEventItemModel(RollEventItemTypeEnum.Talent));
        }
        else if (command.Contains("RemoveReward_"))
        {
          model.Rolls[rollIndex].Rewards.RemoveAt(itemIndex);
        }
        else if (command.Contains("AddReforgeSource_"))
        {
          model.Rolls[rollIndex].ReforgeSource.Add(new RollEventItemModel(RollEventItemTypeEnum.Talent));
        }
        else if (command.Contains("RemoveReforgeSource_"))
        {
          model.Rolls[rollIndex].ReforgeSource.RemoveAt(itemIndex);
        }

        return View(model);
      }

      if (!ModelState.IsValid)
      {
        return View(model);
      }

      return Process(Service.EditRollEvent, model);
    }

    #endregion

    #region Quest Events

    private void QuestEventModelFillSupportData(ref QuestEventModel model)
    {
      model.AvailableLocales = new SelectList(Service.GetBroadcastLocales().ToArray());
      model.PrepareControlFields();
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpGet]
    public ActionResult QuestEvent(int? id)
    {
      QuestEventModel model;

      if (id == null)
      {
        model = new QuestEventModel();
      }
      else
      {
        model = Service.GetQuestEventModel(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "QuestEvent"));
      }

      QuestEventModelFillSupportData(ref model);

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost, ValidateInput(false)]
    public ActionResult QuestEvent(QuestEventModel model, string command)
    {
      QuestEventModelFillSupportData(ref model);

      if (!string.IsNullOrEmpty(command))
      {
        ModelState.Clear();

        string[] cmdArgs = command.Trim().Split(':');

        if (cmdArgs[0].Equals("clone"))
        {
          model.EventId = 0;
          model.New = true;
          return View(model);
        }

        if (cmdArgs[0].Equals("pass"))
        {
          return View(model);
        }

        if (model.ProcessCommand(cmdArgs, 0))
        {
          QuestEventModelFillSupportData(ref model);
          return View(model);
        }

        return View("Error", new HandleErrorInfo(new Exception("Wrong command"), "Events", command));
      }

      if (ModelState.IsValid)
        return Process(Service.EditQuestEvent, model);
      else
        return View(model);
    }

    #endregion

    #region TradeEvent

    private void TradeEventModelFillSupportData(ref TradeEventModel model)
    {
      model.AvailableLocales = new SelectList(Service.GetBroadcastLocales().ToArray());
      model.PrepareControlFields();
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpGet]
    public ActionResult TradeEvent(int? id)
    {
      TradeEventModel model;

      if (id == null)
      {
        model = new TradeEventModel();
      }
      else
      {
        model = Service.GetTradeEventModel(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "TradeEvent"));
      }

      TradeEventModelFillSupportData(ref model);

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost, ValidateInput(false)]
    public ActionResult TradeEvent(TradeEventModel model, string command)
    {
      TradeEventModelFillSupportData(ref model);

      if (!string.IsNullOrEmpty(command))
      {
        ModelState.Clear();

        string[] cmdArgs = command.Trim().Split(':');

        if (cmdArgs[0].Equals("clone"))
        {
          model.EventId = 0;
          model.New = true;
          return View(model);
        }

        if (cmdArgs[0].Equals("pass"))
        {
          return View(model);
        }

        if (model.ProcessCommand(cmdArgs, 0))
        {
          TradeEventModelFillSupportData(ref model);
          return View(model);
        }

        return View("Error", new HandleErrorInfo(new Exception("Wrong command"), "Events", command));
      }


      if (ModelState.IsValid)
        return Process(Service.EditTradeEvent, model);
      else
        return View(model);
    }


    #endregion


    #region SeasonEvent

    private void SeasonEventModelFillSupportData(ref SeasonEventModel model)
    {
        model.AvailableLocales = new SelectList(Service.GetBroadcastLocales().ToArray());
        model.PrepareControlFields();
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpGet]
    public ActionResult SeasonEvent(int? id)
    {
        SeasonEventModel model;

        if (id == null)
        {
            model = new SeasonEventModel();
        }
        else
        {
            model = Service.GetSeasonEventModel(id.Value);
            if (model == null)
                return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "SeasonEvent"));
        }

        SeasonEventModelFillSupportData(ref model);

        return View(model);
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost, ValidateInput(false)]
    public ActionResult SeasonEvent(SeasonEventModel model, string command)
    {
        SeasonEventModelFillSupportData(ref model);

        if (!string.IsNullOrEmpty(command))
        {
            ModelState.Clear();

            string[] cmdArgs = command.Trim().Split(':');

            if (cmdArgs[0].Equals("clone"))
            {
                model.EventId = 0;
                model.New = true;
                return View(model);
            }

            if (cmdArgs[0].Equals("pass"))
            {
                return View(model);
            }

            if (model.ProcessCommand(cmdArgs, 0))
            {
                SeasonEventModelFillSupportData(ref model);
                return View(model);
            }

            return View("Error", new HandleErrorInfo(new Exception("Wrong command"), "Events", command));
        }


        if (ModelState.IsValid)
            return Process(Service.EditSeasonEvent, model);
        else
            return View(model);
    }


    #endregion


    #region Donate Event

    private void DonateEventModelFillSupportData(ref DonateEventModel model)
    {
      //model.AvailableLocales = new SelectList(Service.GetBroadcastLocales().ToArray());
      model.PrepareControlFields();
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpGet]
    public ActionResult DonateEvent(int? id)
    {
      DonateEventModel model;

      if (id == null)
      {
        model = new DonateEventModel();
      }
      else
      {
        model = Service.GetDonateEventModel(id.Value);
        if (model == null)
          return View("Error", new HandleErrorInfo(new Exception("No event with id = " + id), "Events", "DonateEvent"));
      }

      DonateEventModelFillSupportData(ref model);

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost, ValidateInput(false)]
    public ActionResult DonateEvent(DonateEventModel model, string command)
    {
      DonateEventModelFillSupportData(ref model);

      if (!string.IsNullOrEmpty(command))
      {
        ModelState.Clear();

        string[] cmdArgs = command.Trim().Split(':');

        if (cmdArgs[0].Equals("clone"))
        {
          model.Id = 0;
          model.New = true;
          return View(model);
        }

        if (cmdArgs[0].Equals("pass"))
        {
          return View(model);
        }

        if (model.ProcessCommand(cmdArgs, 0))
        {
          DonateEventModelFillSupportData(ref model);
          return View(model);
        }

        return View("Error", new HandleErrorInfo(new Exception("Wrong command"), "Events", command));
      }

      if (!ModelState.IsValid)
      {
        return View(model);
      }

      return Process(Service.EditDonateEvent, model);
    }
    
    #endregion


    //
    // GET: /EventTool/GWEvents/
    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpGet]
    public ActionResult GWEvent()
    {
        try
        {
            var model = Service.GetGwEventsModel();
            if (model == null)
                return View("Error", new HandleErrorInfo(new Exception("Returned model is null"), "Events", ControllerContext.RouteData.Values["action"].ToString()));
            return View(model);
        }
        catch (Exception e)
        {
            return View("Error", new HandleErrorInfo(e, "Events", ControllerContext.RouteData.Values["action"].ToString()));
        }
        
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost, ValidateInput(false)]
    public ActionResult GWEvent(GWEventsModel model)
    {
        var lastEvent = model.GwEvents.Last();
        if (Math.Abs(lastEvent.PointsToAdd) > lastEvent.PointsToAddLimit)
        {
            ModelState.AddModelError("PointsToAdd", string.Format("PointsToAdd it should be between {0} and {1}.", -lastEvent.PointsToAddLimit, lastEvent.PointsToAddLimit));
            return View(model);
        }

        if (!ModelState.IsValid)
            return View(model);


        return Process(Service.EditGwEvent, lastEvent, User.Identity.Name);
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpGet]
    public ActionResult GWEventHistory(int eventIdx, int? page, DateTime? startTime, DateTime? endTime)
    {
      var model = new GWEventHistory();
      model.EventIdx = eventIdx;
      if (page.HasValue) model.Page = page.Value;
      var StartTime = DateTime.MinValue;
      var EndTime = DateTime.MinValue;
      if (startTime.HasValue && endTime.HasValue)
      {
        StartTime = startTime.Value;
        EndTime = endTime.Value;
      }
      else
      {
        StartTime = DateTime.UtcNow.AddDays(-14);
        EndTime = DateTime.UtcNow.AddDays(1);
      }

      model.StartTime = StartTime;
      model.EndTime = EndTime;

      HistorySvc.GetGwEventHistoryByEvent(model, eventIdx, StartTime, EndTime);
      return View(model);
    }

    [AuthorizeWithPermission(Permission = "EventTool")]
    [HttpPost, ValidateInput(false)]
    public ActionResult GWEventHistory(GWEventHistory model)
    {
      return RedirectToAction("GWEventHistory", new { eventIdx = model.EventIdx, startTime = model.StartTime, endTime = model.EndTime });
    }

    /// <summary>
    /// Хелпер для обработки типовых методов
    /// </summary>
    private ActionResult Process<T>(Func<T, string, string> serviceFunc, T model, string login)
    {
        string error = serviceFunc(model, login);

        if (!String.IsNullOrEmpty(error))
            return View("Error", new HandleErrorInfo(new Exception("Can't edit GuildWar event: " + error), "Events", ControllerContext.RouteData.Values["action"].ToString()));

        return RedirectToAction("GWEvent");
    }

    /// <summary>
    /// Хелпер для обработки типовых методов
    /// </summary>
    private ActionResult Process<T>(Func<T, string> serviceFunc, T model)
    {
      string error = serviceFunc(model);

      if (!String.IsNullOrEmpty(error))
        return View("Error", new HandleErrorInfo(new Exception("Can't edit event: " + error), "Events", ControllerContext.RouteData.Values["action"].ToString()));

      return RedirectToAction("Index");
    }

  }

}