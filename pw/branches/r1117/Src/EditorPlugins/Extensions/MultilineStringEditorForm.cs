using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Drawing;

namespace EditorPlugins.Extensions
{
	public partial class MultilineStringEditorForm : Form
	{
		private const string KEYWORDS_FILE = @"..\Profiles\keywords.txt";	
		private readonly Regex keywordsRegex = new Regex( @"\w+" );
		private readonly Regex stringsRegex = new Regex( @"(?<=^|\W)("".*?"")(?=$|\W)", RegexOptions.Singleline );
		private readonly string[] highlight = new string[0];

		public MultilineStringEditorForm()
		{
			InitializeComponent();
		}

        public MultilineStringEditorForm(string _code)
            : this()
		{
			if(File.Exists(KEYWORDS_FILE))
				highlight = File.ReadAllLines(KEYWORDS_FILE);

            Code = _code;
		}

		public string Code 
		{
            get { return rtbCode.Text; }
			set 
			{
        rtbCode.Text = value;
        UpdateHighlight();
        //rtbCode.SelectionStart = rtbCode.Text.Length;
			}
		}

		private void OnTextChanged( object sender, EventArgs e )
		{
			UpdateHighlight();
		}

		private void UpdateHighlight()
		{
      //ClearTextColor();

      ////подсвечиваем клучевые слова
      //      foreach (Match keywordMatch in keywordsRegex.Matches(rtbCode.Text))
      //{
      //  if ( keywordMatch.Success && IsNeedHighlighting( keywordMatch.Value ) )
      //    SetTextColor( keywordMatch.Index, keywordMatch.Value.Length, Color.Blue );
      //}

      ////подсвечиваем строки
      //      foreach (Match stringMatch in stringsRegex.Matches(rtbCode.Text))
      //{
      //  if ( stringMatch.Success )
      //    SetTextColor( stringMatch.Groups[1].Index, stringMatch.Groups[1].Value.Length, Color.Brown );
      //}
		}

		private void ClearTextColor()
		{
            //SetTextColor(0, rtbCode.Text.Length, rtbCode.ForeColor);
		}

		private void SetTextColor(int _pos, int _length, Color _color)
		{
            //int lastPos = rtbCode.SelectionStart;
            //Color lastColor = rtbCode.SelectionColor;

            //rtbCode.Select(_pos, _length);
            //rtbCode.SelectionColor = _color;

            //rtbCode.Select(lastPos, 0);
            //rtbCode.SelectionColor = lastColor;
		}

		private bool IsNeedHighlighting(string _word)
		{
			foreach(var word in highlight)
			{
				if(string.Equals( _word, word.Trim(), StringComparison.CurrentCultureIgnoreCase ))
					return true;
			}

			return false;
		}

        private void rtbCode_KeyUp(object sender, KeyEventArgs e)
		{
			if(e.Control && e.KeyCode == Keys.Enter)
			{
				DialogResult = DialogResult.OK;
			}
		}

	}
}
