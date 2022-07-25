# Wireshark:
ssh kali "tcpdump -i lo -s0 -U -w - 'port 8000'" | wireshark -k -i -

# Slow server:
./build/server 127.0.0.1 8000 1K 0.5s
./build/client 127.0.0.1 8000 100K 1ms

# Echo server:
./build/echo_server 127.0.0.1 8000
./build/echo_client 127.0.0.1 8000
