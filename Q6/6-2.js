
// since all the indices are equal the numbers, we can use binary search search to take advantage of that
// we will look for the first false value (index != number), hence, our missing value!
function binarySearch(array){
    let low = 0;
    let high = 44;

    while (low <= high){
        let mid = low + Math.floor((high-low)/2);

        if (mid === array[mid]){
            low = mid+1;
        }
        else if (low === mid) {
            return mid;
        }
        else {
            high = mid;
        }
    }

    return low;
}

// assuming the missing number is 17  -- numbers are form 0 -> 44
// change the number to your liking 

let arr = [];

for (i=0; i<45; i++){
    if (i===19){
        continue;
    }
    arr.push(i);
}

let result = binarySearch(arr)
console.log(result);

