/*
#about Компиляция условий для скриптов
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
#ref EditorPlugins.dll
#ref GOLDEngine.dll
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using EditorPlugins.Importer.Texture;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;
using System.CodeDom.Compiler;

public class CompileQuestUtils
{
    #region Parser enums

    enum SymbolConstants : int
    {
        SYMBOL_EOF          =  0, // (EOF)
        SYMBOL_ERROR        =  1, // (Error)
        SYMBOL_COMMENT      =  2, // Comment
        SYMBOL_NEWLINE      =  3, // NewLine
        SYMBOL_WHITESPACE   =  4, // Whitespace
        SYMBOL_MINUSMINUS   =  5, // '--'
        SYMBOL_EXCLAMEQ     =  6, // '!='
        SYMBOL_LPAREN       =  7, // '('
        SYMBOL_RPAREN       =  8, // ')'
        SYMBOL_COMMA        =  9, // ','
        SYMBOL_DOT          = 10, // '.'
        SYMBOL_LBRACKET     = 11, // '['
        SYMBOL_RBRACKET     = 12, // ']'
        SYMBOL_PLUSEQ       = 13, // '+='
        SYMBOL_LT           = 14, // '<'
        SYMBOL_LTEQ         = 15, // '<='
        SYMBOL_EQ           = 16, // '='
        SYMBOL_MINUSEQ      = 17, // '-='
        SYMBOL_EQEQ         = 18, // '=='
        SYMBOL_GT           = 19, // '>'
        SYMBOL_GTEQ         = 20, // '>='
        SYMBOL_AND          = 21, // and
        SYMBOL_DECIMAL      = 22, // decimal
        SYMBOL_DO           = 23, // do
        SYMBOL_ELSE         = 24, // else
        SYMBOL_END          = 25, // end
        SYMBOL_FLOAT        = 26, // float
        SYMBOL_FOREACH      = 27, // foreach
        SYMBOL_IF           = 28, // if
        SYMBOL_IN           = 29, // in
        SYMBOL_NOT          = 30, // not
        SYMBOL_OR           = 31, // or
        SYMBOL_RETURN       = 32, // return
        SYMBOL_STRING       = 33, // string
        SYMBOL_THEN         = 34, // then
        SYMBOL_VARIABLE     = 35, // variable
        SYMBOL_ARGUMENTS    = 36, // <arguments>
        SYMBOL_CONDITION    = 37, // <condition>
        SYMBOL_CONDITIONS   = 38, // <conditions>
        SYMBOL_EXPRESSION   = 39, // <expression>
        SYMBOL_EXPRESSIONS  = 40, // <expressions>
        SYMBOL_FOREACH2     = 41, // <foreach>
        SYMBOL_FUNCTION     = 42, // <function>
        SYMBOL_IF2          = 43, // <if>
        SYMBOL_INDEX_MEMBER = 44, // <index_member>
        SYMBOL_MEMBER       = 45, // <member>
        SYMBOL_OPERATION    = 46, // <operation>
        SYMBOL_OPERATOR     = 47, // <operator>
        SYMBOL_PROPERTY     = 48, // <property>
        SYMBOL_RETURN2      = 49, // <return>
        SYMBOL_VALUE        = 50  // <value>
    };

    enum RuleConstants : int
    {
        RULE_PROPERTY_DOT_VARIABLE              =  0, // <property> ::= <property> '.' variable
        RULE_PROPERTY_VARIABLE                  =  1, // <property> ::= variable
        RULE_FUNCTION_LPAREN_RPAREN             =  2, // <function> ::= <property> '(' <arguments> ')'
        RULE_FUNCTION_LPAREN_RPAREN2            =  3, // <function> ::= <property> '(' ')'
        RULE_MEMBER                             =  4, // <member> ::= <property>
        RULE_MEMBER2                            =  5, // <member> ::= <function>
        RULE_MEMBER_DOT                         =  6, // <member> ::= <member> '.' <function>
        RULE_MEMBER_DOT2                        =  7, // <member> ::= <member> '.' <property>
        RULE_MEMBER3                            =  8, // <member> ::= <member> <index_member>
        RULE_INDEX_MEMBER_LBRACKET_RBRACKET     =  9, // <index_member> ::= '[' <member> ']'
        RULE_INDEX_MEMBER_DOT                   = 10, // <index_member> ::= <index_member> '.' <member>
        RULE_VALUE_DECIMAL                      = 11, // <value> ::= decimal
        RULE_VALUE_FLOAT                        = 12, // <value> ::= float
        RULE_VALUE_STRING                       = 13, // <value> ::= string
        RULE_VALUE                              = 14, // <value> ::= <member>
        RULE_ARGUMENTS_COMMA                    = 15, // <arguments> ::= <arguments> ',' <value>
        RULE_ARGUMENTS                          = 16, // <arguments> ::= <value>
        RULE_CONDITION_EQEQ                     = 17, // <condition> ::= <value> '==' <value>
        RULE_CONDITION_GTEQ                     = 18, // <condition> ::= <value> '>=' <value>
        RULE_CONDITION_LTEQ                     = 19, // <condition> ::= <value> '<=' <value>
        RULE_CONDITION_EXCLAMEQ                 = 20, // <condition> ::= <value> '!=' <value>
        RULE_CONDITION_LT                       = 21, // <condition> ::= <value> '<' <value>
        RULE_CONDITION_GT                       = 22, // <condition> ::= <value> '>' <value>
        RULE_CONDITION                          = 23, // <condition> ::= <value>
        RULE_OPERATOR_EQ                        = 24, // <operator> ::= '='
        RULE_OPERATOR_PLUSEQ                    = 25, // <operator> ::= '+='
        RULE_OPERATOR_MINUSEQ                   = 26, // <operator> ::= '-='
        RULE_CONDITIONS                         = 27, // <conditions> ::= <condition>
        RULE_CONDITIONS_NOT                     = 28, // <conditions> ::= not <conditions>
        RULE_CONDITIONS_OR                      = 29, // <conditions> ::= <conditions> or <conditions>
        RULE_CONDITIONS_AND                     = 30, // <conditions> ::= <conditions> and <conditions>
        RULE_CONDITIONS_LPAREN_RPAREN           = 31, // <conditions> ::= '(' <conditions> ')'
        RULE_EXPRESSIONS                        = 32, // <expressions> ::= <expressions> <expression>
        RULE_EXPRESSIONS2                       = 33, // <expressions> ::=
        RULE_EXPRESSION                         = 34, // <expression> ::= <return>
        RULE_EXPRESSION2                        = 35, // <expression> ::= <foreach>
        RULE_EXPRESSION3                        = 36, // <expression> ::= <if>
        RULE_EXPRESSION4                        = 37, // <expression> ::= <operation>
        RULE_FOREACH_FOREACH_VARIABLE_IN_DO_END = 38, // <foreach> ::= foreach variable in <member> do <expressions> end
        RULE_IF_IF_THEN_END                     = 39, // <if> ::= if <conditions> then <expressions> end
        RULE_IF_IF_THEN_ELSE_END                = 40, // <if> ::= if <conditions> then <expressions> else <expressions> end
        RULE_RETURN_RETURN                      = 41, // <return> ::= return <value>
        RULE_OPERATION                          = 42  // <operation> ::= <value> <operator> <value>
    };

    #endregion

    static GOLD.Parser parser = new GOLD.Parser();
    static GOLD.Reduction root = null;
    private const string GrammaFileName = "../Tools/Scripts/QuestConditionParser/simple.egt";

    public static bool InitGramma()
    {
        if (!File.Exists(GrammaFileName))
        {
            Log.TraceError("Gramma file {0} is not found", GrammaFileName);
            return false;
        }
        if (!parser.LoadTables(GrammaFileName))
        {
            Log.TraceError("Gramma file {0} is not valid", GrammaFileName);
            return false;
        }
        parser.TrimReductions = false;
        return true;
    }

    public static bool FillConditionCode(StringBuilder csCode, StringBuilder pyCode, ModelDataCondition cond, string id)
    {
        if (!ParseCondition(cond.code))
        {
            return false;
        }

        csCode.AppendFormat("\t\tprivate static int Condition{0}( IScriptData data )\r\n", id);
        csCode.Append("\t\t{\r\n");
        csCode.AppendLine("\t\t\tvar Heroes = data.Heroes;");
        csCode.AppendLine("\t\t\tvar Buildings = data.Buildings;");
        csCode.AppendLine("\t\t\tvar Lord = data.Lord;");
        csCode.AppendLine("\t\t\tint result = 0;");
        if (root.Count() != 0)
            ProcessConditionTree(csCode, null, root, 3);
        else
            csCode.AppendLine("\t\t\treturn 0;");
        csCode.AppendLine("\t\t}\r\n");

        pyCode.AppendFormat("def Condition( modeldata, **kwargs ):\r\n", id);
        pyCode.AppendLine("\tHeroes = modeldata.Heroes");
        pyCode.AppendLine("\tBuildings = modeldata.Buildings");
        pyCode.AppendLine("\tLord = modeldata.Lord");
        pyCode.AppendLine("\tresult = 0");
        if (root.Count() != 0)
            ProcessConditionTree(null, pyCode, root, 2);
        else
            pyCode.AppendLine("\treturn 0");

        return true;
    }

    private static bool ParseCondition(string code)
    {
        parser.Open(ref code);
        bool failed = false;
        bool accepted = false;
        while (!failed && !accepted)
        {
            switch (parser.Parse())
            {
                case GOLD.ParseMessage.LexicalError:
                case GOLD.ParseMessage.SyntaxError:
                case GOLD.ParseMessage.InternalError:
                case GOLD.ParseMessage.NotLoadedError:
                case GOLD.ParseMessage.GroupError:
                    failed = true;
                    break;
                case GOLD.ParseMessage.Accept:
                    root = (GOLD.Reduction)parser.CurrentReduction;
                    accepted = true;
                    break;
            }
        }
        return accepted;
    }

    private static void ProcessConditionTree(StringBuilder csCode, StringBuilder pyCode, GOLD.Reduction reduction, int indent)
    {
        for (int i = 0; i < reduction.Count(); i++)
        {
            int tabOffset = 0;
            switch (reduction[i].Type())
            {
                case GOLD.SymbolType.Nonterminal: //правило
                    GOLD.Reduction branch = (GOLD.Reduction)reduction[i].Data;
                    if (csCode != null)
                    {
                        string prefix = CreatePrefixFromNonterminalCS(branch, indent);//в частности начинается ли новый логический блок
                        if (prefix != null)
                        {
                            csCode.Append(prefix);
                            tabOffset++;
                        }
                    }

                    if (pyCode != null)
                    {
                        string prefix = CreatePrefixFromNonterminalPY(branch, indent);
                        if (prefix != null)
                        {
                            pyCode.Append(prefix);
                            tabOffset++;
                        }
                    }

                    ProcessConditionTree(csCode, pyCode, branch, indent + tabOffset);
                    if (csCode != null)
                    {
                        string postfix = CreatePostfixFromNonterminalCS(branch, indent);//в частности надо ли переводить строку
                        if (postfix != null)
                        {
                            csCode.Append(postfix);
                        }
                    }
                    if (pyCode != null)
                    {
                        string postfix = CreatePostfixFromNonterminalPY(branch, indent);
                        if (postfix != null)
                        {
                            pyCode.Append(postfix);
                        }
                    }
                    break;

                default:
                    if (csCode != null)
                    {
                        string leaf = CreateReplacementFromTerminalCS(reduction[i], indent);
                        if (leaf == null)
                            leaf = (string)reduction[i].Data;
                        csCode.Append(leaf);
                    }
                    if (pyCode != null)
                    {
                        string leaf = CreateReplacementFromTerminalPY(reduction[i], indent);
                        if (leaf == null)
                            leaf = (string)reduction[i].Data;
                        pyCode.Append(leaf);
                    }
                    break;
            }
        }
    }

    private static string TABx(int count)
    {
        StringBuilder tabs = new StringBuilder();
        for (int i = 0; i < count; i++)
        {
            tabs.Append("\t");
        }
        return tabs.ToString();
    }

    #region Replacement for tokens, C#

    private static string CreateReplacementFromTerminalCS(GOLD.Token token, int indent)
    {
        switch (token.Parent.TableIndex())
        {
            case (int)SymbolConstants.SYMBOL_COMMA:
                return string.Format("{0} ", token.Data);

            case (int)SymbolConstants.SYMBOL_AND:
                return " && ";

            case (int)SymbolConstants.SYMBOL_DO:
                return string.Format(")\r\n{0}{{\r\n", TABx(indent - 1));

            case (int)SymbolConstants.SYMBOL_END:
                return string.Format("{0}}}", TABx(indent - 1));

            case (int)SymbolConstants.SYMBOL_FOREACH:
                return string.Format("{0}(var ", token.Data);

            case (int)SymbolConstants.SYMBOL_IF:
                return string.Format("{0}(", token.Data);

            case (int)SymbolConstants.SYMBOL_IN:
                return string.Format(" {0} ", token.Data);

            case (int)SymbolConstants.SYMBOL_NOT:
                return "!";

            case (int)SymbolConstants.SYMBOL_OR:
                return " || ";

            case (int)SymbolConstants.SYMBOL_RETURN:
                return string.Format("{0} ", token.Data);

            case (int)SymbolConstants.SYMBOL_THEN:
                return string.Format(")\r\n{0}{{\r\n", TABx(indent - 1));

            default:
                return null;
        }
    }

    private static string CreatePrefixFromNonterminalCS(GOLD.Reduction token, int indent)
    {
        switch (token.Parent.TableIndex())
        {
            case (int)RuleConstants.RULE_FOREACH_FOREACH_VARIABLE_IN_DO_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_ELSE_END:
            case (int)RuleConstants.RULE_RETURN_RETURN:
            case (int)RuleConstants.RULE_OPERATION:
                return TABx(indent);

            default:
                return null;
        }
    }

    private static string CreatePostfixFromNonterminalCS(GOLD.Reduction token, int indent)
    {
        switch (token.Parent.TableIndex())
        {
            case (int)RuleConstants.RULE_FOREACH_FOREACH_VARIABLE_IN_DO_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_ELSE_END:
            case (int)RuleConstants.RULE_RETURN_RETURN:
            case (int)RuleConstants.RULE_OPERATION:
                return ";\r\n";

            default:
                return null;
        }
    }

    #endregion

    #region Replacement for tokens, Python

    private static string CreateReplacementFromTerminalPY(GOLD.Token token, int indent)
    {
        switch (token.Parent.TableIndex())
        {
            case (int)SymbolConstants.SYMBOL_MINUSMINUS:
                //'--'
                //todo: Create a new object that corresponds to the symbol
                return "#";

            case (int)SymbolConstants.SYMBOL_COMMA:
                //','
                //todo: Create a new object that corresponds to the symbol
                return string.Format("{0} ", token.Data);

            case (int)SymbolConstants.SYMBOL_AND:
                //and
                //todo: Create a new object that corresponds to the symbol
                return " and ";

            case (int)SymbolConstants.SYMBOL_DO:
                //do
                //todo: Create a new object that corresponds to the symbol
                return string.Format(":\r\n");

            case (int)SymbolConstants.SYMBOL_END:
                //end
                //todo: Create a new object that corresponds to the symbol
                return "";

            case (int)SymbolConstants.SYMBOL_FOREACH:
                //foreach
                //todo: Create a new object that corresponds to the symbol
                return "for ";

            case (int)SymbolConstants.SYMBOL_IF:
                //if
                //todo: Create a new object that corresponds to the symbol
                return string.Format("{0} ", token.Data);

            case (int)SymbolConstants.SYMBOL_IN:
                //in
                //todo: Create a new object that corresponds to the symbol
                return string.Format(" {0} ", token.Data);

            case (int)SymbolConstants.SYMBOL_NOT:
                //not
                //todo: Create a new object that corresponds to the symbol
                return " not ";

            case (int)SymbolConstants.SYMBOL_OR:
                //or
                //todo: Create a new object that corresponds to the symbol
                return " or ";

            case (int)SymbolConstants.SYMBOL_RETURN:
                //return
                //todo: Create a new object that corresponds to the symbol
                return string.Format("{0} ", token.Data);

            case (int)SymbolConstants.SYMBOL_THEN:
                //then
                //todo: Create a new object that corresponds to the symbol
                return string.Format(":\r\n");

            case (int)SymbolConstants.SYMBOL_VARIABLE:
                //variable
                //todo: Create a new object that corresponds to the symbol
                if ( token.Data.ToString() == "Count" )
                {
                  return string.Format( "{0}()", token.Data );
                }
                return null;

            default:
                return null;
        }
    }

    private static string CreatePrefixFromNonterminalPY(GOLD.Reduction token, int indent)
    {
        switch (token.Parent.TableIndex())
        {
            case (int)RuleConstants.RULE_FOREACH_FOREACH_VARIABLE_IN_DO_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_ELSE_END:
            case (int)RuleConstants.RULE_RETURN_RETURN:
            case (int)RuleConstants.RULE_OPERATION:
                return TABx(indent - 1);

            default:
                return null;

        }
    }

    private static string CreatePostfixFromNonterminalPY(GOLD.Reduction token, int indent)
    {
        switch (token.Parent.TableIndex())
        {
            case (int)RuleConstants.RULE_FOREACH_FOREACH_VARIABLE_IN_DO_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_END:
            case (int)RuleConstants.RULE_IF_IF_THEN_ELSE_END:
                return "";

            case (int)RuleConstants.RULE_RETURN_RETURN:
            case (int)RuleConstants.RULE_OPERATION:
                return "\r\n";

            default:
                return null;
        }
    }

    #endregion
}