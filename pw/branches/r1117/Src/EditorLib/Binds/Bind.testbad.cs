using System;
using NUnit.Framework;
using System.Collections.Generic;
using System.Windows.Forms;

namespace EditorLib.Binds
{
  [TestFixture]
  public class BindsTest
  {
    [Test]
    public void TestSimple()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { mouseButtons = MouseButtons.Left, badKeys = new List<Keys>() { Keys.Menu }, ignoreKeys = true } );
      
      Assert.IsFalse( bind.IsActive );
      bind.OnMouseDown( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() );
      Assert.IsTrue( bind.IsActive );
      bind.OnMouseUp( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() );
      Assert.IsFalse( bind.IsActive );
    }

    [Test]
    public void TestActivation()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { mouseButtons = MouseButtons.Left, badKeys = new List<Keys>() { Keys.Menu }, ignoreKeys = true } );

      Assert.IsFalse( bind.IsActivated );
      Assert.IsFalse( bind.IsDeactivated );

      bind.OnMouseDown( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() );
      Assert.IsTrue( bind.IsActivated );
      Assert.IsFalse( bind.IsDeactivated );

      bind.Reset();
      Assert.IsFalse( bind.IsActivated );
      Assert.IsFalse( bind.IsDeactivated );

      bind.OnMouseUp( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() );
      Assert.IsFalse( bind.IsActivated );
      Assert.IsTrue( bind.IsDeactivated );

      bind.Reset();
      Assert.IsFalse( bind.IsActivated );
      Assert.IsFalse( bind.IsDeactivated );
    }

    [Test]
    public void TestActivationCollect()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { mouseButtons = MouseButtons.Left, badKeys = new List<Keys>() { Keys.Menu }, ignoreKeys = true } );

      bind.OnMouseDown( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() );
      bind.OnMouseUp( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() );
      Assert.IsTrue( bind.IsActivated );
      Assert.IsTrue( bind.IsDeactivated );

      bind.Reset();
      Assert.IsFalse( bind.IsActivated );
      Assert.IsFalse( bind.IsDeactivated );
    }

    [Test]
    public void TestIgnoreKeys()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { mouseButtons = MouseButtons.Left, badKeys = new List<Keys>() { Keys.Menu }, ignoreKeys = true } );

      bind.OnMouseDown( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() { Keys.A } );
      Assert.IsTrue( bind.IsActive );
      bind.OnMouseUp( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() { Keys.A } );
      Assert.IsFalse( bind.IsActive );
    }

    [Test]
    public void TestBadKeys()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { mouseButtons = MouseButtons.Left, badKeys = new List<Keys>() { Keys.Menu }, ignoreKeys = true } );

      bind.OnMouseDown( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() { Keys.Menu } );
      Assert.IsFalse( bind.IsActive );
    }

    [Test]
    public void TestKeyboardBind()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { keys = new List<Keys>() { Keys.A } } );

      Assert.IsFalse( bind.IsActive );
      bind.OnKeyDown( new KeyEventArgs( Keys.A ), new List<Keys>() { Keys.A } );
      Assert.IsTrue( bind.IsActive );
      bind.OnKeyUp( new KeyEventArgs( Keys.A ), new List<Keys>() { Keys.A } );
      Assert.IsFalse( bind.IsActive );
    }

    [Test]
    public void TestKeyboardCombinationBind()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { keys = new List<Keys>() { Keys.A, Keys.Menu } } );

      Assert.IsFalse( bind.IsActive );
      bind.OnKeyDown( new KeyEventArgs( Keys.A ), new List<Keys>() { Keys.A } );
      Assert.IsFalse( bind.IsActive );
      bind.OnKeyDown( new KeyEventArgs( Keys.Menu ), new List<Keys>() { Keys.A, Keys.Menu } );
      Assert.IsTrue( bind.IsActive );
      bind.OnKeyUp( new KeyEventArgs( Keys.A ), new List<Keys>() { Keys.A, Keys.Menu } );
      Assert.IsFalse( bind.IsActive );
    }

    [Test]
    public void TestBadKeysDeactivation()
    {
      Bind bind = new Bind( "test", "test", new BindConfig() { mouseButtons = MouseButtons.Left, badKeys = new List<Keys>() { Keys.Menu }, ignoreKeys = true } );

      bind.OnMouseDown( new MouseEventArgs( MouseButtons.Left, 1, 1, 1, 1 ), new List<Keys>() );
      Assert.IsTrue( bind.IsActive );
      bind.OnKeyDown( new KeyEventArgs( Keys.Menu ), new List<Keys>() );
      Assert.IsFalse( bind.IsActive );
    }
  }
}