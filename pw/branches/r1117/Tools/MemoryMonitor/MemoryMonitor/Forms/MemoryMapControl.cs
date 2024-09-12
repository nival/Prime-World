using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing.Drawing2D;
using System.Globalization;
using MemoryMonitor.Memory;
using MemoryMonitor.EventLog;

namespace MemoryMonitor.Forms
{
  public class MemoryCell
  {
    [Flags]
    public enum Changes
    {
      None = 0,
      Alloc = 1,
      Free = 2,
    }

    public UInt32 Address = 0;
    public UInt32 Length = 0;
    public UInt32 Used = 0;
    public List<MemoryMonitor.EventLog.EventAlloc> Allocs = new List<MemoryMonitor.EventLog.EventAlloc>();

    public Changes changes = Changes.None;

    public MemoryCell( UInt32 addr, UInt32 len ) { Address = addr; Length = len; }

    internal string GetTooltip()
    {
      string result = string.Format( "Used: {0} / {1}", Used, Length );
      foreach ( MemoryMonitor.EventLog.EventAlloc e in Allocs )
      {
        if ( null == e )
        {
          result += "\n...";
          break;
        }
        result += string.Format( "\n{0:X8}: {1} bytes", e.Address, e.Size );
      }
      return result;
    }
  }

  public partial class MemoryMapControl : UserControl
  {
    # region Fields

    private int cellPixGap = 2;
    public int CellGap { get { return cellPixGap; } set { cellPixGap = value; UpdateScroll(); } }
    private int cellPixSize = 8;
    public int CellSize { get { return cellPixSize; } set { cellPixSize = value; UpdateScroll(); } }
    private int cellsPixMargin = 10;
    public int CellAreaMargin { get { return cellsPixMargin; } set { cellsPixMargin = value; UpdateScroll(); } }
    
    private SolidBrush emptyCellBrush = new SolidBrush( Color.LightGray );
    private SolidBrush partlyFilledCellBrush = new SolidBrush( Color.LightCoral );
    private SolidBrush filledCellBrush = new SolidBrush( Color.Blue );
    public Color EmptyCellColor { get { return emptyCellBrush.Color; } set { emptyCellBrush.Color = value; Invalidate(); } }
    public Color FullCellColor { get { return filledCellBrush.Color; } set { filledCellBrush.Color = value; Invalidate(); } }
    public Color PartialCellColor { get { return partlyFilledCellBrush.Color; } set { partlyFilledCellBrush.Color = value; Invalidate(); } }
    private Pen selectionPen = new Pen( Color.Black );

    private SolidBrush cellAllocBrush = new SolidBrush( Color.Green );
    private SolidBrush cellFreeBrush = new SolidBrush( Color.Red );

    private UInt32 numberOfCells = 4096;
    public UInt32 NumberOfCells { get { return numberOfCells; } set { numberOfCells = value; UpdateMapping(); UpdateScroll(); } }

    private const UInt32 totalMemorySize = 0x80000000;
    private Range currentMemoryRange = new Range( 0, totalMemorySize );
    public UInt32 ViewStart { get { return currentMemoryRange.Address; } }
    public UInt32 ViewLength { get { return currentMemoryRange.Length; } }
    private bool isZoomed = false;
    public bool IsZoomed { get { return isZoomed; } }
    public event EventHandler ZoomChanged = null;

    private MemoryCell[] cellMap = null;
    private MemoryMap memoryMap = null;

    private MemoryCell tooltipCell = null;

    private int cellsInRow = 0;
    private Control cornerPlaceholder = new Label();

    private int selectedCell = -1;
    public event EventHandler CellSelected = null;

    private EventAlloc WideSelection = null;
    private int WideSelectionFirstCell = -1;
    private int WideSelectionLastCell = -1;
    private Pen wideSelectionPen = new Pen( Color.Magenta );
    private SolidBrush wideSelectionBrush = new SolidBrush( Color.Magenta );
    
    #endregion

    # region Initialization

    public MemoryMapControl()
    {
      InitializeComponent();
      SetStyle( ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw, true );


      cellsInRow = ( this.ClientSize.Width - cellsPixMargin - cellsPixMargin ) / ( cellPixSize + cellPixGap );
      cornerPlaceholder.Height = 1;
      cornerPlaceholder.Width = 1;
      this.Controls.Add( cornerPlaceholder );
      UpdateMapping();
    }

    public void Initialize( MemoryMap map )
    {
      memoryMap = map;
      memoryMap.MemoryStateChangedEvent += MemoryStateChanged;
      UpdateCellStatus();
    }

    # endregion

    #region Paint Methods

    protected override void OnPaint( PaintEventArgs e )
    {
      base.OnPaint( e );

      int vscroll = this.VerticalScroll.Value;

      int col = 0;
      int row = 0;
      for ( int i = 0; i < numberOfCells; ++i )
      {
        int y = row * ( cellPixSize + cellPixGap ) + cellsPixMargin;
        DrawCell( e.Graphics, i, col * ( cellPixSize + cellPixGap ) + cellsPixMargin, y - vscroll );
        ++col;
        if ( col == cellsInRow )
        {
          col = 0;
          ++row;
        }
      }
    }

    private void DrawCell( Graphics g, int i, int x, int y )
    {
      MemoryCell cell = cellMap[i];
      Brush activeBrush = partlyFilledCellBrush;
      if ( cell.Length == cell.Used )
        activeBrush = filledCellBrush;
      else if ( cell.Used == 0 )
        activeBrush = emptyCellBrush;

      if ( WideSelection != null && ( WideSelectionFirstCell < 0 || i >= WideSelectionFirstCell )
          && ( WideSelectionLastCell < 0 || i <= WideSelectionLastCell ) )
      {
        g.FillRectangle( wideSelectionBrush, x - 1, y - 1, cellPixSize + 2, cellPixSize + 2 );
      }

      g.FillRectangle( activeBrush, x, y, cellPixSize, cellPixSize );

      int halfSize = cellPixSize >> 1;
      if ( ( cell.changes & MemoryCell.Changes.Alloc ) == MemoryCell.Changes.Alloc )
        g.FillRectangle( cellAllocBrush, x, y + halfSize, halfSize, halfSize );

      if ( ( cell.changes & MemoryCell.Changes.Free ) == MemoryCell.Changes.Free )
        g.FillRectangle( cellFreeBrush, x + halfSize, y + halfSize, halfSize, halfSize );

      if ( WideSelection != null )
      {
        if ( WideSelectionFirstCell < 0 && i == 0 )
        {
          g.DrawLine( wideSelectionPen, x + halfSize, y, x, y + halfSize );
          g.DrawLine( wideSelectionPen, x + halfSize, y + cellPixSize, x, y + halfSize );
          g.DrawLine( wideSelectionPen, x + halfSize, y, x + halfSize, y + cellPixSize );
        }
        else if ( WideSelectionLastCell < 0 && i == numberOfCells - 1 )
        {
          g.DrawLine( wideSelectionPen, x + halfSize, y, x + cellPixSize, y + halfSize );
          g.DrawLine( wideSelectionPen, x + halfSize, y + cellPixSize, x + cellPixSize, y + halfSize );
          g.DrawLine( wideSelectionPen, x + halfSize, y, x + halfSize, y + cellPixSize );
        }
      }

      if ( i == selectedCell )
        g.DrawRectangle( selectionPen, x - 1, y - 1, cellPixSize + 1, cellPixSize + 1 );
    }

    protected override void OnResize( EventArgs e )
    {
      base.OnResize( e );

      cellsInRow = ( this.ClientSize.Width - cellsPixMargin - cellsPixMargin ) / ( cellPixSize + cellPixGap );
      UpdateScroll();
    }

    private void UpdateScroll()
    {
      int cellRows = (int)numberOfCells / cellsInRow + 1;
      cornerPlaceholder.Top = cellsPixMargin + cellRows * ( cellPixSize + cellPixGap );
      this.PerformLayout();

      Invalidate();
    }

    #endregion

    # region Mouse and Keyboard Event handlers

    protected override void OnMouseMove( MouseEventArgs e )
    {
      base.OnMouseMove( e );
      int cellNo = GetCellIndex( e.Location );
      EventAlloc oldWideSelection = WideSelection;
      WideSelection = null;
      if ( cellNo < 0 )
      {
        toolTip.Hide( this );
        if ( oldWideSelection != null )
          Invalidate();
        return;
      }
      MemoryCell cell = cellMap[cellNo];
      if (cell != tooltipCell)
      {
        tooltipCell = cell;
        toolTip.ToolTipTitle = string.Format("{0:X8}-{1:X8}", cell.Address, cell.Address + cell.Length - 1);
        toolTip.Show(cellMap[cellNo].GetTooltip(), this, e.Location.X + 4, e.Location.Y + 4);
      }

      if ( cell.Allocs.Count == 1 && cell.Allocs[0].Size > cell.Length )
      {
        int startCellNo = (int)( ( (long)cell.Allocs[0].Address - currentMemoryRange.Address ) / cell.Length );
        WideSelectionFirstCell = ( startCellNo >= 0 ) ? startCellNo : -1;
        int endCellNo = (int)( ( (long)cell.Allocs[0].Address + cell.Allocs[0].Size - currentMemoryRange.Address ) / cell.Length );
        WideSelectionLastCell = ( endCellNo < numberOfCells ) ? endCellNo : -1;
        WideSelection = cell.Allocs[0];
      }
      if ( WideSelection != oldWideSelection )
        Invalidate();
    }

    private int GetCellIndex( Point point )
    {
      if ( point.X < this.ClientRectangle.Left + cellsPixMargin || point.X > cellsInRow * ( cellPixSize + cellPixGap )
        || point.Y < this.ClientRectangle.Top + cellsPixMargin )
      {
        return -1;
      }

      int col = ( point.X - ClientRectangle.Left - cellsPixMargin ) / ( cellPixSize + cellPixGap );
      int row = ( point.Y - ClientRectangle.Top - cellsPixMargin ) / ( cellPixSize + cellPixGap );
      int cellNo = row * cellsInRow + col;

      if ( cellNo < 0 || cellNo >= cellMap.Length )
      {
        return -1;
      }

      return cellNo;
    }

    protected override void OnMouseDoubleClick( MouseEventArgs e )
    {
      base.OnMouseDoubleClick( e );
      int cellNo = GetCellIndex( e.Location );
      if ( cellNo < 0 || isZoomed )
        return;

      tooltipCell = null;
      UInt32 cellSize = currentMemoryRange.Length / numberOfCells;
      currentMemoryRange = new Range( (uint)cellNo * cellSize, cellSize );
      isZoomed = true;
      UpdateMapping();
      if ( ZoomChanged != null )
        ZoomChanged( this, new EventArgs() );
    }

    protected override void OnMouseClick( MouseEventArgs e )
    {
      base.OnMouseClick( e );
      SelectCell( GetCellIndex( e.Location ) );     
    }

    protected override void OnKeyDown( KeyEventArgs e )
    {
      base.OnKeyDown( e );
      if ( e.KeyCode == Keys.Escape )
        ZoomOut();
    }

    # endregion

    #region Cell Mapping

    public void ZoomOut()
    {
      if ( !isZoomed )
        return;

      isZoomed = false;
      currentMemoryRange = new Range( 0, totalMemorySize );
      UpdateMapping();
      if ( ZoomChanged != null )
        ZoomChanged( this, new EventArgs() );

    }

    private void UpdateMapping()
    {
      UseWaitCursor = true;
      UInt32 cellLength = currentMemoryRange.Length / numberOfCells;

      if ( null == cellMap || cellMap.Length != numberOfCells )
      {
        cellMap = new MemoryCell[numberOfCells];
        for ( int i = 0; i < numberOfCells; ++i )
          cellMap[i] = new MemoryCell( (UInt32)( currentMemoryRange.Address + i * cellLength ), cellLength );
      }
      else
      {
        for ( int i = 0; i < numberOfCells; ++i )
        {
          cellMap[i].Address = (UInt32)( currentMemoryRange.Address + i * cellLength );
          cellMap[i].Length = cellLength;
        }
      }

      UpdateCellStatus();
      UseWaitCursor = false;
    }

    private void SelectCell( int cellNo )
    {
      selectedCell = cellNo;
      Invalidate();
      if ( CellSelected != null )
        CellSelected( selectedCell >= 0 ? cellMap[selectedCell] : null, new EventArgs() );
    }

    private void UpdateCellStatus()
    {
      if ( null == memoryMap )
        return;

      if ( !traceChanges )
        ResetChanges();

      for ( int i = 0; i < numberOfCells; ++i )
      {
        cellMap[i].Used = memoryMap.GetRangeInfo( cellMap[i].Address, cellMap[i].Length, cellMap[i].Allocs );
      }

      SelectCell( -1 );
      Invalidate();
    }

    private void MemoryStateChanged()
    {
      UpdateCellStatus();
      Invalidate();
    }

    #endregion

    #region Cell changes

    public void ResetChanges()
    {
      foreach( MemoryCell cell in cellMap )
        cell.changes = MemoryCell.Changes.None;

      Invalidate();
    }

    public void MemoryStateChangeAlloc( MemoryMonitor.EventLog.EventAlloc e )
    {
      foreach ( MemoryCell cell in cellMap )
      {
        if ( cell.Address < e.Address + e.Size && cell.Address + cell.Length > e.Address )
        {
          cell.changes |= MemoryCell.Changes.Alloc;
        }
      }
    }

    public void MemoryStateChangeFree( MemoryMonitor.EventLog.EventFree e, UInt32 freedMem )
    {
      foreach ( MemoryCell cell in cellMap )
      {
        if ( cell.Address < e.Address + freedMem && cell.Address + cell.Length > e.Address )
        {
          cell.changes |= MemoryCell.Changes.Free;
        }
      }
    }

    private bool traceChanges = false;
    [Browsable( false )]
    public bool TraceChanges
    {
      get { return traceChanges; } 
      set
      {
        if ( value == traceChanges )
          return;

        traceChanges = value;
        if ( value )
        {
          memoryMap.OnAlloc += MemoryStateChangeAlloc;
          memoryMap.OnFree += MemoryStateChangeFree;

          ResetChanges();
        }
        else
        {
          memoryMap.OnAlloc -= MemoryStateChangeAlloc;
          memoryMap.OnFree -= MemoryStateChangeFree;
        }
      }
    }

    #endregion
  }

}

