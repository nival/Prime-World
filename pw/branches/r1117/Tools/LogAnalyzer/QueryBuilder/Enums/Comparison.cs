
//
// Enum: Comparison
// Copyright 2006 by Ewout Stortenbeker
// Email: 4ewout@gmail.com
//
// This enum is part of the CodeEngine Framework.
// You can download the framework DLL at http://www.code-engine.com/
//
namespace CodeEngine.Framework.QueryBuilder.Enums
{
    /// <summary>
    /// Represents comparison operators for WHERE, HAVING and JOIN clauses
    /// </summary>
    public enum Comparison
    {
        Equals,
        NotEquals,
        Like,
        NotLike,
        GreaterThan,
        GreaterOrEquals,
        LessThan,
        LessOrEquals,
        In,
        Contains,
        NotContains,
    }
}
