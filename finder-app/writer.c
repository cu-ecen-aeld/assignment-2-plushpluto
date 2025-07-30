/*
 * writer.c
 * Author: plushpluto
 * Description:
 *   C application that creates a new file with specified content at a given path.
 *   This serves as an alternative to the writer.sh script from assignment 1.
 *   Uses File I/O and syslog logging as specified in the requirements.
 *
 * Usage:
 *   ./writer <writefile> <writestr>
 *
 * Parameters:
 *   writefile - full path to a file (including filename) on the filesystem
 *   writestr  - text string which will be written within the file
 *
 * Requirements:
 *   - Uses syslog with LOG_USER facility
 *   - Logs "Writing <string> to <file>" with LOG_DEBUG level
 *   - Logs errors with LOG_ERR level
 *   - Does not create directories (assumes caller creates them)
 *
 * Exit Codes:
 *   0 - Success
 *   1 - Invalid arguments or file creation failed
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    const char *writefile;
    const char *writestr;
    FILE *file;

    /* Initialize syslog with LOG_USER facility */
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    /* Check if both arguments are provided */
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Two arguments required - writefile and writestr");
        fprintf(stderr, "Error: Two arguments required - writefile and writestr\n");
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return 1;
    }

    writefile = argv[1];
    writestr = argv[2];

    /* Check if writefile argument is empty */
    if (strlen(writefile) == 0) {
        syslog(LOG_ERR, "Error: writefile argument cannot be empty");
        fprintf(stderr, "Error: writefile argument cannot be empty\n");
        closelog();
        return 1;
    }

    /* Check if writestr argument is empty */
    if (strlen(writestr) == 0) {
        syslog(LOG_ERR, "Error: writestr argument cannot be empty");
        fprintf(stderr, "Error: writestr argument cannot be empty\n");
        closelog();
        return 1;
    }

    /* Log the write operation with LOG_DEBUG level */
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    /* Open the file for writing (create/overwrite) */
    file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Could not create file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not create file %s: %s\n", writefile, strerror(errno));
        closelog();
        return 1;
    }

    /* Write the string to the file */
    if (fprintf(file, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Error: Could not write to file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not write to file %s: %s\n", writefile, strerror(errno));
        fclose(file);
        closelog();
        return 1;
    }

    /* Close the file */
    if (fclose(file) != 0) {
        syslog(LOG_ERR, "Error: Could not close file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not close file %s: %s\n", writefile, strerror(errno));
        closelog();
        return 1;
    }

    /* Success message */
    printf("File %s created successfully with content: %s\n", writefile, writestr);

    /* Close syslog */
    closelog();

    return 0;
}