/*
#ref PF_Types.DBTypes.dll
#ref PF_EditorC.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using System.Xml;
using System.IO;
using PF_EditorC;

public class Heroes2XML
{
  public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
  {
    bool isParamsCorrect = (parameters.Length == 1);

    if (!isParamsCorrect)
    {
      Console.WriteLine("Usage: PF_EditorC.exe run ../Tools/Scripts/Heroes2XML.cs <result_file>");
      yield return true;
    }

    string resultFilePath = parameters[0];

    HeroesDB heroesDB = DataBase.Get<HeroesDB>(DBID.FromFileName("/Heroes/_.HRDB.xdb", false));

    if (File.Exists(resultFilePath))
    {
      File.Delete(resultFilePath);
    }
    using (XmlWriter xmlFile = XmlWriter.Create(resultFilePath))
    {
      xmlFile.WriteStartDocument();

      xmlFile.WriteStartElement("heroes");

      foreach (HeroParams heroParams in heroesDB.heroes)
      {
        Hero hero = heroParams.hero.Get();
        foreach (EFaction faction in Enum.GetValues(typeof(EFaction)))
        {
          bool factionEnablad = false;
          switch (faction)
          {
            case EFaction.Freeze:
              factionEnablad = ((hero.heroRace & EHeroRaces.A) == EHeroRaces.A);
              break;
            case EFaction.Burn:
              factionEnablad = ((hero.heroRace & EHeroRaces.B) == EHeroRaces.B);
              break;
            case EFaction.Neutral:
              factionEnablad = false;
              break;
          }

          if (!factionEnablad)
          {
            continue;
          }

          xmlFile.WriteStartElement("hero");

          string factionName = (faction == EFaction.Freeze) ? "A" : "B";
          xmlFile.WriteAttributeString("heroId", hero.persistentId);
          xmlFile.WriteAttributeString("faction", factionName);
          xmlFile.WriteAttributeString("legal", heroParams.legal.ToString());

          string heroName = (faction == EFaction.Freeze) ? hero.heroNameA.ToString() : hero.heroNameB.ToString();
          xmlFile.WriteStartElement("name");
          xmlFile.WriteString(heroName);
          xmlFile.WriteEndElement();
		  
		   bool isHeroHiredByDefaultMale = hero.lobbyData.IsHeroHiredByDefaultMale;
          xmlFile.WriteStartElement("isHeroHiredByDefaultMale");
          xmlFile.WriteValue(isHeroHiredByDefaultMale);
          xmlFile.WriteEndElement();
		  
		   bool isHeroHiredByDefaultFemale = hero.lobbyData.IsHeroHiredByDefaultFemale;
          xmlFile.WriteStartElement("isHeroHiredByDefaultFemale");
          xmlFile.WriteValue(isHeroHiredByDefaultFemale);
          xmlFile.WriteEndElement();
		  
		  int maxForceStock = hero.lobbyData.Stats.MaxForceStock;
          xmlFile.WriteStartElement("maxForceStock");
          xmlFile.WriteValue(maxForceStock);
          xmlFile.WriteEndElement();
		  
		  
		  int energyRegen = hero.lobbyData.Stats.EnergyRegen;
		  xmlFile.WriteStartElement("energyRegen");
          xmlFile.WriteValue(energyRegen);
          xmlFile.WriteEndElement();
		  
		  int pvPSessionEnergyCost = hero.lobbyData.Stats.PvPSessionEnergyCost;
		  xmlFile.WriteStartElement("pvPSessionEnergyCost");
          xmlFile.WriteValue(pvPSessionEnergyCost);
          xmlFile.WriteEndElement();
		  
          string heroDescription = (faction == EFaction.Freeze) ? hero.lobbyData.heroDescriptionA.ToString() : hero.lobbyData.heroDescriptionB.ToString();
          xmlFile.WriteStartElement("description");
          xmlFile.WriteString(heroDescription);
          xmlFile.WriteEndElement();

          string heroBiography  = ( faction == EFaction.Freeze ) ? hero.lobbyData.heroBiographyA.ToString() : hero.lobbyData.heroBiographyB.ToString();
          xmlFile.WriteStartElement( "biography" );
          xmlFile.WriteString( heroBiography );
          xmlFile.WriteEndElement();

          Texture icon = (faction == EFaction.Freeze) ? hero.heroImageA.Get() : hero.heroImageB.Get();
          string iconPath = (icon != null) ? icon.srcFileName.FileName : "";
          xmlFile.WriteStartElement("iconPath");
          xmlFile.WriteString(iconPath);
          xmlFile.WriteEndElement();

          Texture render = (faction == EFaction.Freeze) ? hero.lobbyData.heroRenderA.Get() : hero.lobbyData.heroRenderB.Get();
          string renderPath = (render != null) ? render.srcFileName.FileName : "";
          xmlFile.WriteStartElement("renderPath");
          xmlFile.WriteString(renderPath);
          xmlFile.WriteEndElement();

          xmlFile.WriteEndElement();
        }
      }

      xmlFile.WriteEndElement();
    }
    yield return true;
  }
}
