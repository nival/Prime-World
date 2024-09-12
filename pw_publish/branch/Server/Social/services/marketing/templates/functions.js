function in_array(what, where) {
    for (var i = 0, length_array = where.length; i < length_array; i++) {
        if (what == where[i]) {
            return true;
        }
    }
    return false;
}

function getURLParameter(name) {
    return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|$)').exec(location.search) || [, ""])[1].replace(/\+/g, '%20')) || null;
}

function addLocaleToSubid(value) {
    var aHost = window.location.host.split('.');
    return (value != null) ? value + "-" + aHost[0] : aHost[0];
}

function sendVisit(ms_url, tracking_key, afterSend, partner_param, subid_param) {
    var sPartner = getURLParameter('p');
    if (sPartner)
        sPartner = sPartner.toLowerCase();
    partner_param = partner_param || sPartner;
    subid_param = subid_param || getURLParameter('subid');
    afterSend = afterSend || function () {
    };

    if (typeof tracking_key === 'undefined') {
        afterSend();
        return false;
    }

    if (tracking_key && !window.no_visit_event) {
        var partner_id = partner_param;
        var subid = subid_param;
        var puid = '';
        var paramsRE = /[а-яА-Я ]/;
        if (paramsRE.test(decodeURIComponent(window.location))) {
            partner_id = "pwpartnererror";
            puid = "";
            subid = "";
        }
        else {
            if (getURLParameter('zanpid')) {
                partner_id = 'zanox';
                puid = getURLParameter('zanpid');
            }
            else if (getURLParameter('prx')) {
                puid = getURLParameter('prx');
            }
            else if (typeof cbnTrackerURL != "undefined") {
                partner_id = "cbn";
                cbnParams = decodeURIComponent(cbnTrackerURL).split('&');
                subid = cbnParams[0];
                cbnParams.shift();
                puid = cbnParams.join('(|)');
            }
            else
                puid = encodeURIComponent(window.location.search.replace(/\?/g, ""));

            switch (partner_id) {
                case "admitad3":
                    puid = getURLParameter('uid');
                    break;
                case "hiconversion":
                    puid = getURLParameter('utm_content');
                    break;
                case "aw":
                    puid = getURLParameter('gclid');
                    if (!puid) {
                        puid = getURLParameter('dclid');
                    }
                    break;
                case "mixmarket":
                    puid = getURLParameter('mixcl');
                    break;
                case "mixmrk":
                    partner_id = "mixmarket";
                    puid = getURLParameter('referal_uid');
                    break;
                case "2ad1":
                    puid = getURLParameter('referal_uid');
                    break;
                case "ad1":
                    puid = getURLParameter('referal_uid');
                    break;
                case "adgor":
                    partner_id = "adgorythmsr";
                    puid = getURLParameter('sspdata');
                    subid = addLocaleToSubid(subid);
                    break;
                case "planb":
                    var planbRE = /^[0-9-]+$/;
                    if (!planbRE.test(puid)) {
                        partner_id = "pwpartnererror_planb";
                        puid = "";
                        subid = "";
                    }
                    break;
                case "kadam":
                    puid = getURLParameter('data');
                    break;
                case "advertstar":
                    puid = getURLParameter('astt');
                    break;
                case "adcash":
                    puid = getURLParameter('cid');
                    break;
                case "adlabs":
                    puid = getURLParameter('ext_meta_id');
                    break;
                case "tradetracker":
                    puid = getURLParameter('ttdata');
                    break;
                case "admitad2":
                    puid = getURLParameter('uid');
                    break;
                case "admitadde":
                case "admitadus":
                    puid = getURLParameter('uid');
                    break;
                case "cpaden":
                    puid = getURLParameter('uid');
                    break;
                case 'inglde':
                    if (getURLParameter('clickID'))
                        puid = getURLParameter('clickID');
                    else if (getURLParameter('clickid'))
                        puid = getURLParameter('clickid');
                    break;
                case 'linkprofit':
                    if (getURLParameter('AffiliateID'))
                        puid = getURLParameter('AffiliateID');
                    else if (getURLParameter('affiliateid'))
                        puid = getURLParameter('affiliateid');
                    break;
            }
        }
        if (partner_id) {
            var partner_params = '';
            if (puid) {
                partner_params += '&puid=' + puid;
            }
            if (subid) {
                partner_params += '&subid=' + subid;
            }
            $.ajax(
                {
                    url: ms_url + '/event?muid=' + tracking_key + '&partner=' + partner_id + partner_params,
                    success: afterSend,
                    error: afterSend
                });
            return true;
        }
        else {
            var locale = window.location.host.split('.')[0];
            $.ajax(
                {
                    url: ms_url + '/event?muid=' + tracking_key + '&partner=pw' + locale + '&puid=' + puid,
                    success: afterSend,
                    error: afterSend
                });
            return true;
        }
    }
    return false;
}