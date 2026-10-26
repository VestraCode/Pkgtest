#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    int  type, reqId, priority, msgId, targetId, userId, unk1, unk2, appId, errorNum, unk3;
    unsigned char useIconImageUri;
    char message[1024];
    char iconUri[1024];
    char unk[1024];
} OrbisNotificationRequest;

int sceKernelSendNotificationRequest(int device, OrbisNotificationRequest *req, size_t size, int blocking);
int sceKernelUsleep(unsigned int usec);

static void notify(const char *msg) {
    OrbisNotificationRequest r;
    memset(&r, 0, sizeof(r));
    r.type = 0;
    r.targetId = -1;
    strncpy(r.message, msg, sizeof(r.message) - 1);
    sceKernelSendNotificationRequest(0, &r, sizeof(r), 0);
}

int main(void) {
    notify("hello from gorilla test pkg");
    for (int i = 0;; i++) {
        printf("tick %d\n", i);
        sceKernelUsleep(1000000);
    }
    return 0;
}
