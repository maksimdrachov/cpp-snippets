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
[nix-shell:~/cpp-snippets]$ cd unique_ptr_custom_deleter
[nix-shell:~/cpp-snippets]$ mkdir build
[nix-shell:~/cpp-snippets]$ cmake ..
[nix-shell:~/cpp-snippets]$ make
[nix-shell:~/cpp-snippets]$ ./main
...
[nix-shell:~/cpp-snippets]$ exit
```
