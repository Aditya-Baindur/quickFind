# quickFind - The ZSH terminal buddy 

Please note that this program is intended for use on **MACOS** and has NOT been tested for Windows or Linux.
If you do want to make version for those, please look at - [Contributing](#contributing)

## Table of Contents
- [Introduction](#introduction)
- [Installation](#installation)
- [Troubleshooting](#troubleshooting)
- [Usage](#usage)
- [Uninstallation Guide](#uninstallation)
- [Contributing](#contributing)
- [License](#license)

## Introduction

So the idea is simple. 

I wanted to make a bash script which basically allows you to basically `save` a directory path, so that wherever you are, you can just put the command in the cmd line, then you gonna be cd’ed into the main directory. 

This is especially useful when you want to work on a project with people and are using git. 

For example, I can map the command `ad` → `./user/desktop/bash_projects/”The Shortcut”`

and every time I do `ad`, i’ll be cd’ed into that directory

---

## Installation

Instructions for installing. 

You just need to run these 2 commands in your terminal, of you copy both commands and past then both in a terminal, it should work correctly too. 
You can also just do one command at a time. 

```bash
brew install aditya-baindur/aditya-baindur-homebrew-tap/quickfind
quickfind
```

When you finish installing it, just follow the instructions on screen and **exit** and **restart the terminal session**. 
---
Here’s a revised version of your troubleshooting guide:

---

## Troubleshooting

If you encounter the following error when running the `quickfind` command after installing with `brew install quickfind`:

```
grep: /Users/adityabaindur/.zshrc: No such file or directory
```

It means that the `.zshrc` file doesn't exist yet. To resolve this, simply run the following commands:

```bash
touch ~/.zshrc
quickfind
```

The `touch` command will create the `.zshrc` file, and then `quickfind` will run properly.

If you continue to experience issues, please [open a new issue](https://github.com/aditya-baindur/quickfind/issues) in the Issues tab.

---

Just replace `your-username/your-repository` with your actual GitHub username and repository name to link correctly.

---

## Usage
How to use the project.

Once you install it, there are a couple things : 

| Command | Arguments | Function                                | Example Usage       |
| ------- | --------- | --------------------------------------- | ------------------- |
| init    | yes       | Creates a new hotkey                    | `init yourname`      |
| rvm     | yes       | Removes an existing hotkey              | `rmv yourname`       |
| list    | no        | Lists all hotkeys created on the device | `list`               |


Please also note that the arguments are not strictly necessary, the program will prompt you to add or remove a name if you do not specify and argument.


Here’s a refined version of your uninstallation guide with some added clarity and detail for a smoother experience:

---

## Uninstallation

To uninstall **quickfind** and remove its configuration from your system, follow these steps carefully:

1. **Open your `~/.zshrc` file**:

   ```bash
   open ~/.zshrc
   ```

2. **Remove the `quickfind` configuration**:

   - Locate the following two sections in your `~/.zshrc` file:
     - `# <<< ALL FUNCTIONS FOR quickfind - © Aditya Baindur <<<`
     - `# <<< END OF quickfind - © Aditya Baindur <<<`

   - Delete everything between these two lines, **including** these lines themselves.

3. **Important**: Be cautious when editing your `~/.zshrc` file:

   - **Do not delete any other content** in the file, as this may affect your other configurations and extensions.
   - If you’re unsure, consider backing up your `~/.zshrc` file before making any changes.

4. **Save and close** the file.

5. You may need to **restart your terminal** or run `source ~/.zshrc` to apply the changes.

--- 


## Contributing
How to contribute.

You can fork this repo and have a pull request, I will review and update the brew formule if required. 

Some ideas which you can use to update this project would be to create the same version for Windows or a Linux distribution. 

Any other ideas are more than welcomed :) 

---

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
