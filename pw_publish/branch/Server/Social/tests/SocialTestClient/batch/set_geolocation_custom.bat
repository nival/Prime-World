pushd ..
python main.py --scenario=set_geolocation --geolocation=%1 --snid=fb --snuid=%2 --sntoken=%3 --threads=1 --loglevel=warning --verbose=2 --login=http://pw.nivalnetwork.com:88 --ping_wait=5.0 --period=0.3
popd
