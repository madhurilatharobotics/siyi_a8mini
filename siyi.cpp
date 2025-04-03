#include "soapH.h"
#include "MediaBinding.nsmap"
#include "sdk.h" 

#define SOAP_DEBUG

int main() {
    int port = 8080;
    struct soap *soap = soap_new();
    soap_set_recv_logfile(soap, NULL);  
    soap_set_sent_logfile(soap, NULL);

    SIYI_SDK siyi_sdk("192.168.2.25", 37260);


    if (siyi_sdk.request_follow_mode()) {  
        std::cout << "Follow mode activated successfully!" << std::endl;
    } else {
        std::cerr << "Failed to activate follow mode!" << std::endl;
    }

    if (!soap_valid_socket(soap_bind(soap, NULL, port, 100))) {
        std::cerr << "! Failed to bind service socket." << std::endl;
        soap_print_fault(soap, stderr);
        soap_destroy(soap);
        soap_end(soap);
        soap_free(soap);
        return 1;
    }

    std::cout << "Server started on port " << port << std::endl;

    while (true) {
        if (!soap_valid_socket(soap_accept(soap))) {
            std::cerr << "! Failed to accept connection." << std::endl;
            soap_print_fault(soap, stderr);
            continue;
        }

        if (soap_serve(soap) != SOAP_OK) {
            soap_print_fault(soap, stderr);
        }
        
        soap_destroy(soap);
        soap_end(soap);
    }

    soap_free(soap);
    std::cerr << "Exiting services loop." << std::endl;
    return 0;
}
