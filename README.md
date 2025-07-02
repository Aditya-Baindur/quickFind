# QuickFind - The terminal buddy

<p align="center">
  <img src="demo.gif" alt="QuickFind demo" width="700">
</p>

Please note that this program is intended for use on **macOS, Ubuntu, and Debian** and has NOT been tested on Windows, WSL, or other Linux distributions (like Arch, Kali, etc...). We recommend using one of the supported platforms for best results and smoothest setup experience.

If you would like to build support for other environments or enhance the existing functionality, check out the [Contributing](#contributing) section below for how to get started.

If you prefer using shell specific scripts in ~/.zshrc or ~/.bashrc, you should checkout the [shell-wrappers](/quickFind/shell-wrappers/) folder

---

## Table of Contents

* [Introduction](#introduction)
* [Installation](#installation)
* [Usage](#usage)
* [Advanced Features](#advanced-features)
* [Uninstallation Guide](#uninstallation)
* [Troubleshooting](#troubleshooting)
* [Contributing](#contributing)
* [License](#license)

---

## Introduction

Tired of navigating deep folder trees manually? Spending too much time `cd`-ing around a large codebase or multi-repo setup?

**QuickFind** lets you save aliases to directories and instantly jump to them with short commands. It’s like a bookmark system for your terminal — fast, efficient, and shell-agnostic. This is especially useful when working across large codebases, remote development environments, or within monorepos with complex folder structures.

For example, instead of typing:

```bash
cd ~/Documents/work/projects/2025/quickfind/shell-wrappers
```

You can do:

```bash
qfcd shell
```

And you'll be taken there — from **anywhere** in your terminal session!

This works across all major POSIX shells (`bash`, `zsh`, `sh`, etc.) and is particularly powerful for developers and collaborators working in shared directory structures or remote development containers.

---

## Installation

The easiest way to get started is with Homebrew:

```bash
brew install aditya-baindur/quickfind/quickfind
```

If you **do not have Homebrew** installed, you can install QuickFind manually:

````bash
git clone https://github.com/Aditya-Baindur/quickFind.git 
cd quickFind

# You will need to install make if it is not already installed:
# Download it from: https://www.gnu.org/software/make

# Then you can run:
make install
```bash
brew install aditya-baindur/quickfind/quickfind
````

Or, step-by-step:

```bash
brew tap aditya-baindur/quickfind
brew install quickfind
```

Once installed, you'll be prompted to enable the `qfcd()` helper function. This may require `sudo` because it writes to a system-wide profile file (`/etc/profile.d/qfcd.sh`) to ensure compatibility with all login shells.

> 🧠 To use `qfcd` immediately without restarting your shell:
>
> ```bash
> . /etc/profile.d/qfcd.sh
> ```

---

## Usage

Once installed, use `quickfind` to create and manage directory shortcuts (aka "aliases"). These are stored locally and are available from any terminal session.

| Command                 | Description                                        | Example                   |
| ----------------------- | -------------------------------------------------- | ------------------------- |
| `quickfind init <name>` | Saves the current working directory as `<name>`    | `quickfind init projectx` |
| `quickfind rmv <name>`  | Deletes the saved alias `<name>`                   | `quickfind rmv projectx`  |
| `quickfind list`        | Displays all aliases and their corresponding paths | `quickfind list`          |
| `quickfind cd <name>`   | Outputs the full path of a saved alias             | `quickfind cd projectx`   |
| `quickfind <name>`      | Shorthand for printing the alias path              | `quickfind projectx`      |

You can also view usage instructions and version info:

```bash
quickfind --help
quickfind --version
```

### Jumping with `qfcd`

Once the helper function is installed, you can jump to any saved alias with one short command:

```bash
qfcd <alias>
```

It behaves just like `cd`, but it resolves the alias via `quickfind` under the hood.

### Examples

```bash
$ cd ~/projects/quickfind
$ quickfind init qf
Saved 'qf' -> /home/user/projects/quickfind

$ qfcd qf
# Instantly jumps to /home/user/projects/quickfind from anywhere in your terminal

$ quickfind list
Saved aliases:
  qf=/home/user/projects/quickfind
```

---

## Advanced Features

* **Shell Agnostic**: Works on any shell that supports POSIX-style login scripts. That includes `bash`, `zsh`, `sh`, `ksh`, and many more.
* **Cross-session Persistence**: Aliases persist across reboots and shell instances.
* **Scripting-Friendly**: Use `quickfind cd <alias>` in your scripts to dynamically resolve paths.
* **Lightweight**: No background processes, no daemons — just fast path resolution!

---

## Uninstallation

To remove `quickfind` and all of its related files, run:

```bash
brew uninstall aditya-baindur/quickfind/quickfind
```

> ⚠️ Note: This only removes the binary. If you want to do a full cleanup:
>
> ```bash
> sudo rm /etc/profile.d/qfcd.sh
> rm -rf ~/.quickfind
> ```

This will remove both the installed helper function and your saved aliases.

---

## Troubleshooting

QuickFind is designed to be minimal, simple, and reliable. But here are a few tips if something doesn't work as expected:

* Make sure `/etc/profile.d/qfcd.sh` is being sourced in your shell.
* If using `zsh`, consider adding this to your `~/.zprofile` manually:

```bash
source /etc/profile.d/qfcd.sh
```

* Verify that the binary is installed by running `which quickfind`
* If alias resolution fails, check that the alias exists by running `quickfind list`

Still having trouble? [File an issue](https://github.com/aditya-baindur/quickfind/issues) and describe your OS, shell, and what’s not working.

---

## Contributing

This project is open-source and community-driven. If you have a feature idea, bug fix, or OS-specific improvement, we'd love to hear from you!

To contribute:

1. Fork the repository
2. Make your changes in a new branch
3. Submit a pull request (with a description of what you did)

Ideas welcome — especially:

* Porting to additional operating systems (e.g., Windows)
* Adding shell completions (e.g., tab-autocomplete for aliases)
* Improving performance for very large alias sets

---

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for full terms and conditions.
