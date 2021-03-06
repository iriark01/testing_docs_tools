/* NetworkSocketAPI Example Program
 * Copyright (c) 2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "LWIPInterface.h"
#include "TCPSocket.h"

LWIPInterface eth;

DigitalOut led(LED_GREEN);
void blink()
{
    led = !led;
}

int main()
{
    Ticker blinky;
    blinky.attach(blink, 0.4f);

    printf("NetworkSocketAPI Example\r\n");

    eth.connect();
    const char *ip = eth.get_ip_address();
    const char *mac = eth.get_mac_address();
    printf("IP address is: %s\r\n", ip ? ip : "No IP");
    printf("MAC address is: %s\r\n", mac ? mac : "No MAC");
    
    SocketAddress addr(&eth, "mbed.org");
    printf("mbed.org resolved to: %s\r\n", addr.get_ip_address());

    TCPSocket socket(&eth);
    socket.connect("4.ifcfg.me", 23);

    char buffer[64];
    int count = socket.recv(buffer, sizeof buffer);
    printf("public IP address is: %.15s\r\n", &buffer[15]);
    
    socket.close();
    eth.disconnect();

    printf("Done\r\n");
}
