#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <string.h>

sf::TcpListener listener;
sf::TcpSocket client;

char data[100];
std::size_t recieved;
std::size_t actual_recieved;

std::string empty_str;
std::string info_response = "SFML network server\n";

void reset_buffer() {
    strcpy(data, empty_str.c_str());
}

std::string to_string() {
    data[strlen(data)-2] = '\0';

    return std::string(data);
}

int main() {
    listener.listen(8080);
    listener.accept(client);
    while(true) {
        client.receive(data, 100, recieved);
        actual_recieved = recieved - 2; // remove CRLF sequence from size;

        std::string msg = to_string();
        if (msg == "info") {
            client.send(info_response.c_str(), strlen(info_response.c_str()));
        }

        reset_buffer();
    }
}
