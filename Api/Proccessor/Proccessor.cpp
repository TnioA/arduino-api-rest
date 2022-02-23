#include <Proccessor.h>
#include <Router.h>
#include <SPI.h>
#include <Ethernet.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

Proccessor::Proccessor(EthernetClient externalClient){
    _client = externalClient;
    _router = Router();
}

void Proccessor::ProccessRequest() {
    if (_client) {
        boolean currentLineIsBlank = true;
        String requestContent = "";
        while (_client.connected()) {
            if (_client.available()) {
                char c = _client.read();
                requestContent += c;
                
                if (c == '\n' && currentLineIsBlank) break;
                if (c == '\n') currentLineIsBlank = true;
                else if (c != '\r') currentLineIsBlank = false;
            }
        }
    
        // response client
        String * response = _router.RouteRequest(GetMethod(requestContent), GetUrl(requestContent));
        SetHeaders(_client, atoi(response[0].c_str()));
        _client.print(response[1]);

        // close connection
        delay(1);
        _client.stop();
    }
}

String Proccessor::GetMethod(String fullRequest)
{
    if(strncmp(fullRequest.c_str(), "POST", strlen("POST")) == 0) return "POST";
    else if(strncmp(fullRequest.c_str(), "PUT", strlen("PUT")) == 0) return "PUT";
    else if(strncmp(fullRequest.c_str(), "DELETE", strlen("DELETE")) == 0) return "DELETE";
    else return "GET";
}

String Proccessor::GetUrl(String fullRequest){
    String url = "";
    bool aux = 0;

    for(int i=0;i<strlen(fullRequest.c_str());i++){
        if(fullRequest[i] == ' ' && aux == 1){
            aux = 0;
            break;
        }

        if(aux == 1){
            url = url + fullRequest[i];
        }

        if(fullRequest[i] == ' ' && aux == 0){
            aux = 1;
        }
    }

    return url;  
}

void Proccessor::SetHeaders(EthernetClient client, int statusCode){
    switch (statusCode){
        case 200:
            client.println("HTTP/1.1 200 OK");
            break;
        case 400:
            client.println("HTTP/1.1 400 Bad Request");
            break;
        case 401:
            client.println("HTTP/1.1 401 Unauthorized");
            break;
        case 403:
            client.println("HTTP/1.1 403 Forbidden");
            break;
        default:
            client.println("HTTP/1.1 400 Bad Request");
            break;
    }

    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println("Access-Control-Allow-Origin: *");
    //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
    client.println();
}