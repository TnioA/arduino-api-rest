#include <DataResponse.h>
#include <SPI.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

DataResponse::DataResponse(){}

DataResponse DataResponse::ErrorResponse(String message){
    DataResponse response = DataResponse();
    response.StatusCode = 400;
    response.Success = false;
    response.Error = "{\"error\":\""+ message +"\",\"success\":\"false\"}";

    return response;
}

DataResponse DataResponse::SuccessData(){
    DataResponse response = DataResponse();
    response.StatusCode = 200;
    response.Success = true;
    response.Content += "{\"success\":\"true\"}";
    return response;
}

DataResponse DataResponse::SuccessData(String pinContent){
    DataResponse response = DataResponse();
    response.StatusCode = 200;
    response.Success = true;
    response.Content = "";
    response.Content += "{\"pin\":";
    response.Content += pinContent;
    response.Content += ",";
    response.Content += "\"success\":\"true\"}";

    return response;
}