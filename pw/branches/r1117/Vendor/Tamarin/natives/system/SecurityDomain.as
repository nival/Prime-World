package flash.system
{

    [native(cls="SecurityDomainClass", instance="SecurityDomainObject", methods="auto")]
    public class SecurityDomain extends Object
    {

        public function SecurityDomain()
        {
            return;
        }// end function

        public static native function get currentDomain() : SecurityDomain;

    }
}
