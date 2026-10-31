# Resume-Maker

A simple command-line tool I built in C to avoid manually formatting my resume and portfolio webpage. It asks for your details in the terminal and automatically generates both a styled `portfolio.html` site and a clean `resume.md` file.

## What it does
- Takes inputs for contact info, skills, projects, and education straight from the terminal.
- Uses C `structs` and dynamic memory (`malloc`) to store as many entries as you need.
- Writes everything out to a dark-mode HTML file and a Markdown document using standard file I/O (`fopen`/`fprintf`).

## How to run it

1. **Compile:**
   ```bash
   gcc Resume_Builder.c -o Resume_Builder
