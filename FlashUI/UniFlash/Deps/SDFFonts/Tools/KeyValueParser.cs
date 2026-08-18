using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using UnityEngine;

namespace SDFFonts.Tools
{
    public class KeyValueParser
    {
        private const string pairDefinition = @"(\w+)=(-?\d+)";

        private Dictionary<string, int> _values = new Dictionary<string, int>();
        private Regex _pairRegEx = new Regex( pairDefinition );

        public void Fill(string line)
        {
            Match match = _pairRegEx.Match(line);
            while (match.Success)
            {
                string key = match.Groups[1].Captures[0].Value;
                string valueStr = match.Groups[2].Captures[0].Value;
                int value = 0;
                try
                {
                    value = Convert.ToInt32(valueStr);
                }
                catch (FormatException e)
                {
                    Debug.LogErrorFormat("Wrong integer value for {0}: {1}, {2}", key, valueStr, e.Message);
                }
                _values[key] = value;
                match = match.NextMatch();
            }
        }

        public int GetValue(string key, int defaultVal)
        {
            int result;
            return _values.TryGetValue( key, out result) ? result : defaultVal;
        }
    }
}