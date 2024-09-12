#define TALENTS_DICT
/*
#about выставление скомпилированных тултипов
#ref PF_Types.DBTypes.dll
#ref PF_EditorC.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;
using System.Xml;
using System.IO;
using System.Globalization;
using PF_EditorC;

public class FillCompiledTooltips
{
    public static string aiLogicPath = "/GameLogic/AILogic.AILP.xdb";
    public static string uiRootPath = "/UI/UIRoot.xdb";
    public static string uiDataPath = "/UI/Content/_.UIDT.xdb";
    public static string defaultStatsPath = "/GameLogic/Hero.UNLP.xdb";


    private static bool _maximize;
    private const int REFINE_RATE = 1;
    private const int MAX_REFINE_RATE = 10;
    private static int _refineRate = REFINE_RATE;
    private static AbilityAndDamageScalingParams _scales;
    private static AILogicParameters _aiLogicParams;
    private TalentInfo curTalentInfo;

    private Dictionary<string, TalentInfo> talents = new Dictionary<string, TalentInfo>();
    private Dictionary<Talent, Hero> heroesTalents = new Dictionary<Talent, Hero>();
    private Dictionary<Talent, TalentGroup> groupTalents = new Dictionary<Talent, TalentGroup>();

    private Dictionary<Talent, TalentKit> _talentsToKits;
    private Dictionary<Talent, TalentPack> _talentsToPacks;

    #region Talent Info - Constants and Condition Formulas

    private static bool CommonGet(string name, out bool result, EFaction faction)
    {
        switch (name)
        {
            case "true":
                result = true;
                break;
            case "false":
                result = false;
                break;
            case "fctnA":
            case "originalFctnA":
                result = (faction == EFaction.Freeze);
                break;
            case "fctnB":
            case "originalFctnB":
                result = (faction == EFaction.Burn);
                break;
            default:
                result = false;
                return false;
        }

        return true;
    }

    private static bool CommonGet(string name, out float result, EFaction faction)
    {
        bool commonResult;
        if (CommonGet(name, out commonResult, faction))
        {
            result = commonResult ? 1.0f : 0.0f;
            return true;
        }

        if (float.TryParse(name, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out result))
        {
            return true;
        }

        switch (name)
        {
            case "ABILITYTYPE__INVALID":
                result = 0.0f;
                break;
            case "ABILITYTYPE__ACTIVE":
                result = 1.0f;
                break;
            case "ABILITYTYPE__MULTIACTIVE":
                result = 2.0f;
                break;
            case "ABILITYTYPE__PASSIVE":
                result = 3.0f;
                break;
            case "ABILITYTYPE__AUTOCASTABLE":
                result = 4.0f;
                break;
            case "ABILITYTYPE__SWITCHABLE":
                result = 5.0f;
                break;
            case "ABILITYTYPE__CHANNELLING":
                result = 6.0f;
                break;
            case "HeroLevel":
                result = 1.0f;
                break;
            case "sTerrainType":
                result = 0.0f;
                break;
            case "sFctn":
                switch (faction)
                {
                    case EFaction.Neutral:
                        result = 0.0f;
                        break;
                    case EFaction.Freeze:
                        result = 1.0f;
                        break;
                    case EFaction.Burn:
                        result = 2.0f;
                        break;
                }
                break;
            default:
                result = 0.0f;
                return false;
        }

        return true;
    }

    #region Substitutes
    private class Substitutes
    {
        private static Dictionary<string, string> globalSubstitutes = new Dictionary<string, string>();
        private Dictionary<string, string> substitutes = new Dictionary<string, string>();

        public Substitutes(Talent talent, TalentPack talPack)
        {
            if (globalSubstitutes.Count == 0)
            {
                UIRoot uiRoot = DataBase.Get<UIRoot>(DBID.FromFileName(uiRootPath, false));
                List<UITextSubstitute> uiSubstitutes = new List<UITextSubstitute>(uiRoot.substitutes);
                foreach (UITextSubstitute uiSubstitute in uiSubstitutes)
                {
                    globalSubstitutes.Add(uiSubstitute.id, uiSubstitute.captionText.ToString());
                }
            }

            substitutes.Add("commonDescription", talent.commonDescription.ToString());
        }

        public string Get(string name)
        {
            string result;
            if (globalSubstitutes.TryGetValue(name, out result))
            {
                return result;
            }

            if (substitutes.TryGetValue(name, out result))
            {
                return result;
            }

            return "";
        }
    }
    #endregion

    #region Constants
    private class Constants
    {
        private static Dictionary<string, StringProcessor.Expression> globalConstants = new Dictionary<string, StringProcessor.Expression>();
        private static Dictionary<string, StringProcessor.Expression> heroStats = new Dictionary<string, StringProcessor.Expression>();
        private Dictionary<string, StringProcessor.Expression> constants = new Dictionary<string, StringProcessor.Expression>();
        private readonly DBID dbid;
        private readonly EFaction faction;
        private static List<int> talentNaftaCostByLevel = new List<int>();

        public Constants(TalentInfo talent)
        {
            if (talentNaftaCostByLevel.Count == 0)
            {

                foreach (int nc in _aiLogicParams.talentNaftaCostByLevel)
                    talentNaftaCostByLevel.Add(nc);
            }

            if (globalConstants.Count == 0)
            {
                UnitConstantsContainer globConstants = _aiLogicParams.globalConstants.Get();
                foreach (UnitConstant globConst in globConstants.vars)
                {
                    if (globalConstants.ContainsKey(globConst.name))
                    {
                        Log.TraceWarning("Global constatns {0} already exists. Cannot add constant from AILogicParameters", globConst.name);
                        continue;
                    }
                    globalConstants.Add(globConst.name, new StringProcessor.Expression(globConst.var.sString, Get));
                }

                globalConstants.Add("NaftaLevel", new StringProcessor.Expression(1.0f.ToString(), Get));
                globalConstants.Add("RefineRate", new StringProcessor.Expression(REFINE_RATE.ToString(), Get));

                UnitLogicParameters unitLogic = DataBase.Get<UnitLogicParameters>(DBID.FromFileName(defaultStatsPath, false));
                StatsContainer defaultStats = unitLogic.defaultStats.Get();
                foreach (UnitStat heroStat in defaultStats.stats)
                {
                    string statName = heroStat.statId.ToString();
                    if (globalConstants.ContainsKey(statName))
                    {
                        Log.TraceWarning("Global constatns {0} already exists. Cannot add constant from UnitLogicParameters.defaultStats", statName);
                        continue;
                    }
                    globalConstants.Add(statName, new StringProcessor.Expression(heroStat.value.sString, Get));
                }
                if (talent.Hero != null)
                {
                    StatsContainer s = talent.Hero.stats.Get();
                    foreach (UnitStat stat in s.stats)
                    {
                        if (heroStats.ContainsKey(stat.statId.ToString()))
                        {
                            Log.TraceWarning("Trying to add hero stat {0}, but stat already added.", stat.statId.ToString());
                            continue;
                        }
                        heroStats.Add(stat.statId.ToString(), new StringProcessor.Expression(stat.value.sString, Get));
                    }
                }
            }

            dbid = talent.Tal.DBId;
            faction = talent.Faction;

            int talNaftaCost = talent.Tal.naftaCost;
            if (talNaftaCost < 0)
                talNaftaCost = talentNaftaCostByLevel[talent.Tal.minLevel];

            constants.Add("Cooldown", new StringProcessor.Expression(talent.Tal.cooldownTime.sString, Get));
            constants.Add("ManaCost", new StringProcessor.Expression(talent.Tal.manaCost.sString, Get));
            constants.Add("NaftaCost", new StringProcessor.Expression(talNaftaCost.ToString(), Get));
            constants.Add("DevPoints", new StringProcessor.Expression(talent.Tal.devPoints.ToString(), Get));
            constants.Add("TalentLevel", new StringProcessor.Expression(talent.Tal.minLevel.ToString(), Get));
            constants.Add("TalentDevPoints", new StringProcessor.Expression(talent.Tal.devPoints.ToString(), Get));
            constants.Add("AbilityType", new StringProcessor.Expression(((int)talent.Tal.type).ToString(), Get));
            constants.Add("ConsumptionBonusConst", new StringProcessor.Expression(talent.Tal.consumptionBonus.constant.ToString(), Get));
            constants.Add("ConsumptionBonusPercent", new StringProcessor.Expression(talent.Tal.consumptionBonus.percent.ToString(), Get));

            if ((talent.Tal.constants != null) && (talent.Tal.constants.Get() != null))
            {
                foreach (var constant in talent.Tal.constants.Get().vars)
                {
                    if ((constant != null) && (constant.Get() != null))
                    {
                        string name = constant.Get().name;
                        if (constants.ContainsKey(name))
                        {
                            Log.TraceWarning("Constant \"{0}\" already defined in talent \"{1}\"", name, talent.Tal.DBId);
                        }
                        else
                        {
                            constants.Add(name, new StringProcessor.Expression(constant.Get().var.sString, Get));
                        }
                    }
                }
            }
        }
        //, StatsContainer heroStats
        public float Get(string name)
        {
            float commonResult;
            if (CommonGet(name, out commonResult, faction))
            {
                return commonResult;
            }

            StringProcessor.Expression expression;
            if (name.StartsWith("sender.") || name.StartsWith("receiver."))
            {
                return 0.0f;
            }
            else
                if (name.StartsWith("s"))
                {
                    int statNameIndex = 1;

                    if (name.StartsWith("sMax"))
                    {
                        statNameIndex = 4;
                    }

                    if (name.StartsWith("sBase") && name != "sBaseAttack")
                    {
                        statNameIndex = 5;
                    }

                    string statName = name.Substring(statNameIndex);

                    //Overriding BaseAttack if defined in hero.
                    if (statName == "BaseAttack")
                        if (heroStats.TryGetValue(statName, out expression))
                            return expression.Calculate();

                    if (globalConstants.TryGetValue(statName, out expression))
                    {
                        float result = expression.Calculate();

                        if (_maximize)
                        {
                            if (statName == "BaseAttack")
                                return result;

                            StringProcessor.Expression statModifierExpression;
                            if (globalConstants.TryGetValue("StatModifier", out statModifierExpression))
                            {
                                float modifier = statModifierExpression.Calculate();
                                float multiplier = 1.0f;
                                if ((statName == "Life") || (statName == "Energy"))
                                {
                                    StringProcessor.Expression lifeEnergyMultiplierExpression;
                                    if (globalConstants.TryGetValue("LifeEnergyMultiplier", out lifeEnergyMultiplierExpression))
                                    {
                                        multiplier = lifeEnergyMultiplierExpression.Calculate();
                                    }
                                }
                                result += modifier * multiplier;
                            }
                        }

                        return result;
                    }
                }

            if (constants.TryGetValue(name, out expression))
            {
                return expression.Calculate();
            }

            if (globalConstants.TryGetValue(name, out expression))
            {
                return expression.Calculate();
            }

            Log.TraceWarning("Constant \"{0}\" not defined in talent \"{1}\"", name, dbid);

            return 0.0f;
        }
    }
    #endregion

    #region Condition formulas
    private class ConditionFormulas
    {
        private Dictionary<string, StringProcessor.Expression> globalConditionFormulas = new Dictionary<string, StringProcessor.Expression>();
        private Dictionary<string, StringProcessor.Expression> conditionFormulas = new Dictionary<string, StringProcessor.Expression>();
        private readonly DBID dbid;
        private readonly EFaction faction;

        public ConditionFormulas(Talent talent, EFaction _faction)
        {
            if (globalConditionFormulas.Count == 0)
            {
                List<DBPtr<ConditionFormula>> globCondFormulas = new List<DBPtr<ConditionFormula>>(_aiLogicParams.conditionFormulas);
                foreach (DBPtr<ConditionFormula> globCond in globCondFormulas)
                {
                    globalConditionFormulas.Add(globCond.Get().name, new StringProcessor.Expression(globCond.Get().condition.sString,
                      (string arg) => { return Get(arg) ? 1.0f : 0.0f; }));
                }
            }

            dbid = talent.DBId;
            faction = _faction;

            if (talent.conditionFormulas.Count != 0)
            {
                foreach (var conditionFormula in talent.conditionFormulas)
                {
                    if ((conditionFormula != null) && (conditionFormula.Get() != null))
                    {
                        string name = conditionFormula.Get().name;
                        if (conditionFormulas.ContainsKey(name))
                        {
                            Log.TraceWarning("Condition formula \"{0}\" already defined in talent \"{1}\"", name, talent.DBId);
                        }
                        else
                        {
                            conditionFormulas.Add(name, new StringProcessor.Expression(conditionFormula.Get().condition.sString,
                              (string arg) => { return Get(arg) ? 1.0f : 0.0f; }));
                        }
                    }
                }
            }
        }

        public bool Get(string name)
        {
            bool commonResult;
            if (CommonGet(name, out commonResult, faction))
            {
                return commonResult;
            }

            StringProcessor.Expression expression;
            if (globalConditionFormulas.TryGetValue(name, out expression))
            {
                return (expression.Calculate() != 0.0f);
            }

            if (conditionFormulas.TryGetValue(name, out expression))
            {
                return (expression.Calculate() != 0.0f);
            }

            Log.TraceWarning("Condition formula \"{0}\" not defined in talent \"{1}\"", name, dbid);
            return false;
        }
    }
    #endregion
    #endregion

    #region Process text, resolve values and conditions

    private bool ResolveCondition(string text)
    {
        if (text.StartsWith("talent.if."))
        {
            ConditionFormulas formulas = new ConditionFormulas(curTalentInfo.Tal, curTalentInfo.Faction);
            string condition = text.Substring(text.IndexOf("if.") + "if.".Length);
            return formulas.Get(condition);
        }
        else if (text == "talent.isInGroup")
        {
            return (curTalentInfo.Group != null);
        }
        else if (text == "talent.isBought")
        {
            return false;
        }
        else if (text == "talent.isClass")
        {
            return (curTalentInfo.Tal.rarity == ETalentRarity.Class);
        }
        else if (text == "talent.isOrdinary")
        {
            return (curTalentInfo.Tal.rarity == ETalentRarity.ordinary);
        }
        else if (text == "talent.isGood")
        {
            return (curTalentInfo.Tal.rarity == ETalentRarity.good);
        }
        else if (text == "talent.isExcellent")
        {
            return (curTalentInfo.Tal.rarity == ETalentRarity.excellent);
        }
        else if (text == "talent.isMagnificent")
        {
            return (curTalentInfo.Tal.rarity == ETalentRarity.magnificent);
        }
        else if (text == "talent.isExclusive")
        {
            return (curTalentInfo.Tal.rarity == ETalentRarity.exclusive);
        }
        else if (text == "talent.spendsLife")
        {
            return ((curTalentInfo.Tal.flags & EAbilityFlags.SpendLifeInsteadEnergy) != 0);
        }
        try
        {
            return ResolveValue(text) != 0.0f;
        }
        catch (Exception e)
        {
            Log.TraceError("Talent {0} has problem with {1}: {2}", curTalentInfo.Tal.name, text, e.Message);
        }
        return false;
    }

    /// <summary>
    /// <see cref="ResolveValue"/> overload for string values
    /// </summary>
    /// <param name="text">Base text string</param>
    /// <param name="result">result value</param>
    /// <returns></returns>
    private bool TryToResolveStringValue(string text, out string result)
    {
        result = string.Empty;
        if (text.StartsWith("talent."))
        {
            string fieldName = text.Substring(text.IndexOf("talent.") + "talent.".Length);
            switch (fieldName)
            {
                case "kitName":
                    TalentKit kit = GetTalentKit(curTalentInfo.Tal);
                    result = kit != null ? kit.name.GetText() : string.Empty;
                    return true;
                case "packIcon":
                    TalentPack pack = GetTalentPack(curTalentInfo.Tal);
                    result = pack != null ? pack.iconStyle : string.Empty;
                    return true;
            }
        }
        return false;
    }

    private float ResolveValue(string text)
    {
        float result = 0.0f;
        int precision = 0;

        Regex formatExpression = new Regex(@" format=\d\.(\d+)f?");
        MatchCollection formatMatches = formatExpression.Matches(text);
        if (formatMatches.Count == 1)
        {
            int.TryParse(formatMatches[0].Groups[1].Value, out precision);
            text = text.Replace(formatMatches[0].Groups[0].Value, "");
            text = text.TrimEnd(' ');
        }
        if (text == "force")
        {
            result = GetTalentForce(curTalentInfo.Tal, _aiLogicParams.forceParameters, _aiLogicParams.talentBaseStatBudget);
        }
        else if (text.StartsWith("talent.const.") || text.StartsWith("const."))
        {
            string constantName = text.Substring(text.IndexOf("const.") + "const.".Length);
            Constants constants = new Constants(curTalentInfo);
            try
            {
                result = constants.Get(constantName);
            }
            catch (Exception e)
            {
                Log.TraceError("Talent {0}. Can't get constant value {1}. Check expression in editor. Error details: {2}", curTalentInfo.Tal.DBId, constantName, e.Message);
                throw e;
            }
        }
        else
        {
            if (text.StartsWith("talent."))
            {
                Constants constants = new Constants(curTalentInfo);
                string fieldName = text.Substring(text.IndexOf("talent.") + "talent.".Length);
                TalentKit kit = GetTalentKit(curTalentInfo.Tal);
                TalentPack pack = GetTalentPack(curTalentInfo.Tal);
                switch (fieldName)
                {
                    case "moneyCost":
                        result = constants.Get("NaftaCost");
                        break;
                    case "manaCost":
                        result = constants.Get("ManaCost");
                        break;
                    case "devPoints":
                        result = constants.Get("DevPoints");
                        break;
                    case "cooldown":
                        result = constants.Get("Cooldown");
                        break;
                    case "mConsumptionBonusPercent":
                        result = constants.Get("ConsumptionBonusPercent");
                        break;
                    case "mConsumptionBonusConst":
                        result = constants.Get("ConsumptionBonusConst");
                        break;
                    case "castLimit":
                        result = constants.Get("castLimit");
                        break;
                    #region kit
                    case "isInKit":
                        result = kit != null ? 1 : 0;
                        break;
                    case "isSpecialInKit":
                        result = kit != null && kit.special.Get() == curTalentInfo.Tal ? 1 : 0;
                        break;
                    case "activatedInKitWithoutSelf":
                        result = 0;
                        break;
                    case "totalInKit":
                        result = kit != null ? kit.talents.Count : 0;
                        break;
                    //Everytime 0 for castle(no activate operation)
                    case "activatedInKit":
                        result = 0;
                        break;
                    case "isInPack":
                        result = pack != null ? 1 : 0;
                        break;
                    #endregion
                    default:
                        throw new InvalidOperationException(curTalentInfo.Tal.DBId.ToString() + ": can't find talent field " + fieldName + "!");
                }
            }

        }

        return (float)Math.Round(result, precision);
    }

    private string ProcessIfs(string text)
    {
        string tagOpenIf = @"☺\<if=([^\>]*)\>";
        string tagCloseIf = @"☺\</if\>";
        string tagElse = @"☺\<else\>";
        string body = "([^☺]*)";
        Regex ifExpression = new Regex(tagOpenIf + body + "(" + tagElse + body + ")?" + tagCloseIf);
        MatchCollection ifMatches = ifExpression.Matches(text);
        if (ifMatches.Count == 0)
        {
            return text;
        }

        foreach (Match match in ifMatches)
        {
            string condition = match.Groups[1].Value;
            string ifBody = match.Groups[2].Value;
            string elseBody = match.Groups[4].Value;

            if (ResolveCondition(condition))
            {
                text = text.Replace(match.Value, ifBody);
            }
            else
            {
                text = text.Replace(match.Value, elseBody);
            }
        }
        return ProcessIfs(text);
    }

    private string ProcessSubstitutes(string text)
    {
        string result = text;
        Regex substituteRegex = new Regex(@"\$\(([^\)]+)\)");
        MatchCollection substituteMatches = substituteRegex.Matches(result);
        int i = 0;
        foreach (Match match in substituteMatches)
        {
            string substitute = match.Groups[1].Value;
            string substituteText = string.Empty;

            if (substitute.StartsWith("TTRecommended"))
                substituteText = string.Format("<recommended:{0}>", substitute);
            else
            {
                Substitutes substitutes = new Substitutes(curTalentInfo.Tal, GetTalentPack(curTalentInfo.Tal));
                substituteText = substitutes.Get(substitute);
                if (!string.IsNullOrEmpty(substituteText))
                    i++;
            }

            result = result.Replace(match.Value, substituteText);
            if (substitute == "commonDescription")
                i++;
        }
        if (i > 0)
            result = ProcessSubstitutes(result);
        return result;
    }

    private static Regex reNoCompile = new Regex("<nocompile>(.*?)</nocompile>", RegexOptions.Compiled | RegexOptions.Singleline | RegexOptions.IgnoreCase);

    private string ExtractNoCompileFragments(string text, out Dictionary<string, string> fragments)
    {
        fragments = new Dictionary<string, string>();

        MatchCollection matches = reNoCompile.Matches(text);

        foreach (Match match in matches)
        {
            string fragmentId = string.Concat("##nocompile:", fragments.Count, "##");
            string fragment = match.Groups[1].Value;

            // do some processing on fragment
            // TODO: more processing?
            fragment = fragment.Replace("talent.if.", string.Empty);

            fragments.Add(fragmentId, fragment);

            text = text.Replace(match.Value, fragmentId);
        }

        return text;
    }

    private string InsertNoCompileFragments(string text, Dictionary<string, string> fragments)
    {
        foreach (var pair in fragments)
        {
            text = text.Replace(pair.Key, pair.Value);
        }

        return text;
    }

    private string ProcessText(string text)
    {
        Dictionary<string, string> noCompileFragments;

        text = ProcessSubstitutes(text);
        text = ExtractNoCompileFragments(text, out noCompileFragments);

        text = text.Replace("<if", "☺<if");
        text = text.Replace("<else", "☺<else");
        text = text.Replace("</if", "☺</if");
        //text = Regex.Replace( text, @"<session>.*?</session>", string.Empty, RegexOptions.IgnoreCase | RegexOptions.Singleline );
        text = ProcessIfs(text);

        Regex rarityRegex = new Regex("<value=talent.rarityName>");
        MatchCollection rarityMatches = rarityRegex.Matches(text);

        foreach (Match match in rarityMatches)
        {
            DBUIData uiData = DataBase.Get<DBUIData>(DBID.FromFileName(uiDataPath, false));
            List<TextRef> rarityValues = new List<TextRef>(uiData.rarityValue);
            string style = rarityValues[(int)curTalentInfo.Tal.rarity].ToString();
            text = text.Replace(match.Value, style);
        }

        Regex abilityNameRegex = new Regex("<value=talent.abilityName>");
        MatchCollection abilityNameMatches = abilityNameRegex.Matches(text);

        foreach (Match match in abilityNameMatches)
        {
            string abilityName = curTalentInfo.Tal.name.ToString();
            text = text.Replace(match.Value, abilityName);
        }

        Regex groupNameRegex = new Regex("<value=talent.groupName>");
        MatchCollection groupNameMatches = groupNameRegex.Matches(text);

        foreach (Match match in groupNameMatches)
        {
            string groupName = curTalentInfo.Group != null ? curTalentInfo.Group.name.ToString() : string.Empty;
            text = text.Replace(match.Value, groupName);
        }

        Regex groupDescRegex = new Regex("<value=talent.groupDescription>");
        MatchCollection groupDescMatches = groupDescRegex.Matches(text);

        foreach (Match match in groupDescMatches)
        {
            string groupDesc = curTalentInfo.Group != null ? curTalentInfo.Group.description.ToString() : string.Empty;
            text = text.Replace(match.Value, groupDesc);
        }

        Regex valueRegex = new Regex("<value=([^>]*)>");
        MatchCollection valueMatches = valueRegex.Matches(text);

        foreach (Match match in valueMatches)
        {
            string value = match.Groups[1].Value;
            string resultValue = string.Empty;

            //Trying to get string value;
            if (!TryToResolveStringValue(value, out resultValue))
            {
                //Float value found. Calculating "min-max" expression.
                _maximize = false;
                float minValue = ResolveValue(value);
                _maximize = true;
                float maxValue = ResolveValue(value);
                resultValue = (minValue == maxValue)
                                ? FormatFloat(minValue)
                                : string.Format("{0}-{1}", FormatFloat(Math.Min(minValue, maxValue)),
                                                              FormatFloat(Math.Max(minValue, maxValue)));
            }
            text = text.Replace(match.Value, resultValue);
        }

        text = InsertNoCompileFragments(text, noCompileFragments);

        return text;
    }

    private string FormatFloat(float f)
    {
        return f.ToString(CultureInfo.InvariantCulture);
    }
    #endregion
    /*
#insert_begin
*/
    #region Functions (this region duplicated in ExportItems.cs and FillCompiledTooltips.cs)
    private void InitalizeFunctions()
    {
        StringProcessor.AddFunction("pow", 2, (float[] args) => { return Convert.ToSingle(Math.Pow(args[0], args[1])); });
        StringProcessor.AddFunction("min", 2, (float[] args) => { return Math.Min(args[0], args[1]); });
        StringProcessor.AddFunction("max", 2, (float[] args) => { return Math.Max(args[0], args[1]); });
        StringProcessor.AddFunction("nt", 2, (float[] args) => { return args[1]; });

        StringProcessor.AddFunction("round", 1, (float[] args) => { return Convert.ToSingle(Math.Round(args[0])); });
        StringProcessor.AddFunction("f2l", 1, (float[] args) => { return Convert.ToSingle(Math.Round(args[0])); });
        StringProcessor.AddFunction("floor", 1, (float[] args) => { return Convert.ToSingle(Math.Floor(args[0])); });
        StringProcessor.AddFunction("ceil", 1, (float[] args) => { return Convert.ToSingle(Math.Ceiling(args[0])); });

        StringProcessor.AddFunction("tal", 1, GetTalent);
        StringProcessor.AddFunction("talconst", 2, GetTalentConst);
        StringProcessor.AddFunction("talconstNoCheck", 2, GetTalentConstNoCheck);
        StringProcessor.AddFunction("stalconst", 3, GetTalentConstWithDefault);
        StringProcessor.AddFunction("curtalconst", 1, GetCurrentTalentConst);
        StringProcessor.AddFunction("s", 3, Switch);

        StringProcessor.AddFunction("sender.GetHeroStatisticsValue", 1, GetZero);
        StringProcessor.AddFunction("sender.GetHeroAchievementCount", 1, GetZero);
        StringProcessor.AddFunction("sender.GetBaseIntellect", 0, GetBaseIntellect);
        StringProcessor.AddFunction("sender.CountApplicators", 3, GetZero);

        StringProcessor.AddFunction("abilityScale", 3, GetAbilityScale);
        StringProcessor.AddFunction("abilityScale", 4, GetAbilityScale);
        StringProcessor.AddFunction("refineScale", 2, GetRefineScale);
        StringProcessor.AddFunction("abilityScaleLife", 2, GetSecondArgument);
        StringProcessor.AddFunction("abilityScaleMaxLife", 2, GetSecondOrFirstArgument);
        StringProcessor.AddFunction("abilityScaleEnergy", 2, GetSecondArgument);
        StringProcessor.AddFunction("abilityScaleMaxEnergy", 2, GetSecondOrFirstArgument);
        StringProcessor.AddFunction("IsRecommended", 1, GetZero);
        StringProcessor.AddFunction("abilityScaleCustomLife", 3, GetAbilityScaleCustomLife);
        StringProcessor.AddFunction("abilityScaleCustomEnergy", 3, GetAbilityScaleCustomEnergy);
        StringProcessor.AddFunction("damageScale", 3, GetDamageScale);
        StringProcessor.AddFunction("damageScale", 4, GetDamageScale);
        StringProcessor.AddFunction("damageScaleCustomLife", 3, GetDamageScaleCustomLife);
        StringProcessor.AddFunction("damageScaleCustomEnergy", 3, GetDamageScaleCustomEnergy);
        StringProcessor.AddFunction("receiver.GetDamageDealt", 1, (float[] args) => { return 1; });
        StringProcessor.AddFunction("getTalentRefineRate", 2, GetTalentRefineRate);
    }

    #region TalentInfo
    public const string CLASS_TALENTS_PATH = "/Items/Talents/Class/";
    private class TalentInfo
    {
        public TalentInfo(DBTypes.Talent _talent)
        {
            Tal = _talent;
            Faction = EFaction.Neutral;
        }

        public Hero Hero { get; set; }
        public EFaction Faction { get; set; }
        public DBTypes.Talent Tal { get; private set; }
        public TalentGroup Group { get; set; }
        public bool HasClass { get { return Tal.DBId.FileName.StartsWith(CLASS_TALENTS_PATH); } }
    }
    #endregion

    #region Handlers
    public float GetTalentForce(DBTypes.Talent staticTalent, ForceParameters forceParams, float talentBaseStatBudget)
    {
        return GetTalentForce(staticTalent, forceParams, talentBaseStatBudget, 0);
    }
    public float GetTalentForce(DBTypes.Talent staticTalent, ForceParameters forceParams, float talentBaseStatBudget, int upgradeLevel)
    {
        float result = 0;
        if (staticTalent.rarity == ETalentRarity.Class)
        {
            float modifier = forceParams.classTalentLevelForceModifiers[staticTalent.minLevel];
            result = staticTalent.budget / (1.0f + modifier * 0.01f);
        }
        else
        {
            if (staticTalent.budget < 0.0f)
            {
                float modifier = forceParams.talentLevelForceModifiers[staticTalent.minLevel];
                float baseForce = talentBaseStatBudget * forceParams.talentForceModifier / 220.0f;
                float turForce = 1.0f + forceParams.talentLevelForceModifiers[staticTalent.minLevel] / 100.0f;
                float rarForce = forceParams.talentRarityForceModifiers[(int)staticTalent.rarity] / 100.0f;
                float starForce = 1.0f + forceParams.talentForceBonusPerStar * upgradeLevel / 100.0f;
                result = baseForce * turForce * rarForce * starForce / (1.0f + modifier * 0.01f);
            }
            else
            {
                float modifier = forceParams.talentLevelForceModifiers[staticTalent.minLevel];
                result = staticTalent.budget / (1.0f + modifier * 0.01f);
            }
        }
        return (float)Math.Floor(10 * result + 1e-4f);
    }

    private TalentKit GetTalentKit(DBTypes.Talent talent)
    {
        //If dictionary Talent to TalentKit not already cached
        if (_talentsToKits == null)
        {
            //Fetching talentKits list from AILogicParameters
            TalentKitList list = _aiLogicParams.talentKits.Get();
            if (list == null)
                return null;
            List<TalentKit> talentKits = new List<TalentKit>();
            foreach (var talentKit in list.kits)
                talentKits.Add(talentKit.Get());

            //Fetching Talent to TalentKit dictionary
            _talentsToKits = new Dictionary<DBTypes.Talent, TalentKit>();
            foreach (var kit in talentKits)
                foreach (var talentInKit in kit.talents)
                    if (!_talentsToKits.ContainsKey(talentInKit))
                        _talentsToKits.Add(talentInKit, kit);
                    else
                        Log.TraceWarning("Talent '{0}' defined more than one time in kit ('{1}', '{2}'). ",
                          talentInKit.DBId.ToString(), kit.DBId.ToString(), _talentsToKits[talentInKit].DBId.ToString());
        }

        TalentKit result = null;
        _talentsToKits.TryGetValue(talent, out result);
        return result;
    }

    private TalentPack GetTalentPack(DBTypes.Talent talent)
    {
        //If dictionary Talent to TalentPack not already cached
        if (_talentsToPacks == null)
        {
            //Fetching talentKits list from AILogicParameters
            TalentPackList list = _aiLogicParams.talentPacks.Get();
            if (list == null)
                return null;
            List<TalentPack> talentPacks = new List<TalentPack>();
            foreach (var talentPack in list.packs)
                talentPacks.Add(talentPack.Get());

            //Fetching Talent to TalentKit dictionary
            _talentsToPacks = new Dictionary<DBTypes.Talent, TalentPack>();
            foreach (var pack in talentPacks)
                foreach (var talentInPack in pack.talents)
                    if (!_talentsToPacks.ContainsKey(talentInPack))
                        _talentsToPacks.Add(talentInPack, pack);
                    else
                        Log.TraceWarning("Talent '{0}' defined more than one time in pack ('{1}', '{2}'). ",
                          talentInPack.DBId.ToString(), pack.DBId.ToString(), _talentsToPacks[talentInPack].DBId.ToString());
        }

        TalentPack result = null;
        _talentsToPacks.TryGetValue(talent, out result);
        return result;
    }

    private float GetTalent(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetTalent", args, 1);

        return 0.0f;
    }

    private float GetTalentConst(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetTalentConst", args, 2);

        return 0.0f;
    }

    private float GetTalentConstNoCheck(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetTalentConstNoCheck", args, 2);
#if TALENTS_DICT
        TalentInfo talentInfo;
        if (!talents.TryGetValue(args[0].stringValue, out talentInfo))
        {
            return 0.0f;
        }

        TalentInfo oldCurTalentInfo = curTalentInfo;
        curTalentInfo = talentInfo;
        Constants constants = new Constants(curTalentInfo);
        float result = constants.Get(args[1].stringValue);
        curTalentInfo = oldCurTalentInfo;
        return result;
#elif TALENTS_CONTAINER
      DBTypes.Talent talent = TalentsContainer.GetTalent( args[0].stringValue );
      if ( talent == null )
        return 0.0f;

      DBTypes.Ability oldTalent = AssignAbility( talent );
      float result = Evaluate( args[1].stringValue );
      AssignAbility( oldTalent );

      return result;
#endif
    }

    private float GetTalentConstWithDefault(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetTalentConstWithDefault", args, StringProcessor.ValueType.StringType, StringProcessor.ValueType.StringType, StringProcessor.ValueType.FloatType);

        return args[2].floatValue;
    }

    private float GetCurrentTalentConst(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetCurrentTalentConst", args, 1);

#if TALENTS_DICT
        Constants constants = new Constants(curTalentInfo);
        return constants.Get(args[0].stringValue);
#elif TALENTS_CONTAINER
      return Evaluate( args[0].stringValue );
#endif
    }

    private float Switch(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("Switch", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        return (args[0].floatValue != 0.0f) ? args[1].floatValue : args[2].floatValue;
    }

    private float GetZero(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        return 0;
    }

    private float GetBaseIntellect(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
#if TALENTS_DICT
        Constants constants = new Constants(curTalentInfo);
        return constants.Get("Intellect");
#elif TALENTS_CONTAINER
      return Evaluate( "Intellect" );
#endif
    }

    private float GetRefineScale(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetRefineScale", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);
        //#define abilityScale(stat,s50,s160)           max ( (stat) - 50.0f )  * ( (s160) - (s50) ) / 110.0f  + (s50), (s50) )
        float valueAtRefineLevel0 = args[0].floatValue;
        float incrementPerLevel = args[1].floatValue;

        return valueAtRefineLevel0 + incrementPerLevel * (_refineRate - 1.0f);
    }

    private float Lerp(float param, float minvalue, float maxvalue)
    {
        return minvalue * (1.0f - param) + maxvalue * param;
    }

    private float GetAbilityScale(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetAbilityScale", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        var value = args[0].floatValue;
        var s50 = args[1].floatValue;
        var s160 = args[2].floatValue;

        float result = ((s160 - s50) / (_scales.abilityScaleStatRight - _scales.abilityScaleStatLeft)) * (value - _scales.abilityScaleStatLeft) + s50;
        if (args.Length > 3 && args[3].floatValue == 0f)
            return result;

        return (int)Math.Round(result);
    }

    private float GetDamageScale(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetDamageScale", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);
        //#define damageScale(stat,s50,s160)    pMisc->GetAbilityScale( true, (stat), false, (s50), (s160) )
        //damageScale( sWill, 3.5, 26 )
        var value = args[0].floatValue;
        var min = args[1].floatValue;
        var max = args[2].floatValue;

        float result = ((max - min) / (_scales.damageScaleStatRight - _scales.damageScaleStatLeft)) * (value - _scales.damageScaleStatLeft) + min;

        if (args.Length > 3 && args[3].floatValue == 0f)
            return result;

        return (int)Math.Round(result);
    }

    private float GetSecondArgument(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetSecondArgument", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        return args[1].floatValue;
    }

    private float GetSecondOrFirstArgument(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetSecondOrFirstArgument", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        return _maximize ? args[1].floatValue : args[0].floatValue;
    }

    private float GetTalentRefineRate(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetTalentRefineRate", args, StringProcessor.ValueType.StringType, StringProcessor.ValueType.FloatType);

        return args[1].floatValue;
    }

    #region Custom scales calculations
    private enum ScaleMode
    {
        Stat = 0,
        Life,
        Energy
    }

    private float GetAbilityScaleCustom(bool isDamage, float statValue, float valueLeft, float valueRight, ScaleMode mode)
    {
        float statLeft = 0.0f, statRight = 0.0f;

        switch (mode)
        {
            case ScaleMode.Stat:
                statLeft = isDamage ? _scales.damageScaleStatLeft : _scales.abilityScaleStatLeft;
                statRight = isDamage ? _scales.damageScaleStatRight : _scales.abilityScaleStatRight;
                break;
            case ScaleMode.Life:
                statLeft = isDamage ? _scales.damageScaleLifeLeft : _scales.abilityScaleLifeLeft;
                statRight = isDamage ? _scales.damageScaleLifeRight : _scales.abilityScaleLifeRight;
                break;
            case ScaleMode.Energy:
                statLeft = isDamage ? _scales.damageScaleEnergyLeft : _scales.abilityScaleEnergyLeft;
                statRight = isDamage ? _scales.damageScaleEnergyRight : _scales.abilityScaleEnergyRight;
                break;
            default:
                Log.TraceError("Unknown ability scale mode '{0}'", mode);
                throw new Exception(string.Format("Unknown ability scale mode '{0}'", mode));
        }

        float result = Math.Max((statValue - statLeft) * (valueRight - valueLeft) /
                                  (statRight - statLeft) + valueLeft, valueLeft);

        return (int)Math.Round(result);
    }

    private float GetDamageScaleCustomLife(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetDamageScaleCustomLife", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        float stat = args[0].floatValue;
        float s50 = args[1].floatValue;
        float s160 = args[2].floatValue;

        return GetAbilityScaleCustom(true, stat, s50, s160, ScaleMode.Life);
    }

    private float GetDamageScaleCustomEnergy(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetDamageScaleCustomEnergy", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        float stat = args[0].floatValue;
        float s50 = args[1].floatValue;
        float s160 = args[2].floatValue;

        return GetAbilityScaleCustom(true, stat, s50, s160, ScaleMode.Energy);
    }

    private float GetAbilityScaleCustomLife(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetAbilityScaleCustomLife", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        float stat = args[0].floatValue;
        float s50 = args[1].floatValue;
        float s160 = args[2].floatValue;

        return GetAbilityScaleCustom(false, stat, s50, s160, ScaleMode.Life);
    }

    private float GetAbilityScaleCustomEnergy(StringProcessor.VariableHandler variables, StringProcessor.UniValue[] args)
    {
        CheckUniValueArgs("GetAbilityScaleCustomEnergy", args, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType, StringProcessor.ValueType.FloatType);

        float stat = args[0].floatValue;
        float s50 = args[1].floatValue;
        float s160 = args[2].floatValue;

        return GetAbilityScaleCustom(false, stat, s50, s160, ScaleMode.Energy);
    }
    #endregion
    #endregion

    #region Helpers
    private static void CheckUniValueArgs(string function, StringProcessor.UniValue[] args, params StringProcessor.ValueType[] types)
    {
        if (args.Length < types.Length)
            throw new ArgumentException(string.Format("Function \"{0}\" has {1} arguments but {2} used", function, types.Length, args.Length));

        for (int i = 0; i < types.Length; ++i)
        {
            if (args[i].bindedType != types[i])
                throw new ArgumentException(string.Format("Function \"{0}\" cannot convert {1} argument from {2} to {3}", function, i, args[i].bindedType, types[i]));
        }
    }

    private static void CheckUniValueArgs(string function, StringProcessor.UniValue[] args, int argsCount)
    {
        if (args.Length < argsCount)
            throw new ArgumentException(string.Format("Function \"{0}\" has {1} arguments but {2} used", function, argsCount, args.Length));

        for (int i = 0; i < argsCount; ++i)
        {
            if (args[i].bindedType != StringProcessor.ValueType.StringType)
                throw new ArgumentException(string.Format("Function \"{0}\" cannot convert {1} argument from {2} to {3}", function, i, args[i].bindedType, StringProcessor.ValueType.StringType));
        }
    }
    #endregion
    #endregion
    /*
#insert_end
*/
    public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
    {
        const string TALEN_PERSISTENCE_ID_PREFIX = "G";

        if (parameters.Length < 1)
        {
            Log.TraceMessage("At least one parameters must be setup. Provided: {0}", parameters.Length);
            yield return false;
        }

        Log.TraceMessage("Script started with parameters:");

        foreach (var scriptParam in parameters)
        {
            Log.TraceMessage(" --- {0}", scriptParam);
        }

        bool saveDB = true;
        bool searchingTlentByPersistenceId = false;

        string taletPersistentId = parameters[0].ToUpper();

        //check for compatibility
        if (!taletPersistentId.Contains("save") && taletPersistentId.StartsWith(TALEN_PERSISTENCE_ID_PREFIX))
        {
            searchingTlentByPersistenceId = true;
            Log.TraceMessage("Rendering tooltip for talent {0}", taletPersistentId);
        }

        _aiLogicParams = DataBase.Get<AILogicParameters>(DBID.FromFileName(aiLogicPath, false)).Get();
        if (_aiLogicParams == null)
        {
            Log.TraceError("AILogicParameters not found at '{0}'. Operation terminated.", aiLogicPath);
            yield return false;
        }
        _scales = _aiLogicParams.abilityAndDamageScalingParams;
        InitalizeFunctions();
        Log.TraceMessage("Collecting talents...");
        List<DBID> talentsDbids;
        ObjectsSelector.CollectObjects(app, "/Items/Talents", typeof(Talent), true, false, out talentsDbids);
        Log.TraceMessage("{0} talents collected", talentsDbids.Count);

        Log.TraceMessage("Collecting talents groups...");
        TalentGroupList talentGroupList = _aiLogicParams.talentGroups;
        Log.TraceMessage("{0} talents groups collected", talentGroupList.groups.Count);
        Log.TraceMessage("Getting group talents from talent sets...");
        foreach (var talentGroup in talentGroupList.groups)
        {
            foreach (var talentPtr in talentGroup.talents)
            {
                Talent talent = talentPtr.Get();
                if (talent != null)
                {
                    if (groupTalents.ContainsKey(talent))
                    {
                        Log.TraceError("Talent {0} already added to talent group. Will be used first founded group.", talent.name);
                        continue;
                    }
                    else
                        groupTalents.Add(talent, talentGroup);
                }
            }
        }
        Log.TraceMessage("{0} group talents found", groupTalents.Count);

        //Collecting heroes from HeroesDB
        Log.TraceMessage("Collecting heroes...");
        HeroesDB heroesdb = DataBase.Get<HeroesDB>(DBID.FromFileName("/Heroes/_.HRDB.xdb", false));
        Log.TraceMessage("{0} heroes collected", heroesdb.heroes.Count);
        Log.TraceMessage("Getting class talents from talent sets...");
        foreach ( var heroPtr in heroesdb.heroes )
        {
          if ( heroPtr == null )
            continue;
          Hero hero = heroPtr.Get();
          if ( hero != null )
          {
            if ( hero.defaultTalentsSets == null )
              continue;
            foreach ( var _telentsSet in hero.defaultTalentsSets )
            {
              TalentsSet telentsSet = _telentsSet.Get();
              if ( telentsSet == null || telentsSet.levels == null )
                continue;
              foreach ( var tsl in telentsSet.levels )
              {
                foreach ( var talentSlot in tsl.talents )
                {
                  Talent t = talentSlot.talent.Get();
                  if ( t != null && t.rarity == ETalentRarity.Class )
                  {
                    if ( heroesTalents.ContainsKey( t ) )
                    {
                      Log.TraceError( "In talents set of '{0}' founded talent '{1}', which already addded to talent set of '{2}'. Will be used first founded hero.",
                            telentsSet.DBId, t.name, heroesTalents[t].DBId );
                      continue;
                    }
                    else
                      heroesTalents.Add( t, hero );
                  }
                }
              }
            }
          }
        }

        Log.TraceMessage("{0} class talents found", heroesTalents.Count);

        foreach (var talentDbid in talentsDbids)
        {
            // filling talents
            Talent talent = DataBase.Get<Talent>(talentDbid);
            talents[talent.persistentId] = new TalentInfo(talent);
        }

        bool isTalentFound = false;
        
        foreach (DBID talentDbid in talentsDbids)
        {
            Talent talent = DataBase.Get<Talent>(talentDbid);

            if (searchingTlentByPersistenceId && string.Compare(taletPersistentId, talent.persistentId) == 0 )
            {
              isTalentFound = true;
            }
            else if(searchingTlentByPersistenceId)
            {
              isTalentFound = false;
              continue;
            }

            Log.TraceMessage("Processing {0}....", talentDbid.Name);

            curTalentInfo = new TalentInfo(talent);

            TalentGroup group;
            if (groupTalents.TryGetValue(talent, out group))
            {
                curTalentInfo.Group = group;
            }

            Hero h;
            if (heroesTalents.TryGetValue(talent, out h))
                curTalentInfo.Hero = h;
            else
                if (talent.rarity == ETalentRarity.Class)
                {
                    Log.TraceWarning("Talent '{0}' marked as class but was not founded in any heroes default talents sets. Add talent to any talent set or change Rarity field in editor.", talentDbid.Name);
                }

            #region PSMA modifiers per level calculations
            Log.TraceDebug("Calculating PSMA modifiers for all levels");
            Log.TraceDebug("Talent id={0}", talent.persistentId);
            talent.variativeMaxTalentStats.Clear();
            talent.variativeMinTalentStats.Clear();
            var pa = talent.passiveApplicators;
            foreach (var baseApplicator in pa)
            {
                var statApplicator = baseApplicator.Get() as PermanentStatModApplicator;
                if (statApplicator != null)
                {
                    if (String.IsNullOrEmpty(statApplicator.modifier.variable))
                    {

                        var modifier = statApplicator.modifier;
                        var name = modifier.addValue.sString.TrimStart('c');
                        if (statApplicator.customApplyType != ECustomApplyType.None)
                        {
                            Constants constants = new Constants(curTalentInfo);
                            //talent.variativeTalentStats.Add( new TalentStats() );
                            //var ts = talent.talentStats[talent.variativeTalentStats.Count - 1];
                            var ts = new TalentStats();

                            ts.stat = modifier.stat;
                            ts.addValueName = name;
                            for (int i = 1; i <= MAX_REFINE_RATE; i++)
                            {
                                _refineRate = i;
                                var statValue = constants.Get(name);
                                ts.values.Add(statValue);
                                Log.TraceDebug("level={0}: {1}={2}",
                                                i, modifier.stat, statValue);
                            }

                            if (statApplicator.customApplyType == ECustomApplyType.Minimize)
                                talent.variativeMinTalentStats.Add(ts);
                            if (statApplicator.customApplyType == ECustomApplyType.Maximize)
                                talent.variativeMaxTalentStats.Add(ts);
                        }
                    }
                }
            }
            Log.TraceDebug("Calculating PSMA modifiers for all levels Done");
            _refineRate = REFINE_RATE;
            #endregion

            #region Descriptions
            talent.compiledDescriptionA.Reset();
            talent.compiledDescriptionB.Reset();

            foreach (EFaction faction in Enum.GetValues(typeof(EFaction)))
            {
                if (curTalentInfo.HasClass && (faction == EFaction.Neutral) ||
                   !curTalentInfo.HasClass && (faction != EFaction.Neutral))
                    continue;

                if (talent.persistentId == String.Empty)
                    continue;
                curTalentInfo.Faction = faction;

                string description = ProcessText(talent.description.ToString());

                //writing to sepcified faction or to A, because in castle only not empty field will be used
                if (faction == EFaction.Burn)
                    //if adornian docts
                    talent.compiledDescriptionB.FromString(description);
                else
                    //if docts or no faction writing to
                    talent.compiledDescriptionA.FromString(description);
            }
            #endregion

            if (isTalentFound)
            {
                break;
            }
        }

        if (saveDB)
        {
           if (searchingTlentByPersistenceId && isTalentFound)
            Log.TraceMessage("Saving {0} item...", taletPersistentId);
          else 
            Log.TraceMessage("Saving {0} items...", talentsDbids.Count);
            
          if(searchingTlentByPersistenceId && !isTalentFound)
            Log.TraceMessage("Talent {0} not found.", taletPersistentId);
          else
          {            
            DataBase.Store();
            Log.TraceMessage("Succesfully saved");
          }
        }
        
        yield return true;
    }
}

