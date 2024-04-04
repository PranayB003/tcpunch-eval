## Evaluating TCPunch on Google Cloud

As of now, it has been verified that a connection can be established between 2
VMs on Google Cloud. I'm working on veryfying the same between a Cloud Run
instance and a VM.

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
Compute Engine and Cloud Run APIs.

- A hole punching server (hosted on a GCP VM) is already running and accessible
through the public IP `34.16.205.190`. You could create your own server using:
```
gcloud compute instances create-with-container hole-punching-server --project=tcpunch-testing --machine-type=e2-micro --container-image=docker.io/pranayb003/tcpunch-eval:latest --container-stdin --container-command=./bin/tcpunchd
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
