using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PW_MiniLauncher
{
    public class NoBorderButton : Button
    {
        protected override void OnPaint(PaintEventArgs pevent)
        {
            this.FlatStyle = FlatStyle.Flat;
            this.FlatAppearance.BorderSize = 0;
            base.OnPaint(pevent);
        }
    }
}
