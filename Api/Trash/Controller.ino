void ControllerApi(EthernetClient client, String url){
  char params[10][100] = {"","","","","","","","","",""};
  int index = 0;
  String aux = "";
  String strsp = "\""; // VARIABLE USED TO ADD "" AT ATTR WITH STRING TYPE
  char* conc;

  // IF THERE IS A " " AT THE END, IT'S REMOVED
  if(url[url.length()-1] == ' '){
    url.remove(url.length()-1, 1);
  }

  // IF THERE IS A "/" AT THE END, IT'S REMOVED
  while(url[url.length()-1] == '/'){
    url.remove(url.length()-1, 1);
  }
  
  //SESSION FOR GETTING PARAMS
  if(url.length() > 2){
    for(int i = 0; i < url.length(); i++){
      if(url[i] == '/'){
        aux = "";
        if(i > 0){
          index++;   
        }
      }else{
        aux = url[i];
        char* foo = aux.c_str();
        strcat(params[index], foo);
      }
    }
  }

  client.print("{\"parameters\": {\"status\": 1,\"Number\":");
  client.print(index > 0 ? index : 0);
  client.print(",\"full-route\": \"");
  client.print(url);
  client.print("\"}, \"atributes\":[");  
  for(int i=0;i<=index;i++){
    if(strcmp(params[i], "") != 0){
      if(isdigit(*params[i])){
        client.print(params[i]);
      }else{
        client.print(strsp);
        client.print(params[i]);
        client.print(strsp);
      }
    }
    if(index > 0 && i < index){
      client.print(",");
    }
  }

  //GETTING CONTENT RETURN
  client.print("],\"response\":");

  //MAPPING ROUTES CONTENT
  if(strcmp(params[0], "") == 0){
    ReturnValues(client);   
  }
  else if(strcmp(params[0], "api") == 0){
    if(strcmp(params[1], "setpin") == 0){
      if(isdigit(*params[2])){
        if((strcmp(params[3], "true") == 0) || (strcmp(params[3], "false") == 0)){
          SetDigitalPin(client, atoi(params[2]), (strcmp(params[3], "true") == 0) ? true : false);
        }else{
          if(isdigit(*params[3])){
            SetAnalogPin(client, atoi(params[2]), atoi(params[3]));
          }else{
            ErrorMessage(client);
          }
        }
      }else{
        ErrorMessage(client);
      }
    }
    else if(strcmp(params[1], "getpin") == 0){
      if(isdigit(*params[2])){
        GetPin(client, atoi(params[2]));
      }else{
        ErrorMessage(client);
      }
    }
    else{
      ErrorMessage(client);
    }
  }
  else{
    ErrorMessage(client);
  }
  client.print("}");
  
}
