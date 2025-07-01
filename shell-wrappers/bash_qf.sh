#!/bin/bash

# This script was made by Aditya Baindur in Canadian Winter 2025
# Last update - 2025-02-10 ; 18th April 2025
# All rights reserved 

# Check if the function block already exists in ~/.bashrc
if ! grep -q "# <<< ALL FUNCTIONS FOR quickfind - © Aditya Baindur - Winter 2025 <<<" ~/.bashrc; then
    echo "Saving the init function to ~/.bashrc for future use..."

    # Append the function definitions to ~/.bashrc
    if [ -f ~/.bashrc ]; then
        cat << 'EOF' >> ~/.bashrc


# <<< ALL FUNCTIONS FOR quickfind - © Aditya Baindur - Winter 2025 <<<

# Init function to save directory paths with custom commands for bash

protected_commands=($(builtin)) # Get built-in shell commands
protected_commands+=($(alias | awk -F= '{print $1}')) # Get existing aliases
protected_commands+=($(declare -F | awk '{print $3}')) # Get all defined shell functions
protected_commands+=("ls" "cd" "mv" "rm" "cp" "echo" "exit" "pwd" "source" "grep" "sed" "awk")


init() {
    local command_name="$1"
    current_path=$(pwd)  # Save the current working directory
    echo "Current directory is: $current_path"
    
    if [[ -z "$command_name" ]]; then
        echo "Enter the custom command you'd like to map to this directory (e.g., 'ad'): "
        read command_name
    fi

    # Check if the custom command is a protected shell command
    if [[ " ${protected_commands[@]} " =~ " $command_name " ]]; then
        echo "Error: '$command_name' is a reserved shell command. Please choose a different name."
        return 1
    fi

    echo "Mapping '$command_name' to the directory: $current_path"
    echo "Is this correct? (y/n)"
    read confirmation

    if [[ "$confirmation" == "y" ]]; then
        if grep -q "alias $command_name=" ~/.bashrc; then
            echo "Alias '$command_name' already exists in ~/.bashrc. It will be updated."
            sed -i "/alias $command_name=/d" ~/.bashrc
        fi

        echo "alias $command_name='cd $current_path'" >> ~/.bashrc
        echo "Directory mapped successfully!"
        exec bash
        echo "The changes have been applied. You can now use '$command_name' to navigate."
    else
        echo "Operation canceled. No changes were made."
    fi
}

rmv() {
    local command_name="$1"
    
    if [[ -z "$command_name" ]]; then
        echo "Enter the custom command you'd like to remove (e.g., 'ad'): "
        read command_name
    fi
    
    if grep -q "alias $command_name=" ~/.bashrc; then
        echo "Are you sure you want to remove the alias '$command_name'? (y/n)"
        read confirmation
        if [[ "$confirmation" == "y" ]]; then
            sed -i "/alias $command_name=/d" ~/.bashrc
            echo "Alias '$command_name' has been removed."
            exec bash
            echo "The changes have been applied."
        else
            echo "Operation canceled. No changes were made."
        fi
    else
        echo "No alias found for '$command_name'."
    fi
}

list() {
    echo "Listing all mapped commands and their directories:"
    echo "------"
    grep "^alias " ~/.bashrc | while read -r line; do
        command=$(echo $line | cut -d'=' -f1 | sed 's/alias //')
        directory=$(echo $line | cut -d"'" -f2)
        echo "$command -> $directory"
    done
    echo "------"
}

# <<< END OF quickfind - © Aditya Baindur - Winter 2025 <<<
EOF
        echo "The init, rmv, and list functions have been saved to ~/.bashrc!"
        echo "-----PLEASE RESTART THIS TERMINAL--------------"
        echo "You can do so by exiting and opening the terminal again."
        echo "Or, run 'source ~/.bashrc' in this terminal."
        echo "-----THIS IS ONLY FOR THE FIRST TIME SETUP-----"
    fi
else
    echo "The init function already exists in ~/.bashrc."
    echo "You can now use the 'init' command in your terminal."
fi
