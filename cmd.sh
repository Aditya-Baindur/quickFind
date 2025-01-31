#!/bin/zsh

# Check if the function block already exists in ~/.zshrc
if ! grep -q "# <<< INIT Function for cmd.sh" ~/.zshrc; then
    echo "Saving the init function to ~/.zshrc for future use..."

    # Append the function definitions to ~/.zshrc
    if [ -f ~/.zshrc ]; then
        cat << 'EOF' >> ~/.zshrc


# <<< INIT Function for cmd.sh  - © Aditya Baindur <<<

# Init function to save directory paths with custom commands for zsh

init() {
    local command_name="$1"
    local protected_commands=($(alias) $(whence -w))
    protected_commands=($(echo "${protected_commands[@]}" | tr ' ' '\n' | sort -u | tr '\n' ' '))
    
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
        if grep -q "alias $command_name=" ~/.zshrc; then
            echo "Alias '$command_name' already exists in ~/.zshrc. It will be updated."
            sed -i "" "/alias $command_name=/d" ~/.zshrc
        fi

        echo "alias $command_name='cd $current_path'" >> ~/.zshrc
        echo "Directory mapped successfully!"
        exec zsh
        echo "The changes have been applied. You can now use '$command_name' to navigate."
    else
        echo "Operation canceled. No changes were made."
    fi
}

rmv() {
    echo "Enter the custom command you'd like to remove (e.g., 'ad'): "
    read command_name
    if grep -q "alias $command_name=" ~/.zshrc; then
        echo "Are you sure you want to remove the alias '$command_name'? (y/n)"
        read confirmation
        if [[ "$confirmation" == "y" ]]; then
            sed -i "" "/alias $command_name=/d" ~/.zshrc
            echo "Alias '$command_name' has been removed."
            exec zsh
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
    grep "^alias " ~/.zshrc | while read -r line; do
        command=$(echo $line | cut -d'=' -f1 | sed 's/alias //')
        directory=$(echo $line | cut -d"'" -f2)
        echo "$command -> $directory"
    done
    echo "------"
}
EOF
        echo "The init, rmv, and list functions have been saved to ~/.zshrc!"
        echo "-----PLEASE RESTART THIS TERMINAL--------------"
        echo "You can do so by exiting and opening the terminal again."
        echo "Or, run 'source ~/.zshrc' in this terminal."
        echo "-----THIS IS ONLY FOR THE FIRST TIME SETUP-----"
    fi
else
    echo "The init function already exists in ~/.zshrc."
    echo "You can now use the 'init' command in your terminal."
fi
