class Quickfind < Formula
    desc "QuickFind - A useful ZSH script"
    homepage "https://github.com/Aditya-Baindur/quickFind"
    url "https://github.com/Aditya-Baindur/quickFind/archive/refs/tags/v1.0.0.tar.gz"
    sha256 "SHA256_CHECKSUM"  # Replace with actual checksum
  
    depends_on "zsh"  # Ensure Zsh is available for the script
  
    def install
      # Install the quickFind.zsh script to bin/
      bin.install "cmd.zsh"
    end
  
    def post_install
      # Run the script after installation
      system "#{bin}/cmd.zsh", "list"  # Adjust this to your needs
    end
  end
  