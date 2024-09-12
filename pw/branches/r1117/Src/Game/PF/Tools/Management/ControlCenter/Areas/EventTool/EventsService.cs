using System;
using System.Collections.Generic;
using System.Linq;
using AccountLib;
using ControlCenter.Areas.EventTool.Models;
using ControlCenter.Areas.GWEvents.Models;
using ControlCenter.Helpers;
using GWEventModel = ControlCenter.Areas.GWEvents.Models.GWEventModel;
using GWEventsModel = ControlCenter.Areas.GWEvents.Models.GWEventsModel;
using TradeEventModel = ControlCenter.Areas.EventTool.Models.TradeEventModel;
using SeasonEventModel = ControlCenter.Areas.EventTool.Models.SeasonEventModel;

namespace ControlCenter.Areas.EventTool
{

  public class EventsService
  {

    private static Uri gmaccountingAddress;
    public static string GmAccountingAddress
    {
      set
      {
        if (!Uri.TryCreate(value, UriKind.Absolute, out gmaccountingAddress))
          throw new ArgumentException("Invalid value for gmaccountingAddress = " + (value ?? "(null)"));
      }
    }


    private readonly IEventManagementService eventManagementService;

    public EventsService()
    {
      if (gmaccountingAddress == null)
        throw new InvalidOperationException("gmaccountingAddress is null");

      eventManagementService = new EventManagementService(gmaccountingAddress);
    }


    public IEnumerable<EventShortInfo> GetEvents()
    {
      var response = eventManagementService.GetAvailableEvents();
      return response != null && response.Result == RequestResult.Success
        ? response.AvailableEvents.Select(e => new EventShortInfo(e)).OrderByDescending(e => e.Id)
        : null;
    }


    private string ToStringResult(RequestResult result)
    {
      return result == RequestResult.Success ? null : result.ToString();
    }

    public List<string> GetBroadcastLocales()
    {
      var resp = eventManagementService.GetBroadcastLocales();
      if ( resp != null )
      {
        if ( resp.Result != RequestResult.Success || resp.Locales.Count == 0 )
          throw new Exception( "Failed to get broadcast locales list from server" );

        return resp.Locales;
      }
      return null;
    }


    public string StartEvent(int id)
    {
      return ToStringResult(eventManagementService.ChangeEventStateById(id, true));
    }


    public string StopEvent(int id)
    {
      return ToStringResult(eventManagementService.ChangeEventStateById(id, false));
    }


    public string DeleteEvent(int id)
    {
      return ToStringResult(eventManagementService.DeleteEventById(id));
    }


    public List<SkinPriceInfoModel> GetDefaultSkinPrices()
    {
      var response = eventManagementService.GetSkinPrices();
      if (response != null && response.Result == RequestResult.Success)
      {
        return response.DefaultPrices.Select(p => new SkinPriceInfoModel(p)).ToList();
      }
      return null;
    }


    public SkinPriceModel GetSkinPriceById(int id)
    {
      var response = eventManagementService.GetSkinPriceById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      var result = new SkinPriceModel(response.SkinEvent);
      result.DefaultPrices.AddRange(response.DefaultPrices.Select(p => new SkinPriceInfoModel(p)));

      return result;
    }


    public string EditSkinPriceEvent(SkinPriceModel model)
    {
      var evt = new SkinGoldPriceEvent
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  Enabled = model.Enabled,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Skins = model.NewPrices.Select(p => new SkinGoldPrice
                                                      {
                                                        HeroClassId = p.Hero,
                                                        PersistentId = p.Skin,
                                                        Price = p.Price
                                                      }).ToList()
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddSkinPricesEvent(evt)
        : eventManagementService.EditSkinPricesEvent(evt);

      return ToStringResult(res);
    }


    public List<HeroPriceInfoModel> GetDefaultHeroPrices()
    {
      var response = eventManagementService.GetHeroPrices();
      if (response != null && response.Result == RequestResult.Success)
      {
        return response.DefaultPrices.Select(p => new HeroPriceInfoModel(p)).ToList();
      }

      return null;
    }


    public HeroPriceModel GetHeroPriceById(int id)
    {
      var response = eventManagementService.GetHeroPriceById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      var result = new HeroPriceModel(response.HeroEvent);
      result.DefaultPrices.AddRange(response.DefaultPrices.Select(p => new HeroPriceInfoModel(p)));

      return result;
    }


    public string EditHeroPriceEvent(HeroPriceModel model)
    {
      var evt = new HeroPriceEvent
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  Enabled = model.Enabled,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Heroes = model.NewPrices.Select(p => new HeroPrice
                                                       {
                                                         PersistentId = p.Hero,
                                                         GoldPrice = p.GoldPrice,
                                                         SilverPrice = p.SilverPrice
                                                       }).ToList()
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddHeroPricesEvent(evt)
        : eventManagementService.EditHeroPricesEvent(evt);

      return ToStringResult(res);
    }


    public CustomEventModel GetCustomEventById(int id)
    {
      var response = eventManagementService.GetCustomEventById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new CustomEventModel(response.CustomEvent);
    }


    public string EditCustomEvent(CustomEventModel model)
    {
      var evt = new CustomEvent
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  Enabled = model.Enabled,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Type = model.Type
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddCustomEvent(evt)
        : eventManagementService.EditCustomEvent(evt);

      return ToStringResult(res);
    }


    public TechsModel GetTechsById(int id)
    {
      var response = eventManagementService.GetTechsInfoById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new TechsModel(response.TechInfo);
    }


    public string EditTechsEvent(TechsModel model)
    {
      var evt = new TechsInfo
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Type = model.Type,
                  Time = model.Time
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddTechs(evt)
        : eventManagementService.EditTechs(evt);

      return ToStringResult(res);
    }


    public CustomMapModel GetCustomMapById(int id)
    {
      var response = eventManagementService.GetCustomMapById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new CustomMapModel(response.CustomMap);
    }


    public string EditCustomMapEvent(CustomMapModel model)
    {
      var evt = new CustomMap
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Enabled = model.Enabled,
                  Day = model.Day,
                  StartHour = model.StartHour,
                  EndHour = model.EndHour,
                  MapDbid = model.MapDbid,
                  MapType = model.MapType,
                  MapEnabled = model.MapEnabled
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddCustomMap(evt)
        : eventManagementService.EditCustomMap(evt);

      return ToStringResult(res);
    }


    public Dictionary<bool, TalentDropRarityInfoModel> GetDefaultTalentDropRarities()
    {
      var response = eventManagementService.GetTalentDropRarities();
      if (response != null && response.Result == RequestResult.Success)
      {
        return new Dictionary<bool, TalentDropRarityInfoModel>
               {
                 { false, new TalentDropRarityInfoModel(response.OrdinaryDefault) },
                 { true, new TalentDropRarityInfoModel(response.PremiumDefault) }
               };
      }
      return null;
    }


    public TalentDropRarityModel GetTalentDropRarityById(int id)
    {
      var response = eventManagementService.GetTalentDropRarityById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new TalentDropRarityModel(response.TalentDropEvent)
             {
               OrdinaryDefault = new TalentDropRarityInfoModel(response.OrdinaryDefault),
               PremiumDefault = new TalentDropRarityInfoModel(response.PremiumDefault)
             };
    }


    public string EditTalentDropRarityEvent(TalentDropRarityModel model)
    {
      var evt = new TalentDropRarityEvent
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Enabled = model.Enabled,
                  Premium = model.Premium,
                  DropRarity = new TalentDropRarity
                               {
                                 Good = model.GoodRarity,
                                 Excellent = model.ExcellentRarity,
                                 Magnificent = model.MagnificentRarity,
                                 Exclusive = model.ExclusiveRarity
                               }
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddTalentDropRarities(evt)
        : eventManagementService.EditTalentDropRarities(evt);

      return ToStringResult(res);
    }


    public NewsBannerModel GetNewsBannerById(int id)
    {
      var response = eventManagementService.GetNewsBannerById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new NewsBannerModel(response.NewsBanner);
    }


    public string EditNewsBanner(NewsBannerModel model)
    {
      var evt = new NewsBanner
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Enabled = model.Enabled,
                  ButtonText = model.ButtonText,
                  WindowCaption = model.WindowCaption,
                  ButtonUrl = model.ButtonUrl,
                  MainUrl = model.MainUrl,
                  Tooltip = model.Tooltip,
                  MainUrlB = model.MainUrlB,
                  LoginNetworks = model.LoginNetworks,
                  MinLordLevel = model.MinLordLevel,
                  HideIfViewed = model.HideIfViewed,
                  Locale = model.Locale,
                  ExtensionJson = model.ExtensionJson
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddNewsBanner(evt)
        : eventManagementService.EditNewsBanner(evt);

      return ToStringResult(res);
    }


    public int? GetDefaultTransmutation()
    {
      var response = eventManagementService.GetTransmutationTalentsPerPerl();
      if (response != null && response.Result == RequestResult.Success)
      {
        return response.TalentsDefault;
      }
      return null;
    }


    public TransmutationEventModel GetTransmutationEventById(int id)
    {
      var response = eventManagementService.GetTransmutationTalentsPerPerlById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new TransmutationEventModel(response.TalentsPerPerl)
             {
               TalentsDefault = response.TalentsDefault
             };
    }


    public string EditTransmutationEvent(TransmutationEventModel model)
    {
      var evt = new TransmutationTalentsPerPerl
                {
                  PersistentId = model.Id,
                  Description = model.Description,
                  StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
                  Enabled = model.Enabled,
                  Talents = model.Talents
                };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddTalentPerPerlEvent(evt)
        : eventManagementService.EditTalentPerPerlEvent(evt);

      return ToStringResult(res);
    }

    public ReforgeTalentsEventModel GetDefaultReforgeTalents()
    {
        var response = eventManagementService.GetReforgeTalentPrice();
        if (response != null && response.Result == RequestResult.Success)
        {
    
            List<ReforgeTalentPriceModel>  defaultList = new List<ReforgeTalentPriceModel>();
            defaultList.AddRange(response.DefaultReforgeTalentPrices.ListReforgeTalentPrices.Select(p => new ReforgeTalentPriceModel(p)));
            return new ReforgeTalentsEventModel()
            {
                DefaultListReforgeTalentPrices = defaultList
            };
        }
        return null;
    }

    public RerollSlotsModel GetDefaultRerollSlots()
    {
      var response = eventManagementService.GetRerollShopSlots();
      if ( response != null && response.Result == RequestResult.Success )
      {


        return new RerollSlotsModel()
               {
                 MaxActivePremiumSlots = response.DefaultMaxActivePremiumSlots,
                 MaxActiveUsualSlots = response.DefaultMaxActiveUsualSlots,
                 PremiumSlots = response.DefaultPremiumSlots,
                 UsualSlots = response.DefaultUsualSlots
               };
      }
      return null;
    }

    public ReforgeTalentsEventModel GetDefaultReforgeTalentsById(int id)
    {
        var response = eventManagementService.GetReforgeTalentPriceById(id);

        if (response == null || response.Result != RequestResult.Success)
            return null;

        List<ReforgeTalentPriceModel>  defaultList = new List<ReforgeTalentPriceModel>();
        defaultList.AddRange(response.DefaultReforgeTalentPrices.ListReforgeTalentPrices.Select(p => new ReforgeTalentPriceModel(p)));

        return new ReforgeTalentsEventModel(response.ReforgeTalentPrices)
        {
            DefaultListReforgeTalentPrices = defaultList
        };

    }


    public string EditReforgeTalentsEvent(ReforgeTalentsEventModel model)
    {
        var evt = new ReforgeTalentPrices()
        {
            PersistentId = model.Id,
            Description = model.Description,
            StartTime = model.StartTime.AddHours(-model.TimeZone).ToUnixTimestamp(),
            EndTime = model.EndTime.AddHours(-model.TimeZone).ToUnixTimestamp(),
            Enabled = model.Enabled
        };
        evt.ListReforgeTalentPrices = new List<ReforgeTalentPrice>();
        evt.ListReforgeTalentPrices.AddRange(model.ListReforgeTalentPrices.Select(p => new ReforgeTalentPrice
        {
            Rarity = p.Rarity,
            RerollPrice = p.RerollPrice,
            UpgradePrice = p.UpgradePrice,
            TalentsToUpgrade = p.TalentsToUpgrade            
        }));
        
        RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddReforgeTalentPriceEvent(evt)
        : eventManagementService.EditReforgeTalentPriceEvent(evt);

      return ToStringResult(res);
    }

    public RerollShopSlotsModel GetRerollShopSlotsById( int id )
    {
      var response = eventManagementService.GetRerollShopSlotsById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      return new RerollShopSlotsModel( response.RerollShopSlots )
      {
        DefaultRerollSlots = new RerollSlotsModel()
               {
                 MaxActivePremiumSlots = response.DefaultMaxActivePremiumSlots,
                 MaxActiveUsualSlots = response.DefaultMaxActiveUsualSlots,
                 PremiumSlots = response.DefaultPremiumSlots,
                 UsualSlots = response.DefaultUsualSlots
               }
      };
    }


    public string EditRerollShopSlotsEvent( RerollShopSlotsModel model )
    {
      var evt = new RerollShopSlots()
      {
        PersistentId = model.Id,
        Description = model.Description,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Enabled = model.Enabled,
        UsualSlots = model.RerollSlots.UsualSlots,
        PremiumSlots = model.RerollSlots.PremiumSlots,
        MaxActiveUsualSlots = model.RerollSlots.MaxActiveUsualSlots,
        MaxActivePremiumSlots = model.RerollSlots.MaxActivePremiumSlots,
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopSlotsEvent( evt )
        : eventManagementService.EditRerollShopSlotsEvent( evt );

      return ToStringResult( res );
    }

    public ResourcesTableSmallModel GetDefaultRerollPrice()
    {
      var response = eventManagementService.GetRerollShopPrices();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return new ResourcesTableSmallModel()
        {
          Resource1 = response.DefaultRerollShopPrice.Resource1,
          Resource2 = response.DefaultRerollShopPrice.Resource2,
          Resource3 = response.DefaultRerollShopPrice.Resource3,
          Silver = response.DefaultRerollShopPrice.Silver,
          Gold = response.DefaultRerollShopPrice.Gold,
          Perl = response.DefaultRerollShopPrice.Perl,
          RedPerl = response.DefaultRerollShopPrice.RedPerl,          
        };
      }
      return null;
    }


    public RerollShopPriceModel GetRerollShopPriceById( int id )
    {
      var response = eventManagementService.GetRerollShopPriceById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      return new RerollShopPriceModel( response.RerollShopPrice )
      {
        DefaultPrice = new ResourcesTableSmallModel()
        {
          Resource1 = response.DefaultRerollShopPrice.Resource1,
          Resource2 = response.DefaultRerollShopPrice.Resource2,
          Resource3 = response.DefaultRerollShopPrice.Resource3,
          Silver = response.DefaultRerollShopPrice.Silver,
          Gold = response.DefaultRerollShopPrice.Gold,
          Perl = response.DefaultRerollShopPrice.Perl,
          RedPerl = response.DefaultRerollShopPrice.RedPerl,          
        }        
      };
    }


    public string EditRerollShopPriceEvent( RerollShopPriceModel model )
    {
      var evt = new RerollShopPrice()
      {
        PersistentId = model.Id,
        Description = model.Description,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Enabled = model.Enabled,
        Price = new ResourceTableSmall()
                {
                  Resource1 = model.Price.Resource1,
                  Resource2 = model.Price.Resource2,
                  Resource3 = model.Price.Resource3,
                  Silver = model.Price.Silver,
                  Gold = model.Price.Gold,
                  Perl = model.Price.Perl,
                  RedPerl = model.Price.RedPerl,
                }
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopPriceEvent( evt )
        : eventManagementService.EditRerollShopPriceEvent( evt );

      return ToStringResult( res );
    }

    public List<RerollShopGroupPriceInfoModel> GetDefaultRerollShopGroupPrices()
    {
      var response = eventManagementService.GetRerollShopGroupPrices();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.DefaultPrices.Select( p => new RerollShopGroupPriceInfoModel( p ) ).ToList();
      }

      return null;
    }


    public RerollShopGroupPriceModel GetRerollShopGroupPriceById( int id )
    {
      var response = eventManagementService.GetRerollShopGroupPriceById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      var result = new RerollShopGroupPriceModel( response.GroupEvent );
      result.DefaultPrices.AddRange( response.DefaultPrices.Select( p => new RerollShopGroupPriceInfoModel( p ) ) );

      return result;
    }


    public string EditRerollShopGroupPriceEvent( RerollShopGroupPriceModel model )
    {
      var evt = new RerollShopGroupPriceEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        Enabled = model.Enabled,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Groups = model.NewPrices.Select( p => new RerollShopGroupPrice
        {
          PersistentId = p.Group,
          MinPrice = p.MinPrice,
          MaxPrice = p.MaxPrice
        } ).ToList()
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopGroupPriceEvent( evt )
        : eventManagementService.EditRerollShopGroupPriceEvent( evt );

      return ToStringResult( res );
    }

    public List<RerollShopGroupCurrenciesInfoModel> GetDefaultRerollShopGroupCurrencies()
    {
      var response = eventManagementService.GetRerollShopGroupCurrencies();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.DefaultCurrencies.Select( p => new RerollShopGroupCurrenciesInfoModel( p ) ).ToList();
      }

      return null;
    }


    public RerollShopGroupCurrenciesModel GetRerollShopGroupCurrenciesById( int id )
    {
      var response = eventManagementService.GetRerollShopGroupCurrenciesById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      var result = new RerollShopGroupCurrenciesModel( response.GroupEvent );
      result.DefaultPrices.AddRange( response.DefaultCurrencies.Select( p => new RerollShopGroupCurrenciesInfoModel( p ) ) );

      return result;
    }


    public string EditRerollShopGroupCurrenciesEvent( RerollShopGroupCurrenciesModel model )
    {
      var evt = new RerollShopGroupCurrenciesEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        Enabled = model.Enabled,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Groups = model.NewPrices.Select( p => new RerollShopGroupCurrencies
        {
          PersistentId = p.Group,
          Currencies = p.GetIntCurrencies()          
        } ).ToList()
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopGroupCurrenciesEvent( evt )
        : eventManagementService.EditRerollShopGroupCurrenciesEvent( evt );

      return ToStringResult( res );
    }

    public List<RerollShopGroupProbabilityInfoModel> GetDefaultRerollShopGroupProbabilities()
    {
      var response = eventManagementService.GetRerollShopGroupProbabilities();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.DefaultProbability.Select( p => new RerollShopGroupProbabilityInfoModel( p ) ).ToList();
      }

      return null;
    }


    public RerollShopGroupProbabilityModel GetRerollShopGroupProbabilityById( int id )
    {
      var response = eventManagementService.GetRerollShopGroupProbabilityById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      var result = new RerollShopGroupProbabilityModel( response.GroupEvent );
      result.DefaultPrices.AddRange( response.DefaultProbability.Select( p => new RerollShopGroupProbabilityInfoModel( p ) ) );

      return result;
    }


    public string EditRerollShopGroupProbabilityEvent( RerollShopGroupProbabilityModel model )
    {
      var evt = new RerollShopGroupProbabilityEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        Enabled = model.Enabled,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Groups = model.NewPrices.Select( p => new RerollShopGroupProbability
        {
          PersistentId = p.Group,
          RerollTime = p.RerollTime,
          Probability = p.Probability,
          MinUpgradeLevel = p.MinUpgradeLevel,
          MaxUpgradeLevel = p.MaxUpgradeLevel
        } ).ToList()
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopGroupProbabilityEvent( evt )
        : eventManagementService.EditRerollShopGroupProbabilityEvent( evt );

      return ToStringResult( res );
    }

    public List<RerollSlotPriceInfoModel> GetDefaultRerollSlotPrices()
    {
      var response = eventManagementService.GetRerollShopSlotPrices();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.DefaultPrices.Select( p => new RerollSlotPriceInfoModel( p ) ).ToList();
      }

      return null;
    }


    public RerollShopSlotPriceModel GetRerollSlotPriceById( int id )
    {
      var response = eventManagementService.GetRerollShopSlotPriceById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      var result = new RerollShopSlotPriceModel( response.SlotEvent );
      result.DefaultPrices.AddRange( response.DefaultPrices.Select( p => new RerollSlotPriceInfoModel( p ) ) );

      return result;
    }


    public string EditRerollSlotPriceEvent( RerollShopSlotPriceModel model )
    {
      var evt = new RerollShopSlotPriceEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        Enabled = model.Enabled,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Slots = model.NewPrices.Select( p => new RerollShopSlotPrice
        {
          PersistentId = p.Slot,
          GroupId = p.Group,
          MinPrice = p.MinPrice,
          MaxPrice = p.MaxPrice
        } ).ToList()
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopSlotPricesEvent( evt )
        : eventManagementService.EditRerollShopSlotPricesEvent( evt );

      return ToStringResult( res );
    }

    public List<RerollSlotAmountInfoModel> GetDefaultRerollSlotAmounts()
    {
      var response = eventManagementService.GetRerollShopSlotAmounts();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.DefaultAmounts.Select( p => new RerollSlotAmountInfoModel( p ) ).ToList();
      }

      return null;
    }


    public RerollShopSlotAmountModel GetRerollSlotAmountById( int id )
    {
      var response = eventManagementService.GetRerollShopSlotAmountById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      var result = new RerollShopSlotAmountModel( response.SlotEvent );
      result.DefaultPrices.AddRange( response.DefaultAmounts.Select( p => new RerollSlotAmountInfoModel( p ) ) );

      return result;
    }


    public string EditRerollSlotAmountEvent( RerollShopSlotAmountModel model )
    {
      var evt = new RerollShopSlotAmountEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        Enabled = model.Enabled,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Slots = model.NewPrices.Select( p => new RerollShopSlotAmount
        {
          PersistentId = p.Slot,
          GroupId = p.Group,
          Amount = p.Amount
        } ).ToList()
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopSlotAmountsEvent( evt )
        : eventManagementService.EditRerollShopSlotAmountsEvent( evt );

      return ToStringResult( res );
    }

    public List<FirstBuyPriceInfoModel> GetDefaultFirstBuyPrices()
    {
      var response = eventManagementService.GetFirstBuyPrices();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.DefaultPrices.Select( p => new FirstBuyPriceInfoModel( p ) ).ToList();
      }
      return null;
    }


    public FirstBuyPriceModel GetFirstBuyPriceById( int id )
    {
      var response = eventManagementService.GetFirstBuyPriceById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      var result = new FirstBuyPriceModel( response.FirstBuyEvent );
      result.DefaultPrices.AddRange( response.DefaultPrices.Select( p => new FirstBuyPriceInfoModel( p ) ) );

      return result;
    }


    public string EditFirstBuyPriceEvent( FirstBuyPriceModel model )
    {
      var evt = new FirstBuyGoldPriceEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        Enabled = model.Enabled,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        FirstBuys = model.NewPrices.Select( p => new FirstBuyGoldPrice
        {          
          PersistentId = p.Construction,
          Price = p.GoldPrice
        } ).ToList()
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddFirstBuyPricesEvent( evt )
        : eventManagementService.EditFirstBuyPricesEvent( evt );

      return ToStringResult( res );
    }

    public bool? GetDefaultRerollShopPremiumNotInactive()
    {
      var response = eventManagementService.GetRerollShopPremiumNotInactive();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.RerollShopPremiumNotInactiveDefault;
      }
      return null;
    }

    public RerollShopPremiumNotInactiveEventModel GetRerollShopPremiumNotInactiveEventById( int id )
    {
      var response = eventManagementService.GetRerollShopPremiumNotInactiveById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      return new RerollShopPremiumNotInactiveEventModel( response.RerollShopPremiumNotInactive )
      {
        IsInactiveDefault = response.RerollShopPremiumNotInactiveDefault
      };
    }


    public string EditRerollShopPremiumNotInactiveEvent( RerollShopPremiumNotInactiveEventModel model )
    {
      var evt = new RerollShopPremiumNotInactiveEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Enabled = model.Enabled,
        IsInactive = model.IsInactive
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopPremiumNotInactiveEvent( evt )
        : eventManagementService.EditRerollShopPremiumNotInactiveEvent( evt );

      return ToStringResult( res );
    }

    public List<RerollShopGroupSlotsInfoModel> GetDefaultRerollShopGroupSlots()
    {
      var response = eventManagementService.GetRerollShopGroupSlots();
      if ( response != null && response.Result == RequestResult.Success )
      {
        return response.DefaultSlots.Select( p => new RerollShopGroupSlotsInfoModel( p ) ).ToList();
      }

      return null;
    }


    public RerollShopGroupSlotsModel GetRerollShopGroupSlotsById( int id )
    {
      var response = eventManagementService.GetRerollShopGroupSlotsById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      var result = new RerollShopGroupSlotsModel( response.SlotEvent );
      result.DefaultPrices.AddRange( response.DefaultSlots.Select( p => new RerollShopGroupSlotsInfoModel( p ) ) );

      return result;
    }


    public string EditRerollShopGroupSlotsEvent( RerollShopGroupSlotsModel model )
    {
      var evt = new RerollShopGroupSlotsEvent
      {
        PersistentId = model.Id,
        Description = model.Description,
        Enabled = model.Enabled,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Groups = model.NewPrices.Select( p => new RerollShopGroupSlots
        {
          GroupId = p.Group,
          PersistentIds = new List<string>(p.Slots.Split(','))
        } ).ToList()
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopGroupSlotsEvent( evt )
        : eventManagementService.EditRerollShopGroupSlotsEvent( evt );

      return ToStringResult( res );
    }

    public RerollShopBannerModel GetRerollShopBannerById( int id )
    {
      var response = eventManagementService.GetRerollShopBannerById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      return new RerollShopBannerModel( response.RerollShopBanner );
    }


    public string EditRerollShopBanner( RerollShopBannerModel model )
    {
      var evt = new RerollShopBanner
      {
        PersistentId = model.Id,
        Description = model.Description,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Enabled = model.Enabled,
        MainUrl = model.MainUrl,
        Locale = model.Locale
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopBanner( evt )
        : eventManagementService.EditRerollShopBanner( evt );

      return ToStringResult( res );
    }

    public RerollShopTooltipModel GetRerollShopTooltipById( int id )
    {
      var response = eventManagementService.GetRerollShopTooltipById( id );

      if ( response == null || response.Result != RequestResult.Success )
        return null;

      return new RerollShopTooltipModel( response.RerollShopTooltip );
    }


    public string EditRerollShopTooltip( RerollShopTooltipModel model )
    {
      var evt = new RerollShopTooltip
      {
        PersistentId = model.Id,
        Description = model.Description,
        StartTime = model.StartTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        EndTime = model.EndTime.AddHours( -model.TimeZone ).ToUnixTimestamp(),
        Enabled = model.Enabled,
        Tooltip = model.Tooltip,
        Locale = model.Locale
      };

      RequestResult res = evt.PersistentId == 0
        ? eventManagementService.AddRerollShopTooltip( evt )
        : eventManagementService.EditRerollShopTooltip( evt );

      return ToStringResult( res );
    }

    public RollEventModel GetRollEventModel(int id)
    {
      var response = eventManagementService.GetRollEventById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new RollEventModel(response.RollEvent);
    }

    public string EditRollEvent(RollEventModel model)
    {
      var rollEvent = model.ToRollEvent();
      RequestResult result = rollEvent.PersistentId == 0
        ? eventManagementService.AddRollEvent(rollEvent)
        : eventManagementService.EditRollEvent(rollEvent);
      return ToStringResult(result);
    }

    public QuestEventModel GetQuestEventModel(int id)
    {
      var response = eventManagementService.GetQuestEventById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return  new QuestEventModel(response.QuestEvent);
    }

    public string EditQuestEvent(QuestEventModel model)
    {
      QuestEvent questEvent = model.ToQuestEvent();
      RequestResult result = questEvent.PersistentId == 0
        ? eventManagementService.AddQuestEvent(questEvent)
        : eventManagementService.EditQuestEvent(questEvent);
      return ToStringResult(result);
    }

    public GWEventsModel GetGwEventsModel()
    {
        var response = eventManagementService.GetGWEvents();

        if (response == null || response.Result != RequestResult.Success)
            return null;

        return new GWEventsModel(response.GwEvents);
    }

    public string EditGwEvent(GWEventModel model, string gmLogin)
    {
        var tGwEvent = model.toTGWEventModel();
        RequestResult result = eventManagementService.EditGWEvent(tGwEvent, gmLogin);
        return ToStringResult(result);
    }

    public TradeEventModel GetTradeEventModel(int id)
    {
      var response = eventManagementService.GetTradeEventById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new TradeEventModel(response.TradeEvent);
    }

    public string EditTradeEvent(TradeEventModel model)
    {
      var tradeEvent = model.ToTType();
      RequestResult result = tradeEvent.PersistentId == 0
        ? eventManagementService.AddTradeEvent(tradeEvent)
        : eventManagementService.EditTradeEvent(tradeEvent);
      return ToStringResult(result);
    }

    public SeasonEventModel GetSeasonEventModel(int id)
    {
        var response = eventManagementService.GetSeasonEventById(id);

        if (response == null || response.Result != RequestResult.Success)
            return null;

        return new SeasonEventModel(response.SeasonEvent);
    }

    public string EditSeasonEvent(SeasonEventModel model)
    {
        var seasonEvent = model.ToTType();
        RequestResult result = seasonEvent.PersistentId == 0
            ? eventManagementService.AddSeasonEvent(seasonEvent)
            : eventManagementService.EditSeasonEvent(seasonEvent);
        return ToStringResult(result);
    }

    public DonateEventModel GetDonateEventModel(int id)
    {
      var response = eventManagementService.GetDonateEventById(id);

      if (response == null || response.Result != RequestResult.Success)
        return null;

      return new DonateEventModel(response.DonateEvent);
    }

    public string EditDonateEvent(DonateEventModel model)
    {
      var eventInfo = model.ToTType();
      RequestResult result = eventInfo.PersistentId == 0
          ? eventManagementService.AddDonateEvent(eventInfo)
          : eventManagementService.EditDonateEvent(eventInfo);
      return ToStringResult(result);
    }
  }

}