# Filedrop
Filedrop is a basic filesharing program which allows the user to share a file over the network with another machine.

## Compilation
Filedrop is very basic to setup:
```bash
git clone https://github.com/tomScheers/filedrop
cd filedrop
make
```
The binary will be located at ./bin/filedrop

## Usage
If you want to share a file with someone you would run the following:
```bash
bin/filedrop send
```

Now, for the user receiving it:
```bash
bin/filedrop receive -ip [SENDER IP ADDRESS] -o [OUTPUT FILE]
```

You can modify the port for both receiving and sending using the `-p` flag.

### Flags
#### Receiving

| Flag  | Purpose                                            |
|-------|----------------------------------------------------|
| `-o`  | Set the output file path                           |
| `-p`  | Set the port on which you want to receive the file |
| `-ip` | IP address of the machine sending the file         |
| `-h`  | Open help menu                                     |

#### Sending

| Flag  | Purpose                                            |
|-------|----------------------------------------------------|
| `-p`  | Set the port on which you want to receive the file |
| `-h`  | Open help menu                                     |
