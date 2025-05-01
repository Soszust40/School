// Largest Monotonic Island (Each item is only 1 element apart and counting up or down)

method LargestMonotonicIsland(A: array<int>) returns (l: int, r: int)
    // Precondition: An array A with integer elements n, where 1 <= n <= 100
    requires 1 <= A.Length <= 100
    // Postcondition: l and r are valid indices, such that 0 <= l <= r < A.Length
    ensures 0 <= l <= r < A.Length
    // **Prove that the output indices correspond to a valid monotonic island.**
    // Postcondition: The subarray between l and r (inclusive) is a valid contiguous monotonic island,
    // where each element is either greater than or less than the next, and the difference between consecutive elements is +-1.
    ensures forall i :: (l <= i < r) ==> ((A[i] < A[i + 1] || A[i] > A[i + 1]) && ((A[i + 1] - A[i] == 1) || (A[i + 1] - A[i] == -1)))
{
    // Base case: If the array has only one element, the entire array is the island.
    if A.Length == 1 {
        l := 0;
        r := 0;
        return;
    }

    var maxL := 0;       // Start of the largest island
    var maxR := 0;       // End of the largest island
    var maxLength := 1;  // Length of the largest island

    var currentL := 0;   // Start of the current island
    var direction := 0;  // 1 for increasing, -1 for decreasing, 0 for no direction yet
    var i := 1;          // Iterations

    // **Prove the algorithm terminates**: Non-monotonic breaks finalize the current island.
    while i < A.Length
        invariant 0 <= currentL <= i <= A.Length    // Invariant: The indices are valid and within bounds
        invariant 0 <= maxL <= maxR < A.Length      // Invariant: The largest island found so far is valid
        invariant maxLength == maxR - maxL + 1      // Invariant: maxLength tracks the length of the largest monotonic island
        invariant forall j :: maxL <= j < maxR && j + 1 < A.Length ==> (A[j + 1] - A[j] == 1 || A[j + 1] - A[j] == -1)          // Invariant: The change between values in the island is only 1 if increasing
        invariant forall j :: currentL <= j < i - 1 && j + 1 < A.Length ==> (A[j + 1] - A[j] == 1 || A[j + 1] - A[j] == -1)     // Invariant: The change between values in the island is only -1 if decreasing
        decreases A.Length - i  // The measure is the remaining iterations of the loop
    {
        var diff := A[i] - A[i - 1];  // Difference between adjacent elements

        if diff == 1 {
            // Sequence is increasing and change by 1
            if direction == -1 {
                // If it was previously decreasing, finalize the current island
                var currentLength := i - currentL;
                // **Prove that the output island is the largest one in the array.**: When an island is found, only the biggest is kept.
                if currentLength > maxLength {
                    maxLength := currentLength;
                    maxL := currentL;
                    maxR := i - 1;
                }
                currentL := i - 1;  // Start new island from previous element
            }
            direction := 1;  // Mark as increasing
        } else if diff == -1 {
            // Sequence is decreasing and change by -1
            if direction == 1 {
                // If it was previously increasing, finalize the current island
                var currentLength := i - currentL;
                // **Prove that the output island is the largest one in the array.**: When an island is found, only the biggest is kept.
                if currentLength > maxLength {
                    maxLength := currentLength;
                    maxL := currentL;
                    maxR := i - 1;
                }
                currentL := i - 1;  // Start new island from previous element
            }
            direction := -1;  // Mark as decreasing
        } else {
            // No valid monotonic change, finalize the current island
            var currentLength := i - currentL;
            if currentLength > maxLength {
                maxLength := currentLength;
                maxL := currentL;
                maxR := i - 1;
            }
            currentL := i;  // Start a new island
        }
        i := i + 1;  // Increment the loop variable
    }

    // Finalize the last island after the loop ends
    var currentLength := A.Length - currentL;
    if currentLength > maxLength {
        maxL := currentL;
        maxR := A.Length - 1;
    }
    else if currentLength == maxLength && currentL < maxL {
        maxL := currentL;
        maxR := A.Length - 1;
    }

    // Return the indices of the largest monotonic island
    if maxLength == 0 {
        //  If no island is found, set both indices to 0
        l := 0;
        r := 0;
    } else {
        l := maxL;  // Return the start index of the largest island
        r := maxR;  // Return the end index of the largest island
    }
}

method Main()
{
    // Test cases
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    TestCase6();
    TestCase7();
    TestCase8();
    TestCase9();
    TestCase10();
}

method TestCase8() {
    var A := new int[8];
    A[0] := 1;
    A[1] := 2;
    A[2] := 3;
    A[3] := 1;
    A[4] := 1;
    A[5] := 2;
    A[6] := 2;
    A[7] := 3;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (0 , 2));
    print("\n");
    
}

method TestCase2() {
    var A := new int[6];
    A[0] := 3;
    A[1] := 2;
    A[2] := 1;
    A[3] := 2;
    A[4] := 3;
    A[5] := 4;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (2, 5));
    print("\n");
}

method TestCase5() {
    var A := new int[5];
    A[0] := 5;
    A[1] := 4;
    A[2] := 3;
    A[3] := 2;
    A[4] := 1;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (0 , 4));
    print("\n");
    
}

method TestCase4() {
    var A := new int[4];
    A[0] := 1;
    A[1] := 2;
    A[2] := 2;
    A[3] := 3;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (0 , 1));
    print("\n");
    
}

method TestCase9() {
    var A := new int[9];
    A[0] := 1;
    A[1] := 2;
    A[2] := 3;
    A[3] := 1;
    A[4] := 2;
    A[5] := 3;
    A[6] := 1;
    A[7] := 2;
    A[8] := 3;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (0 , 2));
    print("\n");
    
}

method TestCase1() {
    var A := new int[1];
    A[0] := 1;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (0 , 0));
    print("\n");
    
}

method TestCase6() {
    var A := new int[6];
    A[0] := 1;
    A[1] := 2;
    A[2] := 1;
    A[3] := 2;
    A[4] := 3;
    A[5] := 4;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (2 , 5));
    print("\n");
    
}

method TestCase7() {
    var A := new int[7];
    A[0] := 1;
    A[1] := 2;
    A[2] := 9;
    A[3] := 8;
    A[4] := 7;
    A[5] := 6;
    A[6] := 1;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (2 , 5));
    print("\n");
    
}

method TestCase10() {
    var A := new int[10];
    A[0] := 2;
    A[1] := 4;
    A[2] := 6;
    A[3] := 1;
    A[4] := 2;
    A[5] := 6;
    A[6] := 7;
    A[7] := 8;
    A[8] := 9;
    A[9] := 2;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (5 , 8));
    print("\n");
    
}

method TestCase3() {
    var A := new int[3];
    A[0] := 2;
    A[1] := 4;
    A[2] := 6;

    // Call LargestMonotonicIsland method
    var l, r := LargestMonotonicIsland(A);
    print(l, r);
    print((l, r) == (0, 0));
    print("\n");
    
}