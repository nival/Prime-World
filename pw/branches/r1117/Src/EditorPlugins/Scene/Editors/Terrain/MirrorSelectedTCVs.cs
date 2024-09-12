using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.Menu;
using EditorLib.ObjectsBrowser;
using EditorLib.Operations;
using EditorNative;
using EditorNative.Terrain;
using EditorNative.SceneElements;
using EditorPlugins.Forms;
using EditorPlugins.ObjectLayers;
using EditorPlugins.Scene.Editors.Terrain;
using libdb;
using libdb.DB;
using EditorNative.Manipulators;

namespace EditorPlugins.Scene.Editors
{
  internal sealed class MirrorSelectedTCVs
  {
    private List<ControlableTcvMarker> selectedTCVs;
    private List<ControlableTerrainElement> selectedTerrElems;
    private EditorTerrain terrain;
    private EditorScene scene;
    private float fELEM_SIZE = TerrainUtils.PatchSize;

    public MirrorSelectedTCVs( EditorScene scene )
    {
      this.selectedTCVs = new List<ControlableTcvMarker>();
      this.selectedTerrElems = new List<ControlableTerrainElement>();
      this.scene = scene;
      this.terrain = scene.SceneTerrain;
    }

    public void Execute()
    {
      CollectTerrElements();

      Mirror();
    }

    public bool CheckSelectionAndCollect( IList<SceneElement> selection )
    {
      int side = -1; // -1 undefined or mid, 0 one side, 1 another
      float mid = terrain.SizeX / 2.0f;

      foreach ( SceneElement elem in selection )
      {
        ControlableTcvMarker tcv = elem as ControlableTcvMarker;
        if ( tcv == null )
        {
          MessageBox.Show( "Please select TCVs only", "Error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk );
          return false;
        }

        float param = tcv.MarkerX;

        int newSide = -1;
        if ( param < mid )
          newSide = 0;
        else if ( param > mid )
          newSide = 1;

        if ( newSide != -1 )
        {
          if ( side != -1 && newSide != side )
          {
            MessageBox.Show( "Please select TCVs from one half of map only", "Error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk );
            return false;
          }
          else
          {
            side = newSide;
          }

          selectedTCVs.Add( tcv );
        }

      }

      return true;
    }

    private void CollectTerrElements()
    {
      Dictionary<ControlableTerrainElement,int> potentialTerrElems = new Dictionary<ControlableTerrainElement, int>();

      foreach ( ControlableTerrainElement elem in terrain.Elements )
      {
        foreach ( ControlableTcvMarker tcv in selectedTCVs )
        {
          if ( Math.Abs( elem.Location.X - tcv.MarkerX * fELEM_SIZE ) < fELEM_SIZE && Math.Abs( elem.Location.Y - tcv.MarkerY * fELEM_SIZE ) < fELEM_SIZE )
          {
            int counter = 0;
            if ( potentialTerrElems.TryGetValue( elem, out counter ) )
            {
              counter++;
              if ( counter == 4 )
                selectedTerrElems.Add( elem );
              else
                potentialTerrElems[elem] = counter;
            }
            else
            {
              potentialTerrElems.Add( elem, 1 );
            }
          }
        }
      }
    }

    private void Mirror()
    {
      foreach ( ControlableTerrainElement selectedElem in selectedTerrElems )
      {
        float mirrX = terrain.SizeX * fELEM_SIZE - selectedElem.Location.X;
        float mirrY = terrain.SizeY * fELEM_SIZE - selectedElem.Location.Y;

        foreach ( ControlableTerrainElement elem in terrain.Elements )
        {
          if ( elem.Location.X == mirrX && elem.Location.Y == mirrY )
          {
            float angle = selectedElem.Resource.angle;
            elem.Resource.angle = angle > 180.0f ? angle - 180.0f : angle + 180.0f; ;
            elem.Resource.material = selectedElem.Resource.material;
            elem.Resource.terrainObject = selectedElem.Resource.terrainObject;
          }
        }
      }

      foreach ( ControlableTcvMarker selectedTcv in selectedTCVs )
      {
        float mirrX = terrain.SizeX - selectedTcv.MarkerX;
        float mirrY = terrain.SizeY - selectedTcv.MarkerY;

        foreach ( ControlableTcvMarker tcv in terrain.TcvMarkers )
        {
          if ( tcv.MarkerX == mirrX && tcv.MarkerY == mirrY )
          {
            Vector3 newLocation = tcv.Location;
            newLocation.Z = selectedTcv.Location.Z;
            var newTCV = tcv as IObjectTransformController;
            if ( newTCV != null )
            {
              newTCV.Location = newLocation;
              newTCV.Rotation = selectedTcv.Rotation;
              double angle;
              Vector3 axis;
              selectedTcv.Rotation.DecompAngleAxis( out angle, out axis );
              axis.X = -axis.X;
              axis.Y = -axis.Y;
              newTCV.Rotation = Quaternion.FromAngleAxis( angle, axis );
            }
          }
        }
      }
    }
  }
}