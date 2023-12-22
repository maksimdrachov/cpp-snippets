# C++ Code Snippets

## Setup

1. Install [Nix](https://nixos.org/download)

- Linux

```bash
sh <(curl -L https://nixos.org/nix/install) --daemon
```

- macOS

```bash
sh <(curl -L https://nixos.org/nix/install)
```

- Windows (WSL 2)

```bash
sh <(curl -L https://nixos.org/nix/install) --daemon
```

2. Open Nix Shell

```bash
cd ~/cpp-snippets
nix-shell
[nix-shell]$ cd 01_unique_ptr_custom_dtor
[nix-shell]$ mkdir build && cd build
[nix-shell]$ cmake ..
[nix-shell]$ make
[nix-shell]$ ./main
...
[nix-shell]$ exit
```
