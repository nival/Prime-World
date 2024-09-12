using System;
using System.Collections.Generic;
using System.Text;
using CodeEngine.Framework.QueryBuilder.Enums;

//
// Class: OrderByClause
// Copyright 2006 by Ewout Stortenbeker
// Email: 4ewout@gmail.com
//
// This class is part of the CodeEngine Framework.
// You can download the framework DLL at http://www.code-engine.com/
//
namespace CodeEngine.Framework.QueryBuilder
{
    /// <summary>
    /// Represents a ORDER BY clause to be used with SELECT statements
    /// </summary>
    public struct OrderByClause
    {
        public string FieldName;
        public Sorting SortOrder;
        public OrderByClause(string field)
        {
            FieldName = field;
            SortOrder = Sorting.Ascending;
        }
        public OrderByClause(string field, Sorting order)
        {
            FieldName = field;
            SortOrder = order;
        }
    }
}
