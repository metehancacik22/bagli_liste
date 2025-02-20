//
//  main.c
//  Bagli_Liste
//
//  Created by Metehan Cacık on 20.02.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LogNode {
    char timestamp[30];
    char hostname[50];
    char application[50];
    char message[256];
    struct LogNode* next;
} LogNode;

LogNode* createNode(char* timestamp, char* hostname, char* application, char* message) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    strcpy(newNode->timestamp, timestamp);
    strcpy(newNode->hostname, hostname);
    strcpy(newNode->application, application);
    strcpy(newNode->message, message);
    newNode->next = NULL;
    return newNode;
}

void appendNode(LogNode** head, LogNode* newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        LogNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printLogs(LogNode* head) {
    LogNode* temp = head;
    while (temp != NULL) {
        printf("[%s] %s %s: %s\n", temp->timestamp, temp->hostname, temp->application, temp->message);
        temp = temp->next;
    }
}

void freeList(LogNode* head) {
    LogNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void parseLogLine(char* line, LogNode** head) {
    char timestamp[30], hostname[50], application[50], message[256];
    
    scanf(line, "%s %s %s %[^:]: %[^\n]", timestamp, hostname, application, application, message);

    LogNode* newNode = createNode(timestamp, hostname, application, message);
    appendNode(head, newNode);
}

int main() {
    FILE* logFile;
    char line[512];
    LogNode* head = NULL;

    logFile = fopen("/var/log/syslog", "r");
    if (logFile == NULL) {
        perror("Log dosyası açılamadı");
        return 1;
    }

    while (fgets(line, sizeof(line), logFile)) {
        parseLogLine(line, &head);
    }
    fclose(logFile);

    printLogs(head);

    freeList(head);

    return 0;
}
