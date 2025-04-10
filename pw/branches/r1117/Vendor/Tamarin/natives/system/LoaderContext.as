package flash.system
{

    public class LoaderContext extends Object
    {
        public var applicationDomain:ApplicationDomain = null;
        public var checkPolicyFile:Boolean = false;
        public var securityDomain:SecurityDomain = null;

        public function LoaderContext(checkPolicyFile:Boolean = false, applicationDomain:ApplicationDomain = null, securityDomain:SecurityDomain = null)
        {
            this.checkPolicyFile = checkPolicyFile;
            this.applicationDomain = applicationDomain;
            this.securityDomain = securityDomain;
            return;
        }// end function

    }
}
