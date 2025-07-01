#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define CONFIG_PATH_SUFFIX "/.quickfind/aliases.db"
#define MAX_LINE 512
#define ZSHRC_APPEND_TAG "# <<< quickfind cd override >>>"

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
    getcwd(cwd, sizeof(cwd));

    FILE *file = fopen(get_config_path(), "a");
    fprintf(file, "%s=%s\n", name, cwd);
    fclose(file);
    printf("Saved '%s' -> %s\n", name, cwd);
}

void remove_alias(const char* name) {
    FILE *src = fopen(get_config_path(), "r");
    FILE *tmp = fopen("/tmp/.quickfind.tmp", "w");
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
    char line[MAX_LINE];
    printf("Saved aliases:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("  %s", line);
    }
    fclose(file);
}

void get_alias(const char* name) {
    FILE *file = fopen(get_config_path(), "r");
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == '=') {
            printf("%s", line + strlen(name) + 1);  // just print the path
            fclose(file);
            return;
        }
    }
    fclose(file);
    fprintf(stderr, "Alias '%s' not found.\n", name);
    exit(1);
}

void init_shell_integration() {
    const char* home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Unable to determine home directory.\n");
        exit(1);
    }

    char zshrc_path[1024];
    snprintf(zshrc_path, sizeof(zshrc_path), "%s/.zshrc", home);

    FILE* file = fopen(zshrc_path, "r");
    if (!file) {
        fprintf(stderr, "Could not open ~/.zshrc for reading.\n");
        return;
    }

    char line[MAX_LINE];
    int already_present = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, ZSHRC_APPEND_TAG)) {
            already_present = 1;
            break;
        }
    }
    fclose(file);

    if (already_present) {
        printf("Quickfind shell integration already exists in ~/.zshrc.\n");
        return;
    }

    file = fopen(zshrc_path, "a");
    if (!file) {
        fprintf(stderr, "Could not open ~/.zshrc for appending.\n");
        return;
    }

    fprintf(file, "\n%s\n", ZSHRC_APPEND_TAG);
    fprintf(file,
        "function cd() {\n"
        "  if quickfind \"$1\" >/dev/null 2>&1; then\n"
        "    builtin cd \"$(quickfind \"$1\")\"\n"
        "  else\n"
        "    builtin cd \"$@\"\n"
        "  fi\n"
        "}\n"
        "# <<< end quickfind cd override >>>\n\n"
    );
    fclose(file);

    printf("quickfind shell integration added to ~/.zshrc!\n");
    printf("Run `source ~/.zshrc` or restart your terminal to activate it.\n");
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
            printf("Usage: quickfind [init <name> | rmv <name> | list | init-shell | <alias>]\n");
            printf("Flags:\n");
            printf("  --version     Show version info\n");
            printf("  --help        Show this help message\n");
            return 0;
        }
    }

    ensure_config();

    if (argc < 2) {
        fprintf(stderr, "Usage: quickfind [init|rmv|list|init-shell|<alias>]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0 && argc == 3) {
        init_alias(argv[2]);
    } else if (strcmp(argv[1], "rmv") == 0 && argc == 3) {
        remove_alias(argv[2]);
    } else if (strcmp(argv[1], "list") == 0) {
        list_aliases();
    } else if (strcmp(argv[1], "init-shell") == 0) {
        init_shell_integration();
    } else if (argc == 2) {
        get_alias(argv[1]); // quickfind <alias>
    } else {
        fprintf(stderr, "Invalid command.\n");
        return 1;
    }

    return 0;
}