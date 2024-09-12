using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Drawing;
using EditorLib;
using EditorLib.Settings;

namespace PF_Editor.Extensions
{
	public partial class BaseExecutableStringEditor : Form
	{
		//private const string KEYWORDS_FILE = @"..\Profiles\keywords.txt";	
		//private readonly Regex keywordsRegex = new Regex( @"\w+" );
		//private readonly Regex stringsRegex = new Regex( @"(?<=^|\W)("".*?"")(?=$|\W)", RegexOptions.Singleline );
		//private readonly string[] highlight = new string[0];

        private IEditorWinApplication application;

        [ConfigObject(true)]
        public class BaseExecutableStringEditorConfig : SimpleConfigObject
        {
            public int LocationX = 100;
            public int LocationY = 100;
            public int Width = 400;
            public int Height = 250;
            public bool WordWrap = false;
        }

        public BaseExecutableStringEditor(IEditorWinApplication application)
		{
			InitializeComponent();
            this.application = application;
		}

		public BaseExecutableStringEditor(IEditorWinApplication application, string _formula) : this(application)
		{
            //if(File.Exists(KEYWORDS_FILE))
            //    highlight = File.ReadAllLines(KEYWORDS_FILE);

			Formula = _formula;
		}

		public string Formula 
		{
			get { return rtbFormula.Text; }
			set 
			{ 
				rtbFormula.Text = value; 
				//UpdateHighlight();
				//rtbFormula.SelectionStart = rtbFormula.Text.Length;
			}
		}

		private void OnTextChanged( object sender, EventArgs e )
		{
			//UpdateHighlight();
		}

		private void UpdateHighlight()
		{
      //ClearTextColor();

      ////подсвечиваем клучевые слова
      //foreach ( Match keywordMatch in keywordsRegex.Matches( rtbFormula.Text ) )
      //{
      //  if ( keywordMatch.Success && IsNeedHighlighting( keywordMatch.Value ) )
      //    SetTextColor( keywordMatch.Index, keywordMatch.Value.Length, Color.Blue );
      //}

      ////подсвечиваем строки
      //foreach ( Match stringMatch in stringsRegex.Matches( rtbFormula.Text ) )
      //{
      //  if ( stringMatch.Success )
      //    SetTextColor( stringMatch.Groups[1].Index, stringMatch.Groups[1].Value.Length, Color.Brown );
      //}
		}

		private void ClearTextColor()
		{
			//SetTextColor( 0, rtbFormula.Text.Length, rtbFormula.ForeColor );
		}

		private void SetTextColor(int _pos, int _length, Color _color)
		{
      //int lastPos = rtbFormula.SelectionStart;
      //Color lastColor = rtbFormula.SelectionColor;

      //rtbFormula.Select( _pos, _length );
      //rtbFormula.SelectionColor = _color;

      //rtbFormula.Select( lastPos, 0 );
      //rtbFormula.SelectionColor = lastColor;
		}

        //private bool IsNeedHighlighting(string _word)
        //{
        //    foreach(var word in highlight)
        //    {
        //        if(string.Equals( _word, word.Trim(), StringComparison.CurrentCultureIgnoreCase ))
        //            return true;
        //    }

        //    return false;
        //}

		private void rtbFormula_KeyUp( object sender, KeyEventArgs e )
		{
			if(e.Control && e.KeyCode == Keys.Enter)
			{
				DialogResult = DialogResult.OK;
			}
		}

        private void cbWordWrap_CheckedChanged(object sender, EventArgs e)
        {
            if (cbWordWrap.Checked)
            {
                rtbFormula.LineWrapping.Mode = ScintillaNET.LineWrappingMode.Word;
            }
            else
            {
                rtbFormula.LineWrapping.Mode = ScintillaNET.LineWrappingMode.None;
            }
        }

        private void BaseExecutableStringEditor_Load(object sender, EventArgs e)
        {
            var c = application.Application.Settings.Get<BaseExecutableStringEditorConfig>();
            this.SetBounds(c.LocationX, c.LocationY, c.Width, c.Height);
            cbWordWrap.Checked = c.WordWrap;
        }

        private void BaseExecutableStringEditor_FormClosing(object sender, FormClosingEventArgs e)
        {
            var c = application.Application.Settings.Get<BaseExecutableStringEditorConfig>();
            c.LocationX = Location.X;
            c.LocationY = Location.Y;
            c.Width = Width;
            c.Height = Height;
            c.WordWrap = cbWordWrap.Checked;
        }

	}
}
