package flash.ui
{

    [native(cls="KeyboardClass", instance="KeyboardObject", methods="auto")]
    final public class Keyboard extends Object
    {
        public static const ESCAPE:uint = 27;
        public static const RIGHT:uint = 39;
        public static const LEFT:uint = 37;
        public static const NUMPAD_7:uint = 103;
        public static const TAB:uint = 9;
        public static const NUMPAD_ADD:uint = 107;
        public static const SPACE:uint = 32;
        public static const DOWN:uint = 40;
        public static const UP:uint = 38;
        public static const F1:uint = 112;
        public static const F2:uint = 113;
        public static const F3:uint = 114;
        public static const F4:uint = 115;
        public static const F5:uint = 116;
        public static const F6:uint = 117;
        public static const F7:uint = 118;
        public static const DELETE:uint = 46;
        public static const F9:uint = 120;
        public static const ENTER:uint = 13;
        public static const INSERT:uint = 45;
        public static const NUMPAD_DIVIDE:uint = 111;
        public static const END:uint = 35;
        public static const CONTROL:uint = 17;
        public static const NUMPAD_1:uint = 97;
        public static const NUMPAD_2:uint = 98;
        public static const F8:uint = 119;
        public static const NUMPAD_4:uint = 100;
        public static const NUMPAD_5:uint = 101;
        public static const NUMPAD_8:uint = 104;
        public static const NUMPAD_9:uint = 105;
        public static const NUMPAD_3:uint = 99;
        public static const CAPS_LOCK:uint = 20;
        public static const NUMPAD_6:uint = 102;
        public static const NUMPAD_0:uint = 96;
        public static const NUMPAD_ENTER:uint = 108;
        public static const NUMPAD_DECIMAL:uint = 110;
        public static const BACKSPACE:uint = 8;
        public static const PAGE_DOWN:uint = 34;
        public static const PAGE_UP:uint = 33;
        public static const F10:uint = 121;
        public static const HOME:uint = 36;
        public static const F12:uint = 123;
        public static const F13:uint = 124;
        public static const F14:uint = 125;
        public static const F15:uint = 126;
        public static const SHIFT:uint = 16;
        public static const NUMPAD_SUBTRACT:uint = 109;
        public static const F11:uint = 122;
        public static const NUMPAD_MULTIPLY:uint = 106;

        public function Keyboard()
        {
            return;
        }// end function

        public static native function get capsLock() : Boolean;

        public static native function isAccessible() : Boolean;

        public static native function get numLock() : Boolean;

    }
}
