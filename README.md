## Evaluating TCPunch on Google Cloud

As of now, it has been verified that a connection can be established between 2
VMs on Google Cloud. Establishing a connection between a VM and a Cloud Run
instance fails because only a single port (8080 by default) can accept
connections, and only over HTTP. The outgoing request from the function reaches
the hole punching server, and the server responds to both the VM and the
function. However, the response from the hole punching server is blocked on the
function since that port is not open. Unlike the VMs, where setting firewall
rules allowed incoming connections on all ports, a similar thing cannot be done
for Cloud Run or Cloud Function instances.

I'm thinking of modifying TCPunch by allowing clients to specify additional
`response_PORT` and `response_PROTOCOL` parameters while calling `pair()`, for 
the server to send its response to, as a way to get around the above
limitation.

## Development

Clone the repository:
```
git clone https://github.com/PranayB003/tcpunch-eval.git
cd tcpunch-eval
```

Pull the TCPunch submodule:
```
git submodule update --init
```

Run the setup script to build all libraries and binaries for testing TCPunch
locally:
```
./setup.sh
```

To build the docker image containing the compiled hole punching server and
client binaries and dependencies, run `docker build -t <image_name> .` in the
root of the project.

## Reproducing the results

> [!NOTE]
> It is recommended to run the below steps in 
[cloud shell](https://cloud.google.com/shell) since the gcloud CLI is already
authenticated and other required tools are pre-installed.

Create a new Google Cloud project named `tcpunch-testing` (make suitable
replacements in the below commands if you choose a different name). Enable the
Compute Engine, Cloud Run, and Artifact Registry APIs.

- A hole punching server (hosted on a GCP VM) is already running and accessible
through the public IP `34.16.205.190`. You could create your own server using:
```
gcloud compute instances create-with-container hole-punching-server --project=tcpunch-testing --machine-type=e2-micro --container-image=docker.io/pranayb003/tcpunch-eval:latest --container-stdin --container-command=./bin/tcpunchd
```
- Allow incoming and outgoing traffic on all ports by creating two firewall
rules:
```
gcloud compute firewall-rules create allow-incoming --direction=ingress --action=allow --source-ranges=0.0.0.0/0 --rules=all
gcloud compute firewall-rules create allow-outgoing --direction=egress --action=allow --destination-ranges=0.0.0.0/0 --rules=all
```
- Create 2 VMs:
```
gcloud compute instances create-with-container node-a --project=tcpunch-testing --machine-type=e2-micro --container-image=docker.io/pranayb003/tcpunch-eval:latest
gcloud compute instances create-with-container node-b --project=tcpunch-testing --machine-type=e2-micro --container-image=docker.io/pranayb003/tcpunch-eval:latest
```
- SSH onto these VMs using the Google Cloud Console. Then run `docker run -it 
pranayb003/tcpunch-eval bash` followed by `./bin/node-b <IP>` and `./bin/node-a
<IP>` respectively where `<IP>` is the hole-punching server's public IP address.
If the connection is successfully established node B will receive the correct 
message from node A.

- Deploy a serverless function on Cloud Run by running these from the root of the
repository (replace "us-west4" with the region you chose earlier):
```
docker run --mount type=bind,source=./function/,target=/tmp/ --rm pranayb003/tcpunch-eval bash -c "rm -rf /tmp/deps/ && cd extern/tcpunch/client && mkdir -p /tmp/deps && cp ./tcpunch.h ./build/libtcpunch.a /tmp/deps/"

gcloud builds submit --machine-type=e2_highcpu_32 --tag us-west4-docker.pkg.dev/tcpunch-testing/tcpunch-eval-docker/function ./function/

gcloud run deploy serverless-node --image=us-west4-docker.pkg.dev/tcpunch-testing/tcpunch-eval-docker/function --allow-unauthenticated
```
- Call the function using `curl <URL>` where `<URL>` is the function URL. This
is displayed at the successful completion of the previous step and can also be
viewed from the Google Cloud Console.
