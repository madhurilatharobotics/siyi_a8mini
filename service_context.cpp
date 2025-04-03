#include <arpa/inet.h>

#include <stdlib.h> 
#include <sstream>
#include <iomanip>

#include "stools.h"
#include "service_context.h"

ServiceContext::ServiceContext():
    port(8080),
    user("admin"),
    password("admin"),
    manufacturer("HC Robotics"),
    model("HCR SIYI DN"),
    firmware_version("1.0.0"),
    serial_number("HCR_001"),
    hardware_id("HC0712"),
    tz_format(TZ_UTC_OFFSET){

}

std::string ServiceContext::get_time_zone() const {
    #define HH_FORMAT   std::setfill('0') << std::internal << std::setw(3) << std::showpos
    #define MM_FORMAT   ':' << std::setw(2) << std::noshowpos

    std::ostringstream res;
    char* TZ_env;
    const time_t  timestamp = time(nullptr);
    struct tm    *now       = localtime(&timestamp);

    int hh = now->tm_gmtoff/3600;
    int mm = abs(now->tm_gmtoff%60);

    switch (tz_format)
    {
        case TZ_UTC_OFFSET:
            res << HH_FORMAT << hh << MM_FORMAT << mm;
            return res.str();


        case TZ_GMT_OFFSET:
            res << HH_FORMAT << -hh << MM_FORMAT << mm;
            return res.str();


        case TZ_UTC:
            res << "UTC" << HH_FORMAT << hh << MM_FORMAT << mm;
            return res.str();


        case TZ_GMT:
            res << "GMT" << HH_FORMAT << -hh << MM_FORMAT << mm;
            return res.str();


        case TZ_ENV:
            TZ_env = getenv("TZ");
            return (TZ_env ? TZ_env : "UTC+00");


        default:
            TZ_env = getenv("TZ_ONVIF");
            return (TZ_env ? TZ_env : "UTC+00");
    }
}

tt__SystemDateTime* ServiceContext::get_SystemDateAndTime(struct soap* soap)
{
    const time_t  timestamp = time(nullptr);
    struct tm    *time_info = localtime(&timestamp);

    auto res = soap_new_req_tt__SystemDateTime(soap,
                                               tt__SetDateTimeType::tt__SetDateTimeType__Manual,
                                               (time_info->tm_isdst > 0));

    if(res)
    {
        res->TimeZone      = soap_new_req_tt__TimeZone(soap, get_time_zone());
        res->LocalDateTime = get_DateTime(soap, time_info);
        res->UTCDateTime   = get_DateTime(soap, gmtime(&timestamp));
    }

    return res;
}

tt__DateTime* ServiceContext::get_DateTime(struct soap* soap, tm* time_info)
{
    return soap_new_req_tt__DateTime(
               soap,
               soap_new_req_tt__Time(
                   soap,
                   time_info->tm_hour,
                   time_info->tm_min,
                   time_info->tm_sec
               ),
               soap_new_req_tt__Date(
                   soap,
                   time_info->tm_year+1900,
                   time_info->tm_mon+1,
                   time_info->tm_mday
               )
           );
}

bool ServiceContext::set_tz_format(const char* new_val)
{
    std::istringstream ss(new_val);
    unsigned int tmp_val;
    ss >> tmp_val;


    if( tmp_val >= TZ_CNT_FORMATS )
    {
        str_err = "tz_format is not supported";
        return false;
    }


    tz_format = static_cast<TimeZoneForamt>(tmp_val);
    return true;
}

std::string ServiceContext::getServerIpFromClientIp(uint32_t client_ip) const
{
    // char server_ip[INET_ADDRSTRLEN];


    // if (eth_ifs.size() == 1)
    // {
    //     eth_ifs[0].get_ip(server_ip);
    //     return server_ip;
    // }

    // for(size_t i = 0; i < eth_ifs.size(); ++i)
    // {
    //     uint32_t if_ip, if_mask;
    //     eth_ifs[i].get_ip(&if_ip);
    //     eth_ifs[i].get_mask(&if_mask);

    //     if( (if_ip & if_mask) == (client_ip & if_mask) )
    //     {
    //         eth_ifs[i].get_ip(server_ip);
    //         return server_ip;
    //     }
    // }


    return "192.168.144.33";  
}



std::string ServiceContext::getXAddr(struct soap *soap) const
{
    std::ostringstream os;

    os << "http://" << getServerIpFromClientIp(htonl(soap->ip)) << ":" << port << "/onvif/device_service";

    return os.str();
}

tds__DeviceServiceCapabilities* ServiceContext::getDeviceServiceCapabilities(struct soap* soap)
{
    auto *caps = soap_new_tds__DeviceServiceCapabilities(soap);
    if (caps)
    {
        // ✅ Use tds__SystemCapabilities instead of tt__SystemCapabilities
        caps->System = soap_new_tds__SystemCapabilities(soap);
        caps->Security = soap_new_tds__SecurityCapabilities(soap);
        caps->Network = soap_new_tds__NetworkCapabilities(soap);

        // ✅ Fix bool assignment
        caps->System->DiscoveryResolve = soap_new_bool(soap);
        *(caps->System->DiscoveryResolve) = true;
    }
    return caps;
}

bool ServiceContext::add_profile(const StreamProfile &profile)
{
    if( !profile.is_valid() )
    {
        str_err = "profile has unset parameters";
        return false;
    }


    if( profiles.find(profile.get_name()) != profiles.end() )
    {
        str_err = "profile: " + profile.get_name() +  " already exist";
        return false;
    }


    profiles[profile.get_name()] = profile;
    return true;
}

std::string ServiceContext::get_stream_uri(const std::string &profile_url, uint32_t client_ip) const
{
    std::string uri(profile_url);
    std::string template_str("%s");


    auto it = uri.find(template_str, 0);

    if( it != std::string::npos )
        uri.replace(it, template_str.size(), getServerIpFromClientIp(client_ip));


    return uri;
}

tds__DeviceServiceCapabilities *ServiceContext::getDeviceServiceCapabilities(struct soap *soap)
{
    auto net_caps = soap_new_req_tds__NetworkCapabilities(soap);
    if(net_caps)
    {
        net_caps->IPFilter            = soap_new_ptr(soap, false);
        net_caps->ZeroConfiguration   = soap_new_ptr(soap, false);
        net_caps->IPVersion6          = soap_new_ptr(soap, false);
        net_caps->DynDNS              = soap_new_ptr(soap, false);
        net_caps->Dot11Configuration  = soap_new_ptr(soap, false);
        net_caps->Dot1XConfigurations = soap_new_ptr(soap, 0);
        net_caps->HostnameFromDHCP    = soap_new_ptr(soap, false);
        net_caps->NTP                 = soap_new_ptr(soap, 0);
        net_caps->DHCPv6              = soap_new_ptr(soap, false);
    }


    auto sec_caps = soap_new_req_tds__SecurityCapabilities(soap);
    if(sec_caps)
    {
        sec_caps->TLS1_x002e0          = soap_new_ptr(soap, false);
        sec_caps->TLS1_x002e1          = soap_new_ptr(soap, false);
        sec_caps->TLS1_x002e2          = soap_new_ptr(soap, false);
        sec_caps->OnboardKeyGeneration = soap_new_ptr(soap, false);
        sec_caps->AccessPolicyConfig   = soap_new_ptr(soap, false);
        sec_caps->DefaultAccessPolicy  = soap_new_ptr(soap, false);
        sec_caps->Dot1X                = soap_new_ptr(soap, false);
        sec_caps->RemoteUserHandling   = soap_new_ptr(soap, false);
        sec_caps->X_x002e509Token      = soap_new_ptr(soap, false);
        sec_caps->SAMLToken            = soap_new_ptr(soap, false);
        sec_caps->KerberosToken        = soap_new_ptr(soap, false);
        sec_caps->UsernameToken        = soap_new_ptr(soap, false);
        sec_caps->HttpDigest           = soap_new_ptr(soap, false);
        sec_caps->RELToken             = soap_new_ptr(soap, false);
        sec_caps->MaxUsers             = soap_new_ptr(soap, 0);
        sec_caps->MaxUserNameLength    = soap_new_ptr(soap, 0);
        sec_caps->MaxPasswordLength    = soap_new_ptr(soap, 0);
    }


    auto sys_caps = soap_new_req_tds__SystemCapabilities(soap);
    if(sys_caps)
    {
        sys_caps->DiscoveryResolve       = soap_new_ptr(soap, true);
        sys_caps->DiscoveryBye           = soap_new_ptr(soap, true);
        sys_caps->RemoteDiscovery        = soap_new_ptr(soap, true);
        sys_caps->SystemBackup           = soap_new_ptr(soap, false);
        sys_caps->SystemLogging          = soap_new_ptr(soap, false);
        sys_caps->FirmwareUpgrade        = soap_new_ptr(soap, false);
        sys_caps->HttpFirmwareUpgrade    = soap_new_ptr(soap, false);
        sys_caps->HttpSystemBackup       = soap_new_ptr(soap, false);
        sys_caps->HttpSystemLogging      = soap_new_ptr(soap, false);
        sys_caps->HttpSupportInformation = soap_new_ptr(soap, false);
        sys_caps->StorageConfiguration   = soap_new_ptr(soap, false);
    }


    return soap_new_req_tds__DeviceServiceCapabilities(soap, net_caps, sec_caps, sys_caps);
}



trt__Capabilities *ServiceContext::getMediaServiceCapabilities(struct soap *soap)
{
    auto prof_caps = soap_new_req_trt__ProfileCapabilities(soap);
    if(prof_caps)
        prof_caps->MaximumNumberOfProfiles = soap_new_ptr(soap, 1);


    auto str_caps = soap_new_req_trt__StreamingCapabilities(soap);
    if(str_caps)
    {
        str_caps->RTPMulticast             = soap_new_ptr(soap, false);
        str_caps->RTP_USCORETCP            = soap_new_ptr(soap, false);
        str_caps->RTP_USCORERTSP_USCORETCP = soap_new_ptr(soap, true);
    }


    auto caps = soap_new_req_trt__Capabilities(soap, prof_caps, str_caps);
    if(caps)
    {
        auto& profiles = get_profiles();
        for( auto& p : profiles )
        {
            if (( !p.second.get_snapurl().empty() ) && ( caps->SnapshotUri == nullptr ))
            {
                caps->SnapshotUri = soap_new_ptr(soap, true);
            }
        }

        caps->Rotation        = soap_new_ptr(soap, false);
        caps->VideoSourceMode = soap_new_ptr(soap, false);
        caps->OSD             = soap_new_ptr(soap, false);
        caps->EXICompression  = soap_new_ptr(soap, false);
    }


    return caps;
}

tt__DeviceCapabilities *ServiceContext::getDeviceCapabilities(struct soap *soap, const std::string &XAddr) const
{
    auto dev_caps = soap_new_req_tt__DeviceCapabilities(soap, XAddr);
    if(!dev_caps)
        return nullptr;

    auto sys_caps = soap_new_tt__SystemCapabilities(soap);
    if(sys_caps)
    {
        sys_caps->DiscoveryResolve = false;
        sys_caps->DiscoveryBye     = false;
        sys_caps->RemoteDiscovery  = false;
        sys_caps->SystemBackup     = false;
        sys_caps->SystemLogging    = false;
        sys_caps->FirmwareUpgrade  = false;
        sys_caps->SupportedVersions.push_back(soap_new_req_tt__OnvifVersion(soap, 2, 4));

        dev_caps->System = sys_caps;
    }


    dev_caps->IO       = soap_new_req_tt__IOCapabilities(soap);
    dev_caps->Network  = soap_new_req_tt__NetworkCapabilities(soap);
    dev_caps->Security = soap_new_tt__SecurityCapabilities(soap);

    return dev_caps;
}



tt__MediaCapabilities *ServiceContext::getMediaCapabilities(struct soap *soap, const std::string &XAddr) const
{
    auto str_caps = soap_new_req_tt__RealTimeStreamingCapabilities(soap);
    if(str_caps)
    {
        str_caps->RTPMulticast             = soap_new_ptr(soap, false);
        str_caps->RTP_USCORETCP            = soap_new_ptr(soap, false);
        str_caps->RTP_USCORERTSP_USCORETCP = soap_new_ptr(soap, true);
    }

    return soap_new_req_tt__MediaCapabilities(soap, XAddr, str_caps);
}

// tt__NetworkInterface *ServiceContext::getNetworkInterface(struct soap *soap, const Eth_Dev_Param &eth_param) const
// {
//     char tmp_buf[20] = {0};
//     eth_param.get_hwaddr(tmp_buf);
//     std::string HwAddress(tmp_buf);

//     tmp_buf[0] = 0;
//     eth_param.get_ip(tmp_buf);
//     std::string IPv4Address(tmp_buf);


//     auto net_if = soap_new_req_tt__NetworkInterface(soap, true, eth_param.dev_name());
//     if(!net_if)
//         return nullptr;

//     net_if->Info = soap_new_req_tt__NetworkInterfaceInfo(soap, HwAddress);
//     if(net_if->Info)
//         net_if->Info->Name = soap_new_std_string(soap, eth_param.dev_name());


//     auto IPv4_prefix = soap_new_req_tt__PrefixedIPv4Address(soap, IPv4Address, eth_param.get_mask_prefix());
//     auto IPv4_config = soap_new_req_tt__IPv4Configuration(soap, false);
//     if(IPv4_config && IPv4_prefix)
//         IPv4_config->Manual.push_back(IPv4_prefix);


//     net_if->IPv4 = soap_new_req_tt__IPv4NetworkInterface(soap, true, IPv4_config);


//     return net_if;
// }

tptz__Capabilities* ServiceContext::getptzCapabilities(struct soap* soap, const std::string &XAddr) const
{
    auto *ptzCaps = soap_new_tptz__Capabilities(soap);
    if (ptzCaps)
    {
        ptzCaps->EFlip = soap_new_bool(soap);
        *(ptzCaps->EFlip) = true;
        
        ptzCaps->Reverse = soap_new_bool(soap);
        *(ptzCaps->Reverse) = true;

    }
    return ptzCaps;
}
tt__VideoSourceConfiguration* StreamProfile::get_video_src_cnf(struct soap *soap) const
{
    auto src_cfg = soap_new_tt__VideoSourceConfiguration(soap);

    if(src_cfg)
    {
        src_cfg->UseCount    = 1;
        src_cfg->Name        = name;
        src_cfg->token       = name;
        src_cfg->SourceToken = name;
        src_cfg->Bounds      = soap_new_req_tt__IntRectangle(soap, 0, 0, width, height);
    }

    return src_cfg;
}

tt__VideoEncoderConfiguration* StreamProfile::get_video_enc_cfg(struct soap *soap) const
{
    auto enc_cfg = soap_new_tt__VideoEncoderConfiguration(soap);

    if(enc_cfg)
    {
        enc_cfg->soap_default(soap);
        enc_cfg->UseCount           = 1;
        enc_cfg->Name               = name;
        enc_cfg->token              = name;
        enc_cfg->Resolution         = soap_new_req_tt__VideoResolution(soap, width, height);
        enc_cfg->RateControl        = soap_new_req_tt__VideoRateControl(soap, 0, 0, 0);
        enc_cfg->Encoding           = static_cast<tt__VideoEncoding>(type);
        enc_cfg->Multicast          = soap_new_tt__MulticastConfiguration(soap);
        if(enc_cfg->Multicast)
        {
            enc_cfg->Multicast->soap_default(soap);
            enc_cfg->Multicast->Address = soap_new_req_tt__IPAddress(soap, tt__IPType::tt__IPType__IPv4);
        }
    }

    return enc_cfg;
}

tt__Profile* StreamProfile::get_profile(struct soap *soap) const
{
    auto ctx     = (ServiceContext*)soap->user;
    auto profile = soap_new_tt__Profile(soap);

    if(!profile)
        return nullptr;

    profile->soap_default(soap);
    profile->Name  = name;
    profile->token = name;
    profile->fixed = soap_new_ptr(soap, true);

    profile->VideoSourceConfiguration  = get_video_src_cnf(soap);
    profile->VideoEncoderConfiguration = get_video_enc_cfg(soap);

    return profile;
}

tt__VideoSource* StreamProfile::get_video_src(soap *soap) const
{
    auto video_src = soap_new_tt__VideoSource(soap);
    if(!video_src)
        return nullptr;

    video_src->soap_default(soap);
    video_src->token      = name;
    video_src->Framerate  = 25;
    video_src->Resolution = soap_new_req_tt__VideoResolution(soap, width, height);
    video_src->Imaging    = soap_new_req_tt__ImagingSettings(soap);

    return video_src;
}

bool StreamProfile::set_name(const char *new_val)
{
    if(!new_val)
    {
        str_err = "Name is empty";
        return false;
    }


    name = new_val;
    return true;
}

bool StreamProfile::set_width(const char *new_val)
{

    std::istringstream ss(new_val);
    int tmp_val;
    ss >> tmp_val;


    if( (tmp_val < 100) || (tmp_val >= 10000) )
    {
        str_err = "width is bad, correct range: 100-10000";
        return false;
    }


    width = tmp_val;
    return true;
}

bool StreamProfile::set_height(const char *new_val)
{
    std::istringstream ss(new_val);
    int tmp_val;
    ss >> tmp_val;


    if( (tmp_val < 100) || (tmp_val >= 10000) )
    {
        str_err = "height is bad, correct range: 100-10000";
        return false;
    }


    height = tmp_val;
    return true;
}

bool StreamProfile::set_url(const char *new_val)
{
    if(!new_val)
    {
        str_err = "URL is empty";
        return false;
    }


    url = new_val;
    return true;
}

bool StreamProfile::set_snapurl(const char *new_val)
{
    if(!new_val)
    {
        str_err = "URL is empty";
        return false;
    }


    snapurl = new_val;
    return true;
}

bool StreamProfile::set_type(const char *new_val)
{
    std::string new_type(new_val);


    if( new_type == "JPEG" )
        type = static_cast<int>(tt__VideoEncoding::tt__VideoEncoding__JPEG);
    else if( new_type == "MPEG4" )
        type = static_cast<int>(tt__VideoEncoding::tt__VideoEncoding__MPEG4);
    else if( new_type == "H264" )
        type = static_cast<int>(tt__VideoEncoding::tt__VideoEncoding__H264);
    else
    {
        str_err = "type dont support";
        return false;
    }


    return true;
}

void StreamProfile::clear()
{
    name.clear();
    url.clear();
    snapurl.clear();

    width  = -1;
    height = -1;
    type   = -1;
}

bool StreamProfile::is_valid() const
{
    return ( !name.empty()  &&
             !url.empty()   &&
             (width  != -1) &&
             (height != -1) &&
             (type   != -1)
           );
}