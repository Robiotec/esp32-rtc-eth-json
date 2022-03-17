#include <ArduinoJson.h>

String createResponse(int statusCode, DynamicJsonDocument Json) {
  String response;
  switch (statusCode) {
    case 200:
      response = "HTTP/1.1 200 OK\r\n";
      break;
    case 404:
      response = "HTTP/1.1 404 Not found\r\n";
      break;
    default:
      response = "HTTP/1.1 500 Internal server error\r\n";
      break;
  }

  return response;
}

String createResponse(int statusCode) {
  String response;
  switch (statusCode) {
    case 200:
      response = "HTTP/1.1 200 OK\r\n";
      break;
    case 404:
      response = "HTTP/1.1 404 Not found\r\n";
      break;
    default:
      response = "HTTP/1.1 500 Internal server error\r\n";
      break;
  }

  return response;
}

String create404() {
  return createResponse(404);
}

void sendResponse(const String &response, EthernetClient &client) {
  client.print(response);
}