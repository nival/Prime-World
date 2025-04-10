package flash.system
{
    import flash.utils.*;

    [native(cls="ApplicationDomainClass", instance="ApplicationDomainObject", methods="auto")]
    final public class ApplicationDomain extends Object
    {

        public function ApplicationDomain(parentDomain:ApplicationDomain = null);

        public native function get domainMemory() : ByteArray;

        public native function getDefinition(name:String) : Object;

        public native function set domainMemory(mem:ByteArray);

        public native function hasDefinition(name:String) : Boolean;

        public native function get parentDomain() : ApplicationDomain;

        public static native function get currentDomain() : ApplicationDomain;

        public static native function get MIN_DOMAIN_MEMORY_LENGTH() : uint;

    }
}
