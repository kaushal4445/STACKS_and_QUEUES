<div align="center">

# 📊 Sum of Subarray Ranges

### Optimal O(n) Approach using Monotonic Stacks

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Time](https://img.shields.io/badge/Time-O(n)-brightgreen?style=for-the-badge)
![Space](https://img.shields.io/badge/Space-O(n)-blue?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)

</div>

---

## 📌 Problem Statement

The **range** of a subarray is defined as:

```
range = max(subarray) - min(subarray)
```

Given an integer array `nums`, return the **sum of ranges of all its contiguous subarrays**.

> **Example**
> Input: `nums = [1, 2, 3]`
> Output: `4`

A brute-force solution checks every subarray in **O(n²)** and finds its min/max in **O(n)**, giving **O(n³)** — way too slow for large inputs. This repo documents the **O(n) optimal approach**.

---

## 💡 Core Insight

Instead of computing the range of each subarray directly, split the problem in two:

<div align="center">

**`Sum of Ranges = Sum of Subarray Maximums − Sum of Subarray Minimums`**

</div>

This works because subtraction distributes across every subarray:
`Σ(max − min) = Σ(max) − Σ(min)`

So the problem reduces to two classic, independently solvable sub-problems:

| Sub-problem | Goal |
|---|---|
| 🔻 `sumSubarrayMins` | Sum of the **minimum** element of every subarray |
| 🔺 `sumSubarrayMaxs` | Sum of the **maximum** element of every subarray |

Both are solved using the same trick: **for each element, count how many subarrays it is the min (or max) of** — using a **monotonic stack** to find boundaries in O(n), instead of checking every subarray.

---

## 🧠 The "Contribution" Technique

For every index `i`, instead of asking *"what is the min of this subarray?"*, we flip the question:

> **"In how many subarrays is `nums[i]` the minimum?"**

`nums[i]` is the minimum of a subarray `[L...R]` exactly when:
- `L` is anywhere between the **previous smaller element** and `i` (exclusive of the boundary)
- `R` is anywhere between `i` and the **next smaller-or-equal element** (exclusive of the boundary)

```
left  = i - prevSmaller[i]        → number of valid left endpoints
right = nextSmallerOrEqual[i] - i → number of valid right endpoints

contribution of nums[i] = nums[i] × left × right
```

Summing this contribution over all `i` gives `sumSubarrayMins` in a single O(n) pass (after computing boundaries).

The **maximum** case is the exact mirror image — using `previous greater` and `next greater-or-equal` boundaries.

> ⚠️ **Why one side is strict (`<`) and the other isn't (`<=`)?**
> To avoid double-counting subarrays when duplicate values are present. Exactly one boundary must be inclusive, or equal elements would be counted as the min/max of the same subarray twice.

---

## 🖼️ Visual Walkthrough

The diagram below traces the full algorithm step-by-step on `nums = [1, 2, 3]` — first computing every element's contribution to `sum of subarray minimums`, then to `sum of subarray maximums`, and finally combining them.

![Sum of Subarray Ranges - Optimal Approach Walkthrough](./assets/optimal-approach.png)

**Trace for `nums = [1, 2, 3]`:**

| i | value | prevSmaller | nextSmaller≤ | left | right | contribution (min) |
|---|---|---|---|---|---|---|
| 0 | 1 | -1 | 3 | 1 | 3 | 3 |
| 1 | 2 | 0 | 3 | 1 | 2 | 4 |
| 2 | 3 | 1 | 3 | 1 | 1 | 3 |

`sum of subarray minimums = 3 + 4 + 3 = 10`

| i | value | prevGreater | nextGreater≥ | left | right | contribution (max) |
|---|---|---|---|---|---|---|
| 0 | 1 | -1 | 1 | 1 | 1 | 1 |
| 1 | 2 | -1 | 2 | 2 | 1 | 4 |
| 2 | 3 | -1 | 3 | 3 | 1 | 9 |

`sum of subarray maximums = 1 + 4 + 9 = 14`

<div align="center">

### ✅ Final Answer: `14 − 10 = 4`

</div>

---

## ⚙️ Algorithm Breakdown

The solution needs **four monotonic-stack passes**, one for each boundary array:

| Function | Finds | Comparison |
|---|---|---|
| `findPSE` (Prev Smaller) | previous smaller element | strict `<` |
| `findNSE` (Next Smaller) | next smaller-or-equal | non-strict `>=` |
| `findPGE` (Prev Greater) | previous greater element | strict `>` |
| `findNGE` (Next Greater) | next greater-or-equal | non-strict `<=` |

Each is implemented with a **monotonic stack** that stores *indices*, not values — allowing O(1) amortized push/pop per element since each index enters and leaves the stack exactly once.

**Overall flow:**

```
subArrayRanges(nums)
   │
   ├── sumSubarrayMaxs(nums)
   │      ├── findNGE(nums)   → next greater-or-equal boundary
   │      ├── findPGE(nums)   → previous greater boundary
   │      └── Σ nums[i] × (i - pge[i]) × (nge[i] - i)
   │
   ├── sumSubarrayMins(nums)
   │      ├── findNSE(nums)   → next smaller-or-equal boundary
   │      ├── findPSE(nums)   → previous smaller boundary
   │      └── Σ nums[i] × (i - pse[i]) × (nse[i] - i)
   │
   └── return sumSubarrayMaxs - sumSubarrayMins
```

---

## 💻 C++ Solution

```cpp
class Solution {
private:
    // Next Smaller Element
    vector<int> findNSE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            ans[i] = !st.empty() ? st.top() : n;

            st.push(i);
        }

        return ans;
    }

    // Previous Smaller Element
    vector<int> findPSE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;

        for (int i = 0; i < n; i++) {

            while (!st.empty() && nums[st.top()] > nums[i]) {
                st.pop();
            }

            ans[i] = !st.empty() ? st.top() : -1;

            st.push(i);
        }

        return ans;
    }

    // Next Greater Element
    vector<int> findNGE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {

            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            ans[i] = !st.empty() ? st.top() : n;

            st.push(i);
        }

        return ans;
    }

    // Previous Greater Element
    vector<int> findPGE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;
        for (int i = 0; i < n; i++) {

            while (!st.empty() && nums[st.top()] < nums[i]) {
                st.pop();
            }
            ans[i] = !st.empty() ? st.top() : -1;

            st.push(i);
        }

        return ans;
    }

    long long sumSubarrayMins(vector<int>& nums) {

        int n = nums.size();

        vector<int> nse = findNSE(nums);
        vector<int> pse = findPSE(nums);

        long long sum = 0;

        for (int i = 0; i < n; i++) {

            long long left = i - pse[i];
            long long right = nse[i] - i;

            long long frequency = left * right;

            sum += frequency * nums[i];
        }

        return sum;
    }

    long long sumSubarrayMaxs(vector<int>& nums) {

        int n = nums.size();

        vector<int> nge = findNGE(nums);
        vector<int> pge = findPGE(nums);

        long long sum = 0;

        for (int i = 0; i < n; i++) {

            long long left = i - pge[i];
            long long right = nge[i] - i;

            long long frequency = left * right;

            sum += frequency * nums[i];
        }

        return sum;
    }

public:

    long long subArrayRanges(vector<int>& nums) {

        return sumSubarrayMaxs(nums) - sumSubarrayMins(nums);
    }
};
```

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Why |
|---|---|---|
| **Time** | `O(n)` | Each of the 4 stack passes is O(n) — every index is pushed and popped at most once |
| **Space** | `O(n)` | For the stack and the 4 boundary arrays (`pse`, `nse`, `pge`, `nge`) |

Compare this to the brute-force **O(n³)** (or a better-but-still-slow **O(n²)** using running min/max) — the monotonic stack approach scales comfortably to inputs of size `10⁵` or more.

---

## 🧪 Example Run

```text
Input:  nums = [1, 2, 3]

Step 1-4  → sum of subarray minimums = 10
Step 5-8  → sum of subarray maximums = 14
Step 9    → answer = 14 - 10 = 4

Output: 4
```

---

## 🗂️ Repository Structure

```
.
├── README.md
└── assets/
    └── optimal-approach.png     # step-by-step visual walkthrough
```

---

## 🏷️ Related Problems

- LeetCode 907 — Sum of Subarray Minimums
- LeetCode 2104 — Sum of Subarray Ranges
- Next Greater / Smaller Element (foundational monotonic stack pattern)

<div align="center">

---

Made with 🧠 and a monotonic stack

</div>