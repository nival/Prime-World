using System;
using log4net;
using Thrift.Protocol;
using Thrift.Transport;

namespace AccountLib
{

  public interface IEventManagementService
  {
    BroadcastLocalesResponse GetBroadcastLocales();

    CommonEventsListResponse GetAvailableEvents();
    RequestResult ChangeEventStateById(int persistentId, bool state);
    RequestResult DeleteEventById(int persistentId);

    SkinGoldPricesResponse GetSkinPrices();
    SkinGoldPriceByIdResponse GetSkinPriceById(int id);
    RequestResult AddSkinPricesEvent(SkinGoldPriceEvent e);
    RequestResult EditSkinPricesEvent(SkinGoldPriceEvent e);

    HeroPricesResponse GetHeroPrices();
    HeroPriceByIdResponse GetHeroPriceById(int id);
    RequestResult AddHeroPricesEvent(HeroPriceEvent e);
    RequestResult EditHeroPricesEvent(HeroPriceEvent e);

    CustomEventByIdResponse GetCustomEventById(int id);
    RequestResult AddCustomEvent(CustomEvent e);
    RequestResult EditCustomEvent(CustomEvent e);

    TechsInfoByIdResponse GetTechsInfoById(int id);
    RequestResult AddTechs(TechsInfo e);
    RequestResult EditTechs(TechsInfo e);

    CustomMapByIdResponse GetCustomMapById(int id);
    RequestResult AddCustomMap(CustomMap e);
    RequestResult EditCustomMap(CustomMap e);

    TalentDropRaritiesResponse GetTalentDropRarities();
    TalentDropRarityByIdResponse GetTalentDropRarityById(int id);
    RequestResult AddTalentDropRarities(TalentDropRarityEvent e);
    RequestResult EditTalentDropRarities(TalentDropRarityEvent e);

    NewsBannerByIdResponse GetNewsBannerById(int id);
    RequestResult AddNewsBanner(NewsBanner e);
    RequestResult EditNewsBanner(NewsBanner e);

    TransmutationTalentsPerPerlResponse GetTransmutationTalentsPerPerl();
    TransmutationTalentsPerPerlByIdResponse GetTransmutationTalentsPerPerlById(int id);
    RequestResult AddTalentPerPerlEvent(TransmutationTalentsPerPerl e);
    RequestResult EditTalentPerPerlEvent(TransmutationTalentsPerPerl e);

    ReforgeTalentPriceResponse GetReforgeTalentPrice();
    ReforgeTalentPriceByIdResponse GetReforgeTalentPriceById(int id);
    RequestResult AddReforgeTalentPriceEvent(ReforgeTalentPrices e);
    RequestResult EditReforgeTalentPriceEvent(ReforgeTalentPrices e);

    RerollShopSlotsResponse GetRerollShopSlots();
    RerollShopSlotsByIdResponse GetRerollShopSlotsById( int id );
    RequestResult AddRerollShopSlotsEvent( RerollShopSlots e );
    RequestResult EditRerollShopSlotsEvent( RerollShopSlots e );

    RerollShopPricesResponse GetRerollShopPrices();
    RerollShopPriceByIdResponse GetRerollShopPriceById( int id );
    RequestResult AddRerollShopPriceEvent( RerollShopPrice e );
    RequestResult EditRerollShopPriceEvent( RerollShopPrice e );

    RerollShopGroupPricesResponse GetRerollShopGroupPrices();
    RerollShopGroupPriceByIdResponse GetRerollShopGroupPriceById( int id );
    RequestResult AddRerollShopGroupPriceEvent( RerollShopGroupPriceEvent e );
    RequestResult EditRerollShopGroupPriceEvent( RerollShopGroupPriceEvent e );

    RerollShopSlotPricesResponse GetRerollShopSlotPrices();
    RerollShopSlotPriceByIdResponse GetRerollShopSlotPriceById( int id );
    RequestResult AddRerollShopSlotPricesEvent( RerollShopSlotPriceEvent e );
    RequestResult EditRerollShopSlotPricesEvent( RerollShopSlotPriceEvent e );

    RerollShopSlotAmountsResponse GetRerollShopSlotAmounts();
    RerollShopSlotAmountByIdResponse GetRerollShopSlotAmountById( int id );
    RequestResult AddRerollShopSlotAmountsEvent( RerollShopSlotAmountEvent e );
    RequestResult EditRerollShopSlotAmountsEvent( RerollShopSlotAmountEvent e );

    RerollShopGroupCurrenciesResponse GetRerollShopGroupCurrencies();
    RerollShopGroupCurrenciesByIdResponse GetRerollShopGroupCurrenciesById( int id );
    RequestResult AddRerollShopGroupCurrenciesEvent( RerollShopGroupCurrenciesEvent e );
    RequestResult EditRerollShopGroupCurrenciesEvent( RerollShopGroupCurrenciesEvent e );

    RerollShopGroupProbabilitiesResponse GetRerollShopGroupProbabilities();
    RerollShopGroupProbabilityByIdResponse GetRerollShopGroupProbabilityById( int id );
    RequestResult AddRerollShopGroupProbabilityEvent( RerollShopGroupProbabilityEvent e );
    RequestResult EditRerollShopGroupProbabilityEvent( RerollShopGroupProbabilityEvent e );

    FirstBuyGoldPricesResponse GetFirstBuyPrices();
    FirstBuyGoldPriceByIdResponse GetFirstBuyPriceById( int id );
    RequestResult AddFirstBuyPricesEvent( FirstBuyGoldPriceEvent e );
    RequestResult EditFirstBuyPricesEvent( FirstBuyGoldPriceEvent e );

    RerollShopPremiumNotInactiveResponse GetRerollShopPremiumNotInactive();
    RerollShopPremiumNotInactiveByIdResponse GetRerollShopPremiumNotInactiveById( int id );
    RequestResult AddRerollShopPremiumNotInactiveEvent( RerollShopPremiumNotInactiveEvent e );
    RequestResult EditRerollShopPremiumNotInactiveEvent( RerollShopPremiumNotInactiveEvent e );

    RerollShopGroupSlotsResponse GetRerollShopGroupSlots();
    RerollShopGroupSlotsByIdResponse GetRerollShopGroupSlotsById( int id );
    RequestResult AddRerollShopGroupSlotsEvent( RerollShopGroupSlotsEvent e );
    RequestResult EditRerollShopGroupSlotsEvent( RerollShopGroupSlotsEvent e );

    RerollShopBannerByIdResponse GetRerollShopBannerById( int id );
    RequestResult AddRerollShopBanner( RerollShopBanner e );
    RequestResult EditRerollShopBanner( RerollShopBanner e );

    RerollShopTooltipByIdResponse GetRerollShopTooltipById( int id );
    RequestResult AddRerollShopTooltip( RerollShopTooltip e );
    RequestResult EditRerollShopTooltip( RerollShopTooltip e );

    // Roll Events
    RollEventsResponse GetRollEvents();
    RollEventByIdResponse GetRollEventById( int id );
    RequestResult AddRollEvent( RollEvent e );
    RequestResult EditRollEvent( RollEvent e );

    // Quest Events
    QuestEventsResponse GetQuestEvents();
    QuestEventByIdResponse GetQuestEventById(int id);
    RequestResult AddQuestEvent(QuestEvent e);
    RequestResult EditQuestEvent(QuestEvent e);

    //GW Events
    GWEventsModelResponse GetGWEvents();
    GWEventsModelByIdResponse GetGwEventById(int id);
    RequestResult EditGWEvent(GWEventModel e, string gmLogin);

    // Trade Events
    TradeEventsResponse GetTradeEvents();
    TradeEventByIdResponse GetTradeEventById(int id);
    RequestResult AddTradeEvent(TradeEventModel e);
    RequestResult EditTradeEvent(TradeEventModel e);

    // Season Events
    SeasonEventsResponse GetSeasonEvents();
    SeasonEventByIdResponse GetSeasonEventById(int id);
    RequestResult AddSeasonEvent(SeasonEvent e);
    RequestResult EditSeasonEvent(SeasonEvent e);

    // Donate Events
    DonateEventsResponse GetDonateEvents();
    DonateEventByIdResponse GetDonateEventById(int id);
    RequestResult AddDonateEvent(DonateEvent e);
    RequestResult EditDonateEvent(DonateEvent e);
  }


  public class EventManagementService : IEventManagementService
  {
    /// <summary>
    /// Таймаут соединения с сервисом (мс)
    /// </summary>
    public const int Timeout = 30000;

    private AccountManagement.Client client;
    private static ILog _log = LogManager.GetLogger(typeof(EventManagementService));

    public EventManagementService(Uri address)
    {
      if (address == null)
        throw new ArgumentNullException("address");
      // init thrift client
      TTransport transport = new THttpClient(address) { ConnectTimeout = Timeout };
      TProtocol proto = new TBinaryProtocol(transport);
      this.client = new AccountManagement.Client( proto );
    }


    private static T PerformAndHandle<T>(Func<T> function) 
      where T : class
    {
      try
      {
        T result = function();
        _log.DebugFormat("EventManagement response: {0}", result);
        return result;
      }
      catch (Exception ex)
      {
        _log.Error("EventManagement error", ex);
        return null;
      }
    }

    private static RequestResult PerformAndHandle(Func<RequestResult> function)
    {
      try
      {
        RequestResult result = function();
        _log.DebugFormat("EventManagement response: {0}", result);
        return result;
      }
      catch (Exception ex)
      {
        _log.Error("EventManagement error", ex);
        return RequestResult.BadResult;
      }
    }

    public BroadcastLocalesResponse GetBroadcastLocales()
    {
      _log.DebugFormat( "EventManagement request GetBroadcastLocales()" );
      return PerformAndHandle( () => client.GetBroadcastLocales() );
    }

    public CommonEventsListResponse GetAvailableEvents()
    {
      _log.Debug("EventManagement request GetAvailableEvents()");
      return PerformAndHandle(() => client.GetAvailableEvents());
    }

    public RequestResult ChangeEventStateById(int persistentId, bool state)
    {
      _log.DebugFormat("EventManagement request ChangeEventStateById({0}, {1})", persistentId, state);
      return PerformAndHandle(() => client.ChangeEventStateById(persistentId, state));
    }

    public RequestResult DeleteEventById(int persistentId)
    {
      _log.DebugFormat("EventManagement request DeleteEventById({0})", persistentId);
      return PerformAndHandle(() => client.DeleteEventById(persistentId));
    }

    public SkinGoldPricesResponse GetSkinPrices()
    {
      _log.Debug("EventManagement request GetSkinPrices()");
      return PerformAndHandle(() => client.GetSkinPrices());
    }

    public SkinGoldPriceByIdResponse GetSkinPriceById(int id)
    {
      _log.DebugFormat("EventManagement request GetSkinPriceById({0})", id);
      return PerformAndHandle(() => client.GetSkinPriceById(id));
    }

    public RequestResult AddSkinPricesEvent(SkinGoldPriceEvent e)
    {
      _log.DebugFormat("EventManagement request AddSkinPricesEvent({0})", e);
      return PerformAndHandle(() => client.AddSkinPricesEvent(e));
    }

    public RequestResult EditSkinPricesEvent(SkinGoldPriceEvent e)
    {
      _log.DebugFormat("EventManagement request EditSkinPricesEvent({0})", e);
      return PerformAndHandle(() => client.EditSkinPricesEvent(e));
    }


    public HeroPricesResponse GetHeroPrices()
    {
      _log.Debug("EventManagement request GetHeroPrices()");
      return PerformAndHandle(() => client.GetHeroPrices());
    }

    public HeroPriceByIdResponse GetHeroPriceById(int id)
    {
      _log.DebugFormat("EventManagement request GetHeroPriceById({0})", id);
      return PerformAndHandle(() => client.GetHeroPriceById(id));
    }

    public RequestResult AddHeroPricesEvent(HeroPriceEvent e)
    {
      _log.DebugFormat("EventManagement request AddHeroPricesEvent({0})", e);
      return PerformAndHandle(() => client.AddHeroPricesEvent(e));
    }

    public RequestResult EditHeroPricesEvent(HeroPriceEvent e)
    {
      _log.DebugFormat("EventManagement request EditHeroPricesEvent({0})", e);
      return PerformAndHandle(() => client.EditHeroPricesEvent(e));
    }


    public CustomEventByIdResponse GetCustomEventById(int id)
    {
      _log.DebugFormat("EventManagement request CustomEventByIdResponse({0})", id);
      return PerformAndHandle(() => client.GetCustomEventById(id));
    }

    public RequestResult AddCustomEvent(CustomEvent e)
    {
      _log.DebugFormat("EventManagement request AddCustomEvent({0})", e);
      return PerformAndHandle(() => client.AddCustomEvent(e));
    }

    public RequestResult EditCustomEvent(CustomEvent e)
    {
      _log.DebugFormat("EventManagement request EditCustomEvent({0})", e);
      return PerformAndHandle(() => client.EditCustomEvent(e));
    }

    public TechsInfoByIdResponse GetTechsInfoById(int id)
    {
      _log.DebugFormat("EventManagement request GetTechsInfoById({0})", id);
      return PerformAndHandle(() => client.GetTechsInfoById(id));
    }

    public RequestResult AddTechs(TechsInfo e)
    {
      _log.DebugFormat("EventManagement request AddTechs({0})", e);
      return PerformAndHandle(() => client.AddTechs(e));
    }

    public RequestResult EditTechs(TechsInfo e)
    {
      _log.DebugFormat("EventManagement request EditTechs({0})", e);
      return PerformAndHandle(() => client.EditTechs(e));
    }

    public CustomMapByIdResponse GetCustomMapById(int id)
    {
      _log.DebugFormat("EventManagement request GetCustomMapById({0})", id);
      return PerformAndHandle(() => client.GetCustomMapById(id));
    }

    public RequestResult AddCustomMap(CustomMap e)
    {
      _log.DebugFormat("EventManagement request AddCustomMap({0})", e);
      return PerformAndHandle(() => client.AddCustomMap(e));
    }

    public RequestResult EditCustomMap(CustomMap e)
    {
      _log.DebugFormat("EventManagement request EditCustomMap({0})", e);
      return PerformAndHandle(() => client.EditCustomMap(e));
    }

    public TalentDropRaritiesResponse GetTalentDropRarities()
    {
      _log.DebugFormat("EventManagement request GetTalentDropRarities()");
      return PerformAndHandle(() => client.GetTalentDropRarities());
    }

    public TalentDropRarityByIdResponse GetTalentDropRarityById(int id)
    {
      _log.DebugFormat("EventManagement request GetTalentDropRarityById({0})", id);
      return PerformAndHandle(() => client.GetTalentDropRarityById(id));
    }

    public RequestResult AddTalentDropRarities(TalentDropRarityEvent e)
    {
      _log.DebugFormat("EventManagement request AddTalentDropRarities({0})", e);
      return PerformAndHandle(() => client.AddTalentDropRarities(e));
    }

    public RequestResult EditTalentDropRarities(TalentDropRarityEvent e)
    {
      _log.DebugFormat("EventManagement request EditTalentDropRarities({0})", e);
      return PerformAndHandle(() => client.EditTalentDropRarities(e));
    }

    public NewsBannerByIdResponse GetNewsBannerById(int id)
    {
      _log.DebugFormat("EventManagement request GetNewsBannerById({0})", id);
      return PerformAndHandle(() => client.GetNewsBannerById(id));
    }

    public RequestResult AddNewsBanner(NewsBanner e)
    {
      _log.DebugFormat("EventManagement request AddNewsBanner({0})", e);
      return PerformAndHandle(() => client.AddNewsBanner(e));
    }

    public RequestResult EditNewsBanner(NewsBanner e)
    {
      _log.DebugFormat("EventManagement request EditNewsBanner({0})", e);
      return PerformAndHandle(() => client.EditNewsBanner(e));
    }

    public TransmutationTalentsPerPerlResponse GetTransmutationTalentsPerPerl()
    {
      _log.DebugFormat("EventManagement request GetTransmutationTalentsPerPerl()");
      return PerformAndHandle(() => client.GetTransmutationTalentsPerPerl());
    }

    public TransmutationTalentsPerPerlByIdResponse GetTransmutationTalentsPerPerlById(int id)
    {
      _log.DebugFormat("EventManagement request GetTransmutationTalentsPerPerlById({0})", id);
      return PerformAndHandle(() => client.GetTransmutationTalentsPerPerlById(id));
    }

    public RequestResult AddTalentPerPerlEvent(TransmutationTalentsPerPerl e)
    {
      _log.DebugFormat("EventManagement request AddTalentPerPerlEvent({0})", e);
      return PerformAndHandle(() => client.AddTalentPerPerlEvent(e));
    }

    public RequestResult EditTalentPerPerlEvent(TransmutationTalentsPerPerl e)
    {
      _log.DebugFormat("EventManagement request EditTalentPerPerlEvent({0})", e);
      return PerformAndHandle(() => client.EditTalentPerPerlEvent(e));
    }


    public ReforgeTalentPriceResponse GetReforgeTalentPrice()
    {
        _log.DebugFormat("EventManagement request GetReforgeTalentPrice()");
        return PerformAndHandle(() => client.GetReforgeTalentPrice());
    }

    public ReforgeTalentPriceByIdResponse GetReforgeTalentPriceById(int id)
    {
        _log.DebugFormat("EventManagement request GetReforgeTalentPriceById({0})", id);
        return PerformAndHandle(() => client.GetReforgeTalentPriceById(id));
    }

    public RequestResult AddReforgeTalentPriceEvent(ReforgeTalentPrices e)
    {
        _log.DebugFormat("EventManagement request AddReforgeTalentPriceEvent({0})", e);
        return PerformAndHandle(() => client.AddReforgeTalentPriceEvent(e));
    }

    public RequestResult EditReforgeTalentPriceEvent(ReforgeTalentPrices e)
    {
        _log.DebugFormat("EventManagement request EditReforgeTalentPriceEvent({0})", e);
        return PerformAndHandle(() => client.EditReforgeTalentPriceEvent(e));
    }


    public RerollShopSlotsResponse GetRerollShopSlots()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopSlots()" );
      return PerformAndHandle( () => client.GetRerollShopSlots() );
    }

    public RerollShopSlotsByIdResponse GetRerollShopSlotsById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopSlotsById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopSlotsById( id ) );
    }

    public RequestResult AddRerollShopSlotsEvent( RerollShopSlots e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopSlotsEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopSlotsEvent( e ) );
    }

    public RequestResult EditRerollShopSlotsEvent( RerollShopSlots e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopSlotsEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopSlotsEvent( e ) );
    }

    public RerollShopPricesResponse GetRerollShopPrices()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopSlots()" );
      return PerformAndHandle( () => client.GetRerollShopPrices() );
    }

    public RerollShopPriceByIdResponse GetRerollShopPriceById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopPriceById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopPriceById( id ) );
    }

    public RequestResult AddRerollShopPriceEvent( RerollShopPrice e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopPriceEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopPriceEvent( e ) );
    }

    public RequestResult EditRerollShopPriceEvent( RerollShopPrice e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopPriceEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopPriceEvent( e ) );
    }

    public RerollShopGroupPricesResponse GetRerollShopGroupPrices()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupPrices()" );
      return PerformAndHandle( () => client.GetRerollShopGroupPrices() );
    }

    public RerollShopGroupPriceByIdResponse GetRerollShopGroupPriceById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupPriceById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopGroupPriceById( id ) );
    }

    public RequestResult AddRerollShopGroupPriceEvent( RerollShopGroupPriceEvent e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopGroupPriceEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopGroupPricesEvent( e ) );
    }

    public RequestResult EditRerollShopGroupPriceEvent( RerollShopGroupPriceEvent e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopGroupPriceEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopGroupPricesEvent( e ) );
    }

    public RerollShopGroupProbabilitiesResponse GetRerollShopGroupProbabilities()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupProbabilities()" );
      return PerformAndHandle( () => client.GetRerollShopGroupProbabilities() );
    }

    public RerollShopGroupProbabilityByIdResponse GetRerollShopGroupProbabilityById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupProbabilityById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopGroupProbabilityById( id ) );
    }

    public RequestResult AddRerollShopGroupProbabilityEvent( RerollShopGroupProbabilityEvent e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopGroupProbabilityEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopGroupProbabilityEvent( e ) );
    }

    public RequestResult EditRerollShopGroupProbabilityEvent( RerollShopGroupProbabilityEvent e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopGroupProbabilityEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopGroupProbabilityEvent( e ) );
    }

    public RerollShopGroupCurrenciesResponse GetRerollShopGroupCurrencies()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupCurrencies()" );
      return PerformAndHandle( () => client.GetRerollShopGroupCurrencies() );
    }

    public RerollShopGroupCurrenciesByIdResponse GetRerollShopGroupCurrenciesById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupCurrenciesById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopGroupCurrenciesById( id ) );
    }

    public RequestResult AddRerollShopGroupCurrenciesEvent( RerollShopGroupCurrenciesEvent e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopGroupCurrenciesEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopGroupCurrenciesEvent( e ) );
    }

    public RequestResult EditRerollShopGroupCurrenciesEvent( RerollShopGroupCurrenciesEvent e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopGroupCurrenciesEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopGroupCurrenciesEvent( e ) );
    }

    public RerollShopSlotPricesResponse GetRerollShopSlotPrices()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopSlotPrices()" );
      return PerformAndHandle( () => client.GetRerollShopSlotPrices() );
    }

    public RerollShopSlotPriceByIdResponse GetRerollShopSlotPriceById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopSlotPriceById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopSlotPriceById( id ) );
    }

    public RequestResult AddRerollShopSlotPricesEvent( RerollShopSlotPriceEvent e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopSlotPriceEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopSlotPricesEvent( e ) );
    }

    public RequestResult EditRerollShopSlotPricesEvent( RerollShopSlotPriceEvent e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopSlotPriceEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopSlotPricesEvent( e ) );
    }

    public RerollShopSlotAmountsResponse GetRerollShopSlotAmounts()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopSlotAmounts()" );
      return PerformAndHandle( () => client.GetRerollShopSlotAmount() );
    }

    public RerollShopSlotAmountByIdResponse GetRerollShopSlotAmountById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopSlotAmountById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopSlotAmountById( id ) );
    }

    public RequestResult AddRerollShopSlotAmountsEvent( RerollShopSlotAmountEvent e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopSlotAmountEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopSlotAmountsEvent( e ) );
    }

    public RequestResult EditRerollShopSlotAmountsEvent( RerollShopSlotAmountEvent e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopSlotAmountEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopSlotAmountsEvent( e ) );
    }

    public FirstBuyGoldPricesResponse GetFirstBuyPrices()
    {
      _log.Debug( "EventManagement request GetFirstBuyPrices()" );
      return PerformAndHandle( () => client.GetFirstBuyPrices() );
    }

    public FirstBuyGoldPriceByIdResponse GetFirstBuyPriceById( int id )
    {
      _log.DebugFormat( "EventManagement request GetFirstBuyPriceById({0})", id );
      return PerformAndHandle( () => client.GetFirstBuyPriceById( id ) );
    }

    public RequestResult AddFirstBuyPricesEvent( FirstBuyGoldPriceEvent e )
    {
      _log.DebugFormat( "EventManagement request AddFirstBuyPricesEvent({0})", e );
      return PerformAndHandle( () => client.AddFirstBuyPricesEvent( e ) );
    }

    public RequestResult EditFirstBuyPricesEvent( FirstBuyGoldPriceEvent e )
    {
      _log.DebugFormat( "EventManagement request EditFirstBuyPricesEvent({0})", e );
      return PerformAndHandle( () => client.EditFirstBuyPricesEvent( e ) );
    }

    public RerollShopPremiumNotInactiveResponse GetRerollShopPremiumNotInactive()
    {
      _log.Debug( "EventManagement request GetRerollShopPremiumNotInactive()" );
      return PerformAndHandle( () => client.GetRerollShopPremiumNotInactive() );
    }

    public RerollShopPremiumNotInactiveByIdResponse GetRerollShopPremiumNotInactiveById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopPremiumNotInactiveById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopPremiumNotInactiveById( id ) );
    }

    public RequestResult AddRerollShopPremiumNotInactiveEvent( RerollShopPremiumNotInactiveEvent e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopPremiumNotInactiveEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopPremiumNotInactiveEvent( e ) );
    }

    public RequestResult EditRerollShopPremiumNotInactiveEvent( RerollShopPremiumNotInactiveEvent e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopPremiumNotInactiveEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopPremiumNotInactiveEvent( e ) );
    }

    public RerollShopGroupSlotsResponse GetRerollShopGroupSlots()
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupSlots()" );
      return PerformAndHandle( () => client.GetRerollShopGroupSlots() );
    }

    public RerollShopGroupSlotsByIdResponse GetRerollShopGroupSlotsById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopGroupSlotsById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopGroupSlotsById( id ) );
    }

    public RequestResult AddRerollShopGroupSlotsEvent( RerollShopGroupSlotsEvent e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopGroupSlotsEvent({0})", e );
      return PerformAndHandle( () => client.AddRerollShopGroupSlotsEvent( e ) );
    }

    public RequestResult EditRerollShopGroupSlotsEvent( RerollShopGroupSlotsEvent e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopGroupSlotsEvent({0})", e );
      return PerformAndHandle( () => client.EditRerollShopGroupSlotsEvent( e ) );
    }

    public RerollShopBannerByIdResponse GetRerollShopBannerById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopBannerById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopBannerById( id ) );
    }

    public RequestResult AddRerollShopBanner( RerollShopBanner e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopBanner({0})", e );
      return PerformAndHandle( () => client.AddRerollShopBanner( e ) );
    }

    public RequestResult EditRerollShopBanner( RerollShopBanner e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopBanner({0})", e );
      return PerformAndHandle( () => client.EditRerollShopBanner( e ) );
    }

    public RerollShopTooltipByIdResponse GetRerollShopTooltipById( int id )
    {
      _log.DebugFormat( "EventManagement request GetRerollShopTooltipById({0})", id );
      return PerformAndHandle( () => client.GetRerollShopTooltipById( id ) );
    }

    public RequestResult AddRerollShopTooltip( RerollShopTooltip e )
    {
      _log.DebugFormat( "EventManagement request AddRerollShopTooltip({0})", e );
      return PerformAndHandle( () => client.AddRerollShopTooltip( e ) );
    }

    public RequestResult EditRerollShopTooltip( RerollShopTooltip e )
    {
      _log.DebugFormat( "EventManagement request EditRerollShopTooltip({0})", e );
      return PerformAndHandle( () => client.EditRerollShopTooltip( e ) );
    }

    #region Roll Events

    public RollEventsResponse GetRollEvents()
    {
      _log.DebugFormat("EventManagement request GetRollEvents()");
      return PerformAndHandle(() => client.GetRollEvents());
    }

    public RollEventByIdResponse GetRollEventById(int id)
    {
      _log.DebugFormat("EventManagement request GetRollEventById({0})", id);
      return PerformAndHandle(() => client.GetRollEventById(id));
    }

    public RequestResult AddRollEvent(RollEvent e)
    {
      _log.DebugFormat("EventManagement request AddRollEvent({0})", e);
      return PerformAndHandle(() => client.AddRollEvent(e));
    }

    public RequestResult EditRollEvent(RollEvent e)
    {
      _log.DebugFormat("EventManagement request EditRollEvent({0})", e);
      return PerformAndHandle(() => client.EditRollEvent(e));
    }

    #endregion

    #region Quest Events

    public QuestEventsResponse GetQuestEvents()
    {
      _log.DebugFormat("EventManagement request GetQuestEvents()");
      return PerformAndHandle(() => client.GetQuestEvents());
    }

    public QuestEventByIdResponse GetQuestEventById(int id)
    {
      _log.DebugFormat("EventManagement request GetQuestEventById({0})", id);
      return PerformAndHandle(() => client.GetQuestEventById(id));
    }

    public RequestResult AddQuestEvent(QuestEvent e)
    {
      _log.DebugFormat("EventManagement request AddQuestEvent({0})", e);
      return PerformAndHandle(() => client.AddQuestEvent(e));
    }

    public RequestResult EditQuestEvent(QuestEvent e)
    {
      _log.DebugFormat("EventManagement request EditQuestEvent({0})", e);
      return PerformAndHandle(() => client.EditQuestEvent(e));
    }

    #endregion

    // Gw Events
      public GWEventsModelResponse GetGWEvents()
      {
          _log.DebugFormat("EventManagement request GetGWEvents()");
          return PerformAndHandle(() => client.GetGWEvents());
      }

      public GWEventsModelByIdResponse GetGwEventById(int id)
      {
          _log.DebugFormat("EventManagement request GetGwEventById({0})", id);
          return PerformAndHandle(() => client.GetGWEventsModelById(id));
      }

      public RequestResult EditGWEvent(GWEventModel e, string gmLogin)
      {
          _log.DebugFormat("EventManagement request EditGwEvent({0})", e);
          return PerformAndHandle(() => client.EditGWEvent(e, gmLogin));
      }

    #region Trade Events

    public TradeEventsResponse GetTradeEvents()
    {
      _log.DebugFormat("EventManagement request GetTradeEvents()");
      return PerformAndHandle(() => client.GetTradeEvents());
    }

    public TradeEventByIdResponse GetTradeEventById(int id)
    {
      _log.DebugFormat("EventManagement request GetTradeEventById({0})", id);
      return PerformAndHandle(() => client.GetTradeEventById(id));
    }

    public RequestResult AddTradeEvent(TradeEventModel e)
    {
      _log.DebugFormat("EventManagement request AddTradeEvent({0})", e);
      return PerformAndHandle(() => client.AddTradeEvent(e));
    }

    public RequestResult EditTradeEvent(TradeEventModel e)
    {
      _log.DebugFormat("EventManagement request EditTradeEvent({0})", e);
      return PerformAndHandle(() => client.EditTradeEvent(e));
    }

    #endregion

    #region Season Events

    public SeasonEventsResponse GetSeasonEvents()
    {
        _log.DebugFormat("EventManagement request GetSeasonEvents()");
        return PerformAndHandle(() => client.GetSeasonEvents());
    }

    public SeasonEventByIdResponse GetSeasonEventById(int id)
    {
        _log.DebugFormat("EventManagement request GetSeasonEventById({0})", id);
        return PerformAndHandle(() => client.GetSeasonEventById(id));
    }

    public RequestResult AddSeasonEvent(SeasonEvent e)
    {
        _log.DebugFormat("EventManagement request AddSeasonEvent({0})", e);
        return PerformAndHandle(() => client.AddSeasonEvent(e));
    }

    public RequestResult EditSeasonEvent(SeasonEvent e)
    {
        _log.DebugFormat("EventManagement request EditSeasonEvent({0})", e);
        return PerformAndHandle(() => client.EditSeasonEvent(e));
    }

    public DonateEventsResponse GetDonateEvents()
    {
      _log.DebugFormat("EventManagement request GetDonateEvents()");
      return PerformAndHandle(() => client.GetDonateEvents());
    }

    public DonateEventByIdResponse GetDonateEventById(int id)
    {
      _log.DebugFormat("EventManagement request GetDonateEventById({0})", id);
      return PerformAndHandle(() => client.GetDonateEventById(id));
    }

    public RequestResult AddDonateEvent(DonateEvent e)
    {
      _log.DebugFormat("EventManagement request AddDonateEvent({0})", e);
      return PerformAndHandle(() => client.AddDonateEvent(e));
    }

    public RequestResult EditDonateEvent(DonateEvent e)
    {
      _log.DebugFormat("EventManagement request EditDonateEvent({0})", e);
      return PerformAndHandle(() => client.EditDonateEvent(e));
    }

    #endregion
  }

}