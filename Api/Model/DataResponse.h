#ifndef _DATARESPONSE_H
#define _DATARESPONSE_H

#include <SPI.h>

class DataResponse {
    public: 
        int StatusCode;
        String Content;
        String Error;
        bool Success;

        DataResponse();
        DataResponse ErrorResponse(String message);
        DataResponse SuccessData();
        DataResponse SuccessData(String pinContent);
};

#endif