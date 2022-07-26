# Local Wireshark:
wireshark -f "host 212.183.159.230" -i en0 -k
# Download file:
curl -o 5MB.bin http://212.183.159.230/5MB.zip
# Statistics -> TCP Stream Graphs -> Window Scaling

# SSH Wireshark:
ssh kali "tcpdump -i lo -s0 -U -w - 'port 8000'" | wireshark -k -i -

# Slow server:
./build/server 127.0.0.1 8000 1K 0.5s
./build/client 127.0.0.1 8000 100K 1ms

# Msg size Echo server:
./build/echo_server 127.0.0.1 8000
./build/echo_client 127.0.0.1 8000

# Const size Echo server:
./build/char_server 127.0.0.1 8000
./build/char_client 127.0.0.1 8000
