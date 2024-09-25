package flash.system
{

    public class JPEGLoaderContext extends LoaderContext
    {
        public var deblockingFilter:Number = 0;

        public function JPEGLoaderContext(deblockingFilter:Number = 0, checkPolicyFile:Boolean = false, applicationDomain:ApplicationDomain = null, securityDomain:SecurityDomain = null)
        {
            super(checkPolicyFile, applicationDomain, securityDomain);
            this.deblockingFilter = deblockingFilter;
            return;
        }// end function

    }
}
