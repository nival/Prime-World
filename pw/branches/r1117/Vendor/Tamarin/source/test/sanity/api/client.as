/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
 
// test client code

/*
   asc -config CONFIG::VERSION=0 -api 0 client.as
*/

package {
import avmplus.*;
CONFIG const V0 = CONFIG::VERSION==0;
CONFIG const V1 = CONFIG::VERSION==1;
CONFIG const V2 = CONFIG::VERSION==2;
CONFIG const V3 = CONFIG::VERSION==3;
CONFIG const V4 = CONFIG::VERSION==4;
CONFIG const V5 = CONFIG::VERSION==5;
CONFIG const V6 = CONFIG::VERSION==6;

CONFIG::V0 {
  use namespace AS3;
  public class B extends A {
    override public function m () { return 11 }
  }

  public class D extends A {
    override public function m () { return 11 }
    public function n () { return 21 }
    public function r () { return 51 }
    //public function s () { return 61 }
  }
  var o = new D();

  run(function() { return x0 }, false);
  run(function() { return x1 }, true);
  run(function() { return x2 }, true);
  run(function() { return x3 }, true);
  run(function() { return x4 }, true);
  run(function() { return x5 }, true);
  run(function() { return x12 }, true);
  run(function() { return x23 }, true);
  run(function() { return o.x==10 }, true);
  run(function() { return o.m()==11 }, false);
  run(function() { return o.n()==21 }, false);
  run(function() { return o.q()==41 }, true);
  run(function() { return o.r()==51 }, false);
  run(function() { return o.s()==61 }, true);
  run(function() { return C.m()==50 }, false);
}

CONFIG::V1 {
  use namespace AS3;
  public class B extends A {
    override public function m () { return 11 }
  }

  public class D extends A {
    override public function m () { return 11 }
    override public function n () { return 21 }
    public function r () { return 51 }
    public function s () { return 61 }
  }

  var o = new D();

  run(function() { return x0 }, false);
  run(function() { return x1 }, false);
  run(function() { return x2 }, true);
  run(function() { return x3 }, true);
  run(function() { return x4 }, true);
  run(function() { return x5 }, true);
  run(function() { return x12 }, false);
  run(function() { return x23 }, true);
  run(function() { return o.x==10 }, false);
  run(function() { return o.m()==11 }, false);
  run(function() { return o.n()==21 }, false);
  run(function() { return o.q()==41 }, true);
  run(function() { return o.r()==51 }, false);
  run(function() { return o.s()==61 }, false);
  run(function() { return C.m()==50 }, false);
}

CONFIG::V2 {
  public class B extends A {
    override public function m () { return 11 }
  }

  public class E extends A {
    override public function m () { return 11 }
    override public function n () { return 21 }
    //public function q () { return 41 }
    public function r () { return 51 }
    //public function s () { return 61 }
  }

  var o = new E();
  run(function() { return x0 }, false);
  run(function() { return x1 }, true);
  run(function() { return x2 }, false);
  run(function() { return x3 }, true);
  run(function() { return x4 }, true);
  run(function() { return x5 }, true);
  run(function() { return x12 }, false);
  run(function() { return x23 }, false);
  run(function() { return o.x==10 }, true);
  run(function() { return o.m()==11 }, false);
  run(function() { return o.n()==21 }, false);
  run(function() { return o.q()==41 }, true);
  run(function() { return o.r()==51 }, false);
  run(function() { return o.s()==61 }, true);
  run(function() { return C.m()==50 }, false);
}

CONFIG::V3 {
  public class B extends A {
    override public function m () { return 11 }
  }

  public class D extends A {
    override public function m () { return 11 }
    override public function n () { return 21 }
    public function q () { return 41 }
    public function r () { return 51 }
    public function s () { return 61 }
  }

  var o = new D();
  run(function() { return x0 }, false);
  run(function() { return x1 }, false);
  run(function() { return x2 }, false);
  run(function() { return x3 }, false);
  run(function() { return x4 }, true);
  run(function() { return x5 }, true);
  run(function() { return x23 }, false);
  run(function() { return o.m()==11 }, false);
  run(function() { return o.n()==21 }, false);
  run(function() { return o.q()==41 }, false);
  run(function() { return o.r()==51 }, false);
  run(function() { return o.s()==61 }, false);
  run(function() { return o.x==10 }, false);
}

CONFIG::V4 {
  public class B extends A {
    override public function m () { return 11 }
  }

  public class D extends A {
    override public function m () { return 11 }
    override public function n () { return 21 }
    public function q () { return 41 }
    public function r () { return 51 }
    public function s () { return 61 }
  }

  var o = new D();
  run(function() { return x0 }, false);
  run(function() { return x1 }, false);
  run(function() { return x2 }, false);
  run(function() { return x3 }, false);
  run(function() { return x4 }, false);
  run(function() { return x5 }, true);
  run(function() { return x23 }, false);
  run(function() { return o.x==10 }, false);
  run(function() { return o.m()==11 }, false);
  run(function() { return o.n()==21 }, false);
  run(function() { return o.q()==41 }, false);
  run(function() { return o.r()==51 }, false);
  run(function() { return o.s()==61 }, false);
  run(function() { return C.m()==50 }, false);  // FIXME crashes jit
}

CONFIG::V5 {
  public class D extends A {
    override public function m () { return 11 }
    override public function n () { return 21 }
    public function q () { return 41 }
    public function r () { return 51 }
    public function s () { return 61 }
  }

  var o = new D();

  run(function() { return x0 }, false);
  run(function() { return x1 }, true);
  run(function() { return x2 }, false);
  run(function() { return x3 }, true);
  run(function() { return x4 }, true);
  run(function() { return x5 }, false);
  run(function() { return x23 }, false);
  run(function() { return o.x==10 }, false);
  run(function() { return o.m()==11 }, false);
  run(function() { return o.n()==21 }, false);
  run(function() { return o.q()==41 }, false);
  run(function() { return o.r()==51 }, false);
  run(function() { return o.s()==61 }, false);
  run(function() { return C.m()==50 }, false);
}

CONFIG::V6 {
  public class D extends A {
    override public function m () { return 11 }
    override public function n () { return 21 }
    public function q () { return 41 }
    public function r () { return 51 }
    public function s () { return 61 }
  }

  var o = new D();

  run(function() { return x0 }, false);
  run(function() { return x1 }, false);
  run(function() { return x2 }, false);
  run(function() { return x3 }, false);
  run(function() { return x4 }, false);
  run(function() { return x5 }, false);
  run(function() { return x23 }, false);
  run(function() { return o.x==10 }, false);
  run(function() { return o.m()==11 }, false);
  run(function() { return o.n()==21 }, false);
  run(function() { return o.q()==41 }, false);
  run(function() { return o.r()==51 }, false);
  run(function() { return o.s()==61 }, false);
  run(function() { return C.m()==50 }, false);
}
}

