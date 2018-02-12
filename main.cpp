#include "mbed.h"
#include "storage-selector.h"

Semaphore format(0);

void btn_press() {
    format.release();
}

int main() {
    printf("FAT Formatter for Mbed\n");

    InterruptIn btn(BUTTON1);
    btn.fall(&btn_press);

    BlockDevice* bd = storage_selector();
    if (!bd) {
        printf("Cannot instantiate block device\n");
        return 1;
    }

    printf("Instantiated block device, press BUTTON1 to format\n");

    format.wait();

    printf("Formatting...\n");

    FATFileSystem fs(MBED_CONF_STORAGE_SELECTOR_MOUNT_POINT, bd);

    int v = fs.format(bd);
    if (v != 0) {
        printf("Formatting failed (%d)\n", v);
        return 1;
    }

    printf("Formatting OK\n");
}
