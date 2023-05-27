#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int pivot_element(int* nums, int low, int high) {
    int pivot = nums[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (nums[j] <= pivot) {
            i++;
            swap(&nums[i], &nums[j]);
        }
    }
    swap(&nums[i + 1], &nums[high]);
    return i + 1;
}

void quicksort(int* nums, int low, int high) {
    if (low < high) {
        int pivot = pivot_element(nums, low, high);
        quicksort(nums, low, pivot - 1);
        quicksort(nums, pivot + 1, high);
    }
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    quicksort(nums1, 0, nums1Size - 1);
    quicksort(nums2, 0, nums2Size - 1);

    int count1 = 0;
    for (int i = 0; i < nums1Size - 1; i++) {
        if (nums1[i] == nums1[i + 1]) {
            count1++;
        }
    }

    int count2 = 0;
    for (int i = 0; i < nums2Size - 1; i++) {
        if (nums2[i] == nums2[i + 1]) {
            count2++;
        }
    }

    int t = -1;
    int* arr = malloc((nums1Size + nums2Size - count1 - count2) * sizeof(int));
    for (int i = 0; i < nums1Size - 1; i++) {
        if (nums1[i] != nums1[i + 1]) {
            t++;
            arr[t] = nums1[i];
        }
    }
    int index1 = nums1Size - 1;
    if (nums1[index1] != nums1[index1 - 1]) {
        arr[t + 1] = nums1[nums1Size - 1];
        t++;
    }

    t = t + 1;

    for (int i = 0; i < nums2Size - 1; i++) {
        if (nums2[i] != nums2[i + 1]) {
            t++;
            arr[t] = nums2[i];
        }
    }

    int index2 = nums2Size - 1;
    if (nums2[index2] != nums2[index2 - 1]) {
        arr[t + 1] = nums2[nums2Size - 1];
        t++;
    }

    quicksort(arr, 0, nums1Size + nums2Size - count1 - count2 - 1);
    for (int i = 0; i < nums1Size + nums2Size - count1 - count2 - 2; i++) {
        if (arr[i] == arr[i + 1]) {
            return &arr[i];
        }
    }
    return NULL;
}

int main() {
    int nums1[] = { 1, 2, 2, 1 };
    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
    int nums2[] = {1,22,3,4,1,1,5};
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);
    int returnSize;

    int* result = intersection(nums1, nums1Size, nums2, nums2Size, &returnSize);

    printf("Intersection: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return 0;
}
