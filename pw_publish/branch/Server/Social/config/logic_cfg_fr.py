# -*- coding: utf-8 -*-
# this file is to be loaded through execfile() called from some config class' method
# so `self.` refers to the loader method's object

##----------------------------------------------------------------------------------------------------------------------
## блок настроек игровой логики
self.INIT_SILVER = 525000
self.overrideData( "/Dialog/CastleTutorial/Ador/m3/m30_qB::objectives.Item.[1].instant.Item.[0].url", "http://fr.playpw.com/gold/first-purchase.html" )
self.overrideData( "/Dialog/CastleTutorial/Dokt/m3/m30_qA::objectives.Item.[1].instant.Item.[0].url", "http://fr.playpw.com/gold/first-purchase.html" )

self.overrideData( "/UI/Content/MarketingEvents/FirstBuy::imageA", "http://fr.playpw.com/images/promo/001-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/FirstBuy::imageB", "http://fr.playpw.com/images/promo/001-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/BuyGoldHero::imageA", "http://fr.playpw.com/images/promo/002-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/BuyGoldHero::imageB", "http://fr.playpw.com/images/promo/002-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/BuyHero::imageA", "http://fr.playpw.com/images/promo/003-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/BuyHero::imageB", "http://fr.playpw.com/images/promo/003-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/PremiumAcc::imageA", "http://fr.playpw.com/images/promo/006-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/PremiumAcc::imageB", "http://fr.playpw.com/images/promo/006-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/BuySpecialHero::imageA", "http://fr.playpw.com/images/promo/007-fr.png" )
self.overrideData( "/UI/Content/MarketingEvents/BuySpecialHero::imageB", "http://fr.playpw.com/images/promo/008-fr.png" )