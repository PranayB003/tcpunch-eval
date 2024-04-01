## Usage

Clone the repository
```
git clone https://github.com/PranayB003/tcpunch-eval.git
cd tcpunch-eval
```

Run the setup script to build all libraries and binaries
```
./setup.sh
```

3 VMs need to be set up - the Hole Punching Server, Node A, and Node B. On the hole punching server, run `./extern/tcpunch/server/build/tcpunchd`.
On the other two compute instances, run `./build/node-b <IP>` and `./build/node-a <IP>` respectively, where `<IP>` is the hole-punching server's
public IP address. If the connection is successfully established, node B will receive the correct message from node A.
