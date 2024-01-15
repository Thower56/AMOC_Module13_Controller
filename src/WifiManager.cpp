#include <WifiManager.h>

WifiManager::WifiManager(){};

WifiManager::WifiManager(String ssid, String password)
{
    Serial.println("Connection to : " + ssid);
    int nbEssais = 0;
    int nbEssaisMaximum = 100;
    WiFi.begin(ssid, password);

    Serial.print("Connexion : ");
    while (nbEssais < nbEssaisMaximum && WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        nbEssais++;
    }
    Serial.println("");

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Connecté au réseau WiFi, adresse IP : ");
        Serial.println(WiFi.localIP());
        Serial.println("");
    }
    else{
      Serial.println("Connection failed");
      Serial.println(WiFi.status());
    }
};

String WifiManager::GetJsonFromAPI(String api)
{
    String res = "";
  if(WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi is connected");
    Serial.println("Trying to get the string from the API...");
    String url = api;
    HTTPClient httpClient;
    Serial.println("HttpClient begin request");
    httpClient.begin(url);
    Serial.println("Getting code status...");
    int codeStatut = httpClient.GET();
    Serial.println("Code status: " + String(codeStatut));

    if(codeStatut != 200){
      Serial.println("Code status is not equal to 200");
      Serial.println(HTTPClient::errorToString(codeStatut));
    }
    else
    {
      Serial.println("Getting the response...");
      res = httpClient.getString();
      Serial.println("Reponse : " + res);
    }
  } 
  else 
  {
    Serial.println("Non connecte");
  }

  return res;
};

void WifiManager::PutJsonToAPI(String api, String json){
  if(WiFi.status() == WL_CONNECTED){
    String url = api;
    HTTPClient httpClient;
    httpClient.begin(url);
    Serial.println("");
    Serial.println("#####| PutJsonToAPI |#####");
    Serial.println("Url : " + url);
    Serial.println("Trying to put in API... : " + json);
    httpClient.addHeader("Content-Type", "application/json");
    int codeStatut = httpClient.PUT(json);

    if(codeStatut != 200){
      Serial.println("codeStatut is not 200 (PutJsonToAPI)");
      Serial.println("CodeStatus: " + String(codeStatut));
      Serial.println(HTTPClient::errorToString(codeStatut));
    }
  }
};

String WifiManager::GetIp()
{
    return String(WiFi.localIP());
};

String WifiManager::obtenirIPPublique(){
  String res = "";
  if(WiFi.status() == WL_CONNECTED)
  {
    String url = "https://ifconfig.co/json";
    HTTPClient httpClient;
    httpClient.begin(url);
    int codeStatus = httpClient.GET();

    if(codeStatus != 200){
      Serial.println(HTTPClient::errorToString(codeStatus));
    }else{
      res = httpClient.getString();
    }
  }
  else
  {
    Serial.println("Non connecte");
  }

  return res;
}

bool WifiManager::isConnected(){
  return WiFi.status() == WL_CONNECTED;
};