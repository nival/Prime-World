using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using System.Globalization;
using MemoryMonitor.Memory;
using MemoryMonitor.EventLog;
using System.Diagnostics;
using MemoryMonitor.CallStack;

namespace MemoryMonitor.Forms
{
  public partial class MainForm : Form
  {
    private MemoryMap memoryMap = new MemoryMap();
    private DebugInfoProvider debugInfoProvider = new DebugInfoProvider();

    private string baseWindowTitle = string.Empty;

    public MainForm( string fileName )
    {
      InitializeComponent();

      MemoryMapControl.Initialize( memoryMap );

      if ( !string.IsNullOrEmpty( fileName ) && File.Exists( fileName ) )
      {
        memoryMap.SetEventProvider( new AllocEventLog( fileName ) );
      }

      MemoryMapControl.ZoomChanged += MapControl_OnZoomChanged;
      tsmZoomOut.Visible = MemoryMapControl.IsZoomed;

      MemoryMapControl.CellSelected += MapControl_OnSelectionChanged;

      baseWindowTitle = this.Text;
      UpdateWindowTitle();
    }

    private void UpdateWindowTitle()
    {
      string result = baseWindowTitle;
      if ( !string.IsNullOrEmpty( memoryMap.ProviderName ) )
      {
        result += " (" + Path.GetFileName( memoryMap.ProviderName ) + ")";

        if ( MemoryMapControl.IsZoomed )
        {
          result += string.Format( " ZOOM: {0:X8}-{1:X8}", MemoryMapControl.ViewStart, MemoryMapControl.ViewStart + MemoryMapControl.ViewLength - 1 );
        }
      }
      this.Text = result;
    }

    private void OpenBinaryData( string fileName )
    {
      memoryMap.SetEventProvider( new AllocEventLog( fileName ) );
      UpdateWindowTitle();
    }

    private void exitToolStripMenuItem_Click( object sender, EventArgs e )
    {
      Close();
    }

    private void openBinaryDataToolStripMenuItem_Click( object sender, EventArgs e )
    {
      OpenFileDialog dialog = new OpenFileDialog();
      if( DialogResult.OK == dialog.ShowDialog() )
      {
        string fileName = dialog.FileName;
        OpenBinaryData( fileName );
      }
    }

    private void tsmZoomOut_Click( object sender, EventArgs e )
    {
      MemoryMapControl.ZoomOut();
    }

    private void MapControl_OnZoomChanged( object sender, EventArgs e )
    {
      tsmZoomOut.Visible = MemoryMapControl.IsZoomed;
      UpdateWindowTitle();
    }

    private void MapControl_OnSelectionChanged( object sender, EventArgs e )
    {
      lbSelectedAllocs.Items.Clear();
      lbCallStack.Items.Clear();
      if ( null == sender || !( sender is MemoryCell ) )
        return;

      MemoryCell cell = sender as MemoryCell;
      List<EventAlloc> fullAllocList = new List<EventAlloc>();
      memoryMap.GetRangeFullInfo( cell.Address, cell.Length, fullAllocList );
      foreach ( EventAlloc item in fullAllocList )
      {
        lbSelectedAllocs.Items.Add( item );
      }

      if ( fullAllocList.Count == 1 )
        lbSelectedAllocs.SelectedIndex = 0;
    }

    private void tbTime_Leave( object sender, EventArgs e )
    {
      ApplyTime();
    }

    private void ApplyTime()
    {
      try
      {
        uint time = uint.Parse( tbTime.Text );
        memoryMap.NavigateToTime( time );
      }
      catch
      { }

      tbTime.Text = memoryMap.CurrentTime.ToString();
    }

    private void tbTime_KeyDown( object sender, KeyEventArgs e )
    {
      if ( e.KeyCode != Keys.Enter )
        return;

      ApplyTime();
      e.Handled = true;
    }

    private void bNextTime_Click( object sender, EventArgs e )
    {
      MemoryMapControl.TraceChanges = true;
      memoryMap.NavigateByTimeOffset( 1000 );
      tbTime.Text = memoryMap.CurrentTime.ToString();
      MemoryMapControl.TraceChanges = false;
    }

    private void bNextEvent_Click( object sender, EventArgs e )
    {
      MemoryMapControl.TraceChanges = true;
      memoryMap.NavigateByEventOffset( 1 );
      tbTime.Text = memoryMap.CurrentTime.ToString();
      MemoryMapControl.TraceChanges = false;
    }

    private void bNextNEvents_Click( object sender, EventArgs e )
    {
      MemoryMapControl.TraceChanges = true;
      memoryMap.NavigateByEventOffset( 10 );
      tbTime.Text = memoryMap.CurrentTime.ToString();
      MemoryMapControl.TraceChanges = false;
    }

    private void bPrevTime_Click( object sender, EventArgs e )
    {
      memoryMap.NavigateByTimeOffset( -1000 );
      tbTime.Text = memoryMap.CurrentTime.ToString();
    }

    private void bPrevEvent_Click( object sender, EventArgs e )
    {
      memoryMap.NavigateByEventOffset( -1 );
      tbTime.Text = memoryMap.CurrentTime.ToString();
    }

    private void bPrevNEvents_Click( object sender, EventArgs e )
    {
      memoryMap.NavigateByEventOffset( -10 );
      tbTime.Text = memoryMap.CurrentTime.ToString();
    }

    #region Alloc and call stack info

    private void tsmiOpenModules_Click( object sender, EventArgs e )
    {
      OpenFileDialog dialog = new OpenFileDialog();
      if ( DialogResult.OK == dialog.ShowDialog() )
      {
        string fileName = dialog.FileName;
        debugInfoProvider.LoadModuleLayout( fileName );
      }
    }

    private void lbSelectedAllocs_SelectedIndexChanged( object sender, EventArgs e )
    {
      lbCallStack.Items.Clear();

      EventAlloc alloc = lbSelectedAllocs.SelectedItem as EventAlloc;
      if ( null == alloc )
        return;

      foreach ( UInt32 item in alloc.CallStack )
        lbCallStack.Items.Add( string.Format( "{0:X8} \t{1}", item, debugInfoProvider.GetInfo( item ) ) );
    }

    #endregion


  }
}
