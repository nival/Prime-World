package flash.net
{

    final public class NetStreamInfo extends Object
    {
        private var m_dataByteCount:Number;
        private var m_videoBufferLength:Number;
        private var m_audioBufferByteLength:Number;
        private var m_byteCount:Number;
        private var m_dataBytesPerSecond:Number;
        private var m_dataBufferLength:Number;
        private var m_srtt:Number;
        private var m_droppedFrames:Number;
        private var m_videoBufferByteLength:Number;
        private var m_videoByteCount:Number;
        private var m_audioByteCount:Number;
        private var m_audioLossRate:Number;
        private var m_dataBufferByteLength:Number;
        private var m_currentBytesPerSecond:Number;
        private var m_videoBytesPerSecond:Number;
        private var m_playbackBytesPerSecond:Number;
        private var m_audioBytesPerSecond:Number;
        private var m_audioBufferLength:Number;
        private var m_maxBytesPerSecond:Number;

        public function NetStreamInfo(curBPS:Number, byteCount:Number, maxBPS:Number, audioBPS:Number, audioByteCount:Number, videoBPS:Number, videoByteCount:Number, dataBPS:Number, dataByteCount:Number, playbackBPS:Number, droppedFrames:Number, audioBufferByteLength:Number, videoBufferByteLength:Number, dataBufferByteLength:Number, audioBufferLength:Number, videoBufferLength:Number, dataBufferLength:Number, srtt:Number, audioLossRate:Number)
        {
            this.m_currentBytesPerSecond = curBPS;
            this.m_byteCount = byteCount;
            this.m_maxBytesPerSecond = maxBPS;
            this.m_audioBytesPerSecond = audioBPS;
            this.m_audioByteCount = audioByteCount;
            this.m_videoBytesPerSecond = videoBPS;
            this.m_videoByteCount = videoByteCount;
            this.m_dataBytesPerSecond = dataBPS;
            this.m_dataByteCount = dataByteCount;
            this.m_playbackBytesPerSecond = playbackBPS;
            this.m_droppedFrames = droppedFrames;
            this.m_audioBufferByteLength = audioBufferByteLength;
            this.m_videoBufferByteLength = videoBufferByteLength;
            this.m_dataBufferByteLength = dataBufferByteLength;
            this.m_audioBufferLength = audioBufferLength;
            this.m_videoBufferLength = videoBufferLength;
            this.m_dataBufferLength = dataBufferLength;
            this.m_srtt = srtt;
            this.m_audioLossRate = audioLossRate;
            return;
        }// end function

        public function get videoBufferByteLength() : Number
        {
            return this.m_videoBufferByteLength;
        }// end function

        public function get droppedFrames() : Number
        {
            return this.m_droppedFrames;
        }// end function

        public function get dataBytesPerSecond() : Number
        {
            return this.m_dataBytesPerSecond;
        }// end function

        public function get dataBufferLength() : Number
        {
            return this.m_dataBufferLength;
        }// end function

        public function get audioLossRate() : Number
        {
            return this.m_audioLossRate;
        }// end function

        public function get currentBytesPerSecond() : Number
        {
            return this.m_currentBytesPerSecond;
        }// end function

        public function get videoBytesPerSecond() : Number
        {
            return this.m_videoBytesPerSecond;
        }// end function

        public function get videoByteCount() : Number
        {
            return this.m_videoByteCount;
        }// end function

        public function get SRTT() : Number
        {
            return this.m_srtt;
        }// end function

        public function get audioByteCount() : Number
        {
            return this.m_audioByteCount;
        }// end function

        public function get audioBytesPerSecond() : Number
        {
            return this.m_audioBytesPerSecond;
        }// end function

        public function get dataBufferByteLength() : Number
        {
            return this.m_dataBufferByteLength;
        }// end function

        public function get playbackBytesPerSecond() : Number
        {
            return this.m_playbackBytesPerSecond;
        }// end function

        public function get maxBytesPerSecond() : Number
        {
            return this.m_maxBytesPerSecond;
        }// end function

        public function get dataByteCount() : Number
        {
            return this.m_dataByteCount;
        }// end function

        public function get audioBufferLength() : Number
        {
            return this.m_audioBufferLength;
        }// end function

        public function get videoBufferLength() : Number
        {
            return this.m_videoBufferLength;
        }// end function

        public function get audioBufferByteLength() : Number
        {
            return this.m_audioBufferByteLength;
        }// end function

        public function get byteCount() : Number
        {
            return this.m_byteCount;
        }// end function

        public function toString() : String
        {
            return "currentBytesPerSecond=" + this.m_currentBytesPerSecond + " byteCount=" + this.m_byteCount + " maxBytesPerSecond=" + this.m_maxBytesPerSecond + " audioBytesPerSecond=" + this.m_audioBytesPerSecond + " audioByteCount=" + this.m_audioByteCount + " videoBytesPerSecond=" + this.m_videoBytesPerSecond + " videoByteCount=" + this.m_videoByteCount + " dataBytesPerSecond=" + this.m_dataBytesPerSecond + "dataByteCount=" + this.m_dataByteCount + " playbackBytesPerSecond=" + this.m_playbackBytesPerSecond + " droppedFrames=" + this.m_droppedFrames + " audioBufferLength=" + this.m_audioBufferLength + "videoBufferLength=" + this.m_videoBufferLength + " dataBufferLength=" + this.m_dataBufferLength + " audioBufferByteLength=" + this.m_audioBufferByteLength + " videoBufferByteLength=" + this.m_videoBufferByteLength + "dataBufferByteLength=" + this.m_dataBufferByteLength + " srtt=" + this.m_srtt + " audioLossRate=" + this.m_audioLossRate;
        }// end function

    }
}
