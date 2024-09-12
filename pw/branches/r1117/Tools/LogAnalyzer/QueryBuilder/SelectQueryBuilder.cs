using System;
using System.Collections.Generic;
using System.Text;
using System.Data.Common;
using CodeEngine.Framework.QueryBuilder.Enums;

//
// Class: SelectQueryBuilder
// Copyright 2006 by Ewout Stortenbeker
// Email: 4ewout@gmail.com
//
// This class is part of the CodeEngine Framework. This framework also contains
// the UpdateQueryBuilder, InsertQueryBuilder and DeleteQueryBuilder.
// You can download the framework DLL at http://www.code-engine.com/
// 
namespace CodeEngine.Framework.QueryBuilder
{
    public class SelectQueryBuilder : IQueryBuilder
    {
        protected bool _distinct = false;
        protected TopClause _topClause = new TopClause(100, TopUnit.Percent);
        protected List<string> _selectedColumns = new List<string>();	// array of string
        protected List<string> _selectedTables = new List<string>();	// array of string
        protected List<JoinClause> _joins = new List<JoinClause>();	// array of JoinClause
        protected WhereStatement _whereStatement = new WhereStatement();
        protected List<OrderByClause> _orderByStatement = new List<OrderByClause>();	// array of OrderByClause
        protected List<string> _groupByColumns = new List<string>();		// array of string
        protected WhereStatement _havingStatement = new WhereStatement();

        internal WhereStatement WhereStatement
        {
            get { return _whereStatement; }
            set { _whereStatement = value; }
        }

        public SelectQueryBuilder() { }
        public SelectQueryBuilder(DbProviderFactory factory)
        {
            _dbProviderFactory = factory;
        }

        private DbProviderFactory _dbProviderFactory;
        public void SetDbProviderFactory(DbProviderFactory factory)
        {
            _dbProviderFactory = factory;
        }

        public bool Distinct
        {
            get { return _distinct; }
            set { _distinct = value; }
        }

        public int TopRecords
        {
            get { return _topClause.Quantity; }
            set
            {
                _topClause.Quantity = value;
                _topClause.Unit = TopUnit.Records;
            }
        }
        public TopClause TopClause
        {
            get { return _topClause; }
            set { _topClause = value; }
        }

        public string[] SelectedColumns
        {
            get
            {
                if (_selectedColumns.Count > 0)
                    return _selectedColumns.ToArray();
                else
                    return new string[1] { "*" };
            }
        }
        public string[] SelectedTables
        {
            get { return _selectedTables.ToArray(); }
        }

        public void SelectAllColumns()
        {
            _selectedColumns.Clear();
        }
        public void SelectCount()
        {
            SelectColumn("count(1)");
        }
        public void SelectColumn(string column)
        {
            _selectedColumns.Clear();
            _selectedColumns.Add(column);
        }
        public void SelectColumns(params string[] columns)
        {
            _selectedColumns.Clear();
            foreach (string column in columns)
            {
                _selectedColumns.Add(column);
            }
        }
        public void SelectFromTable(string table)
        {
            _selectedTables.Clear();
            _selectedTables.Add(table);
        }
        public void SelectFromTables(params string[] tables)
        {
            _selectedTables.Clear();
            foreach (string Table in tables)
            {
                _selectedTables.Add(Table);
            }
        }
        public void AddJoin(JoinClause newJoin)
        {
            _joins.Add(newJoin);
        }
        public void AddJoin(JoinType join, string toTableName, string toColumnName, Comparison @operator, string fromTableName, string fromColumnName)
        {
            JoinClause NewJoin = new JoinClause(join, toTableName, toColumnName, @operator, fromTableName, fromColumnName);
            _joins.Add(NewJoin);
        }

        public WhereStatement Where
        {
            get { return _whereStatement; }
            set { _whereStatement = value; }
        }

        public void AddWhere(WhereClause clause) { AddWhere(clause, 1); }
        public void AddWhere(WhereClause clause, int level)
        {
            _whereStatement.Add(clause, level);
        }
        public WhereClause AddWhere(string field, Comparison @operator, object compareValue) { return AddWhere(field, @operator, compareValue, 1); }
        public WhereClause AddWhere(Enum field, Comparison @operator, object compareValue) { return AddWhere(field.ToString(), @operator, compareValue, 1); }
        public WhereClause AddWhere(string field, Comparison @operator, object compareValue, int level)
        {
            WhereClause NewWhereClause = new WhereClause(field, @operator, compareValue);
            _whereStatement.Add(NewWhereClause, level);
            return NewWhereClause;
        }

        public void AddOrderBy(OrderByClause clause)
        {
            _orderByStatement.Add(clause);
        }
        public void AddOrderBy(Enum field, Sorting order) { this.AddOrderBy(field.ToString(), order); }
        public void AddOrderBy(string field, Sorting order)
        {
            OrderByClause NewOrderByClause = new OrderByClause(field, order);
            _orderByStatement.Add(NewOrderByClause);
        }

        public void GroupBy(params string[] columns)
        {
            foreach (string Column in columns)
            {
                _groupByColumns.Add(Column);
            }
        }

        public WhereStatement Having
        {
            get { return _havingStatement; }
            set { _havingStatement = value; }
        }

        public void AddHaving(WhereClause clause) { AddHaving(clause, 1); }
        public void AddHaving(WhereClause clause, int level)
        {
            _havingStatement.Add(clause, level);
        }
        public WhereClause AddHaving(string field, Comparison @operator, object compareValue) { return AddHaving(field, @operator, compareValue, 1); }
        public WhereClause AddHaving(Enum field, Comparison @operator, object compareValue) { return AddHaving(field.ToString(), @operator, compareValue, 1); }
        public WhereClause AddHaving(string field, Comparison @operator, object compareValue, int level)
        {
            WhereClause NewWhereClause = new WhereClause(field, @operator, compareValue);
            _havingStatement.Add(NewWhereClause, level);
            return NewWhereClause;
        }

        public DbCommand BuildCommand()
        {
            return (DbCommand)this.BuildQuery(true);
        }

        public string BuildQuery()
        {
            return (string)this.BuildQuery(false);
        }

        /// <summary>
        /// Builds the select query
        /// </summary>
        /// <returns>Returns a string containing the query, or a DbCommand containing a command with parameters</returns>
        private object BuildQuery(bool buildCommand)
        {
            if (buildCommand && _dbProviderFactory == null)
                throw new Exception("Cannot build a command when the Db Factory hasn't been specified. Call SetDbProviderFactory first.");

            DbCommand command = null;
            if (buildCommand)
                command = _dbProviderFactory.CreateCommand();

            string Query = "SELECT ";

            // Output Distinct
            if (_distinct)
            {
                Query += "DISTINCT ";
            }

            // Output Top clause
            if (!(_topClause.Quantity == 100 & _topClause.Unit == TopUnit.Percent))
            {
                Query += "TOP " + _topClause.Quantity;
                if (_topClause.Unit == TopUnit.Percent)
                {
                    Query += " PERCENT";
                }
                Query += " ";
            }

            // Output column names
            if (_selectedColumns.Count == 0)
            {
                if (_selectedTables.Count == 1)
                    Query += "*"; // By default only select * from the table that was selected. If there are any joins, it is the responsibility of the user to select the needed columns.
            }
            else
            {
                foreach (string ColumnName in _selectedColumns)
                {
                    Query += ColumnName + ',';
                }
                Query = Query.TrimEnd(','); // Trim de last comma inserted by foreach loop
                Query += ' ';
            }
            // Output table names
            if (_selectedTables.Count > 0)
            {
                Query += " FROM ";
                foreach (string TableName in _selectedTables)
                {
                    Query += TableName + ',';
                }
                Query = Query.TrimEnd(','); // Trim de last comma inserted by foreach loop
                Query += ' ';
            }

            // Output joins
            if (_joins.Count > 0)
            {
                foreach (JoinClause Clause in _joins)
                {
                    string JoinString = "";
                    switch (Clause.JoinType)
                    {
                        case JoinType.InnerJoin: JoinString = "INNER JOIN"; break;
                        case JoinType.OuterJoin: JoinString = "OUTER JOIN"; break;
                        case JoinType.LeftJoin: JoinString = "LEFT JOIN"; break;
                        case JoinType.RightJoin: JoinString = "RIGHT JOIN"; break;
                    }
                    JoinString += " " + Clause.ToTable + " ON ";
                    JoinString += WhereStatement.CreateComparisonClause(Clause.FromTable + '.' + Clause.FromColumn, Clause.ComparisonOperator, new SqlLiteral(Clause.ToTable + '.' + Clause.ToColumn));
                    Query += JoinString + ' ';
                }
            }

            // Output where statement
            if (_whereStatement.ClauseLevels > 0)
            {
                if (buildCommand)
                    Query += " WHERE " + _whereStatement.BuildWhereStatement(true, ref command);
                else
                    Query += " WHERE " + _whereStatement.BuildWhereStatement();
            }

            // Output GroupBy statement
            if (_groupByColumns.Count > 0)
            {
                Query += " GROUP BY ";
                foreach (string Column in _groupByColumns)
                {
                    Query += Column + ',';
                }
                Query = Query.TrimEnd(',');
                Query += ' ';
            }

            // Output having statement
            if (_havingStatement.ClauseLevels > 0)
            {
                // Check if a Group By Clause was set
                if (_groupByColumns.Count == 0)
                {
                    throw new Exception("Having statement was set without Group By");
                }
                if (buildCommand)
                    Query += " HAVING " + _havingStatement.BuildWhereStatement(true, ref command);
                else
                    Query += " HAVING " + _havingStatement.BuildWhereStatement();
            }

            // Output OrderBy statement
            if (_orderByStatement.Count > 0)
            {
                Query += " ORDER BY ";
                foreach (OrderByClause Clause in _orderByStatement)
                {
                    string OrderByClause = "";
                    switch (Clause.SortOrder)
                    {
                        case Sorting.Ascending:
                            OrderByClause = Clause.FieldName + " ASC"; break;
                        case Sorting.Descending:
                            OrderByClause = Clause.FieldName + " DESC"; break;
                    }
                    Query += OrderByClause + ',';
                }
                Query = Query.TrimEnd(','); // Trim de last AND inserted by foreach loop
                Query += ' ';
            }

            if (buildCommand)
            {
                // Return the build command
                command.CommandText = Query;
                return command;
            }
            else
            {
                // Return the built query
                return Query;
            }
        }
    }

}
