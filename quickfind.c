#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define CONFIG_PATH_SUFFIX "/.quickfind/aliases.db"
#define MAX_LINE 512

char* get_config_path() {
    const char* home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Could not determine home directory.\n");
        exit(1);
    }

    static char path[1024];
    snprintf(path, sizeof(path), "%s%s", home, CONFIG_PATH_SUFFIX);
    return path;
}

void ensure_config() {
    const char* home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Could not determine home directory.\n");
        exit(1);
    }

    char dir[1024];
    snprintf(dir, sizeof(dir), "%s/.quickfind", home);
    mkdir(dir, 0755);  // create ~/.quickfind if it doesn't exist

    FILE* file = fopen(get_config_path(), "a");
    if (file) fclose(file);
}

void init_alias(const char* name) {
    char cwd[1024];
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("getcwd");
        exit(1);
    }

    FILE *file = fopen(get_config_path(), "a");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    fprintf(file, "%s=%s\n", name, cwd);
    fclose(file);
    printf("Saved '%s' -> %s\n", name, cwd);
}

void remove_alias(const char* name) {
    FILE *src = fopen(get_config_path(), "r");
    FILE *tmp = fopen("/tmp/.quickfind.tmp", "w");
    if (!src || !tmp) {
        fprintf(stderr, "Failed to open alias database or temp file.\n");
        exit(1);
    }

    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), src)) {
        if (strncmp(line, name, strlen(name)) != 0 || line[strlen(name)] != '=') {
            fputs(line, tmp);
        } else {
            found = 1;
        }
    }

    fclose(src);
    fclose(tmp);
    rename("/tmp/.quickfind.tmp", get_config_path());

    if (found)
        printf("Alias '%s' removed.\n", name);
    else
        printf("Alias '%s' not found.\n", name);
}

void list_aliases() {
    FILE *file = fopen(get_config_path(), "r");
    if (!file) {
        fprintf(stderr, "Alias DB not found. Use `quickfind init <alias>` first.\n");
        exit(1);
    }

    char line[MAX_LINE];
    printf("Saved aliases:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("  %s", line);
    }
    fclose(file);
}

void get_alias(const char* name) {
    FILE *file = fopen(get_config_path(), "r");
    if (!file) {
        fprintf(stderr, "Alias DB not found.\n");
        exit(1);
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == '=') {
            printf("%s", line + strlen(name) + 1);  // path only
            fclose(file);
            return;
        }
    }

    fclose(file);
    fprintf(stderr, "Alias '%s' not found.\n", name);
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("quickfind version 1.0.0\n");
            return 0;
        } else if (strcmp(argv[1], "--brew") == 0) {
            printf("true\n");
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("Usage: quickfind [init <alias> | rmv <alias> | list | cd <alias> | <alias>]\n");
            printf("  init <alias>   Save current directory as alias\n");
            printf("  rmv <alias>    Remove alias\n");
            printf("  list           Show all saved aliases\n");
            printf("  cd <alias>     Print path for alias (used by qfcd)\n");
            printf("  <alias>        Print path for alias\n");
            printf("Flags:\n");
            printf("  --version      Show version\n");
            printf("  --help         Show help\n");
            printf("  --brew         Used for Homebrew test\n");
            return 0;
        }
    }

    ensure_config();

    if (argc < 2) {
        fprintf(stderr, "Usage: quickfind [init|rmv|list|cd <alias>|<alias>]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0 && argc == 3) {
        init_alias(argv[2]);
    } else if (strcmp(argv[1], "rmv") == 0 && argc == 3) {
        remove_alias(argv[2]);
    } else if (strcmp(argv[1], "list") == 0) {
        list_aliases();
    } else if (strcmp(argv[1], "cd") == 0 && argc == 3) {
        get_alias(argv[2]);
    } else if (argc == 2) {
        get_alias(argv[1]);
    } else {
        fprintf(stderr, "Invalid command.\n");
        return 1;
    }

    return 0;
}
