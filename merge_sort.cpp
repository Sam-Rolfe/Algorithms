#include <iostream>
#include <string>
#include <array>
using namespace std;


// Given an array of integers, 
// check if array is sorted. 
bool is_sorted(int* array, int array_length) {
    for(int i = 1; i < array_length; i++) {
      if(array[i] < array[i-1]) {
        return(false);
      }
    } 
    return(true); 
}

// Given array, print to std::out
void print_array(int* array, int array_length) {
    bool is_last = false;
    for(int i = 0; i < array_length; i++) {
        if(i == array_length - 1) {
            is_last = true;
        }
        if(is_last) {
            std::cout << array[i];
        } else {
            std::cout << array[i] << ", ";
        }
    }
    std::cout << std::endl;
}

// Given two sorted arrays, combine them and preserve sortedness.
// Return combined and sorted array
int* combine_sorted_arrays(int* sorted_array_left, int sorted_array_left_size, 
                           int* sorted_array_right, int sorted_array_right_size) {

    // Take the sum of the two array lengths for use in looping over elements
    int combined_array_length = sorted_array_left_size + sorted_array_right_size;

    // Create new array to house the sorted combination
    int* sorted_array = new int[combined_array_length];

    // Loop over elements for comparison
    int index_left = 0;
    int index_right = 0;
    bool left_complete = false;
    bool right_complete = false;
    bool add_left = false;

    for(int i = 0; i < combined_array_length; i++) {
        // Update flag used to signify whether left/right array has finished being added
        if(index_left == sorted_array_left_size) {
            left_complete = true;
        }
        if(index_right == sorted_array_right_size) {
            right_complete = true;
        }

        // If either sub-array is already completely added to the combined sorted
        // array, simply add the elements from the as-of-yet unadded array. Otherwise, 
        // compare values
        if(right_complete) {
            add_left = true;
        } else if ((!left_complete) && (sorted_array_left[index_left] < sorted_array_right[index_right])) {
            add_left = true;
        }
        
        // Debugging message
        if(left_complete && right_complete) {
            // std::cout << "---- Left: Complete. Right: Complete" << std::endl; 
        } else if(left_complete) {
            // std::cout << "---- Left: Complete. Right: " << sorted_array_right[index_right] << std::endl; 
        } else if (right_complete) {
            // std::cout << "---- Left: " << sorted_array_left[index_left] << " Right: Complete" << std::endl; 
        } else {
            // std::cout << "---- Left: " << sorted_array_left[index_left] << " Right: " << sorted_array_right[index_right] << std::endl;  
        }

        if(add_left) {
            // std::cout << "------ Adding left: " << sorted_array_left[index_left] << std::endl;  
            sorted_array[i] = sorted_array_left[index_left];
            index_left++;
        } else {
            // std::cout << "------ Adding right: " << sorted_array_right[index_right] << std::endl;  
            sorted_array[i] = sorted_array_right[index_right];
            index_right++;
        }
        add_left = false;
        // std::cout << "Printing partially sorted array: ";
        // print_array(sorted_array, i + 1);
    }
    // std::cout << "Printing sorted array: " << std::endl;
    // print_array(sorted_array, sorted_array_left_size + sorted_array_right_size);

    return(sorted_array);
}

// Given an array of integers, 
// sort using merge sort and return
// the sorted product
int* merge_sort(int* unsorted_array, int array_length) {
    // If array is sorted, return array
    if(is_sorted(unsorted_array, array_length)) {
        // std::cout << "Array is sorted: " << std::endl;
        // print_array(unsorted_array, array_length);
        return(unsorted_array);
    }

    // Else, sort left, sort right, 
    // then marge and sort
    int index_split = array_length / 2;
    int* sorted_array_left = merge_sort(unsorted_array, index_split);
    int* sorted_array_right = merge_sort(unsorted_array + index_split, array_length - index_split);
    int* sorted_array = combine_sorted_arrays(sorted_array_left, index_split, 
                                              sorted_array_right, array_length - index_split);

    // Return sorted array
    // print_array(sorted_array, array_length);
    return(sorted_array);
}

int main()
{
    int unsorted_array[] = {2, 1, 4, 8, 3};
    int array_length = sizeof(unsorted_array) / sizeof(unsorted_array[0]);
    int* sorted_array = merge_sort(unsorted_array, array_length);
    print_array(sorted_array, array_length);
}