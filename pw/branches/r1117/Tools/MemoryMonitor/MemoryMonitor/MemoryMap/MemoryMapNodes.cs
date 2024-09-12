using System;
using System.Collections.Generic;
using System.Text;
using MemoryMonitor.EventLog;

namespace MemoryMonitor.Memory
{
  public class Node
  {
    private const int TreeFactorBits = 4;
    private const int TreeFactor = 16;
    private const int Granularity = 16;
    private const int MinNodeSize = TreeFactor * Granularity;
    private const int InfoAllocsCapacity = 5;

    public readonly UInt32 AddressStart = 0;
    public readonly UInt32 Length = 0;

    private UInt32 memUsed = 0;
    public UInt32 MemoryUsed { get { return memUsed; } }
    public UInt32 MemoryFree { get { return Length - memUsed; } }

    private Node[] children = null;
    private LinkedList<EventAlloc> nodeAllocs = new LinkedList<EventAlloc>();

    public readonly bool IsLeaf;
    public Node( UInt32 a, UInt32 l )
    {
      AddressStart = a;
      Length = l;

      IsLeaf = l <= MinNodeSize;
      if ( !IsLeaf )
        children = new Node[TreeFactor];
    }

    private bool IsIntersectsRegion( EventAlloc e )
    {
      return AddressStart < e.Address + e.Size && AddressStart + Length > e.Address;
    }

    private bool IsContainsAddress( UInt32 address )
    {
      return address >= AddressStart && address < AddressStart + Length;
    }

    private uint GetChildIndex( UInt32 address )
    {
      return (uint)( ( address - AddressStart ) / ( Length >> TreeFactorBits ) );
    }

    #region Process Allocation

    public EventAlloc GetInfo( UInt32 address )
    {
      if ( !IsContainsAddress( address ) )
        return null;

      if ( nodeAllocs.Count > 0 )
      {
        foreach ( EventAlloc e in nodeAllocs )
        {
          if ( e.Address <= address && e.Address + e.Size > address )
            return e;
        }
      }

      if ( !IsLeaf )
      {
        uint index = GetChildIndex( address );
        if ( children[index] != null )
          return children[index].GetInfo( address );
      }

      return null;
    }

    public void ProcessAlloc( EventAlloc e )
    {
      if ( !IsIntersectsRegion( e ) )
        throw new AllocationIntegrityException();

      UInt32 eEnd = e.Address + e.Size;
      UInt32 nEnd = AddressStart + Length;

      UInt32 projStart = e.Address > AddressStart ? e.Address : AddressStart;
      UInt32 projEnd = eEnd > nEnd ? nEnd : eEnd;

      if ( IsLeaf )
      {
        CheckOverlapAndAdd( e );
      }
      else
      {
        uint indexS = GetChildIndex( projStart );
        uint indexE = GetChildIndex( projEnd - 1 );

        if ( indexE - indexS > 1
          || eEnd > nEnd || e.Address < AddressStart
          || indexS != indexE && ( eEnd == nEnd || e.Address == AddressStart ) )
        {
          CheckOverlapAndAdd( e );
        }

        if ( e.Address >= AddressStart )
          AddToChild( indexS, e );          // Store start

        if ( ( indexS != indexE || e.Address < AddressStart ) && eEnd <= nEnd )
          AddToChild( indexE, e );          // Store end separately from start if necessary
      }
      memUsed += projEnd - projStart;
    }

    private void AddToChild( uint index, EventAlloc e )
    {
      if ( null == children[index] )
      {
        //Create
        UInt32 childSize = Length >> TreeFactorBits;
        children[index] = new Node( AddressStart + index * childSize, childSize );
      }

      children[index].ProcessAlloc( e );
    }

    private void CheckOverlapAndAdd( EventAlloc e )
    {
      if ( nodeAllocs.Count > 0 )
      {
        // Test for overlap
        foreach ( EventAlloc item in nodeAllocs )
        {
          if ( e.Address < item.Address + item.Size && item.Address < e.Address + e.Size )
            throw new AllocationOverlapException();
        }
      }

      nodeAllocs.AddLast( e );
    }

    #endregion

    #region Process Deallocation

    public UInt32 ProcessFree( EventFree e )
    {
      EventAlloc ea = GetInfo( e.Address );
      if ( null == ea )
        throw new DeallocationMissException();

      UInt32 oldMemUsed = memUsed;
      ProcessFreeInternal( ea );
      return oldMemUsed - memUsed;
    }

    private void ProcessFreeInternal( EventAlloc e )
    {
      if ( !IsIntersectsRegion( e ) )
        return;

      UInt32 eEnd = e.Address + e.Size;
      UInt32 nEnd = AddressStart + Length;
      UInt32 projStart = e.Address > AddressStart ? e.Address : AddressStart;
      UInt32 projEnd = eEnd > nEnd ? nEnd : eEnd;

      nodeAllocs.Remove( e );

      if ( !IsLeaf )
      {
        uint indexS = GetChildIndex( projStart );
        uint indexE = GetChildIndex( projEnd - 1 );

        if ( null != children[indexS] )
        {
          RemoveFromChild( indexS, e );
        }
        if ( indexS != indexE && null != children[indexE] )
        {
          RemoveFromChild( indexE, e );
        }
      }

      memUsed -= projEnd - projStart;
    }

    private void RemoveFromChild( uint index, EventAlloc e )
    {
      children[index].ProcessFreeInternal( e );

      if ( children[index].MemoryUsed == 0 )
        children[index] = null;
    }

    #endregion

    #region Check if a region is filled

    private UInt32 GetIntersectionSize( UInt32 a1, UInt32 l1, UInt32 a2, UInt32 l2 )
    {
      long result = (long)( a1 + l1 > a2 + l2 ? a2 + l2 : a1 + l1 ) - ( a1 > a2 ? a1 : a2 );

      return result > 0 ? (UInt32)result : 0;
    }

    private bool IsFullyContained( UInt32 aInner, UInt32 lInner, UInt32 aOuter, UInt32 lOuter )
    {
      return aInner >= aOuter && aInner + lInner <= aOuter + lOuter;
    }

    private Range GetIntersection( UInt32 a1, UInt32 l1, UInt32 a2, UInt32 l2 )
    {
      return new Range( a1 > a2 ? a1 : a2, GetIntersectionSize( a1, l1, a2, l2 ) );
    }

    public UInt32 GetFastRegionInfo( uint address, uint length, List<EventAlloc> allocs )
    {
      allocs.Clear();

      return GetRegionInfo( address, length, allocs, InfoAllocsCapacity );
    }

    public UInt32 GetFullRegionInfo( uint address, uint length, List<EventAlloc> allocs )
    {
      allocs.Clear();

      return GetRegionInfo( address, length, allocs, 0 );
    }

    private UInt32 GetRegionInfo( uint address, uint length, List<EventAlloc> allocs, int maxAllocs )
    {
      if ( memUsed == 0 )
        return 0;

      Range proj = GetIntersection( address, length, AddressStart, Length );
      bool[] fullSkip = new bool[TreeFactor];
      for ( int i = 0; i < TreeFactor; ++i )
        fullSkip[i] = false;

      UInt32 childSize = Length >> TreeFactorBits;
      UInt32 eProjTotal = 0;

      if ( nodeAllocs.Count > 0 )
      {
        foreach ( EventAlloc e in nodeAllocs )
        {
          uint eProj = GetIntersectionSize( proj.Address, proj.Length, e.Address, e.Size );

          if ( eProj > 0 )
          {
            eProjTotal += eProj;
            StoreRegionInfoElement( allocs, e, maxAllocs );
          }

          if ( !IsLeaf )
          {
            for ( uint i = 0; i < TreeFactor; ++i )
            {
              if ( children[i] != null || fullSkip[i] )
                continue;

              if ( IsFullyContained( AddressStart + childSize * i, childSize, e.Address, e.Size ) )
                fullSkip[i] = true;
            }
          }
        }
      }

      if ( IsLeaf )
        return eProjTotal;

      return GetChildrenRegionInfo( proj, fullSkip, allocs, maxAllocs );
    }

    private UInt32 GetChildrenRegionInfo( Range proj, bool[] fullSkip, List<EventAlloc> allocs, int maxAllocs )
    {
      uint indexS = GetChildIndex( proj.Address );
      uint indexE = GetChildIndex( proj.Address + proj.Length - 1 );
      uint childLength = Length >> TreeFactorBits;

      UInt32 result = 0;
      if ( null == children[indexS] )
      {
        if ( fullSkip[indexS] )
          result += GetIntersectionSize( AddressStart + childLength * indexS, childLength, proj.Address, proj.Length );
      }
      else
        result += children[indexS].GetRegionInfo( proj.Address, proj.Length, allocs, maxAllocs );

      for ( uint i = indexS + 1; i <= indexE; ++i )
      {
        if ( null == children[i] )
        {
          if ( fullSkip[i] )
            result += GetIntersectionSize( AddressStart + childLength * i, childLength, proj.Address, proj.Length );
        }
        else
          result += children[i].GetRegionInfo( proj.Address, proj.Length, allocs, maxAllocs );

      }

      return result;
    }

    private void StoreRegionInfoElement( List<EventAlloc> allocs, EventAlloc e, int maxAllocs )
    {
      if ( allocs.Count > maxAllocs && maxAllocs > 0 || allocs.Contains( e ) )
        return;

      if ( allocs.Count == maxAllocs && maxAllocs > 0 )
        allocs.Add( null );
      else
        allocs.Add( e );
    }

    #endregion

    internal Node Clone()
    {
      Node result = new Node( this.AddressStart, this.Length );
      result.memUsed = this.memUsed;
      foreach ( var item in this.nodeAllocs )
        result.nodeAllocs.AddLast( item );

      if ( !IsLeaf )
      {
        for ( int i = 0; i < TreeFactor; ++i )
        {
          if ( null == this.children[i] )
            continue;

          result.children[i] = this.children[i].Clone();
        }
      }

      return result;
    }
  }
}
