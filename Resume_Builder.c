#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_TEXT 1024

/* --- Data Structures --- */

typedef struct {
    char fullName[MAX_LINE];
    char title[MAX_LINE];
    char email[MAX_LINE];
    char phone[MAX_LINE];
    char location[MAX_LINE];
    char github[MAX_LINE];
    char linkedin[MAX_LINE];
    char summary[MAX_TEXT];
} PersonalInfo;

typedef struct {
    char degree[MAX_LINE];
    char institution[MAX_LINE];
    char year[MAX_LINE];
    char score[MAX_LINE];
} Education;

typedef struct {
    char title[MAX_LINE];
    char techStack[MAX_LINE];
    char description[MAX_TEXT];
} Project;

typedef struct {
    char role[MAX_LINE];
    char organization[MAX_LINE];
    char duration[MAX_LINE];
    char description[MAX_TEXT];
} Experience;

typedef struct {
    PersonalInfo personal;

    Education *educationList;
    int educationCount;

    char **skills;
    int skillCount;

    Project *projectList;
    int projectCount;

    Experience *experienceList;
    int experienceCount;
} Profile;

/* --- Utility Helper Functions --- */

void readString(const char *prompt, char *buffer, int maxLen) {
    printf("%s", prompt);
    if (fgets(buffer, maxLen, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

int readInteger(const char *prompt) {
    char buf[64];
    readString(prompt, buf, sizeof(buf));
    return atoi(buf);
}

/* --- Section Input Handlers --- */

void inputPersonalInfo(PersonalInfo *p) {
    printf("\n========================================\n");
    printf("         PERSONAL INFORMATION           \n");
    printf("========================================\n");
    readString("Full Name: ", p->fullName, MAX_LINE);
    readString("Professional Title (e.g., Software Engineer): ", p->title, MAX_LINE);
    readString("Email: ", p->email, MAX_LINE);
    readString("Phone: ", p->phone, MAX_LINE);
    readString("Location (City, Country): ", p->location, MAX_LINE);
    readString("GitHub Profile / URL: ", p->github, MAX_LINE);
    readString("LinkedIn Profile / URL: ", p->linkedin, MAX_LINE);
    readString("Professional Summary / Bio:\n> ", p->summary, MAX_TEXT);
}

void inputEducation(Profile *prof) {
    int count = readInteger("\nHow many education entries would you like to add? ");
    if (count <= 0) return;

    prof->educationList = (Education *)malloc(count * sizeof(Education));
    if (!prof->educationList) {
        printf("Memory allocation failed for education entries.\n");
        return;
    }
    prof->educationCount = count;

    for (int i = 0; i < count; i++) {
        printf("\n--- Education Entry #%d ---\n", i + 1);
        readString("Degree / Certificate: ", prof->educationList[i].degree, MAX_LINE);
        readString("Institution / University: ", prof->educationList[i].institution, MAX_LINE);
        readString("Year / Duration (e.g., 2024 - 2028): ", prof->educationList[i].year, MAX_LINE);
        readString("GPA / Percentage / Honors: ", prof->educationList[i].score, MAX_LINE);
    }
}

void inputSkills(Profile *prof) {
    int count = readInteger("\nHow many technical skills would you like to add? ");
    if (count <= 0) return;

    prof->skills = (char **)malloc(count * sizeof(char *));
    if (!prof->skills) {
        printf("Memory allocation failed for skills.\n");
        return;
    }
    prof->skillCount = count;

    for (int i = 0; i < count; i++) {
        prof->skills[i] = (char *)malloc(MAX_LINE * sizeof(char));
        printf("Skill #%d (e.g., C/C++, Docker, PyTorch): ", i + 1);
        readString("", prof->skills[i], MAX_LINE);
    }
}

void inputProjects(Profile *prof) {
    int count = readInteger("\nHow many projects would you like to add? ");
    if (count <= 0) return;

    prof->projectList = (Project *)malloc(count * sizeof(Project));
    if (!prof->projectList) {
        printf("Memory allocation failed for projects.\n");
        return;
    }
    prof->projectCount = count;

    for (int i = 0; i < count; i++) {
        printf("\n--- Project #%d ---\n", i + 1);
        readString("Project Name: ", prof->projectList[i].title, MAX_LINE);
        readString("Tech Stack Used: ", prof->projectList[i].techStack, MAX_LINE);
        readString("Description & Key Metrics:\n> ", prof->projectList[i].description, MAX_TEXT);
    }
}

void inputExperience(Profile *prof) {
    int count = readInteger("\nHow many work/leadership experiences would you like to add? ");
    if (count <= 0) return;

    prof->experienceList = (Experience *)malloc(count * sizeof(Experience));
    if (!prof->experienceList) {
        printf("Memory allocation failed for experience.\n");
        return;
    }
    prof->experienceCount = count;

    for (int i = 0; i < count; i++) {
        printf("\n--- Experience #%d ---\n", i + 1);
        readString("Role / Position: ", prof->experienceList[i].role, MAX_LINE);
        readString("Company / Organization / Club: ", prof->experienceList[i].organization, MAX_LINE);
        readString("Duration (e.g., Jun 2025 - Present): ", prof->experienceList[i].duration, MAX_LINE);
        readString("Key Responsibilities / Impact:\n> ", prof->experienceList[i].description, MAX_TEXT);
    }
}

/* --- Exporters --- */

void exportHTML(const Profile *prof, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open %s for writing.\n", filename);
        return;
    }

    fprintf(fp, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n");
    fprintf(fp, "  <meta charset=\"UTF-8\">\n");
    fprintf(fp, "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(fp, "  <title>%s | Portfolio</title>\n", prof->personal.fullName);
    fprintf(fp, "  <style>\n");
    fprintf(fp, "    :root {\n");
    fprintf(fp, "      --bg-color: #0f172a;\n");
    fprintf(fp, "      --card-bg: #1e293b;\n");
    fprintf(fp, "      --accent: #38bdf8;\n");
    fprintf(fp, "      --text-main: #f8fafc;\n");
    fprintf(fp, "      --text-muted: #94a3b8;\n");
    fprintf(fp, "      --border: #334155;\n");
    fprintf(fp, "    }\n");
    fprintf(fp, "    * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; }\n");
    fprintf(fp, "    body { background-color: var(--bg-color); color: var(--text-main); line-height: 1.6; padding: 2rem 1rem; }\n");
    fprintf(fp, "    .container { max-width: 860px; margin: 0 auto; }\n");
    fprintf(fp, "    header { margin-bottom: 2.5rem; border-bottom: 1px solid var(--border); padding-bottom: 1.5rem; }\n");
    fprintf(fp, "    h1 { font-size: 2.5rem; font-weight: 700; color: #ffffff; letter-spacing: -0.025em; }\n");
    fprintf(fp, "    .title { font-size: 1.25rem; color: var(--accent); margin-top: 0.25rem; font-weight: 500; }\n");
    fprintf(fp, "    .meta-links { display: flex; flex-wrap: wrap; gap: 1rem; margin-top: 1rem; font-size: 0.9rem; color: var(--text-muted); }\n");
    fprintf(fp, "    .meta-links span { display: inline-flex; align-items: center; }\n");
    fprintf(fp, "    section { margin-bottom: 2.5rem; }\n");
    fprintf(fp, "    h2 { font-size: 1.4rem; color: #ffffff; border-left: 4px solid var(--accent); padding-left: 0.75rem; margin-bottom: 1.25rem; text-transform: uppercase; letter-spacing: 0.05em; }\n");
    fprintf(fp, "    .card { background: var(--card-bg); border: 1px solid var(--border); border-radius: 8px; padding: 1.25rem; margin-bottom: 1rem; }\n");
    fprintf(fp, "    .card-header { display: flex; justify-content: space-between; align-items: baseline; margin-bottom: 0.5rem; flex-wrap: wrap; }\n");
    fprintf(fp, "    .card-title { font-size: 1.1rem; font-weight: 600; color: #ffffff; }\n");
    fprintf(fp, "    .card-subtitle { color: var(--accent); font-size: 0.95rem; }\n");
    fprintf(fp, "    .card-date { color: var(--text-muted); font-size: 0.85rem; }\n");
    fprintf(fp, "    .card-body { color: var(--text-muted); font-size: 0.95rem; white-space: pre-line; }\n");
    fprintf(fp, "    .skill-badges { display: flex; flex-wrap: wrap; gap: 0.5rem; }\n");
    fprintf(fp, "    .badge { background: #334155; color: var(--accent); padding: 0.35rem 0.75rem; border-radius: 9999px; font-size: 0.85rem; font-weight: 500; }\n");
    fprintf(fp, "  </style>\n</head>\n<body>\n");

    fprintf(fp, "  <div class=\"container\">\n");
    fprintf(fp, "    <header>\n");
    fprintf(fp, "      <h1>%s</h1>\n", prof->personal.fullName);
    if (strlen(prof->personal.title) > 0)
        fprintf(fp, "      <div class=\"title\">%s</div>\n", prof->personal.title);

    fprintf(fp, "      <div class=\"meta-links\">\n");
    if (strlen(prof->personal.email) > 0)
        fprintf(fp, "        <span>Email: %s</span>\n", prof->personal.email);
    if (strlen(prof->personal.phone) > 0)
        fprintf(fp, "        <span>Phone: %s</span>\n", prof->personal.phone);
    if (strlen(prof->personal.location) > 0)
        fprintf(fp, "        <span>Location: %s</span>\n", prof->personal.location);
    if (strlen(prof->personal.github) > 0)
        fprintf(fp, "        <span>GitHub: %s</span>\n", prof->personal.github);
    if (strlen(prof->personal.linkedin) > 0)
        fprintf(fp, "        <span>LinkedIn: %s</span>\n", prof->personal.linkedin);
    fprintf(fp, "      </div>\n");
    fprintf(fp, "    </header>\n");

    if (strlen(prof->personal.summary) > 0) {
        fprintf(fp, "    <section>\n      <h2>About Me</h2>\n");
        fprintf(fp, "      <div class=\"card\"><p class=\"card-body\">%s</p></div>\n", prof->personal.summary);
        fprintf(fp, "    </section>\n");
    }

    if (prof->skillCount > 0) {
        fprintf(fp, "    <section>\n      <h2>Technical Skills</h2>\n      <div class=\"skill-badges\">\n");
        for (int i = 0; i < prof->skillCount; i++) {
            fprintf(fp, "        <span class=\"badge\">%s</span>\n", prof->skills[i]);
        }
        fprintf(fp, "      </div>\n    </section>\n");
    }

    if (prof->projectCount > 0) {
        fprintf(fp, "    <section>\n      <h2>Key Projects</h2>\n");
        for (int i = 0; i < prof->projectCount; i++) {
            fprintf(fp, "      <div class=\"card\">\n");
            fprintf(fp, "        <div class=\"card-header\">\n");
            fprintf(fp, "          <div class=\"card-title\">%s</div>\n", prof->projectList[i].title);
            fprintf(fp, "          <div class=\"card-subtitle\">%s</div>\n", prof->projectList[i].techStack);
            fprintf(fp, "        </div>\n");
            fprintf(fp, "        <p class=\"card-body\">%s</p>\n", prof->projectList[i].description);
            fprintf(fp, "      </div>\n");
        }
        fprintf(fp, "    </section>\n");
    }

    if (prof->experienceCount > 0) {
        fprintf(fp, "    <section>\n      <h2>Experience & Leadership</h2>\n");
        for (int i = 0; i < prof->experienceCount; i++) {
            fprintf(fp, "      <div class=\"card\">\n");
            fprintf(fp, "        <div class=\"card-header\">\n");
            fprintf(fp, "          <div class=\"card-title\">%s</div>\n", prof->experienceList[i].role);
            fprintf(fp, "          <div class=\"card-date\">%s</div>\n", prof->experienceList[i].duration);
            fprintf(fp, "        </div>\n");
            fprintf(fp, "        <div class=\"card-subtitle\" style=\"margin-bottom: 0.5rem;\">%s</div>\n", prof->experienceList[i].organization);
            fprintf(fp, "        <p class=\"card-body\">%s</p>\n", prof->experienceList[i].description);
            fprintf(fp, "      </div>\n");
        }
        fprintf(fp, "    </section>\n");
    }

    if (prof->educationCount > 0) {
        fprintf(fp, "    <section>\n      <h2>Education</h2>\n");
        for (int i = 0; i < prof->educationCount; i++) {
            fprintf(fp, "      <div class=\"card\">\n");
            fprintf(fp, "        <div class=\"card-header\">\n");
            fprintf(fp, "          <div class=\"card-title\">%s</div>\n", prof->educationList[i].degree);
            fprintf(fp, "          <div class=\"card-date\">%s</div>\n", prof->educationList[i].year);
            fprintf(fp, "        </div>\n");
            fprintf(fp, "        <div class=\"card-subtitle\">%s</div>\n", prof->educationList[i].institution);
            if (strlen(prof->educationList[i].score) > 0) {
                fprintf(fp, "        <p class=\"card-body\" style=\"margin-top: 0.25rem;\">Grade/Score: %s</p>\n", prof->educationList[i].score);
            }
            fprintf(fp, "      </div>\n");
        }
        fprintf(fp, "    </section>\n");
    }

    fprintf(fp, "  </div>\n</body>\n</html>\n");
    fclose(fp);
    printf("[+] Generated modern HTML portfolio: %s\n", filename);
}

void exportMarkdown(const Profile *prof, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open %s for writing.\n", filename);
        return;
    }

    fprintf(fp, "# %s\n\n", prof->personal.fullName);
    if (strlen(prof->personal.title) > 0) {
        fprintf(fp, "**%s**\n\n", prof->personal.title);
    }

    fprintf(fp, "%s | %s | %s", prof->personal.location, prof->personal.email, prof->personal.phone);
    if (strlen(prof->personal.github) > 0) fprintf(fp, " | [GitHub](%s)", prof->personal.github);
    if (strlen(prof->personal.linkedin) > 0) fprintf(fp, " | [LinkedIn](%s)", prof->personal.linkedin);
    fprintf(fp, "\n\n---\n\n");

    if (strlen(prof->personal.summary) > 0) {
        fprintf(fp, "## Professional Summary\n%s\n\n", prof->personal.summary);
    }

    if (prof->skillCount > 0) {
        fprintf(fp, "## Technical Skills\n");
        for (int i = 0; i < prof->skillCount; i++) {
            fprintf(fp, "`%s`%s", prof->skills[i], (i == prof->skillCount - 1) ? "" : " • ");
        }
        fprintf(fp, "\n\n");
    }

    if (prof->projectCount > 0) {
        fprintf(fp, "## Key Projects\n");
        for (int i = 0; i < prof->projectCount; i++) {
            fprintf(fp, "### %s\n", prof->projectList[i].title);
            fprintf(fp, "*Technologies:* %s\n\n", prof->projectList[i].techStack);
            fprintf(fp, "%s\n\n", prof->projectList[i].description);
        }
    }

    if (prof->experienceCount > 0) {
        fprintf(fp, "## Experience\n");
        for (int i = 0; i < prof->experienceCount; i++) {
            fprintf(fp, "### %s | %s\n", prof->experienceList[i].role, prof->experienceList[i].organization);
            fprintf(fp, "*%s*\n\n", prof->experienceList[i].duration);
            fprintf(fp, "%s\n\n", prof->experienceList[i].description);
        }
    }

    if (prof->educationCount > 0) {
        fprintf(fp, "## Education\n");
        for (int i = 0; i < prof->educationCount; i++) {
            fprintf(fp, "- **%s**, %s (%s)", prof->educationList[i].degree, prof->educationList[i].institution, prof->educationList[i].year);
            if (strlen(prof->educationList[i].score) > 0) {
                fprintf(fp, " — *Score: %s*", prof->educationList[i].score);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("[+] Generated Markdown resume: %s\n", filename);
}

void freeMemory(Profile *prof) {
    if (prof->educationList) free(prof->educationList);
    if (prof->projectList) free(prof->projectList);
    if (prof->experienceList) free(prof->experienceList);

    if (prof->skills) {
        for (int i = 0; i < prof->skillCount; i++) {
            free(prof->skills[i]);
        }
        free(prof->skills);
    }
}

int main(void) {
    Profile userProfile;
    memset(&userProfile, 0, sizeof(Profile));

    printf("====================================================\n");
    printf("   DYNAMIC PORTFOLIO & RESUME BUILDER (C ENGINE)    \n");
    printf("====================================================\n");

    inputPersonalInfo(&userProfile.personal);
    inputSkills(&userProfile);
    inputProjects(&userProfile);
    inputExperience(&userProfile);
    inputEducation(&userProfile);

    printf("\nGenerating artifacts...\n");
    exportHTML(&userProfile, "portfolio.html");
    exportMarkdown(&userProfile, "resume.md");

    freeMemory(&userProfile);

    printf("\nBuild complete. Check 'portfolio.html' and 'resume.md' in your current directory.\n");
    return 0;
}