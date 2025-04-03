#ifndef SERVICE_CONTEXT_H
#define SERVICE_CONTEXT_H

#include <map>
#include <string>
#include <vector>

#include "soapH.h"

class StreamProfile {
    public:
    struct PTZNode
    {
        bool enable;
    };

    PTZNode ptzNode;
        StreamProfile(){
            clear();
        }

        void clear();
        bool is_valid() const;

        std::string get_name() const {
            return name;
        }

        std::string get_url() const {
            return url;
        }

        std::string get_snapurl() const {
            return snapurl;
        }

        int get_height() const {
            return height;
        }

        int get_width() const {
            return width;
        }

        int get_type() const {
            return type;
        }

        bool set_name   (const char *new_val);
        bool set_width  (const char *new_val);
        bool set_height (const char *new_val);
        bool set_url    (const char *new_val);
        bool set_snapurl(const char *new_val);
        bool set_type   (const char *new_val);

        std::string get_str_err()  const { return str_err;         }
        const char* get_cstr_err() const { return str_err.c_str(); }

        tt__Profile* get_profile(struct soap *soap) const;
        tt__VideoSource* get_video_src(struct soap *soap) const;

        tt__VideoSourceConfiguration*  get_video_src_cnf(struct soap *soap) const;
        tt__VideoEncoderConfiguration* get_video_enc_cfg(struct soap *soap) const;
        
    private:
        std::string name;
        int width;
        int height;
        std::string url;
        std::string snapurl;
        int type;
        std::string str_err;
};


class ServiceContext
{
    public:

        enum TimeZoneForamt : unsigned int
        {
            TZ_UTC_OFFSET,   //[+|-]hh:mm
            TZ_GMT_OFFSET,   //[+|-]hh:mm     (reverse sign of TZ_UTC_OFFSET)
            TZ_UTC,          //UTC[+|-]hh:mm
            TZ_GMT,          //GMT[+|-]hh:mm  (reverse sign of TZ_UTC)
            TZ_ENV,          //value from TZ environment variable
            TZ_ONVIF_ENV,    //value from TZ_ONVIF environment variable(its not std)

            TZ_CNT_FORMATS   //Its not format! Its counter for use in code (max index)
        };

        ServiceContext();

        int         port;
        std::string user;
        std::string password;


        //Device Information
        std::string manufacturer;
        std::string model;
        std::string firmware_version;
        std::string serial_number;
        std::string hardware_id;

        std::vector<std::string> scopes;
        // std::vector<Eth_Dev_Param> eth_ifs; //ethernet interfaces

        std::string  get_time_zone() const;

        tt__SystemDateTime *get_SystemDateAndTime(struct soap* soap);
        tt__DateTime *get_DateTime(struct soap* soap, struct tm *time_info);

        TimeZoneForamt get_tz_format() const { return tz_format; }
        bool set_tz_format(const char *new_val);

        std::string getServerIpFromClientIp(uint32_t client_ip) const;
        std::string getXAddr(struct soap* soap) const;

        std::string get_str_err() const { return str_err;         }
        const char* get_cstr_err()const { return str_err.c_str(); }

        bool add_profile(const StreamProfile& profile);

        std::string get_stream_uri(const std::string& profile_url, uint32_t client_ip) const;

        const std::map<std::string, StreamProfile> &get_profiles(void) { return profiles; }

        // service capabilities
        tds__DeviceServiceCapabilities* getDeviceServiceCapabilities(struct soap* soap);
        trt__Capabilities*  getMediaServiceCapabilities    (struct soap* soap);
        tptz__Capabilities*  getptzCapabilities    (struct soap* soap);
         
        // capabilities
        tt__DeviceCapabilities* getDeviceCapabilities(struct soap* soap, const std::string &XAddr) const;
        tt__MediaCapabilities*  getMediaCapabilities (struct soap* soap, const std::string &XAddr) const;
        tptz__Capabilities* getptzCapabilities(struct soap* soap, const std::string &XAddr) const; 

        // tt__NetworkInterface*   getNetworkInterface(struct soap* soap, const Eth_Dev_Param& eth_param) const;
        const StreamProfile::PTZNode* get_ptz_node() const {
            if (profiles.empty()) {
                return nullptr;
            }
            return &(profiles.begin()->second.ptzNode);  // Get PTZNode from first profile
        }
    private:
        std::map<std::string, StreamProfile> profiles;
        TimeZoneForamt tz_format;
        std::string  str_err;
};

#endif