#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define TMP_PATH "/tmp/qfcd.sh"
#define DEST_DIR "/etc/profile.d"
#define DEST_PATH "/etc/profile.d/qfcd.sh"

int main() {
    // Step 1: Write the function to /tmp/qfcd.sh
    FILE *file = fopen(TMP_PATH, "w");
    if (!file) {
        fprintf(stderr, "❌ Failed to create temporary file at %s\n", TMP_PATH);
        return 1;
    }

    fprintf(file,
        "#!/bin/sh\n"
        "qfcd() {\n"
        "  cd \"$(quickfind cd \"$1\")\"\n"
        "}\n"
    );

    fclose(file);
    chmod(TMP_PATH, 0755);

    // Step 2: Ensure /etc/profile.d exists
    int mkdir_status = system("sudo mkdir -p " DEST_DIR);
    if (mkdir_status != 0) {
        fprintf(stderr, "❌ Failed to create directory %s\n", DEST_DIR);
        return 1;
    }

    // Step 3: Move it into place
    int mv_status = system("sudo mv " TMP_PATH " " DEST_PATH);
    if (mv_status != 0) {
        fprintf(stderr, "❌ Failed to move script to %s\n", DEST_PATH);
        return 1;
    }

    printf("✅ qfcd() function installed to %s\n", DEST_PATH);
    printf("ℹ️  It will now load in all POSIX login shells (bash, zsh, sh, etc.)\n");

    return 0;
}
